/******************************************************************************
 *
 * Copyright(c) 2021 Realtek Corporation.
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
#ifndef _HALRF_KFREE_8720E_H_
#define _HALRF_KFREE_8720E_H_
#ifdef RF_8720E_SUPPORT

/*@--------------------------Define Parameters-------------------------------*/

#define HIDE_EFUSE_START_ADDR_8720E	 0x7B0
#define HIDE_EFUSE_END_ADDR_8720E	 0x7CF
#define HIDE_EFUSE_SIZE_8720E		 HIDE_EFUSE_END_ADDR_8720E - HIDE_EFUSE_START_ADDR_8720E + 1

#define THERMAL_TRIM_HIDE_EFUSE_A_8720E 0x7B0

#define PABIAS_TRIM_HIDE_EFUSE_A_8720E 0x7B1

#define TSSI_TRIM_HIDE_EFUSE_2GL_A_8720E 0x7B5
#define TSSI_TRIM_HIDE_EFUSE_2GH_A_8720E 0x7B6
#define TSSI_TRIM_HIDE_EFUSE_5GL1_A_8720E 0x7B7
#define TSSI_TRIM_HIDE_EFUSE_5GL2_A_8720E 0x7B8
#define TSSI_TRIM_HIDE_EFUSE_5GM1_A_8720E 0x7B9
#define TSSI_TRIM_HIDE_EFUSE_5GM2_A_8720E 0x7BA
#define TSSI_TRIM_HIDE_EFUSE_5GH1_A_8720E 0x7BB
#define TSSI_TRIM_HIDE_EFUSE_5GH2_A_8720E 0x7BC


/*@-----------------------End Define Parameters-----------------------*/

void halrf_get_efuse_trim_8720e(struct rf_info *rf,
					enum phl_phy_idx phy);

#endif
#endif	/*_HALRF_SET_PWR_TABLE_8720E_H_*/
