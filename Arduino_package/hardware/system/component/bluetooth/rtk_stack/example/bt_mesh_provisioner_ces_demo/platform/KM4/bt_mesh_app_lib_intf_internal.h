/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_mesh_app_lib_intf_internal.h
  * @brief    head file for ces demo(km4).
  * @details  
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */
#ifndef _BT_MESH_APP_LIB_INTF_INTERNAL_H_
#define _BT_MESH_APP_LIB_INTF_INTERNAL_H_

#include "bt_ipc_host_api.h"

typedef enum
{
	API_PB_ADV_LINK_OPEN = 0x0,
	API_PROV_INVITE = 0x1,
	API_CFG_APP_KEY_ADD = 0x2,
	API_CFG_MODEL_APP_BIND = 0x3,
	API_CFG_MODEL_PUB_SET = 0x4,
	API_CFG_MODEL_SUB_ADD = 0x5,
	API_CFG_MODEL_SUB_GET = 0x6,
	API_CFG_MODEL_SUB_DELETE_ALL = 0x7,
	API_CFG_NODE_RESET = 0x8,
	API_GENERIC_ON_OFF_GET = 0x9,
	API_GENERIC_ON_OFF_SET = 0xA,
	API_GENERIC_ON_OFF_PUBLISH = 0xB,
} T_MESH_API_TYPE;

struct BT_MESH_NODE_STATE {
	uint16_t connect_device_mesh_addr;
	uint16_t connect_device_goog_mesh_addr;
	uint16_t connect_device_nr_mesh_addr;
	uint16_t delete_node_mesh_addr;
	uint16_t set_node_state_mesh_addr;
	uint16_t set_node_group_mesh_addr;

	uint8_t connect_device_flag;
	uint8_t set_node_group_flag;

	uint8_t connect_device_goog_light_state;
	uint8_t set_node_state_light_state;
};

void bt_mesh_user_cmd_handle(bt_ipc_host_request_message *p_ipc_msg);

#endif

