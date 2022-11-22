/******************************************************************************
*
* Copyright(c) 2016 Realtek Corporation. All rights reserved.
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
#ifndef _RTL8735B_H_
#define _RTL8735B_H_

#include <drv_types.h>		/* PADAPTER */
#include <rtw_rf.h>		/* CHANNEL_WIDTH */
#include <rtw_xmit.h>		/* struct pkt_attrib, struct xmit_frame */
#include <rtw_recv.h>		/* struct recv_frame */
#include <hal_intf.h>		/* HAL_DEF_VARIABLE */
//#include <rtl8735b.h>	// _SYSON_BASE
#include <hal_api.h>	// HAL_READ32
#include "cmsis.h"

#define SYSTEM_CTRL_BASE	0x40000000UL
#define WIFI_REG_BASE		WLAN_BASE   // 0x40080000UL

#define DRIVER_EARLY_INT_TIME_8735B	0x05
#define BCN_DMA_ATIME_INT_TIME_8735B	0x02

/* rtl8735b_halinit.c */
u32 rtl8735b_power_on(PADAPTER);
void rtl8735b_power_off(PADAPTER);

u8 rtl8735b_mac_init(PADAPTER);
//u8 rtl8735b_mac_verify(PADAPTER);
void rtl8735b_hal_init_channel_setting(PADAPTER adapter);
void rtl8735b_hal_init_misc(PADAPTER padapter);
u32 rtl8735b_hal_init(PADAPTER);
u32 rtl8735b_hal_deinit(PADAPTER);
void rtl8735b_init_default_value(PADAPTER);
u8 rtl8735b_phy_init(PADAPTER adapter);
u8 rtl8735b_init_phy_parameter_mac(PADAPTER adapter);

/* rtl8735b_mac.c */
u8 rtl8735b_rcr_config(PADAPTER, u32 rcr);
u8 rtl8735b_rcr_get(PADAPTER, u32 *rcr);
u8 rtl8735b_rcr_check(PADAPTER, u32 check_bit);
u8 rtl8735b_rcr_add(PADAPTER, u32 add);
u8 rtl8735b_rcr_clear(PADAPTER, u32 clear);
u8 rtl8735b_rx_ba_ssn_appended(PADAPTER);
u8 rtl8735b_rx_fcs_append_switch(PADAPTER, u8 enable);
u8 rtl8735b_rx_fcs_appended(PADAPTER);
u8 rtl8735b_rx_tsf_addr_filter_config(_adapter *adapter, u8 config);
void rtl8735b_fw_dl(PADAPTER, u8 wowlan);

/* rtl8735b_ops.c */
void rtl8735b_read_efuse(PADAPTER);
void rtl8735b_run_thread(PADAPTER);
void rtl8735b_cancel_thread(PADAPTER);
void rtl8735b_sethwreg(PADAPTER, u8 variable, u8 *pval);
void rtl8735b_gethwreg(PADAPTER, u8 variable, u8 *pval);
u8 rtl8735b_sethaldefvar(PADAPTER, HAL_DEF_VARIABLE, void *pval);
u8 rtl8735b_gethaldefvar(PADAPTER, HAL_DEF_VARIABLE, void *pval);
//void rtl8735b_set_hal_ops(PADAPTER);
void rtl8735b_resume_tx_beacon(PADAPTER);
void rtl8735b_stop_tx_beacon(PADAPTER);

/* tx */
void rtl8735b_init_xmit_priv(_adapter *adapter);
void rtl8735b_fill_txdesc_sectype(struct pkt_attrib *, u8 *ptxdesc);
void rtl8735b_fill_txdesc_vcs(PADAPTER, struct pkt_attrib *, u8 *ptxdesc);
void rtl8735b_fill_txdesc_phy(PADAPTER, struct pkt_attrib *, u8 *ptxdesc);
u8 rtl8735b_bw_mapping(PADAPTER, struct pkt_attrib *);
u8 rtl8735b_sc_mapping(PADAPTER, struct pkt_attrib *);
void rtl8735b_cal_txdesc_chksum(PADAPTER, u8 *ptxdesc);
void rtl8735b_update_txdesc(struct xmit_frame *, u8 *pbuf);
void rtl8735b_dbg_dump_tx_desc(PADAPTER, int frame_tag, u8 *ptxdesc);

/* rx */
void rtl8735b_rxdesc2attribute(struct rx_pkt_attrib *a, u8 *desc);
void rtl8735b_query_rx_desc(union recv_frame *, u8 *pdesc);

/* rtl8735b_cmd.c */
s32 rtl8735b_fillh2ccmd(PADAPTER, u8 id, u32 buf_len, u8 *pbuf);
void rtl8735b_set_FwMacIdConfig_cmd(PADAPTER, u64 bitmap, u8 *arg, u8 bw);
void rtl8735b_set_FwRssiSetting_cmd(PADAPTER, u8 *param);
void rtl8735b_set_FwPwrMode_cmd(PADAPTER, u8 psmode);
void rtl8735b_set_FwPwrMode_Ext_cmd(PADAPTER adapter);
void rtl8735b_set_FwPwrModeInIPS_cmd(PADAPTER adapter, u8 cmd_param);
void c2h_handler_rtl8735b(_adapter *adapter, u8 *pbuf, u16 length);
void c2h_pre_handler_rtl8735b(_adapter *adapter, u8 *pbuf, s32 length);
#ifdef CONFIG_BT_COEXIST
void rtl8735b_download_BTCoex_AP_mode_rsvd_page(PADAPTER);
#endif /* CONFIG_BT_COEXIST */

/* rtl8735b_phy.c */
u32 rtl8735b_read_bb_reg(PADAPTER, u32 addr, u32 mask);
void rtl8735b_write_bb_reg(PADAPTER, u32 addr, u32 mask, u32 val);
u32 rtl8735b_read_rf_reg(PADAPTER, u32 path, u32 addr, u32 mask);
void rtl8735b_write_rf_reg(PADAPTER, u32 path, u32 addr, u32 mask, u32 val);
void rtl8735b_set_channel_bw(PADAPTER, u8 center_ch, enum channel_width, u8 offset40, u8 offset80);
void rtl8735b_set_channel(PADAPTER, u8 center_ch);
void rtl8735b_set_tx_power_level(PADAPTER, u8 channel);
void rtl8735b_get_tx_power_level(PADAPTER, s32 *power);
void rtl8735b_set_txpwr_done(PADAPTER);
void rtl8735b_set_tx_power_index(PADAPTER, u32 powerindex, u8 rfpath, u8 rate);
//u8 rtl8735b_get_tx_power_index(PADAPTER, u8 rfpath, u8 rate, u8 bandwidth, u8 channel, struct txpwr_idx_comp *tic);
void rtl8735b_notch_filter_switch(PADAPTER, bool enable);

/* rtl8735b_dm.c */
void rtl8735b_query_phy_statistic(PADAPTER padapter, rtw_phy_statistics_t *statistic);

#endif /* _RTL8735B_H_ */
