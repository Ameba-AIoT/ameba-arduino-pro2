/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __RTL8188E_DM_H__
#define __RTL8188E_DM_H__
enum {
	UP_LINK,
	DOWN_LINK,
};
//###### duplicate code,will move to ODM #########
#define IQK_MAC_REG_NUM		4
#define IQK_ADDA_REG_NUM		16
#define IQK_BB_REG_NUM			9
#define HP_THERMAL_NUM		8
//###### duplicate code,will move to ODM #########

void rtl8188e_init_dm_priv(IN _adapter *Adapter);
void rtl8188e_deinit_dm_priv(IN _adapter *Adapter);
void rtl8188e_InitHalDm(IN _adapter *Adapter);
void rtl8188e_HalDmWatchDog(IN _adapter *Adapter);
//void rtl8192c_dm_CheckTXPowerTracking(IN _adapter * Adapter);

//void rtl8192c_dm_RF_Saving(IN _adapter * pAdapter, IN u8 bForceInNormal);

#ifdef CONFIG_ANTENNA_DIVERSITY
void	AntDivCompare8188E(_adapter *Adapter, WLAN_BSSID_EX *dst, WLAN_BSSID_EX *src);
u8 AntDivBeforeLink8188E(_adapter *Adapter);
#endif
#endif

