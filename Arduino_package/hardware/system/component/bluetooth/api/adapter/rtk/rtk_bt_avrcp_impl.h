/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_BT_AVRCP_IMPL_H__
#define __RTK_BT_AVRCP_IMPL_H__

/* -------------------------------- Includes -------------------------------- */
#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C" {
#endif
/* -------------------------------- Defines --------------------------------- */

/**
 * @brief  process avrcp initialization.
 * @param  none.
 * @return rtk_bt_err_t.
 */
rtk_bt_err_t rtk_bt_avrcp_init(void);

/**
 * @brief  process avrcp deinit.
 * @param  none.
 * @return none.
 */
void rtk_bt_avrcp_deinit(void);


#ifdef __cplusplus
}
#endif

#endif /*!< __RTK_BT_AVRCP_IMPL_H__ */