#ifndef USBD_NEW_UVC_H
#define USBD_NEW_UVC_H
#include "osdep_service.h"
#include "usbd_video.h"
#define VALUE_FPS(fps) (10000000/fps)

#define FORMAT_TYPE_YUY2        0
#define FORMAT_TYPE_NV12        1
#define FORMAT_TYPE_MJPEG       2
#define FORMAT_TYPE_H264        3
#define FORMAT_TYPE_H265        4

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

#define UVC_CMD_THREAD_PRIORITY	2

//#define UVC_NUM_REQUESTS 4

#define UVC_NUM_REQUESTS			2
#define UVC_MAX_REQUEST_SIZE		64
#define UVC_MAX_EVENTS				4

//Tuning tool
#define VendorCommand   0X0A
#define VendorData      0X0B
#define VendorLength    0X08
#define UserDefineCommand  0X0E
#define UserDownloadData     0X0F
#define UserDefineLength   0X40

#define WEBCAM_VENDOR_ID		0x1d6b	/* Linux Foundation */
#define WEBCAM_PRODUCT_ID		0x0102	/* Webcam A/V gadget */
#define WEBCAM_DEVICE_BCD		0x0010	/* 0.10 */
#define USBD_UVC_LANGID_STRING 0x0409U

#define USBD_UVC_MFG_STRING_DESC_SIZE 	  16U
#define USBD_UVC_PRODUCT_STRING_DESC_SIZE 28U
#define USBD_UVC_SN_STRING_DESC_SIZE      22U
#define USBD_UVC_SELF_POWERED             0U
#define USBD_UVC_CONFIG_DESC_SIZE         27U

#define USB_CLASS_MISC                  0xef
#define CONFIG_USB_GADGET_VBUS_DRAW     100


struct uvc_frame_info {
	unsigned int width;
	unsigned int height;
	unsigned int intervals[4];
};

struct uvc_format_info {
	unsigned int fcc;
	struct uvc_frame_info *frames;
};


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

struct uvcd_request_data {
	int length;
	u8 data[64];
};

struct usbd_uvc_buffer {
	struct list_head buffer_list;
	unsigned char *mem;
	unsigned int bytesused;
	void *exbuf;
	int index;
};

struct uvcd_req_data {
	u32				type;
	union {
		usb_setup_req_t req;
		struct uvcd_request_data uvc_data;
		unsigned char buf[64];
	};
	_list	list;
};

struct uvcd_video {
	struct usbd_uvc_buffer uvc_buffer;
	int stream_index;
	/* Frame parameters */
	u8 bpp;
	u32 fcc;
	unsigned int width;
	unsigned int height;
	unsigned int imagesize;
	unsigned int frm_type;

	/* Requests */
	unsigned int req_size;

	/* Context data used by the completion handler */
	u32 payload_size;
	u32 max_payload_size;

	//struct uvc_video_queue queue;
	unsigned int fid;
	unsigned int format;
	unsigned int buf_used;
	unsigned int end_flag;

	// payload list
	struct list_head input_queue;
	struct list_head output_queue;
	_mutex input_lock;
	_mutex output_lock;
	_sema output_queue_sema;

	/* to wakeup complete bottom half task */
	_xqueue complete_bf_req;
	xQueueHandle uvc_complete_queue;
	void *complete_bf_task;
};

struct uvcd_dev {
	struct uvcd_video video;

	struct uvcd_streaming_control probe;
	struct uvcd_streaming_control commit;

	u16 interface_number;
	u8 config;

	//const struct usb_endpoint_descriptor *in, *out, *status;
	// lock is held when accessing usb
	struct uvcd_req_data req_data;
	/* Events */
	unsigned int event_length;
	unsigned int event_setup_out : 1;
	int control;		   //control selector
	int command_interface; //Interface and entiny 0x00 control 0x01 streaming &0xff
	int command_entity;	   //0x02 process unit 0x03 extension unit >>8&0xff
	unsigned char result[64];
	void (*change_parm_cb)(void *);
	usb_dev_t *dev;
	//Command
	struct task_struct uvc_CmdTask;
	_mutex  bod_mutex;
	_list	bod_list;
	_lock lock;
	u32 running;
	u8  ctrl_req;
	u8  ctrl_data_len;
	TaskHandle_t task_usb_uvc;
};


/*-------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Function descriptors
 */

/* string IDs are assigned dynamically */

#define UVC_STRING_CONTROL_IDX			0
#define UVC_STRING_STREAMING_IDX		1

#define UVC_INTF_VIDEO_CONTROL			0
#define UVC_INTF_VIDEO_STREAMING		1

#define UVC_STATUS_MAX_PACKET_SIZE		64	/* 16 bytes status */
extern struct usb_configuration uvcd_cfg_driver;
extern struct uvcd_header_descriptor uvcd_control_header;
extern struct uvcd_streaming_control uvcd_probe;
extern struct uvcd_streaming_control uvcd_commit;
extern struct uvcd_output_header_descriptor uvcd_input_header;
extern struct usb_descriptor_header *usbd_uvcd_descriptors_FS[];
extern struct usb_descriptor_header *usbd_uvcd_descriptors_HS[];
extern struct uvcd_descriptor_header *uvcd_hs_streaming_cls[];
extern struct uvcd_descriptor_header *uvcd_fs_control_cls[];
void uvcd_events_process(struct uvcd_dev *dev, struct uvcd_req_data *uvc_event);
extern struct uvc_format_info uvcd_formats[];

struct uvcd_dev *get_private_usbd_uvcd(void);
void uvcd_video_put_out_stream_queue(struct usbd_uvc_buffer *payload, struct uvcd_dev *uvc_ctx);
void uvcd_video_put_in_stream_queue(struct usbd_uvc_buffer *payload, struct uvcd_dev *uvc_ctx);
struct usbd_uvc_buffer *uvcd_video_out_stream_queue(struct uvcd_dev *uvc_ctx);

/////////////////////////////////////////////////////
#endif