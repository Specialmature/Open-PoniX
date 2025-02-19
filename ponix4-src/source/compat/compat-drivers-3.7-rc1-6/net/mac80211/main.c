/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <net/mac80211.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/skbuff.h>
#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/rtnetlink.h>
#include <linux/bitmap.h>
#include <linux/pm_qos.h>
#include <linux/inetdevice.h>
#include <net/net_namespace.h>
#include <net/cfg80211.h>

#include "ieee80211_i.h"
#include "driver-ops.h"
#include "rate.h"
#include "mesh.h"
#include "wep.h"
#include "led.h"
#include "cfg.h"
#include "debugfs.h"

static struct lock_class_key ieee80211_rx_skb_queue_class;

void ieee80211_configure_filter(struct ieee80211_local *local)
{
	u64 mc;
	unsigned int changed_flags;
	unsigned int new_flags = 0;

	if (atomic_read(&local->iff_promiscs))
		new_flags |= FIF_PROMISC_IN_BSS;

	if (atomic_read(&local->iff_allmultis))
		new_flags |= FIF_ALLMULTI;

	if (local->monitors || test_bit(SCAN_SW_SCANNING, &local->scanning) ||
	    test_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning))
		new_flags |= FIF_BCN_PRBRESP_PROMISC;

	if (local->fif_probe_req || local->probe_req_reg)
		new_flags |= FIF_PROBE_REQ;

	if (local->fif_fcsfail)
		new_flags |= FIF_FCSFAIL;

	if (local->fif_plcpfail)
		new_flags |= FIF_PLCPFAIL;

	if (local->fif_control)
		new_flags |= FIF_CONTROL;

	if (local->fif_other_bss)
		new_flags |= FIF_OTHER_BSS;

	if (local->fif_pspoll)
		new_flags |= FIF_PSPOLL;

	spin_lock_bh(&local->filter_lock);
	changed_flags = local->filter_flags ^ new_flags;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
	mc = drv_prepare_multicast(local, &local->mc_list);
#else
	mc = drv_prepare_multicast(local, local->mc_count, local->mc_list);
#endif
	spin_unlock_bh(&local->filter_lock);

	/* be a bit nasty */
	new_flags |= (1<<31);

	drv_configure_filter(local, changed_flags, &new_flags, mc);

	WARN_ON(new_flags & (1<<31));

	local->filter_flags = new_flags & ~(1<<31);
}

static void ieee80211_reconfig_filter(struct work_struct *work)
{
	struct ieee80211_local *local =
		container_of(work, struct ieee80211_local, reconfig_filter);

	ieee80211_configure_filter(local);
}

int ieee80211_hw_config(struct ieee80211_local *local, u32 changed)
{
	struct ieee80211_channel *chan;
	int ret = 0;
	int power;
	enum nl80211_channel_type channel_type;
	u32 offchannel_flag;

	might_sleep();

	offchannel_flag = local->hw.conf.flags & IEEE80211_CONF_OFFCHANNEL;
	if (local->scan_channel) {
		chan = local->scan_channel;
		/* If scanning on oper channel, use whatever channel-type
		 * is currently in use.
		 */
		if (chan == local->oper_channel)
			channel_type = local->_oper_channel_type;
		else
			channel_type = NL80211_CHAN_NO_HT;
	} else if (local->tmp_channel) {
		chan = local->tmp_channel;
		channel_type = local->tmp_channel_type;
	} else {
		chan = local->oper_channel;
		channel_type = local->_oper_channel_type;
	}

	if (chan != local->oper_channel ||
	    channel_type != local->_oper_channel_type)
		local->hw.conf.flags |= IEEE80211_CONF_OFFCHANNEL;
	else
		local->hw.conf.flags &= ~IEEE80211_CONF_OFFCHANNEL;

	offchannel_flag ^= local->hw.conf.flags & IEEE80211_CONF_OFFCHANNEL;

	if (offchannel_flag || chan != local->hw.conf.channel ||
	    channel_type != local->hw.conf.channel_type) {
		local->hw.conf.channel = chan;
		local->hw.conf.channel_type = channel_type;
		changed |= IEEE80211_CONF_CHANGE_CHANNEL;
	}

	if (!conf_is_ht(&local->hw.conf)) {
		/*
		 * mac80211.h documents that this is only valid
		 * when the channel is set to an HT type, and
		 * that otherwise STATIC is used.
		 */
		local->hw.conf.smps_mode = IEEE80211_SMPS_STATIC;
	} else if (local->hw.conf.smps_mode != local->smps_mode) {
		local->hw.conf.smps_mode = local->smps_mode;
		changed |= IEEE80211_CONF_CHANGE_SMPS;
	}

	if (test_bit(SCAN_SW_SCANNING, &local->scanning) ||
	    test_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning) ||
	    test_bit(SCAN_HW_SCANNING, &local->scanning) ||
	    !local->ap_power_level)
		power = chan->max_power;
	else
		power = min(chan->max_power, local->ap_power_level);

	if (local->user_power_level >= 0)
		power = min(power, local->user_power_level);

	if (local->hw.conf.power_level != power) {
		changed |= IEEE80211_CONF_CHANGE_POWER;
		local->hw.conf.power_level = power;
	}

	if (changed && local->open_count) {
		ret = drv_config(local, changed);
		/*
		 * Goal:
		 * HW reconfiguration should never fail, the driver has told
		 * us what it can support so it should live up to that promise.
		 *
		 * Current status:
		 * rfkill is not integrated with mac80211 and a
		 * configuration command can thus fail if hardware rfkill
		 * is enabled
		 *
		 * FIXME: integrate rfkill with mac80211 and then add this
		 * WARN_ON() back
		 *
		 */
		/* WARN_ON(ret); */
	}

	return ret;
}

void ieee80211_bss_info_change_notify(struct ieee80211_sub_if_data *sdata,
				      u32 changed)
{
	struct ieee80211_local *local = sdata->local;
	static const u8 zero[ETH_ALEN] = { 0 };

	if (!changed)
		return;

	if (sdata->vif.type == NL80211_IFTYPE_STATION) {
		sdata->vif.bss_conf.bssid = sdata->u.mgd.bssid;
	} else if (sdata->vif.type == NL80211_IFTYPE_ADHOC)
		sdata->vif.bss_conf.bssid = sdata->u.ibss.bssid;
	else if (sdata->vif.type == NL80211_IFTYPE_AP)
		sdata->vif.bss_conf.bssid = sdata->vif.addr;
	else if (sdata->vif.type == NL80211_IFTYPE_WDS)
		sdata->vif.bss_conf.bssid = NULL;
	else if (ieee80211_vif_is_mesh(&sdata->vif)) {
		sdata->vif.bss_conf.bssid = zero;
	} else if (sdata->vif.type == NL80211_IFTYPE_P2P_DEVICE) {
		sdata->vif.bss_conf.bssid = sdata->vif.addr;
		WARN_ONCE(changed & ~(BSS_CHANGED_IDLE),
			  "P2P Device BSS changed %#x", changed);
	} else {
		WARN_ON(1);
		return;
	}

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_WDS:
	case NL80211_IFTYPE_MESH_POINT:
		break;
	default:
		/* do not warn to simplify caller in scan.c */
		changed &= ~BSS_CHANGED_BEACON_ENABLED;
		if (WARN_ON(changed & BSS_CHANGED_BEACON))
			return;
		break;
	}

	if (changed & BSS_CHANGED_BEACON_ENABLED) {
		if (local->quiescing || !ieee80211_sdata_running(sdata) ||
		    test_bit(SDATA_STATE_OFFCHANNEL, &sdata->state)) {
			sdata->vif.bss_conf.enable_beacon = false;
		} else {
			/*
			 * Beacon should be enabled, but AP mode must
			 * check whether there is a beacon configured.
			 */
			switch (sdata->vif.type) {
			case NL80211_IFTYPE_AP:
				sdata->vif.bss_conf.enable_beacon =
					!!sdata->u.ap.beacon;
				break;
			case NL80211_IFTYPE_ADHOC:
				sdata->vif.bss_conf.enable_beacon =
					!!sdata->u.ibss.presp;
				break;
#ifdef CONFIG_MAC80211_MESH
			case NL80211_IFTYPE_MESH_POINT:
				sdata->vif.bss_conf.enable_beacon =
					!!sdata->u.mesh.mesh_id_len;
				break;
#endif
			default:
				/* not reached */
				WARN_ON(1);
				break;
			}
		}
	}

	drv_bss_info_changed(local, sdata, &sdata->vif.bss_conf, changed);
}

u32 ieee80211_reset_erp_info(struct ieee80211_sub_if_data *sdata)
{
	sdata->vif.bss_conf.use_cts_prot = false;
	sdata->vif.bss_conf.use_short_preamble = false;
	sdata->vif.bss_conf.use_short_slot = false;
	return BSS_CHANGED_ERP_CTS_PROT |
	       BSS_CHANGED_ERP_PREAMBLE |
	       BSS_CHANGED_ERP_SLOT;
}

static void ieee80211_tasklet_handler(unsigned long data)
{
	struct ieee80211_local *local = (struct ieee80211_local *) data;
	struct sta_info *sta, *tmp;
	struct skb_eosp_msg_data *eosp_data;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&local->skb_queue)) ||
	       (skb = skb_dequeue(&local->skb_queue_unreliable))) {
		switch (skb->pkt_type) {
		case IEEE80211_RX_MSG:
			/* Clear skb->pkt_type in order to not confuse kernel
			 * netstack. */
			skb->pkt_type = 0;
			ieee80211_rx(&local->hw, skb);
			break;
		case IEEE80211_TX_STATUS_MSG:
			skb->pkt_type = 0;
			ieee80211_tx_status(&local->hw, skb);
			break;
		case IEEE80211_EOSP_MSG:
			eosp_data = (void *)skb->cb;
			for_each_sta_info(local, eosp_data->sta, sta, tmp) {
				/* skip wrong virtual interface */
				if (memcmp(eosp_data->iface,
					   sta->sdata->vif.addr, ETH_ALEN))
					continue;
				clear_sta_flag(sta, WLAN_STA_SP);
				break;
			}
			dev_kfree_skb(skb);
			break;
		default:
			WARN(1, "mac80211: Packet is of unknown type %d\n",
			     skb->pkt_type);
			dev_kfree_skb(skb);
			break;
		}
	}
}

static void ieee80211_restart_work(struct work_struct *work)
{
	struct ieee80211_local *local =
		container_of(work, struct ieee80211_local, restart_work);

	/* wait for scan work complete */
	flush_workqueue(local->workqueue);

	mutex_lock(&local->mtx);
	WARN(test_bit(SCAN_HW_SCANNING, &local->scanning) ||
	     rcu_dereference_protected(local->sched_scan_sdata,
				       lockdep_is_held(&local->mtx)),
		"%s called with hardware scan in progress\n", __func__);
	mutex_unlock(&local->mtx);

	rtnl_lock();
	ieee80211_scan_cancel(local);
	ieee80211_reconfig(local);
	rtnl_unlock();
}

void ieee80211_restart_hw(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	trace_api_restart_hw(local);

	wiphy_info(hw->wiphy,
		   "Hardware restart was requested\n");

	/* use this reason, ieee80211_reconfig will unblock it */
	ieee80211_stop_queues_by_reason(hw,
		IEEE80211_QUEUE_STOP_REASON_SUSPEND);

	/*
	 * Stop all Rx during the reconfig. We don't want state changes
	 * or driver callbacks while this is in progress.
	 */
	local->in_reconfig = true;
	barrier();

	schedule_work(&local->restart_work);
}
EXPORT_SYMBOL(ieee80211_restart_hw);

static void ieee80211_recalc_smps_work(struct work_struct *work)
{
	struct ieee80211_local *local =
		container_of(work, struct ieee80211_local, recalc_smps);

	ieee80211_recalc_smps(local);
}

#ifdef CONFIG_INET
static int ieee80211_ifa_changed(struct notifier_block *nb,
				 unsigned long data, void *arg)
{
	struct in_ifaddr *ifa = arg;
	struct ieee80211_local *local =
		container_of(nb, struct ieee80211_local,
			     ifa_notifier);
	struct net_device *ndev = ifa->ifa_dev->dev;
	struct wireless_dev *wdev = ndev->ieee80211_ptr;
	struct in_device *idev;
	struct ieee80211_sub_if_data *sdata;
	struct ieee80211_bss_conf *bss_conf;
	struct ieee80211_if_managed *ifmgd;
	int c = 0;

	/* Make sure it's our interface that got changed */
	if (!wdev)
		return NOTIFY_DONE;

	if (wdev->wiphy != local->hw.wiphy)
		return NOTIFY_DONE;

	sdata = IEEE80211_DEV_TO_SUB_IF(ndev);
	bss_conf = &sdata->vif.bss_conf;

	/* ARP filtering is only supported in managed mode */
	if (sdata->vif.type != NL80211_IFTYPE_STATION)
		return NOTIFY_DONE;

	idev = __in_dev_get_rtnl(sdata->dev);
	if (!idev)
		return NOTIFY_DONE;

	ifmgd = &sdata->u.mgd;
	mutex_lock(&ifmgd->mtx);

	/* Copy the addresses to the bss_conf list */
	ifa = idev->ifa_list;
	while (c < IEEE80211_BSS_ARP_ADDR_LIST_LEN && ifa) {
		bss_conf->arp_addr_list[c] = ifa->ifa_address;
		ifa = ifa->ifa_next;
		c++;
	}

	/* If not all addresses fit the list, disable filtering */
	if (ifa) {
		sdata->arp_filter_state = false;
		c = 0;
	} else {
		sdata->arp_filter_state = true;
	}
	bss_conf->arp_addr_cnt = c;

	/* Configure driver only if associated (which also implies it is up) */
	if (ifmgd->associated) {
		bss_conf->arp_filter_enabled = sdata->arp_filter_state;
		ieee80211_bss_info_change_notify(sdata,
						 BSS_CHANGED_ARP_FILTER);
	}

	mutex_unlock(&ifmgd->mtx);

	return NOTIFY_DONE;
}
#endif

static int ieee80211_napi_poll(struct napi_struct *napi, int budget)
{
	struct ieee80211_local *local =
		container_of(napi, struct ieee80211_local, napi);

	return local->ops->napi_poll(&local->hw, budget);
}

void ieee80211_napi_schedule(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	napi_schedule(&local->napi);
}
EXPORT_SYMBOL(ieee80211_napi_schedule);

void ieee80211_napi_complete(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	napi_complete(&local->napi);
}
EXPORT_SYMBOL(ieee80211_napi_complete);

/* There isn't a lot of sense in it, but you can transmit anything you like */
static const struct ieee80211_txrx_stypes
ieee80211_default_mgmt_stypes[NUM_NL80211_IFTYPES] = {
	[NL80211_IFTYPE_ADHOC] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4),
	},
	[NL80211_IFTYPE_STATION] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	},
	[NL80211_IFTYPE_AP] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	},
	[NL80211_IFTYPE_AP_VLAN] = {
		/* copy AP */
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	},
	[NL80211_IFTYPE_P2P_CLIENT] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	},
	[NL80211_IFTYPE_P2P_GO] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
			BIT(IEEE80211_STYPE_DISASSOC >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4) |
			BIT(IEEE80211_STYPE_ACTION >> 4),
	},
	[NL80211_IFTYPE_MESH_POINT] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_AUTH >> 4) |
			BIT(IEEE80211_STYPE_DEAUTH >> 4),
	},
	[NL80211_IFTYPE_P2P_DEVICE] = {
		.tx = 0xffff,
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
			BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
	},
};

static const struct ieee80211_ht_cap mac80211_ht_capa_mod_mask = {
	.ampdu_params_info = IEEE80211_HT_AMPDU_PARM_FACTOR |
			     IEEE80211_HT_AMPDU_PARM_DENSITY,

	.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				IEEE80211_HT_CAP_MAX_AMSDU |
				IEEE80211_HT_CAP_SGI_40),
	.mcs = {
		.rx_mask = { 0xff, 0xff, 0xff, 0xff, 0xff,
			     0xff, 0xff, 0xff, 0xff, 0xff, },
	},
};

struct ieee80211_hw *ieee80211_alloc_hw(size_t priv_data_len,
					const struct ieee80211_ops *ops)
{
	struct ieee80211_local *local;
	int priv_size, i;
	struct wiphy *wiphy;

	if (WARN_ON(!ops->tx || !ops->start || !ops->stop || !ops->config ||
		    !ops->add_interface || !ops->remove_interface ||
		    !ops->configure_filter))
		return NULL;

	if (WARN_ON(ops->sta_state && (ops->sta_add || ops->sta_remove)))
		return NULL;

	/* Ensure 32-byte alignment of our private data and hw private data.
	 * We use the wiphy priv data for both our ieee80211_local and for
	 * the driver's private data
	 *
	 * In memory it'll be like this:
	 *
	 * +-------------------------+
	 * | struct wiphy	    |
	 * +-------------------------+
	 * | struct ieee80211_local  |
	 * +-------------------------+
	 * | driver's private data   |
	 * +-------------------------+
	 *
	 */
	priv_size = ALIGN(sizeof(*local), NETDEV_ALIGN) + priv_data_len;

	wiphy = wiphy_new(&mac80211_config_ops, priv_size);

	if (!wiphy)
		return NULL;

	wiphy->mgmt_stypes = ieee80211_default_mgmt_stypes;

	wiphy->privid = mac80211_wiphy_privid;

	wiphy->flags |= WIPHY_FLAG_NETNS_OK |
			WIPHY_FLAG_4ADDR_AP |
			WIPHY_FLAG_4ADDR_STATION |
			WIPHY_FLAG_REPORTS_OBSS |
			WIPHY_FLAG_OFFCHAN_TX;

	if (ops->remain_on_channel)
		wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	wiphy->features = NL80211_FEATURE_SK_TX_STATUS |
			  NL80211_FEATURE_HT_IBSS;

	if (!ops->set_key)
		wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	wiphy->bss_priv_size = sizeof(struct ieee80211_bss);

	local = wiphy_priv(wiphy);

	local->hw.wiphy = wiphy;

	local->hw.priv = (char *)local + ALIGN(sizeof(*local), NETDEV_ALIGN);

	local->ops = ops;

	/* set up some defaults */
	local->hw.queues = 1;
	local->hw.max_rates = 1;
	local->hw.max_report_rates = 0;
	local->hw.max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;
	local->hw.max_tx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;
	local->hw.offchannel_tx_hw_queue = IEEE80211_INVAL_HW_QUEUE;
	local->hw.conf.long_frame_max_tx_count = wiphy->retry_long;
	local->hw.conf.short_frame_max_tx_count = wiphy->retry_short;
	local->hw.radiotap_mcs_details = IEEE80211_RADIOTAP_MCS_HAVE_MCS |
					 IEEE80211_RADIOTAP_MCS_HAVE_GI |
					 IEEE80211_RADIOTAP_MCS_HAVE_BW;
	local->user_power_level = -1;
	wiphy->ht_capa_mod_mask = &mac80211_ht_capa_mod_mask;

	INIT_LIST_HEAD(&local->interfaces);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))

	__hw_addr_init(&local->mc_list);

#endif
	mutex_init(&local->iflist_mtx);
	mutex_init(&local->mtx);

	mutex_init(&local->key_mtx);
	spin_lock_init(&local->filter_lock);
	spin_lock_init(&local->queue_stop_reason_lock);

	/*
	 * The rx_skb_queue is only accessed from tasklets,
	 * but other SKB queues are used from within IRQ
	 * context. Therefore, this one needs a different
	 * locking class so our direct, non-irq-safe use of
	 * the queue's lock doesn't throw lockdep warnings.
	 */
	skb_queue_head_init_class(&local->rx_skb_queue,
				  &ieee80211_rx_skb_queue_class);

	INIT_DELAYED_WORK(&local->scan_work, ieee80211_scan_work);

	INIT_WORK(&local->restart_work, ieee80211_restart_work);

	INIT_WORK(&local->reconfig_filter, ieee80211_reconfig_filter);
	INIT_WORK(&local->recalc_smps, ieee80211_recalc_smps_work);
	local->smps_mode = IEEE80211_SMPS_OFF;

	INIT_WORK(&local->dynamic_ps_enable_work,
		  ieee80211_dynamic_ps_enable_work);
	INIT_WORK(&local->dynamic_ps_disable_work,
		  ieee80211_dynamic_ps_disable_work);
	setup_timer(&local->dynamic_ps_timer,
		    ieee80211_dynamic_ps_timer, (unsigned long) local);

	INIT_WORK(&local->sched_scan_stopped_work,
		  ieee80211_sched_scan_stopped_work);

	spin_lock_init(&local->ack_status_lock);
	idr_init(&local->ack_status_frames);
	/* preallocate at least one entry */
	idr_pre_get(&local->ack_status_frames, GFP_KERNEL);

	sta_info_init(local);

	for (i = 0; i < IEEE80211_MAX_QUEUES; i++) {
		skb_queue_head_init(&local->pending[i]);
		atomic_set(&local->agg_queue_stop[i], 0);
	}
	tasklet_init(&local->tx_pending_tasklet, ieee80211_tx_pending,
		     (unsigned long)local);

	tasklet_init(&local->tasklet,
		     ieee80211_tasklet_handler,
		     (unsigned long) local);

	skb_queue_head_init(&local->skb_queue);
	skb_queue_head_init(&local->skb_queue_unreliable);

	/* init dummy netdev for use w/ NAPI */
	init_dummy_netdev(&local->napi_dev);

	ieee80211_led_names(local);

	ieee80211_roc_setup(local);

	return &local->hw;
}
EXPORT_SYMBOL(ieee80211_alloc_hw);

int ieee80211_register_hw(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);
	int result, i;
	enum ieee80211_band band;
	int channels, max_bitrates;
	bool supp_ht, supp_vht;
	netdev_features_t feature_whitelist;
	static const u32 cipher_suites[] = {
		/* keep WEP first, it may be removed below */
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,

		/* keep last -- depends on hw flags! */
		WLAN_CIPHER_SUITE_AES_CMAC
	};

	if (hw->flags & IEEE80211_HW_QUEUE_CONTROL &&
	    (local->hw.offchannel_tx_hw_queue == IEEE80211_INVAL_HW_QUEUE ||
	     local->hw.offchannel_tx_hw_queue >= local->hw.queues))
		return -EINVAL;

#ifdef CONFIG_PM
	if ((hw->wiphy->wowlan.flags || hw->wiphy->wowlan.n_patterns) &&
	    (!local->ops->suspend || !local->ops->resume))
		return -EINVAL;
#endif

	if ((hw->flags & IEEE80211_HW_SCAN_WHILE_IDLE) && !local->ops->hw_scan)
		return -EINVAL;

	/* Only HW csum features are currently compatible with mac80211 */
	feature_whitelist = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			    NETIF_F_HW_CSUM;
	if (WARN_ON(hw->netdev_features & ~feature_whitelist))
		return -EINVAL;

	if (hw->max_report_rates == 0)
		hw->max_report_rates = hw->max_rates;

	/*
	 * generic code guarantees at least one band,
	 * set this very early because much code assumes
	 * that hw.conf.channel is assigned
	 */
	channels = 0;
	max_bitrates = 0;
	supp_ht = false;
	supp_vht = false;
	for (band = 0; band < IEEE80211_NUM_BANDS; band++) {
		struct ieee80211_supported_band *sband;

		sband = local->hw.wiphy->bands[band];
		if (!sband)
			continue;
		if (!local->oper_channel) {
			/* init channel we're on */
			local->hw.conf.channel =
			local->oper_channel = &sband->channels[0];
			local->hw.conf.channel_type = NL80211_CHAN_NO_HT;
		}
		channels += sband->n_channels;

		if (max_bitrates < sband->n_bitrates)
			max_bitrates = sband->n_bitrates;
		supp_ht = supp_ht || sband->ht_cap.ht_supported;
		supp_vht = supp_vht || sband->vht_cap.vht_supported;
	}

	local->int_scan_req = kzalloc(sizeof(*local->int_scan_req) +
				      sizeof(void *) * channels, GFP_KERNEL);
	if (!local->int_scan_req)
		return -ENOMEM;

	for (band = 0; band < IEEE80211_NUM_BANDS; band++) {
		if (!local->hw.wiphy->bands[band])
			continue;
		local->int_scan_req->rates[band] = (u32) -1;
	}

	/* if low-level driver supports AP, we also support VLAN */
	if (local->hw.wiphy->interface_modes & BIT(NL80211_IFTYPE_AP)) {
		hw->wiphy->interface_modes |= BIT(NL80211_IFTYPE_AP_VLAN);
		hw->wiphy->software_iftypes |= BIT(NL80211_IFTYPE_AP_VLAN);
	}

	/* mac80211 always supports monitor */
	hw->wiphy->interface_modes |= BIT(NL80211_IFTYPE_MONITOR);
	hw->wiphy->software_iftypes |= BIT(NL80211_IFTYPE_MONITOR);

	/*
	 * mac80211 doesn't support more than 1 channel, and also not more
	 * than one IBSS interface
	 */
	for (i = 0; i < hw->wiphy->n_iface_combinations; i++) {
		const struct ieee80211_iface_combination *c;
		int j;

		c = &hw->wiphy->iface_combinations[i];

		if (c->num_different_channels > 1)
			return -EINVAL;

		for (j = 0; j < c->n_limits; j++)
			if ((c->limits[j].types & BIT(NL80211_IFTYPE_ADHOC)) &&
			    c->limits[j].max > 1)
				return -EINVAL;
	}

#ifndef CONFIG_MAC80211_MESH
	/* mesh depends on Kconfig, but drivers should set it if they want */
	local->hw.wiphy->interface_modes &= ~BIT(NL80211_IFTYPE_MESH_POINT);
#endif

	/* if the underlying driver supports mesh, mac80211 will (at least)
	 * provide routing of mesh authentication frames to userspace */
	if (local->hw.wiphy->interface_modes & BIT(NL80211_IFTYPE_MESH_POINT))
		local->hw.wiphy->flags |= WIPHY_FLAG_MESH_AUTH;

	/* mac80211 supports control port protocol changing */
	local->hw.wiphy->flags |= WIPHY_FLAG_CONTROL_PORT_PROTOCOL;

	if (local->hw.flags & IEEE80211_HW_SIGNAL_DBM)
		local->hw.wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;
	else if (local->hw.flags & IEEE80211_HW_SIGNAL_UNSPEC)
		local->hw.wiphy->signal_type = CFG80211_SIGNAL_TYPE_UNSPEC;

	WARN((local->hw.flags & IEEE80211_HW_SUPPORTS_UAPSD)
	     && (local->hw.flags & IEEE80211_HW_PS_NULLFUNC_STACK),
	     "U-APSD not supported with HW_PS_NULLFUNC_STACK\n");

	/*
	 * Calculate scan IE length -- we need this to alloc
	 * memory and to subtract from the driver limit. It
	 * includes the DS Params, (extended) supported rates, and HT
	 * information -- SSID is the driver's responsibility.
	 */
	local->scan_ies_len = 4 + max_bitrates /* (ext) supp rates */ +
		3 /* DS Params */;
	if (supp_ht)
		local->scan_ies_len += 2 + sizeof(struct ieee80211_ht_cap);

	if (supp_vht)
		local->scan_ies_len +=
			2 + sizeof(struct ieee80211_vht_capabilities);

	if (!local->ops->hw_scan) {
		/* For hw_scan, driver needs to set these up. */
		local->hw.wiphy->max_scan_ssids = 4;
		local->hw.wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	}

	/*
	 * If the driver supports any scan IEs, then assume the
	 * limit includes the IEs mac80211 will add, otherwise
	 * leave it at zero and let the driver sort it out; we
	 * still pass our IEs to the driver but userspace will
	 * not be allowed to in that case.
	 */
	if (local->hw.wiphy->max_scan_ie_len)
		local->hw.wiphy->max_scan_ie_len -= local->scan_ies_len;

	/* Set up cipher suites unless driver already did */
	if (!local->hw.wiphy->cipher_suites) {
		local->hw.wiphy->cipher_suites = cipher_suites;
		local->hw.wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);
		if (!(local->hw.flags & IEEE80211_HW_MFP_CAPABLE))
			local->hw.wiphy->n_cipher_suites--;
	}
	if (IS_ERR(local->wep_tx_tfm) || IS_ERR(local->wep_rx_tfm)) {
		if (local->hw.wiphy->cipher_suites == cipher_suites) {
			local->hw.wiphy->cipher_suites += 2;
			local->hw.wiphy->n_cipher_suites -= 2;
		} else {
			u32 *suites;
			int r, w = 0;

			/* Filter out WEP */

			suites = kmemdup(
				local->hw.wiphy->cipher_suites,
				sizeof(u32) * local->hw.wiphy->n_cipher_suites,
				GFP_KERNEL);
			if (!suites)
				return -ENOMEM;
			for (r = 0; r < local->hw.wiphy->n_cipher_suites; r++) {
				u32 suite = local->hw.wiphy->cipher_suites[r];
				if (suite == WLAN_CIPHER_SUITE_WEP40 ||
				    suite == WLAN_CIPHER_SUITE_WEP104)
					continue;
				suites[w++] = suite;
			}
			local->hw.wiphy->cipher_suites = suites;
			local->hw.wiphy->n_cipher_suites = w;
			local->wiphy_ciphers_allocated = true;
		}
	}

	if (!local->ops->remain_on_channel)
		local->hw.wiphy->max_remain_on_channel_duration = 5000;

	if (local->ops->sched_scan_start)
		local->hw.wiphy->flags |= WIPHY_FLAG_SUPPORTS_SCHED_SCAN;

	/* mac80211 based drivers don't support internal TDLS setup */
	if (local->hw.wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS)
		local->hw.wiphy->flags |= WIPHY_FLAG_TDLS_EXTERNAL_SETUP;

	result = wiphy_register(local->hw.wiphy);
	if (result < 0)
		goto fail_wiphy_register;

	/*
	 * We use the number of queues for feature tests (QoS, HT) internally
	 * so restrict them appropriately.
	 */
	if (hw->queues > IEEE80211_MAX_QUEUES)
		hw->queues = IEEE80211_MAX_QUEUES;

	local->workqueue =
		alloc_ordered_workqueue(wiphy_name(local->hw.wiphy), 0);
	if (!local->workqueue) {
		result = -ENOMEM;
		goto fail_workqueue;
	}

	/*
	 * The hardware needs headroom for sending the frame,
	 * and we need some headroom for passing the frame to monitor
	 * interfaces, but never both at the same time.
	 */
	local->tx_headroom = max_t(unsigned int , local->hw.extra_tx_headroom,
				   IEEE80211_TX_STATUS_HEADROOM);

	debugfs_hw_add(local);

	/*
	 * if the driver doesn't specify a max listen interval we
	 * use 5 which should be a safe default
	 */
	if (local->hw.max_listen_interval == 0)
		local->hw.max_listen_interval = 5;

	local->hw.conf.listen_interval = local->hw.max_listen_interval;

	local->dynamic_ps_forced_timeout = -1;

	result = ieee80211_wep_init(local);
	if (result < 0)
		wiphy_debug(local->hw.wiphy, "Failed to initialize wep: %d\n",
			    result);

	ieee80211_led_init(local);

	rtnl_lock();

	result = ieee80211_init_rate_ctrl_alg(local,
					      hw->rate_control_algorithm);
	if (result < 0) {
		wiphy_debug(local->hw.wiphy,
			    "Failed to initialize rate control algorithm\n");
		goto fail_rate;
	}

	/* add one default STA interface if supported */
	if (local->hw.wiphy->interface_modes & BIT(NL80211_IFTYPE_STATION)) {
		result = ieee80211_if_add(local, "wlan%d", NULL,
					  NL80211_IFTYPE_STATION, NULL);
		if (result)
			wiphy_warn(local->hw.wiphy,
				   "Failed to add default virtual iface\n");
	}

	rtnl_unlock();

	local->network_latency_notifier.notifier_call =
		ieee80211_max_network_latency;
	result = pm_qos_add_notifier(PM_QOS_NETWORK_LATENCY,
				     &local->network_latency_notifier);
	if (result) {
		rtnl_lock();
		goto fail_pm_qos;
	}

#ifdef CONFIG_INET
	local->ifa_notifier.notifier_call = ieee80211_ifa_changed;
	result = register_inetaddr_notifier(&local->ifa_notifier);
	if (result)
		goto fail_ifa;
#endif

	netif_napi_add(&local->napi_dev, &local->napi, ieee80211_napi_poll,
			local->hw.napi_weight);

	return 0;

#ifdef CONFIG_INET
 fail_ifa:
	pm_qos_remove_notifier(PM_QOS_NETWORK_LATENCY,
			       &local->network_latency_notifier);
	rtnl_lock();
#endif
 fail_pm_qos:
	ieee80211_led_exit(local);
	ieee80211_remove_interfaces(local);
 fail_rate:
	rtnl_unlock();
	ieee80211_wep_free(local);
	sta_info_stop(local);
	destroy_workqueue(local->workqueue);
 fail_workqueue:
	wiphy_unregister(local->hw.wiphy);
 fail_wiphy_register:
	if (local->wiphy_ciphers_allocated)
		kfree(local->hw.wiphy->cipher_suites);
	kfree(local->int_scan_req);
	return result;
}
EXPORT_SYMBOL(ieee80211_register_hw);

void ieee80211_unregister_hw(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	tasklet_kill(&local->tx_pending_tasklet);
	tasklet_kill(&local->tasklet);

	pm_qos_remove_notifier(PM_QOS_NETWORK_LATENCY,
			       &local->network_latency_notifier);
#ifdef CONFIG_INET
	unregister_inetaddr_notifier(&local->ifa_notifier);
#endif

	rtnl_lock();

	/*
	 * At this point, interface list manipulations are fine
	 * because the driver cannot be handing us frames any
	 * more and the tasklet is killed.
	 */
	ieee80211_remove_interfaces(local);

	rtnl_unlock();

	cancel_work_sync(&local->restart_work);
	cancel_work_sync(&local->reconfig_filter);

	ieee80211_clear_tx_pending(local);
	rate_control_deinitialize(local);

	if (skb_queue_len(&local->skb_queue) ||
	    skb_queue_len(&local->skb_queue_unreliable))
		wiphy_warn(local->hw.wiphy, "skb_queue not empty\n");
	skb_queue_purge(&local->skb_queue);
	skb_queue_purge(&local->skb_queue_unreliable);
	skb_queue_purge(&local->rx_skb_queue);

	destroy_workqueue(local->workqueue);
	wiphy_unregister(local->hw.wiphy);
	sta_info_stop(local);
	ieee80211_wep_free(local);
	ieee80211_led_exit(local);
	kfree(local->int_scan_req);
}
EXPORT_SYMBOL(ieee80211_unregister_hw);

static int ieee80211_free_ack_frame(int id, void *p, void *data)
{
	WARN_ONCE(1, "Have pending ack frames!\n");
	kfree_skb(p);
	return 0;
}

void ieee80211_free_hw(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	mutex_destroy(&local->iflist_mtx);
	mutex_destroy(&local->mtx);

	if (local->wiphy_ciphers_allocated)
		kfree(local->hw.wiphy->cipher_suites);

	idr_for_each(&local->ack_status_frames,
		     ieee80211_free_ack_frame, NULL);
	idr_destroy(&local->ack_status_frames);

	wiphy_free(local->hw.wiphy);
}
EXPORT_SYMBOL(ieee80211_free_hw);

static int __init ieee80211_init(void)
{
	struct sk_buff *skb;
	int ret;

	BUILD_BUG_ON(sizeof(struct ieee80211_tx_info) > sizeof(skb->cb));
	BUILD_BUG_ON(offsetof(struct ieee80211_tx_info, driver_data) +
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE > sizeof(skb->cb));

	ret = rc80211_minstrel_init();
	if (ret)
		return ret;

	ret = rc80211_minstrel_ht_init();
	if (ret)
		goto err_minstrel;

	ret = rc80211_pid_init();
	if (ret)
		goto err_pid;

	ret = ieee80211_iface_init();
	if (ret)
		goto err_netdev;

	return 0;
 err_netdev:
	rc80211_pid_exit();
 err_pid:
	rc80211_minstrel_ht_exit();
 err_minstrel:
	rc80211_minstrel_exit();

	return ret;
}

static void __exit ieee80211_exit(void)
{
	rc80211_pid_exit();
	rc80211_minstrel_ht_exit();
	rc80211_minstrel_exit();

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37))
	flush_scheduled_work();
#endif

	if (mesh_allocated)
		ieee80211s_stop();

	ieee80211_iface_exit();

	rcu_barrier();
}


subsys_initcall(ieee80211_init);
module_exit(ieee80211_exit);

MODULE_DESCRIPTION("IEEE 802.11 subsystem");
MODULE_LICENSE("GPL");
