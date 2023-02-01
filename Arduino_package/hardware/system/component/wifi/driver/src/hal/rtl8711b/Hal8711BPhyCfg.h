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
#ifndef __INC_HAL8711BPHYCFG_H__
#define __INC_HAL8711BPHYCFG_H__

/*--------------------------Define Parameters-------------------------------*/
#define LOOP_LIMIT				5
#define MAX_STALL_TIME			50		//us
#define AntennaDiversityValue	0x80	//(Adapter->bSoftwareAntennaDiversity ? 0x00:0x80)
#define MAX_TXPWR_IDX_NMODE_92S	63
#define Reset_Cnt_Limit			3

#if defined (CONFIG_PCI_HCI) || defined(CONFIG_LX_HCI)
#define MAX_AGGR_NUM	0x0B
#else
#define MAX_AGGR_NUM	0x07
#endif // CONFIG_PCI_HCI


/*--------------------------Define Parameters End-------------------------------*/


/*------------------------------Define structure----------------------------*/

/* BB/RF related */

/*------------------------------Define structure End----------------------------*/

/*--------------------------Exported Function prototype---------------------*/

u32
PHY_QueryBBReg_8711B(
	IN	PADAPTER	Adapter,
	IN	u32		RegAddr,
	IN	u32		BitMask
);

VOID
PHY_SetBBReg_8711B(
	IN	PADAPTER	Adapter,
	IN	u32		RegAddr,
	IN	u32		BitMask,
	IN	u32		Data
);

u32
PHY_QueryRFReg_8711B(
	IN	PADAPTER			Adapter,
	IN	u32				eRFPath,
	IN	u32				RegAddr,
	IN	u32				BitMask
);

VOID
PHY_SetRFReg_8711B(
	IN	PADAPTER			Adapter,
	IN	u32				eRFPath,
	IN	u32				RegAddr,
	IN	u32				BitMask,
	IN	u32				Data
);

u32 PHY_QueryBBReg_8711B_Safe(
	IN PADAPTER         Adapter,
	IN u32              RegAddr,
	IN u32              BitMask
);

VOID PHY_SetBBReg_8711B_Safe(
	IN PADAPTER         Adapter,
	IN u32              RegAddr,
	IN u32              BitMask,
	IN u32              Data
);

#define PHY_QueryBBReg(Adapter, RegAddr, BitMask) PHY_QueryBBReg_8711B_Safe((Adapter), (RegAddr), (BitMask))
#define PHY_SetBBReg(Adapter, RegAddr, BitMask, Data) PHY_SetBBReg_8711B_Safe((Adapter), (RegAddr), (BitMask), (Data))
#define PHY_QueryRFReg(Adapter, eRFPath, RegAddr, BitMask) PHY_QueryRFReg_8711B((Adapter), (eRFPath), (RegAddr), (BitMask))
#define PHY_SetRFReg(Adapter, eRFPath, RegAddr, BitMask, Data) PHY_SetRFReg_8711B((Adapter), (eRFPath), (RegAddr), (BitMask), (Data))

#define PHY_SetMacReg	PHY_SetBBReg
#define PHY_QueryMacReg PHY_QueryBBReg
/* MAC/BB/RF HAL config */
int PHY_BBConfig8711B(PADAPTER	Adapter);

int PHY_RFConfig8711B(PADAPTER	Adapter);

s32 PHY_MACConfig8711B(PADAPTER padapter);

#ifdef CONFIG_SUDO_PHY_SETTING
int PHY_SudoPhyConfig8711B(PADAPTER Adapter);
#endif

int
PHY_ConfigRFWithParaFile_8711B(
	IN	PADAPTER			Adapter,
	IN	u8 				*pFileName,
	enum rf_path				eRFPath
);
int
PHY_ConfigRFWithHeaderFile_8723B(
	IN	PADAPTER			Adapter,
	enum rf_path				eRFPath
);

u8
PHY_GetTxPowerIndex_8711B(
	IN	PADAPTER			pAdapter,
	IN	u8					RFPath,
	IN	u8					Rate,
	IN	enum channel_width		BandWidth,
	IN	u8					Channel
);

VOID
PHY_SetTxPowerLevel8711B(
	IN	PADAPTER		Adapter,
	IN	u8			channel
);

VOID
PHY_SetBWMode8711B(
	IN	PADAPTER				Adapter,
	IN	enum channel_width			Bandwidth,	// 20M or 40M
	IN	unsigned char				Offset		// Upper, Lower, or Don't care
);

VOID
PHY_SwChnl8711B( // Call after initialization
	IN	PADAPTER	Adapter,
	IN	u8		channel
);

VOID
PHY_SetSwChnlBWMode8711B(
	IN	PADAPTER			Adapter,
	IN	u8					channel,
	IN	enum channel_width		Bandwidth,
	IN	u8					Offset40,
	IN	u8					Offset80
);

VOID PHY_SetRFPathSwitch_8723B(
	IN	PADAPTER	pAdapter,
	IN	BOOLEAN		bMain
);

/*--------------------------Exported Function prototype End---------------------*/

#endif

