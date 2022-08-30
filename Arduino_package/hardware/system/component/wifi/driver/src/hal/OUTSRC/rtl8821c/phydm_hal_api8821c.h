/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
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
#ifndef __INC_PHYDM_API_H_8821C__
#define __INC_PHYDM_API_H_8821C__

#if (RTL8821C_SUPPORT == 1)

#define	PHY_CONFIG_VERSION_8821C			"3.1.12"	/*2016.09.07     (HW user guide version: R03, SW user guide version: R01, Modification: R12)*/

#define	INVALID_RF_DATA					0xffffffff
#define	INVALID_TXAGC_DATA				0xff

#define	config_phydm_read_rf_check_8821c(data)			(data != INVALID_RF_DATA)
#define	config_phydm_read_txagc_check_8821c(data)		(data != INVALID_TXAGC_DATA)

enum rf_set_8821c {
	SWITCH_TO_BTG		= 0x0,
	SWITCH_TO_WLG		= 0x1,
	SWITCH_TO_WLA		= 0x2
};

u32
config_phydm_read_rf_reg_8821c(
	PDM_ODM_T p_dm_odm,
	ODM_RF_RADIO_PATH_E		rf_path,
	u32					reg_addr,
	u32					bit_mask
);

bool
config_phydm_write_rf_reg_8821c(
	PDM_ODM_T p_dm_odm,
	ODM_RF_RADIO_PATH_E		rf_path,
	u32					reg_addr,
	u32					bit_mask,
	u32					data
);

bool
config_phydm_write_txagc_8821c(
	PDM_ODM_T p_dm_odm,
	u32					power_index,
	ODM_RF_RADIO_PATH_E		path,
	u8					hw_rate
);

u8
config_phydm_read_txagc_8821c(
	PDM_ODM_T p_dm_odm,
	ODM_RF_RADIO_PATH_E		path,
	u8					hw_rate
);

bool
config_phydm_switch_band_8821c(
	PDM_ODM_T p_dm_odm,
	u8					central_ch
);

bool
config_phydm_switch_channel_8821c(
	PDM_ODM_T p_dm_odm,
	u8					central_ch
);

bool
config_phydm_switch_bandwidth_8821c(
	PDM_ODM_T p_dm_odm,
	u8					primary_ch_idx,
	ODM_BW_E				bandwidth
);

bool
config_phydm_switch_channel_bw_8821c(
	PDM_ODM_T p_dm_odm,
	u8					central_ch,
	u8					primary_ch_idx,
	ODM_BW_E				bandwidth
);

bool
config_phydm_trx_mode_8821c(
	PDM_ODM_T p_dm_odm,
	ODM_RF_PATH_E			tx_path,
	ODM_RF_PATH_E			rx_path,
	bool					is_tx2_path
);

bool
config_phydm_parameter_init_8821c(
	PDM_ODM_T p_dm_odm,
	enum odm_parameter_init_e	type
);

void
config_phydm_switch_rf_set_8821c(
	PDM_ODM_T p_dm_odm,
	u8				rf_set
);

/* ======================================================================== */
/* These following functions can be used for PHY DM only*/

bool
phydm_write_txagc_1byte_8821c(
	PDM_ODM_T p_dm_odm,
	u32					power_index,
	ODM_RF_RADIO_PATH_E		path,
	u8					hw_rate
);

void
phydm_init_hw_info_by_rfe_type_8821c(
	PDM_ODM_T p_dm_odm
);

/* ======================================================================== */

u32
query_phydm_trx_capability_8821c(
	PDM_ODM_T p_dm_odm
);

u32
query_phydm_stbc_capability_8821c(
	PDM_ODM_T p_dm_odm
);

u32
query_phydm_ldpc_capability_8821c(
	PDM_ODM_T p_dm_odm
);

u32
query_phydm_txbf_parameters_8821c(
	PDM_ODM_T p_dm_odm
);

u32
query_phydm_txbf_capability_8821c(
	PDM_ODM_T p_dm_odm
);

u8
query_phydm_default_rf_set_8821c(
	PDM_ODM_T p_dm_odm
);

u8
query_phydm_current_rf_set_8821c(
	PDM_ODM_T p_dm_odm
);

u8
query_phydm_rfetype_8821c(
	PDM_ODM_T p_dm_odm
);

#endif	/* RTL8821C_SUPPORT == 1 */
#endif	/*  __INC_PHYDM_API_H_8821C__ */
