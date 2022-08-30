#ifndef __HAL_DEF_H__
#define __HAL_DEF_H__

/*
* structs defined in this file are shared with halbb or halrf
*/

/*control of pwr by limit and power by rate*/
enum hal_pwr_by_rate_setting {
	PW_BY_RATE_ALL_SAME = 0,
	PW_BY_RATE_ON = 1
};

enum hal_pwr_limit_type {
	PWLMT_DISABLE = 0,
	PWBYRATE_AND_PWLMT = 1,
	PWLMT_BY_EFUSE = 2
};

enum rtw_chip_id {
	CHIP_WIFI6_8852A,
	CHIP_WIFI6_8834A,
	CHIP_WIFI6_8852B,
	CHIP_WIFI6_8852C,
	CHIP_WIFI6_8730A,
	CHIP_WIFI6_8720E,
	CHIP_WIFI6_MAX
};

enum rtw_cv {/*cut version*/
	CAV,
	CBV,
	CCV,
	CDV,
	CEV,
	CFV,
	CGV,
	CTV,
	CMAXV,
};

enum rtw_hal_status {
	RTW_HAL_STATUS_SUCCESS, /* 0 */
	RTW_HAL_STATUS_FAILURE, /* 1 */
	RTW_HAL_STATUS_RESOURCE, /* 2 */
	RTW_HAL_STATUS_IO_INIT_FAILURE, /* 3 */
	RTW_HAL_STATUS_MAC_INIT_FAILURE, /* 4 */
	RTW_HAL_STATUS_BB_INIT_FAILURE, /* 5 */
	RTW_HAL_STATUS_RF_INIT_FAILURE, /* 6 */
	RTW_HAL_STATUS_BTC_INIT_FAILURE, /* 7 */
	RTW_HAL_STATUS_HAL_INIT_FAILURE, /* 8 */
	RTW_HAL_STATUS_EFUSE_UNINIT, /* 9 */
	RTW_HAL_STATUS_EFUSE_IVALID_OFFSET, /* 10 */
	RTW_HAL_STATUS_EFUSE_PG_FAIL, /* 11 */
	RTW_HAL_STATUS_MAC_API_FAILURE, /* 12 */
	RTW_HAL_STATUS_BB_CH_INFO_LAST_SEG, /*13*/
	RTW_HAL_STATUS_UNKNOWN_RFE_TYPE, /* 14 */
	RTW_HAL_STATUS_TIMEOUT, /* 15 */
};

struct rtw_rssi_info {//AX_TODO
	u8 rssi; /* u(8,1), hal-bb provide, read only : 0~110 (dBm = rssi -110) */
	u16 rssi_ma; /* u(16,5),  hal-bb provide, read only : u16 U(12,4)*/
	u16 rssi_ma_path[4];
	u16 pkt_cnt_data;
	u8 rssi_bcn; /* u(8,1), beacon RSSI, hal-bb provide, read only : 0~110 (dBm = rssi -110) */
	u16 rssi_bcn_ma; /* u(16,5),  beacon RSSI, hal-bb provide, read only*/
	u16 rssi_bcn_ma_path[4];
	u16 pkt_cnt_bcn;
	u8 ma_factor: 4;
	u8 ma_factor_bcn: 4;
	u8 rssi_ofdm; /* u(8,1),  hal-bb provide, read only : packet, for debug */
	u8 rssi_cck; /* u(8,1),  hal-bb provide, read only : packet, for debug */
	u8 assoc_rssi; /* phl_rx provide, read only */
	/* phl_rx provide, read only : Moving Average RSSI information for the STA */
	u8 ma_rssi; /* moving average : 0 ~ PHL_MAX_RSSI (dBm = rssi - PHL_MAX_RSSI) */
	u8 ma_rssi_mgnt; /* moving average rssi for beacon/probe : 0 ~ PHL_MAX_RSSI (dBm = rssi - PHL_MAX_RSSI) */
	u16 snr_ma; /* u(16,4), hal-bb provide, read only, SNR= snr_ma dBm*/
};

/* from cmn_sta_info */
struct rtw_ra_sta_info {//AX_TODO
	/*u8 rate_id;			remove !!! use wmode in phl, [PHYDM] ratr_idx*/
	/*u8 rssi_level;			[PHYDM]*/
	/*u8 is_first_connect:1;		change connect flow, [PHYDM] CE: ra_rpt_linked, AP: H2C_rssi_rpt*/
	/*u8 is_support_sgi:1;		mov to phl [driver]*/
	/*u8 is_vht_enable:2;		mov to phl [driver]*/
	/*u8 disable_ra:1;			mov to hal [driver]*/
	/*u8 disable_pt:1;			remove for no PT, [driver] remove is_disable_power_training*/
	/*u8 txrx_state:2;			///////////////need to check if needed, [PHYDM] 0: Tx, 1:Rx, 2:bi-direction*/
	/*u8 is_noisy:1;			///////////////need to check if needed, [PHYDM]*/
	u16 curr_tx_rate;			/*use struct bb_rate_info, [PHYDM] FW->Driver*/
	enum channel_width ra_bw_mode;	/*remove to phl, [Driver] max bandwidth, for RA only*/
	enum channel_width curr_tx_bw;	/*bb_rate_info, [PHYDM] FW->Driver*/
	/* u8 drv_ractrl; */

	/* Ctrl */
	bool dis_ra; /*move from rtw_hal_stainfo_t*/
	bool ra_registered;/*move from rtw_hal_stainfo_t*/
	u64 ra_mask;/*move from rtw_hal_stainfo_t*/ /*drv decide by specific req*/
	u64 cur_ra_mask;/*move from rtw_hal_stainfo_t*/
	/*halbb create, mod by driver and decide by rssi or other*/
	u8 cal_giltf; /* 3bit gi_ltf ctrl by driver*/
	bool fix_giltf_en; /*giltf from cal_giltf or halbb*/
	bool fixed_rt_en;
	//struct rtw_rate_info fixed_rt_i; //AX_TODO
	u8 rainfo_cfg1; /* prepare for other control*/
	u8 rainfo_cfg2; /* prepare for other control*/

	/* Report */
	//struct rtw_rate_info rpt_rt_i; //AX_TODO
	u8 curr_retry_ratio;		/*[HALBB] FW->Driver*/

	bool ra_csi_rate_en;
	bool fixed_csi_rate_en;
	u8 band_num;
	//struct rtw_rate_info csi_rate; //AX_TODO

	u8 avg_agg;
	u32 tx_ok_cnt[4];
	u32 tx_retry_cnt[4];
	u32 tx_total_cnt;
	/*u64 ramask;*/
};


struct rtw_hw_band {
	struct rtw_chan_def cur_chandef;
};

struct rtw_hal_com_t {
#ifdef USE_HALBB_HALRF
	enum rtw_chip_id chip_id;
	enum rtw_cv cv;/* cut version */
	struct dev_cap_t dev_hw_cap;/* halbb/halrf will set these values */
#endif
	struct rtw_hw_band band[MAX_BAND_NUM];/*band0/band1 for DBCC*/
};

struct rtw_hal_stainfo_t {
	struct rtw_rssi_info rssi_stat;
	/* from cmn_sta_info */
	struct rtw_ra_sta_info	ra_info;
};

#endif
