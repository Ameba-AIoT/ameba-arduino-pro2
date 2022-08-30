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
#ifndef __INC_PHYDM_API_H_8735B__
#define __INC_PHYDM_API_H_8735B__

#if (RTL8735B_SUPPORT)

#define PHY_CONFIG_VERSION_8735B "1.1.1" 
/*#define CONFIG_TXAGC_DEBUG_8735B*/

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff
#define L_BND_DEFAULT_8735B 0xd
#define number_channel_interferecne 4

#define config_phydm_read_rf_check_8735b(data) ((data) != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8735b(data) ((data) != INVALID_TXAGC_DATA)

enum agc_tab_sel_8735b {
	OFDM_2G_BW40_8735b		= 0,
	OFDM_5G_LOW_BAND_8735b		= 1,
	OFDM_5G_MID_BAND_8735b		= 2,
	OFDM_5G_HIGH_BAND_8735b		= 3,
	OFDM_2G_BW20_8735b			= 4,
	CCK_BW20_40_8735b			= 5,
};

struct txagc_table_8735b {
	u8 ref_pow_cck[2];
	u8 ref_pow_ofdm[2];
	s8 diff_t[NUM_RATE_N_1SS]; /*by rate differential table*/
};

void phydm_init_hw_info_by_rfe_type_8735b(struct dm_struct *dm);

boolean phydm_chk_pkg_set_valid_8735b(struct dm_struct *dm,
				      u8 ver_bb, u8 ver_rf);

u32 config_phydm_read_rf_reg_8735b(struct dm_struct *dm, enum rf_path path,
				   u32 reg_addr, u32 bit_mask);

boolean config_phydm_write_rf_reg_8735b(struct dm_struct *dm,
					enum rf_path path, u32 reg_addr,
					u32 bit_mask, u32 data);

boolean phydm_write_txagc_1byte_8735b(struct dm_struct *dm, u32 pw_idx,
				      u8 hw_rate);

boolean config_phydm_write_txagc_ref_8735b(struct dm_struct *dm,
					   u8 power_index, enum rf_path path,
					   enum PDM_RATE_TYPE rate_type);

boolean config_phydm_write_txagc_diff_8735b(struct dm_struct *dm,
					    s8 power_index1, s8 power_index2,
					    s8 power_index3, s8 power_index4,
					    u8 hw_rate);

#ifdef CONFIG_TXAGC_DEBUG_8735B
void phydm_txagc_tab_buff_show_8735b(struct dm_struct *dm);
#endif

s8 config_phydm_read_txagc_diff_8735b(struct dm_struct *dm, u8 hw_rate);

u8 config_phydm_read_txagc_8735b(struct dm_struct *dm, enum rf_path path,
				 u8 hw_rate, enum PDM_RATE_TYPE rate_type);

void phydm_config_tx_path_8735b(struct dm_struct *dm,
				enum bb_path tx_path_en,
				enum bb_path tx_path_sel_1ss,
				enum bb_path tx_path_sel_cck);

boolean config_phydm_trx_mode_8735b(struct dm_struct *dm,
				    enum bb_path tx_path_en,
				    enum bb_path rx_path,
				    enum bb_path tx_path_sel_1ss);

boolean config_phydm_switch_band_8735b(struct dm_struct *dm, u8 central_ch);

boolean config_phydm_switch_channel_8735b(struct dm_struct *dm,
					  u8 central_ch);

boolean config_phydm_switch_bandwidth_8735b(struct dm_struct *dm, u8 pri_ch,
					    enum channel_width bw);

boolean config_phydm_switch_csimask_8735b(struct dm_struct *dm,
				u8 central_ch, enum channel_width bandwidth);

boolean config_phydm_switch_bbpowercut_8735b(struct dm_struct *dm,
				u8 central_ch, enum channel_width bandwidth);

boolean config_phydm_switch_channel_bw_8735b(struct dm_struct *dm,
					     u8 central_ch,
					     u8 primary_ch_idx,
					     enum channel_width bandwidth);

void phydm_i_only_setting_8735b(struct dm_struct *dm, boolean en_i_only,
				   boolean en_before_cca, u8 rf_ionly_mode);

void phydm_pmac_enable_8735b(struct dm_struct *dm, boolean en_pmac);

boolean config_phydm_parameter_init_8735b(struct dm_struct *dm,
					  enum odm_parameter_init type);
boolean phydm_chk_bb_state_idle_8735b(struct dm_struct *dm);

void phydm_bw80_enable_8735b(struct dm_struct *dm, boolean enable);

#if CONFIG_POWERSAVING
boolean phydm_8735b_lps(struct dm_struct *dm, boolean enable_lps);
#endif /* #if CONFIG_POWERSAVING */

void config_phydm_set_txagc_to_hw_8735b(struct dm_struct *dm);

boolean config_phydm_write_txagc_8735b(struct dm_struct *dm, u32 power_index,
				       enum rf_path path, u8 hw_rate);

void phydm_set_txagc_by_table_8735b(struct dm_struct *dm,
				    struct txagc_table_8735b *tab);

void phydm_get_txagc_ref_and_diff_8735b(struct dm_struct *dm,
					u8 txagc_buff[2][NUM_RATE_N_1SS],
					u16 length,
					struct txagc_table_8735b *tab);
#endif /* RTL8735B_SUPPORT */
#endif /*  __INC_PHYDM_API_H_8735B__ */
