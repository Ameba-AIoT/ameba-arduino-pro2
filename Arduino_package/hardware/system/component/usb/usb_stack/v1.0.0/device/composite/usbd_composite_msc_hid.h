/*
 * Copyright (c) 2026 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef USBD_COMPOSITE_MSC_HID_H
#define USBD_COMPOSITE_MSC_HID_H

/* Includes ------------------------------------------------------------------*/

#include "usbd.h"
#include "usbd_composite_config.h"
#include "usbd_composite_hid.h"
#include "usbd_composite_msc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported defines ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/** @addtogroup USB_Device_API USB Device API
 *  @{
 */
/** @addtogroup USB_Device_Functions USB Device Functions
 * @{
 */
/** @addtogroup Device_Composite_MSC_HID_Functions Device Composite MSC HID Functions
 * @{
 */
/**
 * @brief  Init composite class
 * @param[in] hid_tx_buf_len: HID interrupt IN xfer buffer size
 * @param[in] hid_cb: HID user callback
 * @param[in] cb: Composite user callback
 * @return 0 on success, non-zero on failure
 */
int usbd_composite_msc_hid_init(u16 hid_tx_buf_len, const usbd_composite_hid_usr_cb_t *hid_cb, const usbd_composite_cb_t *cb);

/**
 * @brief  DeInit composite class
 */
void usbd_composite_msc_hid_deinit(void);
/** @} End of Device_Composite_MSC_HID_Functions group */
/** @} End of USB_Device_Functions group */
/** @} End of USB_Device_API group */

#ifdef __cplusplus
}
#endif

#endif /* USBD_COMPOSITE_MSC_HID_H */
