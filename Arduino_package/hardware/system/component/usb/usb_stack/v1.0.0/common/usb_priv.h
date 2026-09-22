/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef USB_PRIV_H
#define USB_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "basic_types.h"
/* Exported defines ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifndef CONFIG_NON_OS
/**
 * @brief Create the USB diag task that periodically drains the diag ring buffer to serial.
 * @note  The task is unique: calling this again while it is already running is a no-op.
 *        Only the ring buffer is heap-allocated internally, and it is freed by
 *        @ref usb_diag_task_delete. It is created by the USB core and not meant to be called
 *        directly by applications.
 * @param[in] depth    Ring buffer depth in entries; 0 falls back to @ref USB_DIAG_DEFAULT_DEPTH.
 * @param[in] poll_ms  Polling interval in ms; 0 falls back to @ref USB_DIAG_DEFAULT_POLL_MS.
 * @return HAL_OK on success (or if the task is already running), HAL_ERR_MEM on failure.
 */
int usb_diag_task_create(u16 depth, u16 poll_ms);

/**
 * @brief Delete the USB diag task created by @ref usb_diag_task_create.
 * @note  Safe to call when the task is not running. It is deleted by the USB core during deinit.
 */
void usb_diag_task_delete(void);
#endif /* CONFIG_NON_OS */

#endif /* USB_PRIV_H */
