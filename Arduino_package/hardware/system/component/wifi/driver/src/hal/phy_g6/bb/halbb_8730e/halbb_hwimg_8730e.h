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

#ifndef _HALBB_HW_IMG_8730E_H_
#define _HALBB_HW_IMG_8730E_H_



/******************************************************************************
 *                           phy_reg.TXT
 ******************************************************************************/
#define DONT_CARE_8730E	0xff

#define IF_8730E	0x8
#define ELSE_IF_8730E	0x9
#define ELSE_8730E	0xa
#define END_8730E	0xb
#define CHK_8730E	0x4

bool halbb_cfg_bbcr_ax_8730e(struct bb_info *bb, bool is_form_folder,
							 u32 folder_len, u32 *folder_array,
							 enum phl_phy_idx phy_idx);
bool halbb_cfg_bb_gain_ax_8730e(struct bb_info *bb, bool is_form_folder,
								u32 folder_len, u32 *folder_array);
u32 halbb_get_8730e_phy_reg_ver(void);

#endif /* end of HWIMG_SUPPORT*/

