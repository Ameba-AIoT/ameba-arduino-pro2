/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      peripheral_app.h
   * @brief     This file handles BLE peripheral application routines.
   * @author    jane
   * @date      2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

#ifndef _BT_HARMONY_ADAPTER_PERIPHERAL_APP_H_
#define _BT_HARMONY_ADAPTER_PERIPHERAL_APP_H_

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <app_msg.h>
#include <gap_le.h>
#include <profile_server.h>
#include "ohos_bt_def.h"
#include "ohos_bt_gatt.h"
#include "bt_harmony_adapter_service.h"

/*============================================================================*
 *                              Variables
 *============================================================================*/
#define BT_HARMONY_ADAPTER_SERVICE_MAX_NUM 12

typedef struct {
	uint16_t H_adv_int_min;   //represent H_adv_int_min * 0.625ms
	uint16_t H_adv_int_max;   //represent H_adv_int_max * 0.625ms
	uint8_t H_adv_evt_type;
	uint8_t H_local_addr_type;
	uint8_t  H_adv_direct_type;
	uint8_t  H_adv_direct_addr[OHOS_BD_ADDR_LEN];
	uint8_t H_adv_chann_map;
	uint8_t H_adv_filter_policy;
	int H_duration;  //represent H_duration * 10ms
	uint8_t txPower;
	unsigned int adv_datalen;
	unsigned int scanrep_datalen;
} H_adv_param;

typedef struct {
	BdAddr Address;
	bool accept;
} H_SecurityRsp_param;
typedef enum {
	BHA_API_MSG_START_ADV,
	BHA_API_MSG_STOP_ADV,
	BHA_API_MSG_DISCONNECT,
	BHA_API_MSG_AUTH_RESPOND,
	BHA_API_MSG_ADD_SERVICE,
	BHA_API_MSG_SEND_INDICATION,
	BHA_API_MSG_MAX
} T_BHA_API_MSG_TYPE;

typedef enum {
	BHA_CALLBACK_MSG_ADV_STARTED,
	BHA_CALLBACK_MSG_ADV_STOPED,
	BHA_CALLBACK_MSG_CONNECTED,
	BHA_CALLBACK_MSG_DISCONNECTED,
	BHA_CALLBACK_MSG_AUTH_REQUEST,
	BHA_CALLBACK_MSG_SERVICE_ADDED,
	BHA_CALLBACK_MSG_INDICATION_SENT,
	BHA_CALLBACK_MSG_WRITE_SENT,
	BHA_CALLBACK_MSG_MTU_CHANGED,
	BHA_CALLBACK_MSG_MAX
} T_BHA_CALLBACK_MSG_TYPE;

typedef struct {
	T_BHA_CALLBACK_MSG_TYPE type;
	void *buf;
} T_BHA_CALLBACK_MSG;

typedef struct {
	T_SERVER_RESULT result;
	T_SERVER_ID srv_id;
} T_BHA_SRV_ADDED_CALLBACK_DATA;

typedef struct {
	uint8_t conn_id;
	uint8_t serverID;
	BdAddr bt_addr;
} T_BHA_CONNECTED_CALLBACK_DATA;

typedef struct {
	int conn_id;
	int mtu_size;
} T_BHA_MTU_CALLBACK_DATA;

typedef struct {
	T_SERVER_RESULT result;
	T_SERVER_ID srv_id;
	uint8_t att_index;
} T_BHA_IND_SENT_CALLBACK_DATA;

typedef struct {
	uint8_t write_len;
	uint8_t write_value[HARMONY_WRITE_MAX_LEN];
	BleGattServiceWrite write_cb;
} T_BHA_WRITE_DATA;
/*============================================================================*
 *                              Functions
 *============================================================================*/

bool bt_harmony_adapter_app_send_api_msg(T_BHA_API_MSG_TYPE sub_type, void *buf);

bool bt_harmony_adapter_app_send_callback_msg(T_BHA_CALLBACK_MSG_TYPE type, void *buf);

/**
 * @brief    All the application messages are pre-handled in this function
 * @note     All the IO MSGs are sent to this function, then the event handling
 *           function shall be called according to the MSG type.
 * @param[in] io_msg  IO message data
 * @return   void
 */
void bt_harmony_adapter_app_handle_io_msg(T_IO_MSG io_msg);

void bt_harmony_adapter_app_handle_callback_msg(T_BHA_CALLBACK_MSG callback_msg);

/**
 * @brief    All the BT Profile service callback events are handled in this function
 * @note     Then the event handling function shall be called according to the
 *           service_id.
 * @param[in] service_id  Profile service ID
 * @param[in] p_data      Pointer to callback data
 * @return   Indicates the function call is successful or not
 * @retval   result @ref T_APP_RESULT
 */
T_APP_RESULT bt_harmony_adapter_app_profile_callback(T_SERVER_ID service_id, void *p_data);

/**
  * @brief Callback for gap le to notify app
  * @param[in] cb_type callback msy type @ref GAP_LE_MSG_Types.
  * @param[in] p_cb_data point to callback data @ref T_LE_CB_DATA.
  * @retval result @ref T_APP_RESULT
  */
T_APP_RESULT bt_harmony_adapter_app_gap_callback(uint8_t cb_type, void *p_cb_data);

#endif
