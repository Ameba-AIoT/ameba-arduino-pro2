/******************************************************************************
 *
 * Copyright(c) 2016 - 2017 Realtek Corporation.
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
 *****************************************************************************/
#ifndef __INC_PHYDM_API_H_8195B__
#define __INC_PHYDM_API_H_8195B__

#if (RTL8195B_SUPPORT == 1)

#define PHY_CONFIG_VERSION_8195B "0.0.0" /*2017.12.01     (HW user guide version: R01, SW user guide version: R01, Modification: R01)*/

#define INVALID_RF_DATA 0xffffffff
#define INVALID_TXAGC_DATA 0xff

#define config_phydm_read_rf_check_8195b(data) (data != INVALID_RF_DATA)
#define config_phydm_read_txagc_check_8195b(data) (data != INVALID_TXAGC_DATA)

enum rf_set_8195b {
	SWITCH_TO_WLG_95B = 0x1,
	SWITCH_TO_WLA_95B = 0x2,
};

#if 0
enum ant_num_8195b {
	SWITCH_TO_ANT1	= 0x0,
	SWITCH_TO_ANT2	= 0x1
};

enum ant_num_map_8195b {
	BOTH_AVAILABLE		= 0x1,
	ONLY_ANT1				= 0x2,
	ONLY_ANT2				= 0x3,
	DONT_CARE				= 0x4
};
#endif

s8 phydm_cck_rssi_8195B(struct dm_struct *dm, u8 lna_idx, u8 vga_idx);

u32 config_phydm_read_rf_reg_8195b(
	struct dm_struct *dm,
	enum rf_path path,
	u32 reg_addr,
	u32 bit_mask);

boolean
config_phydm_write_rf_reg_8195b(
	struct dm_struct *dm,
	enum rf_path path,
	u32 reg_addr,
	u32 bit_mask,
	u32 data);

boolean
config_phydm_write_txagc_8195b(
	struct dm_struct *dm,
	u32 power_index,
	enum rf_path path,
	u8 hw_rate);

u8 config_phydm_read_txagc_8195b(
	struct dm_struct *dm,
	enum rf_path path,
	u8 hw_rate);

boolean
config_phydm_switch_band_8195b(
	struct dm_struct *dm,
	u8 central_ch);

boolean
config_phydm_switch_channel_8195b(
	struct dm_struct *dm,
	u8 central_ch);

boolean
config_phydm_switch_bandwidth_8195b(
	struct dm_struct *dm,
	u8 primary_ch_idx,
	enum channel_width bandwidth);

boolean
config_phydm_switch_csimask_8195b(struct dm_struct *dm,
				  u8 central_ch, enum channel_width bandwidth);

boolean
config_phydm_switch_bbpowercut_8195b(struct dm_struct *dm, u8 central_ch,
				     enum channel_width bandwidth);

boolean
config_phydm_switch_channel_bw_8195b(
	struct dm_struct *dm,
	u8 central_ch,
	u8 primary_ch_idx,
	enum channel_width bandwidth);

boolean
config_phydm_trx_mode_8195b(
	struct dm_struct *dm,
	enum bb_path tx_path,
	enum bb_path rx_path,
	boolean is_tx2_path);

boolean
config_phydm_parameter_init_8195b(
	struct dm_struct *dm,
	enum odm_parameter_init type);

#if 0
void
config_phydm_switch_rf_set_8195b(
	struct dm_struct			*dm,
	u8				rf_set
);

void
config_phydm_set_ant_path(struct dm_struct *dm, u8 rf_set, u8 ant_num);
#endif

/* ======================================================================== */
/* These following functions can be used for PHY DM only*/

boolean
phydm_write_txagc_1byte_8195b(
	struct dm_struct *dm,
	u32 power_index,
	enum rf_path path,
	u8 hw_rate);

void phydm_init_hw_info_by_rfe_type_8195b(
	struct dm_struct *dm);

void phydm_bb_reset_8195b(
	struct dm_struct *dm);

void odm_set_rf_reg_8195b(
	struct dm_struct *dm, 
	u8 rf_path, 
	u32 reg_addr,
	u32 bit_mask,
	u32 data);

#if 0
void
phydm_set_gnt_state_8195b(
	struct dm_struct			*dm,
	boolean				gnt_wl_state,
	boolean				gnt_bt_state
);

/* ======================================================================== */
#endif

u32 query_phydm_trx_capability_8195b(
	struct dm_struct *dm);

u32 query_phydm_stbc_capability_8195b(
	struct dm_struct *dm);

u32 query_phydm_ldpc_capability_8195b(
	struct dm_struct *dm);

u32 query_phydm_txbf_parameters_8195b(
	struct dm_struct *dm);

u32 query_phydm_txbf_capability_8195b(
	struct dm_struct *dm);

#if 0
u8
query_phydm_default_rf_set_8195b(
	struct dm_struct				*dm
);

u8
query_phydm_current_rf_set_8195b(
	struct dm_struct				*dm
);

u8
query_phydm_rfetype_8195b(
	struct dm_struct				*dm
);

u8
query_phydm_current_ant_num_8195b(
	struct dm_struct				*dm
);

u8
query_phydm_ant_num_map_8195b(
	struct dm_struct				*dm
);
#endif

#endif /* RTL8195B_SUPPORT == 1 */
#endif /*  __INC_PHYDM_API_H_8195B__ */
