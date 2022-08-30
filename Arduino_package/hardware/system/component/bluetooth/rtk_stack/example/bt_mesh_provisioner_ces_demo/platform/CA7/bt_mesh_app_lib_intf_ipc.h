/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_mesh_app_lib_intf_ipc.h
  * @brief    head file for ces demo(CA7).
  * @details  
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */

#ifndef _BT_MESH_APP_LIB_INTF_H_
#define _BT_MESH_APP_LIB_INTF_H_

#include "osdep_service.h"

struct BT_MESH_LIB_PRIV {
	_sema connect_device_sema;
	_sema connect_device_goog_sema;
	_sema connect_device_nr_sema;
	_sema delete_node_sema;
	_sema set_node_state_sema;
	_sema set_node_group_sema;

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

uint8_t bt_mesh_cmd_start_provisioner_api(void);

uint8_t bt_mesh_cmd_connect_device_api(uint8_t *dev_uuid, uint16_t *mesh_addr, uint8_t *light_state);

uint8_t bt_mesh_cmd_delete_node_api(uint16_t mesh_addr);

uint8_t bt_mesh_cmd_set_node_state_api(uint16_t mesh_addr, uint16_t group_addr, uint8_t light_state, uint8_t flag);

uint8_t bt_mesh_cmd_get_node_state_api(uint16_t mesh_addr);

uint8_t bt_mesh_cmd_set_node_group_api(uint16_t mesh_addr, uint16_t group_addr);

uint8_t bt_mesh_cmd_get_node_group_api(uint16_t mesh_addr);

#endif

