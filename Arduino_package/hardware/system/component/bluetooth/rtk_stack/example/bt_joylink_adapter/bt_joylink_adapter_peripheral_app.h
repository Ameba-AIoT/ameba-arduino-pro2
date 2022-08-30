/**
*****************************************************************************************
*	 Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file	  peripheral_app.h
   * @brief	 This file handles BLE peripheral application routines.
   * @author	jane
   * @date	  2017-06-06
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

#ifndef _BT_JOYLINK_ADAPTER_PERIPHERAL_APP_H_
#define _BT_JOULINK_ADAPTER_PERIPHERAL_APP_H_

/*============================================================================*
 *							  Header Files
 *============================================================================*/
#include <app_msg.h>
#include <gap_le.h>
#include <profile_server.h>
#include "bt_joylink_adapter_service.h"

/*============================================================================*
 *							  Variables
 *============================================================================*/
#define BT_JOULINK_ADAPTER_SERVICE_MAX_NUM 12

typedef enum {
	BJA_API_MSG_SEND_INDICATION,
	BHA_API_MSG_MAX
} T_BJA_API_MSG_TYPE;

typedef struct {
	T_SERVER_RESULT result;
	T_SERVER_ID srv_id;
} T_BJA_SRV_ADDED_CALLBACK_DATA;

typedef struct {
	T_SERVER_RESULT result;
	T_SERVER_ID srv_id;
	uint8_t att_index;
} T_BJA_IND_SENT_CALLBACK_DATA;

typedef struct {
	uint8_t write_len;
	uint8_t write_value[JOYLINK_WRITE_MAX_LEN];
	//BleGattServiceWrite write_cb;
} T_BJA_WRITE_DATA;
typedef enum {
	BJA_CALLBACK_MSG_DISCONNECTED,
	BJA_CALLBACK_MSG_INDICATION_SENT,
	BJA_CALLBACK_MSG_WRITE_SENT,
	BJA_CALLBACK_MSG_MAX
} T_BJA_CALLBACK_MSG_TYPE;

typedef struct {
	T_BJA_CALLBACK_MSG_TYPE type;
	void *buf;
} T_BJA_CALLBACK_MSG;

/*============================================================================*
 *							  Functions
 *============================================================================*/

bool bt_joylink_adapter_app_send_api_msg(T_BJA_API_MSG_TYPE sub_type, void *buf);

/**
 * @brief	All the application messages are pre-handled in this function
 * @note	 All the IO MSGs are sent to this function, then the event handling
 *		   function shall be called according to the MSG type.
 * @param[in] io_msg  IO message data
 * @return   void
 */
void bt_joylink_adapter_app_handle_io_msg(T_IO_MSG io_msg);

/**
 * @brief	All the BT Profile service callback events are handled in this function
 * @note	 Then the event handling function shall be called according to the
 *		   service_id.
 * @param[in] service_id  Profile service ID
 * @param[in] p_data	  Pointer to callback data
 * @return   Indicates the function call is successful or not
 * @retval   result @ref T_APP_RESULT
 */
T_APP_RESULT bt_joylink_adapter_app_profile_callback(T_SERVER_ID service_id, void *p_data);

/**
  * @brief Callback for gap le to notify app
  * @param[in] cb_type callback msy type @ref GAP_LE_MSG_Types.
  * @param[in] p_cb_data point to callback data @ref T_LE_CB_DATA.
  * @retval result @ref T_APP_RESULT
  */
T_APP_RESULT bt_joylink_adapter_app_gap_callback(uint8_t cb_type, void *p_cb_data);

#endif
