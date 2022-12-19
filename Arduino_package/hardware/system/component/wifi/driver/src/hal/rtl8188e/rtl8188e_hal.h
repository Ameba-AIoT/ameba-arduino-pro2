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
#ifndef __RTL8188E_HAL_H__
#define __RTL8188E_HAL_H__


//include HAL Related header after HAL Related compiling flags
#include "hal_data.h"
#include "rtl8188e_spec.h"
#include "Hal8188EPhyReg.h"
#include "Hal8188EPhyCfg.h"
#include "rtl8188e_rf.h"
#include "rtl8188e_dm.h"
#include "rtl8188e_recv.h"
#include "rtl8188e_xmit.h"
#include "rtl8188e_fwcmd.h"
#include "Hal8188EPwrSeq.h"
#include "rtl8188e_led.h"
#ifdef DBG_CONFIG_ERROR_DETECT
#include "rtl8188e_sreset.h"
#endif

#include "../OUTSRC/phydm_precomp.h"

// Fw Array
#define Rtl8188E_FwImageArray				Array_MP_8188E_FW_NIC_89EM
#define Rtl8188E_FWImgArrayLength			ArrayLength_MP_8188E_FW_NIC_89EM
#ifdef CONFIG_WOWLAN
#define Rtl8188E_FwWoWImageArray			Array_8188E_FW_WoWLAN
#define Rtl8188E_FwWoWImgArrayLength		ArrayLength_8188E_FW_WoWLAN
#endif //CONFIG_WOWLAN


#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)

//TODO: We should define 8188ES firmware related macro settings here!!
//TODO:  The following need to check!!
#define RTL8188E_FW_UMC_IMG				"rtl8188E\\rtl8188efw.bin"
#define RTL8188E_PHY_REG					"rtl8188E\\PHY_REG_1T.txt"
#define RTL8188E_PHY_RADIO_A				"rtl8188E\\radio_a_1T.txt"
#define RTL8188E_PHY_RADIO_B				"rtl8188E\\radio_b_1T.txt"
#define RTL8188E_AGC_TAB					"rtl8188E\\AGC_TAB_1T.txt"
#define RTL8188E_PHY_MACREG 				"rtl8188E\\MAC_REG.txt"
#define RTL8188E_PHY_REG_PG				"rtl8188E\\PHY_REG_PG.txt"
#define RTL8188E_PHY_REG_MP				"rtl8188E\\PHY_REG_MP.txt"

//---------------------------------------------------------------------
//		RTL8188E From header
//---------------------------------------------------------------------
#if 0
#define Rtl8188E_PHY_REG_Array_PG			Rtl8188ESPHY_REG_Array_PG
#define Rtl8188E_PHY_REG_Array_PGLength	Rtl8188ESPHY_REG_Array_PGLength

#endif

//---------------------------------------------------------------------
//		RTL8188E Power Configuration CMDs for USB/SDIO interfaces
//---------------------------------------------------------------------
#define Rtl8188E_NIC_PWR_ON_FLOW				rtl8188E_power_on_flow
#define Rtl8188E_NIC_RF_OFF_FLOW				rtl8188E_radio_off_flow
#define Rtl8188E_NIC_DISABLE_FLOW				rtl8188E_card_disable_flow
#define Rtl8188E_NIC_ENABLE_FLOW				rtl8188E_card_enable_flow
#define Rtl8188E_NIC_SUSPEND_FLOW				rtl8188E_suspend_flow
#define Rtl8188E_NIC_RESUME_FLOW				rtl8188E_resume_flow
#define Rtl8188E_NIC_PDN_FLOW					rtl8188E_hwpdn_flow
#define Rtl8188E_NIC_LPS_ENTER_FLOW			rtl8188E_enter_lps_flow
#define Rtl8188E_NIC_LPS_LEAVE_FLOW			rtl8188E_leave_lps_flow

#elif defined(CONFIG_USB_HCI)
#define RTL8188E_FW_UMC_IMG				"rtl8188E\\rtl8188efw.bin"
#define RTL8188E_PHY_REG					"rtl8188E\\PHY_REG_1T.txt"
#define RTL8188E_PHY_RADIO_A				"rtl8188E\\radio_a_1T.txt"
#define RTL8188E_PHY_RADIO_B				"rtl8188E\\radio_b_1T.txt"
#define RTL8188E_AGC_TAB					"rtl8188E\\AGC_TAB_1T.txt"
#define RTL8188E_PHY_MACREG 				"rtl8188E\\MAC_REG.txt"
#define RTL8188E_PHY_REG_PG				"rtl8188E\\PHY_REG_PG.txt"
#define RTL8188E_PHY_REG_MP				"rtl8188E\\PHY_REG_MP.txt"

#if 0
#define Rtl8188E_PHY_REG_Array_PG			Rtl8188EUPHY_REG_Array_PG
#define Rtl8188E_PHY_REG_Array_PGLength	Rtl8188EUPHY_REG_Array_PGLength

#endif

//---------------------------------------------------------------------
//		RTL8188E Power Configuration CMDs for USB/SDIO interfaces
//---------------------------------------------------------------------
#define Rtl8188E_NIC_PWR_ON_FLOW				rtl8188E_power_on_flow
#define Rtl8188E_NIC_RF_OFF_FLOW				rtl8188E_radio_off_flow
#define Rtl8188E_NIC_DISABLE_FLOW				rtl8188E_card_disable_flow
#define Rtl8188E_NIC_ENABLE_FLOW				rtl8188E_card_enable_flow
#define Rtl8188E_NIC_SUSPEND_FLOW				rtl8188E_suspend_flow
#define Rtl8188E_NIC_RESUME_FLOW				rtl8188E_resume_flow
#define Rtl8188E_NIC_PDN_FLOW					rtl8188E_hwpdn_flow
#define Rtl8188E_NIC_LPS_ENTER_FLOW			rtl8188E_enter_lps_flow
#define Rtl8188E_NIC_LPS_LEAVE_FLOW			rtl8188E_leave_lps_flow

#elif defined(CONFIG_PCI_HCI)
#define RTL8188E_FW_UMC_IMG				"rtl8188E\\rtl8188efw.bin"
#define RTL8188E_PHY_REG					"rtl8188E\\PHY_REG_1T.txt"
#define RTL8188E_PHY_RADIO_A				"rtl8188E\\radio_a_1T.txt"
#define RTL8188E_PHY_RADIO_B				"rtl8188E\\radio_b_1T.txt"
#define RTL8188E_AGC_TAB					"rtl8188E\\AGC_TAB_1T.txt"
#define RTL8188E_PHY_MACREG 				"rtl8188E\\MAC_REG.txt"
#define RTL8188E_PHY_REG_PG				"rtl8188E\\PHY_REG_PG.txt"
#define RTL8188E_PHY_REG_MP				"rtl8188E\\PHY_REG_MP.txt"

#define Rtl8188E_PHY_REG_Array_PG			Rtl8188EEPHY_REG_Array_PG
#define Rtl8188E_PHY_REG_Array_PGLength	Rtl8188EEPHY_REG_Array_PGLength

//---------------------------------------------------------------------
//		RTL8188E Power Configuration CMDs for USB/SDIO/PCIE interfaces
//---------------------------------------------------------------------
#define Rtl8188E_NIC_PWR_ON_FLOW				rtl8188E_power_on_flow
#define Rtl8188E_NIC_RF_OFF_FLOW				rtl8188E_radio_off_flow
#define Rtl8188E_NIC_DISABLE_FLOW				rtl8188E_card_disable_flow
#define Rtl8188E_NIC_ENABLE_FLOW				rtl8188E_card_enable_flow
#define Rtl8188E_NIC_SUSPEND_FLOW				rtl8188E_suspend_flow
#define Rtl8188E_NIC_RESUME_FLOW				rtl8188E_resume_flow
#define Rtl8188E_NIC_PDN_FLOW					rtl8188E_hwpdn_flow
#define Rtl8188E_NIC_LPS_ENTER_FLOW			rtl8188E_enter_lps_flow
#define Rtl8188E_NIC_LPS_LEAVE_FLOW			rtl8188E_leave_lps_flow
#endif //CONFIG_***_HCI


#if 1 // download firmware related data structure
#define FW_8188E_SIZE				0x4000 //16384,16k
#define FW_8188E_SIZE_2 		0x8000 /* 32768, 32k */
#define FW_8188E_START_ADDRESS	0x1000
#define FW_8188E_END_ADDRESS		0x1FFF //0x5FFF

#define MAX_PAGE_SIZE			4096	// @ page : 4k bytes

#define IS_FW_HEADER_EXIST(_pFwHdr)	((le16_to_cpu(_pFwHdr->Signature)&0xFFF0) == 0x92C0 ||\
									(le16_to_cpu(_pFwHdr->Signature)&0xFFF0) == 0x88C0 ||\
									(le16_to_cpu(_pFwHdr->Signature)&0xFFF0) == 0x2300 ||\
									(le16_to_cpu(_pFwHdr->Signature)&0xFFF0) == 0x88E0)

typedef struct _RT_FIRMWARE {
	FIRMWARE_SOURCE	eFWSource;
	u8			*szFwBuffer;
	u32			ulFwLength;

#ifdef CONFIG_WOWLAN
	u8			*szWoWLANFwBuffer;
	u32			ulWoWLANFwLength;
#endif //CONFIG_WOWLAN
} RT_FIRMWARE, *PRT_FIRMWARE, RT_FIRMWARE_8188E, *PRT_FIRMWARE_8188E;

//
// This structure must be cared byte-ordering
//

typedef struct _RT_8188E_FIRMWARE_HDR {
	// 8-byte alinment required

	//--- LONG WORD 0 ----
	u16		Signature;	// 92C0: test chip; 92C, 88C0: test chip; 88C1: MP A-cut; 92C1: MP A-cut
	u8		Category;	// AP/NIC and USB/PCI
	u8		Function;	// Reserved for different FW function indcation, for further use when driver needs to download different FW in different conditions
	u16		Version;		// FW Version
	u8		Subversion;	// FW Subversion, default 0x00
	u8		Rsvd1;


	//--- LONG WORD 1 ----
	u8		Month;	// Release time Month field
	u8		Date;	// Release time Date field
	u8		Hour;	// Release time Hour field
	u8		Minute;	// Release time Minute field
	u16		RamCodeSize;	// The size of RAM code
	u8		Foundry;
	u8		Rsvd2;

	//--- LONG WORD 2 ----
	u32		SvnIdx;	// The SVN entry index
	u32		Rsvd3;

	//--- LONG WORD 3 ----
	u32		Rsvd4;
	u32		Rsvd5;
} RT_8188E_FIRMWARE_HDR, *PRT_8188E_FIRMWARE_HDR;
#endif // download firmware related data structure


#define DRIVER_EARLY_INT_TIME		0x05
#define BCN_DMA_ATIME_INT_TIME		0x02

#ifdef CONFIG_USB_RX_AGGREGATION

typedef enum _USB_RX_AGG_MODE {
	USB_RX_AGG_DISABLE,
	USB_RX_AGG_DMA,
	USB_RX_AGG_USB,
	USB_RX_AGG_MIX
} USB_RX_AGG_MODE;

//#define MAX_RX_DMA_BUFFER_SIZE	10240		// 10K for 8192C RX DMA buffer

#endif


#define MAX_RX_DMA_BUFFER_SIZE_88E	      0x2400 //9k for 88E nornal chip , //MaxRxBuff=10k-max(TxReportSize(64*8), WOLPattern(16*24))

#define MAX_TX_REPORT_BUFFER_SIZE			0x0400 // 1k 


// Note: We will divide number of page equally for each queue other than public queue!
// 22k = 22528 bytes = 176 pages (@page =  128 bytes)
// must reserved about 7 pages for LPS =>  176-7 = 169 (0xA9)
// 2*BCN / 1*ps-poll / 1*null-data /1*prob_rsp /1*QOS null-data /1*BT QOS null-data

#define TX_TOTAL_PAGE_NUMBER_88E		0xA9//  169 (21632=> 21k)

#ifdef RTL8188ES_MAC_LOOPBACK
#define TX_PAGE_BOUNDARY_88E 0x48 //72
#else //TX_PAGE_BOUNDARY_LOOPBACK_MODE
#define TX_PAGE_BOUNDARY_88E (TX_TOTAL_PAGE_NUMBER_88E + 1)
#endif


//Note: For Normal Chip Setting ,modify later
#define WMM_NORMAL_TX_TOTAL_PAGE_NUMBER	TX_TOTAL_PAGE_NUMBER_88E  //0xA9 , 0xb0=>176=>22k
#define WMM_NORMAL_TX_PAGE_BOUNDARY_88E	(WMM_NORMAL_TX_TOTAL_PAGE_NUMBER + 1) //0xA9



//-------------------------------------------------------------------------
//	Chip specific
//-------------------------------------------------------------------------
#define CHIP_BONDING_IDENTIFIER(_value)	(((_value)>>22)&0x3)
#define CHIP_BONDING_92C_1T2R	0x1
#define CHIP_BONDING_88C_USB_MCARD	0x2
#define CHIP_BONDING_88C_USB_HP	0x1

//-------------------------------------------------------------------------
//	Channel Plan
//-------------------------------------------------------------------------
enum ChannelPlan {
	CHPL_FCC	= 0,
	CHPL_IC		= 1,
	CHPL_ETSI	= 2,
	CHPL_SPAIN	= 3,
	CHPL_FRANCE	= 4,
	CHPL_MKK	= 5,
	CHPL_MKK1	= 6,
	CHPL_ISRAEL	= 7,
	CHPL_TELEC	= 8,
	CHPL_GLOBAL	= 9,
	CHPL_WORLD	= 10,
};

typedef struct _TxPowerInfo {
	u8 CCKIndex[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 HT40_1SIndex[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 HT40_2SIndexDiff[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 HT20IndexDiff[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 OFDMIndexDiff[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 HT40MaxOffset[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 HT20MaxOffset[MAX_RF_PATH][CHANNEL_GROUP_MAX_88E];
	u8 TSSI_A[3];
	u8 TSSI_B[3];
	u8 TSSI_A_5G[3];		//5GL/5GM/5GH
	u8 TSSI_B_5G[3];
} TxPowerInfo, *PTxPowerInfo;

#define EFUSE_REAL_CONTENT_LEN		512
#define EFUSE_MAP_LEN				128
#define EFUSE_MAX_SECTION			16
#define EFUSE_IC_ID_OFFSET			506	//For some inferiority IC purpose. added by Roger, 2009.09.02.
#define AVAILABLE_EFUSE_ADDR(addr) 	(addr < EFUSE_REAL_CONTENT_LEN)
//
// <Roger_Notes>
// To prevent out of boundary programming case,
// leave 1byte and program full section
// 9bytes + 1byt + 5bytes and pre 1byte.
// For worst case:
// | 1byte|----8bytes----|1byte|--5bytes--|
// |         |            Reserved(14bytes)	      |
//
#define EFUSE_OOB_PROTECT_BYTES 		15	// PG data exclude header, dummy 6 bytes frome CP test and reserved 1byte.

#define		HWSET_MAX_SIZE_88E		512

#define		EFUSE_REAL_CONTENT_LEN_88E	256
#define		EFUSE_MAP_LEN_88E		512
#define		EFUSE_MAX_SECTION_88E		64
#define		EFUSE_MAX_WORD_UNIT_88E		4
#define		EFUSE_IC_ID_OFFSET_88E			506	//For some inferiority IC purpose. added by Roger, 2009.09.02.
#define 		AVAILABLE_EFUSE_ADDR_88E(addr) 	(addr < EFUSE_REAL_CONTENT_LEN_88E)
// <Roger_Notes> To prevent out of boundary programming case, leave 1byte and program full section
// 9bytes + 1byt + 5bytes and pre 1byte.
// For worst case:
// | 2byte|----8bytes----|1byte|--7bytes--| //92D
#define 		EFUSE_OOB_PROTECT_BYTES_88E	18 	// PG data exclude header, dummy 7 bytes frome CP test and reserved 1byte.
#define		EFUSE_PROTECT_BYTES_BANK_88E	16


//========================================================
//			EFUSE for BT definition
//========================================================
#define EFUSE_BT_REAL_CONTENT_LEN		1536	// 512*3
#define EFUSE_BT_MAP_LEN				1024	// 1k bytes
#define EFUSE_BT_MAX_SECTION			128		// 1024/8

#define EFUSE_PROTECT_BYTES_BANK		16

#define GET_HAL_DATA(__pAdapter)	((HAL_DATA_TYPE *)((__pAdapter)->HalData))
#define GET_RF_TYPE(priv)			(GET_HAL_DATA(priv)->rf_type)

#define INCLUDE_MULTI_FUNC_BT(_Adapter)	(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_BT)
#define INCLUDE_MULTI_FUNC_GPS(_Adapter)	(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_GPS)

//#define IS_MULTI_FUNC_CHIP(_Adapter)	(((((PHAL_DATA_TYPE)(_Adapter->HalData))->MultiFunc) & (RT_MULTI_FUNC_BT|RT_MULTI_FUNC_GPS)) ? _TRUE : _FALSE)

//#define RT_IS_FUNC_DISABLED(__pAdapter, __FuncBits) ( (__pAdapter)->DisabledFunctions & (__FuncBits) )

// rtl8188e_hal_init.c
u8 _CardEnable(_adapter *padapter);
s32 rtl8188e_FirmwareDownload(_adapter *padapter, BOOLEAN  bUsedWoWLANFw);
void _8051Reset88E(_adapter *padapter);
void rtl8188e_InitializeFirmwareVars(_adapter *padapter);

u32 rtl8188e_InitPowerOn(_adapter *padapter);
void rtl8188e_start_thread(_adapter *padapter);
void rtl8188e_stop_thread(_adapter *padapter);
u32 rtl8188e_hal_init(_adapter *padapter);
u32 rtl8188e_hal_deinit(_adapter *padapter);


u32 rtl8188e_inirp_init(_adapter *padapter);
u32 rtl8188e_inirp_deinit(_adapter *padapter);
void rtl8188e_irp_reset(_adapter *padapter);

s32 InitLLTTable(_adapter *padapter, u8 txpktbuf_bndy);
void _InitBeaconParameters(_adapter *padapter);

// EFuse
u8 GetEEPROMSize8188E(_adapter *padapter);
void Hal_InitPGData88E(_adapter *padapter);
void Hal_EfuseParseIDCode88E(_adapter *padapter, u8 *hwinfo);
void Hal_ReadTxPowerInfo88E(_adapter *padapter, u8 *hwinfo, BOOLEAN	AutoLoadFail);

void Hal_EfuseParseEEPROMVer88E(_adapter *padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void rtl8188e_EfuseParseChnlPlan(_adapter *padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseCustomerID88E(_adapter *padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_ReadAntennaDiversity88E(_adapter *pAdapter, u8 *PROMContent, BOOLEAN AutoLoadFail);
void Hal_ReadThermalMeter_88E(_adapter 	*Adapter, u8 *PROMContent, BOOLEAN 	AutoloadFail);
void Hal_EfuseParseXtal_8188E(_adapter *pAdapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseBoardType88E(_adapter *pAdapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_ReadPowerSavingMode88E(_adapter *pAdapter, u8 *hwinfo, BOOLEAN AutoLoadFail);

void rtl8188e_read_chip_version(_adapter *padapter);
void rtl8188e_ReadEFuse(_adapter 	*Adapter, u8 efuseType, u16 _offset,	u16 _size_byte,
						u8 *pbuf, IN BOOLEAN bPseudoTest);
void rtl8188e_EfusePowerSwitch(IN	_adapter *pAdapter, IN	u8 bWrite, IN	u8 PwrState);
void ReadEFuse_Pseudo(_adapter *Adapter, u8 efuseType, u16 _offset, u16 _size_byte,
					  u8 *pbuf, IN BOOLEAN bPseudoTest);
void rtl8188e_EFUSE_GetEfuseDefinition(IN	_adapter *pAdapter,	IN u8 efuseType, IN u8 type,
									   OUT void *pOut, IN BOOLEAN bPseudoTest);
u16
rtl8188e_EfuseGetCurrentSize(IN _adapter *pAdapter, IN u8 efuseType, IN	BOOLEAN	bPseudoTest);
int rtl8188e_Efuse_PgPacketRead(IN _adapter 	*pAdapter, IN u8 offset, IN u8 *data, IN BOOLEAN bPseudoTest);
int rtl8188e_Efuse_PgPacketWrite(IN _adapter *pAdapter, IN u8 offset, IN u8 word_en, IN u8 *data,
								 IN BOOLEAN bPseudoTest);
u8 rtl8188e_Efuse_WordEnableDataWrite(IN _adapter *pAdapter, IN u16 efuse_addr, IN u8 word_en,
									  IN u8 *data, IN BOOLEAN bPseudoTest);

void EnableInterrupt8188E(IN _adapter 			*Adapter);
void DisableInterrupt8188E(IN _adapter 			*Adapter);
s32	rtl8188e_interrupt_handler(_adapter *padapter);

BOOLEAN HalDetectPwrDownMode88E(_adapter *Adapter);

#ifdef CONFIG_WOWLAN
void Hal_DetectWoWMode(_adapter *pAdapter);
#endif //CONFIG_WOWLAN
//RT_CHANNEL_DOMAIN rtl8723a_HalMapChannelPlan(_adapter * padapter, u8 HalChannelPlan);
//VERSION_8192C rtl8723a_ReadChipVersion(_adapter * padapter);
//void rtl8723a_ReadBluetoothCoexistInfo(_adapter * padapter, u8 *PROMContent, BOOLEAN AutoloadFail);
void Hal_InitChannelPlan(_adapter *padapter);

s32 _ReadAdapterInfo8188ES(_adapter *padapter);

s32 rtl8188e_mgnt_xmit(_adapter *padapter, struct xmit_frame *pmgntframe);
s32 rtl8188e_hal_xmit(PADAPTER padapter, struct xmit_frame *pxmitframe);

u32 rtl8188e_set_hal_ops(_adapter *padapter);

// register
//void SetBcnCtrlReg(_adapter * padapter, u8 SetBits, u8 ClearBits);

void rtl8188e_clone_haldata(_adapter *dst_adapter, _adapter *src_adapter);

void InitInterrupt8188E(_adapter *Adapter);
void ClearInterrupt8188E(_adapter *Adapter);
void EnableInterrupt8188E(_adapter *Adapter);
void DisableInterrupt8188E(_adapter *Adapter);
void UpdateInterruptMask8188E(
	IN _adapter *padapter,
	IN u32 AddMSR,
	IN u32 RemoveMSR);
BOOLEAN InterruptRecognized8188E(
	IN	_adapter 			*Adapter,
	OUT	u32	*pIsrContent1,
	OUT	u32	*pIsrContent2
);

#endif //__RTL8188E_HAL_H__

