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

/*Image2HeaderVersion: 2.16*/
#if (RTL8821C_SUPPORT == 1)
#ifndef __INC_MP_FW_HW_IMG_8821C_H
#define __INC_MP_FW_HW_IMG_8821C_H


/******************************************************************************
*                           FW_AP.TXT
******************************************************************************/

void
ODM_ReadFirmware_MP_8821C_FW_AP(
	PDM_ODM_T p_dm_odm,
	u8       *p_firmware,
	u32       *p_firmware_size
);

/******************************************************************************
*                           FW_NIC.TXT
******************************************************************************/

void
ODM_ReadFirmware_MP_8821C_FW_NIC(
	PDM_ODM_T p_dm_odm,
	u8       *p_firmware,
	u32       *p_firmware_size
);

/******************************************************************************
*                           FW_WoWLAN.TXT
******************************************************************************/

void
ODM_ReadFirmware_MP_8821C_FW_WoWLAN(
	PDM_ODM_T p_dm_odm,
	u8       *p_firmware,
	u32       *p_firmware_size
);
#ifndef CONFIG_NO_FW
//extern const u8 array_mp_8821c_fw_nic[97576];
//extern u32 array_length_mp_8821c_fw_nic;
extern const u8 array_mp_8821c_fw_nic[114344];
extern u32 array_length_mp_8821c_fw_nic;
//extern const u8 array_mp_8821c_fw_wowlan[101880];
//extern u32 array_length_mp_8821c_fw_wowlan;
extern const u8 array_mp_8821c_fw_wowlan[92784];
extern u32 array_length_mp_8821c_fw_wowlan;

#endif
#endif
#endif /* end of HWIMG_SUPPORT*/
