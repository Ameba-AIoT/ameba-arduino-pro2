#ifndef USBD_UVC_INTERNAL_H
#define USBD_UVC_INTERNAL_H
/*-------------------------------------------------------------------------*/
#include "core/inc/usb_config.h"
#ifndef CONFIG_PLATFORM_8735B
#include "core/inc/usb_composite.h"
#else
#include "usb_composite.h"
#endif
#include "osdep_service.h"
#include "uvc_os_wrap_via_osdep_api.h"
#include "usb.h"

#define USBD_UVC_DEBUG          0
#define DBG_8195A printf
#if	USBD_UVC_DEBUG
#define USBD_PRINTF(fmt, args...)		            printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_ERROR(fmt, args...)		            printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)		            	printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#else
#define USBD_PRINTF(fmt, args...)
#define USBD_ERROR(fmt, args...)		            printf("\n\r%s: " fmt, __FUNCTION__, ## args)
#define USBD_WARN(fmt, args...)
#define FUN_ENTER
#define FUN_EXIT
#define FUN_TRACE
#endif

/* module parameters specific to the Video streaming endpoint */
static unsigned int streaming_interval = 1;

static unsigned int streaming_maxpacket = 1000;//1024;

static unsigned int streaming_maxburst;
/* --------------------------------------------------------------------------
 * Function descriptors
 */
#define UVC_INTF_CONTROL        0
#define UVC_INTF_STREAMING      1

#define UVC_EVENT_FIRST			0//(V4L2_EVENT_PRIVATE_START + 0)
#define UVC_EVENT_CONNECT		1//(V4L2_EVENT_PRIVATE_START + 0)
#define UVC_EVENT_DISCONNECT		2//(V4L2_EVENT_PRIVATE_START + 1)
#define UVC_EVENT_STREAMON		3//(//V4L2_EVENT_PRIVATE_START + 2)
#define UVC_EVENT_STREAMOFF		4//(V4L2_EVENT_PRIVATE_START + 3)
#define UVC_EVENT_SETUP			5//(V4L2_EVENT_PRIVATE_START + 4)
#define UVC_EVENT_DATA			6//(V4L2_EVENT_PRIVATE_START + 5)
#define UVC_EVENT_LAST			7//(V4L2_EVENT_PRIVATE_START + 5)

/* string IDs are assigned dynamically */

#define UVC_STRING_CONTROL_IDX			0
#define UVC_STRING_STREAMING_IDX		1

#define UVC_INTF_VIDEO_CONTROL			0
#define UVC_INTF_VIDEO_STREAMING		1

#define UVC_STATUS_MAX_PACKET_SIZE		64	/* 16 bytes status */

/////////////////////////////////////////////////////

#define WEBCAM_VENDOR_ID		0x1d6b	/* Linux Foundation */
#define WEBCAM_PRODUCT_ID		0x0102	/* Webcam A/V gadget */
#define WEBCAM_DEVICE_BCD		0x0010	/* 0.10 */

#define USB_CLASS_MISC                  0xef
#define CONFIG_USB_GADGET_VBUS_DRAW     100


#define STRING_MANUFACTURER		1
#define STRING_PRODUCT			2
#define STRING_SERIALNUMBER		3
#define STRING_INTERFACE		4
#define STRING_UVC			5


#define DRIVER_DESC	"USB UVC CLASS"
#define DRIVER_VERSION	"Feb 2016"

#define MANUFACTURER 	"Realtek"

static char webcam_config_label[] = "Video";

static char	string_manufacturer [50] = MANUFACTURER;
static char	string_product [40] = DRIVER_DESC;
static char	string_serial [20] = "0123456789";

static struct usb_string
	webcam_strings [] = {
	{ STRING_MANUFACTURER,	string_manufacturer, },
	{ STRING_PRODUCT,	string_product, },
	{ STRING_SERIALNUMBER,	string_serial, },
	{ STRING_INTERFACE,		"USB UVC Interface", },
	{ STRING_UVC,		"USB UVC", },
};

static struct usb_gadget_strings webcam_stringtab = {
	.language = 0x0409,	/* en-us */
	.strings = webcam_strings,
};

static struct usb_gadget_strings *webcam_device_strings[] = {
	&webcam_stringtab,
	NULL,
};

static struct usb_device_descriptor webcam_device_descriptor = {
	.bLength		= USB_DT_DEVICE_SIZE,
	.bDescriptorType	= USB_DT_DEVICE,
	.bcdUSB			= cpu_to_le16(0x0200),
	.bDeviceClass		= USB_CLASS_MISC,
	.bDeviceSubClass	= 0x02,
	.bDeviceProtocol	= 0x01,
	.bMaxPacketSize0	= 64, /* dynamic */
	.idVendor		= cpu_to_le16(WEBCAM_VENDOR_ID),
	.idProduct		= cpu_to_le16(WEBCAM_PRODUCT_ID),
	.bcdDevice		= cpu_to_le16(WEBCAM_DEVICE_BCD),
	.iManufacturer		= 0, /* dynamic */
	.iProduct		= 0, /* dynamic */
	.iSerialNumber		= 0, /* dynamic */
	.bNumConfigurations	= 0, /* dynamic */
};
////////////////////////

#define MAKE_SUBCMD(data,dir,subcmd) ((u8)(data)<<7|(u8)(dir)<<6|subcmd)

typedef struct _UvcVendorCmd {
	unsigned char cmd;
	unsigned char subcmd;
	unsigned short address;
	unsigned short length;
	unsigned short reserved;
	unsigned char buffer[8];
} UvcVendorCmd;

typedef struct _process_unit {
	int cur;//0X81
	int min;//0X82
	int max;//0X83
	int res;//0X84
	int len;//0X85
	int info;//0X86
	int def;//0X87
} process_unit;

typedef struct _isp_usbd_cmd_data {
	u16 cmdcode;
	u8 index;
	u8 length;
	u16 param;
	u16 addr;
	u8 buf[0x40];//The maximum buffer size
	u32 offset;//to recode the index for read and write
	//u32 error_type;
} isp_usbd_cmd_data;

struct ExtUnitCmd {
	u8 byCmd;
	u8 bySubCmd;
	u16 byarAddr;
	u16 byarLen;
	union {
		u16 byReserved;
		u16 byarAddrH;
	};
	u32 offset;//to recode the index for read and write
};

struct uvc_video {
	struct usb_ep *ep;
	struct usbd_uvc_buffer uvc_buffer;

	/* Frame parameters */
	u8 bpp;
	u32 fcc;
	unsigned int width;
	unsigned int height;
	unsigned int imagesize;
	unsigned int frm_type;


	void (*encode)(struct usb_iso_request *req, struct uvc_video *video, struct usbd_uvc_buffer *buf);


	/* Requests */
	unsigned int req_size;

	struct usb_iso_request *req;

	__u8 *req_buffer[UVC_NUM_REQUESTS];
	//struct list_head req_free;
	//spinlock_t req_lock;


	/* Context data used by the completion handler */
	__u32 payload_size;
	__u32 max_payload_size;

	//struct uvc_video_queue queue;
	unsigned int    fid;
	unsigned int    format;
	unsigned int    buf_used;

	// payload list
	struct list_head input_queue;
	struct list_head output_queue;
	_mutex input_lock;
	_mutex output_lock;
	_sema output_queue_sema;
};

struct uvc_request_data {
	__s32 length;
	__u8 data[64];
};

struct uvc_req_data {
	__u32				type;
	union {
		struct usb_ctrlrequest req;
		struct uvc_request_data uvc_data;
		unsigned char buf[64];
	};
	_list	list;
};



struct uvc_common {
	struct msc_dev	*mscdev;

	struct usb_gadget	*gadget;
	struct usb_ep		*ep0;
	struct usb_request	*req0;		/* for control responses */
	unsigned int 		running;
	/* bolk cmd data*/
	_mutex  bod_mutex;
	_list	bod_list;
};

//typedef void*	_lock;

struct uvc_dev {
	struct uvc_common 	*common;
	struct uvc_video        video;

	struct uvc_streaming_control probe;
	struct uvc_streaming_control commit;

	u16 		interface_number;
	u8			config;

	struct usb_ep	*in_ep;
	struct usb_ep	*out_ep;
	//unsigned int	bulk_in_enabled:1;
	//unsigned int	bulk_out_enabled:1;
	struct usb_request *control_req;
	void *control_buf;

	//const struct usb_endpoint_descriptor *in, *out, *status;
	// lock is held when accessing usb
	struct usb_function	func;
	_lock lock;
	struct task_struct uvc_CmdTask;
	struct usb_ctrlrequest req_ctrl;
	struct uvc_req_data    req_data;
	/* Events */
	unsigned int event_length;
	unsigned int event_setup_out : 1;
	int control;//control selector
	int command_interface;//Interface and entiny 0x00 control 0x01 streaming &0xff
	int command_entity;//0x02 process unit 0x03 extension unit >>8&0xff
	unsigned char result[64];
	struct uvc_req_data  *exten_temp_data;
	//UvcVendorCmd tuning_data;
	isp_usbd_cmd_data isp_data;
	struct ExtUnitCmd isp_data_pro2;
	void (*change_parm_cb)(void *);
	void (*uvcd_ext_get_cb)(void *buf, unsigned int len); //Host get the data from device
	void (*uvcd_ext_set_cb)(void *buf, unsigned int len); //Host set the data to device
};

void uvc_events_process(struct uvc_dev *dev, struct uvc_req_data *uvc_event);
#endif