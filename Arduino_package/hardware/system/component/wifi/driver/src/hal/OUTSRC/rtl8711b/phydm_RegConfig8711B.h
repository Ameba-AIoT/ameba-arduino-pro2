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
#ifndef __INC_ODM_REGCONFIG_H_8711B
#define __INC_ODM_REGCONFIG_H_8711B
 
#if (RTL8711B_SUPPORT == 1)

void
odm_ConfigRFReg_8711B(
	IN 	PDM_ODM_T 				pDM_Odm,
	IN 	u4Byte 					Addr,
	IN 	u4Byte 					Data,
	IN  ODM_RF_RADIO_PATH_E     RF_PATH,
	IN	u4Byte				    RegAddr
	);

void 
odm_ConfigRF_RadioA_8711B(
	IN 	PDM_ODM_T 				pDM_Odm,
	IN 	u4Byte 					Addr,
	IN 	u4Byte 					Data
	);

void 
odm_ConfigMAC_8711B(
 	IN 	PDM_ODM_T 	pDM_Odm,
 	IN 	u4Byte 		Addr,
 	IN 	u1Byte 		Data
 	);

void 
odm_ConfigBB_AGC_8711B(
    IN 	PDM_ODM_T 	pDM_Odm,
    IN 	u4Byte 		Addr,
    IN 	u4Byte 		Bitmask,
    IN 	u4Byte 		Data
    );

void
odm_ConfigBB_PHY_REG_PG_8711B(
	IN 	PDM_ODM_T 	pDM_Odm,
	IN	u4Byte		Band,
	IN	u4Byte		RfPath,
	IN	u4Byte		TxNum,
   	IN 	u4Byte 		Addr,
    IN 	u4Byte 		Bitmask,
    IN 	u4Byte 		Data
    );

void 
odm_ConfigBB_PHY_8711B(
	IN 	PDM_ODM_T 	pDM_Odm,
    IN 	u4Byte 		Addr,
    IN 	u4Byte 		Bitmask,
    IN 	u4Byte 		Data
    );

void
odm_ConfigBB_TXPWR_LMT_8711B(
	IN 	PDM_ODM_T 	pDM_Odm,
	IN	u1Byte		Regulation,
	IN	u1Byte		Band,
	IN	u1Byte		Bandwidth,
	IN	u1Byte		RateSection,
	IN	u1Byte		RfPath,
	IN	u1Byte		Channel,
	IN	u1Byte		PowerLimit
    );

#endif
#endif // end of SUPPORT

