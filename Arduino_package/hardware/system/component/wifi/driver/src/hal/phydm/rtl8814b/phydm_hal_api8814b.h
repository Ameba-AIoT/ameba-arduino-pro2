/******************************************************************************
 *
 * Copyright(c) 2007 - 2017  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#ifndef __INC_PHYDM_API_H_8814B__
#define __INC_PHYDM_API_H_8814B__
#if (RTL8814B_SUPPORT == 1)
#define PHY_CONFIG_VERSION_8814B "0.0.0" /*2017.11.27*/
/*#define CONFIG_TXAGC_DEBUG_8814B*/
/*#define CONFIG_RCK_OFFSET_ADJUST_8814B*/

#define SMTANT_TMP_RFE_TYPE 100

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff

#define number_channel_interferecne 4

#define NUM_PATH 4
#define NUM_TRY_SW_PSD_8814B_LOG2 5 /* 1 << 5 */
#define NUM_TRY_SW_PSD_8814C_LOG2 0 /* use hw psd avg */

#define DET_AUTO 0
#define DET_NBI 1
#define DET_CSI 2
#define DET_DISABLE 3
#define DET_CSI_NBI_EN 4

#define config_phydm_read_rf_check_8814b(data) (data != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8814b(data) (data != INVALID_TXAGC_DATA)

struct txagc_table_8814b {
	u8 ref_pow_cck[4];
	u8 ref_pow_ofdm[4];
	s8 diff_t[NUM_RATE_AC_4SS]; /*by rate differential table*/
};

#ifdef CONFIG_RCK_OFFSET_ADJUST_8814B
enum rck_adjust_level {
	RCK_OFFSET_NORMAL	= 0,
	RCK_OFFSET_MINUS_LV1	= 1
};
#endif

boolean phydm_chk_pkg_set_valid_8814b(struct dm_struct *dm,
				      u8 ver_bb, u8 ver_rf);

void phydm_rfe_8814b_init(struct dm_struct *dm);

boolean
phydm_rfe_8814b(struct dm_struct *dm, u8 channel);

void
phydm_bb_reset_8814b(struct dm_struct *dm);

u32 config_phydm_read_syn_reg_8814b(struct dm_struct *dm, enum rf_syn syn_path,
				    u32 reg_addr, u32 bit_mask);

u32 config_phydm_read_rf_reg_8814b(struct dm_struct *dm, enum rf_path path,
				   u32 reg_addr, u32 bit_mask);

u32 config_phydm_write_rf_syn_8814b(struct dm_struct *dm,
				    enum rf_syn syn_path, u32 reg_addr,
				    u32 bit_mask, u32 data);
boolean
config_phydm_write_rf_reg_8814b(struct dm_struct *dm, enum rf_path path,
				u32 reg_addr, u32 bit_mask, u32 data);
boolean
phydm_write_txagc_1byte_8814b(struct dm_struct *dm, s8 pw_idx, u8 hw_rate);
boolean
config_phydm_write_txagc_ref_8814b(struct dm_struct *dm, u8 power_index,
				   enum rf_path path,
				   enum PDM_RATE_TYPE mod_type);

boolean
config_phydm_write_txagc_diff_8814b(struct dm_struct *dm,
				    s8 power_index1, s8 power_index2,
				    s8 power_index3, s8 power_index4,
				    u8 hw_rate);

#ifdef CONFIG_TXAGC_DEBUG_8814B
void phydm_txagc_tab_buff_show_8814b(struct dm_struct *dm);
#endif

s8 config_phydm_read_txagc_diff_8814b(struct dm_struct *dm, u8 hw_rate);

u8 config_phydm_read_txagc_8814b(struct dm_struct *dm, enum rf_path path,
				 u8 hw_rate, enum PDM_RATE_TYPE mod_type);

void config_phydm_path_adda_setting_8814b(struct dm_struct *dm);

boolean
config_phydm_trx_mode_8814b(struct dm_struct *dm, enum bb_path tx_path,
			    enum bb_path rx_path);
boolean
config_phydm_trx_mode_ext_8814b(struct dm_struct *dm, enum bb_path tx_path,
				enum bb_path rx_path,
				enum bb_path tx_path_sel_1ss,
				enum bb_path tx_path_sel_2ss,
				enum bb_path tx_path_sel_3ss);
boolean
config_bf_tx_path_ext_8814b(struct dm_struct *dm,
				    enum bb_path tx_path,
				    enum bb_path tx_path_sel_1ss,
				    enum bb_path tx_path_sel_2ss,
				    enum bb_path tx_path_sel_3ss);

boolean
config_phydm_trx_80p80_8814b(struct dm_struct *dm, enum bb_path tx_path,
			     enum bb_path rx_path, u8 primary_ch_idx);

boolean
config_phydm_switch_band_8814b(struct dm_struct *dm, u8 central_ch);

boolean
config_phydm_switch_channel_8814b(struct dm_struct *dm, u8 central_ch);

boolean
config_phydm_switch_bw_8814b(struct dm_struct *dm, u8 primary_ch_idx,
			     enum channel_width bandwidth);

boolean
config_phydm_ch_80p80_8814b(struct dm_struct *dm, u8 central_ch1,
			    u8 central_ch2, u8 primary_ch_idx);

boolean
config_phydm_switch_channel_bw_8814b(struct dm_struct *dm, u8 central_ch,
				     u8 primary_ch_idx, enum channel_width bw);

boolean
config_phydm_parameter_init_8814b(struct dm_struct *dm,
				  enum odm_parameter_init type);

boolean
config_phydm_syn_ch_8814b(struct dm_struct *dm, u8 central_ch,
			  enum rf_syn syn_path);

#if CONFIG_POWERSAVING
boolean phydm_rfe_8814b_lps(struct dm_struct *dm, boolean enable_sw_rfe);

boolean phydm_8814b_lps(struct dm_struct *dm, boolean enable_lps);
#endif /* #if CONFIG_POWERSAVING */

void
config_phydm_set_txagc_to_hw_8814b(struct dm_struct *dm);

boolean
config_phydm_write_txagc_8814b(struct dm_struct *dm,
			       u32 power_index, enum rf_path path, u8 hw_rate);

void phydm_dynamic_spur_det_eliminate_8814b(struct dm_struct *dm);

boolean config_phydm_mu_anapar_8814b(struct dm_struct *dm, u8 mu_bfee_cnt);
/* ======================================================================== */
/* These following functions can be used for PHY DM only*/
void phydm_init_hw_info_by_rfe_type_8814b(struct dm_struct *dm);

s32 phydm_get_condition_number_8814b(struct dm_struct *dm);
/* ======================================================================== */
#endif /* RTL8814B_SUPPORT */
#endif /* __INC_PHYDM_API_H_8814B__ */
