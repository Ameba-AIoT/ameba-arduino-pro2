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
#ifndef __RTL8192E_SPEC_H__
#define __RTL8192E_SPEC_H__

#include <drv_conf.h>


#define	EEPROM_TX_PWR_INX_8192E				0x10

#define	EEPROM_ChannelPlan_8192E			0xB8
#define	EEPROM_XTAL_8192E					0xB9
#define	EEPROM_THERMAL_METER_8192E			0xBA
#define	EEPROM_IQK_LCK_8192E				0xBB
#define	EEPROM_2G_5G_PA_TYPE_8192E			0xBC
#define	EEPROM_2G_LNA_TYPE_GAIN_SEL_8192E	0xBD
#define	EEPROM_5G_LNA_TYPE_GAIN_SEL_8192E	0xBF

#define	EEPROM_RF_BOARD_OPTION_8192E		0xC1
#define	EEPROM_FEATURE_OPTION_8192E			0xC2 /* 0xC2 */
#define	EEPROM_RF_BT_SETTING_8192E			0xC3
#define	EEPROM_VERSION_8192E				0xC4
#define	EEPROM_CustomID_8192E				0xC5
#define	EEPROM_THERMAL_METER_8192E			0xBA
#define	EEPROM_TX_BBSWING_2G_8192E			0xC6
#define	EEPROM_TX_PWR_CALIBRATE_RATE_8192E	0xC8
#define	EEPROM_RF_ANTENNA_OPT_8192E			0xC9
#define	EEPROM_RFE_OPTION_8192E				0xCA
#define EEPROM_CUSTOMER_ID_8192E			0x7F
#define EEPROM_SUBCUSTOMER_ID_8192E			0x59

/* RTL8192EE */
#define EEPROM_MAC_ADDR_8192EE				0xD0
#define EEPROM_VID_8192EE					0xD6
#define EEPROM_DID_8192EE					0xD8
#define EEPROM_SVID_8192EE					0xDA
#define EEPROM_SMID_8192EE					0xDC

/* RTL8192EU */
#define EEPROM_MAC_ADDR_8192EU				0x107
#define EEPROM_VID_8192EU					0x100
#define EEPROM_PID_8192EU					0x102
#define EEPROM_PA_TYPE_8192EU				0xBC
#define EEPROM_LNA_TYPE_2G_8192EU			0xBD
#define EEPROM_USB_OPTIONAL_FUNCTION0_8192EU 0x0E

/* RTL8192ES */
#define	EEPROM_MAC_ADDR_8192ES				0x11A
#define EEPROM_Voltage_ADDR_8192E			0x8
#define EEPROM_PID__8192ES					0xF9
#define EEPROM_8192ES_PID_VALUE                                 0x01
//eeprom frankie from sd4
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

#define RTL_EEPROM_ID							0x8129
#define EEPROM_Default_TSSI						0x0
#define EEPROM_Default_BoardType				0x02
#define EEPROM_Default_ThermalMeter			0x12
#define EEPROM_Default_ThermalMeter_92SU		0x7
#define EEPROM_Default_ThermalMeter_88E		0x18
#define EEPROM_Default_ThermalMeter_8812		0x18
#define	EEPROM_Default_ThermalMeter_8192E			0x1A
#define	EEPROM_Default_ThermalMeter_8723B		0x18
#define	EEPROM_Default_ThermalMeter_8703B		0x18
#define	EEPROM_Default_ThermalMeter_8192E		0x18
#define EEPROM_Default_ThermalMeter_8814A		0x18


#define EEPROM_Default_CrystalCap				0x0
#define EEPROM_Default_CrystalCap_8723A		0x20
#define EEPROM_Default_CrystalCap_88E 			0x20
#define EEPROM_Default_CrystalCap_8812			0x20
#define EEPROM_Default_CrystalCap_8814			0x20
#define EEPROM_Default_CrystalCap_8192E			0x20
#define EEPROM_Default_CrystalCap_8723B			0x20
#define EEPROM_Default_CrystalCap_8703B			0x20
#define EEPROM_Default_CrystalCap_8192E			0x20
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
#ifdef CONFIG_PCI_HCI
#define EEPROM_Default_internalPA_SPDT_CC	0xA0
#else
#define EEPROM_Default_internalPA_SPDT_CC	0xFA
#endif
#define EEPROM_Default_PAType						0
#define EEPROM_Default_LNAType						0

//New EFUSE deafult value
#define EEPROM_DEFAULT_24G_INDEX			0x2D
#define EEPROM_DEFAULT_24G_HT20_DIFF		0X02
#define EEPROM_DEFAULT_24G_OFDM_DIFF	0X04

#define EEPROM_DEFAULT_5G_INDEX			0X2A
#define EEPROM_DEFAULT_5G_HT20_DIFF		0X00
#define EEPROM_DEFAULT_5G_OFDM_DIFF		0X04

#define EEPROM_DEFAULT_DIFF				0XFE
#define EEPROM_DEFAULT_CHANNEL_PLAN		0x7F
#define EEPROM_DEFAULT_BOARD_OPTION		0x00
#define EEPROM_DEFAULT_RFE_OPTION_8192E 0x03
#define EEPROM_DEFAULT_RFE_OPTION		0x04
#define EEPROM_DEFAULT_FEATURE_OPTION	0x00
#define EEPROM_DEFAULT_BT_OPTION			0x10


#define EEPROM_DEFAULT_TX_CALIBRATE_RATE	0x00

// PCIe related
#define	EEPROM_PCIE_DEV_CAP_01				0xE0 // Express device capability in PCIe configuration space, i.e., map to offset 0x74
#define	EEPROM_PCIE_DEV_CAP_02				0xE1



#define HAL_NAV_UPPER_UNIT_8192E		128		// micro-second

//-----------------------------------------------------
//
//	0x0000h ~ 0x00FFh	System Configuration
//
//-----------------------------------------------------
#define REG_RSV_CTRL_8192E				0x001C	// 3 Byte
#define REG_BT_WIFI_ANTENNA_SWITCH_8192E	0x0038
#define REG_HSISR_8192E					0x005c
#define REG_PAD_CTRL1_8192E		0x0064
#define REG_AFE_CTRL_4_8192E		0x0078
#define REG_HMEBOX_DBG_0_8192E	0x0088
#define REG_HMEBOX_DBG_1_8192E	0x008A
#define REG_HMEBOX_DBG_2_8192E	0x008C
#define REG_HMEBOX_DBG_3_8192E	0x008E
#define REG_HIMR0_8192E					0x00B0
#define REG_HISR0_8192E					0x00B4
#define REG_HIMR1_8192E					0x00B8
#define REG_HISR1_8192E					0x00BC
#define REG_PMC_DBG_CTRL2_8192E			0x00CC

//-----------------------------------------------------
//
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//
//-----------------------------------------------------
#define REG_C2HEVT_CMD_ID_8192E	0x01A0
#define REG_C2HEVT_CMD_LEN_8192E	0x01AE
#define REG_WOWLAN_WAKE_REASON 0x01C7
#define REG_WOWLAN_GTK_DBG1	0x630
#define REG_WOWLAN_GTK_DBG2	0x634

#define REG_HMEBOX_EXT0_8192E			0x01F0
#define REG_HMEBOX_EXT1_8192E			0x01F4
#define REG_HMEBOX_EXT2_8192E			0x01F8
#define REG_HMEBOX_EXT3_8192E			0x01FC

//-----------------------------------------------------
//
//	0x0200h ~ 0x027Fh	TXDMA Configuration
//
//-----------------------------------------------------

//-----------------------------------------------------
//
//	0x0280h ~ 0x02FFh	RXDMA Configuration
//
//-----------------------------------------------------
#define REG_RXDMA_CONTROL_8192E		0x0286 // Control the RX DMA.
#define REG_RXDMA_MODE_CTRL_8192E		0x0290

//-----------------------------------------------------
//
//	0x0300h ~ 0x03FFh	PCIe
//
//-----------------------------------------------------
#define	REG_PCIE_CTRL_REG_8192E		0x0300
#define	REG_INT_MIG_8192E				0x0304	// Interrupt Migration 
#define	REG_BCNQ_DESA_8192E			0x0308	// TX Beacon Descriptor Address
#define	REG_HQ_DESA_8192E				0x0310	// TX High Queue Descriptor Address
#define	REG_MGQ_DESA_8192E			0x0318	// TX Manage Queue Descriptor Address
#define	REG_VOQ_DESA_8192E			0x0320	// TX VO Queue Descriptor Address
#define	REG_VIQ_DESA_8192E				0x0328	// TX VI Queue Descriptor Address
#define	REG_BEQ_DESA_8192E			0x0330	// TX BE Queue Descriptor Address
#define	REG_BKQ_DESA_8192E			0x0338	// TX BK Queue Descriptor Address
#define	REG_RX_DESA_8192E				0x0340	// RX Queue	Descriptor Address
#define	REG_DBI_WDATA_8192E			0x0348	// DBI Write Data
#define	REG_DBI_RDATA_8192E			0x034C	// DBI Read Data
#define	REG_DBI_ADDR_8192E				0x0350	// DBI Address
#define	REG_DBI_FLAG_8192E				0x0352	// DBI Read/Write Flag
#define	REG_MDIO_WDATA_8192E		0x0354	// MDIO for Write PCIE PHY
#define	REG_MDIO_RDATA_8192E			0x0356	// MDIO for Reads PCIE PHY
#define	REG_MDIO_CTL_8192E			0x0358	// MDIO for Control
#define	REG_DBG_SEL_8192E				0x0360	// Debug Selection Register
#define	REG_PCIE_HRPWM_8192E			0x0361	//PCIe RPWM
#define	REG_PCIE_HCPWM_8192E			0x0363	//PCIe CPWM
#define	REG_PCIE_MULTIFET_CTRL_8192E	0x036A	//PCIE Multi-Fethc Control

//-----------------------------------------------------
//
//	0x0400h ~ 0x047Fh	Protocol Configuration
//
//-----------------------------------------------------
#define REG_TXPKTBUF_BCNQ_BDNY_8192E	0x0424
#define REG_TXPKTBUF_MGQ_BDNY_8192E	0x0425
#define REG_TXPKTBUF_WMAC_LBK_BF_HD_8192E	0x045D
#ifdef CONFIG_WOWLAN
#define REG_TXPKTBUF_IV_LOW             0x0484
#define REG_TXPKTBUF_IV_HIGH            0x0488
#endif
#define REG_AMPDU_BURST_MODE_8192E	0x04BC

//-----------------------------------------------------
//
//	0x0500h ~ 0x05FFh	EDCA Configuration
//
//-----------------------------------------------------
#define REG_SECONDARY_CCA_CTRL_8192E	0x0577

//-----------------------------------------------------
//
//	0x0600h ~ 0x07FFh	WMAC Configuration
//
//-----------------------------------------------------


//============================================================
// SDIO Bus Specification
//============================================================

//-----------------------------------------------------
// SDIO CMD Address Mapping
//-----------------------------------------------------

//-----------------------------------------------------
// I/O bus domain (Host)
//-----------------------------------------------------

//-----------------------------------------------------
// SDIO register
//-----------------------------------------------------
#define SDIO_REG_HIQ_FREEPG_8192E	0x20
#define SDIO_REG_MID_FREEPG_8192E	0x22
#define SDIO_REG_LOW_FREEPG_8192E	0x24
#define SDIO_REG_PUB_FREEPG_8192E	0x26
#define SDIO_REG_EXQ_FREEPG_8192E	0x28
#define SDIO_REG_AC_OQT_FREEPG_8192E	0x002A
#define SDIO_REG_NOAC_OQT_FREEPG_8192E	0x002B



//============================================================================
//	8188 Regsiter Bit and Content definition
//============================================================================

//2 HSISR
// interrupt mask which needs to clear
#define MASK_HSISR_CLEAR		(HSISR_GPIO12_0_INT |\
								HSISR_SPS_OCP_INT |\
								HSISR_RON_INT |\
								HSISR_PDNINT |\
								HSISR_GPIO9_INT)

//-----------------------------------------------------
//
//	0x0100h ~ 0x01FFh	MACTOP General Configuration
//
//-----------------------------------------------------


//-----------------------------------------------------
//
//	0x0200h ~ 0x027Fh	TXDMA Configuration
//
//-----------------------------------------------------

//-----------------------------------------------------
//
//	0x0280h ~ 0x02FFh	RXDMA Configuration
//
//-----------------------------------------------------
#define BIT_USB_RXDMA_AGG_EN	BIT(31)
#define RXDMA_AGG_MODE_EN		BIT(1)

#ifdef CONFIG_WOWLAN
#define RXPKT_RELEASE_POLL		BIT(16)
#define RXDMA_IDLE				BIT(17)
#define RW_RELEASE_EN			BIT(18)
#endif

//-----------------------------------------------------
//
//	0x0400h ~ 0x047Fh	Protocol Configuration
//
//-----------------------------------------------------

//----------------------------------------------------------------------------
//       8192E REG_CCK_CHECK						(offset 0x454)
//----------------------------------------------------------------------------
#define BIT_BCN_PORT_SEL		BIT5

//-----------------------------------------------------
//
//	0x0500h ~ 0x05FFh	EDCA Configuration
//
//-----------------------------------------------------

//-----------------------------------------------------
//
//	0x0600h ~ 0x07FFh	WMAC Configuration
//
//-----------------------------------------------------

#ifdef CONFIG_RTL8192E
#define EEPROM_RF_GAIN_OFFSET			0xC1
#endif

#define EEPROM_RF_GAIN_VAL				0x1F6
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

//----------------------------------------------------------------------------
//       8195 IMR/ISR bits						(offset 0xB0,  8bits)
//----------------------------------------------------------------------------
#define	IMR_DISABLED_8192E					0
// IMR DW0(0x00B0-00B3) Bit 0-31
#if 0//devin_li warning 
#define	IMR_TIMER2_8192E					BIT31		// Timeout interrupt 2
#define	IMR_TIMER1_8192E					BIT30		// Timeout interrupt 1	
#define	IMR_PSTIMEOUT_8192E				BIT29		// Power Save Time Out Interrupt
#define	IMR_GTINT4_8192E					BIT28		// When GTIMER4 expires, this bit is set to 1	
#define	IMR_GTINT3_8192E					BIT27		// When GTIMER3 expires, this bit is set to 1	
#define	IMR_TXBCN0ERR_8192E				BIT26		// Transmit Beacon0 Error			
#define	IMR_TXBCN0OK_8192E				BIT25		// Transmit Beacon0 OK			
#define	IMR_TSF_BIT32_TOGGLE_8192E		BIT24		// TSF Timer BIT32 toggle indication interrupt			
#define	IMR_BCNDMAINT0_8192E				BIT20		// Beacon DMA Interrupt 0			
#define	IMR_BCNDERR0_8192E				BIT16		// Beacon Queue DMA OK0			
#define	IMR_HSISR_IND_ON_INT_8192E		BIT15		// HSISR Indicator (HSIMR & HSISR is true, this bit is set to 1)
#define	IMR_BCNDMAINT_E_8192E			BIT14		// Beacon DMA Interrupt Extension for Win7			
#define	IMR_ATIMEND_8192E				BIT12		// CTWidnow End or ATIM Window End
#define	IMR_C2HCMD_8192E					BIT10		// CPU to Host Command INT Status, Write 1 clear	
#define	IMR_CPWM2_8192E					BIT9			// CPU power Mode exchange INT Status, Write 1 clear	
#define	IMR_CPWM_8192E					BIT8			// CPU power Mode exchange INT Status, Write 1 clear	
#define	IMR_HIGHDOK_8192E				BIT7			// High Queue DMA OK	
#define	IMR_MGNTDOK_8192E				BIT6			// Management Queue DMA OK	
#define	IMR_BKDOK_8192E					BIT5			// AC_BK DMA OK		
#define	IMR_BEDOK_8192E					BIT4			// AC_BE DMA OK	
#define	IMR_VIDOK_8192E					BIT3			// AC_VI DMA OK		
#define	IMR_VODOK_8192E					BIT2			// AC_VO DMA OK	
#define	IMR_RDU_8192E					BIT1			// Rx Descriptor Unavailable	
#define	IMR_ROK_8192E					BIT0			// Receive DMA OK

// IMR DW1(0x00B4-00B7) Bit 0-31
#define	IMR_BCNDMAINT7_8192E				BIT27		// Beacon DMA Interrupt 7
#define	IMR_BCNDMAINT6_8192E				BIT26		// Beacon DMA Interrupt 6
#define	IMR_BCNDMAINT5_8192E				BIT25		// Beacon DMA Interrupt 5
#define	IMR_BCNDMAINT4_8192E				BIT24		// Beacon DMA Interrupt 4
#define	IMR_BCNDMAINT3_8192E				BIT23		// Beacon DMA Interrupt 3
#define	IMR_BCNDMAINT2_8192E				BIT22		// Beacon DMA Interrupt 2
#define	IMR_BCNDMAINT1_8192E				BIT21		// Beacon DMA Interrupt 1
#define	IMR_BCNDOK7_8192E					BIT20		// Beacon Queue DMA OK Interrup 7
#define	IMR_BCNDOK6_8192E					BIT19		// Beacon Queue DMA OK Interrup 6
#define	IMR_BCNDOK5_8192E					BIT18		// Beacon Queue DMA OK Interrup 5
#define	IMR_BCNDOK4_8192E					BIT17		// Beacon Queue DMA OK Interrup 4
#define	IMR_BCNDOK3_8192E					BIT16		// Beacon Queue DMA OK Interrup 3
#define	IMR_BCNDOK2_8192E					BIT15		// Beacon Queue DMA OK Interrup 2
#define	IMR_BCNDOK1_8192E					BIT14		// Beacon Queue DMA OK Interrup 1
#define	IMR_ATIMEND_E_8192E				BIT13		// ATIM Window End Extension for Win7
#define	IMR_TXERR_8192E					BIT11		// Tx Error Flag Interrupt Status, write 1 clear.
#define	IMR_RXERR_8192E					BIT10		// Rx Error Flag INT Status, Write 1 clear
#define	IMR_TXFOVW_8192E					BIT9			// Transmit FIFO Overflow
#define	IMR_RXFOVW_8192E					BIT8			// Receive FIFO Overflow
#endif //devin_li warning

#ifdef CONFIG_PCI_HCI
//#define IMR_RX_MASK		(IMR_ROK_8192E|IMR_RDU_8192E|IMR_RXFOVW_8192E)
#define IMR_TX_MASK			(IMR_VODOK_8192E|IMR_VIDOK_8192E|IMR_BEDOK_8192E|IMR_BKDOK_8192E|IMR_MGNTDOK_8192E|IMR_HIGHDOK_8192E)

#define RT_BCN_INT_MASKS	(IMR_BCNDMAINT0_8192E | IMR_TXBCN0OK_8192E | IMR_TXBCN0ERR_8192E | IMR_BCNDERR0_8192E)

#define RT_AC_INT_MASKS	(IMR_VIDOK_8192E | IMR_VODOK_8192E | IMR_BEDOK_8192E|IMR_BKDOK_8192E)
#endif

//========================================================
// General definitions
//========================================================
#define GET_PG_KFREE_ON_8192E(_pg_m)			LE_BITS_TO_1BYTE(((u8 *)(_pg_m)) + 0xC1, 4, 1)
#define GET_PG_KFREE_THERMAL_K_ON_8192E(_pg_m)	LE_BITS_TO_1BYTE(((u8 *)(_pg_m)) + 0xC8, 5, 1)

#define PPG_BB_GAIN_2G_TXA_OFFSET_8192E	0xEE
#define PPG_THERMAL_OFFSET_8192E		0xEF

#endif /* __RTL8192E_SPEC_H__ */

