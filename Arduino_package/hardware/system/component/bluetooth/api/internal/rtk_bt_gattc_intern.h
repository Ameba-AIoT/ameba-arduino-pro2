/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation All rights reserved
 *******************************************************************************
 */

#ifndef __RTK_BT_GATTC_INTERN_H__
#define __RTK_BT_GATTC_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of BT GATT message
 */
typedef enum {
    RTK_BT_ACT_GATTC_REGISTER_APP,
    RTK_BT_ACT_GATTC_UNREGISTER_APP,
    RTK_BT_ACT_GATTC_APP_SUBSCRIBE,
    RTK_BT_ACT_GATTC_APP_UNSUBSCRIBE,
    RTK_BT_ACT_GATTC_DISCOVER,
    RTK_BT_ACT_GATTC_READ,
    RTK_BT_ACT_GATTC_WRITE,
    RTK_BT_ACT_GATTC_CONFIRM,
    RTK_BT_ACT_IPC_REGISTER_GATTC_CB,
    RTK_BT_ACT_IPC_UNREGISTER_GATTC_CB,
} rtk_bt_gattc_act_t;

/**
 * @brief     Bluetooth GATT client sync api paramters definition.
 */
typedef enum {
    RTK_BT_GATTC_RET_OK,
    RTK_BT_GATTC_RET_FAIL,
} rtk_bt_gattc_ret_t;

typedef struct {
    rtk_bt_gattc_ret_t* pret;
    void* data;
    void* sync;
} rtk_bt_gattc_sync_param_t;

/**
 * @brief     Deep copy function for GATT client.
 *
 * @param[in] msg: Pointer to API/Event message
 * @param[in] op: Operation of how to create data in message
 * @param[in] param: Pointer to BT paramters
 *
 * @return    - NULL:  Failed
 *            - Other: Pointer to API/Event message
 */
void* rtk_bt_gattc_deep_copy(rtk_bt_msg_t* msg, void* param);

/**
 * @brief     Deep free function for GATT client.
 *
 * @param[in] msg: Pointer to API/Event message
 * @param[in] op: Operation of how to create data in message
 * @param[in] param: Pointer to BT paramters
 *
 * @return    - NULL:  Failed
 *            - Other: Pointer to API/Event message
 */
void rtk_bt_gattc_deep_free(rtk_bt_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif     /* __RTK_BT_GATTC_INTERN_H__ */
