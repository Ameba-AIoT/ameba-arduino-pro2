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

#if (RTL8188E_SUPPORT == 1)
#ifndef __INC_MAC_8188E_HW_IMG_H
#define __INC_MAC_8188E_HW_IMG_H

//static BOOLEAN CheckCondition(const u4Byte Condition, const u4Byte Hex);

/******************************************************************************
*                           MAC_REG.TXT
******************************************************************************/
#if (BE_I_CUT == 0)

HAL_STATUS
ODM_ReadAndConfig_MP_8188E_MAC_REG( // TC: Test Chip, MP: MP Chip
	IN   PDM_ODM_T  pDM_Odm
);

/******************************************************************************
*                           MAC_REG_ICUT.TXT
******************************************************************************/
#else

HAL_STATUS
ODM_ReadAndConfig_MP_8188E_MAC_REG_ICUT( // TC: Test Chip, MP: MP Chip
	IN   PDM_ODM_T  pDM_Odm
);
#endif // #if (BE_I_CUT == 0)

#endif
#endif // end of HWIMG_SUPPORT

