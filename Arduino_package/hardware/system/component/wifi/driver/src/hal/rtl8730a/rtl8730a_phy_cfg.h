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
#ifndef __INC_HAL8730APHYCFG_H__
#define __INC_HAL8730APHYCFG_H__

/*--------------------------Define Parameters-------------------------------*/
#define LOOP_LIMIT				5
#define MAX_STALL_TIME			50		//us
#define AntennaDiversityValue	0x80	//(Adapter->bSoftwareAntennaDiversity ? 0x00:0x80)
#define MAX_TXPWR_IDX_NMODE_92S	63
#define Reset_Cnt_Limit			3

#define		bMaskByte0                	0xff
#define		bMaskByte1                	0xff00
#define		bMaskByte2                	0xff0000
#define		bMaskByte3                	0xff000000
#define		bMaskHWord                	0xffff0000
#define		bMaskLWord                	0x0000ffff
#define		bMaskDWord                	0xffffffff
#define		bMask12Bits					0xfff
#define		bMaskH4Bits					0xf0000000

#define		bEnable						0x1
#define		bDisable					0x0

/*--------------------------Define Parameters End-------------------------------*/


/*------------------------------Define structure----------------------------*/

/* BB/RF related */

/*------------------------------Define structure End----------------------------*/

/*--------------------------Exported Function prototype---------------------*/
u32 rtl8730a_read_bb_reg(
	IN PADAPTER         Adapter,
	IN u32              RegAddr,
	IN u32              BitMask
);

VOID rtl8730a_write_bb_reg(
	IN PADAPTER         Adapter,
	IN u32              RegAddr,
	IN u32              BitMask,
	IN u32              Data
);
u32 rtl8730a_read_rf_reg(
	IN	PADAPTER			Adapter,
	IN	u32				eRFPath,
	IN	u32				RegAddr,
	IN	u32				BitMask
);

VOID rtl8730a_write_rf_reg(
	IN	PADAPTER			Adapter,
	IN	u32				eRFPath,
	IN	u32				RegAddr,
	IN	u32				BitMask,
	IN	u32				Data
);

#define PHY_QueryBBReg(Adapter, RegAddr, BitMask) rtl8730a_read_bb_reg((Adapter), (RegAddr), (BitMask))
#define PHY_SetBBReg(Adapter, RegAddr, BitMask, Data) rtl8730a_write_bb_reg((Adapter), (RegAddr), (BitMask), (Data))
#define PHY_QueryRFReg(Adapter, eRFPath, RegAddr, BitMask) rtl8730a_read_rf_reg((Adapter), (eRFPath), (RegAddr), (BitMask))
#define PHY_SetRFReg(Adapter, eRFPath, RegAddr, BitMask, Data) rtl8730a_write_rf_reg((Adapter), (eRFPath), (RegAddr), (BitMask), (Data))

#define PHY_SetMacReg	PHY_SetBBReg
#define PHY_QueryMacReg PHY_QueryBBReg
/* MAC/BB/RF HAL config */
u8 rtl8730a_phy_init(PADAPTER adapter);
s32 PHY_MACConfig8730A(PADAPTER padapter);

u8
PHY_GetTxPowerIndex_8730A(
	IN	PADAPTER			pAdapter,
	IN	u8					RFPath,
	IN	u8					Rate,
	IN	enum channel_width		BandWidth,
	IN	u8					Channel
);

VOID
PHY_SetTxPowerLevel8730A(
	IN	PADAPTER		Adapter,
	IN	u8			channel
);

VOID
PHY_SetBWMode8730A(
	IN	PADAPTER				Adapter,
	IN	enum channel_width			Bandwidth,	// 20M or 40M
	IN	unsigned char				Offset		// Upper, Lower, or Don't care
);

VOID
PHY_SwChnl8730A( // Call after initialization
	IN	PADAPTER	Adapter,
	IN	u8		channel
);

VOID
PHY_SetSwChnlBWMode8730A(
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
void rtl8730a_set_tx_power_level(PADAPTER adapter, u8 channel);
void rtl8730a_get_tx_power_level(PADAPTER adapter, s32 *power);
void rtl8730a_set_channel_bw(PADAPTER adapter, u8 center_ch, enum channel_width bw, u8 offset40, u8 offset80);
void rtl8730a_set_channel(PADAPTER adapter, u8 center_ch);

/*--------------------------Exported Function prototype End---------------------*/

#endif

