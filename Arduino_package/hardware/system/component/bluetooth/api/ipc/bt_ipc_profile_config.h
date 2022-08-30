/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
  * @file     bt_ipc_profile_config.h
  * @brief    bt ipc profile enum.
  * @details  
  * @author   sherman
  * @date     2021-10-20
  * @version  v1.0
  * *************************************************************************************
  */

#ifndef _BT_IPC_PROFILE_CONFIG_H_
#define _BT_IPC_PROFILE_CONFIG_H_

/* ------------------------------- Data Types ------------------------------- */

enum BT_IPC_PROFILE {
    RTK_BT_IPC_MAIN = 0,
    RTK_BT_IPC_GAP_BLE,
    RTK_BT_IPC_GAP_BTC,
    RTK_BT_IPC_GATT,
    RTK_BT_IPC_GATTC,
    RTK_BT_IPC_GATTS,
};

#endif /* _BT_IPC_PROFILE_CONFIG_H_ */