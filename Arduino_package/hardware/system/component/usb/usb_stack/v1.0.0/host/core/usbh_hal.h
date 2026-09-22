/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef USBH_HAL_H
#define USBH_HAL_H

/* Includes ------------------------------------------------------------------*/

#include "usb_regs.h"
#include "usb_hal.h"
#include "usbh.h"

/* Exported defines ----------------------------------------------------------*/
#define USBH_HCFG_30_60_MHZ                         0U
#define USBH_HCFG_48_MHZ                            1U
#define USBH_HCFG_6_MHZ                             2U

#define USBH_GRXSTS_PKTSTS_IN                       2U
#define USBH_GRXSTS_PKTSTS_IN_XFER_COMP             3U
#define USBH_GRXSTS_PKTSTS_DATA_TOGGLE_ERR          5U
#define USBH_GRXSTS_PKTSTS_CH_HALTED                7U

/* Exported types ------------------------------------------------------------*/

/* Host packet PID definition */
typedef enum {
	USBH_PID_DATA0 = 0U,
	USBH_PID_DATA2 = 1U,
	USBH_PID_DATA1 = 2U,
	USBH_PID_SETUP = 3U
} usbh_pid_t;

/* Host channel states definition */
typedef enum {
	USBH_HC_IDLE = 0U,
	USBH_HC_XFRC,
	USBH_HC_HALTED,
	USBH_HC_AHBERR,
	USBH_HC_STALL,
	USBH_HC_NAK,
	USBH_HC_ACK,
	USBH_HC_NYET,
	USBH_HC_XACTERR,
	USBH_HC_BBLERR,
	USBH_HC_FRMOVRUN,
	USBH_HC_DATATGLERR
} usbh_hc_state_t;

/* Host channel definition */
typedef struct {
	u8 *xfer_buff;                 /*!< Pointer to transfer buffer */
	__IO u32 xfer_len;             /*!< The length of data want to be transferred */
	__IO u32 actual_length;        /* Bytes successfully transferred in the previous transfer (0 if first transfer);
	                                  always a multiple of MPS */
	__IO u32 rx_len;               /*!< Bytes successfully received in the current transfer */

	/*
		Bulk IN: after the RX request is sent, the device replies only NAKs, so the IN token does not get sent out.
		For this issue, we enable the NAK mask to check whether NAKs are still coming.

		Bulk OUT: after the request is sent, the device replies NYET and keeps PINGing, then keeps replying NAK.
		For this issue, we enable the NAK mask to check whether NAKs are still coming.
	 */
	__IO u16 nak_cnt;             /* xfer nak count */
	__IO u16 busy_cnt;            /* xfer busy count  */

	__IO u16 pktcnt;              /*!< Endpoint Max packet Count */
	__IO u16 mps;                 /*!< Endpoint Max packet size(MPS), 0~65536 */

	__IO u8 error_cnt;            /*!< Host channel error count. */
	u8 ch_num;                    /*!< Host channel number, 1~15 */
	u8 dev_addr;                  /*!< USB device address, 1~255 */
	u8 speed;                     /*!< Host speed, 0~3 */
	u8 intr_exit;                 /*!< intr handle should exit, 0~1 */

	u8 hc_state;                  /*!< Host Channel state, @ref usbh_hc_state_t 0~8 */
	u8 urb_state;                 /*!< URB state, @ref usbh_urb_state_t 0~4 */
	u8 ep_num;                    /*!< Endpoint number, 1~15 */

	u8 driver_idx;                /*!< Owning class driver's slot index (0..class_num-1);
	                                  USBH_PIPE_NO_OWNER(0xFF) when unowned (control EP0 or free).
	                                  Set in usbh_open_pipe() from the owner arg; read in CLASS_READY
	                                  to route URB/state events straight to the owning class. */

	u8 ep_type : 2;               /*!< Endpoint Type, @ref usb_ch_ep_type_t 0~3 */
	u8 data_pid : 2;              /*!< Initial data PID, @ref usbh_pid_t 0~3 */
	u8 ep_is_in : 1;              /*!< Endpoint direction, 0~1 */
	u8 toggle_in : 1;             /*!< IN transfer current toggle flag, 0~1 */
	u8 toggle_out : 1;            /*!< OUT transfer current toggle flag, 0~1 */
	u8 do_ping : 1;               /*!< Enable or disable the use of the PING protocol for HS mode 0~1 */
} usbh_hc_t;

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

int usbh_hal_host_init(usbh_config_t *cfg, u8 ch_max);
int usbh_hal_init_clock(void);
int usbh_hal_set_frame_interval(u8 speed);
int usbh_hal_reset_port(void);
int usbh_hal_drive_vbus(u8 state);
u8 usbh_hal_get_host_speed(void);
u32 usbh_hal_get_current_frame(void);
int usbh_hal_hc_init(usbh_hc_t *hc);
int usbh_hal_hc_start_transfer(usbh_hc_t *hc);
u32 usbh_hal_hc_read_interrupt(void);
int usbh_hal_hc_halt(u8 hc_num);
int usbh_hal_do_ping(u8 ch_num);
int usbh_hal_stop(void);

#endif /* USBH_HAL_H */
