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
#ifndef _RTL8710C_H_
#define _RTL8710C_H_

#include <drv_types.h>		/* PADAPTER */
#include <rtw_rf.h>		/* CHANNEL_WIDTH */
#include <rtw_xmit.h>		/* struct pkt_attrib, struct xmit_frame */
#include <rtw_recv.h>		/* struct recv_frame */
#include <hal_intf.h>		/* HAL_DEF_VARIABLE */
#include <hal_api.h>	// HAL_READ32
#include "cmsis.h"

#define WIFI_REG_BASE KM4_WLAN_BASE
#define SYSTEM_CTRL_BASE	SYSON_BASE
#define WLAN_BASE KM4_WLAN_BASE

#define DRIVER_EARLY_INT_TIME_8710C	0x05
#define BCN_DMA_ATIME_INT_TIME_8710C	0x02

#define FLASH_CAL_DATA_SIZE				0x1000

/* rtl8710c_halinit.c */
u32 rtl8710c_power_on(PADAPTER);
void rtl8710c_power_off(PADAPTER);

u8 rtl8710c_mac_init(PADAPTER);
//u8 rtl8710c_mac_verify(PADAPTER);
void rtl8710c_hal_init_channel_setting(PADAPTER adapter);
void rtl8710c_hal_init_misc(PADAPTER padapter);
u32 rtl8710c_hal_init(PADAPTER);
u32 rtl8710c_hal_deinit(PADAPTER);
void rtl8710c_init_default_value(PADAPTER);
u8 rtl8710c_phy_init(PADAPTER adapter);
u8 rtl8710c_init_phy_parameter_mac(PADAPTER adapter);

/* rtl8710c_mac.c */
u8 rtl8710c_rcr_config(PADAPTER, u32 rcr);
u8 rtl8710c_rcr_get(PADAPTER, u32 *rcr);
u8 rtl8710c_rcr_check(PADAPTER, u32 check_bit);
u8 rtl8710c_rcr_add(PADAPTER, u32 add);
u8 rtl8710c_rcr_clear(PADAPTER, u32 clear);
u8 rtl8710c_rx_ba_ssn_appended(PADAPTER);
u8 rtl8710c_rx_fcs_append_switch(PADAPTER, u8 enable);
u8 rtl8710c_rx_fcs_appended(PADAPTER);
u8 rtl8710c_rx_tsf_addr_filter_config(_adapter *adapter, u8 config);
void rtl8710c_fw_dl(PADAPTER, u8 wowlan);
void rtl8710c_fw_redl(PADAPTER, u8 wowlan);

/* rtl8710c_ops.c */
void rtl8710c_read_efuse(PADAPTER);
void rtl8710c_run_thread(PADAPTER);
void rtl8710c_cancel_thread(PADAPTER);
void rtl8710c_sethwreg(PADAPTER, u8 variable, u8 *pval);
void rtl8710c_gethwreg(PADAPTER, u8 variable, u8 *pval);
u8 rtl8710c_sethaldefvar(PADAPTER, HAL_DEF_VARIABLE, void *pval);
u8 rtl8710c_gethaldefvar(PADAPTER, HAL_DEF_VARIABLE, void *pval);
//void rtl8710c_set_hal_ops(PADAPTER);
void rtl8710c_resume_tx_beacon(PADAPTER);
void rtl8710c_stop_tx_beacon(PADAPTER);

/* tx */
void rtl8710c_init_xmit_priv(_adapter *adapter);
#if defined(RTW_HALMAC)
void rtl8710c_fill_txdesc_sectype(struct pkt_attrib *, u8 *ptxdesc);
#else
u8 rtl8710c_fill_txdesc_sectype(struct pkt_attrib *pattrib);
#endif
void rtl8710c_fill_txdesc_vcs(PADAPTER, struct pkt_attrib *, u8 *ptxdesc);
void rtl8710c_fill_txdesc_phy(PADAPTER, struct pkt_attrib *, u8 *ptxdesc);
u8 rtl8710c_bw_mapping(PADAPTER, struct pkt_attrib *);
u8 rtl8710c_sc_mapping(PADAPTER, struct pkt_attrib *);
void rtl8710c_cal_txdesc_chksum(PADAPTER, u8 *ptxdesc);
void rtl8710c_update_txdesc(struct xmit_frame *, u8 *pbuf);
void rtl8710c_dbg_dump_tx_desc(PADAPTER, int frame_tag, u8 *ptxdesc);

/* rx */
void rtl8710c_rxdesc2attribute(struct rx_pkt_attrib *a, u8 *desc);
void rtl8710c_query_rx_desc(union recv_frame *, u8 *pdesc);

/* rtl8710c_cmd.c */
s32 rtl8710c_fillh2ccmd(PADAPTER, u8 id, u32 buf_len, u8 *pbuf);
void rtl8710c_set_FwMacIdConfig_cmd(PADAPTER, u64 bitmap, u8 *arg, u8 bw);
void rtl8710c_set_FwRssiSetting_cmd(PADAPTER, u8 *param);
void rtl8710c_set_FwPwrMode_cmd(PADAPTER, u8 psmode);
void rtl8710c_set_FwPwrModeInIPS_cmd(PADAPTER adapter, u8 cmd_param);
void c2h_handler_rtl8710c(_adapter *adapter, u8 *pbuf, u16 length);
void c2h_pre_handler_rtl8710c(_adapter *adapter, u8 *pbuf, s32 length);
#if defined(CONFIG_BT_COEXIST) || defined(CONFIG_BT_COEXIST_SOC)
void rtl8710c_set_FwRsvdPagePkt(PADAPTER padapter, BOOLEAN bDLFinished);
void rtl8710c_download_BTCoex_AP_mode_rsvd_page(PADAPTER padapter, u8 mstatus, u8 mode);
#endif /* CONFIG_BT_COEXIST */

/* rtl8710c_phy.c */
u32 rtl8710c_read_bb_reg(PADAPTER, u32 addr, u32 mask);
void rtl8710c_write_bb_reg(PADAPTER, u32 addr, u32 mask, u32 val);
u32 rtl8710c_read_rf_reg(PADAPTER, u32 path, u32 addr, u32 mask);
void rtl8710c_write_rf_reg(PADAPTER, u32 path, u32 addr, u32 mask, u32 val);
void rtl8710c_set_channel_bw(PADAPTER, u8 center_ch, enum channel_width, u8 offset40, u8 offset80);
void rtl8710c_set_channel(PADAPTER, u8 center_ch);
void rtl8710c_set_tx_power_level(PADAPTER, u8 channel);
void rtl8710c_get_tx_power_level(PADAPTER, s32 *power);
void rtl8710c_set_tx_power_index(PADAPTER, u32 powerindex, u8 rfpath, u8 rate);
//u8 rtl8710c_get_tx_power_index(PADAPTER, u8 rfpath, u8 rate, u8 bandwidth, u8 channel, struct txpwr_idx_comp *tic);
void rtl8710c_notch_filter_switch(PADAPTER, bool enable);

#define PHY_QueryBBReg(Adapter, RegAddr, BitMask) rtl8710c_read_bb_reg((Adapter), (RegAddr), (BitMask))
#define PHY_SetBBReg(Adapter, RegAddr, BitMask, Data) rtl8710c_write_bb_reg((Adapter), (RegAddr), (BitMask), (Data))
#define PHY_QueryRFReg(Adapter, eRFPath, RegAddr, BitMask) rtl8710c_read_rf_reg((Adapter), (eRFPath), (RegAddr), (BitMask))
#define PHY_SetRFReg(Adapter, eRFPath, RegAddr, BitMask, Data) rtl8710c_write_rf_reg((Adapter), (eRFPath), (RegAddr), (BitMask), (Data))
#define PHY_SetMacReg	PHY_SetBBReg
#define PHY_QueryMacReg PHY_QueryBBReg
#endif /* _RTL8710C_H_ */
