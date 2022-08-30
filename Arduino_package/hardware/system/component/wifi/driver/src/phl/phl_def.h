#ifndef _PHL_DEF_H_
#define _PHL_DEF_H_
/*
* structs defined in this file are shared with halbb or halrf
*/

#define MAX_BAND_NUM 1 /*DBCC use 2 bands*/

struct rtw_chan_def {
	enum band_type band; /* protocol -2.4G,5G,6G*/
	enum channel_width bw;
	enum chan_offset offset;/*used as offset of 40MHz, g6 driver may also used as offset of primary channel*/
	u8 chan; /*primary channel*/
	u8 center_ch;
};

enum rtw_edcca_mode_t {
	RTW_EDCCA_NORM	= 0, /* normal */
	RTW_EDCCA_ADAPT	= 1, /* adaptivity */
	RTW_EDCCA_CS	= 2, /* carrier sense */

	RTW_EDCCA_MODE_NUM,
	RTW_EDCCA_DEF		= RTW_EDCCA_MODE_NUM, /* default (ref to domain code), used at country chplan map's override field */
};

enum rtw_drv_mode {
	RTW_DRV_MODE_NORMAL = 0,
	RTW_DRV_MODE_MP = 1,/*mp mode has to be 1 to be compatible with phydm code 'dm->mp_mode == 1'*/

	/* Fixed Max Value*/
	RTW_DRV_MODE_MAX = 255
};

struct rtw_wifi_role_t {
	u8 hw_band;/*useless, just for halbb*/
};

enum wlan_mode {
	WLAN_MD_INVALID = 0,
	WLAN_MD_11B	= BIT0,
	WLAN_MD_11A	= BIT1,
	WLAN_MD_11G	= BIT2,
	WLAN_MD_11N	= BIT3,
	WLAN_MD_11AC	= BIT4,
	WLAN_MD_11AX	= BIT5,

	/* Type for current wireless mode */
	WLAN_MD_11BG	= (WLAN_MD_11B | WLAN_MD_11G),
	WLAN_MD_11GN	= (WLAN_MD_11G | WLAN_MD_11N),
	WLAN_MD_11AN	= (WLAN_MD_11A | WLAN_MD_11N),
	WLAN_MD_11BN	= (WLAN_MD_11B | WLAN_MD_11N),
	WLAN_MD_11BGN	= (WLAN_MD_11B | WLAN_MD_11G | WLAN_MD_11N),
	WLAN_MD_11BGAC = (WLAN_MD_11B | WLAN_MD_11G | WLAN_MD_11AC),
	WLAN_MD_11BGAX = (WLAN_MD_11B | WLAN_MD_11G | WLAN_MD_11AX),
	WLAN_MD_11GAC  = (WLAN_MD_11G | WLAN_MD_11AC),
	WLAN_MD_11GAX  = (WLAN_MD_11G | WLAN_MD_11AX),
	WLAN_MD_11A_AC = (WLAN_MD_11A | WLAN_MD_11AC),
	WLAN_MD_11A_AX = (WLAN_MD_11A | WLAN_MD_11AX),

	/* Capability -Type for registry default wireless mode */
	WLAN_MD_11AGN	= (WLAN_MD_11A | WLAN_MD_11G | WLAN_MD_11N),
	WLAN_MD_11ABGN	= (WLAN_MD_11A | WLAN_MD_11B | WLAN_MD_11G | WLAN_MD_11N),
	WLAN_MD_11ANAC	= (WLAN_MD_11A | WLAN_MD_11N | WLAN_MD_11AC),
	WLAN_MD_11BGNAC = (WLAN_MD_11B | WLAN_MD_11G | WLAN_MD_11N | WLAN_MD_11AC),
	WLAN_MD_11GNAC  = (WLAN_MD_11G | WLAN_MD_11N | WLAN_MD_11AC),
	WLAN_MD_24G_MIX = (WLAN_MD_11B | WLAN_MD_11G | WLAN_MD_11N | WLAN_MD_11AC | WLAN_MD_11AX),
	WLAN_MD_5G_MIX	= (WLAN_MD_11A | WLAN_MD_11N | WLAN_MD_11AC | WLAN_MD_11AX),
	WLAN_MD_6G_MIX 	= (WLAN_MD_11A | WLAN_MD_11AX),
	WLAN_MD_MAX	= (WLAN_MD_24G_MIX | WLAN_MD_5G_MIX),
};

enum rtw_gi_ltf {//AX_TODO
	RTW_GILTF_LGI_4XHE32 = 0,
	RTW_GILTF_SGI_4XHE08 = 1,
	RTW_GILTF_2XHE16 = 2,
	RTW_GILTF_2XHE08 = 3,
	RTW_GILTF_1XHE16 = 4,
	RTW_GILTF_1XHE08 = 5,
	RTW_GILTF_MAX
};
/*
Protocol - RX CAP from 80211 PKT,
driver TX related function need to
reference __rx__ of rtw_phl_stainfo_t->asoc_cap
*/
struct protocol_cap_t {//AX_TODO
	/* MAC related */
	u8 trig_padding: 2;	//hal_mac used
	u8 sm_ps: 2;
	u8 twt: 6;
	u8 all_ack: 1;
	u8 a_ctrl: 3;	/* BSR, BSPR BQPR AMPDU AGG, BQR */
	u8 ht_vht_trig_rx: 1;
	u8 bsscolor;
	u16 rts_th: 10;

	/* BB related */
	u8 ht_ldpc: 1;
	u8 vht_ldpc: 1;
	u8 he_ldpc: 1;	//halbb used

	/*
	 * supported_rates: Supported data rate of CCK/OFDM.
	 * The rate definition follow Wi-Fi spec, unit is 500kb/s,
	 * and the MSB(bit 7) represent basic rate.
	 * ex. CCK 2Mbps not basic rate is encoded as 0x04,
	 *     and OFDM 6M basic rate is encoded as 0x8c.
	 * Suppose rates come from Supported Rates and Extended Supported
	 * Rates IE.
	 * Value 0 means it is end of array, and no more valid data rate follow.
	 */
	u8 he_rx_mcs[6];/*80,160,80+80*/ //halbb used
	u8 he_tx_mcs[6];/*80,160,80+80*/
	u8 stbc_ht_tx: 1;	//halbb used
	u8 stbc_ht_rx: 2;	//halbb used
	u8 stbc_vht_rx: 3;	//halbb used
	u8 stbc_he_rx: 1;	//halbb used
	u8 ltf_gi;	//halbb used
	u8 dcm_max_const_rx: 2;	//halbb used
	u8 pkt_padding: 2;
	u8 ppe_thr[8][4];
	u8 er_su: 1;	//halbb used

	/* RF related */
	u8 nss_tx: 3;
	u8 nss_rx: 3;	//halbb used

};

/*for halbb, driver can set these or use default value in halbb*/
struct rtw_edcca_cap_t {
	u8 edcca_adap_th_2g;
	u8 edcca_adap_th_5g;
	u8 edcca_cbp_th_6g;
	u8 edcca_carrier_sense_th;
};

struct dev_cap_t {
#ifdef USE_HALBB_HALRF
	struct rtw_edcca_cap_t edcca_cap;
	u32 rfk_cap;
	u8 pkg_type;/*todo, halbb/halrf not really used this right now*/
	u8 pwrbyrate_off;
	u8 pwrlmt_type;
	u8 rf_board_opt;
#endif
	u8 xcap;
	u8 rfe_type;
};

struct rtw_stats {
	u64 tx_byte_uni;/*halbb just print for debug*/
	u64 rx_byte_uni;/*halbb just print for debug*/
	u64 tx_byte_total;/*halbb just print for debug*/
	u64 rx_byte_total;/*halbb just print for debug*/
	u32 tx_tp_kbits;/*halbb needs*/
	u32 rx_tp_kbits;/*halbb needs*/
	u16 tx_moving_average_tp; /*todo, g6 driver todo, halbb just print for debug*/
	u16 rx_moving_average_tp; /*todo, g6 driver todo,halbb just print for debug*/
	u64 last_rx_byte_uni;
	u64 last_tx_byte_uni;
	u32 rx_tf_cnt; /* rx trigger frame number (accumulated, only reset in disconnect) */
};

struct rtw_hal_stainfo_t;
struct rtw_phl_stainfo_t {
	bool active;
	struct rtw_wifi_role_t *wrole;
	struct rtw_hal_stainfo_t *hal_sta;
	struct rtw_stats stats;
	enum wlan_mode wmode;
	struct rtw_chan_def chandef;//AX_TODO
	struct protocol_cap_t asoc_cap;//AX_TODO
	u8 macid;		/* driver & halbb */
	u16 aid;			/* driver */
	u8 mac_addr[6];	/* driver */
};

struct rtw_phl_com_t {
	enum rtw_hci_type hci_type;/*useless, ameba is always axi, but hallbb need this!*/
	enum rtw_drv_mode drv_mode;/*normal or mp mode*/
	struct dev_cap_t dev_cap;
#ifdef USE_HALBB_HALRF
	struct rtw_stats phl_stats;
	u8 edcca_mode;
#endif
};
#endif
