#ifndef __RTL8730A_API_MAC_H__
#define __RTL8730A_API_MAC_H__

/*this file calls mac's APIs*/
u32 rtw_hal_mac_send_h2c(struct rtw_hal_com_t *hal_com, struct rtw_g6_h2c_hdr *hdr, u32 *pvalue);
enum rtw_hal_status rtw_hal_mac_send_h2c_ameba(struct rtw_hal_com_t *hal_com, u8 ElementID, u32 CmdLen, u32 *pvalue);
enum rtw_hal_status rtw_hal_mac_lamode_cfg(struct rtw_hal_com_t *hal_com, u8 func_en,
		u8 restart_en, u8 timeout_en, u8 timeout_val,
		u8 data_loss_imr, u8 la_tgr_tu_sel, u8 tgr_time_val);
void rtw_hal_mac_get_buffer_data(struct rtw_hal_com_t *hal_com, u32 strt_addr, u8 *buf, u32 len, u32 dbg_path);
enum rtw_hal_status rtw_hal_mac_set_xcap(struct rtw_hal_com_t *hal_com, u8 sc_xo, u32 value);
enum rtw_hal_status rtw_hal_mac_lamode_cfg_buf(struct rtw_hal_com_t *hal_com, u8 buf_sel, u32 *addr_start, u32 *addr_end);
u32 rtw_hal_mac_lamode_trig(struct rtw_hal_com_t *hal_com, u8 trig);
enum rtw_hal_status rtw_hal_mac_get_lamode_st(struct rtw_hal_com_t *hal_com, u8 *la_state,
		u16 *la_finish_addr, bool *la_round_up,
		bool *la_loss_data);
enum rtw_hal_status rtw_hal_mac_get_xcap(struct rtw_hal_com_t *hal_com, u8 sc_xo, u32 *value);
enum rtw_hal_status rtw_hal_mac_set_tpu_mode(struct rtw_hal_com_t *hal_com,
		enum rtw_tpu_op_mode op_mode_new, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_limit_reg(struct rtw_hal_com_t *hal_com, enum phl_band_idx phy_idx);
enum rtw_hal_status rtw_hal_mac_write_pwr_by_rate_reg(struct rtw_hal_com_t *hal_com, enum phl_band_idx phy_idx);
enum rtw_hal_status rtw_hal_mac_write_pwr_limit_rua_reg(struct rtw_hal_com_t *hal_com, u8 band);
u32 rtw_hal_mac_write_msk_pwr_reg(struct rtw_hal_com_t *hal_com, u8 band, u32 offset, u32 mask, u32 val);
enum rtw_hal_status rtw_hal_mac_get_pwr_reg(struct rtw_hal_com_t *hal_com, u8 band, u32 offset, u32 *val);
enum rtw_hal_status rtw_hal_mac_write_pwr_ofst_mode(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_ofst_bw(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_limit_en(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_ref_reg(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_set_pwr_reg(struct rtw_hal_com_t *hal_com, u8 band, u32 offset, u32 val);

enum rtw_hal_status rtw_hal_tx_pause(struct rtw_hal_com_t *hal_com, u8 band_idx, bool tx_pause, enum tx_pause_rson rson);
enum rtw_hal_status rtw_hal_efuse_get_info(struct rtw_hal_com_t *hal_com, enum rtw_efuse_info info_type, void *value, u8 size);
enum rtw_hal_status rtw_hal_mac_read_phy_efuse(struct rtw_hal_com_t *hal_com, u32 addr, u32 size, u8 *value);

#endif
