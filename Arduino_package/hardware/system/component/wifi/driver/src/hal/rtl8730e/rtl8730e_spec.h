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
#ifndef __RTL8730E_SPEC_H__
#define __RTL8730E_SPEC_H__

#include <drv_conf.h>

#ifndef BIT
#define BIT(x)		((u32)1 << (x))
#endif

#define HAL_NAV_UPPER_UNIT_8723B		128		// micro-second

#ifdef CONFIG_WOWLAN
#define REG_WOWLAN_WAKE_REASON 0x01C7
#endif


#define REG_TXPKTBUF_IV_LOW             0x0484
#define REG_TXPKTBUF_IV_HIGH            0x0488


#define	IMR_BCNDERR7_8730E				BIT31		// Beacon Queue DMA Error
#define	IMR_BCNDERR6_8730E				BIT30		// Beacon Queue DMA Error
#define	IMR_BCNDERR5_8730E				BIT29		// Beacon Queue DMA Error
#define	IMR_BCNDERR4_8730E				BIT28		// Beacon Queue DMA Error
#define	IMR_BCNDERR3_8730E				BIT27		// Beacon Queue DMA Error
#define	IMR_BCNDERR2_8730E				BIT26		// Beacon Queue DMA Error
#define	IMR_BCNDERR1_8730E				BIT25		// Beacon Queue DMA Error
#define	IMR_BCNDERR0_8730E				BIT24		// Beacon Queue DMA Error
#define	IMR_BCNDMAOK7_8730E				BIT23		// Beacon DMA OK Interrupt 7
#define	IMR_BCNDMAOK6_8730E				BIT22		// Beacon DMA OK Interrupt 6
#define	IMR_BCNDMAOK5_8730E				BIT21		// Beacon DMA OK Interrupt 5
#define	IMR_BCNDMAOK4_8730E				BIT20		// Beacon DMA OK Interrupt 4
#define	IMR_BCNDMAOK3_8730E				BIT19		// Beacon DMA OK Interrupt 3
#define	IMR_BCNDMAOK2_8730E				BIT18		// Beacon DMA OK Interrupt 2
#define	IMR_BCNDMAOK1_8730E				BIT17		// Beacon DMA OK Interrupt 1
#define	IMR_BCNDMAOK0_8730E				BIT16		// Beacon DMA OK Interrupt 0
#define	IMR_H7DOK_8730E					BIT15		// High Queue DMA OK Interrup 7
#define	IMR_H6DOK_8730E					BIT14		// High Queue DMA OK Interrup 6
#define	IMR_H5DOK_8730E					BIT13		// High Queue DMA OK Interrup 5
#define	IMR_H4DOK_8730E					BIT12		// High Queue DMA OK Interrup 4
#define	IMR_H3DOK_8730E					BIT11		// High Queue DMA OK Interrup 3
#define	IMR_H2DOK_8730E					BIT10		// High Queue DMA OK Interrup 2
#define	IMR_H1DOK_8730E					BIT9		// High Queue DMA OK Interrup 1
#define	IMR_H0DOK_8730E					BIT8		// High Queue DMA OK Interrup 1
#define	IMR_MGNTDOK_8730E				BIT6			// Management Queue DMA OK	
#define	IMR_BKDOK_8730E                 BIT5			// AC_BK DMA OK		
#define	IMR_BEDOK_8730E                 BIT4			// AC_BE DMA OK	
#define	IMR_VIDOK_8730E                 BIT3			// AC_VI DMA OK		
#define	IMR_VODOK_8730E                 BIT2			// AC_VO DMA OK	
#define	IMR_RDU_8730E                   BIT1			// Rx Descriptor Unavailable	
#define	IMR_ROK_8730E                   BIT0			// Receive DMA OK

#endif

//====================================================
//			EEPROM/Efuse PG Offset for 8730E
//====================================================
// 0x10 ~ 0x63 = TX power area.
#define	EEPROM_TX_PWR_INX_8730E				0x20
#define	EEPROM_ChannelPlan_8730E			0xC8
#define	EEPROM_XTAL_8730E					0xC9
#define	EEPROM_THERMAL_METER_8730E			0xCA

#define	EEPROM_IQK_LCK_8730E				0xCB
#define	EEPROM_2G_5G_PA_TYPE_8730E			0xCC
#define	EEPROM_2G_LNA_TYPE_GAIN_SEL_8730E	0xCD
#define	EEPROM_5G_LNA_TYPE_GAIN_SEL_8730E	0xCE

#define	EEPROM_RF_BOARD_OPTION_8730E		0x131

#define	EEPROM_FEATURE_OPTION_8730E			0x132
#define	EEPROM_RF_BT_SETTING_8730E			0x133

#define	EEPROM_VERSION_8730E				0x134
#define	EEPROM_CustomID_8730E				0x135

#define	EEPROM_TX_BBSWING_2G_8730E			0x136
#define	EEPROM_TX_PWR_CAL_RATE_8730E		0x138
#define	EEPROM_RF_ANTENNA_OPT_8730E			0x139
#define	EEPROM_RFE_OPTION_8730E				0x13A

//RTL8723BU
#define EEPROM_MAC_ADDR_8723BU				0x107
#define EEPROM_VID_8723BU					0x100
#define EEPROM_PID_8723BU					0x102
#define EEPROM_PA_TYPE_8723BU				0xBC
#define EEPROM_LNA_TYPE_2G_8723BU			0xBD

//RTL8723BS
#define	EEPROM_MAC_ADDR_8730E				0x11A

#define EEPROM_Voltage_ADDR_8723B			0x8

#define EEPROM_TX_KFREE_8730E				0xEE

#define EEPROM_THERMAL_OFFSET_8730E	       	0xEF

#define EEPROM_PACKAGE_TYPE_8730E			0x1F8

//====================================================
//			EEPROM/Efuse Value Type
//====================================================
#define EETYPE_TX_PWR							0x0
//====================================================
//			EEPROM/Efuse Default Value
//====================================================
#define EEPROM_CID_DEFAULT					0x0
#define EEPROM_CID_DEFAULT_EXT				0xFF // Reserved for Realtek
#define EEPROM_CID_TOSHIBA						0x4
#define EEPROM_CID_CCX							0x10
#define EEPROM_CID_QMI							0x0D
#define EEPROM_CID_WHQL 						0xFE

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
#define EEPROM_CHANNEL_PLAN_NCC_TAIWAN		0xB
#define EEPROM_CHANNEL_PLAN_CHIAN			0XC
#define EEPROM_CHANNEL_PLAN_SINGAPORE_INDIA_MEXICO  0XD
#define EEPROM_CHANNEL_PLAN_KOREA			0xE
#define EEPROM_CHANNEL_PLAN_TURKEY              	0xF
#define EEPROM_CHANNEL_PLAN_JAPAN                 	0x10
#define EEPROM_CHANNEL_PLAN_FCC_NO_DFS		0x11
#define EEPROM_CHANNEL_PLAN_JAPAN_NO_DFS	0x12
#define EEPROM_CHANNEL_PLAN_WORLD_WIDE_5G	0x13
#define EEPROM_CHANNEL_PLAN_TAIWAN_NO_DFS 	0x14

#define EEPROM_USB_OPTIONAL1					0xE
#define EEPROM_CHANNEL_PLAN_BY_HW_MASK		0x80

#define RTL_EEPROM_ID							0x8730
#define EEPROM_Default_TSSI						0x0
#define EEPROM_Default_BoardType				0x02
#define EEPROM_Default_ThermalMeter			0x12
#define EEPROM_Default_ThermalMeter_92SU		0x7
#define EEPROM_Default_ThermalMeter_88E		0x18
#define EEPROM_Default_ThermalMeter_8812		0x18
#define	EEPROM_Default_ThermalMeter_8192E			0x1A
#define	EEPROM_Default_ThermalMeter_8723B		0x18
#define	EEPROM_Default_ThermalMeter_8730E		0x1A


#define EEPROM_Default_CrystalCap				0x0
#define EEPROM_Default_CrystalCap_8723B			0x20
#define EEPROM_Default_CrystalCap_8730E			0x38
#define EEPROM_Default_CrystalFreq				0x0
#define EEPROM_Default_TxPowerLevel_92C		0x22
#define EEPROM_Default_TxPowerLevel_2G			0x2C
#define EEPROM_Default_TxPowerLevel_5G			0x22
#define EEPROM_Default_TxPowerLevel			0x22
#define EEPROM_Default_HT40_2SDiff				0x0
#define EEPROM_Default_HT20_Diff				2
#define EEPROM_Default_LegacyHTTxPowerDiff		0x3
#define EEPROM_Default_LegacyHTTxPowerDiff_92C	0x3
#define EEPROM_Default_LegacyHTTxPowerDiff_92D	0x4
#define EEPROM_Default_HT40_PwrMaxOffset		0
#define EEPROM_Default_HT20_PwrMaxOffset		0

#define EEPROM_Default_PID						0x1234
#define EEPROM_Default_VID						0x5678
#define EEPROM_Default_CustomerID				0xAB
#define EEPROM_Default_CustomerID_8188E		0x00
#define EEPROM_Default_SubCustomerID			0xCD
#define EEPROM_Default_Version					0

#define EEPROM_Default_externalPA_C9		0x00
#define EEPROM_Default_externalPA_CC		0xFF
#define EEPROM_Default_internalPA_SP3T_C9	0xAA
#define EEPROM_Default_internalPA_SP3T_CC	0xAF
#define EEPROM_Default_internalPA_SPDT_C9	0xAA
#define EEPROM_Default_internalPA_SPDT_CC	0xFA
#define EEPROM_Default_PAType						0
#define EEPROM_Default_LNAType						0

//New EFUSE deafult value
#define EEPROM_DEFAULT_24G_CCK_INDEX		0x40
#define EEPROM_DEFAULT_24G_40M_INDEX		0x40
#define EEPROM_DEFAULT_24G_HT20_DIFF		0X00
#define EEPROM_DEFAULT_24G_OFDM_DIFF		0X02

#define EEPROM_DEFAULT_5G_INDEX				0X44
#define EEPROM_DEFAULT_5G_HT20_DIFF			0X00
#define EEPROM_DEFAULT_5G_OFDM_DIFF			0X04

#define EEPROM_DEFAULT_DIFF					0XFE
#define EEPROM_DEFAULT_CHANNEL_PLAN			0x7F
#define EEPROM_DEFAULT_BOARD_OPTION			0x01	// Enable power by rate and power limit
#define EEPROM_DEFAULT_RFE_OPTION			0x04
#define EEPROM_DEFAULT_FEATURE_OPTION		0x00
#define EEPROM_DEFAULT_BT_OPTION			0x10
#define EEPROM_DEFAULT_TX_CALIBRATE_RATE	0x00

