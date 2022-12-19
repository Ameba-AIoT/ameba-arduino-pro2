#ifndef USBD_CDC_H
#define USBD_CDC_H

#include "usb.h"
#include "usb_gadget.h"
#include "core/inc/usb_composite.h"

#define ACM_APP_ECHO_SYNC                     0     // Echo synchronously in USB IRQ thread, for ACM_BULK_XFER_SIZE <= ACM_BULK_IN_BUF_SIZE
#define ACM_APP_ECHO_ASYNC                    1     // Echo asynchronously in dedicated USB CDC ACM bulk in thread (USBD_CDC_ACM_USE_BULK_IN_THREAD == 1), for ACM_BULK_XFER_SIZE > ACM_BULK_IN_BUF_SIZE
#define ACM_APP_LOOPBACK				2 	//loopback with AmebD usb cdc acm host

#define CONFIG_USDB_CDC_ACM_APP              (ACM_APP_ECHO_SYNC)

// Use thread for bulk in transfer, turn it on when using usbd_cdc_acm_async_transmit_data API to transfer large data,
// which can not be transfered via single bulk in transfer, i.e. the transfer size is larger than bulk_in_buf_size.
#define USBD_CDC_ACM_USE_BULK_IN_THREAD          1

// Allocate async bulk in buffer, turn it on to release bulk in transfer buffer in user application ASAP.
#define USBD_CDC_ACM_ALLOC_ASYNC_BULK_IN_BUF     0

// Bulk in request number
#define USBD_CDC_ACM_BULK_IN_REQ_NUM             20

// Bulk out request number
#define USBD_CDC_ACM_BULK_OUT_REQ_NUM            10

// Bulk transfer configurations
#define USBD_CDC_ACM_HS_BULK_MAX_PACKET_SIZE     512
#define USBD_CDC_ACM_FS_BULK_MAX_PACKET_SIZE     64

#define USBD_CDC_ACM_HS_BULK_IN_PACKET_SIZE     (USBD_CDC_ACM_HS_BULK_MAX_PACKET_SIZE)
#define USBD_CDC_ACM_HS_BULK_OUT_PACKET_SIZE    (USBD_CDC_ACM_HS_BULK_MAX_PACKET_SIZE)
#define USBD_CDC_ACM_FS_BULK_IN_PACKET_SIZE     (USBD_CDC_ACM_FS_BULK_MAX_PACKET_SIZE)
#define USBD_CDC_ACM_FS_BULK_OUT_PACKET_SIZE    (USBD_CDC_ACM_FS_BULK_MAX_PACKET_SIZE)

#define USBD_CDC_ACM_MAX_BULK_IN_XFER_SIZE       65535

#define USBD_CDC_ACM_DEFAULT_BULK_IN_XFER_SIZE   1024  // Shall be <= USBD_CDC_ACM_MAX_BULK_IN_XFER_SIZE, restrict it to save memory
#define USBD_CDC_ACM_DEFAULT_BULK_OUT_XFER_SIZE  1024  // Shall be <= USBD_CDC_ACM_MAX_BULK_IN_XFER_SIZE, restrict it to save memory
#define USBD_CDC_ACM_DEFAULT_INT_IN_XFER_SIZE  16

// Bulk in task configurations
#define USBD_CDC_ACM_BULK_IN_TASK_PRIORITY      (tskIDLE_PRIORITY + 2) // Should be lower than USBD_IRQ_THREAD_PRIORITY
#define USBD_CDC_ACM_BULK_IN_TASK_STACK_SIZE     512

// Endpoint address
#define USBD_CDC_ACM_BULK_IN_EP_ADDRESS          0x81
#define USBD_CDC_ACM_BULK_OUT_EP_ADDRESS         0x02
#define USBD_CDC_ACM_INT_IN_EP_ADDRESS           0x83

// CDC descriptor types
#define USBD_CDC_HEADER_TYPE                     0x00
#define USBD_CDC_CALL_MANAGEMENT_TYPE            0x01
#define USBD_CDC_ACM_TYPE                        0x02
#define USBD_CDC_UNION_TYPE                      0x06
#define USBD_CDC_COUNTRY_TYPE                    0x07
#define USBD_CDC_NETWORK_TERMINAL_TYPE           0x0A
#define USBD_CDC_ETHERNET_TYPE                   0x0F
#define USBD_CDC_WHCM_TYPE                       0x11
#define USBD_CDC_MDLM_TYPE                       0x12
#define USBD_CDC_MDLM_DETAIL_TYPE                0x13
#define USBD_CDC_DMM_TYPE                        0x14
#define USBD_CDC_OBEX_TYPE                       0x15

// CDC subclass
#define USBD_CDC_SUBCLASS_ACM                    0x02
#define USBD_CDC_SUBCLASS_ETHERNET               0x06
#define USBD_CDC_SUBCLASS_WHCM                   0x08
#define USBD_CDC_SUBCLASS_DMM                    0x09
#define USBD_CDC_SUBCLASS_MDLM                   0x0A
#define USBD_CDC_SUBCLASS_OBEX                   0x0B

// CDC ACM protocol
#define USBD_CDC_ACM_PROTO_NONE                  0x00
#define USBD_CDC_ACM_PROTO_AT                    0x01
#define USBD_CDC_ACM_PROTO_VENDOR                0xFF

// CDC ACM requests
#define USBD_CDC_SEND_ENCAPSULATED_COMMAND       0x00U
#define USBD_CDC_GET_ENCAPSULATED_RESPONSE       0x01U
#define USBD_CDC_SET_COMM_FEATURE                0x02U
#define USBD_CDC_GET_COMM_FEATURE                0x03U
#define USBD_CDC_CLEAR_COMM_FEATURE              0x04U
#define USBD_CDC_SET_LINE_CODING                 0x20U
#define USBD_CDC_GET_LINE_CODING                 0x21U
#define USBD_CDC_SET_CONTROL_LINE_STATE          0x22U
#define USBD_CDC_SEND_BREAK                      0x23U

// CDC ACM debug options
#define USBD_CDC_ACM_DEBUG                       0
#if USBD_CDC_ACM_DEBUG
#define USBD_CDC_INFO(fmt, args...)              printf("\n\r[CDC]%s: " fmt, __FUNCTION__, ## args)
#define USBD_CDC_WARN(fmt, args...)              printf("\n\r[CDC]%s: " fmt, __FUNCTION__, ## args)
#define USBD_CDC_ERROR(fmt, args...)             printf("\n\r[CDC]%s: " fmt, __FUNCTION__, ## args)
#define USBD_CDC_ENTER                           printf("\n\r[CDC]%s: =>", __FUNCTION__)
#define USBD_CDC_EXIT                            printf("\n\r[CDC]%s: <=", __FUNCTION__)
#define USBD_CDC_EXIT_ERR                        printf("\n\r[CDC]%s: ERR <=", __FUNCTION__)
#else
#define USBD_CDC_INFO(fmt, args...)
#define USBD_CDC_WARN(fmt, args...)
#define USBD_CDC_ERROR(fmt, args...)             //printf("\n\r[CDC]%s: " fmt, __FUNCTION__, ## args)
#define USBD_CDC_ENTER
#define USBD_CDC_EXIT
#define USBD_CDC_EXIT_ERR
#endif

/* config usb msc device debug inforation */
#define USBD_MSC_DEBUG          0
#if defined(CONFIG_PLATFORM_8195BHP)
#if	USBD_MSC_DEBUG
#define USBD_PRINTF(fmt, args...)		            DBG_8195BL("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_ERROR(fmt, args...)		            DBG_8195BL("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)		            	DBG_8195BL("\n\r%s: " fmt, __FUNCTION__, ## args)
#define FUN_ENTER                                   DBG_8195BL("\n\r%s ==>\n", __func__)
#define FUN_EXIT                                    DBG_8195BL("\n\r%s <==\n", __func__)
#define FUN_TRACE                                   DBG_8195BL("\n\r%s:%d \n", __func__, __LINE__)
#else
#define USBD_PRINTF(fmt, args...)
#define USBD_ERROR(fmt, args...)		            DBG_8195BL("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)
#define FUN_ENTER
#define FUN_EXIT
#define FUN_TRACE
#endif
#else
#if	USBD_MSC_DEBUG
#define USBD_PRINTF(fmt, args...)		            DBG_8195A("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_ERROR(fmt, args...)		            DBG_8195A("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)		            	DBG_8195A("\n\r%s: " fmt, __FUNCTION__, ## args)
#define FUN_ENTER                                   DBG_8195A("\n\r%s ==>\n", __func__)
#define FUN_EXIT                                    DBG_8195A("\n\r%s <==\n", __func__)
#define FUN_TRACE                                   DBG_8195A("\n\r%s:%d \n", __func__, __LINE__)
#else
#define USBD_PRINTF(fmt, args...)
#define USBD_ERROR(fmt, args...)		            DBG_8195A("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)
#define FUN_ENTER
#define FUN_EXIT
#define FUN_TRACE
#endif
#endif

#pragma pack(push)
#pragma pack(1)

struct usb_cdc_notification {
	u8 bmRequestType;
	u8 bNotificationType;
	u16 wValue;
	u16 wIndex;
	u16 wLength;
};

/*Class specific notification type*/
#define USB_CDC_NOTIFY_NETWORK_CONNECTION			0x00
#define USB_CDC_NOTIFY_SERIAL_STATE					0x20

// Header Functional Descriptor
struct usb_cdc_header_desc {
	u8  bLength;
	u8  bDescriptorType;
	u8  bDescriptorSubType;

	u16 bcdCDC;
} __attribute__((packed));

#define USBD_CDC_DT_HEADER_SIZE 5

// Call Management Descriptor
struct usb_cdc_call_mgmt_descriptor {
	u8  bLength;
	u8  bDescriptorType;
	u8  bDescriptorSubType;

	u8  bmCapabilities;
#define USB_CDC_CALL_MGMT_CAP_CALL_MGMT     0x01
#define USB_CDC_CALL_MGMT_CAP_DATA_INTF     0x02

	u8  bDataInterface;
} __attribute__((packed));

#define USBD_CDC_DT_CALL_MGMT_SIZE 5

// Abstract Control Management Descriptor
struct usb_cdc_acm_descriptor {
	u8  bLength;
	u8  bDescriptorType;
	u8  bDescriptorSubType;

	u8  bmCapabilities;
} __attribute__((packed));

#define USBD_CDC_DT_ACM_SIZE 4

// Union Functional Descriptor
struct usb_cdc_union_desc {
	u8  bLength;
	u8  bDescriptorType;
	u8  bDescriptorSubType;

	u8  bControlInterface;
	u8  bSubordinateInterface0;
} __attribute__((packed));

#define USBD_CDC_DT_UNION_SIZE 5

typedef struct {
	u32 dwDTERate;
	u8  bCharFormat;
	u8  bParityType;
	u8  bDataBits;
}  __attribute__((packed)) usbd_cdc_acm_line_coding_t;

#define USBD_CDC_ACM_LINE_CODING_SIZE      7

#define USBD_CDC_ACM_CHAR_FORMAT_STOP_1    0
#define USBD_CDC_ACM_CHAR_FORMAT_STOP_1_5  1
#define USBD_CDC_ACM_CHAR_FORMAT_STOP_2    2

#define USBD_CDC_ACM_PARITY_TYPE_NONE      0
#define USBD_CDC_ACM_PARITY_TYPE_ODD       1
#define USBD_CDC_ACM_PARITY_TYPE_EVEN      2
#define USBD_CDC_ACM_PARITY_TYPE_MARK      3
#define USBD_CDC_ACM_PARITY_TYPE_SPACE     4

#define USBD_CDC_ACM_DATA_BIT_5            5
#define USBD_CDC_ACM_DATA_BIT_6            6
#define USBD_CDC_ACM_DATA_BIT_7            7
#define USBD_CDC_ACM_DATA_BIT_8            8
#define USBD_CDC_ACM_DATA_BIT_16           16

typedef union {
	u16 d16;
	struct {
		unsigned present: 1;
		unsigned activate: 1;
		unsigned reserved_2_15: 14;
	} b;
}  __attribute__((packed)) usbd_cdc_acm_ctrl_line_state_t;

#pragma pack(pop)

#define USBD_CDC_ACM_STRING_MANUFACTURER        1
#define USBD_CDC_ACM_STRING_PRODUCT             2
#define USBD_CDC_ACM_STRING_SERIALNUMBER        3

// Default PID/VID
#define REALTEK_USB_VID             0x0BDA
#define REALTEK_USB_PID             0x4042


// CDC ACM Device Descriptor
static struct usb_device_descriptor cdc_acm_device_desc = {
	.bLength            = USB_DT_DEVICE_SIZE,
	.bDescriptorType    = USB_DT_DEVICE,
	.bcdUSB             = 0x0200,
	.bDeviceClass       = USB_CLASS_COMM,
	.bDeviceSubClass    = 0,
	.bDeviceProtocol    = 0,
	.bMaxPacketSize0    = 64,
	.idVendor           = REALTEK_USB_VID,
	.idProduct          = REALTEK_USB_PID,
	.bcdDevice          = 0x0100,
	.iManufacturer      = USBD_CDC_ACM_STRING_MANUFACTURER,
	.iProduct           = USBD_CDC_ACM_STRING_PRODUCT,
	.iSerialNumber      = USBD_CDC_ACM_STRING_SERIALNUMBER,
	.bNumConfigurations = 1,
};

// CDC ACM Communication Interface
static struct usb_interface_descriptor cdc_acm_comm_if_desc = {
	.bLength            = USB_DT_INTERFACE_SIZE,
	.bDescriptorType    = USB_DT_INTERFACE,
	.bInterfaceNumber   = 0,                        // This will be assign automatically
	.bAlternateSetting  = 0,
	.bNumEndpoints      = 1,
	.bInterfaceClass    = USB_CLASS_COMM,
	.bInterfaceSubClass = USBD_CDC_SUBCLASS_ACM,    // Abstract Control Model
	.bInterfaceProtocol = USBD_CDC_ACM_PROTO_NONE,  // None
	.iInterface         = 0,
};

// CDC ACM Function Header Descriptor
static struct usb_cdc_header_desc cdc_acm_header_desc = {
	.bLength            = USBD_CDC_DT_HEADER_SIZE,
	.bDescriptorType    = USB_DT_CS_INTERFACE,
	.bDescriptorSubType = USBD_CDC_HEADER_TYPE,

	.bcdCDC             = 0x0110,
};

// CDC ACM Call Magagement Functional Descriptor
static struct usb_cdc_call_mgmt_descriptor cdc_acm_call_mgmt_desc = {
	.bLength            = USBD_CDC_DT_CALL_MGMT_SIZE,
	.bDescriptorType    = USB_DT_CS_INTERFACE,
	.bDescriptorSubType = USBD_CDC_CALL_MANAGEMENT_TYPE,

	.bmCapabilities     = 0x00,
	.bDataInterface     = 0x01,
};

// CDC ACM ACM Functional Descriptor
static struct usb_cdc_acm_descriptor cdc_acm_acm_desc = {
	.bLength            = USBD_CDC_DT_ACM_SIZE,
	.bDescriptorType    = USB_DT_CS_INTERFACE,
	.bDescriptorSubType = USBD_CDC_ACM_TYPE,

	.bmCapabilities     = 0x02,
};

// CDC ACM Union Functional Descriptor
static struct usb_cdc_union_desc cdc_acm_union_desc = {
	.bLength            = USBD_CDC_DT_UNION_SIZE,
	.bDescriptorType    = USB_DT_CS_INTERFACE,
	.bDescriptorSubType = USBD_CDC_UNION_TYPE,

	.bControlInterface  = 0,     // index of control interface
	.bSubordinateInterface0 = 1, // index of data interface
};

// CDC ACM Communication INT IN Endpoint for Low-speed/Full-speed, unused
static struct usb_endpoint_descriptor usbd_cdc_acm_notify_ep_desc_FS = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USBD_CDC_ACM_INT_IN_EP_ADDRESS,
	.bmAttributes       = USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize     = USBD_CDC_ACM_DEFAULT_INT_IN_XFER_SIZE,
	.bInterval          = 16,

};

// CDC ACM Communication INT IN Endpoint for High-speed, unused
static struct usb_endpoint_descriptor usbd_cdc_acm_notify_ep_desc_HS = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USBD_CDC_ACM_INT_IN_EP_ADDRESS,
	.bmAttributes       = USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize     = USBD_CDC_ACM_DEFAULT_INT_IN_XFER_SIZE,
	.bInterval          = 16,

};

// CDC ACM Data Interface
static struct usb_interface_descriptor cdc_acm_data_if_desc = {
	.bLength            = USB_DT_INTERFACE_SIZE,
	.bDescriptorType    = USB_DT_INTERFACE,

	.bInterfaceNumber   = 1,
	.bAlternateSetting  = 0,
	.bNumEndpoints      = 2,
	.bInterfaceClass    = USB_CLASS_CDC_DATA,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface         = 0,
};

// CDC ACM Data Bulk IN Endpoint for Low-speed/Full-speed
static struct usb_endpoint_descriptor cdc_acm_data_bulk_in_ep_desc_FS = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USBD_CDC_ACM_BULK_IN_EP_ADDRESS,
	.bmAttributes       = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize     = USBD_CDC_ACM_FS_BULK_MAX_PACKET_SIZE,
	.bInterval          = 0,
};

// CDC ACM Data Bulk OUT Endpoint for Low-speed/Full-speed
static struct usb_endpoint_descriptor cdc_acm_data_bulk_out_ep_desc_FS = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USBD_CDC_ACM_BULK_OUT_EP_ADDRESS,
	.bmAttributes       = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize     = USBD_CDC_ACM_FS_BULK_MAX_PACKET_SIZE,
	.bInterval          = 0,
};

// CDC ACM Data Bulk IN Endpoint for High-speed
static struct usb_endpoint_descriptor cdc_acm_data_bulk_in_ep_desc_HS = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USBD_CDC_ACM_BULK_IN_EP_ADDRESS,
	.bmAttributes       = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize     = USBD_CDC_ACM_HS_BULK_MAX_PACKET_SIZE,
	.bInterval          = 0,
};

// CDC ACM Data Bulk OUT Endpoint for High-speed
static struct usb_endpoint_descriptor cdc_acm_data_bulk_out_ep_desc_HS = {
	.bLength            = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType    = USB_DT_ENDPOINT,
	.bEndpointAddress   = USBD_CDC_ACM_BULK_OUT_EP_ADDRESS,
	.bmAttributes       = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize     = USBD_CDC_ACM_HS_BULK_MAX_PACKET_SIZE,
	.bInterval          = 0,
};

static struct usb_descriptor_header *cdc_acm_descriptors_FS[] = {
	(struct usb_descriptor_header *) &cdc_acm_comm_if_desc,
	(struct usb_descriptor_header *) &cdc_acm_header_desc,
	(struct usb_descriptor_header *) &cdc_acm_call_mgmt_desc,
	(struct usb_descriptor_header *) &cdc_acm_acm_desc,
	(struct usb_descriptor_header *) &cdc_acm_union_desc,
	(struct usb_descriptor_header *) &usbd_cdc_acm_notify_ep_desc_FS,
	(struct usb_descriptor_header *) &cdc_acm_data_if_desc,
	(struct usb_descriptor_header *) &cdc_acm_data_bulk_in_ep_desc_FS,
	(struct usb_descriptor_header *) &cdc_acm_data_bulk_out_ep_desc_FS,
	NULL,
};

static struct usb_descriptor_header *cdc_acm_descriptors_HS[] = {
	(struct usb_descriptor_header *) &cdc_acm_comm_if_desc,
	(struct usb_descriptor_header *) &cdc_acm_header_desc,
	(struct usb_descriptor_header *) &cdc_acm_call_mgmt_desc,
	(struct usb_descriptor_header *) &cdc_acm_acm_desc,
	(struct usb_descriptor_header *) &cdc_acm_union_desc,
	(struct usb_descriptor_header *) &usbd_cdc_acm_notify_ep_desc_HS,
	(struct usb_descriptor_header *) &cdc_acm_data_if_desc,
	(struct usb_descriptor_header *) &cdc_acm_data_bulk_in_ep_desc_HS,
	(struct usb_descriptor_header *) &cdc_acm_data_bulk_out_ep_desc_HS,
	NULL,
};



static struct usb_string cdc_acm_strings[] = {
	{
		.id = USBD_CDC_ACM_STRING_MANUFACTURER,
		.s  = "Realtek",
	},
	{
		.id = USBD_CDC_ACM_STRING_PRODUCT,
		.s  = "USB CDC ACM Device",
	},
	{
		.id = USBD_CDC_ACM_STRING_SERIALNUMBER,
		.s  = "0123456789AB",
	},
};

static struct usb_gadget_strings cdc_acm_gadget_string_tab = {
	.language = 0x0409,
	.strings = cdc_acm_strings,
};

static struct usb_gadget_strings *cdc_acm_gadget_strings[] = {
	&cdc_acm_gadget_string_tab,
	NULL
};

enum data_direction {
	DATA_DIR_UNKNOWN = 0,
	DATA_DIR_FROM_HOST,
	DATA_DIR_TO_HOST,
	DATA_DIR_NONE
};

struct cdc_common {
	struct msc_dev	*mscdev;

	struct usb_gadget	*gadget;
	struct usb_ep		*ep0;
	struct usb_request	*req0;		/* for control responses */
	u32 running;
};

typedef struct {
	int(* init)(void);
	int(* deinit)(void);
	int(* receive)(void *buf, u16 length);
	void(*transmit_complete)(int status);
} usbd_cdc_acm_usr_cb_t;


struct usb_cdc_dev_t {

	struct usb_ep		*ep0;
	struct usb_request	*req0;		/* for control responses */
	u32 running;

	struct cdc_common 	*common;

	int 		interface_number;
	int			config;
	struct usb_gadget *gadget;

	struct usb_ep	*bulk_in_ep;
	_list bulk_in_req_list;
	u16 bulk_in_req_num;
	volatile u16 bulk_in_req_act_num;
	u16 bulk_in_buf_size;
	_mutex bulk_in_mutex;
	volatile int bulk_in_busy;

	struct usb_ep	*bulk_out_ep;
	_list bulk_out_req_list;
	u16 bulk_out_req_num;
	volatile u16 bulk_out_req_act_num;
	u16 bulk_out_buf_size;
	_mutex bulk_out_mutex;

	struct usb_ep   *int_in_ep;

	struct usb_request *bulk_in_req;
	struct usb_request *bulk_out_req;
	struct usb_request *int_in_req;

	const struct usb_endpoint_descriptor *in, *out, *status;

	struct task_struct cdc_outCmdTask;
	struct task_struct cdc_outDataTask;
	struct usb_function	func;
	usbd_cdc_acm_usr_cb_t *cb;
	u16 serial_state;
	volatile int pending;
};

int usbd_cdc_acm_init(u16 bulk_in_buf_size, u16 bulk_out_buf_size, usbd_cdc_acm_usr_cb_t *cb);
int usbd_cdc_init(void);
void usbd_cdc_deinit(void);
int cdc_port_status(void);
int usb_insert_status(void);
int usbd_cdc_acm_sync_transmit_data(void *buf, u16 length);
#endif
