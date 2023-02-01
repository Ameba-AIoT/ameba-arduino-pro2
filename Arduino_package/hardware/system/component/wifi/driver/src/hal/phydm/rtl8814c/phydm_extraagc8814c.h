/******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation.
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

#if (RTL8814C_SUPPORT == 1)
#ifndef __INC_PHYDM_EXTRA_AGC_8814C_H
#define __INC_PHYDM_EXTRA_AGC_8814C_H
#define AGC_TAB_8814C(cut, rfe, tabidx, band) \
	(array_8814c##cut##rfe##tabidx##band)

/* tc: Test Chip, mp: mp Chip*/
void
odm_config_mp_8814c_extra_agc_tab(struct dm_struct *dm, enum odm_rf_band band);
u32 odm_get_version_mp_8814c_extra_agc_tab(void);

#endif /* end of EXTRA_AGC_SUPPORT*/
#endif
