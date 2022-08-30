/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_mesh_lcd_intf.h
  * @brief    interface for synchronization with LCD monitor.
  * @details  
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */

#ifndef _BT_MESH_LCD_INTF_H_
#define _BT_MESH_LCD_INTF_H_

#include <stdint.h>

enum CES_LCD_EVENT {
    CES_DEMO_BT_CONFIG_WIFI_SUCCESS = 0,
	CES_DEMO_STARTING_PROVISIONER,
    CES_DEMO_START_PROVISIONER_SUCCESS,
    CES_DEMO_START_PROVISIONER_FAILED,
    CES_DEMO_GET_UNPROVISIONED_DEVICE,
    CES_DEMO_CONNECTING_UNPROVISIONED_DEVICE,
    CES_DEMO_CONNECTED_DEVICE_SUCCESS,
    CES_DEMO_CONNECTED_DEVICE_FAIL,
    CES_DEMO_DELETING_NODE,
	CES_DEMO_DELETED_NODE_SUCCESS,
	CES_DEMO_DELETED_NODE_FAIL,
    CES_DEMO_GET_NODE_STATUS,
    CES_DEMO_SETTING_NODE_STATE,
    CES_DEMO_SET_NODE_STATE_SUCCESS,
    CES_DEMO_SET_NODE_STATE_FAIL,
    CES_DEMO_SETTING_NODE_GROUP,
    CES_DEMO_SET_NODE_GROUP_SUCCESS,
    CES_DEMO_SET_NODE_GROUP_FAIL,
    CES_DEMO_SET_NODE_NAME
};

/**
 * @brief  to post the lcd monitor event.
 * @param  event_id[in]: event descriptor
 * @param  param[in]: pointer to parameters.
 * @return none.
 */
void bt_mesh_status_update_handle(uint32_t event_id, void *param);

/**
 * @brief  control single mesh light.
 * @param  mesh_addr[in]: mesh address(unicast address or group address)
 * @param  light_state[in]: target light state.
 * @return result 1 -> success, 0 -> fail.
 */
uint8_t bt_mesh_lcd_set_node_state_api(uint16_t mesh_addr, uint8_t light_state);

#endif /* _BT_MESH_LCD_INTF_H_ */