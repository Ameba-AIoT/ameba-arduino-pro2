/**
 * @file      rtk_bt_vendor.h
 * @author    
 * @brief     Bluetooth Common function definition
 * @copyright Copyright (c) 2022. Realtek Semiconductor Corporation. All rights reserved.
 */

#ifndef __RTK_BT_VENDOR_H__
#define __RTK_BT_VENDOR_H__

#include <rtk_bt_defs.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief     set bt tx power gain index.
 * @param[in] index: tx power gain index.
 * @return    None
 */
void rtk_bt_set_bt_tx_power_gain_index(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_VENDOR_H__ */
