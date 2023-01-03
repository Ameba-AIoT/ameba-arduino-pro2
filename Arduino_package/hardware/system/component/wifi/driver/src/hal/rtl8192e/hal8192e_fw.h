/******************************************************************************
 *
 * Copyright(c) 2012 - 2017 Realtek Corporation.
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
#include "../../../include/drv_types.h"

#ifndef CONFIG_RTL8192E
#define CONFIG_RTL8192E
#endif

#ifdef CONFIG_RTL8192E

#ifndef _FW_HEADER_8192E_H
#define _FW_HEADER_8192E_H

#if (defined(CONFIG_AP_WOWLAN) || (DM_ODM_SUPPORT_TYPE & (ODM_AP)))
extern u8 array_mp_8192e_fw_ap[24666];
extern u32 array_length_mp_8192e_fw_ap;
#endif

#if (DM_ODM_SUPPORT_TYPE & (ODM_WIN)) || (DM_ODM_SUPPORT_TYPE & (ODM_CE))
extern const u8 array_mp_8192e_fw_nic[32180];
extern const u32 array_length_mp_8192e_fw_nic;
extern const u8 array_mp_8192e_fw_wowlan[28136];
extern const u32 array_length_mp_8192e_fw_wowlan;
#endif

#endif

#endif

