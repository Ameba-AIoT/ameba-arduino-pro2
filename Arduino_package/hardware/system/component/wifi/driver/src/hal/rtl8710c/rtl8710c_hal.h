/******************************************************************************
 *
 * Copyright(c) 2016 Realtek Corporation. All rights reserved.
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
#ifndef _RTL8710C_HAL_H_
#define _RTL8710C_HAL_H_

#include <osdep_service.h>		/* BIT(x) */
#if defined(RTW_HALMAC)
#include "halmac_api.h"	/* MAC REG definition */
#endif
#include "hal_data.h"
#include "hal8710c_fw.h"
#include "rtl8710c/rtl8710c_spec.h"
#include "rtl8710c/rtl8710c_dm.h"
#include "rtl8710c/rtl8710c_hal_efuse.h"
#include "rtl8710c/rtl8710c.h"
#include "phydm_precomp.h"
#ifdef CONFIG_BT_COEXIST_SOC
#include "rtl8710c/rtl8710c_btcoex.h"
#endif
#include "rtl8710c/rtl8710c_xmit.h"
#if !defined(RTW_HALMAC)
#include "rtl8710c/hal_pwr_seq_8710c.h"
#include <hal_com_h2c.h>
#include "rtl8710c/rtl8710c_pmu_cmd.h"
#endif

#ifdef CONFIG_SUPPORT_TRX_SHARED
#define FIFO_BLOCK_SIZE		32768 /*@Block size = 32K*/
#define RX_FIFO_EXPANDING	(1 * FIFO_BLOCK_SIZE)
#else
#define RX_FIFO_EXPANDING	0
#endif

#define GET_RF_TYPE(priv)			(GET_HAL_DATA(priv)->rf_type)

#define PHY_CFG_DCT_2G_A_P		"2g_a_p"
#define PHY_CFG_DCT_2G_A_N		"2g_a_n"
#define PHY_CFG_DCT_2G_CCK_A_P	"2g_cck_a_p"
#define PHY_CFG_DCT_2G_CCK_A_N	"2g_cck_a_n"

#if !defined(RTW_HALMAC)
// for 8710C
// TX 16K, RX 12K, Page size 128B for TX, 8B for RX
#define PAGE_SIZE_TX_8710C                  128
#define PAGE_SIZE_RX_8710C                  8

#define TX_FIFO_SIZE_8710C                  0x4000 //16K, only the last 8K can keep data in power-gated mode
#define TX_FIFO_MAX_PAGE_IDX_8710C          (TX_FIFO_SIZE_8710C/PAGE_SIZE_TX_8710C - 1) //0x0~0x7F, 0x40 ~ 0x7F is retention memory
#define RX_DMA_SIZE_8710C                   0x3000	// 12K
#define RX_DMA_RESERVED_SIZE_8710C          0x80	// 128B, reserved for tx report
#define RX_DMA_BOUNDARY_8710C               (RX_DMA_SIZE_8710C - RX_DMA_RESERVED_SIZE_8710C - 1)

// Note: We will divide number of page equally for each queue other than public queue!

//For General Reserved Page Number(Beacon Queue is reserved page)
//Beacon:2, PS-Poll:1, Null Data:1,Qos Null Data:1,BT Qos Null Data:1
#ifdef CONFIG_WLAN_HAL_TEST
#define BCNQ_PAGE_NUM_8710C             0x00
#else
#define BCNQ_PAGE_NUM_8710C             0x08
#endif

#ifdef CONFIG_CONCURRENT_MODE
#define BCNQ1_PAGE_NUM_8710C            0x04
#else
#define BCNQ1_PAGE_NUM_8710C            0x00
#endif

//For WoWLan , more reserved page
//ARP Rsp:1, RWC:1, GTK Info:1,GTK RSP:2,GTK EXT MEM:2
#ifdef CONFIG_WOWLAN
#define WOWLAN_PAGE_NUM_8710C           0x07
#else
#define WOWLAN_PAGE_NUM_8710C           0x00
#endif

//For LPS POFF , more reserved page
//only the last 8KB of
//BB&MAC parameter:24, RADIOA paramter:14, LCK:14
#define LPS_POFF_BBMAC_PAGE_NUM_8710C           0x00
#define LPS_POFF_RADIOA_PAGE_NUM_8710C           0x00
#define LPS_POFF_LCK_PAGE_NUM_8710C           0x00

#ifdef CONFIG_WLAN_HAL_TEST
#define TX_TOTAL_PAGE_NUMBER_8710C    (0x78 - BCNQ_PAGE_NUM_8710C - BCNQ1_PAGE_NUM_8710C - WOWLAN_PAGE_NUM_8710C)
#define TX_PAGE_BOUNDARY_8710C          (TX_TOTAL_PAGE_NUMBER_8710C + 1)
#else
#define TX_TOTAL_PAGE_NUMBER_8710C  (TX_FIFO_MAX_PAGE_IDX_8710C - BCNQ_PAGE_NUM_8710C - BCNQ1_PAGE_NUM_8710C - WOWLAN_PAGE_NUM_8710C)
#define TX_PAGE_BOUNDARY_8710C          (TX_TOTAL_PAGE_NUMBER_8710C + 1)
#endif

#define WMM_NORMAL_TX_TOTAL_PAGE_NUMBER TX_TOTAL_PAGE_NUMBER_8710C
#define WMM_NORMAL_TX_PAGE_BOUNDARY		(WMM_NORMAL_TX_TOTAL_PAGE_NUMBER + 1)

// For Normal Chip Setting
// (HPQ + LPQ + NPQ + PUBQ) shall be TX_TOTAL_PAGE_NUMBER_8710C
#ifdef CONFIG_WLAN_HAL_TEST
#define NORMAL_PAGE_NUM_HPQ_8710C		0x10
#define NORMAL_PAGE_NUM_LPQ_8710C		0x10
#define NORMAL_PAGE_NUM_NPQ_8710C		0x10
#else
#define NORMAL_PAGE_NUM_HPQ_8710C		0x0C
#define NORMAL_PAGE_NUM_LPQ_8710C		0x02
#define NORMAL_PAGE_NUM_NPQ_8710C		0x02
#endif

#ifdef CONFIG_WLAN_HAL_TEST
#define WMM_NORMAL_PAGE_NUM_HPQ_8710C   0x10
#define WMM_NORMAL_PAGE_NUM_LPQ_8710C   0x10
#define WMM_NORMAL_PAGE_NUM_NPQ_8710C   0x10
#else
// Note: For Normal Chip Setting, modify later
#define WMM_NORMAL_PAGE_NUM_HPQ_8710C   0x30
#define WMM_NORMAL_PAGE_NUM_LPQ_8710C   0x20
#define WMM_NORMAL_PAGE_NUM_NPQ_8710C   0x20
#endif

#define WriteLE1Byte(_ptr, _val) WriteEF1Byte(_ptr, _val)
#define WriteLE2Byte(_ptr, _val) WriteEF2Byte(_ptr, _val)

// _PWR_MOD_CMD_0x20
#define SET_H2CCMD_PWRMODE_PARM_MODE(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE(__pH2CCmd, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_RLBM(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE((__pH2CCmd)+1, 0, 4, __Value)
#define SET_H2CCMD_PWRMODE_PARM_SMART_PS(__pH2CCmd, __Value)		SET_BITS_TO_LE_1BYTE((__pH2CCmd)+1, 4, 4, __Value)
#define SET_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+2, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+3, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_PWR_STATE(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+4, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_BYTE5(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+5, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_TDMA_SLOT_LEN(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+7, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_TDMA_PERIOD_LEN_1(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+8, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_TDMA_PERIOD_LEN_2(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+9, 0, 8, __Value)
#define SET_H2CCMD_PWRMODE_PARM_TDMA_PERIOD_LEN_3(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE((__pH2CCmd)+10, 0, 8, __Value)

// _PS_TUNE_PARAM_CMD_0x21
#define SET_H2CCMD_PSTUNE_PARM_BCN_TO_LIMIT(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE(__pH2CCmd, 0, 8, __Value)
#define SET_H2CCMD_PSTUNE_PARM_DTIM_TIMEOUT(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE(__pH2CCmd+1, 0, 8, __Value)
#define SET_H2CCMD_PSTUNE_PARM_ADOPT(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE(__pH2CCmd+2, 0, 1, __Value)
#define SET_H2CCMD_PSTUNE_PARM_PS_TIMEOUT(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE(__pH2CCmd+2, 1, 7, __Value)
#define SET_H2CCMD_PSTUNE_PARM_DTIM_PERIOD(__pH2CCmd, __Value)			SET_BITS_TO_LE_1BYTE(__pH2CCmd+3, 0, 8, __Value)
#define SET_H2CCMD_PSTUNE_PARM_NULL0_RETRY_LIMIT(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE(__pH2CCmd+4, 0, 5, __Value)
#define SET_H2CCMD_PSTUNE_PARM_FIX_DELAY_FORWARD(__pH2CCmd, __Value)	SET_BITS_TO_LE_1BYTE(__pH2CCmd+4, 5, 1, __Value)

#define H2C_PSTUNEPARAM_LEN_8710C		5
#endif //!defined(RTW_HALMAC)

/* MP Functions */
#ifdef CONFIG_MP_INCLUDED
void rtl8710c_phy_init_haldm(PADAPTER);				/* rtw_mp.c */
void rtl8710c_prepare_mp_txdesc(PADAPTER, struct mp_priv *);	/* rtw_mp.c */
void rtl8710c_mp_config_rfpath(PADAPTER);			/* hal_mp.c */
#endif
void rtl8710c_recv_tasklet(void *priv);
void update_recvframe_phyinfo_8710c(union recv_frame	*precvframe, u8 *pphy_status);

u32 rtl8710c_wlan_suspend(u32 expected_idle_time, void *param);
u32 rtl8710c_wlan_late_resume(u32 expected_idle_time, void *param);
u32 rtl8710c_wlan_resume(u32 expected_idle_time, void *param);
void rtl8710c_tcp_suspend_indicate(struct xmit_frame *pxmitframe);

#endif /* _RTL8710C_HAL_H_ */
