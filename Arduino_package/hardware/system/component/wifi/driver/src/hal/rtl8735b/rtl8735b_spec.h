/******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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
#ifndef __RTL8735B_SPEC_H__
#define __RTL8735B_SPEC_H__

#include <hal_halmac.h>	// HALMAC_EFUSE_SIZE_8735B

#ifndef BIT
#define BIT(x)		((u32)1 << (x))
#endif

//#define EFUSE_MAP_SIZE		HALMAC_EFUSE_SIZE_8735B

#define MACID_NUM_8735B	128
#define NSS_NUM_8735B		1
#define HW_PORT_NUM_8735B	5

/*
 * MAC Register definition
 */
//#define REG_AFE_XTAL_CTRL			REG_AFE_CTRL1_8735B	/* hal_com.c & phydm */
//#define REG_AFE_PLL_CTRL			REG_AFE_CTRL2_8735B	/* hal_com.c & phydm */
//#define REG_MAC_PHY_CTRL			REG_AFE_CTRL3_8735B	/* phydm only */
#define REG_LEDCFG0					REG_LED_CFG_8735B	/* rtw_mp.c */
#define MSR							(REG_CR_8735B + 2)	/* rtw_mp.c */
#define MSR1						REG_CR_EXT_8735B	/* rtw_mp.c & hal_com.c */
#define REG_C2HEVT_MSG_NORMAL		0x1A0			/* hal_com.c */
#define REG_C2HEVT_CLEAR			0x1AF			/* hal_com.c */
#define REG_BCN_CTRL_1				REG_BCN_CTRL_CLINT0_8735B/* hal_com.c */
#define REG_TSFTR1					REG_FREERUN_CNT_8735B	/* hal_com.c */
#define REG_RXFLTMAP2				REG_RXFLTMAP2_8735B	/* rtw_mp.c */
#define REG_WOWLAN_WAKE_REASON		0x01C7
#define REG_WOWLAN_WAKE_PATTERN_INDEX		0x01C5

/* RXERR_RPT, for rtw_mp.c */
#define RXERR_TYPE_OFDM_PPDU		0
#define RXERR_TYPE_OFDM_FALSE_ALARM	2
#define RXERR_TYPE_OFDM_MPDU_OK		0
#define RXERR_TYPE_OFDM_MPDU_FAIL	1
#define RXERR_TYPE_CCK_PPDU		3
#define RXERR_TYPE_CCK_FALSE_ALARM	5
#define RXERR_TYPE_CCK_MPDU_OK		3
#define RXERR_TYPE_CCK_MPDU_FAIL	4
#define RXERR_TYPE_HT_PPDU		8
#define RXERR_TYPE_HT_FALSE_ALARM	9
#define RXERR_TYPE_HT_MPDU_TOTAL	6
#define RXERR_TYPE_HT_MPDU_OK		6
#define RXERR_TYPE_HT_MPDU_FAIL		7
#define RXERR_TYPE_RX_FULL_DROP		10

#define RXERR_COUNTER_MASK		BIT_MASK_RPT_COUNTER_8735B
#define RXERR_RPT_RST			BIT_RXERR_RPT_RST_8735B
#define _RXERR_RPT_SEL(type)		(BIT_RXERR_RPT_SEL_V1_3_0_8735B(type) \
		| ((type & 0x10) ? BIT_RXERR_RPT_SEL_V1_4_8735B : 0))

/*
 * BB Register definition
 */

/* Page1(0x100) */
#define bBBResetB					0x100

/* Page8(0x800) */
#define bCCKEn						0x1000000
#define bOFDMEn						0x2000000
/* Reg 0x80C rFPGA0_TxGainStage */
#define bXBTxAGC						0xF00
#define bXCTxAGC						0xF000
#define bXDTxAGC						0xF0000

/* PageA(0xA00) */
#define bCCKBBMode					0x3

#define bCCKScramble					0x8
#define bCCKTxRate					0x3000

/* General */
#define bMaskByte0		0xFF		/* mp, rtw_odm.c & phydm */
#define bMaskByte1		0xFF00		/* hal_mp.c & phydm */
#define bMaskByte2		0xFF0000	/* hal_mp.c & phydm */
#define bMaskByte3		0xFF000000	/* hal_mp.c & phydm */
#define bMaskHWord		0xFFFF0000	/* hal_com.c, rtw_mp.c */
#define bMaskLWord		0x0000FFFF	/* mp, hal_com.c & phydm */
#define bMaskDWord		0xFFFFFFFF	/* mp, hal, rtw_odm.c & phydm */
#define bMaskH3Bytes		0xffffff00

#define bEnable			0x1		/* hal_mp.c, rtw_mp.c */
#define bDisable			0x0		/* rtw_mp.c */

#define MAX_STALL_TIME		50		/* unit: us, hal_com_phycfg.c */

#define Rx_Smooth_Factor		20		/* phydm only */

/*
 * RF Register definition
 */
#define RF_AC			0x00
#define RF_AC_Jaguar		0x00	/* hal_mp.c */
#define RF_CHNLBW		0x18	/* rtl8735b_phy.c */
#define RF_0x52			0x52

struct hw_port_reg {
	u32 net_type;	/*reg_offset*/
	u8 net_type_shift;
	u32 macaddr;	/*reg_offset*/
	u32 bssid;	/*reg_offset*/
	u32 bcn_ctl;			/*reg_offset*/
	u32 tsf_rst;			/*reg_offset*/
	u8 tsf_rst_bit;
	u32 bcn_space;		/*reg_offset*/
	u8 bcn_space_shift;
	u16 bcn_space_mask;
};

/* ****************************************************
 *	EEPROM/Efuse PG Offset
 * **************************************************** */
// Efuse logical offset
#define	EEPROM_TX_PWR_INX_8735B				0x20
#define	EEPROM_CHANNEL_PLAN_8735B			0xC8
#define	EEPROM_XTAL_8735B					0xC9
#define	EEPROM_THERMAL_METER_8735B			0xCA
#define	EEPROM_IQK_LCK_8735B				0xCB
#define	EEPROM_2G_5G_PA_TYPE_8735B			0xCC
#define	EEPROM_2G_LNA_TYPE_GAIN_SEL_AB_8735B	0xCD
#define	EEPROM_2G_LNA_TYPE_GAIN_SEL_CD_8735B	0xCE
#define	EEPROM_5G_LNA_TYPE_GAIN_SEL_AB_8735B	0xCF
#define	EEPROM_5G_LNA_TYPE_GAIN_SEL_CD_8735B	0x130

#define	EEPROM_MAC_ADDR_8735B				0x11A
#define	EEPROM_BT_MAC_ADDR_8735B			0x194

#define	EEPROM_RF_BOARD_OPTION_8735B		0x131
#define	EEPROM_FEATURE_OPTION_8735B			0x132
#define	EEPROM_RF_BT_SETTING_8735B			0x133	// Antenna Setting
#define	EEPROM_VERSION_8735B				0x134
#define	EEPROM_CUSTOMER_ID_8735B			0x135
#define	EEPROM_TX_BBSWING_2G_8735B			0x136
#define	EEPROM_TX_BBSWING_5G_8735B			0x137
#define	EEPROM_TX_PWR_CALIBRATE_RATE_8735B	0x138
#define	EEPROM_RF_ANTENNA_OPT_8735B			0x139
#define	EEPROM_RFE_OPTION_8735B				0x13A
#define EEPROM_COUNTRY_CODE_8735B			0x13B

// Efuse physical offset
#define EEPROM_RF_OFFSET_5G_RX_LNA_8735B	0x1CC

//EFUSE deafult value

#define RTL_EEPROM_ID						0x8735

#define EEPROM_DEFAULT_24G_INDEX			0x54
#define EEPROM_DEFAULT_24G_HT20_DIFF		0X02	// 0x2B[7:4]
#define EEPROM_DEFAULT_24G_OFDM_DIFF		0X04	// 0x2B[3:0]

#define EEPROM_DEFAULT_5G_INDEX				0X54
#define EEPROM_DEFAULT_5G_HT20_DIFF			0X00	// 0x40[7:4], Difference between BW20-1s and BW40-1s
#define EEPROM_DEFAULT_5G_OFDM_DIFF			0X00	// 0x40[3:0], Difference between OFDM-1Tx and BW40-1s

#define EEPROM_DEFAULT_5G_HT80_DIFF			0X04	// 0x46[7:4], Difference between BW80-1s and BW40-1s, -8~7
#define EEPROM_DEFAULT_5G_HT160_DIFF		0X0F	// 0x46[3:0], Difference between BW160-1s and BW80-1s, -8~7
#define EEPROM_DEFAULT_DIFF					0XFE

#define EEPROM_DEFAULT_CHANNEL_PLAN			0x7F	// 0xC8
#define EEPROM_DEFAULT_CRYSTALCAP			0x3F	// 0xC9
#define EEPROM_DEFAULT_THERMALMETER			0x1A	// 0xCA

#define EEPROM_DEFAULT_PA_TYPE				0x00	// 0xCC
#define EEPROM_DEFAULT_LNA_TYPE				0x00	// 0xCD, 0xCE

#define EEPROM_DEFAULT_BOARD_OPTION			0x00	// 0x131, 0: refer to Power by rate table, 1: refer to Power by rate table and Power limit table to take the smaller index value, 2: Don't refer to Power by rate table
#define EEPROM_DEFAULT_FEATURE_OPTION		0x00	// 0x132
#define EEPROM_DEFAULT_BT_OPTION			0x10	// 0x133, Antenna setting
#define EEPROM_DEFAULT_RFE_OPTION			0x00	// 0x13A

#define EEPROM_DEFAULT_TX_CALIBRATE_RATE	0x40	// 0x138[7:4], 0x4h ~ 0x7h for power tracking by TSSI

#ifdef CONFIG_WOWLAN
#define REG_TXPKTBUF_IV_LOW             0x0484
#define REG_TXPKTBUF_IV_HIGH            0x0488
#endif

#endif /* __RTL8192E_SPEC_H__ */
