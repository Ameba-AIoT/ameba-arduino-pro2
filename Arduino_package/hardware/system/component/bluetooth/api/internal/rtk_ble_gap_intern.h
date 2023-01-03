/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_GAP_INTERN_H__
#define __RTK_BT_GAP_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of BLE GAP message, reused as BLE IPC GAP message
 */
typedef enum {
    RTK_BLE_ACT_GET_DEVICE_ADDR = 1,
    RTK_BLE_ACT_SET_DEVICE_NAME,
    RTK_BLE_ACT_SET_APPEARANCE,
    RTK_BLE_ACT_SET_RAND_ADDR,
    RTK_BLE_ACT_SET_ADV_DATA,
    RTK_BLE_ACT_SET_SCAN_RSP_DATA,
    RTK_BLE_ACT_START_ADV,
    RTK_BLE_ACT_STOP_ADV,
    RTK_BLE_ACT_SET_SCAN_PARAM,
    RTK_BLE_ACT_START_SCAN,
    RTK_BLE_ACT_STOP_SCAN,
    RTK_BLE_ACT_CONNECT,
    RTK_BLE_ACT_DISCONNECT,
    RTK_BLE_ACT_UPDATE_CONN_PARAM,
    RTK_BLE_ACT_MODIFY_WHITE_LIST,
    RTK_BLE_ACT_GET_WHITE_SIZE,
    RTK_BLE_ACT_READ_RSSI,
    RTK_BLE_ACT_GET_CONN_INFO,
    RTK_BLE_ACT_SET_CHAN_MAP,
    RTK_BLE_ACT_WRITE_DEFAULT_DATA_LEN,
    RTK_BLE_ACT_SET_DATA_LEN,
    RTK_BLE_ACT_SET_PHY,
    RTK_BLE_ACT_SET_PRIVACY_ENABLE,
    RTK_BLE_ACT_SET_PRIVACY_MODE,
    RTK_BLE_ACT_SET_SEC_PARAM,
    RTK_BLE_ACT_START_SECURITY,
    RTK_BLE_ACT_AUTH_PAIRING_CONFIRM, 
    RTK_BLE_ACT_AUTH_PASSKEY_INPUT,
    RTK_BLE_ACT_AUTH_PASSKEY_CONFIRM,
    RTK_BLE_ACT_AUTH_OOB_KEY_INPUT,
    RTK_BLE_ACT_GET_BOND_NUM,
    RTK_BLE_ACT_GET_BOND_INFO,
    RTK_BLE_ACT_DELETE_BOND_DEVICE,
    RTK_BLE_ACT_CLEAR_BOND_DEVICE,
    RTK_BLE_ACT_SET_DEFAULT_GAP_PARAM,
    RTK_BLE_ACT_IPC_REGISTER_GAP_CB,
    RTK_BLE_ACT_IPC_UNREGISTER_GAP_CB,
    RTK_BT_ACT_GET_VERIFY_CMD_INDEX,
    RTK_BT_ACT_VERIFY,
    RTK_BT_ACT_RESERVED,
} rtk_ble_gap_act_t;

/**
 * @brief     All bluetooth gap sync api internal paramters.
 */
/* RTK_BLE_ACT_GET_DEVICE_ADDR */
typedef struct {
    rtk_bt_err_t *pret;
    rtk_ble_bd_addr_t *paddr;
    void* sync;
} rtk_ble_gap_addr_param_t;

/* RTK_BLE_ACT_GET_WHITE_SIZE */
typedef struct {
    rtk_bt_err_t *pret;
    uint16_t *plen;
    void* sync;
} rtk_ble_gap_wl_sz_param_t;

/* RTK_BLE_ACT_GET_CONN_INFO */
typedef struct {
    rtk_bt_err_t *pret;
    uint8_t conn_id;
    void *pinfo; /* rtk_ble_conn_info_t* pinfo; */
    void* sync;
} rtk_ble_gap_conn_info_param_t;

/* RTK_BLE_ACT_GET_BOND_NUM */
typedef struct {
    rtk_bt_err_t *pret;
    uint8_t *pbond_num;
    void* sync;
} rtk_ble_gap_bond_num_param_t;

/* RTK_BLE_ACT_GET_BOND_INFO */
typedef struct {
    rtk_bt_err_t *pret;
    void *pinfo; /* rtk_ble_conn_info_t* pinfo; */
    uint8_t *psize; /* array size of pinfo[] */
    uint8_t *pactual; /* actual num of bond info stored in device */
    void* sync;
} rtk_ble_gap_bond_info_param_t;

uint32_t get_ble_gap_evt_mem_size(uint8_t evt_code);

/**
 * @brief     Deep copy function for BLE gap.
 *
 * @param[in] msg: BT message
 * @param[in] param: Pointer to BT paramters
 * 
 */
void* rtk_ble_gap_deep_copy(rtk_bt_msg_t* msg, void* param);

/**
 * @brief     Deep free function for BLE gap.
 *
 * @param[in] msg: BT message
 * 
 */
void rtk_ble_gap_deep_free(rtk_bt_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_GAP_INTERN_H__ */
