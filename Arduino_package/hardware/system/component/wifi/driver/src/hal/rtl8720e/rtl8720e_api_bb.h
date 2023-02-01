#ifndef __RTL8720E_API_BB_H__
#define __RTL8720E_API_BB_H__

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
void rtw_hal_bb_cmd(struct rtw_hal_com_t *hal_com, char *input, char *output, u32 out_len);
bool rtw_hal_bb_physts_parsing(_adapter *padapter, struct rx_pkt_attrib	*pattrib, u8 *addr, u16 physts_total_length);
enum rtw_hal_status rtw_hal_bb_set_plcp_tx(struct rtw_hal_com_t *hal_com, void *in, void *user, enum phl_phy_idx plcp_phy_idx, u8 *plcp_sts);

#ifdef CONFIG_MP_INCLUDED
void rtw_hal_bb_plcp_gen(_adapter *padapter);
void rtw_hal_bb_set_pmac_con_tx(_adapter *padapter, u8 enable, u8 is_cck);
void rtw_hal_bb_set_tmac_tx(_adapter *padapter);
void rtw_hal_bb_reset_bb_hw_cnt(_adapter *padapter);
u32 rtw_hal_bb_mp_get_rx_crc_ok(_adapter *padapter);
void rtw_hal_bb_set_crystal_cap(struct rtw_hal_com_t *hal_com, u8 crystal_cap);
void rtw_hal_bb_ctrl_rx_cca(struct rtw_hal_com_t *hal_com, bool cca_en, enum phl_phy_idx phy_idx);
void rtw_hal_bb_cck_cnt_statistics(struct rtw_hal_com_t *hal_com);
void rtw_hal_bb_ofdm_cnt_statistics(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx);
void rtw_hal_bb_cck_tx_cnt_statistics(struct rtw_hal_com_t *hal_com);
void rtw_hal_bb_ofdm_tx_cnt_statistics(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx);
void rtw_hal_bb_print_cnt(struct rtw_hal_com_t *hal_com, bool cck_en, enum phl_phy_idx phy_idx);
void rtw_hal_bb_set_pwr_index(struct rtw_hal_com_t *hal_com,  u16 pwr_idx, enum rf_path tx_path);
void rtw_hal_bb_set_pwr_dbm(struct rtw_hal_com_t *hal_com, s16 pwr_dbm);
void rtw_hal_bb_mp_rx_get_rssi(struct rtw_hal_com_t *hal_com, enum rf_path rx_path, u8 *rssi);
void rtw_hal_bb_set_gain_offset(struct rtw_hal_com_t *hal_com, s8 rx_gain_offset, enum rf_path rx_path, enum phl_phy_idx phy_idx, u8 iscck);
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

u8 rtw_hal_bb_set_sta_id(_adapter *padapter, u16 sta_id, enum phl_phy_idx phy_idx);
u8 rtw_hal_bb_set_bss_color(_adapter *padapter, u8 bss_color, enum phl_phy_idx phy_idx);
u8 rtw_hal_bb_set_tb_pwr_ofst(_adapter *padapter, s16 ofst, enum phl_phy_idx phy_idx);

#ifdef CONFIG_CSI
enum rtw_hal_status rtw_hal_bb_csi_parsing(_adapter *padapter, u8 *addr, u32 len, u8 *rpt_buf,
		struct rtw_csi_rpt_hdr_info *rpt_hdr, struct rtw_csi_phyinfo_rpt *phy_info, struct rtw_csi_drv_rpt *drv);
void rtw_hal_bb_csi_cfg(_adapter *padapter, struct rtw_csi_bbcr_cfg *cfg);
void rtw_hal_bb_csi_status_en(_adapter *padapter, bool en, enum phl_phy_idx phy_idx);
#endif /* CONFIG_CSI */

#endif
