#include "usb_ch9.h"
#include "usb_defs.h"
#include "usb_gadget.h"

#include "usb.h"
#include "usb_gadget.h"
#include "core/inc/usb_composite.h"

#define DFU_CONFIG_VAL			1
#define DFU_DT_FUNC			0x21

//#define DFU_TIMEOUT                     2000 //2S
#define DFU_DEFAULT_POLL_TIMEOUT 5000

#define DFU_BIT_WILL_DETACH		(0x1 << 3)
#define DFU_BIT_MANIFESTATION_TOLERANT	(0x1 << 2)
#define DFU_BIT_CAN_UPLOAD		(0x1 << 1)
#define DFU_BIT_CAN_DNLOAD		0x1

/* big enough to hold our biggest descriptor */
#define DFU_USB_BUFSIZ			64//4096

#define USB_REQ_DFU_DETACH		0x00
#define USB_REQ_DFU_DNLOAD		0x01
#define USB_REQ_DFU_UPLOAD		0x02
#define USB_REQ_DFU_GETSTATUS		0x03
#define USB_REQ_DFU_CLRSTATUS		0x04
#define USB_REQ_DFU_GETSTATE		0x05
#define USB_REQ_DFU_ABORT		0x06

#define DFU_STATUS_OK			0x00
#define DFU_STATUS_errTARGET		0x01
#define DFU_STATUS_errFILE		0x02
#define DFU_STATUS_errWRITE		0x03
#define DFU_STATUS_errERASE		0x04
#define DFU_STATUS_errCHECK_ERASED	0x05
#define DFU_STATUS_errPROG		0x06
#define DFU_STATUS_errVERIFY		0x07
#define DFU_STATUS_errADDRESS		0x08
#define DFU_STATUS_errNOTDONE		0x09
#define DFU_STATUS_errFIRMWARE		0x0a
#define DFU_STATUS_errVENDOR		0x0b
#define DFU_STATUS_errUSBR		0x0c
#define DFU_STATUS_errPOR		0x0d
#define DFU_STATUS_errUNKNOWN		0x0e
#define DFU_STATUS_errSTALLEDPKT	0x0f

#define RET_STALL			-1
#define RET_ZLP				0
#define RET_STAT_LEN			6

#define DFU_POLL_TIMEOUT_MASK           (0xFFFFFFUL)

#define OTA_BUF (2*1024*1024)

#define DUF_LOG_OFF		4
#define DFU_LOG_ERR		3
#define DFU_LOG_MSG		2
#define DFU_LOG_INF		1
#define DFU_LOG_ALL		0

struct dfu_status {
	u8				bStatus;
	u8				bwPollTimeout[3];
	u8				bState;
	u8				iString;
} __attribute__((packed));

#if 0
struct dfu_function_descriptor {
	u8				bLength;
	u8				bDescriptorType;
	u8				bmAttributes;
	u16				wDetachTimeOut;//cpu_to_le16
	u16				wTransferSize;//cpu_to_le16
	u16				bcdDFUVersion;//cpu_to_le16
} __packed;
#else
struct dfu_function_descriptor {
	u8				bLength;
	u8				bDescriptorType;
	u8				bmAttributes;
	u16				wDetachTimeOut;//cpu_to_le16
	u16				wTransferSize;//cpu_to_le16
	u16				bcdDFUVersion;//cpu_to_le16
} __attribute__((packed));;
#endif
enum dfu_state {
	DFU_STATE_appIDLE		= 0,
	DFU_STATE_appDETACH		= 1,
	DFU_STATE_dfuIDLE		= 2,
	DFU_STATE_dfuDNLOAD_SYNC	= 3,
	DFU_STATE_dfuDNBUSY		= 4,
	DFU_STATE_dfuDNLOAD_IDLE	= 5,
	DFU_STATE_dfuMANIFEST_SYNC	= 6,
	DFU_STATE_dfuMANIFEST		= 7,
	DFU_STATE_dfuMANIFEST_WAIT_RST	= 8,
	DFU_STATE_dfuUPLOAD_IDLE	= 9,
	DFU_STATE_dfuERROR		= 10,
};


struct f_dfu {
	struct usb_gadget	*gadget;
	struct usb_ep		*ep0;
	struct usb_request	*req0;		/* for control responses */
	/* when configured, we have one config */
	u8				config;
	u8				altsetting;
	enum dfu_state			dfu_state;
	unsigned int			dfu_status;

	/* Send/received block number is handy for data integrity check */
	int                             blk_seq_num;
	unsigned int                    poll_timeout;
	struct usb_function		func;
	unsigned char *ota_buf;
	unsigned int ota_size;
	unsigned int ota_send_index;
	unsigned int ota_send_size;
	_sema wakeup_sema;
};

#define DFU_VENDOR_ID		0x1d6b	/* Linux Foundation */
#define DFU_PRODUCT_ID		0x0202	/* DFU gadget */
#define DFU_DEVICE_BCD		0x0010	/* 0.10 */
static char dfu_config_label[] = "Dful";

static struct usb_device_descriptor dfu_device_descriptor = {
	.bLength		= USB_DT_DEVICE_SIZE,
	.bDescriptorType	= USB_DT_DEVICE,
	.bcdUSB			= cpu_to_le16(0x0200),
	.bDeviceClass		= 0x00,// define in interface descriptor,
	.bDeviceSubClass	= 0x00,
	.bDeviceProtocol	= 0x00,
	.bMaxPacketSize0	= 64, /* dynamic */
	.idVendor		= cpu_to_le16(DFU_VENDOR_ID),
	.idProduct		= cpu_to_le16(DFU_PRODUCT_ID),
	.bcdDevice		= cpu_to_le16(DFU_DEVICE_BCD),
	.iManufacturer		= 0, /* dynamic */
	.iProduct		= 0, /* dynamic */
	.iSerialNumber		= 0, /* dynamic */
	.bNumConfigurations	= 0, /* dynamic */
};

#define DRIVER_DESC	"USB DFU CLASS"
#define DRIVER_VERSION	"Feb 2016"
#define MANUFACTURER 	"Realtek"

#define STRING_MANUFACTURER		1
#define STRING_PRODUCT			2
#define STRING_SERIALNUMBER		3
#define STRING_INTERFACE		4
#define STRING_DFU			    5


static char	string_manufacturer [50] = MANUFACTURER;
static char	string_product [40] = DRIVER_DESC;
static char	string_serial [20] = "0123456789";

#define CONFIG_USB_GADGET_VBUS_DRAW     100

static struct usb_string        dfu_strings [] = {
	{ STRING_MANUFACTURER,	string_manufacturer, },
	{ STRING_PRODUCT,	string_product, },
	{ STRING_SERIALNUMBER,	string_serial, },
	{ STRING_INTERFACE,	"USB DFU Interface", },
	{ STRING_DFU,		"USB DFU", },
	NULL,
};

static struct usb_gadget_strings dfu_stringtab = {
	.language = 0x0409,	/* en-us */
	.strings = dfu_strings,
};

static struct usb_gadget_strings *dfu_device_strings[] = {
	&dfu_stringtab,
	NULL,
};

static struct usb_interface_descriptor dfu_intf_runtime = {
	.bLength =		sizeof dfu_intf_runtime,
	.bDescriptorType =	USB_DT_INTERFACE,
	.bNumEndpoints =	0,
	.bInterfaceClass =	USB_CLASS_APP_SPEC,
	.bInterfaceSubClass =	1,
	.bInterfaceProtocol =	1,
	/* .iInterface = DYNAMIC */
};

static struct dfu_function_descriptor dfu_func = {
	.bLength =		sizeof dfu_func,
	.bDescriptorType =	DFU_DT_FUNC,
	.bmAttributes =		DFU_BIT_WILL_DETACH |
	DFU_BIT_MANIFESTATION_TOLERANT |
	DFU_BIT_CAN_UPLOAD |
	DFU_BIT_CAN_DNLOAD,
	.wDetachTimeOut =	DFU_DEFAULT_POLL_TIMEOUT,
	.wTransferSize =	DFU_USB_BUFSIZ,
	.bcdDFUVersion =	cpu_to_le16(0x0110),
};

static struct usb_descriptor_header *dfu_runtime_descs[] = {
	(struct usb_descriptor_header *) &dfu_intf_runtime,
	(struct usb_descriptor_header *) &dfu_func,
	NULL,
};
