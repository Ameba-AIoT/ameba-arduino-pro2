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
 */

/**
  ******************************************************************************
  * @file    bt_config_wifi.h
  * @author
  * @version
  * @brief   This file provides user interface for Wi-Fi station and AP mode configuration
  *             base on the functionalities provided by Realtek Wi-Fi driver.
  ******************************************************************************
  */
#ifndef __RMESH_BT_CONFIG_WIFI_H_
#define __RMESH_BT_CONFIG_WIFI_H_

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include "platform_stdlib.h"
#if defined(CONFIG_PLATFORM_8721D)
#include "ameba_soc.h"
#endif
#include "wifi_structures.h"
#include <platform_opts.h>
#include <platform_opts_bt.h>

#define DEBUG 0

#if DEBUG
#define BC_DBG_PREFIX	"\n\r[BT Config Wifi][DBG] "
#define	BC_DBG(...)		printf(BC_DBG_PREFIX __VA_ARGS__);
#else
#define BC_DBG(...)
#endif

#define BC_PREFIX		"\n\r[BT Config Wifi] "
#define	BC_printf(...)	printf(BC_PREFIX __VA_ARGS__);

#define RMESH_BC_BSSID_LEN					(6)
#define RMESH_BC_MAX_SSID_LEN					(32)
#define RMESH_BC_MAX_WIFI_SCAN_AP_NUM			(64)
#define RMESH_BC_MAX_WIFI_SCAN_AP_NUM_AIRSYNC	(32)

#define BC_RANDOM_BYTE	4
#define BC_CHANNEL_FIX_LEN	(BC_RANDOM_BYTE + 1)
#define MAX_CHANNEl_FIX_PKT_NUM	55
#define BC_CHANNEL_FIX_INTERVAL	10

typedef enum {
	RMESH_BC_DEV_DISABLED            = 0x0,
	RMESH_BC_DEV_INIT                = 0x1,
	RMESH_BC_DEV_IDLE                = 0x2,
	RMESH_BC_DEV_BT_CONNECTED        = 0x3,
	RMESH_BC_DEV_DEINIT              = 0x4,
} RMESH_BC_device_state_t;

typedef enum {
	RMESH_BC_BAND_UNKNOWN       = 0x00,
	RMESH_BC_BAND_2G            = 0x01,
	RMESH_BC_BAND_5G            = 0x10,
	RMESH_BC_BAND_2G_5G         = RMESH_BC_BAND_2G | RMESH_BC_BAND_5G,
} RMESH_BC_band_t;

typedef enum {
	RMESH_BC_STATE_DISABLED            = 0x0,
	RMESH_BC_STATE_IDLE                = 0x1,
	RMESH_BC_STATE_CONNECTED           = 0x2,
	RMESH_BC_STATE_WRONG_PASSWORD      = 0x3,
} RMESH_BC_status_t;

struct RMESH_BC_wifi_scan_result {
	rtw_scan_result_t ap_info[RMESH_BC_MAX_WIFI_SCAN_AP_NUM];
	uint32_t          ap_num;
};

typedef void (*airsync_send_data_handler)(uint8_t *buf, uint16_t length);

/* API defined in bt_config_wifi_lib */
extern void rmesh_BC_cmd_task_init(void);
extern void rmesh_BC_cmd_task_deinit(void);
extern void rmesh_BC_handle_read_request(uint8_t **pRead_buf, uint32_t *pRead_buf_len, uint16_t read_offset);
extern void rmesh_BC_send_cmd(uint8_t *cmd, uint32_t len);

/* API used in bt_config_wifi_lib */
extern int rmesh_BC_connect_ap(u8 *ssid, u8 *password, rtw_security_t security);
extern void rmesh_BC_req_status_hdl(RMESH_BC_status_t *status, uint8_t *SSID, uint8_t *BSSID, rtw_security_t *security, uint8_t *channel, int *rssi);
extern void rmesh_tx_config_req_to_app();

void rmesh_bt_config_wifi_init(void);
void rmesh_bt_config_wifi_deinit(void);
#endif // __BT_CONFIG_WIFI_H_
