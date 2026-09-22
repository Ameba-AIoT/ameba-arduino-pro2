/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USBD_PCD_PRIV_H
#define USBD_PCD_PRIV_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_hal.h"
#include "usb_priv.h"
/* Exported variables --------------------------------------------------------*/

/* The singleton PCD handle. */
extern usbd_pcd_t usbd_pcd_inst;

/* Exported functions --------------------------------------------------------*/

/* EP0 / control-transfer entry points */
int usbd_pcd_setup_stage(usb_dev_t *dev, u8 *setup);
int usbd_pcd_data_out_stage(usb_dev_t *dev, u8 ep_addr, u8 *buf);
int usbd_pcd_data_in_stage(usb_dev_t *dev, u8 ep_addr, u8 *buf, u8 status);

/* Bus event handlers */
int usbd_pcd_set_speed(usb_dev_t *dev, usb_speed_type_t speed);
int usbd_pcd_suspend(usb_dev_t *dev);
int usbd_pcd_resume(usb_dev_t *dev);
int usbd_pcd_sof(usb_dev_t *dev);
int usbd_pcd_connected(usb_dev_t *dev);
int usbd_pcd_disconnected(usb_dev_t *dev);

/* Interrupt registration */
int usbd_pcd_interrupt_init(usbd_pcd_t *pcd);
int usbd_pcd_interrupt_deinit(usbd_pcd_t *pcd);

/* EP0 state management
 * Used by both the EP0 transfer code and the ISR to manage the EP0 control FSM.
 */
static inline void usbd_pcd_ep0_set_state(usbd_pcd_t *pcd, u8 ep0_state)
{
	pcd->ep0_old_state = pcd->ep0_state;
	pcd->ep0_state = ep0_state;
}

#endif /* USBD_PCD_PRIV_H */
