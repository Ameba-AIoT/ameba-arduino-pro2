#ifndef __RTL8730A_API_BB_H__
#define __RTL8730A_API_BB_H__

/*this file calls halbb's APIs*/
void rtw_hal_bb_stainfo_init(_adapter *padapter, struct rtw_phl_stainfo_t *sta);
void rtw_hal_bb_stainfo_deinit(_adapter *padapter, struct rtw_phl_stainfo_t *sta);
u32 rtw_hal_bb_init(struct rtw_phl_com_t *phl_com, _adapter *padapter);
void rtw_hal_bb_deinit(struct rtw_phl_com_t *phl_com, _adapter *padapter);
void rtw_hal_bb_dm_init(struct rtw_hal_com_t *hal_com);
void rtw_hal_bb_dm_deinit(struct rtw_phl_com_t *phl_com, struct rtw_hal_com_t *hal_com);
void rtw_hal_init_bb_reg(struct rtw_hal_com_t *hal_com);
void rtw_hal_bb_watchdog(struct rtw_hal_com_t *hal_com, u8 is_lps);
u8 rtw_hal_bb_ctrl_bw_ch(struct rtw_hal_com_t *hal_com, u8 pri_ch, u8 central_ch_seg0,
						 u8 central_ch_seg1, enum band_type band,
						 enum channel_width bw, enum phl_phy_idx phy_idx);
u8 rtw_hal_write_rf_reg(struct rtw_hal_com_t *hal_com, enum rf_path path,
						u32 reg_addr, u32 bit_mask, u32 data);
u32 rtw_hal_read_rf_reg(struct rtw_hal_com_t *hal_com, enum rf_path path,
						u32 reg_addr, u32 bit_mask);
void rtw_hal_bb_set_pow_patten_sharp(struct rtw_hal_com_t *hal_com, u8 channel, u8 is_cck, u8 sharp_id, enum phl_phy_idx phy_idx);
void rtw_hal_bb_adc_en(struct rtw_hal_com_t *hal_com, u8 en);
void rtw_hal_bb_reset_en(struct rtw_hal_com_t *hal_com, bool en, enum phl_phy_idx phy_idx);
void rtw_hal_bb_tssi_cont_en(struct rtw_hal_com_t *hal_com, bool en, enum rf_path path);
void rtw_hal_bb_dfs_en(struct rtw_hal_com_t *hal_com, bool en);
void rtw_hal_bb_trx_path_cfg(struct rtw_hal_com_t *hal_com, enum rf_path tx, u8 tx_nss, enum rf_path rx, u8 rx_nss);
void rtw_hal_bb_cmd(_adapter *padapter, char *input, char *output, u32 out_len);
#ifdef CONFIG_MP_INCLUDED
void rtw_hal_bb_plcp_gen(_adapter *padapter);
void rtw_hal_bb_set_pmac_tx(_adapter *padapter);
void rtw_hal_bb_set_tmac_tx(_adapter *padapter);
void rtw_hal_bb_reset_bb_hw_cnt(_adapter *padapter);
u32 rtw_hal_bb_mp_get_rx_crc_ok(_adapter *padapter);
void rtw_hal_bb_set_crystal_cap(struct rtw_hal_com_t *hal_com, u8 crystal_cap);
void rtw_hal_bb_ctrl_rx_cca(struct rtw_hal_com_t *hal_com, bool cca_en, enum phl_phy_idx phy_idx);
void rtw_hal_bb_cck_cnt_statistics(struct rtw_hal_com_t *hal_com);
void rtw_hal_bb_ofdm_cnt_statistics(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx);
void rtw_hal_bb_print_cnt(struct rtw_hal_com_t *hal_com, bool cck_en, enum phl_phy_idx phy_idx);
void rtw_hal_bb_set_pwr_index(struct rtw_hal_com_t *hal_com,  u16 pwr_idx, enum rf_path tx_path);
void rtw_hal_bb_set_pwr_dbm(struct rtw_hal_com_t *hal_com, s16 pwr_dbm);
void rtw_hal_bb_mp_rx_get_rssi(struct rtw_hal_com_t *hal_com, enum rf_path rx_path, u8 *rssi);
#endif

enum rtw_hal_status rtw_hal_bb_cfg_rx_path(struct rtw_hal_com_t *hal_com, u8 rx_path);
enum rtw_hal_status rtw_hal_bb_cfg_tx_path(struct rtw_hal_com_t *hal_com, u8 tx_path);
enum rtw_hal_status rtw_hal_bb_set_pmac_packet_tx(struct rtw_hal_com_t *hal_com, u8 enable,
		u8 is_cck, u16 tx_cnt, u16 period,
		u16 tx_time, u8 cck_lbk_en,
		enum phl_phy_idx phy_idx);
enum rtw_hal_status rtw_hal_bb_backup_info(struct rtw_hal_com_t *hal_com, u8 cur_phy_idx);
enum rtw_hal_status rtw_hal_bb_restore_info(struct rtw_hal_com_t *hal_com, u8 cur_phy_idx);
void rtw_hal_bb_set_tx_pow_ref(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx);
enum rtw_hal_status rtw_hal_bb_set_power(struct rtw_hal_com_t *hal_com, s16 power_dbm, enum phl_phy_idx phy_idx);
enum rtw_hal_status rtw_hal_bb_tx_mode_switch(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u8 mode);
#endif
