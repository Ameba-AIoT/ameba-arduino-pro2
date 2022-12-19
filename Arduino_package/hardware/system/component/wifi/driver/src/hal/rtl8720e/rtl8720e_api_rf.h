#ifndef __RTL8720E_API_RF_H__
#define __RTL8720E_API_RF_H__

/*this file calls harf's APIs*/
enum rtw_hal_status rtw_hal_rf_init(struct rtw_phl_com_t *phl_com, _adapter *padapter);
void rtw_hal_rf_deinit(struct rtw_phl_com_t *phl_com, _adapter *padapter);
void rtw_hal_rf_dm_init(struct rtw_hal_com_t *hal_com);
void rtw_hal_init_rf_reg(struct rtw_hal_com_t *hal_com);
void rtw_hal_rf_watchdog(struct rtw_hal_com_t *hal_com);
enum rtw_hal_status rtw_hal_rf_set_ch_bw(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy, u8 central_ch,
		enum band_type band, enum channel_width bw);
u8 rtw_hal_rf_set_power(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy, enum phl_pwr_table pwr_table);
void rtw_hal_rf_do_tssi_scan(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy);
enum rtw_hal_status rtw_hal_rf_chl_rfk_trigger(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, bool force);
bool rtw_hal_rf_get_efuse_info(struct rtw_hal_com_t *hal_com, u8 *efuse_map, enum rtw_efuse_info id, void *value, u32 length, u8 autoload_status);
void rtw_hal_rf_cmd(struct rtw_hal_com_t *hal_com, char *input, char *output, u32 out_len);

#ifdef CONFIG_MP_INCLUDED
void rtw_hal_rf_dpk_onoff(struct rtw_hal_com_t *hal_com,  bool is_enable);
enum rtw_hal_status rtw_hal_rf_dpk_trigger(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, bool force);
void rtw_hal_rf_dpk_info(struct rtw_hal_com_t *hal_com, char input[][16], u32 *_used, char *output, u32 *_out_len);
enum rtw_hal_status rtw_hal_rf_iqk_trigger(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, bool force);
void rtw_hal_rf_lck_trigger(struct rtw_hal_com_t *hal_com);
u8 rtw_hal_rf_get_thermal(struct rtw_hal_com_t *hal_com, u8 rf_path);
void rtw_hal_rf_set_power_track(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u8 value);
u8 rtw_hal_rf_get_power_track(struct rtw_hal_com_t *hal_com);
void rtw_hal_rf_set_tssi_de_for_tx_verify(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u32 tssi_de, u8 path);
void rtw_hal_rf_set_tssi_de_offset(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u32 tssi_de_offset, u8 path);
s32 rtw_hal_rf_get_online_tssi_de(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u8 path, s32 dbm, s32 puot);
void rtw_hal_rf_psd_init(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u8 path, u8 iq_path, u32 avg, u32 fft);
u32 rtw_hal_rf_psd_get_point_data(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, s32 point);
void rtw_hal_rf_psd_query(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx, u32 point, u32 start_point, u32 stop_point, u32 *outbuf);
void rtw_hal_rf_psd_restore(struct rtw_hal_com_t *hal_com, enum phl_phy_idx phy_idx);
enum rtw_hal_status rtw_hal_rf_set_singletone_tx(struct rtw_hal_com_t *hal_com, u8 is_on, enum rf_path path);

#endif
#endif
