/*
 * Copyright (c) 2026 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_USB_H
#define _AMEBA_USB_H

/* Exported defines ----------------------------------------------------------*/

#define USB_REG_BASE                                        0x400C0000UL
#define USB_ADDON_REG_BASE                                  (USB_REG_BASE + 0x30000UL)

#define USB_MAX_ENDPOINTS                                   8U
#define USB_MAX_PIPES                                       8U
#define USB_IN_TOKEN_QUEUE_DEPTH                            8U

#define USB_VID                                             0x0BDAU
#define USB_PID                                             0x8006U

#define USB_IRQ                                             USB_IRQn
#define USB_IRQ_PRI                                          USB_IRQPri

#endif /* _AMEBA_USB_H */
