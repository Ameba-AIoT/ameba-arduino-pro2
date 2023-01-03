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
#ifndef __INC_PHYDM_API_H_8198F__
#define __INC_PHYDM_API_H_8198F__

#if (RTL8198F_SUPPORT == 1)

#define PHY_CONFIG_VERSION_8198F "0.0.0" /*2017.11.27*/

#define SMTANT_TMP_RFE_TYPE 100

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff

#define NUM_PATH 4
#define NUM_TRY_PSD_8198F 32

#define PSD_VAL_NUM 5
#define PSD_SMP_NUM 3
#define FREQ_PT_2G_NUM 14
#define FREQ_PT_5G_NUM 10

#define number_channel_interferecne 4

#define config_phydm_read_rf_check_8198f(data) (data != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8198f(data) (data != INVALID_TXAGC_DATA)

boolean phydm_chk_pkg_set_valid_8198f(struct dm_struct *dm,
				      u8 ver_bb, u8 ver_rf);

void phydm_rfe_8198f_init(
	struct dm_struct *dm);

boolean
phydm_rfe_8198f(
	struct dm_struct *dm,
	u8 channel);

u32 config_phydm_read_rf_reg_8198f(
	struct dm_struct *dm,
	enum rf_path path,
	u32 reg_addr,
	u32 bit_mask);

boolean
config_phydm_write_rf_reg_8198f(
	struct dm_struct *dm,
	enum rf_path path,
	u32 reg_addr,
	u32 bit_mask,
	u32 data);
boolean
phydm_write_txagc_1byte_8198f(struct dm_struct *dm, u32 pw_idx, u8 hw_rate);
boolean
config_phydm_write_txagc_ref_8198f(
	struct dm_struct *dm,
	u32 power_index,
	enum rf_path path,
	enum PDM_RATE_TYPE rate_type);

boolean
config_phydm_write_txagc_diff_8198f(struct dm_struct *dm, u32 power_index,
				    u8 hw_rate);

s8 config_phydm_read_txagc_diff_8198f(struct dm_struct *dm, u8 hw_rate);

u8 config_phydm_read_txagc_8198f(
	struct dm_struct *dm,
	enum rf_path path,
	u8 hw_rate,
	enum PDM_RATE_TYPE rate_type);

void phydm_dynamic_spur_det_eliminate_8198f(
	struct dm_struct *dm);

boolean
config_phydm_switch_channel_8198f(
	struct dm_struct *dm,
	u8 central_ch);

boolean
config_phydm_switch_bandwidth_8198f(
	struct dm_struct *dm,
	u8 primary_ch_idx,
	enum channel_width bandwidth);

boolean
config_phydm_switch_channel_bw_8198f(
	struct dm_struct *dm,
	u8 central_ch,
	u8 primary_ch_idx,
	enum channel_width bandwidth);

boolean
config_phydm_trx_mode_8198f(
	struct dm_struct *dm,
	enum bb_path tx_path,
	enum bb_path rx_path,
	boolean is_tx2_path);

boolean
config_phydm_parameter_init_8198f(
	struct dm_struct *dm,
	enum odm_parameter_init type);

/* ======================================================================== */
/* These following functions can be used for PHY DM only*/

void phydm_init_hw_info_by_rfe_type_8198f(
	struct dm_struct *dm);

s32 phydm_get_condition_number_8198F(
	struct dm_struct *dm);

/* ======================================================================== */

#endif /* RTL8198F_SUPPORT == 1 */
#endif /*  __INC_PHYDM_API_H_8198F__ */
