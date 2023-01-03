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
 *****************************************************************************/
#if (RTL8197F_SUPPORT == 1)
#ifndef __ODM_RTL8197F_H__
#define __ODM_RTL8197F_H__

#ifdef DYN_ANT_WEIGHTING_SUPPORT
void phydm_dynamic_ant_weighting_8197f(
	void *dm_void);
#endif

s8 odm_cckrssi_8197f(
	struct dm_struct *dm,
	u8 lna_idx,
	u8 vga_idx);

void phydm_phypara_a_cut(
	struct dm_struct *dm);

void phydm_hwsetting_8197f(
	struct dm_struct *dm);

#endif /* #define __ODM_RTL8197F_H__ */
#endif
