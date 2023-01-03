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
#ifndef __INC_PHYDM_API_H_8812F__
#define __INC_PHYDM_API_H_8812F__

#if (RTL8812F_SUPPORT)

#define PHY_CONFIG_VERSION_8812F "1.1.0" /*2019.02.19*/

#define SMTANT_TMP_RFE_TYPE 100

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff

#define NUM_PATH 2
#define NUM_TRY 32

#define DET_AUTO 0
#define DET_NBI 1
#define DET_CSI 2
#define DET_DISABLE 3

#define config_phydm_read_rf_check_8812f(data) ((data) != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8812f(data) ((data) != INVALID_TXAGC_DATA)

struct txagc_table_8812f {
	u8 ref_pow_cck[2];
	u8 ref_pow_ofdm[2];
	s8 diff_t[NUM_RATE_AC_2SS]; /*by rate differential table*/
};

u32 phydm_check_bit_mask_8812f(u32 bit_mask, u32 data_original, u32 data);

struct tx_path_en_8812f {
	u8 tx_path_en_ofdm_1sts;
	u8 tx_path_en_ofdm_2sts;
	u8 tx_path_en_cck;
	boolean is_path_ctrl_by_bb_reg;
};

void phydm_bb_reset_8812f(struct dm_struct *dm);

boolean phydm_chk_pkg_set_valid_8812f(struct dm_struct *dm,
				      u8 ver_bb, u8 ver_rf);

u32 config_phydm_read_rf_reg_8812f(struct dm_struct *dm, enum rf_path path,
				   u32 reg_addr, u32 bit_mask);

boolean config_phydm_write_rf_reg_8812f(struct dm_struct *dm, enum rf_path path,
					u32 reg_addr, u32 bit_mask, u32 data);

boolean phydm_write_txagc_1byte_8812f(struct dm_struct *dm, u32 pw_idx,
				      u8 hw_rate);

boolean config_phydm_write_txagc_ref_8812f(struct dm_struct *dm, u8 power_index,
					   enum rf_path path,
					   enum PDM_RATE_TYPE rate_type);

boolean config_phydm_write_txagc_diff_8812f(struct dm_struct *dm,
					    s8 power_index1, s8 power_index2,
					    s8 power_index3, s8 power_index4,
					    u8 hw_rate);

s8 config_phydm_read_txagc_diff_8812f(struct dm_struct *dm, u8 hw_rate);

u8 config_phydm_read_txagc_8812f(struct dm_struct *dm, enum rf_path path,
				 u8 hw_rate, enum PDM_RATE_TYPE rate_type);

void phydm_get_tx_path_en_setting_8812f(struct dm_struct *dm,
					struct tx_path_en_8812f *path);

void phydm_config_tx_path_8812f(struct dm_struct *dm, enum bb_path tx_path_2ss,
				enum bb_path tx_path_sel_1ss,
				enum bb_path tx_path_sel_cck);

boolean config_phydm_trx_mode_8812f(struct dm_struct *dm,
				    enum bb_path tx_path_en,
				    enum bb_path rx_path,
				    enum bb_path tx_path_sel_1ss);

boolean config_phydm_switch_band_8812f(struct dm_struct *dm, u8 central_ch);

//u16 phydm_get_dis_dpd_by_rate_8812f(struct dm_struct *dm, boolean is_2g);

boolean config_phydm_switch_channel_8812f(struct dm_struct *dm, u8 central_ch);

boolean config_phydm_switch_bandwidth_8812f(struct dm_struct *dm, u8 pri_ch,
					    enum channel_width bw);

boolean config_phydm_switch_channel_bw_8812f(struct dm_struct *dm,
					     u8 central_ch, u8 primary_ch_idx,
					     enum channel_width bandwidth);

void phydm_i_only_setting_8812f(struct dm_struct *dm, boolean en_i_only,
				boolean en_before_cca);

void phydm_1rcca_setting_8812f(struct dm_struct *dm, boolean en_1rcca);

void phydm_ch_smooth_setting_8812f(struct dm_struct *dm, boolean en_ch_smooth);
boolean config_phydm_parameter_init_8812f(struct dm_struct *dm,
					  enum odm_parameter_init type);

#if CONFIG_POWERSAVING

boolean phydm_rfe_8812f_lps(struct dm_struct *dm, boolean enable_sw_rfe);

boolean phydm_8812f_lps(struct dm_struct *dm, boolean enable_lps);

#endif /* #if CONFIG_POWERSAVING */

void config_phydm_set_txagc_to_hw_8812f(struct dm_struct *dm);

boolean config_phydm_write_txagc_8812f(struct dm_struct *dm, u32 power_index,
				       enum rf_path path, u8 hw_rate);

void phydm_set_txagc_by_table_8812f(struct dm_struct *dm,
				    struct txagc_table_8812f *tab);

void phydm_get_txagc_ref_and_diff_812f(struct dm_struct *dm,
				       u8 txagc_buff[2][NUM_RATE_AC_2SS],
				       u16 length,
				       struct txagc_table_8812f *tab);
#endif /* RTL8812F_SUPPORT */
#endif /*  __INC_PHYDM_API_H_8812F__ */
