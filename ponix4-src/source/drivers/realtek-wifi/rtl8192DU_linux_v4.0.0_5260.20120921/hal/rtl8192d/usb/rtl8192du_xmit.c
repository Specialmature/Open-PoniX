/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#define _RTL8192C_XMIT_C_
#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>
#include <rtw_byteorder.h>
#include <wifi.h>
#include <osdep_intf.h>
#include <circ_buf.h>
#include <usb_ops.h>
#include <rtl8192d_hal.h>

#if defined (PLATFORM_LINUX) && defined (PLATFORM_WINDOWS)
#error "Shall be Linux or Windows, but not both!\n"
#endif


s32	rtl8192du_init_xmit_priv(_adapter *padapter)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;

#ifdef PLATFORM_LINUX
	tasklet_init(&pxmitpriv->xmit_tasklet,
	     (void(*)(unsigned long))rtl8192du_xmit_tasklet,
	     (unsigned long)padapter);
#endif
#ifdef PLATFORM_FREEBSD
		TASK_INIT(&pxmitpriv->xmit_tasklet, 1, (task_fn_t *)rtl8192du_xmit_tasklet, (void *)padapter);
#endif

	return _SUCCESS;
}

void	rtl8192du_free_xmit_priv(_adapter *padapter)
{
}

u32 rtw_get_ff_hwaddr(struct xmit_frame	*pxmitframe);
u32 rtw_get_ff_hwaddr(struct xmit_frame	*pxmitframe)
{
	u32 addr;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;	
	
	switch(pattrib->qsel)
	{
		case 0:
		case 3:
			addr = BE_QUEUE_INX;
		 	break;
		case 1:
		case 2:
			addr = BK_QUEUE_INX;
			break;				
		case 4:
		case 5:
			addr = VI_QUEUE_INX;
			break;		
		case 6:
		case 7:
			addr = VO_QUEUE_INX;
			break;
		case 0x10:
			addr = BCN_QUEUE_INX;
			break;
		case 0x11://BC/MC in PS (HIQ)
			addr = HIGH_QUEUE_INX;
			break;
		case 0x12:
			addr = MGT_QUEUE_INX;
			break;
		default:
			addr = BE_QUEUE_INX;
			break;		
			
	}

	return addr;

}

int urb_zero_packet_chk(_adapter *padapter, int sz);
int urb_zero_packet_chk(_adapter *padapter, int sz)
{
	int blnSetTxDescOffset;
	struct dvobj_priv	*pdvobj = (struct dvobj_priv*)&padapter->dvobjpriv;	

	if ( pdvobj->ishighspeed )
	{
		if ( ( (sz + TXDESC_SIZE) % 512 ) == 0 ) {
			blnSetTxDescOffset = 1;
		} else {
			blnSetTxDescOffset = 0;
		}
	}
	else
	{
		if ( ( (sz + TXDESC_SIZE) % 64 ) == 0 ) 	{
			blnSetTxDescOffset = 1;
		} else {
			blnSetTxDescOffset = 0;
		}
	}
	
	return blnSetTxDescOffset;
	
}

void rtl8192du_cal_txdesc_chksum(struct tx_desc	*ptxdesc)
{
		u16	*usPtr = (u16*)ptxdesc;
		u32 count = 16;		// (32 bytes / 2 bytes per XOR) => 16 times
		u32 index;
		u16 checksum = 0;

		//Clear first
		ptxdesc->txdw7 &= cpu_to_le32(0xffff0000);
	
		for(index = 0 ; index < count ; index++){
			checksum = checksum ^ le16_to_cpu(*(usPtr + index));
		}

		ptxdesc->txdw7 |= cpu_to_le32(0x0000ffff&checksum);	

}

void fill_txdesc_sectype(struct pkt_attrib *pattrib, struct tx_desc *ptxdesc);
void fill_txdesc_sectype(struct pkt_attrib *pattrib, struct tx_desc *ptxdesc)
{
	if ((pattrib->encrypt > 0) && !pattrib->bswenc)
	{
		switch (pattrib->encrypt)
		{	
			//SEC_TYPE
			case _WEP40_:
			case _WEP104_:
					ptxdesc->txdw1 |= cpu_to_le32((0x01<<22)&0x00c00000);
					break;				
			case _TKIP_:
			case _TKIP_WTMIC_:	
					//ptxdesc->txdw1 |= cpu_to_le32((0x02<<22)&0x00c00000);
					ptxdesc->txdw1 |= cpu_to_le32((0x01<<22)&0x00c00000);
					break;
			case _AES_:
					ptxdesc->txdw1 |= cpu_to_le32((0x03<<22)&0x00c00000);
					break;
			case _NO_PRIVACY_:
			default:
					break;
		
		}
		
	}

}

void fill_txdesc_vcs(struct pkt_attrib *pattrib, u32 *pdw);
void fill_txdesc_vcs(struct pkt_attrib *pattrib, u32 *pdw)
{
	//DBG_8192C("cvs_mode=%d\n", pattrib->vcs_mode);	

	switch(pattrib->vcs_mode)
	{
		case RTS_CTS:
			*pdw |= cpu_to_le32(BIT(12));
			break;
		case CTS_TO_SELF:
			*pdw |= cpu_to_le32(BIT(11));
			break;
		case NONE_VCS:
		default:
			break;		
	}

	if(pattrib->vcs_mode)
	{
		*pdw |= cpu_to_le32(BIT(13));//ENABLE HW RTS
	}
}

void fill_txdesc_phy(struct pkt_attrib *pattrib, u32 *pdw);
void fill_txdesc_phy(struct pkt_attrib *pattrib, u32 *pdw)
{
	//DBG_8192C("bwmode=%d, ch_off=%d\n", pattrib->bwmode, pattrib->ch_offset);

	if(pattrib->ht_en)
	{
		*pdw |= (pattrib->bwmode&HT_CHANNEL_WIDTH_40)?	cpu_to_le32(BIT(25)):0;

		if(pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
			*pdw |= cpu_to_le32((0x01<<20)&0x003f0000);
		else if(pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_UPPER)
			*pdw |= cpu_to_le32((0x02<<20)&0x003f0000);
		else if(pattrib->ch_offset == HAL_PRIME_CHNL_OFFSET_DONT_CARE)
			*pdw |= 0;
		else
			*pdw |= cpu_to_le32((0x03<<20)&0x003f0000);
	}
}

#ifdef CONFIG_USB_TX_AGGREGATION
/*
	Insert Early mode 's Content,8Byte
Len1	Len0	Pkt_num
Len4	Len3	Len2

*/
VOID
InsertEMContent(IN struct xmit_frame *pxmitframe, IN u8 *VirtualAddress);
VOID
InsertEMContent(IN struct xmit_frame *pxmitframe, IN u8 *VirtualAddress)
{
	_rtw_memset(VirtualAddress, 0, 8);
	SET_EARLYMODE_PKTNUM(VirtualAddress, pxmitframe->EMPktNum);
	SET_EARLYMODE_LEN0(VirtualAddress, pxmitframe->EMPktLen[0]);
	SET_EARLYMODE_LEN1(VirtualAddress, pxmitframe->EMPktLen[1]);
	SET_EARLYMODE_LEN2_1(VirtualAddress, pxmitframe->EMPktLen[2]&0xF);
	SET_EARLYMODE_LEN2_2(VirtualAddress, pxmitframe->EMPktLen[2]>>4);
	SET_EARLYMODE_LEN3(VirtualAddress, pxmitframe->EMPktLen[3]);
	SET_EARLYMODE_LEN4(VirtualAddress, pxmitframe->EMPktLen[4]);
	//RT_PRINT_DATA(COMP_SEND, DBG_LOUD, "EM Header:", VirtualAddress, 8)
}

static void _update_txdesc(struct xmit_frame *pxmitframe, u8 *pmem, int sz)
{
	uint	qsel;
	_adapter				*padapter = pxmitframe->padapter;
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(padapter);
	struct dm_priv		*pdmpriv = &pHalData->dmpriv;
	struct pkt_attrib		*pattrib = &pxmitframe->attrib;
	struct tx_desc		*ptxdesc = (struct tx_desc*)pmem;
	sint	bmcst = IS_MCAST(pattrib->ra);
#ifdef CONFIG_P2P
	struct wifidirect_info*	pwdinfo = &padapter->wdinfo;
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
#endif //CONFIG_P2P

	_rtw_memset(ptxdesc, 0, sizeof(struct tx_desc));
	
	//4 offset 0
	ptxdesc->txdw0 |= cpu_to_le32(sz & 0x0000ffff);
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);
	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE + OFFSET_SZ) << OFFSET_SHT) & 0x00ff0000);//32 bytes for TX Desc
	
	if (bmcst) ptxdesc->txdw0 |= cpu_to_le32(BIT(24));

	RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
		 ("update_txdesc: offset0=0x%08x\n", ptxdesc->txdw0));

	//4 offset 4
	// pkt_offset, unit:8 bytes padding
	if (pxmitframe->pkt_offset > 0)
		ptxdesc->txdw1 |= cpu_to_le32((pxmitframe->pkt_offset << 26) & 0x7c000000);

#ifdef CONFIG_USB_TX_AGGREGATION
	if (pxmitframe->agg_num > 1)
		ptxdesc->txdw5 |= cpu_to_le32((pxmitframe->agg_num << 24) & 0xff000000);
#endif

	if (pxmitframe->frame_tag == DATA_FRAMETAG)
	{
		//4 offset 4
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id&0x1f);

		qsel = (uint)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid << 16) & 0x000f0000);

		fill_txdesc_sectype(pattrib, ptxdesc);

		if(pattrib->ampdu_en==_TRUE){
			ptxdesc->txdw1 |= cpu_to_le32(BIT(5));//AGG EN
			//Insert Early Mode Content after tx desc position.
			if(pHalData->bEarlyModeEnable){
				ptxdesc->txdw0 |= cpu_to_le32(((USB_HWDESC_HEADER_LEN-8) << OFFSET_SHT) & 0x00ff0000);//32 bytes for TX Desc
				if(pxmitframe->EMPktNum > 0){
					InsertEMContent(pxmitframe, pmem+TXDESC_SIZE);
				}
			}
		}
		else
		{
			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
		}


		//4 offset 8


		//4 offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum << 16) & 0xffff0000);


		//4 offset 16 , offset 20
		if (pattrib->qos_en)
			ptxdesc->txdw4 |= cpu_to_le32(BIT(6));//QoS

		if ((pattrib->ether_type != 0x888e) &&
		    (pattrib->ether_type != 0x0806) &&
		    (pattrib->dhcp_pkt != 1))
		{
			//Non EAP & ARP & DHCP type data packet

			fill_txdesc_vcs(pattrib, &ptxdesc->txdw4);
			fill_txdesc_phy(pattrib, &ptxdesc->txdw4);

			ptxdesc->txdw4 |= cpu_to_le32(0x00000008);//RTS Rate=24M
			ptxdesc->txdw5 |= cpu_to_le32(0x0001ff00);
			//ptxdesc->txdw5 |= cpu_to_le32(0x0000000b);//DataRate - 54M

			//use REG_INIDATA_RATE_SEL value
			ptxdesc->txdw5 |= cpu_to_le32(pdmpriv->INIDATA_RATE[pattrib->mac_id]);

			if (0)//for driver dbg
			{
				ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

				if (pattrib->ht_en)
					ptxdesc->txdw5 |= cpu_to_le32(BIT(6));//SGI

				ptxdesc->txdw5 |= cpu_to_le32(0x00000013);//init rate - mcs7
			}
		}
		else
		{
			// EAP data packet and ARP packet.
			// Use the 1M data rate to send the EAP/ARP packet.
			// This will maybe make the handshake smooth.

			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
		   	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

			if(pHalData->CurrentBandType92D == BAND_ON_5G)
				ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
		}

#ifdef CONFIG_P2P
		if(pregistrypriv->wifi_spec==1 && !rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
		{
			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
			
		   	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

			ptxdesc->txdw5 = cpu_to_le32(0x0001ff00);//

#ifdef CONFIG_USB_TX_AGGREGATION
			if (pxmitframe->agg_num > 1)
				ptxdesc->txdw5 |= cpu_to_le32((pxmitframe->agg_num << 24) & 0xff000000);
#endif
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
		}			
#endif //CONFIG_P2P

		//4 offset 24
#ifdef CONFIG_TCP_CSUM_OFFLOAD_TX
		if (pattrib->hw_tcp_csum == 1) {
			// ptxdesc->txdw6 = 0; // clear TCP_CHECKSUM and IP_CHECKSUM. It's zero already!!
			u8 ip_hdr_offset = 32 + pattrib->hdrlen + pattrib->iv_len + 8;
			ptxdesc->txdw7 = (1 << 31) | (ip_hdr_offset << 16);
			DBG_8192C("ptxdesc->txdw7 = %08x\n", ptxdesc->txdw7);
		}
#endif
	}
	else if(pxmitframe->frame_tag == MGNT_FRAMETAG)
	{
		//DBG_8192C("pxmitframe->frame_tag == MGNT_FRAMETAG\n");	

		//4 offset 4
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id&0x1f);

		qsel = (uint)(pattrib->qsel&0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid<< 16) & 0x000f0000);

		//fill_txdesc_sectype(pattrib, ptxdesc);


		//4 offset 8


		//4 offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);


		//4 offset 16
		ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate


		//4 offset 20
		if(pHalData->CurrentBandType92D == BAND_ON_5G)
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
	}
	else if(pxmitframe->frame_tag == TXAGG_FRAMETAG)
	{
		DBG_8192C("pxmitframe->frame_tag == TXAGG_FRAMETAG\n");
	}
	else
	{
		DBG_8192C("pxmitframe->frame_tag = %d\n", pxmitframe->frame_tag);

		//4 offset 4
		ptxdesc->txdw1 |= cpu_to_le32((4)&0x1f);//CAM_ID(MAC_ID)

		ptxdesc->txdw1 |= cpu_to_le32((6<< 16) & 0x000f0000);//raid

		//4 offset 8

		//4 offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum << 16) & 0xffff0000);


		//4 offset 16
		ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

		//4 offset 20
		if(pHalData->CurrentBandType92D == BAND_ON_5G)
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
	}

	// 2009.11.05. tynli_test. Suggested by SD4 Filen for FW LPS.
	// (1) The sequence number of each non-Qos frame / broadcast / multicast /
	// mgnt frame should be controled by Hw because Fw will also send null data
	// which we cannot control when Fw LPS enable.
	// --> default enable non-Qos data sequense number. 2010.06.23. by tynli.
	// (2) Enable HW SEQ control for beacon packet, because we use Hw beacon.
	// (3) Use HW Qos SEQ to control the seq num of Ext port non-Qos packets.
	// 2010.06.23. Added by tynli.
	if(!pattrib->qos_en)
	{		
		ptxdesc->txdw4 |= cpu_to_le32(BIT(7)); // Hw set sequence number
		ptxdesc->txdw3 |= cpu_to_le32((8 <<28)); //set bit3 to 1. Suugested by TimChen. 2009.12.29.
	}

	rtl8192du_cal_txdesc_chksum(ptxdesc);
}
#endif

static s32 update_txdesc(struct xmit_frame *pxmitframe, u8 *pmem, s32 sz)
{
	int	pull=0;
	uint	qsel;
	_adapter				*padapter = pxmitframe->padapter;
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(padapter);
	struct dm_priv		*pdmpriv = &pHalData->dmpriv;
#ifdef CONFIG_AP_MODE
	struct mlme_priv		*pmlmepriv = &padapter->mlmepriv;
#endif //CONFIG_AP_MODE
	struct pkt_attrib		*pattrib = &pxmitframe->attrib;
	struct tx_desc		*ptxdesc = (struct tx_desc *)pmem;
	sint	bmcst = IS_MCAST(pattrib->ra);
#ifdef CONFIG_P2P
	struct wifidirect_info*	pwdinfo = &padapter->wdinfo;
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
#endif //CONFIG_P2P
	

#ifndef CONFIG_USE_USB_BUFFER_ALLOC_TX
	if(urb_zero_packet_chk(padapter, sz)==0)
	{
		ptxdesc = (struct tx_desc *)(pmem+PACKET_OFFSET_SZ);
		pull = 1;
		pxmitframe->pkt_offset --;
	}
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_TX
		
	_rtw_memset(ptxdesc, 0, sizeof(struct tx_desc));

	if((pxmitframe->frame_tag&0x0f) == DATA_FRAMETAG)
	{
		//DBG_8192C("pxmitframe->frame_tag == DATA_FRAMETAG\n");			

		//offset 4
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id&0x1f);

		qsel = (uint)(pattrib->qsel & 0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel << QSEL_SHT) & 0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid<< 16) & 0x000f0000);

		fill_txdesc_sectype(pattrib, ptxdesc);


		if(pattrib->ampdu_en==_TRUE)
			ptxdesc->txdw1 |= cpu_to_le32(BIT(5));//AGG EN
		else
			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
		
		//offset 8
		

		//offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);


		//offset 16 , offset 20
		if (pattrib->qos_en)
			ptxdesc->txdw4 |= cpu_to_le32(BIT(6));//QoS

		if ((pattrib->ether_type != 0x888e) && (pattrib->ether_type != 0x0806) && (pattrib->dhcp_pkt != 1))
		{
              	//Non EAP & ARP & DHCP type data packet
              	
			fill_txdesc_vcs(pattrib, &ptxdesc->txdw4);
			fill_txdesc_phy(pattrib, &ptxdesc->txdw4);

			ptxdesc->txdw4 |= cpu_to_le32(0x00000008);//RTS Rate=24M
			ptxdesc->txdw5 |= cpu_to_le32(0x0001ff00);//
			//ptxdesc->txdw5 |= cpu_to_le32(0x0000000b);//DataRate - 54M

			//use REG_INIDATA_RATE_SEL value
			ptxdesc->txdw5 |= cpu_to_le32(pdmpriv->INIDATA_RATE[pattrib->mac_id]);

              	if(0)//for driver dbg
			{
				ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
				
				if(pattrib->ht_en)
					ptxdesc->txdw5 |= cpu_to_le32(BIT(6));//SGI

				ptxdesc->txdw5 |= cpu_to_le32(0x00000013);//init rate - mcs7
			}

		}
		else
		{
			// EAP data packet and ARP packet.
			// Use the 1M data rate to send the EAP/ARP packet.
			// This will maybe make the handshake smooth.

			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
			
		   	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

			if(pHalData->CurrentBandType92D == BAND_ON_5G)
			{
				ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
			}
#ifdef CONFIG_P2P
			else
			{
				//	Added by Albert 2011/06/09
				//	In the P2P mode, the driver should not support the b mode.
				//	So, the Tx packet shouldn't use the CCK rate
				if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
				{
					ptxdesc->txdw5 |= cpu_to_le32(BIT(2));	//	Use the 6M data rate.
				}
			}
#endif //CONFIG_P2P		

			
		}
		
#ifdef CONFIG_P2P
		if(pregistrypriv->wifi_spec==1 && !rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
		{
			ptxdesc->txdw1 |= cpu_to_le32(BIT(6));//AGG BK
			
		   	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate

			ptxdesc->txdw5 = cpu_to_le32(0x0001ff00);//
		
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
		}			
#endif //CONFIG_P2P

		//offset 24

#ifdef CONFIG_TCP_CSUM_OFFLOAD_TX
		if ( pattrib->hw_tcp_csum == 1 ) {
			// ptxdesc->txdw6 = 0; // clear TCP_CHECKSUM and IP_CHECKSUM. It's zero already!!
			u8 ip_hdr_offset = 32 + pattrib->hdrlen + pattrib->iv_len + 8;
			ptxdesc->txdw7 = (1 << 31) | (ip_hdr_offset << 16);
			DBG_8192C("ptxdesc->txdw7 = %08x\n", ptxdesc->txdw7);
		}
#endif
	}
	else if((pxmitframe->frame_tag&0x0f)== MGNT_FRAMETAG)
	{
		//DBG_8192C("pxmitframe->frame_tag == MGNT_FRAMETAG\n");	
		
		//offset 4		
		ptxdesc->txdw1 |= cpu_to_le32(pattrib->mac_id&0x1f);
		
		qsel = (uint)(pattrib->qsel&0x0000001f);
		ptxdesc->txdw1 |= cpu_to_le32((qsel<<QSEL_SHT)&0x00001f00);

		ptxdesc->txdw1 |= cpu_to_le32((pattrib->raid<< 16) & 0x000f0000);
		
		//fill_txdesc_sectype(pattrib, ptxdesc);
		
		//offset 8		

		//offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);
		
		//offset 16
		ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
		
		//offset 20
#ifdef CONFIG_AP_MODE
		if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
		{
			ptxdesc->txdw5 |= cpu_to_le32(BIT(17));//retry limit enable
			ptxdesc->txdw5 |= cpu_to_le32(0x00180000);//retry limit = 6
		}
#endif

		if(pHalData->CurrentBandType92D == BAND_ON_5G)
		{
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
		}
#ifdef CONFIG_INTEL_WIDI
		else if(padapter->mlmepriv.widi_state == INTEL_WIDI_STATE_LISTEN)
		{
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
		}
#endif //CONFIG_INTEL_WIDI
#ifdef CONFIG_P2P
		else
		{
			//	Added by Albert 2011/06/09
			//	In the P2P mode, the driver should not support the b mode.
			//	So, the Tx packet shouldn't use the CCK rate
			if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
			{
				ptxdesc->txdw5 |= cpu_to_le32(BIT(2));	//	Use the 6M data rate.
			}
		}
#endif //CONFIG_P2P		
		
	}
	else if((pxmitframe->frame_tag&0x0f) == TXAGG_FRAMETAG)
	{
		DBG_8192C("pxmitframe->frame_tag == TXAGG_FRAMETAG\n");
	}
#ifdef CONFIG_MP_INCLUDED
	else if((pxmitframe->frame_tag&0x0f) == MP_FRAMETAG)
	{
		fill_txdesc_for_mp(padapter, ptxdesc);
	}
#endif
	else
	{
		DBG_8192C("pxmitframe->frame_tag = %d\n", pxmitframe->frame_tag);
		
		//offset 4	
		ptxdesc->txdw1 |= cpu_to_le32((4)&0x1f);//CAM_ID(MAC_ID)
		
		ptxdesc->txdw1 |= cpu_to_le32((6<< 16) & 0x000f0000);//raid
		
		//offset 8		

		//offset 12
		ptxdesc->txdw3 |= cpu_to_le32((pattrib->seqnum<<16)&0xffff0000);
		
		//offset 16
		ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
		
		//offset 20
		if(pHalData->CurrentBandType92D == BAND_ON_5G)
			ptxdesc->txdw5 |= cpu_to_le32(BIT(2));// use OFDM 6Mbps
	}

	// 2009.11.05. tynli_test. Suggested by SD4 Filen for FW LPS.
	// (1) The sequence number of each non-Qos frame / broadcast / multicast /
	// mgnt frame should be controled by Hw because Fw will also send null data
	// which we cannot control when Fw LPS enable.
	// --> default enable non-Qos data sequense number. 2010.06.23. by tynli.
	// (2) Enable HW SEQ control for beacon packet, because we use Hw beacon.
	// (3) Use HW Qos SEQ to control the seq num of Ext port non-Qos packets.
	// 2010.06.23. Added by tynli.
	if(!pattrib->qos_en)
	{		
		ptxdesc->txdw4 |= cpu_to_le32(BIT(7)); // Hw set sequence number
		ptxdesc->txdw3 |= cpu_to_le32((8 <<28)); //set bit3 to 1. Suugested by TimChen. 2009.12.29.
	}

	//offset 0
	ptxdesc->txdw0 |= cpu_to_le32(sz&0x0000ffff);
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);
	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE+OFFSET_SZ)<<OFFSET_SHT)&0x00ff0000);//32 bytes for TX Desc
	
	if(bmcst)	
	{
		ptxdesc->txdw0 |= cpu_to_le32(BIT(24));
	}	

	RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("offset0-txdesc=0x%x\n", ptxdesc->txdw0));

	//offset 4
	//if(!pull) ptxdesc->txdw1 |= cpu_to_le32((0x01<<26)&0xff000000);//pkt_offset, unit:8 bytes padding
	// pkt_offset, unit:8 bytes padding
	if (pxmitframe->pkt_offset > 0)
		ptxdesc->txdw1 |= cpu_to_le32((pxmitframe->pkt_offset << 26) & 0x7c000000);

#ifdef CONFIG_USB_TX_AGGREGATION
	if (pxmitframe->agg_num > 1)
		ptxdesc->txdw5 |= cpu_to_le32((pxmitframe->agg_num << 24) & 0xff000000);
#endif

	rtl8192du_cal_txdesc_chksum(ptxdesc);
		
	return pull;
		
}

void rtw_dump_xframe(_adapter *padapter, struct xmit_frame *pxmitframe);
void rtw_dump_xframe(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	int t, sz, w_sz, pull=0;
	u8 *mem_addr;
	u32 ff_hwaddr;
	struct xmit_buf *pxmitbuf = pxmitframe->pxmitbuf;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
#ifdef CONFIG_TDLS
	struct sta_priv 	*pstapriv = &padapter->stapriv;
	struct sta_info *ptdls_sta=NULL, *psta_backup=NULL;
	u8 ra_backup[6];
#endif //CONFIG_TDLS

	if ((pxmitframe->frame_tag == DATA_FRAMETAG) &&
	    (pxmitframe->attrib.ether_type != 0x0806) &&
	    (pxmitframe->attrib.ether_type != 0x888e) &&
	    (pxmitframe->attrib.dhcp_pkt != 1))
	{
#ifdef CONFIG_TDLS
		ptdls_sta = rtw_get_stainfo(pstapriv, pattrib->dst);
		if((ptdls_sta!=NULL)&&(ptdls_sta->tdls_sta_state & TDLS_LINKED_STATE))
		{
			psta_backup = pattrib->psta;
			pattrib->psta = ptdls_sta;
			_rtw_memcpy(ra_backup, pattrib->ra, ETH_ALEN);
			_rtw_memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
			rtw_issue_addbareq_cmd(padapter, pxmitframe);
			pattrib->psta = psta_backup;
			_rtw_memcpy(pattrib->ra, ra_backup, ETH_ALEN);
		}
#endif //CONFIG_TDLS
		rtw_issue_addbareq_cmd(padapter, pxmitframe);
	}

	mem_addr = pxmitframe->buf_addr;

       RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("rtw_dump_xframe()\n"));
	
	for (t = 0; t < pattrib->nr_frags; t++)
	{
		if (t != (pattrib->nr_frags - 1))
		{
			RT_TRACE(_module_rtl871x_xmit_c_,_drv_err_,("pattrib->nr_frags=%d\n", pattrib->nr_frags));

			sz = pxmitpriv->frag_len;
			sz = sz - 4 - (psecuritypriv->sw_encrypt ? 0 : pattrib->icv_len);					
		}
		else //no frag
		{
			sz = pattrib->last_txcmdsz;
		}

		pull = update_txdesc(pxmitframe, mem_addr, sz);
		
		if(pull)
		{
			mem_addr += PACKET_OFFSET_SZ; //pull txdesc head
			
			//pxmitbuf ->pbuf = mem_addr;			
			pxmitframe->buf_addr = mem_addr;

			w_sz = sz + TXDESC_SIZE;
		}
		else
		{
			w_sz = sz + TXDESC_SIZE + PACKET_OFFSET_SZ;
		}	

		ff_hwaddr = rtw_get_ff_hwaddr(pxmitframe);

		rtw_write_port(padapter, ff_hwaddr, w_sz, (unsigned char*)pxmitbuf);

		rtw_count_tx_stats(padapter, pxmitframe, sz);


		RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("rtw_write_port, w_sz=%d\n", w_sz));
		//DBG_8192C("rtw_write_port, w_sz=%d, sz=%d, txdesc_sz=%d, tid=%d\n", w_sz, sz, w_sz-sz, pattrib->priority);      

		mem_addr += w_sz;

		mem_addr = (u8 *)RND4(((SIZE_PTR)(mem_addr)));

	}
	
	rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
	
}


#ifdef CONFIG_USB_TX_AGGREGATION
static u32 xmitframe_need_length(struct xmit_frame *pxmitframe)
{
	struct pkt_attrib *pattrib = &pxmitframe->attrib;

	u32	len = 0;

	// no consider fragement
	len = pattrib->hdrlen + pattrib->iv_len +
		SNAP_SIZE + sizeof(u16) +
		pattrib->pktlen +
		((pattrib->bswenc) ? pattrib->icv_len : 0);

	if(pattrib->encrypt ==_TKIP_)
		len += 8;

	return len;
}

void UpdateEarlyModeInfo8192D(_adapter *padapter, struct xmit_frame *pxmitframe,struct tx_servq	*ptxservq);
void UpdateEarlyModeInfo8192D(_adapter *padapter, struct xmit_frame *pxmitframe,struct tx_servq	*ptxservq)
{
	_irqL irqL;
	u32	len;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct pkt_attrib	*pattrib = &pxmitframe->attrib;
	_list *xmitframe_plist = NULL, *xmitframe_phead = NULL;

	//Some macaddr can't do early mode.
	if(MacAddr_isBcst(pattrib->dst) ||IS_MCAST(pattrib->dst) || !!pattrib->qos_en)
		return;

	pxmitframe->EMPktNum = 0;

	// dequeue same priority packet from station tx queue
	_enter_critical_bh(&pxmitpriv->lock, &irqL);

	xmitframe_phead = get_list_head(&ptxservq->sta_pending);
	xmitframe_plist = get_next(xmitframe_phead);
	while ((rtw_end_of_queue_search(xmitframe_phead, xmitframe_plist) == _FALSE)&&(pxmitframe->EMPktNum < 5))
	{
		pxmitframe = LIST_CONTAINOR(xmitframe_plist, struct xmit_frame, list);
		xmitframe_plist = get_next(xmitframe_plist);

		len = xmitframe_need_length(pxmitframe);
		pxmitframe->EMPktLen[pxmitframe->EMPktNum] = len;
		pxmitframe->EMPktNum++;
	}
	_exit_critical_bh(&pxmitpriv->lock, &irqL);

}

#if 1
#define IDEA_CONDITION 1	// check all packets before enqueue
s32 rtl8192du_xmitframe_complete(_adapter *padapter, struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct xmit_frame *pxmitframe = NULL;
	struct xmit_frame *pfirstframe = NULL;

	// aggregate variable
	struct hw_xmit	*phwxmit = pxmitpriv->hwxmits;
	struct tx_servq	*ptxservq = NULL;

	_irqL irqL;
	_list *xmitframe_plist = NULL, *xmitframe_phead = NULL;

	u32	pbuf=0; // next pkt address
	u32	pbuf_tail; // last pkt tail
	u32	len=0; //packet length, except TXDESC_SIZE and PKT_OFFSET
	u32	aggMaxLength = MAX_XMITBUF_SZ;
	u32	bulkSize = pHalData->UsbBulkOutSize;
	u32	bulkPtr=0;
	u8	descCount=0;
	u8	ac_index;
	u8	bfirst = _TRUE;//first aggregation xmitframe
	u8	bulkstart = _FALSE;

	// dump frame variable
	u32 ff_hwaddr;

#ifndef IDEA_CONDITION
	int res = _SUCCESS;
#endif

	RT_TRACE(_module_rtl8192c_xmit_c_, _drv_info_, ("+xmitframe_complete\n"));

	// check xmitbuffer is ok
	if (pxmitbuf == NULL) {
		pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
		if (pxmitbuf == NULL) return _FALSE;
	}

	if(pHalData->MacPhyMode92D==SINGLEMAC_SINGLEPHY)
		aggMaxLength = MAX_XMITBUF_SZ;
	else
		aggMaxLength = 0x3D00;

	do {
		//3 1. pick up first frame
		if(bfirst)
		{
			pxmitframe = rtw_dequeue_xframe(pxmitpriv, pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);
			if (pxmitframe == NULL) {
				// no more xmit frame, release xmit buffer
				rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
				return _FALSE;
			}

			pxmitframe->pxmitbuf = pxmitbuf;
			pxmitframe->buf_addr = pxmitbuf->pbuf;
			pxmitbuf->priv_data = pxmitframe;

			//pxmitframe->agg_num = 1; // alloc xmitframe should assign to 1.
			pxmitframe->pkt_offset = USB_92D_DUMMY_OFFSET; // first frame of aggregation, reserve 2 offset for 512 alignment and early mode

			pfirstframe = pxmitframe;
			ptxservq = rtw_get_sta_pending(padapter, pfirstframe->attrib.psta, pfirstframe->attrib.priority, (u8 *)(&ac_index));
		}
		//3 2. aggregate same priority and same DA(AP or STA) frames
		else
		{
			// dequeue same priority packet from station tx queue
			_enter_critical_bh(&pxmitpriv->lock, &irqL);

			if (_rtw_queue_empty(&ptxservq->sta_pending) == _FALSE)
			{
				xmitframe_phead = get_list_head(&ptxservq->sta_pending);
				xmitframe_plist = get_next(xmitframe_phead);

				pxmitframe = LIST_CONTAINOR(xmitframe_plist, struct xmit_frame, list);


				len = xmitframe_need_length(pxmitframe) + TXDESC_SIZE + ((USB_92D_DUMMY_OFFSET - 1) * PACKET_OFFSET_SZ);
				if (pbuf + _RND8(len) > aggMaxLength)
				{
					bulkstart = _TRUE;
				}
				else
				{
					rtw_list_delete(&pxmitframe->list);
					ptxservq->qcnt--;
					phwxmit[ac_index].accnt--;

					//Remove sta node when there is no pending packets.
					if (_rtw_queue_empty(&ptxservq->sta_pending) == _TRUE)
						rtw_list_delete(&ptxservq->tx_pending);
				}
			}
			else
			{
				bulkstart = _TRUE;
			}

			_exit_critical_bh(&pxmitpriv->lock, &irqL);

			if(bulkstart)
			{
				break;
			}

			pxmitframe->buf_addr = pxmitbuf->pbuf + pbuf;

			pxmitframe->agg_num = 0; // not first frame of aggregation
			pxmitframe->pkt_offset = USB_92D_DUMMY_OFFSET - 1; // not first frame of aggregation, reserve 1 offset for early mode
		}

		if(pHalData->bEarlyModeEnable)
			UpdateEarlyModeInfo8192D(padapter, pxmitframe,ptxservq);

#ifdef IDEA_CONDITION
		rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
#else
		res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
		if (res == _FALSE) {
			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}
#endif

		// always return ndis_packet after rtw_xmitframe_coalesce
		rtw_os_xmit_complete(padapter, pxmitframe);

		if(bfirst)
		{
			len = xmitframe_need_length(pfirstframe) + USB_HWDESC_HEADER_LEN;
			pbuf_tail = len;
			pbuf = _RND8(pbuf_tail);

			descCount = 0;
			bulkPtr = bulkSize;
			bfirst = _FALSE;
		}
		else
		{
			_update_txdesc(pxmitframe, pxmitframe->buf_addr, pxmitframe->attrib.last_txcmdsz);

			// don't need xmitframe any more
			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);

			// handle pointer and stop condition
			pbuf_tail = pbuf + len;
			pbuf = _RND8(pbuf_tail);

			pfirstframe->agg_num++;
			if (MAX_TX_AGG_PACKET_NUMBER == pfirstframe->agg_num)
				break;
		}

		// check pkt amount in one bluk
		if (pbuf < bulkPtr)
		{
			descCount++;
			if (descCount == pHalData->UsbTxAggDescNum)
				break;
		}
		else
		{
			descCount = 0;
			bulkPtr = ((pbuf / bulkSize) + 1) * bulkSize; // round to next bulkSize
		}
	} while (1);

	if ((pfirstframe->attrib.ether_type != 0x0806) &&
	    (pfirstframe->attrib.ether_type != 0x888e) &&
	    (pfirstframe->attrib.dhcp_pkt != 1))
	{
		rtw_issue_addbareq_cmd(padapter, pfirstframe);
	}

#ifndef CONFIG_USE_USB_BUFFER_ALLOC_TX
	//3 3. update first frame txdesc
	if ((pbuf_tail % bulkSize) == 0) {
		// remove 1 pkt_offset
		pbuf_tail -= PACKET_OFFSET_SZ;
		pfirstframe->buf_addr += PACKET_OFFSET_SZ;
		pfirstframe->pkt_offset--;
	}
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_TX
	_update_txdesc(pfirstframe, pfirstframe->buf_addr, pfirstframe->attrib.last_txcmdsz);

	//3 4. write xmit buffer to USB FIFO
	ff_hwaddr = rtw_get_ff_hwaddr(pfirstframe);

	// xmit address == ((xmit_frame*)pxmitbuf->priv_data)->buf_addr
	rtw_write_port(padapter, ff_hwaddr, pbuf_tail, (u8*)pxmitbuf);

	//3 5. update statisitc
	pbuf_tail -= (pfirstframe->agg_num * TXDESC_SIZE);
	//if (pfirstframe->pkt_offset == 1) pbuf_tail -= PACKET_OFFSET_SZ;
	pbuf_tail -= (pfirstframe->pkt_offset * PACKET_OFFSET_SZ);
	
	rtw_count_tx_stats(padapter, pfirstframe, pbuf_tail);

	rtw_free_xmitframe_ex(pxmitpriv, pfirstframe);

	return _TRUE;
}
#else
#define IDEA_CONDITION 1	// check all packets before enqueue
s32 rtl8192du_xmitframe_complete(_adapter *padapter, struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct xmit_frame *pxmitframe = NULL;
	struct xmit_frame *pfirstframe = NULL;

	// aggregate variable
	//struct hw_xmit *phwxmit;
	struct sta_info *psta = NULL;
	struct tx_servq *ptxservq = NULL;

	_irqL irqL;
	_list *xmitframe_plist = NULL, *xmitframe_phead = NULL;

	u32	pbuf;	// next pkt address
	u32	pbuf_tail;	// last pkt tail
	u32	len;	// packet length, except TXDESC_SIZE and PKT_OFFSET
	u32	aggMaxLength = MAX_XMITBUF_SZ;
	u32	bulkSize = pHalData->UsbBulkOutSize;
	u8	descCount;
	u32	bulkPtr;

	// dump frame variable
	u32 ff_hwaddr;

#ifndef IDEA_CONDITION
	int res = _SUCCESS;
#endif

	RT_TRACE(_module_rtl8192c_xmit_c_, _drv_info_, ("+xmitframe_complete\n"));


	// check xmitbuffer is ok
	if (pxmitbuf == NULL) {
		pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
		if (pxmitbuf == NULL) return _FALSE;
	}

	if(pHalData->MacPhyMode92D==SINGLEMAC_SINGLEPHY)
		aggMaxLength = MAX_XMITBUF_SZ;
	else
		aggMaxLength = 0x3D00;

	//3 1. pick up first frame
	do {
		rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			
		pxmitframe = rtw_dequeue_xframe(pxmitpriv, pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);
		if (pxmitframe == NULL) {
			// no more xmit frame, release xmit buffer
			rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
			return _FALSE;
		}


#ifndef IDEA_CONDITION
		if (pxmitframe->frame_tag != DATA_FRAMETAG) {
			RT_TRACE(_module_rtl8192c_xmit_c_, _drv_err_,
				 ("xmitframe_complete: frame tag(%d) is not DATA_FRAMETAG(%d)!\n",
				  pxmitframe->frame_tag, DATA_FRAMETAG));
//			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}

		// TID 0~15
		if ((pxmitframe->attrib.priority < 0) ||
		    (pxmitframe->attrib.priority > 15)) {
			RT_TRACE(_module_rtl8192c_xmit_c_, _drv_err_,
				 ("xmitframe_complete: TID(%d) should be 0~15!\n",
				  pxmitframe->attrib.priority));
//			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}
#endif

		pxmitframe->pxmitbuf = pxmitbuf;
		pxmitframe->buf_addr = pxmitbuf->pbuf;
		pxmitbuf->priv_data = pxmitframe;

		//pxmitframe->agg_num = 1; // alloc xmitframe should assign to 1.
		pxmitframe->pkt_offset = 1; // first frame of aggregation, reserve offset

#ifdef IDEA_CONDITION
		rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
#else
		res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
		if (res == _FALSE) {
//			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}
#endif

		// always return ndis_packet after rtw_xmitframe_coalesce
		rtw_os_xmit_complete(padapter, pxmitframe);

		break;
	} while (1);

	//3 2. aggregate same priority and same DA(AP or STA) frames
	pfirstframe = pxmitframe;
	len = xmitframe_need_length(pfirstframe) + TXDESC_OFFSET;
	pbuf_tail = len;
	pbuf = _RND8(pbuf_tail);

	// check pkt amount in one bluk
	descCount = 0;
	bulkPtr = bulkSize;
	if (pbuf < bulkPtr)
		descCount++;
	else {
		descCount = 0;
		bulkPtr = ((pbuf / bulkSize) + 1) * bulkSize; // round to next bulkSize
	}

	// dequeue same priority packet from station tx queue
	psta = pfirstframe->attrib.psta;
	switch (pfirstframe->attrib.priority) {
		case 1:
		case 2:
			ptxservq = &(psta->sta_xmitpriv.bk_q);
//			phwxmit = pxmitpriv->hwxmits + 3;
			break;

		case 4:
		case 5:
			ptxservq = &(psta->sta_xmitpriv.vi_q);
//			phwxmit = pxmitpriv->hwxmits + 1;
			break;

		case 6:
		case 7:
			ptxservq = &(psta->sta_xmitpriv.vo_q);
//			phwxmit = pxmitpriv->hwxmits;
			break;

		case 0:
		case 3:
		default:
			ptxservq = &(psta->sta_xmitpriv.be_q);
//			phwxmit = pxmitpriv->hwxmits + 2;
			break;
	}

	_enter_critical_bh(&pxmitpriv->lock, &irqL);

	xmitframe_phead = get_list_head(&ptxservq->sta_pending);
	xmitframe_plist = get_next(xmitframe_phead);
	while (rtw_end_of_queue_search(xmitframe_phead, xmitframe_plist) == _FALSE)
	{
		pxmitframe = LIST_CONTAINOR(xmitframe_plist, struct xmit_frame, list);
		xmitframe_plist = get_next(xmitframe_plist);

		len = xmitframe_need_length(pxmitframe) + TXDESC_SIZE; // no offset
		if (pbuf + len > aggMaxLength) break;

		rtw_list_delete(&pxmitframe->list);
		ptxservq->qcnt--;

#ifndef IDEA_CONDITION
		// suppose only data frames would be in queue
		if (pxmitframe->frame_tag != DATA_FRAMETAG) {
			RT_TRACE(_module_rtl8192c_xmit_c_, _drv_err_,
				 ("xmitframe_complete: frame tag(%d) is not DATA_FRAMETAG(%d)!\n",
				  pxmitframe->frame_tag, DATA_FRAMETAG));
			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}

		// TID 0~15
		if ((pxmitframe->attrib.priority < 0) ||
		    (pxmitframe->attrib.priority > 15)) {
			RT_TRACE(_module_rtl8192c_xmit_c_, _drv_err_,
				 ("xmitframe_complete: TID(%d) should be 0~15!\n",
				  pxmitframe->attrib.priority));
			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}
#endif

//		pxmitframe->pxmitbuf = pxmitbuf;
		pxmitframe->buf_addr = pxmitbuf->pbuf + pbuf;

		pxmitframe->agg_num = 0; // not first frame of aggregation
		pxmitframe->pkt_offset = 0; // not first frame of aggregation, no need to reserve offset

#ifdef IDEA_CONDITION
		rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
#else
		res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
		if (res == _FALSE) {
			rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
			continue;
		}
#endif

		// always return ndis_packet after rtw_xmitframe_coalesce
		rtw_os_xmit_complete(padapter, pxmitframe);

		// (len - TXDESC_SIZE) == pxmitframe->attrib.last_txcmdsz
		_update_txdesc(pxmitframe, pxmitframe->buf_addr, pxmitframe->attrib.last_txcmdsz);

		// don't need xmitframe any more
		rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);

		// handle pointer and stop condition
		pbuf_tail = pbuf + len;
		pbuf = _RND8(pbuf_tail);

		pfirstframe->agg_num++;
		if (MAX_TX_AGG_PACKET_NUMBER == pfirstframe->agg_num)
			break;

		if (pbuf < bulkPtr) {
			descCount++;
			if (descCount == pHalData->UsbTxAggDescNum)
				break;
		} else {
			descCount = 0;
			bulkPtr = ((pbuf / bulkSize) + 1) * bulkSize;
		}
	}
	if (_rtw_queue_empty(&ptxservq->sta_pending) == _TRUE)
		rtw_list_delete(&ptxservq->tx_pending);

	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	if ((pfirstframe->attrib.ether_type != 0x0806) &&
	    (pfirstframe->attrib.ether_type != 0x888e) &&
	    (pfirstframe->attrib.dhcp_pkt != 1))
	{
		rtw_issue_addbareq_cmd(padapter, pfirstframe);
	}

	//3 3. update first frame txdesc
	if ((pbuf_tail % bulkSize) == 0) {
		// remove pkt_offset
		pbuf_tail -= PACKET_OFFSET_SZ;
		pfirstframe->buf_addr += PACKET_OFFSET_SZ;
		pfirstframe->pkt_offset = 0;
	}
	_update_txdesc(pfirstframe, pfirstframe->buf_addr, pfirstframe->attrib.last_txcmdsz);

	//3 4. write xmit buffer to USB FIFO
	ff_hwaddr = rtw_get_ff_hwaddr(pfirstframe);

	// xmit address == ((xmit_frame*)pxmitbuf->priv_data)->buf_addr
	rtw_write_port(padapter, ff_hwaddr, pbuf_tail, (u8*)pxmitbuf);


	//3 5. update statisitc
	pbuf_tail -= (pfirstframe->agg_num * TXDESC_SIZE);
	if (pfirstframe->pkt_offset == 1) pbuf_tail -= PACKET_OFFSET_SZ;
	
	rtw_count_tx_stats(padapter, pfirstframe, pbuf_tail);

	rtw_free_xmitframe_ex(pxmitpriv, pfirstframe);

	return _TRUE;
}
#endif
#else

s32 rtl8192du_xmitframe_complete(_adapter *padapter, struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{		

	struct hw_xmit *phwxmits;
	sint hwentry;
	struct xmit_frame *pxmitframe=NULL;	
	int res=_SUCCESS, xcnt = 0;

	phwxmits = pxmitpriv->hwxmits;
	hwentry = pxmitpriv->hwxmit_entry;

	RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("xmitframe_complete()\n"));

	if(pxmitbuf==NULL)
	{
		pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);		
		if(!pxmitbuf)
		{
			return _FALSE;
		}			
	}

	do
	{		
		pxmitframe =  rtw_dequeue_xframe(pxmitpriv, phwxmits, hwentry);
		
		if(pxmitframe)
		{
			pxmitframe->pxmitbuf = pxmitbuf;				

			pxmitframe->buf_addr = pxmitbuf->pbuf;

			pxmitbuf->priv_data = pxmitframe;	

			if((pxmitframe->frame_tag&0x0f) == DATA_FRAMETAG)
			{	
				if(pxmitframe->attrib.priority<=15)//TID0~15
				{
					res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
				}	
							
				rtw_os_xmit_complete(padapter, pxmitframe);//always return ndis_packet after rtw_xmitframe_coalesce 			
			}	

				
			RT_TRACE(_module_rtl871x_xmit_c_,_drv_info_,("xmitframe_complete(): rtw_dump_xframe\n"));

			
			if(res == _SUCCESS)
			{
				rtw_dump_xframe(padapter, pxmitframe);		 
			}
			else
			{
				rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
				rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);	
			}
	 			 		
			xcnt++;
			
		}
		else
		{			
			rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
			return _FALSE;
		}

		break;
		
	}while(0/*xcnt < (NR_XMITFRAME >> 3)*/);

	return _TRUE;
	
}
#endif


static s32 xmitframe_direct(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	s32 res = _SUCCESS;


	res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
	if (res == _SUCCESS) {
		rtw_dump_xframe(padapter, pxmitframe);
	}

	return res;
}

/*
 * Return
 *	_TRUE	dump packet directly
 *	_FALSE	enqueue packet
 */
static s32 pre_xmitframe(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	_irqL irqL;
	s32 res;
	struct xmit_buf *pxmitbuf = NULL;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	
	_enter_critical_bh(&pxmitpriv->lock, &irqL);
	
#ifdef PLATFORM_FREEBSD
	//force tx to enqueue, and schedule tx task later.
	goto enqueue;
#endif	// PLATFORM_FREEBSD

	if (rtw_txframes_sta_ac_pending(padapter, pattrib) > 0
#ifdef CONFIG_DUALMAC_CONCURRENT
		|| (dc_check_xmit(padapter)== _FALSE)
#endif
		)
		goto enqueue;



	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == _TRUE)
		goto enqueue;

#ifdef CONFIG_CONCURRENT_MODE
	if (check_buddy_fwstate(padapter, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == _TRUE)
		goto enqueue;
#endif //CONFIG_CONCURRENT_MODE

	pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
	if (pxmitbuf == NULL)
		goto enqueue;

	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pxmitframe;

	if (xmitframe_direct(padapter, pxmitframe) != _SUCCESS) {
		rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
		rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);
	}

	return _TRUE;

enqueue:
	res = rtw_xmitframe_enqueue(padapter, pxmitframe);
	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	if (res != _SUCCESS) {
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("pre_xmitframe: enqueue xmitframe fail\n"));
		rtw_free_xmitframe_ex(pxmitpriv, pxmitframe);

		// Trick, make the statistics correct
		pxmitpriv->tx_pkts--;
		pxmitpriv->tx_drop++;
		return _TRUE;
	}

#ifdef PLATFORM_FREEBSD
	rtw_os_xmit_schedule(padapter);
#endif	// PLATFORM_FREEBSD

	return _FALSE;
}

void rtl8192du_mgnt_xmit(_adapter *padapter, struct xmit_frame *pmgntframe)
{
	rtw_dump_xframe(padapter, pmgntframe);
}

/*
 * Return
 *	_TRUE	dump packet directly ok
 *	_FALSE	temporary can't transmit packets to hardware
 */
s32 rtl8192du_hal_xmit(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	return pre_xmitframe(padapter, pxmitframe);
}

#ifdef  CONFIG_HOSTAPD_MLME

static void rtl8192du_hostap_mgnt_xmit_cb(struct urb *urb)
{	
#ifdef PLATFORM_LINUX
	struct sk_buff *skb = (struct sk_buff *)urb->context;

	//DBG_8192C("%s\n", __FUNCTION__);

	dev_kfree_skb_any(skb);
#endif	
}

s32 rtl8192du_hostap_mgnt_xmit_entry(_adapter *padapter, _pkt *pkt)
{
#ifdef PLATFORM_LINUX
	u16 fc;
	int rc, len, pipe;	
	unsigned int bmcst, tid, qsel;
	struct sk_buff *skb, *pxmit_skb;
	struct urb *urb;
	unsigned char *pxmitbuf;
	struct tx_desc *ptxdesc;
	struct rtw_ieee80211_hdr *tx_hdr;
	struct hostapd_priv *phostapdpriv = padapter->phostapdpriv;	
	struct net_device *pnetdev = padapter->pnetdev;
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(padapter);
	struct dvobj_priv *pdvobj = &padapter->dvobjpriv;	

	
	//DBG_8192C("%s\n", __FUNCTION__);

	skb = pkt;
	
	len = skb->len;
	tx_hdr = (struct rtw_ieee80211_hdr *)(skb->data);
	fc = le16_to_cpu(tx_hdr->frame_ctl);
	bmcst = IS_MCAST(tx_hdr->addr1);

	if ((fc & RTW_IEEE80211_FCTL_FTYPE) != RTW_IEEE80211_FTYPE_MGMT)
		goto _exit;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)) // http://www.mail-archive.com/netdev@vger.kernel.org/msg17214.html
	pxmit_skb = dev_alloc_skb(len + TXDESC_SIZE);			
#else			
	pxmit_skb = netdev_alloc_skb(pnetdev, len + TXDESC_SIZE);
#endif		

	if(!pxmit_skb)
		goto _exit;

	pxmitbuf = pxmit_skb->data;
#ifdef PLATFORM_FREEBSD
	urb = rtw_usb_alloc_urb(0, GFP_ATOMIC);
#else //PLATFORM_FREEBSD
	urb = usb_alloc_urb(0, GFP_ATOMIC);
#endif //PLATFORM_FREEBSD
	if (!urb) {
		goto _exit;
	}

	// ----- fill tx desc -----	
	ptxdesc = (struct tx_desc *)pxmitbuf;	
	_rtw_memset(ptxdesc, 0, sizeof(*ptxdesc));
		
	//offset 0	
	ptxdesc->txdw0 |= cpu_to_le32(len&0x0000ffff); 
	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE+OFFSET_SZ)<<OFFSET_SHT)&0x00ff0000);//default = 32 bytes for TX Desc
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);

	if(bmcst)	
	{
		ptxdesc->txdw0 |= cpu_to_le32(BIT(24));
	}	

	//offset 4	
	ptxdesc->txdw1 |= cpu_to_le32(0x00);//MAC_ID

	ptxdesc->txdw1 |= cpu_to_le32((0x12<<QSEL_SHT)&0x00001f00);

	ptxdesc->txdw1 |= cpu_to_le32((0x06<< 16) & 0x000f0000);//b mode

	//offset 8			

	//offset 12		
	ptxdesc->txdw3 |= cpu_to_le32((le16_to_cpu(tx_hdr->seq_ctl)<<16)&0xffff0000);

	//offset 16		
	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));//driver uses rate
		
	//offset 20


	//HW append seq
	ptxdesc->txdw4 |= cpu_to_le32(BIT(7)); // Hw set sequence number
	ptxdesc->txdw3 |= cpu_to_le32((8 <<28)); //set bit3 to 1. Suugested by TimChen. 2009.12.29.
	

	rtl8192cu_cal_txdesc_chksum(ptxdesc);
	// ----- end of fill tx desc -----

	//
	skb_put(pxmit_skb, len + TXDESC_SIZE);
	pxmitbuf = pxmitbuf + TXDESC_SIZE;
	_rtw_memcpy(pxmitbuf, skb->data, len);

	//DBG_8192C("mgnt_xmit, len=%x\n", pxmit_skb->len);


	// ----- prepare urb for submit -----
	
	//translate DMA FIFO addr to pipehandle
	//pipe = ffaddr2pipehdl(pdvobj, MGT_QUEUE_INX);
	pipe = usb_sndbulkpipe(pdvobj->pusbdev, pHalData->Queue2EPNum[(u8)MGT_QUEUE_INX]&0x0f);
#ifdef PLATFORM_FREEBSD
	rtw_usb_fill_bulk_urb(urb, pdvobj->pusbdev, pipe,
		pxmit_skb->data, pxmit_skb->len, rtl8192cu_hostap_mgnt_xmit_cb, pxmit_skb);
#else //PLATFORM_FREEBSD
	usb_fill_bulk_urb(urb, pdvobj->pusbdev, pipe,
		pxmit_skb->data, pxmit_skb->len, rtl8192cu_hostap_mgnt_xmit_cb, pxmit_skb);
#endif //PLATFORM_FREEBSD
	
	urb->transfer_flags |= URB_ZERO_PACKET;
	usb_anchor_urb(urb, &phostapdpriv->anchored);
#ifdef PLATFORM_FREEBSD
	rc = rtw_usb_submit_urb(urb, GFP_ATOMIC);
#else //PLATFORM_FREEBSD
	rc = usb_submit_urb(urb, GFP_ATOMIC);
#endif //PLATFORM_FREEBSD
	if (rc < 0) {
		usb_unanchor_urb(urb);
		kfree_skb(skb);
	}
#ifdef PLATFORM_FREEBSD
	rtw_usb_free_urb(urb);
#else //PLATFORM_FREEBSD
	usb_free_urb(urb);
#endif //PLATFORM_FREEBSD

	
_exit:	
	
	dev_kfree_skb_any(skb);

#endif

	return 0;

}
#endif


