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
#ifndef __RTL8192E_HAL_H__
#define __RTL8192E_HAL_H__
#include "../../../include/cmn_info/rtw_sta_info.h"

#include "hal_data.h"

#include "rtl8192e_spec.h"
#include "rtl8192e_rf.h"
#include "rtl8192e_dm.h"
#include "rtl8192e_recv.h"
#include "rtl8192e_xmit.h"
#include "rtl8192e_cmd.h"
#include "Hal8192EPwrSeq.h"
#include "Hal8192EPhyReg.h"
#include "Hal8192EPhyCfg.h"
#ifdef DBG_CONFIG_ERROR_DETECT
#include "rtl8192e_sreset.h"
#endif

#if 0// devin_li mask phydm
#include "../OUTSRC/rtl8192e/phydm_precomp.h" //frankieodm add ODMLJM
#endif
//---------------------------------------------------------------------
//		RTL8192E From file
//---------------------------------------------------------------------
#define RTL8192E_FW_IMG					"rtl8192e/FW_NIC.bin"
#define RTL8192E_FW_WW_IMG				"rtl8192e/FW_WoWLAN.bin"
#define RTL8192E_PHY_REG					"rtl8192e/PHY_REG.txt"
#define RTL8192E_PHY_RADIO_A				"rtl8192e/RadioA.txt"
#define RTL8192E_PHY_RADIO_B				"rtl8192e/RadioB.txt"
#define RTL8192E_TXPWR_TRACK				"rtl8192e/TxPowerTrack.txt"
#define RTL8192E_AGC_TAB					"rtl8192e/AGC_TAB.txt"
#define RTL8192E_PHY_MACREG 				"rtl8192e/MAC_REG.txt"
#define RTL8192E_PHY_REG_PG				"rtl8192e/PHY_REG_PG.txt"
#define RTL8192E_PHY_REG_MP				"rtl8192e/PHY_REG_MP.txt"
#define RTL8192E_TXPWR_LMT 				"rtl8192e/TXPWR_LMT.txt"

//---------------------------------------------------------------------
//		RTL8192E From header
//---------------------------------------------------------------------

#if MP_DRIVER == 1
#define Rtl8192E_FwBTImgArray				Rtl8192EFwBTImgArray
#define Rtl8192E_FwBTImgArrayLength		Rtl8192EFwBTImgArrayLength

#define Rtl8192E_FwMPImageArray			Rtl8192EFwMPImgArray
#define Rtl8192E_FwMPImgArrayLength		Rtl8192EMPImgArrayLength

#define Rtl8192E_PHY_REG_Array_MP			Rtl8192E_PHYREG_Array_MP
#define Rtl8192E_PHY_REG_Array_MPLength	Rtl8192E_PHYREG_Array_MPLength
#endif


#if 1 /* download firmware related data structure */
#define FW_SIZE_8192E			0x8000 /* Compatible with RTL8192e Maximal RAM code size 32k */
#define FW_START_ADDRESS		0x1000
#define FW_END_ADDRESS			0x5FFF


#define IS_FW_HEADER_EXIST_8192E(_pFwHdr)	((GET_FIRMWARE_HDR_SIGNATURE_8192E(_pFwHdr) & 0xFFF0) == 0x92E0)



typedef struct _RT_FIRMWARE_8192E {
	FIRMWARE_SOURCE	eFWSource;
	u8			*szFwBuffer;
	u32			ulFwLength;
} RT_FIRMWARE_8192E, *PRT_FIRMWARE_8192E;

/*
 * This structure must be cared byte-ordering
 *
 * Added by tynli. 2009.12.04. */

/* *****************************************************
 *					Firmware Header(8-byte alinment required)
 * *****************************************************
 * --- LONG WORD 0 ---- */
#define GET_FIRMWARE_HDR_SIGNATURE_8192E(__FwHdr)		LE_BITS_TO_4BYTE(__FwHdr, 0, 16) /* 92C0: test chip; 92C, 88C0: test chip; 88C1: MP A-cut; 92C1: MP A-cut */
#define GET_FIRMWARE_HDR_CATEGORY_8192E(__FwHdr)		LE_BITS_TO_4BYTE(__FwHdr, 16, 8) /* AP/NIC and USB/PCI */
#define GET_FIRMWARE_HDR_FUNCTION_8192E(__FwHdr)		LE_BITS_TO_4BYTE(__FwHdr, 24, 8) /* Reserved for different FW function indcation, for further use when driver needs to download different FW in different conditions */
#define GET_FIRMWARE_HDR_VERSION_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+4, 0, 16)/* FW Version */
#define GET_FIRMWARE_HDR_SUB_VER_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+4, 16, 8) /* FW Subversion, default 0x00 */
#define GET_FIRMWARE_HDR_RSVD1_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+4, 24, 8)

/* --- LONG WORD 1 ---- */
#define GET_FIRMWARE_HDR_MONTH_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+8, 0, 8) /* Release time Month field */
#define GET_FIRMWARE_HDR_DATE_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+8, 8, 8) /* Release time Date field */
#define GET_FIRMWARE_HDR_HOUR_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+8, 16, 8)/* Release time Hour field */
#define GET_FIRMWARE_HDR_MINUTE_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+8, 24, 8)/* Release time Minute field */
#define GET_FIRMWARE_HDR_ROMCODE_SIZE_8192E(__FwHdr)	LE_BITS_TO_4BYTE(__FwHdr+12, 0, 16)/* The size of RAM code */
#define GET_FIRMWARE_HDR_RSVD2_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+12, 16, 16)

/* --- LONG WORD 2 ---- */
#define GET_FIRMWARE_HDR_SVN_IDX_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+16, 0, 32)/* The SVN entry index */
#define GET_FIRMWARE_HDR_RSVD3_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+20, 0, 32)

/* --- LONG WORD 3 ---- */
#define GET_FIRMWARE_HDR_RSVD4_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+24, 0, 32)
#define GET_FIRMWARE_HDR_RSVD5_8192E(__FwHdr)			LE_BITS_TO_4BYTE(__FwHdr+28, 0, 32)

#endif /* download firmware related data structure */

#define DRIVER_EARLY_INT_TIME_8192E		0x05
#define BCN_DMA_ATIME_INT_TIME_8192E		0x02

// for 8192E
// TX 32K, RX 16K, Page size 128B for TX, 8B for RX
#define PAGE_SIZE_TX_8192E			128
#define PAGE_SIZE_RX_8192E			8

#define RX_DMA_SIZE_8192E			0x4000	// 16K
#ifdef CONFIG_FW_C2H_DEBUG
#define RX_DMA_RESERVED_SIZE_8192E	0x100	// 256B, reserved for c2h debug message
#else
//#define RX_DMA_RESERVED_SIZE_8192E	0x80	// 128B, reserved for tx report
#define RX_DMA_RESERVED_SIZE_8192E	0x40	/* 64B, reserved for c2h event(16bytes) or ccx(8 Bytes) merge from linux code*/
#endif
#define RX_DMA_BOUNDARY_8192E		(RX_DMA_SIZE_8192E - RX_DMA_RESERVED_SIZE_8192E - 1)

#ifdef CONFIG_WOWLAN
#define MAX_WKFM_NUM 16
#define WKFMCAM_SIZE 24
#define RESV_FMWF	WKFMCAM_SIZE*MAX_WKFM_NUM /* 16 entries, for each is 24 bytes*/
#else
#define RESV_FMWF	0
#endif
// Note: We will divide number of page equally for each queue other than public queue!

//For General Reserved Page Number(Beacon Queue is reserved page)
//Beacon:2, PS-Poll:1, Null Data:1,Qos Null Data:1,BT Qos Null Data:1
#define BCNQ_PAGE_NUM_8192E		0x08
#ifdef CONFIG_CONCURRENT_MODE
#define BCNQ1_PAGE_NUM_8192E		0x08 // 0x04
#else
#define BCNQ1_PAGE_NUM_8192E		0x00
#endif

#ifdef CONFIG_PNO_SUPPORT
#undef BCNQ1_PAGE_NUM_8192E
#define BCNQ1_PAGE_NUM_8192E		0x00 // 0x04
#endif
#define MAX_RX_DMA_BUFFER_SIZE_8192E	0x2800	// RX 10K

//For WoWLan , more reserved page
//ARP Rsp:1, RWC:1, GTK Info:1,GTK RSP:2,GTK EXT MEM:2, PNO: 6
#ifdef CONFIG_WOWLAN
#define WOWLAN_PAGE_NUM_8192E	0x07
#else
#define WOWLAN_PAGE_NUM_8192E	0x00
#endif

#ifdef CONFIG_PNO_SUPPORT
#undef WOWLAN_PAGE_NUM_8192E
#define WOWLAN_PAGE_NUM_8192E	0x15
#endif

#ifdef CONFIG_AP_WOWLAN
#define AP_WOWLAN_PAGE_NUM_8192E	0x02
#endif

#define TX_TOTAL_PAGE_NUMBER_8192E	(0xFF - BCNQ_PAGE_NUM_8192E - BCNQ1_PAGE_NUM_8192E - WOWLAN_PAGE_NUM_8192E)
#define TX_PAGE_BOUNDARY_8192E		(TX_TOTAL_PAGE_NUMBER_8192E + 1)

#define WMM_NORMAL_TX_TOTAL_PAGE_NUMBER_8192E	TX_TOTAL_PAGE_NUMBER_8192E
#define WMM_NORMAL_TX_PAGE_BOUNDARY_8192E		(WMM_NORMAL_TX_TOTAL_PAGE_NUMBER_8192E + 1)

// For Normal Chip Setting
// (HPQ + LPQ + NPQ + PUBQ) shall be TX_TOTAL_PAGE_NUMBER_8192E
#define NORMAL_PAGE_NUM_HPQ_8192E		0x10//0x0C
#define NORMAL_PAGE_NUM_LPQ_8192E		0x10//0x02
#define NORMAL_PAGE_NUM_NPQ_8192E	0x10//0x02

// Note: For Normal Chip Setting, modify later
#define WMM_NORMAL_PAGE_NUM_HPQ_8192E		0x30
#define WMM_NORMAL_PAGE_NUM_LPQ_8192E		0x20
#define WMM_NORMAL_PAGE_NUM_NPQ_8192E		0x20


#include "HalVerDef.h"
#include "hal_com.h"

#define EFUSE_OOB_PROTECT_BYTES 		15

#define HWSET_MAX_SIZE_8192E			512
#define EFUSE_REAL_CONTENT_LEN_8192E		512
#define EFUSE_MAP_LEN_8192E				512
#define EFUSE_MAX_SECTION_8192E			64

#define EFUSE_IC_ID_OFFSET			506	//For some inferiority IC purpose. added by Roger, 2009.09.02.
#define AVAILABLE_EFUSE_ADDR(addr) 	(addr < EFUSE_REAL_CONTENT_LEN_8192E)

#define EFUSE_ACCESS_ON			0x69	// For RTL8188 only.
#define EFUSE_ACCESS_OFF			0x00	// For RTL8188 only.

//========================================================
//			EFUSE for BT definition
//========================================================
#define EFUSE_BT_REAL_BANK_CONTENT_LEN	512
#define EFUSE_BT_REAL_CONTENT_LEN		1536	// 512*3
#define EFUSE_BT_MAP_LEN				1024	// 1k bytes
#define EFUSE_BT_MAX_SECTION			128		// 1024/8

#define EFUSE_PROTECT_BYTES_BANK		16

// Description: Determine the types of C2H events that are the same in driver and Fw.
// Fisrt constructed by tynli. 2009.10.09.
#if 0
typedef enum _C2H_EVT {
	C2H_DBG = 0,
	C2H_TSF = 1,
	C2H_AP_RPT_RSP = 2,
	C2H_CCX_TX_RPT = 3,	// The FW notify the report of the specific tx packet.
	C2H_BT_RSSI = 4,
	C2H_BT_OP_MODE = 5,
	C2H_EXT_RA_RPT = 6,
	C2H_8192E_BT_INFO = 9,
	C2H_HW_INFO_EXCH = 10,
	C2H_8192E_BT_MP_INFO = 11,
	C2H_8192E_P2P_RPORT = 0x16,
#ifdef CONFIG_FW_C2H_DEBUG
	C2H_8192E_FW_DEBUG = 0xff,
#endif //CONFIG_FW_C2H_DEBUG
	MAX_C2HEVENT
} C2H_EVT;
#endif

typedef enum tag_Package_Definition {
	PACKAGE_DEFAULT,
	PACKAGE_QFN68,
	PACKAGE_TFBGA90,
	PACKAGE_TFBGA80,
	PACKAGE_TFBGA79
} PACKAGE_TYPE_E;

#define INCLUDE_MULTI_FUNC_BT(_Adapter)		(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_BT)
#define INCLUDE_MULTI_FUNC_GPS(_Adapter)	(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_GPS)

#define GET_RF_TYPE(priv)			(GET_HAL_DATA(priv)->rf_type)
#define GET_HAL_DATA(__pAdapter)	((HAL_DATA_TYPE *)((__pAdapter)->HalData))
// rtl8188a_hal_init.c
s32 rtl8192e_FirmwareDownload(PADAPTER padapter, BOOLEAN  bUsedWoWLANFw);
void rtl8192e_FirmwareSelfReset(PADAPTER padapter);
void rtl8192e_InitializeFirmwareVars(PADAPTER padapter);

void rtl8192e_InitAntenna_Selection(PADAPTER padapter);
void rtl8192e_DeinitAntenna_Selection(PADAPTER padapter);
void rtl8192e_CheckAntenna_Selection(PADAPTER padapter);
void rtl8192e_init_default_value(PADAPTER padapter);

s32 rtl8192e_InitLLTTable(PADAPTER padapter);

s32 CardDisableHWSM(PADAPTER padapter, u8 resetMCU);
s32 CardDisableWithoutHWSM(PADAPTER padapter);

// EFuse
u8 GetEEPROMSize8192E(PADAPTER padapter);
void Hal_InitPGData(PADAPTER padapter, u8 *PROMContent);
void Hal_EfuseParseIDCode(PADAPTER padapter, u8 *hwinfo);
void Hal_EfuseParseTxPowerInfo_8192E(PADAPTER padapter, u8 *PROMContent, BOOLEAN AutoLoadFail);
void Hal_EfuseParseBTCoexistInfo_8192E(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseEEPROMVer_8192E(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseChnlPlan_8192E(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseCustomerID_8192E(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseAntennaDiversity_8192E(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseXtal_8192E(PADAPTER pAdapter, u8 *hwinfo, u8 AutoLoadFail);
void Hal_EfuseParseThermalMeter_8192E(PADAPTER padapter, u8 *hwinfo, u8 AutoLoadFail);
VOID Hal_EfuseParsePackageType_8192E(PADAPTER pAdapter, u8 *hwinfo, BOOLEAN AutoLoadFail);

#if 0 /* Do not need for rtl8192e */
VOID Hal_EfuseParseVoltage_8192E(PADAPTER pAdapter, u8 *hwinfo, BOOLEAN 	AutoLoadFail);
#endif

#ifdef CONFIG_C2H_PACKET_EN
void rtl8192e_c2h_packet_handler(PADAPTER padapter, u8 *pbuf, u16 length);
#endif


void rtl8192e_set_hal_ops(struct hal_ops *pHalFunc);
void SetHwReg8192E(PADAPTER padapter, u8 variable, u8 *val);
void GetHwReg8192E(PADAPTER padapter, u8 variable, u8 *val);
#ifdef CONFIG_C2H_PACKET_EN
void SetHwRegWithBuf8192E(PADAPTER padapter, u8 variable, u8 *pbuf, int len);
#endif // CONFIG_C2H_PACKET_EN
u8 SetHalDefVar8192E(PADAPTER padapter, HAL_DEF_VARIABLE variable, void *pval);
u8 GetHalDefVar8192E(PADAPTER padapter, HAL_DEF_VARIABLE variable, void *pval);

// register
void rtl8192e_InitBeaconParameters(PADAPTER padapter);
void rtl8192e_InitBeaconMaxError(PADAPTER padapter, u8 InfraMode);
void	_InitBurstPktLen_8192ES(PADAPTER Adapter);
void _8051Reset8192E(PADAPTER padapter);
#ifdef CONFIG_WOWLAN
void Hal_DetectWoWMode(PADAPTER pAdapter);
void rtw_get_current_ip_address(PADAPTER padapter, u8 *pcurrentip);
void rtw_get_sec_iv(PADAPTER padapter, u8 *pcur_dot11txpn, u8 *StaAddr);
#endif //CONFIG_WOWLAN
void rtw_set_sec_pn(PADAPTER padapter);
void rtl8192e_start_thread(_adapter *padapter);
void rtl8192e_stop_thread(_adapter *padapter);

#if defined(CONFIG_CHECK_BT_HANG) && defined(CONFIG_BT_COEXIST)
void rtl8192es_init_checkbthang_workqueue(_adapter *adapter);
void rtl8192es_free_checkbthang_workqueue(_adapter *adapter);
void rtl8192es_cancle_checkbthang_workqueue(_adapter *adapter);
void rtl8192es_hal_check_bt_hang(_adapter *adapter);
#endif

#ifdef CONFIG_GPIO_WAKEUP
void HalSetOutPutGPIO(PADAPTER padapter, u8 index, u8 OutPutValue);
#endif
#ifdef CONFIG_BT_COEXIST
int FirmwareDownloadBT(IN PADAPTER Adapter, PRT_MP_FIRMWARE pFirmware);
#endif
void CCX_FwC2HTxRpt_8192e(PADAPTER padapter, u8 *pdata, u8 len);
#ifdef CONFIG_FW_C2H_DEBUG
void Debug_FwC2H_8192e(PADAPTER padapter, u8 *pdata, u8 len);
#endif //CONFIG_FW_C2H_DEBUG
s32 c2h_id_filter_ccx_8192e(u8 *buf);
s32 c2h_handler_8192e(PADAPTER padapter, u8 *pC2hEvent);
u8 MRateToHwRate8192E(u8  rate);
u8 HwRateToMRate8192E(u8	 rate);

#ifdef CONFIG_PCI_HCI
BOOLEAN	InterruptRecognized8192EE(PADAPTER Adapter);
VOID	UpdateInterruptMask8192EE(PADAPTER Adapter, u32 AddMSR, u32 AddMSR1, u32 RemoveMSR, u32 RemoveMSR1);
#endif
extern void InitInterrupt8192ESdio(PADAPTER padapter);
extern void InitSysInterrupt8192ESdio(PADAPTER padapter);
extern void EnableInterrupt8192ESdio(PADAPTER padapter);
extern void DisableInterrupt8192ESdio(PADAPTER padapter);
extern s32  rtl8192e_interrupt_handler(PADAPTER padapter);
extern void rtl8192e_read_chip_version(PADAPTER padapter);
extern void UpdateHalRAMask8192E(PADAPTER padapter, u32 mac_id, u8 rssi_level);
void rtl8192e_SetBeaconRelatedRegisters(PADAPTER padapter);
//void rtl8192e_Add_RateATid(PADAPTER pAdapter, u64 bitmap, u8* arg, u8 rssi_level);
void rtl8192e_recv_tasklet(void *priv);
void rtl8192e_free_hal_data(_adapter *padapter);
void Hal_EfusePowerSwitch(PADAPTER	padapter, u8 bWrite, u8 PwrState);
void
Hal_ReadEFuse(
	PADAPTER	padapter,
	u8			efuseType,
	u16			_offset,
	u16			_size_byte,
	u8			*pbuf,
	u8			bPseudoTest);
void
Hal_GetEfuseDefinition(
	PADAPTER	padapter,
	u8			efuseType,
	u8			type,
	void		*pOut,
	u8			bPseudoTest);
u16
Hal_EfuseGetCurrentSize(
	PADAPTER	pAdapter,
	u8			efuseType,
	u8			bPseudoTest);
s32
Hal_EfusePgPacketRead(
	PADAPTER	padapter,
	u8			offset,
	u8			*data,
	u8			bPseudoTest);
s32
Hal_EfusePgPacketWrite(
	PADAPTER	padapter,
	u8 			offset,
	u8			word_en,
	u8			*pData,
	u8			bPseudoTest);
u8
Hal_EfuseWordEnableDataWrite(
	PADAPTER	padapter,
	u16			efuse_addr,
	u8			word_en,
	u8			*data,
	u8			bPseudoTest);

u8
rtw_config_map_read(
	PADAPTER	 padapter,
	u16			 addr,
	u16 			cnts,
	u8 			*data,
	u8 			efuse);

u8
rtw_config_map_write(
	PADAPTER	 padapter,
	u16			 addr,
	u16 			cnts,
	u8 			*data,
	u8 			efuse);

void rtl8192e_GetHalODMVar(
	PADAPTER				Adapter,
	HAL_ODM_VARIABLE		eVariable,
	PVOID					pValue1,
	BOOLEAN					bSet);
void rtl8192e_SetHalODMVar(
	PADAPTER				Adapter,
	HAL_ODM_VARIABLE		eVariable,
	PVOID					pValue1,
	BOOLEAN					bSet);
void hal_notch_filter_8192e(_adapter *adapter, bool enable);
extern u8 HalQueryTxBufferStatus8192ESdio(PADAPTER padapter);
extern u8 HalQueryTxOQTBufferStatus8192ESdio(PADAPTER padapter);
#if defined(CONFIG_WOWLAN) || defined(CONFIG_AP_WOWLAN)
extern void DisableInterruptButCpwm28192ESdio(PADAPTER padapter);
extern void ClearInterrupt8192ESdio(PADAPTER padapter);
#endif

#endif

