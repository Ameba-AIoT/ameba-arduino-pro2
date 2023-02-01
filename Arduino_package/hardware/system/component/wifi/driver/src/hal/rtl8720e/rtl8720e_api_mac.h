#ifndef __RTL8720E_API_MAC_H__
#define __RTL8720E_API_MAC_H__

/*this file calls mac's APIs*/

#if 0  /* LA_TODO: will be delete when la ok*/
#define hal_to_mac(_halinfo)	((struct mac_ax_adapter *)((_halinfo)->mac))
struct hal_info_t {
	struct rtw_phl_com_t *phl_com;
	struct rtw_hal_com_t *hal_com;
	//_os_atomic hal_mac_mem;

	struct hal_trx_ops *trx_ops;
	//struct hal_ops_t hal_ops;
#ifdef CONFIG_PCI_HCI
	void *txch_map;
#endif
	void *rpr_cfg;
	void *mac;  /*halmac*/
	void *bb;
	void *rf;
	void *btc;
	void *efuse;
	u8 monitor_mode;  /* default: 0 */
};
#endif

struct mac_ax_la_status {
	/* LA data dump finish address = (la_buf_wptr -1) */
	u16 la_buf_wptr;
	/*1: round up, 0: No round up */
	u8 la_buf_rndup_ind: 1;
	/*3'h0: LA idle ; 3'h1: LA start; 3'h2: LA finish stop;*/
	/*3'h3:LA finish timeout; 3'h4: LA re-start*/
	u8 la_sw_fsmst: 3;
	/* LA data loss due to pktbuffer busy */
	u8 la_data_loss: 1;
};

u32 rtw_hal_mac_send_h2c(struct rtw_hal_com_t *hal_com, struct rtw_g6_h2c_hdr *hdr, u32 *pvalue);
enum rtw_hal_status rtw_hal_mac_send_h2c_ameba(struct rtw_hal_com_t *hal_com, u8 ElementID, u32 CmdLen, u32 *pvalue);
enum rtw_hal_status rtw_hal_mac_set_xcap(struct rtw_hal_com_t *hal_com, u8 sc_xo, u32 value);
enum rtw_hal_status rtw_hal_mac_get_xcap(struct rtw_hal_com_t *hal_com, u8 sc_xo, u32 *value);

enum rtw_hal_status rtw_hal_mac_lamode_cfg(struct rtw_hal_com_t *hal_com, u8 func_en,
		u8 restart_en, u8 timeout_en, u8 timeout_val, u8 data_loss_imr, u8 la_tgr_tu_sel, u8 tgr_time_val);
void rtw_hal_mac_get_buffer_data(struct rtw_hal_com_t *hal_com, u32 start_addr, u8 *buf, u32 len, u32 dbg_path);
enum rtw_hal_status rtw_hal_mac_lamode_cfg_buf(struct rtw_hal_com_t *hal_com, u8 buf_sel, u32 *addr_start, u32 *addr_end);
u32 rtw_hal_mac_lamode_trig(struct rtw_hal_com_t *hal_com, u8 trig);
void rtw_hal_mac_get_lamode_st(struct rtw_hal_com_t *hal_com, u8 *la_state, u16 *la_finish_addr, bool *la_round_up, bool *la_loss_data);

enum rtw_hal_status rtw_hal_mac_set_tpu_mode(struct rtw_hal_com_t *hal_com, enum rtw_tpu_op_mode op_mode_new, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_limit_reg(struct rtw_hal_com_t *hal_com, enum phl_band_idx phy_idx);
enum rtw_hal_status rtw_hal_mac_write_pwr_by_rate_reg(struct rtw_hal_com_t *hal_com, enum phl_band_idx phy_idx);
enum rtw_hal_status rtw_hal_mac_write_pwr_limit_rua_reg(struct rtw_hal_com_t *hal_com, u8 band);
u32 rtw_hal_mac_write_msk_pwr_reg(struct rtw_hal_com_t *hal_com, u8 band, u32 offset, u32 mask, u32 val);
enum rtw_hal_status rtw_hal_mac_get_pwr_reg(struct rtw_hal_com_t *hal_com, u8 band, u32 offset, u32 *val);
enum rtw_hal_status rtw_hal_mac_write_pwr_ofst_mode(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_ofst_bw(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_write_pwr_ref_reg(struct rtw_hal_com_t *hal_com, u8 band);
enum rtw_hal_status rtw_hal_mac_set_pwr_reg(struct rtw_hal_com_t *hal_com, u8 band, u32 offset, u32 val);
enum rtw_hal_status rtw_hal_mac_write_pwr_limit_en(struct rtw_hal_com_t *hal_com, u8 band);

enum rtw_hal_status rtw_hal_tx_pause(struct rtw_hal_com_t *hal_com, u8 band_idx, bool tx_pause, enum tx_pause_rson rson);
enum rtw_hal_status rtw_hal_efuse_get_info(struct rtw_hal_com_t *hal_com, enum rtw_efuse_info info_type, void *value, u8 size);
enum rtw_hal_status rtw_hal_mac_read_phy_efuse(struct rtw_hal_com_t *hal_com, u32 addr, u32 size, u8 *value);
void rtw_hal_mac_update_mac_address(u8 mac_id, u8 *mac_addr);
void rtw_hal_mac_update_sounding_cfg(u8 enable, u8 *mac_addr);
#endif
