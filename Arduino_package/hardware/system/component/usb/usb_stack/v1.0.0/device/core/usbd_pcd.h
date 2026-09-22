/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USBD_PCD_H
#define USBD_PCD_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_hal.h"

/* Exported defines ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* Lifecycle */
int usbd_pcd_init(usb_dev_t *dev, const usbd_config_t *config);
int usbd_pcd_deinit(usb_dev_t *dev);
int usbd_pcd_start(usbd_pcd_t *pcd);
int usbd_pcd_stop(usbd_pcd_t *pcd);

/* Connection control */
int usbd_pcd_dev_connected(usbd_pcd_t *pcd);
int usbd_pcd_dev_disconnected(usbd_pcd_t *pcd);

/* EP management */
int usbd_pcd_ep_init(usbd_pcd_t *pcd, usbd_ep_t *ep);
int usbd_pcd_ep_deinit(usbd_pcd_t *pcd, usbd_ep_t *ep);

/* EP transfer */
int usbd_pcd_ep_transmit(usbd_pcd_t *pcd, usbd_ep_t *ep);
int usbd_pcd_ep_receive(usbd_pcd_t *pcd, usbd_ep_t *ep);

/* EP control */
int usbd_pcd_ep_set_stall(usbd_pcd_t *pcd, u8 ep_addr);
int usbd_pcd_ep_clear_stall(usbd_pcd_t *pcd, u8 ep_addr);
int usbd_pcd_ep_is_stall(usbd_pcd_t *pcd, u8 ep_addr);

/* EP0 transfer */
int usbd_pcd_ep0_transmit(usb_dev_t *dev, usbd_ep_t *ep);
int usbd_pcd_ep0_receive(usb_dev_t *dev, usbd_ep_t *ep);

#endif /* USBD_PCD_H */
