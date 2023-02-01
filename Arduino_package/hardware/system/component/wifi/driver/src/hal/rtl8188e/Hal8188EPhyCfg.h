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
#ifndef __INC_HAL8188EPHYCFG_H__
#define __INC_HAL8188EPHYCFG_H__


/*--------------------------Define Parameters-------------------------------*/
#define LOOP_LIMIT				5
#define MAX_STALL_TIME			50		//us
#define AntennaDiversityValue	0x80	//(Adapter->bSoftwareAntennaDiversity ? 0x00:0x80)
#define MAX_TXPWR_IDX_NMODE_92S	63
#define Reset_Cnt_Limit			3

#define IQK_MAC_REG_NUM		4
#define IQK_ADDA_REG_NUM		16
#define IQK_BB_REG_NUM			9
#define HP_THERMAL_NUM		8

#ifdef CONFIG_PCI_HCI
#define MAX_AGGR_NUM	0x0B
#else
#define MAX_AGGR_NUM	0x07
#endif // CONFIG_PCI_HCI


/*--------------------------Define Parameters-------------------------------*/


/*------------------------------Define structure----------------------------*/
typedef enum _SwChnlCmdID {
	CmdID_End,
	CmdID_SetTxPowerLevel,
	CmdID_BBRegWrite10,
	CmdID_WritePortUlong,
	CmdID_WritePortUshort,
	CmdID_WritePortUchar,
	CmdID_RF_WriteReg,
} SwChnlCmdID;


/* 1. Switch channel related */
typedef struct _SwChnlCmd {
	SwChnlCmdID	CmdID;
	u32			Para1;
	u32			Para2;
	u32			msDelay;
} SwChnlCmd;

typedef enum _HW90_BLOCK {
	HW90_BLOCK_MAC = 0,
	HW90_BLOCK_PHY0 = 1,
	HW90_BLOCK_PHY1 = 2,
	HW90_BLOCK_RF = 3,
	HW90_BLOCK_MAXIMUM = 4, // Never use this
} HW90_BLOCK_E, *PHW90_BLOCK_E;

#define MAX_CHNL_GROUP_24G		6	// ch1~2, ch3~5, ch6~8,ch9~11,ch12~13,CH 14 total three groups
#define CHANNEL_GROUP_MAX_88E    	6

typedef enum _PHY_Rate_Tx_Power_Offset_Area {
	RA_OFFSET_LEGACY_OFDM1,
	RA_OFFSET_LEGACY_OFDM2,
	RA_OFFSET_HT_OFDM1,
	RA_OFFSET_HT_OFDM2,
	RA_OFFSET_HT_OFDM3,
	RA_OFFSET_HT_OFDM4,
	RA_OFFSET_HT_CCK,
} RA_OFFSET_AREA, *PRA_OFFSET_AREA;


/* BB/RF related */

/*------------------------------Define structure----------------------------*/


/*------------------------Export global variable----------------------------*/
/*------------------------Export global variable----------------------------*/


/*------------------------Export Marco Definition---------------------------*/
/*------------------------Export Marco Definition---------------------------*/


/*--------------------------Exported Function prototype---------------------*/
//
// BB and RF register read/write
//
u32	rtl8188e_PHY_QueryBBReg(IN	_adapter 	*Adapter,
							IN	u32		RegAddr,
							IN	u32		BitMask);
void	rtl8188e_PHY_SetBBReg(IN	_adapter 	*Adapter,
							  IN	u32		RegAddr,
							  IN	u32		BitMask,
							  IN	u32		Data);
u32	rtl8188e_PHY_QueryRFReg(IN	_adapter 			*Adapter,
							IN	u32				RFPath,
							IN	u32				RegAddr,
							IN	u32				BitMask);
void	rtl8188e_PHY_SetRFReg(IN	_adapter 			*Adapter,
							  IN	u32				RFPath,
							  IN	u32				RegAddr,
							  IN	u32				BitMask,
							  IN	u32				Data);

//
// Initialization related function
//
/* MAC/BB/RF HAL config */
int	PHY_MACConfig8188E(IN	_adapter 	*Adapter);
int	PHY_BBConfig8188E(IN	_adapter 	*Adapter);
int	PHY_RFConfig8188E(IN	_adapter 	*Adapter);

//
// RF Power setting
//
//extern	BOOLEAN	PHY_SetRFPowerState(IN	_adapter *			Adapter,
//									IN	RT_RF_POWER_STATE	eRFPowerState);

//
// BB TX Power R/W
//
void	PHY_SetTxPowerLevel8188E(IN	_adapter 		*Adapter,
								 IN	u8			channel);
//
// Switch bandwidth for 8192S
//
//extern	void	PHY_SetBWModeCallback8192C(	IN	PRT_TIMER		pTimer	);
void	PHY_SetBWMode8188E(IN	_adapter 			*pAdapter,
						   IN	enum channel_width	ChnlWidth,
						   IN	unsigned char	Offset);

//
// Set FW CMD IO for 8192S.
//
//extern	BOOLEAN HalSetIO8192C(	IN	_adapter *			Adapter,
//									IN	IO_TYPE				IOType);

//
// Set A2 entry to fw for 8192S
//
extern	void FillA2Entry8192C(IN	_adapter 			*Adapter,
							  IN	u8				index,
							  IN	u8				*val);


//
// channel switch related funciton
//
//extern	void	PHY_SwChnlCallback8192C(	IN	PRT_TIMER		pTimer	);
void	PHY_SwChnl8188E(IN	_adapter 		*pAdapter,
						IN	u8			channel);

void ChkFwCmdIoDone(IN	_adapter 	*Adapter);

//
// BB/MAC/RF other monitor API
//
void PHY_SetRFPathSwitch_8188E(IN	_adapter 	*pAdapter, IN	BOOLEAN		bMain);

extern	void
PHY_SwitchEphyParameter(
	IN	_adapter 			*Adapter
);

extern	void
PHY_EnableHostClkReq(
	IN	_adapter 			*Adapter
);

BOOLEAN
SetAntennaConfig92C(
	IN	_adapter 	*Adapter,
	IN	u8		DefaultAnt
);

VOID
PHY_SetTxPowerIndex_8188E(
	IN	PADAPTER			Adapter,
	IN	u32 				PowerIndex,
	IN	u8					RFPath,
	IN	u8					Rate
);

u8
PHY_GetTxPowerIndex_8188E(
	IN	PADAPTER			pAdapter,
	IN	u8					RFPath,
	IN	u8					Rate,
	IN	enum channel_width		BandWidth,
	IN	u8					Channel
);

VOID
PHY_SetSwChnlBWMode8188E(
	IN	PADAPTER			Adapter,
	IN	u8					channel,
	IN	enum channel_width		Bandwidth,
	IN	u8					Offset40,
	IN	u8					Offset80
);


/*--------------------------Exported Function prototype---------------------*/

#define PHY_QueryBBReg(Adapter, RegAddr, BitMask) rtl8188e_PHY_QueryBBReg((Adapter), (RegAddr), (BitMask))
#define PHY_SetBBReg(Adapter, RegAddr, BitMask, Data) rtl8188e_PHY_SetBBReg((Adapter), (RegAddr), (BitMask), (Data))
#define PHY_QueryRFReg(Adapter, eRFPath, RegAddr, BitMask) rtl8188e_PHY_QueryRFReg((Adapter), (eRFPath), (RegAddr), (BitMask))
#define PHY_SetRFReg(Adapter, eRFPath, RegAddr, BitMask, Data) rtl8188e_PHY_SetRFReg((Adapter), (eRFPath), (RegAddr), (BitMask), (Data))

#define PHY_SetMacReg	PHY_SetBBReg


//
// Initialization related function
//
/* MAC/BB/RF HAL config */
//extern s32 PHY_MACConfig8723(_adapter * padapter);
//s32 PHY_BBConfig8723(_adapter * padapter);
//s32 PHY_RFConfig8723(_adapter * padapter);



//==================================================================
#define	SIC_ENABLE				0
#define	SIC_HW_SUPPORT		0
//==================================================================


#define	SIC_MAX_POLL_CNT		5

#if(SIC_HW_SUPPORT == 1)
#define	SIC_CMD_READY			0
#define	SIC_CMD_PREWRITE		0x1
#define	SIC_CMD_WRITE			0x40
#define	SIC_CMD_PREREAD		0x2
#define	SIC_CMD_READ			0x80
#define	SIC_CMD_INIT			0xf0
#define	SIC_INIT_VAL			0xff

#define	SIC_INIT_REG			0x1b7
#define	SIC_CMD_REG			0x1EB		// 1byte
#define	SIC_ADDR_REG			0x1E8		// 1b4~1b5, 2 bytes
#define	SIC_DATA_REG			0x1EC		// 1b0~1b3
#else
#define	SIC_CMD_READY			0
#define	SIC_CMD_WRITE			1
#define	SIC_CMD_READ			2

#define	SIC_CMD_REG			0x1EB		// 1byte
#define	SIC_ADDR_REG			0x1E8		// 1b9~1ba, 2 bytes
#define	SIC_DATA_REG			0x1EC		// 1bc~1bf
#endif

#if(SIC_ENABLE == 1)
void SIC_Init(IN _adapter *Adapter);
#endif


#endif	// __INC_HAL8192CPHYCFG_H

