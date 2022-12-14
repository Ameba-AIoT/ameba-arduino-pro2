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
#ifndef _HALRF_PSD_TSSI_8730A_H_
#define _HALRF_PSD_TSSI_8730A_H_

#ifdef RF_8730A_SUPPORT

#define PSD_VER_8730A 0x1
#define PSD_BACKUP_NUM_8730A 41

/*@--------------------------Define Parameters-------------------------------*/
/*@-----------------------End Define Parameters-----------------------*/

void halrf_psd_init_8730a(struct rf_info *rf, enum phl_phy_idx phy,
						  u8 path, u8 iq_path, u32 avg, u32 fft);

void halrf_psd_restore_8730a(struct rf_info *rf, enum phl_phy_idx phy);

u32 halrf_psd_get_point_data_8730a(struct rf_info *rf,
								   enum phl_phy_idx phy, s32 point);

void halrf_psd_query_8730a(struct rf_info *rf, enum phl_phy_idx phy,
						   u32 point, u32 start_point, u32 stop_point, u32 *outbuf);

#endif	/*RF_8730A_SUPPORT*/
#endif	/*_HALRF_PSD_TSSI_8730A_H_*/

