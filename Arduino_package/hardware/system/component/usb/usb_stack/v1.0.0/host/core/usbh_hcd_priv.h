/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Private cross-file declarations for the merged HCD module.
 * Shared only between:
 *   - usbh_hcd.c       (lifecycle + hardware control)
 *   - usbh_hcd_xfer.c  (control FSM, descriptors, hub enum, message queue)
 *   - usbh_hcd_isr.c   (IRQ + per-channel handlers)
 *
 * Anything truly internal to a single .c file stays static there.
 */

#ifndef USBH_HCD_PRIV_H
#define USBH_HCD_PRIV_H

#include "usbh_hcd.h"
#include "usb_priv.h"

/* The singleton HCD handle. */
extern usbh_hcd_t usbh_hcd_inst;

/* USB 2.0 enumeration timings (ms).
 * All values follow the enum flow defined by usbh_enum_state_t /
 * usbh_hub_enum_state_t and are aligned to the USB 2.0 Specification.
 *
 *   7.1.7.3  TATTDB         >= 100 ms  connect debounce
 *   7.1.7.5  TDRSTR         >= 50 ms   root-port reset signaling (driven by HCD)
 *             TDRST          >= 10 ms   downstream-port reset signaling
 *             TRSTRCY        >= 10 ms   post-reset recovery
 *   9.2.6.3  TDSETADDR      >= 2  ms   SET_ADDRESS recovery
 *   11.11    bPwrOn2PwrGood * 2 ms     hub port power-on to power-good
 *
 * Inter-request "settling" sleeps (10 ms) match Linux usbcore behavior
 * (drivers/usb/core/hub.c) and are observed to recover low-quality
 * devices that NAK back-to-back control transfers during enumeration. */
#define USBH_T_CONNECT_DEBOUNCE_MS              110U   /* 7.1.7.3 TATTDB */
#define USBH_T_RESET_RECOVERY_MS                 20U   /* 7.1.7.5 TRSTRCY (>=10, padded) */
#define USBH_T_SET_ADDRESS_RECOVERY_MS           10U   /* 9.2.6.3 TDSETADDR (>=2,  padded) */
#define USBH_T_HUB_PORT_POLL_MS                  10U   /* hub port-status / reset poll interval */
#define USBH_T_HUB_SWITCH_TO_DEVICE_MS           20U   /* 7.1.7.5 TRSTRCY + safety margin */
/* 11.11: spec value is bPwrOn2PwrGood x 2 ms, but many cheap hubs under-report
 * bPwrOn2PwrGood. Enforce a 100 ms floor (matches Linux hub_power_on()). */
#define USBH_T_HUB_PWR_ON_TO_GOOD_MIN_MS        100U
#define USBH_T_HUB_PWR_ON_TO_GOOD_MS(bPwrOn2PwrGood) \
		(((u32)(bPwrOn2PwrGood) * 2U) > USBH_T_HUB_PWR_ON_TO_GOOD_MIN_MS \
		 ? ((u32)(bPwrOn2PwrGood) * 2U) : USBH_T_HUB_PWR_ON_TO_GOOD_MIN_MS)  /* 11.11 */
#define USBH_T_BAD_CFG_DESC_RETRY_MS             10U   /* GET_DESCRIPTOR(CONFIG) later-retry wait; 1st retry is immediate */
#define USBH_T_REENUMERATE_MS                   200U   /* post-disconnect quiesce before re-enum */

/* Internal port state codes passed to usbh_hcd_notify_port_state_change(). */
typedef enum {
	USBH_CORE_PORT_INIT = 0U,
	USBH_CORE_PORT_IDLE,
	USBH_CORE_PORT_ATTACHED,
	USBH_CORE_PORT_DETACHED,
} usbh_hcd_port_state_t;

void usbh_hcd_reset(usbh_hcd_t *hcd);
void usbh_hcd_main_task(void *argument);

/* Internal descriptor buffer management */
void usbh_hcd_destroy_config_desc(usb_host_t *host);
void usbh_hcd_destroy_desc_buf(void);
void usbh_hcd_destroy_desc_string_buf(void);
void usbh_hcd_destroy_hub_resource(usbh_hcd_t *hcd);

/* Internal interrupt and channel management */
int usbh_hcd_interrupt_init(usbh_hcd_t *hcd, usbh_config_t *cfg);
int usbh_hcd_interrupt_deinit(usbh_hcd_t *hcd);
u32 usbh_hcd_handle_hc_transfer_len(usbh_hcd_t *hcd, u8 ch_num);
int usbh_hcd_release_channel(usbh_hcd_t *hcd, u8 ch_num, u8 err_max_cnt);
int usbh_hcd_save_data_toggle(usbh_hc_t *host_ch, u8 ch_num);
int usbh_hcd_set_toggle(usbh_hcd_t *hcd, u8 ch_num, u8 toggle);
u8 usbh_hcd_get_toggle(usbh_hcd_t *hcd, u8 ch_num);

/* Map a 0/1 data toggle bit to its USB PID code. Tiny pure helper, inlined. */
static inline u8 usbh_hcd_get_data_pid_from_toggle(u8 toggle)
{
	return (toggle == 0U) ? USBH_PID_DATA0 : USBH_PID_DATA1;
}

/* Internal notifications */
int usbh_hcd_notify_urb_state_change(usbh_hcd_t *hcd, u8 param);
int usbh_hcd_notify_port_state_change(usbh_hcd_t *hcd, u32 type);

/* State-machine transitions + port state */
int usbh_hcd_connect(usbh_hcd_t *hcd);
int usbh_hcd_disconnect(usbh_hcd_t *hcd);
void usbh_hcd_disable_port(usbh_hcd_t *hcd);
void usbh_hcd_enable_port(usbh_hcd_t *hcd);
int usbh_hcd_is_port_enabled(usbh_hcd_t *hcd);

/* Port hooks */
void usbh_hcd_handle_connect_interrupt(usbh_hcd_t *hcd);
void usbh_hcd_handle_disconnect_interrupt(usbh_hcd_t *hcd);
void usbh_hcd_handle_port_enable_interrupt(usbh_hcd_t *hcd);
void usbh_hcd_handle_port_disable_interrupt(usbh_hcd_t *hcd);

#endif /* USBH_HCD_PRIV_H */
