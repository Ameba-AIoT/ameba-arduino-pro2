/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_ADAPTER_TASK_H__
#define __RTK_BT_ADAPTER_TASK_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Create API message Task.
 *
 * @param[in] scence: application scenario
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_adapter_create_task(uint32_t scence);

/**
 * @brief     Delete API message Task.
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_adapter_delete_task(void);

/**
 * @brief     Send API message to Task.
 *
 * @param[in] msg: message to task
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_adapter_send_to_task(void* msg);

/**
 * @brief     Send message to Task.
 *
 * @param[in] type:  message type
 * @param[in] : message subtype
 * @param[in] msg: message to task          
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_adapter_send_msg_to_task(uint16_t type, uint16_t subtype, void *msg);

rtk_bt_err_t rtk_bt_stack_wait_ready(uint32_t scence);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_ADAPTER_TASK_H__ */