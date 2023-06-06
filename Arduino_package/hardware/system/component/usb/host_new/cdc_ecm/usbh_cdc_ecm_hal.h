/**
  ******************************************************************************
  * The header file for usbh_cdc_ecm_hal.c
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2023, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */

#ifndef USBH_CDC_ECM_HAL_H
#define USBH_CDC_ECM_HAL_H

/* Includes ------------------------------------------------------------------*/


/* Exported defines ----------------------------------------------------------*/


/*  */


/* Exported types ------------------------------------------------------------*/
typedef void (*usb_report_usbdata)(u8 *buf, u32 len);
typedef void (*usb_cdc_ecm_attach)(void);
typedef void (*usb_cdc_ecm_detach)(void);

/* Exported macros -----------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
u8          usbh_cdc_ecm_do_init(usb_report_usbdata cb_handle);
u8          usbh_cdc_ecm_do_deinit(void);

const u8   *usbh_cdc_ecm_process_mac_str(void);
u8          usbh_cdc_ecm_senddata(u8 *buf, u32 len);
u8          usbh_cdc_ecm_get_sendflag(void);
u8          usbh_cdc_ecm_get_connect_status(void);
u16         usbh_cdc_ecm_get_receive_mps(void);

//u8   set_usbh_cdc_ecm_data_report_func(usb_report_usbdata handle);

typedef enum {
	USBH_J_MODE             = 0x00,
	USBH_K_MODE    			= 0x01,
	USBH_SE0_NAK_MODE       = 0x02,
	USBH_PACKET_MODE        = 0x03,
	USBH_FORCE_MODE         = 0x04,
} usbh_eye_pattern_t;

typedef enum {
	USBH_INIT_MODE             = 0x00,
	USBH_INIT_FAIL    		   = 0x01,
	USBH_INIT_OK               = 0x02,
} usbh_cdc_ecm_init_t;

void usbh_ecm_disable_monitor(void);
void usbh_eye_pattern(usbh_eye_pattern_t type);

typedef struct {
	usb_report_usbdata			report_data;
	usb_cdc_ecm_attach          usb_attach;
	usb_cdc_ecm_detach 			usb_detach;
} usbh_cdc_ecm_user_cb_t;

typedef struct {
	struct task_struct intr_task;
	struct task_struct bulk_task;
	struct task_struct sof_task;
	struct task_struct hotplug_task;
	_sema cdc_ecm_detach_sema;
	_sema cdc_ecm_attach_sema;
	_sema cdc_ecm_intr_start_sema;
	_sema cdc_ecm_bulk_start_sema;
} usbh_cdc_ecm_hal_t;

bool usbh_cdc_ecm_on(usbh_cdc_ecm_user_cb_t *arg);//Init the ecm procedure
bool usbh_cdc_ecm_off(void);//Deinit the ecm
bool usbd_cdc_ecm_status(void);//Get the ecm status
bool usbd_cdc_ecm_ethernt_status(void);//Get the ethernet status
#endif  /* USBH_CDC_ECM_HAL_H */

