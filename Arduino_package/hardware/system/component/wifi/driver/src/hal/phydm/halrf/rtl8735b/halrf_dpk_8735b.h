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

#ifndef __HALRF_DPK_8735B_H__
#define __HALRF_DPK_8735B_H__

#if (RTL8735B_SUPPORT == 1)
/*--------------------------Define Parameters-------------------------------*/
#define DPK_RF_PATH_NUM_8735B 1
#define DPK_BB_REG_NUM_8735B 10
#define DPK_RF_REG_NUM_8735B 9
#define DPK_PAS_CHK_DBG_8735B 0
#define DPK_REG_DBG_8735B 0
#define DPK_PAS_DBG_8735B 0
#define DPK_SRAM_LUT_DBG_8735B 0
#define DPK_SRAM_read_DBG_8735B 0
#define DPK_PATH_A_8735B_EN 1


/*---------------------------End Define Parameters----------------------------*/

void dpk_enable_disable_8735b(void *dm_void);

void dpk_reload_8735b(void *dm_void);

void do_dpk_8735b(void *dm_void);

void dpk_track_8735b(void *dm_void);

#endif /* RTL8735B_SUPPORT */

#endif /*#ifndef __HALRF_DPK_8735B_H__*/
