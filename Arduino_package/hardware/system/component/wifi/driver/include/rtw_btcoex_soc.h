/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
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
#ifndef __RTW_BTCOEX_SOC_H__
#define __RTW_BTCOEX_SOC_H__

#include <drv_types.h>
#include <gpio_api.h>
#include <gpio_irq_api.h>
#include <gpio_irq_ex_api.h>
#include <timers.h>
#include <portmacro.h>

#define TO_ENUM_ENTRY(entry_name, entry_value) entry_name entry_value,

#define COEX_ENUM_TOSTRING_CASE(entry_name, entry_value) case entry_name: return #entry_name;

#define COEX_BT_STATE_TOSTRING_FUNCTION(MACRO_DEFINITION, enum_name) \
static char* bt_state_dbg(enum_name enum_value) \
{ \
	switch(enum_value) \
	{ \
		MACRO_DEFINITION(COEX_ENUM_TOSTRING_CASE) \
		default: \
			return "##Error:coex_bt_state unknown enum_name ##"; \
	} \
}

#define COEX_WIFI_STATE_TOSTRING_FUNCTION(MACRO_DEFINITION, enum_name) \
static char* wifi_state_dbg(enum_name enum_value) \
{ \
	switch(enum_value) \
	{ \
		MACRO_DEFINITION(COEX_ENUM_TOSTRING_CASE) \
		default: \
			return "##Error:coex_wifi_state unknown enum_name ##"; \
	} \
}

#define COEX_CONCURRENT_STATE_TOSTRING_FUNCTION(MACRO_DEFINITION, enum_name) \
static char* concurrent_state_dbg(enum_name enum_value) \
{ \
	switch(enum_value) \
	{ \
		MACRO_DEFINITION(COEX_ENUM_TOSTRING_CASE) \
		default: \
			return "##Error:coex_concurrent_state unknown enum_name ##"; \
	} \
}

#define COEX_WIFI_EVENT_TOSTRING_FUNCTION(MACRO_DEFINITION, enum_name) \
static char* wifi_event_dbg(enum_name enum_value) \
{ \
	switch(enum_value) \
	{ \
		MACRO_DEFINITION(COEX_ENUM_TOSTRING_CASE) \
		default: \
			return "##Error:coex_wifi_event unknown enum_name ##"; \
	} \
}

//bt state
#define COEX_BT_STATE_ENUM(BT_STATE) \
	BT_STATE(COEX_STATE_BT_OFF,=0x0) \
	BT_STATE(COEX_STATE_BT_ON,=0x01) \
	BT_STATE(COEX_STATE_BLE_SCAN,=0x02) \
	BT_STATE(COEX_STATE_BLE_INIT,=0x04) \
	BT_STATE(COEX_STATE_MESH_PB_ADV,=0x08) \
	BT_STATE(COEX_STATE_BT_EXTERNAL,=0x80) \
	BT_STATE(COEX_STATE_BT_EXTERNAL_BT_ON,=0x81) \
	BT_STATE(COEX_STATE_BT_EXTERNAL_BT_SCAN,=0x82) \
	BT_STATE(COEX_STATE_BT_EXTERNAL_BT_INIT,=0x84) \
	BT_STATE(COEX_STATE_BT_MAX,)

//ext bt state
#define EXT_BT_GPIO_EVENT_ENUM(EXT_BT_EVENT) \
	EXT_BT_EVENT(EXT_BT_GPIO_EVENT_OFF,=0) \
	EXT_BT_EVENT(EXT_BT_GPIO_EVENT_INIT,=0x01) \
	EXT_BT_EVENT(EXT_BT_GPIO_EVENT_SCAN,=0x02) \
	EXT_BT_EVENT(EXT_BT_GPIO_EVENT_ON,=0x03) \
	EXT_BT_EVENT(EXT_BT_GPIO_EVENT_MAX,)

//wifi state
#define COEX_WIFI_STATE_ENUM(WIFI_STATE) \
	WIFI_STATE(COEX_STATE_WIFI_OFF,=0x00) \
	WIFI_STATE(COEX_STATE_WIFI_STA_UNCONNECTED,=0x01) \
	WIFI_STATE(COEX_STATE_WIFI_STA_SCAN,=0x02) \
	WIFI_STATE(COEX_STATE_WIFI_STA_CONNECTING,=0x03) \
	WIFI_STATE(COEX_STATE_WIFI_STA_FOUR_WAY_DOING,=0x04) \
	WIFI_STATE(COEX_STATE_WIFI_STA_CONNECTED,=0x05) \
	WIFI_STATE(COEX_STATE_WIFI_AP_IDLE,=0x06) \
	WIFI_STATE(COEX_STATE_WIFI_CONCURRENT,=0x07) \
	WIFI_STATE(COEX_STATE_WIFI_OTHER_MODE,=0x08) \
	WIFI_STATE(COEX_STATE_WIFI_MAX,)

//wifi concurrent state
#define COEX_CONCURRENT_STATE_ENUM(CONCURRENT_STATE) \
	CONCURRENT_STATE(CONCURRENT_STATE_NONE,=0x00) \
	CONCURRENT_STATE(CONCURRENT_STATE_AP_UNCONNECTED_STA_UNCONNECTED,=0x01) \
	CONCURRENT_STATE(CONCURRENT_STATE_AP_CONNECTED_STA_UNCONNECTED,=0x02) \
	CONCURRENT_STATE(CONCURRENT_STATE_AP_UNCONNECTED_STA_CONNECTED,=0x03) \
	CONCURRENT_STATE(CONCURRENT_STATE_AP_CONNECTED_STA_CONNECTED,=0x04) \
	CONCURRENT_STATE(CONCURRENT_STATE_MAX,)


//wifi event
#define COEX_WIFI_EVENT_ENUM(WIFI_EVENT) \
	WIFI_EVENT(COEX_EVENT_WIFI_OFF,=0) \
	WIFI_EVENT(COEX_EVENT_WIFI_ON,=1) \
	WIFI_EVENT(COEX_EVENT_WIFI_SCAN_START,=2) \
	WIFI_EVENT(COEX_EVENT_WIFI_SCAN_DONE,=3) \
	WIFI_EVENT(COEX_EVENT_WIFI_JOIN_START,=4) \
	WIFI_EVENT(COEX_EVENT_WIFI_JOIN_SUCCESS,=5) \
	WIFI_EVENT(COEX_EVENT_WIFI_JOIN_FAIL,=6) \
	WIFI_EVENT(COEX_EVENT_WIFI_DISCONNECT,=7) \
	WIFI_EVENT(COEX_EVENT_WIFI_CHANGE_MODE,=8) \
	WIFI_EVENT(COEX_EVENT_WIFI_FOURWAY_DONE,=9) \
	WIFI_EVENT(COEX_EVENT_WIFI_MAX,)

//Define bt state enum
typedef enum coex_bt_state {
	COEX_BT_STATE_ENUM(TO_ENUM_ENTRY)
} coex_bt_state;

//Define external bt state enum
typedef enum coex_ext_bt_event {
	EXT_BT_GPIO_EVENT_ENUM(TO_ENUM_ENTRY)
} coex_ext_bt_event;

//Define wifi state enum
typedef enum coex_wifi_state {
	COEX_WIFI_STATE_ENUM(TO_ENUM_ENTRY)
} coex_wifi_state;

//Define wifi concurrent state enum
typedef enum coex_concurrent_state {
	COEX_CONCURRENT_STATE_ENUM(TO_ENUM_ENTRY)
} coex_concurrent_state;

//Define wifi event enum
typedef enum coex_wifi_event {
	COEX_WIFI_EVENT_ENUM(TO_ENUM_ENTRY)
} coex_wifi_event;
/**
  * @brief  The enumeration is coex state indicated from wlan driver.
  */

struct mailbox_info {
	u8	id;
	u8	*data;
	u8	len;
	_list	list;
};

struct coex_hal_fun_t {
	void (*run_case)(_adapter *padapter, u16 state);
	void (*hal_coex_init)(_adapter *padapter);
	u16(*wifi_tdma_scan_start)(PADAPTER padapter, RT_SCAN_TYPE scan_type);
	u16(*wifi_tdma_scan_handle)(PADAPTER padapter);
	void (*debug_open)(u8 enable);
};

struct wifi_tdma_scan_t {
	u8 scaning;
	u8 slot_num;
	u8 cur_slot;
};

/*may be used before both devices on*/
struct coex_t {
	u8 coex_en;
	u8 wifi_state;
	u8 wifi_concurr_state;
	u8 wifi_last_state;
	u8 bt_state;
	u8 tdma_port;
	u16 state;
	_mutex coex_run_lock;
	struct wifi_tdma_scan_t wifi_tdma_scan;
	struct coex_hal_fun_t *hal_fun;

};

/*only be used after both devices on, so it can be free when only one device is on */
struct coex_priv {
	int table_idx;
	u8 ble_scan_duty;
	u8 random_wlan_slot;
	u8 wlan_connecting_adjust;
	u8 wlan_4way_adjust;
	u8 wlan_connected_adjust;
};

typedef struct _coex_bt_info {
	//low byte 1
	u8 length: 8;

	//low byte 2
	u8 Connection: 1;
	u8 rsvd1: 7;

	//low byte 3
	u8 rsvd2: 8;

	//hign byte 0
	u8 rsvd3: 8;

	//hign byte 1
	u8 rsvd5: 5;
	u8 Ble_scan_en: 1;
	u8 Ble_init_scan: 1;
	u8 rsvd4: 1;

	//hign byte 2
	u8 rsvd6: 8;

	//hign byte 3
	u8 rsvd7: 8;
} coex_bt_info;

typedef struct _Ext_BT_state_GPIO {
	PADAPTER padapter;
	bool first_time;
	TimerHandle_t xOneShotTimer;
	BaseType_t xTimer1Started;
	int total_count;
} Ext_BT_state_GPIO;

#define COEX_MBOX_STACKSIZE						256
#define GPIO_BT_STAT_IRQ_PIN					PF_0//PF_2//PF_0//PA_3
#define COEX_MAILBOX_BT_INFO_REPORT				0x23
#define COEX_MAILBOX_BT_INFO_REPORT_BY_ITSEL	0x27
#define COEX_MAILBOX_BT_INFO_PRE_ADV			0x45
#define COEX_MAILBOX_BT_EXT_PTA					0x88

int rtw_coex_mailbox_to_wifi(_adapter *padapter, u8 *data, u8 len);
int rtw_coex_wifi_info_update(_adapter *padapter, u8 wifi_event);
int rtw_coex_ble_scan_duty_update(_adapter *padapter, u8 duty);
int rtw_coex_wlan_slot_random_set(_adapter *padapter, bool temp);
int rtw_coex_wlan_slot_preempting_set(_adapter *padapter, u8 bitmask);
void rtw_btcoex_init(PADAPTER padapter);
void rtw_btcoex_deinit(PADAPTER padapter);
int rtw_coex_bt_enable(_adapter *padapter, u8 enable);
void rtw_coex_wifi_enable(PADAPTER padapter, u8 enable);
u16 rtw_coex_wifi_tdma_scan_start(PADAPTER padapter, RT_SCAN_TYPE scan_type);
u16 rtw_coex_wifi_tdma_scan_handle(PADAPTER padapter);
u8 rtw_coex_is_bt_disabled(PADAPTER padapter);
#endif /* __RTW_BTCOEX_SOC_H__ */
