/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BLE_IMPL_COMM_H__
#define __RTK_BLE_IMPL_COMM_H__

#include <rtk_bt_defs.h>
#include <rtk_ble_gap.h>
#include <gap.h>
#include <gap_conn_le.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_GOTO_TAG(condition, tag)       \
    do {                                    \
        if (condition) goto tag;            \
    } while(0)

rtk_bt_evt_status_t convert_stack_gap_cause(T_GAP_CAUSE cause);

rtk_ble_link_role_t convert_rtk_link_role(T_GAP_ROLE role);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BLE_IMPL_COMM_H__ */