/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USBH_HCD_H
#define USBH_HCD_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_hal.h"

/* Exported defines ----------------------------------------------------------*/
#define USBH_INVALID_PIPE_NUM                   0xFFU

/* Sentinel stored in usbh_hc_t.driver_idx to mean "no owning class driver"
 * (pipe free, or the control EP0 opened by the core enumerator). */
#define USBH_PIPE_NO_OWNER                      0xFFU

#define USBH_MAX_DATA_BUFFER                    0x200U
#define USBH_MAX_ERROR_COUNT                    0x02U
/* Message queue depth for the HCD main-task event loop.
 * The ISR can enqueue multiple events per SOF: URB completions per active
 * channel + class notify_event calls.  SOF interval is 125 us (high-speed)
 * or 1 ms (full-speed).  With up to ~8 pipes and 2 class drivers, bursts of
 * 10+ messages per SOF are possible.  32 slots give the main task enough
 * headroom before any event is dropped. */
#define USBH_MSG_QUEUE_DEPTH                    32U

#define USBH_ADDRESS_DEFAULT                    0x00U

#define USBH_TOKEN_SETUP                        0U
#define USBH_TOKEN_DATA                         1U

#define USBH_SETUP_PKT_SIZE                     8U

/* Standard Feature Selector for clear feature command */
#define USBH_FEATURE_SELECTOR_ENDPOINT          0x00U
#define USBH_FEATURE_SELECTOR_DEVICE            0x01U
#define USBH_FEATURE_SELECTOR_REMOTEWAKEUP      0X01U

#define USBH_ENABLE_BOS_DESCRIPTOR              0U

/* Exported types ------------------------------------------------------------*/

/* USB host state */
typedef enum {
	USBH_IDLE = 0U,
	USBH_WAIT_DEV_ATTACH,
	USBH_DEV_ATTACHED,
	USBH_DEV_DETACHED,
	USBH_HUB_HANDLE,
	USBH_HUB_PORT_HANDLE,
	USBH_DEVICE_ENUMERATION,
	USBH_CHOOSE_CONFIG,
	USBH_SET_CONFIG,
	USBH_SET_WAKEUP_FEATURE,
	USBH_CLASS_PROBE,
	USBH_CLASS_REQUEST,
	USBH_CLASS_READY,
	USBH_ABORTED,
} usbh_host_state_t;

/* USB enumeration state.
 * USBH_ENUM_IDLE (= 0) is the zero-initialized "not started" sentinel left by
 * usbh_hcd_init()'s memset. The state machine transitions IDLE -> GET_ADDR on
 * its first dispatch; usbh_hcd_reset() may set GET_ADDR directly to skip that
 * hop. Any new enum value must add an explicit case in
 * usbh_hcd_process_enumeration() - the default branch aborts. */
typedef enum {
	USBH_ENUM_IDLE = 0U,
	USBH_ENUM_GET_ADDR,
	USBH_ENUM_SET_ADDR,
	USBH_ENUM_GET_DEV_DESC,
	USBH_ENUM_GET_FULL_DEV_DESC,
	USBH_ENUM_GET_CFG_DESC,
	USBH_ENUM_GET_FULL_CFG_DESC,
	USBH_ENUM_DEVICE_VALIDATE,
	USBH_ENUM_GET_MFC_STRING_DESC,
	USBH_ENUM_GET_PRODUCT_STRING_DESC,
	USBH_ENUM_GET_SERIALNUM_STRING_DESC,
#if USBH_ENABLE_BOS_DESCRIPTOR
	USBH_ENUM_GET_BOS_DESC,
	USBH_ENUM_GET_FULL_BOS_DESC,
#endif
} usbh_enum_state_t;

typedef enum {
	USBH_ENUM_HUB_IDLE = 0U,
	USBH_ENUM_GET_HUB_ADDR,
	USBH_ENUM_SET_HUB_ADDR,
	USBH_ENUM_GET_HUB_DEV_DESC,
	USBH_ENUM_GET_HUB_FULL_DEV_DESC,
	USBH_ENUM_GET_HUB_MFC_STRING_DESC,
	USBH_ENUM_GET_HUB_PRODUCT_STRING_DESC,
	USBH_ENUM_GET_HUB_SERIALNUM_STRING_DESC,

#if USBH_ENABLE_BOS_DESCRIPTOR
	USBH_ENUM_GET_HUB_BOS_DESC,
	USBH_ENUM_GET_HUB_FULL_BOS_DESC,
#endif

	USBH_ENUM_GET_HUB_CFG_DESC,
	USBH_ENUM_GET_HUB_FULL_CFG_DESC,
	USBH_ENUM_GET_HUB_SET_CFG_IDX,
	USBH_ENUM_SET_HUB_REMOTE_WAKEUP,
	USBH_ENUM_SET_HUB_ITF,
	USBH_ENUM_GET_HUB_DEV_STATUS,
	USBH_ENUM_GET_HUB_DESC,
	USBH_ENUM_SET_HUB_PORT_POWER_ON,
	USBH_ENUM_GET_HUB_PORT_POWER_STATUS,
	USBH_ENUM_GET_HUB_STATUS,
	USBH_ENUM_GET_HUB_PORT_CONNECT_EVENT,
	USBH_ENUM_CLEAR_HUB_PORT_CONNECT_STATUS,
	USBH_ENUM_HUB_STATUS_FINISH,

	USBH_ENUM_HUB_PORT_XFER,
	USBH_ENUM_GET_VALID_HUB_PORT,
	USBH_ENUM_SET_HUB_PORT_RESET,
	USBH_ENUM_SET_HUB_PORT_RESET_EVENT,
	USBH_ENUM_CLEAR_HUB_PORT_RESET_STATUS,
	USBH_ENUM_GET_HUB_PORT_STATUS,

	USBH_ENUM_HUB_SWITCH_TO_DEVICE,
} usbh_hub_enum_state_t;

/* USB control transfer state */
typedef enum {
	USBH_CTRL_IDLE = 0U,
	USBH_CTRL_SETUP,
	USBH_CTRL_SETUP_BUSY,
	USBH_CTRL_DATA_IN,
	USBH_CTRL_DATA_IN_BUSY,
	USBH_CTRL_DATA_OUT,
	USBH_CTRL_DATA_OUT_BUSY,
	USBH_CTRL_STATUS_IN,
	USBH_CTRL_STATUS_IN_BUSY,
	USBH_CTRL_STATUS_OUT,
	USBH_CTRL_STATUS_OUT_BUSY,
	USBH_CTRL_ERROR,
	USBH_CTRL_STALLED,
	USBH_CTRL_COMPLETE
} usbh_ctrl_xfer_state_t;

/* USB control request state */
typedef enum {
	USBH_CTRL_REQ_IDLE = 0U,
	USBH_CTRL_REQ_SEND,
	USBH_CTRL_REQ_BUSY
} usbh_ctrl_req_state_t;

/* USB event */
typedef enum {
	USBH_PORT_EVENT = 1U,
	USBH_URB_EVENT,
	USBH_CONTROL_EVENT,
	USBH_CLASS_EVENT,
	USBH_STATE_CHANGED_EVENT,
} usbh_event_type_t;

/* HCD hardware state */
typedef enum {
	USBH_HCD_STATE_RESET = 0x00,
	USBH_HCD_STATE_READY = 0x01,
	USBH_HCD_STATE_ERROR = 0x02,
	USBH_HCD_STATE_BUSY  = 0x03
} usbh_hcd_state_t;

/* USB control request */
typedef struct {
	usbh_setup_req_t *setup;               /* Setup request */
	u8 *buf;                               /* Request buffer */
	u16 len;                               /* Request length */
	u8 pipe_in;                            /* In pipe number */
	u8 pipe_out;                           /* Out pipe number */
	u8 mps;                                /* Pipe mps */
	u8 error_cnt;                          /* Error count, USBH_MSG_ERROR will be issued if USBH_MAX_ERROR_COUNT achieved */
	u8 state;                              /* Control transfer state, @ref usbh_ctrl_xfer_state_t */
	u8 owner_slot;                         /* Class slot that owns the in-flight EP0 transfer; USBH_PIPE_NO_OWNER during enum */
} usbh_ctrl_req_t;

/* USB config descriptor struct*/
typedef struct {
	usbh_cfg_desc_t cfg_desc;              /* Parsed configuration descriptor */
	u8 *cfg_buf;                           /* Raw data for configuration descriptor */
	u16 cfg_buf_len;
} usbh_cfg_desc_data;

/*
	Support hub based on the following assumptions:
	1. only one hub at the top
	2. only one config descriptor for the hub
*/
typedef struct {
	u8 hub_cfg_buf[USBH_MAX_DATA_BUFFER];  /* Raw data for configuration descriptor */
	usbh_dev_desc_t hub_dev_desc;          /* hub device descriptor */
	usbh_cfg_desc_t hub_cfg_desc;          /* hub configuration descriptor */
	usbh_hub_desc_t hub_desc;              /* hub descriptor */
#if USBH_ENABLE_BOS_DESCRIPTOR
	usbh_dev_bos_t hub_bos_desc;           /* hub bos descriptor */
#endif
	u32 port_connected;                    /* hub port connected idx */
	u32 port_connected_check;              /* hub port connected idx backup */
	u16 port_status;
	u16 port_change;
	u8 port_idx;                           /* choose port idx 1,2,3.... 32 */
	u8 hub_address;                        /* hub address */
	u8 hub_cfg_idx;                        /* index for config desc, which config is used */
} usbh_hub_dev_t;

/* Per-class-driver registration slot (indexed by registration order 0..config.class_num-1).
 * Grouping driver pointer + attach flag improves memory locality (single
 * cache line per slot) and lets us do a single allocation for the whole
 * class_slot[] array in usbh_hcd_init(). */
typedef struct {
	const usbh_class_driver_t *driver;   /* Registered class driver, NULL if slot unused */
	u8 attached;                   /* Phase 2 attach() result: 1 = attached, 0 = not */
} usbh_class_slot_t;

/* USB device */
typedef struct {
	usbh_dev_desc_t dev_desc;               /* Parsed device descriptor */
#if USBH_ENABLE_BOS_DESCRIPTOR
	usbh_dev_bos_t bos_desc;                /* Bos descriptor */
#endif
	usbh_hub_dev_t *hub_dev;
	usbh_cfg_desc_data *cfg_data_array;     /* configuration descriptors */
	u8 *desc_buf;                           /* Raw buffer for device descriptor */
	u8 *desc_string_buf;                    /* Raw buffer for device string descriptor */

	u16 string_buf_len;                     /* Desc_string_buf length */
	u8 cfg_idx;                             /* index for cfg_data_array, which config is used */
	u8 cfg_count_max;                       /* max count for config_desc */
	u8 dev_num;                             /* Device count. Default Address is 0, real addresses start with 1 */
	u8 address;                             /* Device address */
	u8 speed;                               /* Device speed 0~3 */
	__IO u8 is_connected;                   /* Flag indicates whether device is connected 0~1 */
	__IO u8 port_enabled;                   /* Flag indicates whether port is enabled 0~1 */
	__IO u8 hub_connected;                  /* Flag indicates hub is connected 0~1 */
	__IO u8 hub_multi_port;                 /* Flag indicates hub has more than 1 port */
} usbh_dev_t;

/* HCD per-channel transfer parameters */
typedef struct {
	u8 *buf;      /* Data buffer */
	u16 length;   /* Data length */
	u8 ch_num;    /* Channel num */
	u8 is_in;     /* Direction: 0 OUT/1 in */
	u8 ep_type;   /* EP type */
	u8 token;     /* Type Data */
} usbh_xfer_params_t;

/*
 * HCD handle. One singleton instance (usbh_hcd_inst, see priv header) holds
 * both the host-stack state and the per-channel hardware state for the device.
 */
typedef struct {
	/* Host-stack state */
	usbh_dev_t device;                                       /* Attached device */
	usbh_config_t config;                                    /* User configuration  */
	usbh_ctrl_req_t ctrl_req;                                /* Current control request */

	/* Host process routine parameters */
	usb_os_queue_t msg_queue;                                /* Host message queue */
	usb_os_task_t main_task;                                 /* Host main task dealing with host message queue */

	/*
	 * Registered class drivers plus per-driver bookkeeping, indexed
	 * by registration order (0 .. config.class_num-1).
	 *
	 *   class_slot[k].driver   - registered driver pointer; NULL until
	 *                            usbh_register_class() fills the slot.
	 *   class_slot[k].attached - 1 after Phase-2 attach() returns HAL_OK;
	 *                            cleared to 0 on DEV_DETACHED.
	 *
	 * Dynamically allocated in usbh_hcd_init() to config.class_num entries;
	 * freed in usbh_hcd_deinit().
	 */
	usbh_class_slot_t *class_slot;

	/*
	 * active_class_driver[i]: Phase-1 (CLASS_PROBE) result - the class driver
	 * that claimed interface i via id_table match, or NULL if no driver matched.
	 * Indexed by position in cfg_data_array[cfg_idx].cfg_desc.itf_data_array[]
	 * (NOT by bInterfaceNumber).
	 *
	 * Interfaces with no matching driver (e.g. CDC Data class 0x0A, vendor
	 * companion interfaces) are left NULL; the owning driver reaches them
	 * directly inside attach() and opens their endpoints.
	 *
	 * Dynamically allocated in CLASS_PROBE to bNumInterfaces entries;
	 * freed on DEV_DETACHED.  NULL when no device is being probed.
	 */
	const usbh_class_driver_t **active_class_driver;

	usb_host_t *host;                                        /* Host handler */

	__IO u32 tick;                                           /* Host timer tick */

	u16 pipes[USB_MAX_PIPES];                                /* Pipes */

	/* HCD per-channel hardware state */
	usbh_hc_t hc[USB_MAX_PIPES];                             /* Host channels parameters */

	/* any_driver_attached: fast gate = OR of all class_slot[k].attached.
	 * Avoids rescanning class_slot[] on every CLASS_REQUEST/CLASS_READY tick.
	 * Set to 1 when the first driver's attach() succeeds; cleared on DEV_DETACHED. */
	u8 any_driver_attached;
	__IO u8 hcd_state;                                       /* HCD communication state, @ref usbh_hcd_state_t */

	/* started: set to 1 by usbh_hcd_start() after VBUS is driven and global
	 * interrupts are enabled (USB TRX live); cleared by usbh_hcd_stop().
	 * Guards against redundant hardware writes if start() is called twice. */
	__IO u8 started;

	/* setup_idx: cursor for USBH_CLASS_REQUEST serial setup.
	 * Points at the class currently being set up; its setup() is a state
	 * machine returning HAL_BUSY until done and HAL_OK when complete.
	 * On HAL_OK the cursor advances to the next attached class.
	 * When setup_idx >= config.class_num all setups are done -> CLASS_READY.
	 * Reset to 0 on entering CLASS_REQUEST and on DEV_DETACHED. */
	u8 setup_idx;

	/* State machines */
	u8 state;                                                /* Host state, @ref usbh_host_state_t */
	u8 enum_state;                                           /* Host Enumeration state, @ref usbh_enum_state_t */
	u8 ctrl_req_state;                                       /* Control request state, @ref usbh_ctrl_req_state_t */
	u8 active_ctrl_owner;                                    /* Class slot whose process() is currently running (CLASS_READY dispatch); binds the EP0 ctrl owner. USBH_PIPE_NO_OWNER when none */
	u8 class_num;                                            /* Number of registered class drivers (0..config.class_num) */
	u8 hub_state;                                            /* Hub Enumeration state, @ref usbh_hub_enum_state_t */

	u8 dev_desc_err_cnt;                                     /* Retry counter for invalid GET_DESCRIPTOR(DEVICE) responses */
	u8 cfg_desc_err_cnt;                                     /* Retry counter for invalid GET_DESCRIPTOR(CONFIGURATION) responses */

	u8 host_ch_max : 7;                                      /* Max host pipes get from HWCFG, max 16 */
	u8 isr_initialized : 1;                                  /* ISR initialized */
} usbh_hcd_t;

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* Lifecycle */
int usbh_hcd_init(usb_host_t *host, const usbh_config_t *cfg);
int usbh_hcd_deinit(usb_host_t *host);
int usbh_hcd_reenumerate(usb_host_t *host);

/* HCD hardware control and transfer functions */
int usbh_hcd_start(usbh_hcd_t *hcd);
int usbh_hcd_stop(usbh_hcd_t *hcd);
int usbh_hcd_hc_submit_request(usbh_hcd_t *hcd, usbh_xfer_params_t *param);
u32 usbh_hcd_hc_get_rx_len(usbh_hcd_t *hcd, u8 ch_num);
void usbh_hcd_enter_suspend(u8 flag);
int usbh_hcd_port_test_ctrl(u8 mode);

/* NAK retry helpers (used by usbh_transfer_process) */
int usbh_hcd_enable_nak_interrupt(usbh_hcd_t *hcd, u8 ch_num);
int usbh_hcd_check_nak_timeout(usbh_hcd_t *hcd, u8 ch_num, u16 tick_cnt);
int usbh_hcd_increase_busy_cnt(usbh_hcd_t *hcd, u8 ch_num, u8 step);
int usbh_hcd_prepare_retransfer(usbh_hcd_t *hcd, u8 ch_num);

/* Pipe management */
int usbh_hcd_alloc_pipe(usbh_hcd_t *hcd, u8 ep_addr, u8 *pipe_num);
int usbh_hcd_free_pipe(usbh_hcd_t *hcd, u8 pipe_num);
int usbh_hcd_open_pipe(usbh_hcd_t *hcd, u8 pipe_num, u8 ep_num, u8 ep_type, u16 mps, u8 dev_addr);
int usbh_hcd_close_pipe(usbh_hcd_t *hcd, u8 pipe_num);

/* Standard control requests */
int usbh_hcd_ctrl_set_interface(usbh_hcd_t *hcd, u8 itf_num, u8 alt_setting);
int usbh_hcd_ctrl_set_feature(usbh_hcd_t *hcd, u8 value);
int usbh_hcd_ctrl_clear_feature(usbh_hcd_t *hcd, u8 ep_num);
int usbh_hcd_ctrl_request(usbh_hcd_t *hcd, usbh_setup_req_t *setup, u8 *buf);
int usbh_hcd_transfer_data(usbh_hcd_t *hcd, usbh_pipe_t *ep);

/* State change notifications */
int usbh_hcd_notify_class_state_change(usbh_hcd_t *hcd, u8 param, u8 slot_idx);

/* URB / class queries */
usbh_urb_state_t usbh_hcd_get_urb_state(usbh_hcd_t *hcd, u8 pipe_num);
u8 usbh_hcd_get_cfg_idx_from_subclass(usbh_hcd_t *hcd, usbh_dev_id_t *id);
int usbh_hcd_set_configuration(usbh_hcd_t *hcd, u8 cfg);
usbh_itf_data_t *usbh_hcd_get_interface_descriptor(usbh_hcd_t *hcd, usbh_dev_id_t *id);

/* Time tick */
u32 usbh_hcd_get_time_tick(void);

#endif /* USBH_HCD_H */
