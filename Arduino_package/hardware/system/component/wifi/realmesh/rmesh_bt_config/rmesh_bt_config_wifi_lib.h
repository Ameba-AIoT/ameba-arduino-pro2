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
  * @file    bt_config_wifi_lib.h
  * @author
  * @version
  * @brief   This file provides user interface for Wi-Fi station and AP mode configuration
  *             base on the functionalities provided by Realtek Wi-Fi driver.
  ******************************************************************************
  */
#ifndef __BT_CONFIG_WIFI_LIB_H_
#define __BT_CONFIG_WIFI_LIB_H_

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include "platform_stdlib.h"
#if defined(CONFIG_PLATFORM_8721D)
#include "ameba_soc.h"
#endif
#include "rmesh_bt_config_wifi.h"

#define RMESH_BC_SCAN_RESLUT_UNIT				3
#define RMESH_BC_SCAN_RESLUT_UNIT_AIRSYNC		32
#define RMESH_BC_SCAN_SECTION_LEN				(9 + 41 * RMESH_BC_SCAN_RESLUT_UNIT) // 132
#define RMESH_BC_MSG_HDR_LEN					3
#define RMESH_BC_MAX_REQ_LEN					512
#define RMESH_BC_MAX_RPL_LEN					RMESH_BC_SCAN_SECTION_LEN
#define RMESH_BC_MAX_RPL_LEN_AIRSYNC			(9 + 41 * RMESH_BC_SCAN_RESLUT_UNIT_AIRSYNC)

/* BT msg tag*/
#define RMESH_TAG_BT_CMD_SCAN					0x01
#define RMESH_TAG_BT_CMD_REPLY_SCAN			0x02
#define RMESH_TAG_BT_CMD_CONNECT				0x04
#define RMESH_TAG_BT_CMD_REPLY_CONNECT		0x05
#define RMESH_TAG_BT_CMD_BC_CONFIG			0x06
#define RMESH_TAG_BT_CMD_REPLY_BC_CONFIG		0x07
#define RMESH_TAG_BT_CMD_GET_STATUS			0x03
#define RMESH_TAG_BT_CMD_REPLY_GET_STATUS		0x09
#define RMESH_TAG_BT_CMD_GET_WLAN_BAND		0x07
#define RMESH_TAG_BT_CMD_REPLY_WLAN_BAND		0x08
#define RMESH_TAG_BT_CMD_REPLY_FAIL			0xFF
enum {
	RMESH_ENTER_CONFIG_MODE	= 0,
	RMESH_ENTER_NET_MODE = 1,
	RMESH_ENTER_BC_CONFIG_MODE = 2,
};

enum {
	RMESH_CONFIG_SUCCESS = 0,
	RMESH_CONFIG_INFO_ERROR = 1,
	RMESH_CONFIG_CONNECT_FAIL = 2,
	RMESH_CONFIG_PASSWORD_ERROR = 3,
	RMESH_CONFIG_DHCP_FAIL = 4,
	RMESH_CONFIG_SOCKET_ERROR = 5,
	RMESH_CONFIG_UNKNOWN,
};

typedef struct {
	uint8_t data[RMESH_BC_MAX_REQ_LEN];
	uint32_t len;
} RMESH_BC_command;

#pragma pack(1)
struct _RMESH_BC_TLV {
	u8 tag;
	uint16_t length;
	uint8_t value[1];
};

#pragma pack(1)
struct _RMESH_BC_bss_info {
	uint8_t security_type;/*0:open,1:WPA,2:WEP*/
	uint8_t BSSID[RMESH_BC_BSSID_LEN];
	uint8_t SSID[RMESH_BC_MAX_SSID_LEN];
	uint8_t channelNumber;
	uint8_t rssi;
};

#pragma pack(1)
struct _RMESH_BC_scan_result {
	uint8_t band;/*0 for 2.4G,1 for 5G*/
	uint32_t number;/*total number of results*/
	struct _RMESH_BC_bss_info bss_info[RMESH_BC_MAX_WIFI_SCAN_AP_NUM];
};

#pragma pack(1)
struct _RMESH_BC_status {
	uint8_t band;/*0 for 2.4G,1 for 5G*/
	uint8_t status; /*0:disconnected,1:connected*/
	uint8_t security_type;/*0:open,1:WPA,2:WEP*/
	uint8_t SSID[RMESH_BC_MAX_SSID_LEN];
	uint8_t BSSID[RMESH_BC_BSSID_LEN];
	uint8_t rssi;
	uint8_t config_status;/*0:unconfigured,1:configured*/
};

#pragma pack(1)
struct _RMESH_BC_band_info {
	uint8_t support_2_4g;
	uint8_t support_5g;
	uint8_t product_type;	/* 1: Ameba */
};

#pragma pack(1)
struct _RMESH_BC_connect_AP_info {
	uint8_t band; //0 for 2.4G,1 for 5G
	uint8_t security_type;/*0:open,1:WPA,2:WEP*/
	uint8_t SSID[RMESH_BC_MAX_SSID_LEN];
	uint8_t BSSID[RMESH_BC_BSSID_LEN];
	uint8_t password[64];
};

extern rtw_security_t rmesh_BC_translate_security_from_app(uint8_t app_security);
extern RMESH_BC_band_t rmesh_BC_req_band_hdl(void);
extern int rmesh_BC_req_scan_hdl(RMESH_BC_band_t band, struct RMESH_BC_wifi_scan_result *BC_scan_result);
extern void rmesh_BC_req_status_hdl(RMESH_BC_status_t *status, uint8_t *SSID, uint8_t *BSSID, rtw_security_t *security, uint8_t *channel, int *rssi);
#endif
