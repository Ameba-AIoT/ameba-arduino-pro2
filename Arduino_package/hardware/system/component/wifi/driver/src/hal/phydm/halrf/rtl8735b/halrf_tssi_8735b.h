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

#ifndef __HALRF_TSSI_8735B_H__
#define __HALRF_TSSI_8735B_H__

#if (RTL8735B_SUPPORT == 1)

/*--------------------------Define Parameters-------------------------------*/

/*---------------------------End Define Parameters----------------------------*/

void halrf_tssi_set_de_for_tx_verify_8735b(void *dm_void, u32 tssi_de, u8 path);

s32 halrf_get_online_tssi_de_8735b(void *dm_void, u8 path, s32 dbm, s32 pout);

void halrf_tssi_get_efuse_8735b(void *dm_void);

u32 halrf_tssi_set_de_8735b(void *dm_void, u32 tssi_de);

void halrf_enable_tssi_8735b(void *dm_void);

void halrf_disable_tssi_8735b(void *dm_void);

void halrf_do_tssi_8735b(void *dm_void);

void halrf_tssi_set_efuse_de_8735b(void *dm_void);

void halrf_tssi_set_power_8735b(void *dm_void, u32 tx_rate, u32 power);

u32 halrf_tssi_get_power_8735b(void *dm_void, u32 tx_rate);

void halrf_pwr_table_info_8735b(void *dm_void, u32 *_used, char *output, u32 *_out_len);

void halrf_tssi_info_8735b(void *dm_void, u32 *_used, char *output, u32 *_out_len);

void halrf_tssi_backup_txagc_8735b(void *dm_void);

void halrf_tssi_reload_txagc_8735b(void *dm_void);

void halrf_tssi_renew_txagc_by_rate_table_8735b(void *dm_void);

#endif /* RTL8735B_SUPPORT */
#endif /*#ifndef __HALRF_TSSI_8735B_H__*/
