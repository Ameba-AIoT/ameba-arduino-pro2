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

/*Image2HeaderVersion: 2.22*/
#if (RTL8711B_SUPPORT == 1)
#ifndef __INC_MP_RF_HW_IMG_8711B_H
#define __INC_MP_RF_HW_IMG_8711B_H


/******************************************************************************
*                           RadioA.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8711B_RadioA(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8711B_RadioA(void);

/******************************************************************************
*                           TxPowerTrack_QFN32.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8711B_TxPowerTrack_QFN32(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8711B_TxPowerTrack_QFN32(void);


/******************************************************************************
*                           TxPowerTrack_QFN48.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8711B_TxPowerTrack_QFN48(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8711B_TxPowerTrack_QFN48(void);


/******************************************************************************
*                           TxPowerTrack_QFN68.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8711B_TxPowerTrack_QFN68(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8711B_TxPowerTrack_QFN68(void);

/******************************************************************************
*                           TXPWR_LMT.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8711B_TXPWR_LMT(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8711B_TXPWR_LMT(void);

/******************************************************************************
*                           TxXtalTrack.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8711B_TxXtalTrack(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8711B_TxXtalTrack(void);

#endif
#endif /* end of HWIMG_SUPPORT*/

