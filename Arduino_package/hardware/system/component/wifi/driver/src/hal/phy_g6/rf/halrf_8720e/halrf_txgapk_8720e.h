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

#ifndef __HALRF_TXGAPK_8720E_H__
#define __HALRF_TXGAPK_8720E_H__

#ifdef RF_8720E_SUPPORT

#define TXGAPK_VER_8720E 0x06

/*--------------------------Define Parameters-------------------------------*/
#define TXGAPK_RF_PATH_MAX_8720E 2

#define TXGAPK_RF_REG_NUM_8720E 1

#define TXGAPK_DEBUGMASK_8720E		0x100EE

#define TXGAP_TB_ADDR_8720E			0x10033
	
#define TXGAP_TB_VAL_8720E			0x1003F
/*---------------------------End Define Parameters----------------------------*/




void halrf_txgapk_enable_8720e
	(struct rf_info *rf, enum phl_phy_idx phy);

void halrf_txgapk_write_table_default_8720e
	(struct rf_info *rf, enum phl_phy_idx phy);

void halrf_do_txgapk_8720e(struct rf_info *rf, enum phl_phy_idx phy);


void halrf_txgapk_init_8720e(struct rf_info *rf);

#endif /* RF_8720E_SUPPORT */
#endif /*#ifndef __HALRF_TXGAPK_8720E_H__*/
