/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_VENDOR_INTERN_H__
#define __RTK_BT_VENDOR_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of BT IPC main message
 */
enum {
    RTK_BT_SET_TX_POWER_GAIN_INDEX = 1,
	RTK_BT_ENABLE_HCI_DEBUG,
};

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_VENDOR_INTERN_H__ */