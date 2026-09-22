/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef USBD_HAL_H
#define USBD_HAL_H

/* Includes ------------------------------------------------------------------*/
#include "usb_regs.h"
#include "usb_hal.h"
#include "usbd.h"

/* Exported defines ----------------------------------------------------------*/
/*  EP0 State */
#define USBD_EP0_IDLE                                  0x00U
#define USBD_EP0_SETUP                                 0x01U
#define USBD_EP0_DATA_IN                               0x02U
#define USBD_EP0_DATA_OUT                              0x03U
#define USBD_EP0_STATUS_IN                             0x04U
#define USBD_EP0_STATUS_OUT                            0x05U
#define USBD_EP0_STALL                                 0x06U

/* USB EPMIS cnt */
#define USBD_EPMIS_CNT                         8U

/* USB setup packet buffer, 3 back-to-back setup packets */
#define USBD_SETUP_PACKET_BUF_LEN              (3U * 8U)
/* USB setup packet cnt, temporarily only for one packet */
#define USBD_SETUP_PACKET_CNT              (1U)

/* USB Core Turnaround Timeout Value */
#define USBD_UTMI_16_BIT_TRDT_VALUE            5U
#define USBD_UTMI_8_BIT_TRDT_VALUE             9U

/* USB Core MPS */
#define USB_OTG_HS_MAX_PACKET_SIZE             512U
#define USB_OTG_FS_MAX_PACKET_SIZE             64U
#define USB_OTG_MAX_EP0_SIZE                   64U

/* USB Core PHY Frequency */
#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     (0U << 1)
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     (1U << 1)
#define DSTS_ENUMSPD_LS_PHY_6MHZ               (2U << 1)
#define DSTS_ENUMSPD_FS_PHY_48MHZ              (3U << 1)

/* USB Core Frame Interval */
#define DCFG_FRAME_INTERVAL_80                 0U
#define DCFG_FRAME_INTERVAL_85                 1U
#define DCFG_FRAME_INTERVAL_90                 2U
#define DCFG_FRAME_INTERVAL_95                 3U

/* USB Core EP0 MPS */
#define DEP0CTL_MPS_64                         0U
#define DEP0CTL_MPS_32                         1U
#define DEP0CTL_MPS_16                         2U
#define DEP0CTL_MPS_8                          3U

/* USB EP Address Mask */
#define EP_ADDR_MSK                            0xFU

/* USB STS Defines */
#define STS_GOUT_NAK                           1U
#define STS_DATA_UPDT                          2U
#define STS_XFER_COMP                          3U
#define STS_SETUP_COMP                         4U
#define STS_SETUP_UPDT                         6U

/* Exported types ------------------------------------------------------------*/

/* USB PCD endpoint structure */
typedef struct {
	usb_ep_info_t *info;
	u8 *xfer_buf;                       /*!< Pointer to transfer buffer */
	u32 xfer_len;                       /*!< Current total transfer length */
	u32 xfer_count;                     /*!< Bytes written to the FIFO so far (successful or not);
                                             used to track partial progress in multi-packet transfers */
#ifdef CONFIG_SUPPORT_USB_SHARED_DFIFO
	u32 dma_addr;                       /*!< 32 bits aligned transfer buffer address */
#endif
	__IO u8 tx_zlp;                     /*!< TX with last ZLP */
	u8 is_stall;                        /*!< Endpoint stall condition */
	u8 tx_fifo_num : 4;                 /*!< Transmission FIFO number, 0~15 */
	u8 is_ptx : 1;                      /*!< Periodic TX Transfer 0~1 */
	u8 is_initialized : 1;              /*!< Flag indicating whether the endpoint is initialized */
	u8 skip_dcache_pre_clean : 1;       /*!< Skip DCache_Clean in TRX API and it will be called in class */
	u8 skip_dcache_post_invalidate : 1; /*!< Skip DCache_Invalidate when RX complete and it will be called in class */
} usbd_pcd_ep_t;

/* PCD state */
typedef enum {
	HAL_PCD_STATE_RESET   = 0x00,
	HAL_PCD_STATE_READY   = 0x01,
	HAL_PCD_STATE_ERROR   = 0x02,
	HAL_PCD_STATE_BUSY    = 0x03,
	HAL_PCD_STATE_TIMEOUT = 0x04,
	HAL_PCD_STATE_STOP    = 0x05
} usbd_pcd_state_t;

/* PCD handle structure */
typedef struct {
	usbd_pcd_ep_t in_ep[USB_MAX_ENDPOINTS];     /*!< IN endpoint parameters */
	usbd_pcd_ep_t out_ep[USB_MAX_ENDPOINTS];    /*!< OUT endpoint parameters */
	usb_dev_t *dev;                             /*!< Pointer to upper stack Handler */
	usbd_config_t *config;	                    /*!< PCD required parameters  */
	u8 *setup;                                  /*!< Setup packet buffer */
	u8 *ep0_in_rem_xfer_buf;                    /**< Pointer to the remaining part of the transfer buffer. */
	u8 *ep0_out_rem_xfer_buf;                   /**< Pointer to the remaining part of the transfer buffer. */
	u32 ep0_in_rem_xfer_len;                    /**< Remaining length of data to transfer (used for EP0). */
	u32 ep0_out_rem_xfer_len;                   /**< Remaining length of data to transfer (used for EP0). */
	u32 ep0_out_intr;                           /**< Previous interrupt status for EP0 OUT. */
	u16 ep0_data_len;                           /**< Data length for the current EP0 transfer. */
	u16 isoc_out_eopf_mask;                     /*!< Bitmask of active isochronous OUT EPs with binterval > 1, for setting EOPF interrupt mask. */
#ifdef CONFIG_SUPPORT_USB_SHARED_DFIFO
	u32 nptx_epmis_cnt;                         /*!< NP TX ep mismatch count */
	u8 nextep_seq[USB_MAX_ENDPOINTS];           /*!< NextEp sequence, including EP0: nextep_seq[] = EP if non-periodic and active, 0xff otherwise */
	u8 in_ep_sequence[USB_MAX_ENDPOINTS];       /*!< IN EP sequence from In token queue */
	u8 start_predict;                           /*!< Start predict NextEP based on Learning Queue if equal 1, also used as counter of disabled NP IN EP's */
	u8 first_in_nextep_seq;                     /*!< Index of first EP in nextep_seq array which should be re-enabled */
#endif
	__IO u8 pcd_state;                          /*!< PCD communication state. See @ref usbd_pcd_state_t. */
	__IO u8 ep0_state;                          /**< Current state of the EP0 state machine. */
	__IO u8 ep0_old_state;                      /**< Previous state of the EP0 state machine. */
	__IO u8 remote_wakeup;                      /*!< Flag indicating whether the device is waking up host from suspend(clear in SOF interrupt) */
	u8 address;                                 /*!< USB Address */
	u8 isr_initialized;                         /*!< ISR initialized */
} usbd_pcd_t;

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

int usbd_hal_device_init(usbd_pcd_t *pcd);
int usbd_hal_set_turnaround_time(void);
int usbd_hal_set_device_speed(u8 speed);
int usbd_hal_ep_activate(usbd_pcd_t *pcd, usbd_pcd_ep_t *pep);
int usbd_hal_ep_deactivate(usbd_pcd_t *pcd, usbd_pcd_ep_t *pep);
int usbd_hal_ep_start_transfer(usbd_pcd_t *pcd, usbd_pcd_ep_t *pep);
int usbd_hal_ep0_start_transfer(usbd_pcd_t *pcd, usbd_pcd_ep_t *pep);
int usbd_hal_ep_set_stall(usbd_pcd_ep_t *pep);
int usbd_hal_ep_clear_stall(usbd_pcd_ep_t *pep);
int usbd_hal_set_device_address(u8 address);
int usbd_hal_connect(void);
int usbd_hal_disconnect(void);
int usbd_hal_device_stop(void);
int usbd_hal_config_dfifo(usbd_pcd_t *pcd);
int usbd_hal_ep0_setup_activate(void);
int usbd_hal_ep0_out_start(usbd_pcd_t *pcd);
void usbd_hal_ep0_out_clear_nak(void);
#ifdef CONFIG_SUPPORT_USB_SHARED_DFIFO
int usbd_hal_reset_in_token_queue(usbd_pcd_t *pcd);
int usbd_hal_predict_next_ep(usbd_pcd_t *pcd, usbd_pcd_ep_t *pep);
#endif
u8 usbd_hal_get_device_speed(void);
u32 usbd_hal_get_tx_fifo_num(usbd_pcd_t *pcd, usbd_pcd_ep_t *pep);
u32 usbd_hal_read_all_out_ep_interrupts(void);
u32 usbd_hal_read_clear_out_ep_interrupts(u8 ep_addr, u32 *ep_all_intr);
u32 usbd_hal_read_all_in_ep_interrupts(void);
u32 usbd_hal_read_clear_in_ep_interrupts(usbd_pcd_ep_t *ep);
int usbd_hal_test_mode(u8 mode);
int usbd_hal_wake_host(usbd_pcd_t *pcd);

#endif /* USBD_HAL_H */
