/******************************************************************************
 * Copyright (c) 2013-2016 Realtek Semiconductor Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#ifndef AUTOCONF_8730E_H
#define AUTOCONF_8730E_H

#ifndef CONFIG_RTL8730E
#define CONFIG_RTL8730E
#endif
#undef RTL8730E_SUPPORT
#define RTL8730E_SUPPORT 1
/* Configure for bus */
#define CONFIG_AXI_HCI
/* For efuse or flash config start */
#define CONFIG_EFUSE_SEPARATE
/* For efuse or flash config end */
/* PHY layer band config */
#define CONFIG_DFS
#define NOT_SUPPORT_40M
/* 0: 20 MHz, 1: 40 MHz, 2: 80 MHz, 3: 160MHz, 4: 80+80MHz
* 2.4G use bit 0 ~ 3, 5G use bit 4 ~ 7
* 0x21 means enable 2.4G 40MHz & 5G 80MHz */
#define  CONFIG_BW_MODE	0x00
#define SUPPORT_5G_CHANNEL
#define CONFIG_INIT_CHAN 1
/* PHY layer band config end */
/* For DM support */
#define RATE_ADAPTIVE_SUPPORT 0
/* Configurations for power saving */
#define CONFIG_WOWLAN
/* enable 1X code in lib_wlan as default (increase 380 bytes) */
#define CONFIG_EAP
/* For phydm configurations */
#define CONFIG_FW_C2H_PKT

#ifdef CONFIG_BT_EN
#define CONFIG_BT_COEXIST
#endif

//#define RX_SHORTCUT
//#define TX_SHORTCUT
#define TXBD_PRE_MALLOC
#define RTL8730A_SPECIFIC
//#define CONFIG_SUPPORT_DYNAMIC_TXPWR   //rtw_phydm_fill_desc_dpt todo
//#define CONFIG_WIFI_MESH	0
#define RTL8730E_WL_TODO
/* config for AP mode */
#define AP_STA_NUM (12) /* reduce ram size, revert this when ddr or psram read */
//Decrease STA due to memory limitation - Alex Fang
#define NUM_STA (2 + AP_STA_NUM)	//2 + supported clients

/*halbb halrf config*/
#define PHYDM_VERSION	3 /*halbb halrf*/
#define DRV_BB_RUA_DISABLE
#define DRV_BB_LA_MODE_DISABLE
#define DRV_BB_DIG_MCC_DISABLE
#define PHL_MAX_STA_NUM NUM_STA

//#define CONFIG_80211AC_VHT
#ifdef CONFIG_80211AC_VHT
#define VHT_OPTION	1	/* 0:disable, 1:enable, 2:force auto enable */
/*00: support mcs0~7, 01: support mcs0~8,10: support mcs0~9, 11: not support*/
#define VHT_RX_MCS_MAP0 	(u8)(0x5555 & 0xFF)
#define VHT_RX_MCS_MAP1 	(u8)((0x5555 & 0xFF00) >> 8)
#endif

#define CONFIG_80211AX_HE
#ifdef CONFIG_80211AX_HE
//#define MBSSID_SUPPORT
//#define CONFIG_TWT
#endif

/*Wifi verification*/
#if defined(CONFIG_WIFI_VERIFY_TRUEPHY) || defined(CONFIG_WIFI_VERIFY_PSPHY)
#define RTL8730E_WIFI_TEST	1//test code, should delete when use ASIC
#define DISABLE_FW
#define DISABLE_BB_RF
#endif
#ifdef CONFIG_MAC_LBK//lbk code will delete later
#define RTL8730E_WIFI_TEST	1
#define DISABLE_FW
#define DISABLE_BB_RF
#define INT_HANDLE_IN_ISR 1
#define CONFIG_WLAN_HAL_TEST
#define CONFIG_WLAN_HAL_RX_TASK
#define CONFIG_MAC_LOOPBACK_DRIVER_AMEBA 1
#endif
#ifdef CONFIG_WIFI_VERIFY_ASIC
#define RTL8730E_WIFI_TEST 1  // add wifi testcode for debug
#endif

//#define CONFIG_DFS_TEST  // add for dfs test

/* enable csi function */
#define CONFIG_CSI

#define CONFIG_REG_ENABLE_KFREE 0	// 0: Depend on efuse(flash), 1: enable, 2: disable
#define DISABLE_BB_WATCHDOG
#define PLATFOM_IS_LITTLE_ENDIAN	1/*for halbb use*/

#define PHYSTS_WORK_AROUND
#define RTL8730E_WORK_AROUND

/*************************** Config for MP_MODE *******************************/
//#define CONFIG_MP_INCLUDED
#ifdef CONFIG_MP_INCLUDED
#define MP_DRIVER 1
#undef CONFIG_ANTENNA_DIVERSITY
#undef CONFIG_BT_COEXIST_SOC
#undef CONFIG_REG_ENABLE_KFREE
#define CONFIG_REG_ENABLE_KFREE 1	 // 1: enable, 2: disable
#define CONFIG_PHYDM_CMD  /*disable it in normal driver,lite can save 172KB code size, smart need check*/
#else /* undef CONFIG_MP_INCLUDED  */
#define MP_DRIVER 0
#endif /* #ifdef CONFIG_MP_INCLUDED */
/************************* Config for MP_MODE end *****************************/

#ifndef CONFIG_PHYDM_CMD
#define DRV_BB_DBG_TRACE_DISABLE
#define DRV_BB_PMAC_TX_DISABLE
#endif


/* debug log level */
#ifdef RELEASE_VERSION
#define RTW_MSG_LEVEL    RTW_MSG_ERROR
#else
#define RTW_MSG_LEVEL    RTW_MSG_WARNING
#endif

#endif /*#ifndef AUTOCONF_8730A_H */

