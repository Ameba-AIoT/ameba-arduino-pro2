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
#ifndef __HALRF_DPK_8720EH__
#define __HALRF_DPK_8720EH__
#ifdef RF_8720E_SUPPORT
/*--------------------------Define Parameters-------------------------------*/
#define DPK_VER_8720E 0x2
#define DPK_RF_PATH_MAX_8720E 1
#define DPK_KIP_REG_NUM_8720E 4
#define DPK_BB_REG_NUM_8720E 6
#define DPK_RF_REG_NUM_8720E 5
#define DPK_RELOAD_EN_8720E 0
#define DPK_REG_DBG 0
#define DPK_NCTL_RXAGC_8720E 0x15
#define DPK_NCTL_TXAGC_8720E 0x16
#define DPK_NCTL_LMS_8720E 0x12

/*---------------------------End Define Parameters----------------------------*/

void halrf_dpk_8720e(struct rf_info *rf, enum phl_phy_idx phy_idx, bool force);

void halrf_dpk_onoff_8720e(struct rf_info *rf, enum rf_path path, bool off);

void halrf_dpk_track_8720e(struct rf_info *rf);

#endif
#endif /*  __HALRF_DPK_8720EH__ */
