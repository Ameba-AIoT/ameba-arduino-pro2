/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_mesh_provisioner_ces_demo_config.h
  * @brief    EVENT ID and API ID.
  * @details  
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */

#ifndef _BT_MESH_PROVISIONER_CES_DEMO_CONFIG_H_
#define _BT_MESH_PROVISIONER_CES_DEMO_CONFIG_H_

/* ------------------------------- Data Types ------------------------------- */
enum CES_DEMO_BT_PROFILE {
	RTK_BT_MESH_CES_DEMO = 0
};

enum CES_DEMO_CMD {
	MESH_DEMO_IPC_HANDSHAKE_COMPLETE = 0,
	//basic
    MESH_DEMO_BC_WIFI_SCAN,
    MESH_DEMO_BC_WIFI_SCAN_COMPLETE,
    MESH_DEMO_INIT,
    MESH_DEMO_START_DHCP,
    MESH_DEMO_LWIP_GET_IP,
    MESH_DEMO_START_PROVISIONER,
    MESH_DEMO_UPDATE_UNPROVISIONED_DEVICE,
    MESH_DEMO_UPDATE_PROVED_DEVICE,
    MESH_DEMO_UPDATE_NODE_GROUP,
	MESH_DEMO_CONNECT_DEVICE,
	MESH_DEMO_DELETE_DEVICE,
    MESH_DEMO_SET_LIGHT_STATE,
    MESH_DEMO_GET_LIGHT_STATE,
    MESH_DEMO_SET_GROUP,
    MESH_DEMO_GET_GROUP
};

enum CES_DEMO_CMD_RESULT {
	MESH_DEMO_CMD_RESULT_OK,
	MESH_DEMO_CMD_RESULT_NOT_FOUND,
	MESH_DEMO_CMD_RESULT_ERROR,
	MESH_DEMO_CMD_RESULT_TIMEOUT,
	MESH_DEMO_CMD_RESULT_INCORRECT_CODE,
	MESH_DEMO_CMD_RESULT_ERROR_MESH_MODE,
	MESH_DEMO_CMD_RESULT_NOT_ENABLE,
	MESH_DEMO_CMD_RESULT_INDICATION_NOT_MATCHED
};

enum IPC_LWIP_INFO_TYPE {
	IPC_WLAN_GET_IP,
	IPC_WLAN_GET_GW,
	IPC_WLAN_GET_GWMSK,
	IPC_WLAN_GET_HW_ADDR,
	IPC_WLAN_IS_VALID_IP
};

#endif /* _BT_MESH_PROVISIONER_CES_DEMO_CONFIG_H_ */