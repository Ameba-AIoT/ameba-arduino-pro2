/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_MP_API_INTERN_H__
#define __RTK_BT_MP_API_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief     Action of BT MP API IPC message
 */
enum {
	RTK_BT_MP_POWER_ON = 1,
	RTK_BT_MP_POWER_OFF,
	RTK_BT_MP_SET_ANT,
};

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_MP_API_INTERN_H__ */