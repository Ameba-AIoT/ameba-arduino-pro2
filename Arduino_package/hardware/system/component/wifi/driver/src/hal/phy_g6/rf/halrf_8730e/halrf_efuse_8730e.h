/******************************************************************************
 *
 * Copyright(c) 2007 - 2021  Realtek Corporation.
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
#ifndef _HALRF_EFUSE_8730E_H_
#define _HALRF_EFUSE_8730E_H_

#ifdef RF_8730E_SUPPORT

enum halrf_efsue_info_8730e_offset {
	EFUSE_INFO_RF_BOARD_OPTION_8730E_ADDR	= 0x131,
	EFUSE_INFO_RF_RFE_8730E_ADDR		= 0x13a,
	EFUSE_INFO_RF_CHAN_PLAN_8730E_ADDR	= 0xc8,
	EFUSE_INFO_RF_XTAL_8730E_ADDR		= 0xc9,
	EFUSE_INFO_RF_THERMAL_A_8730E_ADDR	= 0xca,
	EFUSE_INFO_RF_2G_CCK_A_TSSI_DE_1_8730E_ADDR	= 0x20,
	EFUSE_INFO_RF_2G_CCK_A_TSSI_DE_2_8730E_ADDR	= 0x21,
	EFUSE_INFO_RF_2G_CCK_A_TSSI_DE_3_8730E_ADDR	= 0x22,
	EFUSE_INFO_RF_2G_CCK_A_TSSI_DE_4_8730E_ADDR	= 0x23,
	EFUSE_INFO_RF_2G_CCK_A_TSSI_DE_5_8730E_ADDR	= 0x24,
	EFUSE_INFO_RF_2G_CCK_A_TSSI_DE_6_8730E_ADDR	= 0x25,
	EFUSE_INFO_RF_2G_BW20M_A_TSSI_DE_1_8730E_ADDR	= 0x26,
	EFUSE_INFO_RF_2G_BW20M_A_TSSI_DE_2_8730E_ADDR	= 0x27,
	EFUSE_INFO_RF_2G_BW20M_A_TSSI_DE_3_8730E_ADDR	= 0x28,
	EFUSE_INFO_RF_2G_BW20M_A_TSSI_DE_4_8730E_ADDR	= 0x29,
	EFUSE_INFO_RF_2G_BW20M_A_TSSI_DE_5_8730E_ADDR	= 0x2a,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_1_8730E_ADDR	= 0x32,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_2_8730E_ADDR	= 0x33,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_3_8730E_ADDR	= 0x34,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_4_8730E_ADDR	= 0x35,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_5_8730E_ADDR	= 0x36,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_6_8730E_ADDR	= 0x37,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_7_8730E_ADDR	= 0x38,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_8_8730E_ADDR	= 0x39,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_9_8730E_ADDR	= 0x3a,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_10_8730E_ADDR	= 0x3b,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_11_8730E_ADDR	= 0x3c,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_12_8730E_ADDR	= 0x3d,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_13_8730E_ADDR	= 0x3e,
	EFUSE_INFO_RF_5G_BW20M_A_TSSI_DE_14_8730E_ADDR	= 0x3f,
	EFUSE_INFO_RF_RX_GAIN_K_A_2G_CCK_8730E_ADDR	= 0x146,
	EFUSE_INFO_RF_RX_GAIN_K_A_2G_OFMD_8730E_ADDR	= 0x144,
	EFUSE_INFO_RF_RX_GAIN_K_A_5GL_8730E_ADDR	= 0x148,
	EFUSE_INFO_RF_RX_GAIN_K_A_5GM_8730E_ADDR	= 0x14a,
	EFUSE_INFO_RF_RX_GAIN_K_A_5GH_8730E_ADDR	= 0x14c
};

enum halrf_efsue_default_value_8730e {
	EFUSE_INFO_RF_RFE_8730E_VALUE		= 0x1,
	EFUSE_INFO_RF_CHAN_PLAN_8730E_VALUE	= 0x7f,
	EFUSE_INFO_RF_XTAL_8730E_VALUE		= 0x3f,
	EFUSE_INFO_RF_THERMAL_A_8730E_VALUE	= 0x22,
	EFUSE_INFO_RF_TSSI_DE_8730E_VALUE	= 0x0,
	EFUSE_INFO_RF_RX_GAIN_K_8730E_VALUE	= 0xf,
	EFUSE_INFO_RF_BOARD_OPTION_8730E_VALUE	= 0x1
};

bool halrf_get_efuse_info_8730e(struct rf_info *rf, u8 *efuse_map,
		       enum rtw_efuse_info id, void *value, u32 length,
		       u8 autoload_status);

#endif	/*RF_8730E_SUPPORT*/
#endif	/*_HALRF_EFUSE_8730E_H_*/

