/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BLE_ISO_MGR_INTERN_H__
#define __RTK_BLE_ISO_MGR_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of BLE ISO Management 
 */
typedef enum {
    RTK_BLE_ACT_ISO_MGR_CIG_INIT  = 1,
    RTK_BLE_ACT_ISO_MGR_CIG_SETUP_PATH,
    RTK_BLE_ACT_ISO_MGR_CIG_REMOVE_PATH,
    RTK_BLE_ACT_ISO_MGR_CIG_DISCONNECT,
    RTK_BLE_ACT_ISO_MGR_CIG_READ_TX_SYNC,
    RTK_BLE_ACT_ISO_MGR_CIG_READ_LINK_QUALITY,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_ADD_CIS,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_SET_CIG_PARAM,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_SET_CIS_PARAM,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_START_SETTING,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_SET_CIS_ACL_LINK,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_CREATE_CIS_BY_CIG_ID,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_CREATE_CIS_BY_CIG_CONN_HANDLE,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_REMOVE_CIG,
    RTK_BLE_ACT_ISO_MGR_CIG_ACCEPTOR_ACCEPT_CIS,
    RTK_BLE_ACT_ISO_MGR_CIG_ACCEPTOR_REJECT_CIS,
    RTK_BLE_ACT_ISO_MGR_CIG_ACCEPTOR_CONFIG_SDU_PARAM,
    RTK_BLE_ACT_ISO_MGR_CIG_ACCEPTOR_CONFIG_CIS_REQ_ACTION,
    RTK_BLE_ACT_ISO_MGR_CIG_REGISTER_DIRECT_CALLBACK,
    RTK_BLE_ACT_ISO_MGR_CIG_ACCEPTOR_REGISTER_CALLBACK,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_REGISTER_CALLBACK,
    RTK_BLE_ACT_ISO_MGR_ISO_DATA_SEND,
    RTK_BLE_ACT_ISO_MGR_ISO_DATA_CONFIRM,
    RTK_BLE_ACT_ISO_MGR_CIG_GET_CONN_ID,
    RTK_BLE_ACT_ISO_MGR_CIG_GET_CIS_INFO,
    RTK_BLE_ACT_ISO_MGR_CIG_GET_ISOCH_INFO,
    RTK_BLE_ACT_ISO_MGR_CIG_INITIATOR_GET_CIS_CONN_HANDLE,
} rtk_ble_iso_mgr_act_t;

uint32_t get_ble_iso_mgr_evt_mem_size(uint8_t evt_code);

void* rtk_ble_iso_mgr_deep_copy(rtk_bt_msg_t* msg, void* param);

void rtk_ble_iso_mgr_deep_free(rtk_bt_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BLE_ISO_MGR_INTERN_H__ */
