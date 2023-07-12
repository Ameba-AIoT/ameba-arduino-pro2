#ifndef _MODULE_DEFAULT_H
#define _MODULE_DEFAULT_H
typedef enum {
	USBD_INIT_NONE = -1,
	USBD_INIT_OK = 0,
	USBD_INIT_FAIL = 1,
	USBD_NOT_ATTACHED = 2
} usb_status;
extern void _usb_init(void);
extern int wait_usb_ready(void);
#endif