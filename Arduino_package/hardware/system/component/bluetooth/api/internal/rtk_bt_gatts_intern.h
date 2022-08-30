/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation all rights reserved
 *******************************************************************************
 */

#ifndef __RTK_BT_GATTS_INTERN_H__
#define __RTK_BT_GATTS_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief     Action of BT GATT message, reused as BT IPC GAP message
 */
typedef enum {
    RTK_BT_ACT_GATTS_REGISTER_SERVICE = 1,
    RTK_BT_ACT_GATTS_UNREGISTER_SERVICE, 
    RTK_BT_ACT_GATTS_INDICATE,
    RTK_BT_ACT_GATTS_NOTIFY,
    RTK_BT_ACT_GATTS_READ_RESP,
    RTK_BT_ACT_GATTS_WRITE_RESP,
    RTK_BT_ACT_IPC_REGISTER_GATTS_CB,
    RTK_BT_ACT_IPC_UNREGISTER_GATTS_CB,
} rtk_bt_gatts_act_t;

/**
 * @brief     Bluetooth GATT server sync api paramters definition.
 */
typedef enum {
    RTK_BT_GATTS_RET_OK,
    RTK_BT_GATTS_RET_FAIL,
} rtk_bt_gatts_ret_t;

typedef struct {
    rtk_bt_gatts_ret_t* pret;
    void* data;
    void* sync;
} rtk_bt_gatts_sync_param_t;

/**
 * @brief     Deep copy function for GATT server.
 *
 * @param[in] msg: Pointer to API/Event message
 * @param[in] op: Operation of how to create data in message
 * @param[in] param: Pointer to BT paramters
 *
 * @return    - NULL:  Failed
 *            - Other: Pointer to API/Event message
 */
void* rtk_bt_gatts_deep_copy(rtk_bt_msg_t* msg, void* param);

/**
 * @brief     Deep free function for GATT server.
 *
 * @param[in] msg: Pointer to API/Event message
 * @param[in] op: Operation of how to create data in message
 * @param[in] param: Pointer to BT paramters
 *
 * @return    - NULL:  Failed
 *            - Other: Pointer to API/Event message
 */
void rtk_bt_gatts_deep_free(rtk_bt_msg_t* msg);

uint32_t get_bt_gatts_evt_mem_size(uint8_t evt_code);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_GATTS_INTERN_H__ */