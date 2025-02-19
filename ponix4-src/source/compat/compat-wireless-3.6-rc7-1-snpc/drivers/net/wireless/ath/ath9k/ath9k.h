/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef ATH9K_H
#define ATH9K_H

#include <linux/etherdevice.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/leds.h>
#include <linux/completion.h>

#include "debug.h"
#include "common.h"
#include "mci.h"
#include "dfs.h"

/*
 * Header for the ath9k.ko driver core *only* -- hw code nor any other driver
 * should rely on this file or its contents.
 */

struct ath_node;

/* Macro to expand scalars to 64-bit objects */

#define	ito64(x) (sizeof(x) == 1) ?			\
	(((unsigned long long int)(x)) & (0xff)) :	\
	(sizeof(x) == 2) ?				\
	(((unsigned long long int)(x)) & 0xffff) :	\
	((sizeof(x) == 4) ?				\
	 (((unsigned long long int)(x)) & 0xffffffff) : \
	 (unsigned long long int)(x))

/* increment with wrap-around */
#define INCR(_l, _sz)   do {			\
		(_l)++;				\
		(_l) &= ((_sz) - 1);		\
	} while (0)

/* decrement with wrap-around */
#define DECR(_l,  _sz)  do {			\
		(_l)--;				\
		(_l) &= ((_sz) - 1);		\
	} while (0)

#define TSF_TO_TU(_h,_l) \
	((((u32)(_h)) << 22) | (((u32)(_l)) >> 10))

#define	ATH_TXQ_SETUP(sc, i)        ((sc)->tx.txqsetup & (1<<i))

struct ath_config {
	u16 txpowlimit;
	u8 cabqReadytime;
};

/*************************/
/* Descriptor Management */
/*************************/

#define ATH_TXBUF_RESET(_bf) do {				\
		(_bf)->bf_stale = false;			\
		(_bf)->bf_lastbf = NULL;			\
		(_bf)->bf_next = NULL;				\
		memset(&((_bf)->bf_state), 0,			\
		       sizeof(struct ath_buf_state));		\
	} while (0)

#define ATH_RXBUF_RESET(_bf) do {		\
		(_bf)->bf_stale = false;	\
	} while (0)

/**
 * enum buffer_type - Buffer type flags
 *
 * @BUF_AMPDU: This buffer is an ampdu, as part of an aggregate (during TX)
 * @BUF_AGGR: Indicates whether the buffer can be aggregated
 *	(used in aggregation scheduling)
 */
enum buffer_type {
	BUF_AMPDU		= BIT(0),
	BUF_AGGR		= BIT(1),
};

#define bf_isampdu(bf)		(bf->bf_state.bf_type & BUF_AMPDU)
#define bf_isaggr(bf)		(bf->bf_state.bf_type & BUF_AGGR)

#define ATH_TXSTATUS_RING_SIZE 512

#define	DS2PHYS(_dd, _ds)						\
	((_dd)->dd_desc_paddr + ((caddr_t)(_ds) - (caddr_t)(_dd)->dd_desc))
#define ATH_DESC_4KB_BOUND_CHECK(_daddr) ((((_daddr) & 0xFFF) > 0xF7F) ? 1 : 0)
#define ATH_DESC_4KB_BOUND_NUM_SKIPPED(_len) ((_len) / 4096)

struct ath_descdma {
	void *dd_desc;
	dma_addr_t dd_desc_paddr;
	u32 dd_desc_len;
	struct ath_buf *dd_bufptr;
};

int ath_descdma_setup(struct ath_softc *sc, struct ath_descdma *dd,
		      struct list_head *head, const char *name,
		      int nbuf, int ndesc, bool is_tx);
void ath_descdma_cleanup(struct ath_softc *sc, struct ath_descdma *dd,
			 struct list_head *head);

/***********/
/* RX / TX */
/***********/

#define ATH_RXBUF               512
#define ATH_TXBUF               512
#define ATH_TXBUF_RESERVE       5
#define ATH_MAX_QDEPTH          (ATH_TXBUF / 4 - ATH_TXBUF_RESERVE)
#define ATH_TXMAXTRY            13

#define TID_TO_WME_AC(_tid)				\
	((((_tid) == 0) || ((_tid) == 3)) ? WME_AC_BE :	\
	 (((_tid) == 1) || ((_tid) == 2)) ? WME_AC_BK :	\
	 (((_tid) == 4) || ((_tid) == 5)) ? WME_AC_VI :	\
	 WME_AC_VO)

#define ATH_AGGR_DELIM_SZ          4
#define ATH_AGGR_MINPLEN           256 /* in bytes, minimum packet length */
/* number of delimiters for encryption padding */
#define ATH_AGGR_ENCRYPTDELIM      10
/* minimum h/w qdepth to be sustained to maximize aggregation */
#define ATH_AGGR_MIN_QDEPTH        2
#define ATH_AMPDU_SUBFRAME_DEFAULT 32

#define IEEE80211_SEQ_SEQ_SHIFT    4
#define IEEE80211_SEQ_MAX          4096
#define IEEE80211_WEP_IVLEN        3
#define IEEE80211_WEP_KIDLEN       1
#define IEEE80211_WEP_CRCLEN       4
#define IEEE80211_MAX_MPDU_LEN     (3840 + FCS_LEN +		\
				    (IEEE80211_WEP_IVLEN +	\
				     IEEE80211_WEP_KIDLEN +	\
				     IEEE80211_WEP_CRCLEN))

/* return whether a bit at index _n in bitmap _bm is set
 * _sz is the size of the bitmap  */
#define ATH_BA_ISSET(_bm, _n)  (((_n) < (WME_BA_BMP_SIZE)) &&		\
				((_bm)[(_n) >> 5] & (1 << ((_n) & 31))))

/* return block-ack bitmap index given sequence and starting sequence */
#define ATH_BA_INDEX(_st, _seq) (((_seq) - (_st)) & (IEEE80211_SEQ_MAX - 1))

/* return the seqno for _start + _offset */
#define ATH_BA_INDEX2SEQ(_seq, _offset) (((_seq) + (_offset)) & (IEEE80211_SEQ_MAX - 1))

/* returns delimiter padding required given the packet length */
#define ATH_AGGR_GET_NDELIM(_len)					\
       (((_len) >= ATH_AGGR_MINPLEN) ? 0 :                             \
        DIV_ROUND_UP(ATH_AGGR_MINPLEN - (_len), ATH_AGGR_DELIM_SZ))

#define BAW_WITHIN(_start, _bawsz, _seqno) \
	((((_seqno) - (_start)) & 4095) < (_bawsz))

#define ATH_AN_2_TID(_an, _tidno)  (&(_an)->tid[(_tidno)])

#define IS_CCK_RATE(rate) ((rate >= 0x18) && (rate <= 0x1e))

#define ATH_TX_COMPLETE_POLL_INT	1000

enum ATH_AGGR_STATUS {
	ATH_AGGR_DONE,
	ATH_AGGR_BAW_CLOSED,
	ATH_AGGR_LIMITED,
};

#define ATH_TXFIFO_DEPTH 8
struct ath_txq {
	int mac80211_qnum; /* mac80211 queue number, -1 means not mac80211 Q */
	u32 axq_qnum; /* ath9k hardware queue number */
	void *axq_link;
	struct list_head axq_q;
	spinlock_t axq_lock;
	u32 axq_depth;
	u32 axq_ampdu_depth;
	bool stopped;
	bool axq_tx_inprogress;
	struct list_head axq_acq;
	struct list_head txq_fifo[ATH_TXFIFO_DEPTH];
	u8 txq_headidx;
	u8 txq_tailidx;
	int pending_frames;
	struct sk_buff_head complete_q;
};

struct ath_atx_ac {
	struct ath_txq *txq;
	int sched;
	struct list_head list;
	struct list_head tid_q;
	bool clear_ps_filter;
};

struct ath_frame_info {
	struct ath_buf *bf;
	int framelen;
	enum ath9k_key_type keytype;
	u8 keyix;
	u8 retries;
	u8 rtscts_rate;
};

struct ath_buf_state {
	u8 bf_type;
	u8 bfs_paprd;
	u8 ndelim;
	u16 seqno;
	unsigned long bfs_paprd_timestamp;
};

struct ath_buf {
	struct list_head list;
	struct ath_buf *bf_lastbf;	/* last buf of this unit (a frame or
					   an aggregate) */
	struct ath_buf *bf_next;	/* next subframe in the aggregate */
	struct sk_buff *bf_mpdu;	/* enclosing frame structure */
	void *bf_desc;			/* virtual addr of desc */
	dma_addr_t bf_daddr;		/* physical addr of desc */
	dma_addr_t bf_buf_addr;	/* physical addr of data buffer, for DMA */
	bool bf_stale;
	struct ath_buf_state bf_state;
};

struct ath_atx_tid {
	struct list_head list;
	struct sk_buff_head buf_q;
	struct ath_node *an;
	struct ath_atx_ac *ac;
	unsigned long tx_buf[BITS_TO_LONGS(ATH_TID_MAX_BUFS)];
	int bar_index;
	u16 seq_start;
	u16 seq_next;
	u16 baw_size;
	int tidno;
	int baw_head;   /* first un-acked tx buffer */
	int baw_tail;   /* next unused tx buffer slot */
	int sched;
	int paused;
	u8 state;
};

struct ath_node {
#ifdef CONFIG_ATH9K_DEBUGFS
	struct list_head list; /* for sc->nodes */
#endif
	struct ieee80211_sta *sta; /* station struct we're part of */
	struct ieee80211_vif *vif; /* interface with which we're associated */
	struct ath_atx_tid tid[WME_NUM_TID];
	struct ath_atx_ac ac[WME_NUM_AC];
	int ps_key;

	u16 maxampdu;
	u8 mpdudensity;

	bool sleeping;
};

#define AGGR_CLEANUP         BIT(1)
#define AGGR_ADDBA_COMPLETE  BIT(2)
#define AGGR_ADDBA_PROGRESS  BIT(3)

struct ath_tx_control {
	struct ath_txq *txq;
	struct ath_node *an;
	u8 paprd;
};

#define ATH_TX_ERROR        0x01

/**
 * @txq_map:  Index is mac80211 queue number.  This is
 *  not necessarily the same as the hardware queue number
 *  (axq_qnum).
 */
struct ath_tx {
	u16 seq_no;
	u32 txqsetup;
	spinlock_t txbuflock;
	struct list_head txbuf;
	struct ath_txq txq[ATH9K_NUM_TX_QUEUES];
	struct ath_descdma txdma;
	struct ath_txq *txq_map[WME_NUM_AC];
	u32 txq_max_pending[WME_NUM_AC];
	u16 max_aggr_framelen[WME_NUM_AC][4][32];
};

struct ath_rx_edma {
	struct sk_buff_head rx_fifo;
	u32 rx_fifo_hwsize;
};

struct ath_rx {
	u8 defant;
	u8 rxotherant;
	u32 *rxlink;
	u32 num_pkts;
	unsigned int rxfilter;
	spinlock_t rxbuflock;
	struct list_head rxbuf;
	struct ath_descdma rxdma;
	struct ath_buf *rx_bufptr;
	struct ath_rx_edma rx_edma[ATH9K_RX_QUEUE_MAX];

	struct sk_buff *frag;
};

int ath_startrecv(struct ath_softc *sc);
bool ath_stoprecv(struct ath_softc *sc);
void ath_flushrecv(struct ath_softc *sc);
u32 ath_calcrxfilter(struct ath_softc *sc);
int ath_rx_init(struct ath_softc *sc, int nbufs);
void ath_rx_cleanup(struct ath_softc *sc);
int ath_rx_tasklet(struct ath_softc *sc, int flush, bool hp);
struct ath_txq *ath_txq_setup(struct ath_softc *sc, int qtype, int subtype);
void ath_txq_lock(struct ath_softc *sc, struct ath_txq *txq);
void ath_txq_unlock(struct ath_softc *sc, struct ath_txq *txq);
void ath_txq_unlock_complete(struct ath_softc *sc, struct ath_txq *txq);
void ath_tx_cleanupq(struct ath_softc *sc, struct ath_txq *txq);
bool ath_drain_all_txq(struct ath_softc *sc, bool retry_tx);
void ath_draintxq(struct ath_softc *sc,
		     struct ath_txq *txq, bool retry_tx);
void ath_tx_node_init(struct ath_softc *sc, struct ath_node *an);
void ath_tx_node_cleanup(struct ath_softc *sc, struct ath_node *an);
void ath_txq_schedule(struct ath_softc *sc, struct ath_txq *txq);
int ath_tx_init(struct ath_softc *sc, int nbufs);
void ath_tx_cleanup(struct ath_softc *sc);
int ath_txq_update(struct ath_softc *sc, int qnum,
		   struct ath9k_tx_queue_info *q);
void ath_update_max_aggr_framelen(struct ath_softc *sc, int queue, int txop);
int ath_tx_start(struct ieee80211_hw *hw, struct sk_buff *skb,
		 struct ath_tx_control *txctl);
void ath_tx_tasklet(struct ath_softc *sc);
void ath_tx_edma_tasklet(struct ath_softc *sc);
int ath_tx_aggr_start(struct ath_softc *sc, struct ieee80211_sta *sta,
		      u16 tid, u16 *ssn);
void ath_tx_aggr_stop(struct ath_softc *sc, struct ieee80211_sta *sta, u16 tid);
void ath_tx_aggr_resume(struct ath_softc *sc, struct ieee80211_sta *sta, u16 tid);

void ath_tx_aggr_wakeup(struct ath_softc *sc, struct ath_node *an);
void ath_tx_aggr_sleep(struct ieee80211_sta *sta, struct ath_softc *sc,
		       struct ath_node *an);

/********/
/* VIFs */
/********/

struct ath_vif {
	int av_bslot;
	bool primary_sta_vif;
	__le64 tsf_adjust; /* TSF adjustment for staggered beacons */
	struct ath_buf *av_bcbuf;
};

/*******************/
/* Beacon Handling */
/*******************/

/*
 * Regardless of the number of beacons we stagger, (i.e. regardless of the
 * number of BSSIDs) if a given beacon does not go out even after waiting this
 * number of beacon intervals, the game's up.
 */
#define BSTUCK_THRESH           	9
#define	ATH_BCBUF               	8
#define ATH_DEFAULT_BINTVAL     	100 /* TU */
#define ATH_DEFAULT_BMISS_LIMIT 	10
#define IEEE80211_MS_TO_TU(x)           (((x) * 1000) / 1024)

struct ath_beacon_config {
	int beacon_interval;
	u16 listen_interval;
	u16 dtim_period;
	u16 bmiss_timeout;
	u8 dtim_count;
	bool enable_beacon;
};

struct ath_beacon {
	enum {
		OK,		/* no change needed */
		UPDATE,		/* update pending */
		COMMIT		/* beacon sent, commit change */
	} updateslot;		/* slot time update fsm */

	u32 beaconq;
	u32 bmisscnt;
	u32 bc_tstamp;
	struct ieee80211_vif *bslot[ATH_BCBUF];
	int slottime;
	int slotupdate;
	struct ath9k_tx_queue_info beacon_qi;
	struct ath_descdma bdma;
	struct ath_txq *cabq;
	struct list_head bbuf;

	bool tx_processed;
	bool tx_last;
};

void ath9k_beacon_tasklet(unsigned long data);
bool ath9k_allow_beacon_config(struct ath_softc *sc, struct ieee80211_vif *vif);
void ath9k_beacon_config(struct ath_softc *sc, struct ieee80211_vif *vif,
			 u32 changed);
void ath9k_beacon_assign_slot(struct ath_softc *sc, struct ieee80211_vif *vif);
void ath9k_beacon_remove_slot(struct ath_softc *sc, struct ieee80211_vif *vif);
void ath9k_set_tsfadjust(struct ath_softc *sc, struct ieee80211_vif *vif);
void ath9k_set_beacon(struct ath_softc *sc);
void ath9k_set_beaconing_status(struct ath_softc *sc, bool status);

/*******************/
/* Link Monitoring */
/*******************/

#define ATH_STA_SHORT_CALINTERVAL 1000    /* 1 second */
#define ATH_AP_SHORT_CALINTERVAL  100     /* 100 ms */
#define ATH_ANI_POLLINTERVAL_OLD  100     /* 100 ms */
#define ATH_ANI_POLLINTERVAL_NEW  1000    /* 1000 ms */
#define ATH_LONG_CALINTERVAL_INT  1000    /* 1000 ms */
#define ATH_LONG_CALINTERVAL      30000   /* 30 seconds */
#define ATH_RESTART_CALINTERVAL   1200000 /* 20 minutes */

#define ATH_PAPRD_TIMEOUT	100 /* msecs */
#define ATH_PLL_WORK_INTERVAL   100

void ath_tx_complete_poll_work(struct work_struct *work);
void ath_reset_work(struct work_struct *work);
void ath_hw_check(struct work_struct *work);
void ath_hw_pll_work(struct work_struct *work);
void ath_rx_poll(unsigned long data);
void ath_start_rx_poll(struct ath_softc *sc, u8 nbeacon);
void ath_paprd_calibrate(struct work_struct *work);
void ath_ani_calibrate(unsigned long data);
void ath_start_ani(struct ath_softc *sc);
void ath_stop_ani(struct ath_softc *sc);
void ath_check_ani(struct ath_softc *sc);
int ath_update_survey_stats(struct ath_softc *sc);
void ath_update_survey_nf(struct ath_softc *sc, int channel);
void ath9k_queue_reset(struct ath_softc *sc, enum ath_reset_type type);

/**********/
/* BTCOEX */
/**********/

enum bt_op_flags {
	BT_OP_PRIORITY_DETECTED,
	BT_OP_SCAN,
};

struct ath_btcoex {
	bool hw_timer_enabled;
	spinlock_t btcoex_lock;
	struct timer_list period_timer; /* Timer for BT period */
	u32 bt_priority_cnt;
	unsigned long bt_priority_time;
	unsigned long op_flags;
	int bt_stomp_type; /* Types of BT stomping */
	u32 btcoex_no_stomp; /* in usec */
	u32 btcoex_period; /* in msec */
	u32 btscan_no_stomp; /* in usec */
	u32 duty_cycle;
	u32 bt_wait_time;
	struct ath_gen_timer *no_stomp_timer; /* Timer for no BT stomping */
	struct ath_mci_profile mci;
};

#ifdef CONFIG_ATH9K_BTCOEX_SUPPORT
int ath9k_init_btcoex(struct ath_softc *sc);
void ath9k_deinit_btcoex(struct ath_softc *sc);
void ath9k_start_btcoex(struct ath_softc *sc);
void ath9k_stop_btcoex(struct ath_softc *sc);
void ath9k_btcoex_timer_resume(struct ath_softc *sc);
void ath9k_btcoex_timer_pause(struct ath_softc *sc);
void ath9k_btcoex_handle_interrupt(struct ath_softc *sc, u32 status);
u16 ath9k_btcoex_aggr_limit(struct ath_softc *sc, u32 max_4ms_framelen);
void ath9k_btcoex_stop_gen_timer(struct ath_softc *sc);
#else
static inline int ath9k_init_btcoex(struct ath_softc *sc)
{
	return 0;
}
static inline void ath9k_deinit_btcoex(struct ath_softc *sc)
{
}
static inline void ath9k_start_btcoex(struct ath_softc *sc)
{
}
static inline void ath9k_stop_btcoex(struct ath_softc *sc)
{
}
static inline void ath9k_btcoex_handle_interrupt(struct ath_softc *sc,
						 u32 status)
{
}
static inline u16 ath9k_btcoex_aggr_limit(struct ath_softc *sc,
					  u32 max_4ms_framelen)
{
	return 0;
}
static inline void ath9k_btcoex_stop_gen_timer(struct ath_softc *sc)
{
}
#endif /* CONFIG_ATH9K_BTCOEX_SUPPORT */

struct ath9k_wow_pattern {
	u8 pattern_bytes[MAX_PATTERN_SIZE];
	u8 mask_bytes[MAX_PATTERN_SIZE];
	u32 pattern_len;
};

/********************/
/*   LED Control    */
/********************/

#define ATH_LED_PIN_DEF 		1
#define ATH_LED_PIN_9287		8
#define ATH_LED_PIN_9300		10
#define ATH_LED_PIN_9485		6
#define ATH_LED_PIN_9462		4

#ifdef CONFIG_MAC80211_LEDS
void ath_init_leds(struct ath_softc *sc);
void ath_deinit_leds(struct ath_softc *sc);
void ath_fill_led_pin(struct ath_softc *sc);
#else
static inline void ath_init_leds(struct ath_softc *sc)
{
}

static inline void ath_deinit_leds(struct ath_softc *sc)
{
}
static inline void ath_fill_led_pin(struct ath_softc *sc)
{
}
#endif

/*******************************/
/* Antenna diversity/combining */
/*******************************/

#define ATH_ANT_RX_CURRENT_SHIFT 4
#define ATH_ANT_RX_MAIN_SHIFT 2
#define ATH_ANT_RX_MASK 0x3

#define ATH_ANT_DIV_COMB_SHORT_SCAN_INTR 50
#define ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT 0x100
#define ATH_ANT_DIV_COMB_MAX_PKTCOUNT 0x200
#define ATH_ANT_DIV_COMB_INIT_COUNT 95
#define ATH_ANT_DIV_COMB_MAX_COUNT 100
#define ATH_ANT_DIV_COMB_ALT_ANT_RATIO 30
#define ATH_ANT_DIV_COMB_ALT_ANT_RATIO2 20

#define ATH_ANT_DIV_COMB_LNA1_LNA2_SWITCH_DELTA -1
#define ATH_ANT_DIV_COMB_LNA1_DELTA_HI -4
#define ATH_ANT_DIV_COMB_LNA1_DELTA_MID -2
#define ATH_ANT_DIV_COMB_LNA1_DELTA_LOW 2

enum ath9k_ant_div_comb_lna_conf {
	ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2,
	ATH_ANT_DIV_COMB_LNA2,
	ATH_ANT_DIV_COMB_LNA1,
	ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2,
};

struct ath_ant_comb {
	u16 count;
	u16 total_pkt_count;
	bool scan;
	bool scan_not_start;
	int main_total_rssi;
	int alt_total_rssi;
	int alt_recv_cnt;
	int main_recv_cnt;
	int rssi_lna1;
	int rssi_lna2;
	int rssi_add;
	int rssi_sub;
	int rssi_first;
	int rssi_second;
	int rssi_third;
	bool alt_good;
	int quick_scan_cnt;
	int main_conf;
	enum ath9k_ant_div_comb_lna_conf first_quick_scan_conf;
	enum ath9k_ant_div_comb_lna_conf second_quick_scan_conf;
	bool first_ratio;
	bool second_ratio;
	unsigned long scan_start_time;
};

void ath_ant_comb_scan(struct ath_softc *sc, struct ath_rx_status *rs);
void ath_ant_comb_update(struct ath_softc *sc);

/********************/
/* Main driver core */
/********************/

/*
 * Default cache line size, in bytes.
 * Used when PCI device not fully initialized by bootrom/BIOS
*/
#define DEFAULT_CACHELINE       32
#define ATH_REGCLASSIDS_MAX     10
#define ATH_CABQ_READY_TIME     80      /* % of beacon interval */
#define ATH_MAX_SW_RETRIES      30
#define ATH_CHAN_MAX            255

#define ATH_TXPOWER_MAX         100     /* .5 dBm units */
#define ATH_RATE_DUMMY_MARKER   0

enum sc_op_flags {
	SC_OP_INVALID,
	SC_OP_BEACONS,
	SC_OP_RXFLUSH,
	SC_OP_ANI_RUN,
	SC_OP_PRIM_STA_VIF,
	SC_OP_HW_RESET,
};

/* Powersave flags */
#define PS_WAIT_FOR_BEACON        BIT(0)
#define PS_WAIT_FOR_CAB           BIT(1)
#define PS_WAIT_FOR_PSPOLL_DATA   BIT(2)
#define PS_WAIT_FOR_TX_ACK        BIT(3)
#define PS_BEACON_SYNC            BIT(4)

struct ath_rate_table;

struct ath9k_vif_iter_data {
	const u8 *hw_macaddr; /* phy's hardware address, set
			       * before starting iteration for
			       * valid bssid mask.
			       */
	u8 mask[ETH_ALEN]; /* bssid mask */
	int naps;      /* number of AP vifs */
	int nmeshes;   /* number of mesh vifs */
	int nstations; /* number of station vifs */
	int nwds;      /* number of WDS vifs */
	int nadhocs;   /* number of adhoc vifs */
};

struct ath_softc {
	struct ieee80211_hw *hw;
	struct device *dev;

	struct survey_info *cur_survey;
	struct survey_info survey[ATH9K_NUM_CHANNELS];

	struct tasklet_struct intr_tq;
	struct tasklet_struct bcon_tasklet;
	struct ath_hw *sc_ah;
	void __iomem *mem;
	int irq;
	spinlock_t sc_serial_rw;
	spinlock_t sc_pm_lock;
	spinlock_t sc_pcu_lock;
	struct mutex mutex;
	struct work_struct paprd_work;
	struct work_struct hw_check_work;
	struct work_struct hw_reset_work;
	struct completion paprd_complete;

	unsigned int hw_busy_count;
	unsigned long sc_flags;

	u32 intrstatus;
	u16 ps_flags; /* PS_* */
	u16 curtxpow;
	bool ps_enabled;
	bool ps_idle;
	short nbcnvifs;
	short nvifs;
	unsigned long ps_usecount;

	struct ath_config config;
	struct ath_rx rx;
	struct ath_tx tx;
	struct ath_beacon beacon;
	struct ieee80211_supported_band sbands[IEEE80211_NUM_BANDS];

#ifdef CONFIG_MAC80211_LEDS
	bool led_registered;
	char led_name[32];
	struct led_classdev led_cdev;
#endif

	struct ath9k_hw_cal_data caldata;
	int last_rssi;

#ifdef CONFIG_ATH9K_DEBUGFS
	struct ath9k_debug debug;
	spinlock_t nodes_lock;
	struct list_head nodes; /* basically, stations */
	unsigned int tx_complete_poll_work_seen;
#endif
	struct ath_beacon_config cur_beacon_conf;
	struct delayed_work tx_complete_work;
	struct delayed_work hw_pll_work;
	struct timer_list rx_poll_timer;

#ifdef CONFIG_ATH9K_BTCOEX_SUPPORT
	struct ath_btcoex btcoex;
	struct ath_mci_coex mci_coex;
	struct work_struct mci_work;
#endif

	struct ath_descdma txsdma;

	struct ath_ant_comb ant_comb;
	u8 ant_tx, ant_rx;
	struct dfs_pattern_detector *dfs_detector;
	u32 wow_enabled;

#ifdef CONFIG_PM_SLEEP
	atomic_t wow_got_bmiss_intr;
	atomic_t wow_sleep_proc_intr; /* in the middle of WoW sleep ? */
	u32 wow_intr_before_sleep;
#endif
};

void ath9k_tasklet(unsigned long data);
int ath_cabq_update(struct ath_softc *);

static inline void ath_read_cachesize(struct ath_common *common, int *csz)
{
	common->bus_ops->read_cachesize(common, csz);
}

extern struct ieee80211_ops ath9k_ops;
extern int ath9k_modparam_nohwcrypt;
extern int led_blink;
extern bool is_ath9k_unloaded;

u8 ath9k_parse_mpdudensity(u8 mpdudensity);
irqreturn_t ath_isr(int irq, void *dev);
int ath9k_init_device(u16 devid, struct ath_softc *sc,
		    const struct ath_bus_ops *bus_ops);
void ath9k_deinit_device(struct ath_softc *sc);
void ath9k_set_hw_capab(struct ath_softc *sc, struct ieee80211_hw *hw);
void ath9k_reload_chainmask_settings(struct ath_softc *sc);

bool ath9k_uses_beacons(int type);

#ifdef CONFIG_ATH9K_PCI
int ath_pci_init(void);
void ath_pci_exit(void);
#else
static inline int ath_pci_init(void) { return 0; };
static inline void ath_pci_exit(void) {};
#endif

#ifdef CONFIG_ATH9K_AHB
int ath_ahb_init(void);
void ath_ahb_exit(void);
#else
static inline int ath_ahb_init(void) { return 0; };
static inline void ath_ahb_exit(void) {};
#endif

void ath9k_ps_wakeup(struct ath_softc *sc);
void ath9k_ps_restore(struct ath_softc *sc);

u8 ath_txchainmask_reduction(struct ath_softc *sc, u8 chainmask, u32 rate);

void ath_start_rfkill_poll(struct ath_softc *sc);
extern void ath9k_rfkill_poll_state(struct ieee80211_hw *hw);
void ath9k_calculate_iter_data(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif,
			       struct ath9k_vif_iter_data *iter_data);

#endif /* ATH9K_H */
