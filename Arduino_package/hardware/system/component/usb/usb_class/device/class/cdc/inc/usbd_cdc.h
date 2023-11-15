#ifndef USBD_CDC_H
#define USBD_CDC_H
#include "basic_types.h"
#include "usbd_default.h"

#define ACM_APP_ECHO_SYNC                     0     // Echo synchronously in USB IRQ thread, for ACM_BULK_XFER_SIZE <= ACM_BULK_IN_BUF_SIZE
#define ACM_APP_ECHO_ASYNC                    1     // Echo asynchronously in dedicated USB CDC ACM bulk in thread (USBD_CDC_ACM_USE_BULK_IN_THREAD == 1), for ACM_BULK_XFER_SIZE > ACM_BULK_IN_BUF_SIZE
#define ACM_APP_LOOPBACK				2 	//loopback with AmebD usb cdc acm host

#define CONFIG_USDB_CDC_ACM_APP              (ACM_APP_ECHO_SYNC)

typedef struct {
	int(* init)(void);
	int(* deinit)(void);
	int(* receive)(void *buf, u16 length);
	void(*transmit_complete)(int status);
} usbd_cdc_acm_usr_cb_t;

int usbd_cdc_acm_init(u16 bulk_in_buf_size, u16 bulk_out_buf_size, usbd_cdc_acm_usr_cb_t *cb);
int usbd_cdc_init(void);
void usbd_cdc_deinit(void);
int cdc_port_status(void);
int usb_insert_status(void);
int usbd_cdc_acm_sync_transmit_data(void *buf, u16 length);
void usbd_cdc_stop(void);
#endif
