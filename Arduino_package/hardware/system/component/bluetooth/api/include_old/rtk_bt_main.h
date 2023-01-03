/**
 * @file      rtk_bt_main.h
 * @author    benling_xu@realsil.com.cn
 * @brief     Bluetooth Common function definition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_MAIN_H__
#define __RTK_BT_MAIN_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup  bt_main BT Common APIs
 * @brief     BT Common function APIs
 * @ingroup   BT_APIs
 * @{
 */

/**
 * @fn        rtk_bt_err_t rtk_bt_enable(void)
 * @brief     Enable bluetooth
 *
 * @param
 *            - [in]scence :sceniro
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_enable(uint32_t scence);

/**
 * @fn        rtk_bt_err_t rtk_bt_disable(void)
 * @brief     Disable bluetooth
 *
 * @return
 *            - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_disable(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_MAIN_H__ */
