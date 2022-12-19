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
#ifndef __INC_PHYDM_API_H_8197G__
#define __INC_PHYDM_API_H_8197G__

#if (RTL8197G_SUPPORT)

#define PHY_CONFIG_VERSION_8197G "1.1.4" /* @2018.11.15*/
/*#define CONFIG_TXAGC_DEBUG_8197G*/

#define SMTANT_TMP_RFE_TYPE 100

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff

#define number_channel_interferecne 4

#define config_phydm_read_rf_check_8197g(data) ((data) != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8197g(data) ((data) != INVALID_TXAGC_DATA)

struct txagc_table_8197g {
	u8 ref_pow_cck[2];
	u8 ref_pow_ofdm[2];
	s8 diff_t[NUM_RATE_AC_2SS]; /*by rate differential table*/
};

void phydm_init_hw_info_by_rfe_type_8197g(struct dm_struct *dm);

boolean phydm_chk_pkg_set_valid_8197g(struct dm_struct *dm,
				      u8 ver_bb, u8 ver_rf);

u32 config_phydm_read_rf_reg_8197g(struct dm_struct *dm, enum rf_path path,
				   u32 reg_addr, u32 bit_mask);

boolean config_phydm_write_rf_reg_8197g(struct dm_struct *dm,
					enum rf_path path, u32 reg_addr,
					u32 bit_mask, u32 data);

boolean phydm_write_txagc_1byte_8197g(struct dm_struct *dm, u32 pw_idx,
				      u8 hw_rate);

boolean config_phydm_write_txagc_ref_8197g(struct dm_struct *dm,
					   u8 power_index, enum rf_path path,
					   enum PDM_RATE_TYPE rate_type);

boolean config_phydm_write_txagc_diff_8197g(struct dm_struct *dm,
					    s8 power_index1, s8 power_index2,
					    s8 power_index3, s8 power_index4,
					    u8 hw_rate);

#ifdef CONFIG_TXAGC_DEBUG_8197G
void phydm_txagc_tab_buff_show_8197g(struct dm_struct *dm);
#endif

s8 config_phydm_read_txagc_diff_8197g(struct dm_struct *dm, u8 hw_rate);

u8 config_phydm_read_txagc_8197g(struct dm_struct *dm, enum rf_path path,
				 u8 hw_rate, enum PDM_RATE_TYPE rate_type);

void phydm_config_tx_path_8197g(struct dm_struct *dm,
				enum bb_path tx_path_en,
				enum bb_path tx_path_sel_1ss,
				enum bb_path tx_path_sel_cck);

boolean config_phydm_trx_mode_8197g(struct dm_struct *dm,
				    enum bb_path tx_path_en,
				    enum bb_path rx_path,
				    enum bb_path tx_path_sel_1ss);

boolean config_phydm_switch_band_8197g(struct dm_struct *dm, u8 central_ch);

boolean config_phydm_switch_channel_8197g(struct dm_struct *dm,
					  u8 central_ch);

boolean config_phydm_switch_bandwidth_8197g(struct dm_struct *dm, u8 pri_ch,
					    enum channel_width bw);

boolean config_phydm_switch_channel_bw_8197g(struct dm_struct *dm,
					     u8 central_ch,
					     u8 primary_ch_idx,
					     enum channel_width bandwidth);

void phydm_i_only_setting_8197g(struct dm_struct *dm, boolean en_i_only,
				boolean en_before_cca);

void phydm_1rcca_setting_8197g(struct dm_struct *dm, boolean en_1rcca);

boolean config_phydm_parameter_init_8197g(struct dm_struct *dm,
					  enum odm_parameter_init type);

#if CONFIG_POWERSAVING
boolean phydm_rfe_8197g_lps(struct dm_struct *dm, boolean enable_sw_rfe);

boolean phydm_8197g_lps(struct dm_struct *dm, boolean enable_lps);
#endif /* #if CONFIG_POWERSAVING */

void config_phydm_set_txagc_to_hw_8197g(struct dm_struct *dm);

boolean config_phydm_write_txagc_8197g(struct dm_struct *dm, u32 power_index,
				       enum rf_path path, u8 hw_rate);

void phydm_set_txagc_by_table_8197g(struct dm_struct *dm,
				    struct txagc_table_8197g *tab);

void phydm_get_txagc_ref_and_diff_8197g(struct dm_struct *dm,
					u8 txagc_buff[2][NUM_RATE_AC_2SS],
					u16 length,
					struct txagc_table_8197g *tab);
#endif /* RTL8197G_SUPPORT */
#endif /*  __INC_PHYDM_API_H_8197G__ */
