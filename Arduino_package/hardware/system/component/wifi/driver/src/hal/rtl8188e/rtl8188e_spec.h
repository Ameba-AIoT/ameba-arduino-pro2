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
 *******************************************************************************/
#ifndef __RTL8188E_SPEC_H__
#define __RTL8188E_SPEC_H__

#ifndef BIT
#define BIT(x)		((u32)1 << (x))
#endif

//============================================================
//       8192C Regsiter offset definition
//============================================================

#define		HAL_PS_TIMER_INT_DELAY	50		//  50 microseconds


//============================================================
//
//============================================================

//-----------------------------------------------------
//
//	0x0000h ~ 0x00FFh	System Configuration
//
//-----------------------------------------------------
#define REG_BB_PAD_CTRL				0x0064
#define REG_HMEBOX_E0					0x0088
#define REG_HMEBOX_E1					0x008A
#define REG_HMEBOX_E2					0x008C
#define REG_HMEBOX_E3					0x008E
#define REG_HMEBOX_EXT_0				0x01F0
#define REG_HMEBOX_EXT_1				0x01F4
#define REG_HMEBOX_EXT_2				0x01F8
#define REG_HMEBOX_EXT_3				0x01FC
#define REG_HIMR_88E					0x00B0 //RTL8188E
#define REG_HISR_88E					0x00B4 //RTL8188E
#define REG_HIMRE_88E					0x00B8 //RTL8188E
#define REG_HISRE_88E					0x00BC //RTL8188E
#define REG_MACID_NO_LINK_0			0x0484
#define REG_MACID_NO_LINK_1			0x0488

//-----------------------------------------------------
//
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//
//-----------------------------------------------------
#define REG_PKTBUF_DBG_ADDR 			(REG_PKTBUF_DBG_CTRL)
#define REG_RXPKTBUF_DBG				(REG_PKTBUF_DBG_CTRL+2)
#define REG_TXPKTBUF_DBG				(REG_PKTBUF_DBG_CTRL+3)
#define REG_WOWLAN_WAKE_REASON		REG_MCUTST_WOWLAN


// 8192C EFUSE
//----------------------------------------------------------------------------
#define		HWSET_MAX_SIZE				256
#define		HWSET_MAX_SIZE_88E		512



#define EFUSE_ACCESS_ON			0x69	// For RTL8723 only.
#define EFUSE_ACCESS_OFF			0x00	// For RTL8723 only.


//-----------------------------------------------------
//
//	0x0600h ~ 0x07FFh	WMAC Configuration
//
//-----------------------------------------------------
//2APSD_CTRL
#define APSDOFF						BIT(6)
#define APSDOFF_STATUS				BIT(7)


#define RATE_BITMAP_ALL				0xFFFFF

// Only use CCK 1M rate for ACK
#define RATE_RRSR_CCK_ONLY_1M		0xFFFF1


// SDIO Host Interrupt Service Routine
#define SDIO_HISR_RX_REQUEST			BIT0
#define SDIO_HISR_AVAL				BIT1
#define SDIO_HISR_TXERR				BIT2
#define SDIO_HISR_RXERR				BIT3
#define SDIO_HISR_TXFOVW			BIT4
#define SDIO_HISR_RXFOVW			BIT5
#define SDIO_HISR_TXBCNOK			BIT6
#define SDIO_HISR_TXBCNERR			BIT7
#define SDIO_HISR_BCNERLY_INT			BIT16
#define SDIO_HISR_C2HCMD			BIT17
#define SDIO_HISR_CPWM1				BIT18
#define SDIO_HISR_CPWM2				BIT19
#define SDIO_HISR_HSISR_IND			BIT20
#define SDIO_HISR_GTINT3_IND			BIT21
#define SDIO_HISR_GTINT4_IND			BIT22
#define SDIO_HISR_PSTIMEOUT			BIT23
#define SDIO_HISR_OCPINT			BIT24
#define SDIO_HISR_ATIMEND			BIT25
#define SDIO_HISR_ATIMEND_E			BIT26
#define SDIO_HISR_CTWEND			BIT27

//RTL8188E SDIO Specific
#define	SDIO_HISR_MCU_ERR					BIT28
#define	SDIO_HISR_TSF_BIT32_TOGGLE		BIT29

#define MASK_SDIO_HISR_CLEAR		(SDIO_HISR_TXERR |\
									SDIO_HISR_RXERR |\
									SDIO_HISR_TXFOVW |\
									SDIO_HISR_RXFOVW |\
									SDIO_HISR_TXBCNOK |\
									SDIO_HISR_TXBCNERR |\
									SDIO_HISR_C2HCMD |\
									SDIO_HISR_CPWM1 |\
									SDIO_HISR_CPWM2 |\
									SDIO_HISR_HSISR_IND |\
									SDIO_HISR_GTINT3_IND |\
									SDIO_HISR_GTINT4_IND |\
									SDIO_HISR_PSTIMEOUT |\
									SDIO_HISR_OCPINT)

// SDIO HCI Suspend Control Register
#define HCI_RESUME_PWR_RDY			BIT1
#define HCI_SUS_CTRL				BIT0


/* move to rtl8188e_xmit.h
#if DEV_BUS_TYPE == RT_SDIO_INTERFACE
	#define 	MAX_TX_AGG_PACKET_NUMBER 	0x8
#else
	#define 	MAX_TX_AGG_PACKET_NUMBER 	0xFF
#endif
*/

// vivi added for new cam search flow, 20091028
//#define SCR_TxUseBroadcastDK			BIT6	// Force Tx Use Broadcast Default Key
//#define SCR_RxUseBroadcastDK			BIT7	// Force Rx Use Broadcast Default Key

//-----------------------------------------------------
//
//	0xFE00h ~ 0xFE55h	USB Configuration
//
//-----------------------------------------------------

//2 USB Information (0xFE17)
#define USB_IS_HIGH_SPEED					0
#define USB_IS_FULL_SPEED					1
#define USB_SPEED_MASK					BIT(5)

#define USB_NORMAL_SIE_EP_MASK			0xF
#define USB_NORMAL_SIE_EP_SHIFT			4


//2 Special Option
#define USB_AGG_EN						BIT(3)

// 0; Use interrupt endpoint to upload interrupt pkt
// 1; Use bulk endpoint to upload interrupt pkt,
#define INT_BULK_SEL					BIT(4)



//2REG_C2HEVT_CLEAR
#define		C2H_EVT_HOST_CLOSE			0x00	// Set by driver and notify FW that the driver has read the C2H command message
#define		C2H_EVT_FW_CLOSE			0xFF	// Set by FW indicating that FW had set the C2H command message and it's not yet read by driver.


//2REG_MULTI_FUNC_CTRL(For RTL8723 Only)
#define	WL_HWPDN_EN				BIT0		// Enable GPIO[9] as WiFi HW PDn source
#define	WL_HWPDN_SL				BIT1		// WiFi HW PDn polarity control
#define	WL_FUNC_EN				BIT2		// WiFi function enable
#define	WL_HWROF_EN				BIT3		// Enable GPIO[9] as WiFi RF HW PDn source
#define	BT_HWPDN_EN				BIT16	// Enable GPIO[11] as BT HW PDn source
#define	BT_HWPDN_SL				BIT17	// BT HW PDn polarity control
#define	BT_FUNC_EN					BIT18	// BT function enable
#define	BT_HWROF_EN				BIT19	// Enable GPIO[11] as BT/GPS RF HW PDn source
#define	GPS_HWPDN_EN				BIT20	// Enable GPIO[10] as GPS HW PDn source
#define	GPS_HWPDN_SL				BIT21	// GPS HW PDn polarity control
#define	GPS_FUNC_EN				BIT22	// GPS function enable


//3 REG_LIFECTRL_CTRL
#define	HAL92C_EN_PKT_LIFE_TIME_BK		BIT3
#define	HAL92C_EN_PKT_LIFE_TIME_BE		BIT2
#define	HAL92C_EN_PKT_LIFE_TIME_VI		BIT1
#define	HAL92C_EN_PKT_LIFE_TIME_VO		BIT0

#define	HAL92C_MSDU_LIFE_TIME_UNIT		128		// in us, said by Tim.

//========================================================
// General definitions
//========================================================
//#if (HAL_8195A_USB == 1)
//#define LAST_ENTRY_OF_TX_PKT_BUFFER		255
//#else
#define LAST_ENTRY_OF_TX_PKT_BUFFER		176 // 22k 22528 bytes
//#endif

#define POLLING_LLT_THRESHOLD				20
//#if RTL8188E_FOR_MP_TEST == 1
//#define POLLING_READY_TIMEOUT_COUNT		3000
//#else
#define POLLING_READY_TIMEOUT_COUNT		1000
//#endif
// GPIO BIT
#define	HAL_8192C_HW_GPIO_WPS_BIT		BIT2

//----------------------------------------------------------------------------
//       8192C EEPROM/EFUSE share register definition.
//----------------------------------------------------------------------------

//====================================================
//			EEPROM/Efuse PG Offset for 88EE/88EU/88ES
//====================================================
#define	EEPROM_TX_PWR_INX_88E				0x10

#define	EEPROM_ChannelPlan_88E				0xB8
#define	EEPROM_XTAL_88E						0xB9
#define	EEPROM_THERMAL_METER_88E			0xBA
#define	EEPROM_IQK_LCK_88E					0xBB

#define	EEPROM_RF_BOARD_OPTION_88E			0xC1
#define	EEPROM_RF_FEATURE_OPTION_88E		0xC2
#define	EEPROM_RF_BT_SETTING_88E				0xC3
#define	EEPROM_VERSION_88E					0xC4
#define	EEPROM_CUSTOMERID_88E				0xC5
#define	EEPROM_RF_ANTENNA_OPT_88E			0xC9

// RTL88EE
#define	EEPROM_MAC_ADDR_88EE				0xD0
#define	EEPROM_VID_88EE						0xD6
#define	EEPROM_DID_88EE						0xD8
#define	EEPROM_SVID_88EE						0xDA
#define	EEPROM_SMID_88EE						0xDC

//RTL88EU
#define	EEPROM_MAC_ADDR_88EU				0xD7
#define	EEPROM_VID_88EU						0xD0
#define	EEPROM_PID_88EU						0xD2

// RTL88ES
#define	EEPROM_MAC_ADDR_88ES				0x11A




//====================================================
//			EEPROM/Efuse Value Type
//====================================================
#define EETYPE_TX_PWR							0x0

//
// Default Value for EEPROM or EFUSE!!!
//
#define EEPROM_Default_TSSI					0x0
#define EEPROM_Default_TxPowerDiff			0x0
#define EEPROM_Default_CrystalCap			0x5
#define EEPROM_Default_BoardType			0x02 // Default: 2X2, RTL8192CE(QFPN68)
#define EEPROM_Default_TxPower				0x1010
#define EEPROM_Default_HT2T_TxPwr			0x10

#define EEPROM_Default_LegacyHTTxPowerDiff	0x3
#define EEPROM_Default_ThermalMeter			0x12

#define EEPROM_Default_AntTxPowerDiff		0x0
#define EEPROM_Default_TxPwDiff_CrystalCap	0x5
#if defined(CONFIG_GSPI_HCI) || defined(CONFIG_SDIO_HCI)
#define EEPROM_Default_TxPowerLevel			0x25
#else	//for USB/PCIE
#define EEPROM_Default_TxPowerLevel			0x2A
#endif

#define EEPROM_Default_HT40_2SDiff			0x0
#define EEPROM_Default_HT20_Diff			2	// HT20<->40 default Tx Power Index Difference
#define EEPROM_Default_LegacyHTTxPowerDiff	0x3
#define EEPROM_Default_HT40_PwrMaxOffset	0
#define EEPROM_Default_HT20_PwrMaxOffset	0

#define 	EEPROM_Default_CrystalCap_88E 		0x20
#define	EEPROM_Default_ThermalMeter_88E	0x18

//New EFUSE deafult value
#define 	EEPROM_DEFAULT_24G_INDEX		0x2D
#define 	EEPROM_DEFAULT_24G_HT20_DIFF	0X02
#define 	EEPROM_DEFAULT_24G_OFDM_DIFF	0X04

#define 	EEPROM_DEFAULT_5G_INDEX			0X2A
#define 	EEPROM_DEFAULT_5G_HT20_DIFF		0X00
#define 	EEPROM_DEFAULT_5G_OFDM_DIFF		0X04

#define 	EEPROM_DEFAULT_DIFF				0XFE
#define	EEPROM_DEFAULT_CHANNEL_PLAN	0x7F
#define	EEPROM_DEFAULT_BOARD_OPTION	0x00
#define	EEPROM_DEFAULT_FEATURE_OPTION	0x00
#define	EEPROM_DEFAULT_BT_OPTION		0x10


// For debug
#define EEPROM_Default_PID					0x1234
#define EEPROM_Default_VID					0x5678
#define EEPROM_Default_CustomerID			0xAB
#define	EEPROM_Default_CustomerID_8188E		0x00
#define EEPROM_Default_SubCustomerID		0xCD
#define EEPROM_Default_Version				0

#define EEPROM_CHANNEL_PLAN_FCC				0x0
#define EEPROM_CHANNEL_PLAN_IC				0x1
#define EEPROM_CHANNEL_PLAN_ETSI				0x2
#define EEPROM_CHANNEL_PLAN_SPAIN			0x3
#define EEPROM_CHANNEL_PLAN_FRANCE			0x4
#define EEPROM_CHANNEL_PLAN_MKK				0x5
#define EEPROM_CHANNEL_PLAN_MKK1				0x6
#define EEPROM_CHANNEL_PLAN_ISRAEL			0x7
#define EEPROM_CHANNEL_PLAN_TELEC			0x8
#define EEPROM_CHANNEL_PLAN_GLOBAL_DOMAIN	0x9
#define EEPROM_CHANNEL_PLAN_WORLD_WIDE_13	0xA
#define EEPROM_CHANNEL_PLAN_NCC				0xB
#define EEPROM_USB_OPTIONAL1					0xE
#define EEPROM_CHANNEL_PLAN_BY_HW_MASK		0x80


#define EEPROM_CID_DEFAULT				0x0
#define EEPROM_CID_TOSHIBA					0x4
#define EEPROM_CID_CCX						0x10 // CCX test. By Bruce, 2009-02-25.
#define EEPROM_CID_QMI						0x0D
#define EEPROM_CID_WHQL 					0xFE // added by chiyoko for dtm, 20090108


#define	RTL_EEPROM_ID						0x8129

//-----------------------------------------------------
//
//	Redifine register definition for compatibility
//
//-----------------------------------------------------

// TODO: use these definition when using REG_xxx naming rule.
// NOTE: DO NOT Remove these definition. Use later.
#define ISR_88E				REG_HISR_88E

#endif //__RTL8188E_SPEC_H__

