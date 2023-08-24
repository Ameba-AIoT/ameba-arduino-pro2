#ifndef USBD_UVC_DESC_H
#define USBD_UVC_DESC_H



#include "usbd_default.h"
#include "freertos_service.h"
#include "basic_types.h"
#include "video.h"

#define VALUE_FPS(fps) (10000000/fps)

#define FORMAT_TYPE_YUY2        0
#define FORMAT_TYPE_NV12        1
#define FORMAT_TYPE_MJPEG       2
#define FORMAT_TYPE_H264        3
#define FORMAT_TYPE_H265        4

//structure predefine
/* struct uvc_dev;
struct uvc_video; */

#define UVC_CMD_THREAD_PRIORITY	2

//#define UVC_NUM_REQUESTS 4

#define UVC_NUM_REQUESTS			2
#define UVC_MAX_REQUEST_SIZE			64
#define UVC_MAX_EVENTS				4

//Tuning tool
#define VendorCommand   0X0A
#define VendorData      0X0B
#define VendorLength    0X40
#define UserDefineCommand  0X0C
#define UserDefineData     0X0D
#define UserDefineLength   0X40



//#define UVC_VC_PROCESS_UNIT     0X02
//#define UVC_VC_EXTENSION_UNIT   0X03

//Tuning tool structure

struct uvc_frame_info {
	unsigned int width;
	unsigned int height;
	unsigned int intervals[4];
};

struct uvc_format_info {
	unsigned int fcc;
	//const struct uvc_frame_info *frames;
	struct uvc_frame_info *frames;
};

struct usbd_uvc_buffer {
	struct list_head buffer_list;
	unsigned char *mem;
	unsigned int bytesused;
	void *exbuf;
};

extern struct usb_endpoint_descriptor uvc_fs_streaming_ep;
extern struct usb_endpoint_descriptor uvc_hs_streaming_ep;
extern struct usb_endpoint_descriptor uvc_control_ep;

extern struct usb_interface_assoc_descriptor uvc_iad;
extern struct usb_interface_descriptor uvc_control_intf;
extern struct usb_interface_descriptor uvc_streaming_intf_alt0;
extern struct usb_interface_descriptor uvc_streaming_intf_alt1;
DECLARE_UVC_INPUT_HEADER_DESCRIPTOR(1, 4);
extern struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header;
extern struct usb_descriptor_header *usbd_uvc_descriptors_FS[];
extern struct usb_descriptor_header *usbd_uvc_descriptors_HS[];
extern struct uvc_streaming_control probe;
extern struct uvc_descriptor_header *uvc_hs_streaming_cls[];
extern struct uvc_descriptor_header *uvc_fs_control_cls[];

DECLARE_UVC_HEADER_DESCRIPTOR(1);
extern struct UVC_HEADER_DESCRIPTOR(1) uvc_control_header;

extern struct uvc_streaming_control commit;

DECLARE_UVC_FRAME_UNCOMPRESSED(3);
DECLARE_UVC_FRAME_FRAMEBASED(3);
DECLARE_UVC_FRAME_MJPEG(3);
DECLARE_UVC_EXTENSION_UNIT_DESCRIPTOR(1, 3);

extern struct uvc_camera_terminal_descriptor uvc_camera_terminal;
extern struct uvc_processing_unit_descriptor uvc_processing;
extern struct UVC_EXTENSION_UNIT_DESCRIPTOR(1, 3) uvc_extension_unit;
extern struct uvc_output_terminal_descriptor uvc_output_termina;
extern struct uvc_color_matching_descriptor uvc_color_matching;
extern struct uvc_control_endpoint_descriptor uvc_control_cs_ep;
extern struct uvc_output_terminal_descriptor uvc_output_terminal;

extern struct uvc_format_info uvc_formats[];

int usbd_uvc_init(void);
//int get_frame_index(struct uvc_video *video);
//struct uvc_dev *get_private_usbd_uvc(void);
struct usbd_uvc_buffer *uvc_video_out_stream_queue(void);
void uvc_video_put_in_stream_queue(struct usbd_uvc_buffer *payload);
void uvc_video_put_out_stream_queue(struct usbd_uvc_buffer *payload);
void composite_setup_complete_1(void);
int set_uvc_string(char *product_name, char *serial_name, unsigned short bcdDevice);
void usbd_uvc_set_change_parm_cb(int cb);
int usbd_uvc_get_status(void);
void usbd_wait_frame_down(void);
void usbd_uvc_ext_get_cb(int cb);
void usbd_uvc_ext_set_cb(int cb);
void usbd_uvc_stop(void);
void usbd_uvc_deinit(void);
#endif