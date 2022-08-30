/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_EVENT_INTERN_H__
#define __RTK_BT_EVENT_INTERN_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Create event task
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_event_create_task(void);

/**
 * @brief     Delete event task
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_event_delete_task(void);

/**
 * @brief     Indicate event to event task
 *
 * @param[in] msg: Event message from message task
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_event_indication(void* msg);

/**
 * @brief     Register user callback in event task
 *
 * @param[in] pid: Profile id
 * @param[in] cb: User callback function handle
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_event_register_callback(uint8_t pid, void* cb);

/**
 * @brief     Unregister user callback in event task
 *
 * @param[in] pid: Profile id
 *
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_event_unregister_callback(uint8_t pid);

/**
 * @brief     Reset user callback in event task
 */
void rtk_bt_event_reset_callback(void);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_EVENT_INTERN_H__ */