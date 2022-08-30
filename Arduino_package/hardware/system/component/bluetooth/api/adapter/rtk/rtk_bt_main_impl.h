/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_MAIN_IMPL_H__
#define __RTK_BT_MAIN_IMPL_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      RTK BT main initialization.
 *
 * @param[in]  evt_msg_q: Event message queue
 * @param[in]  io_msg_q: IO message queue
 * 
 * @return     - RTK_BT_OK  : Succeed
 *             - RTK_BT_FAIL: Failed
 * 
 */
rtk_bt_err_t rtk_bt_main_init_impl(void *evt_msg_q, void *io_msg_q);

/**
 * @brief      RTK BT main Deinitialization.
 * 
 * @return     - RTK_BT_OK  : Succeed
 *             - RTK_BT_FAIL: Failed
 * 
 */
rtk_bt_err_t rtk_bt_main_deinit_impl(void);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_MAIN_IMPL_H__ */