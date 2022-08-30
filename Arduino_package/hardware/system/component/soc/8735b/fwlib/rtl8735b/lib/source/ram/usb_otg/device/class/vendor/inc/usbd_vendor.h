#ifndef USBD_MSC_H
#define USBD_MSC_H

#include "usb.h"
#include "usb_gadget.h"
#include "usb_composite.h"
#include "rtl8735_otg.h"

/* config usb msc device debug inforation */
#define USBD_VENDOR_DEBUG          1

#if USBD_VENDOR_DEBUG
#define USBD_PRINTF(fmt, args...)                   DBG_8735B_OTG("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_ERROR(fmt, args...)                    DBG_8735B_OTG("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)                     DBG_8735B_OTG("\n\r%s: " fmt, __FUNCTION__, ## args)
#define FUN_ENTER                                   DBG_8735B_OTG("\n\r%s ==>\n", __func__)
#define FUN_EXIT                                    DBG_8735B_OTG("\n\r%s <==\n", __func__)
#define FUN_TRACE                                   DBG_8735B_OTG("\n\r%s:%d \n", __func__, __LINE__)
#else
#define USBD_PRINTF(fmt, args...)
#define USBD_ERROR(fmt, args...)                    DBG_8735B_OTG("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)
#define FUN_ENTER
#define FUN_EXIT
#define FUN_TRACE
#endif
struct vend_common;
struct vend_dev;

#define VEN_NUM_REQUESTS 1

#define VEN_MAX_PKT_LEN         2048
#define VEN_USB_DMA_ALIGN_4     4
#define VEN_NR_TX_SKB_PERBUF    1

#define VEN_BO_BUFF_SZ  VEN_NR_TX_SKB_PERBUF*VEN_MAX_PKT_LEN
#define VEN_BI_BUFF_SZ  VEN_NR_TX_SKB_PERBUF*VEN_MAX_PKT_LEN

struct ven_common {
	struct ven_dev  *vendev;
	struct usb_gadget   *gadget;
	struct usb_ep       *ep0;
	struct usb_request  *req0;      /* for control responses */
	unsigned int        running;
};

struct ven_dev {
	struct ven_common   *common;
	struct usb_function func;
	struct usb_ep       *in_ep;
	struct usb_ep       *out_ep;
	struct usb_ep       *iso_in_ep;
	struct usb_ep       *iso_out_ep;
#if 1
	struct usb_ep       *iso_in2_ep;  //wei add
//	struct usb_ep        *iso2_out_ep;
#endif

	/* Requests */
	unsigned int req_size;
#if !defined(DWC_EN_ISOC)
	struct usb_request *req_out[VEN_NUM_REQUESTS];
#else
	struct usb_iso_request *req_out[VEN_NUM_REQUESTS];
#endif
	unsigned char *req_buffer_out[VEN_NUM_REQUESTS * 2];

#if !defined(DWC_EN_ISOC)
	struct usb_request *req_in[VEN_NUM_REQUESTS];
#else
	struct usb_iso_request *req_in[VEN_NUM_REQUESTS];
	struct usb_iso_request *req_in2[VEN_NUM_REQUESTS];  //wei add
#endif
	unsigned char *req_buffer_in[VEN_NUM_REQUESTS * 2];
	unsigned char *req_buffer_in2[VEN_NUM_REQUESTS * 2]; //wei add
};

/*
* N_bh : number of buffer header
* Size_bh: buffer size per buffer
* type:msc physical disk type
*/
int usbd_vendor_init(int N_bh, int Size_bh, int type);
void usbd_vendor_deinit(void);

//declare function
int usb_assign_descriptors(struct usb_function *f,
						   struct usb_descriptor_header **fs,
						   struct usb_descriptor_header **hs,
						   struct usb_descriptor_header **ss);
void usb_free_all_descriptors(struct usb_function *f);
int usb_add_function(struct usb_configuration *config,
					 struct usb_function *function);
void usb_put_function(struct usb_function *f);
void usb_composite_unregister(struct usb_composite_driver *driver);

#endif
