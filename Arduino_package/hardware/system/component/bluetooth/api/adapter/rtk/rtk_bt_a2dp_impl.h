/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_BT_A2DP_IMPL_H__
#define __RTK_BT_A2DP_IMPL_H__

/* -------------------------------- Includes -------------------------------- */
#include <rtk_bt_defs.h>
#include <rtk_bt_a2dp.h>
#include <rtk_legacy_gap_impl.h>

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------------- Defines --------------------------------- */


/**
 * @brief  process a2dp initialization.
 * @param  none.
 * @return rtk_bt_err_t.
 */
rtk_bt_err_t rtk_bt_a2dp_init(void);

/**
 * @brief  process avrcp deinit.
 * @param  none.
 * @return none.
 */
void rtk_bt_a2dp_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BT_A2DP_IMPL_H__ */