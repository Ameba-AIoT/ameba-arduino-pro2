#include "osdep_service.h"
#include "uvc_os_wrap_via_osdep_api.h"
#include "osdep_service.h"
#include "basic_types.h"
#include "video.h"
#include "uvc/inc/usbd_uvc_desc.h"
#include "UVCD_pram.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* --------------------------------------------------------------------------
 * Device descriptor
 */

struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header = {
    .bLength = UVC_DT_INPUT_HEADER_SIZE(1, 4),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_INPUT_HEADER,
    .bNumFormats = 4,
    .wTotalLength = 0,     // 69, /* dynamic */
    .bEndpointAddress = 0, /* dynamic */
    .bmInfo = 0,
    .bTerminalLink = 4,
    .bStillCaptureMethod = 0,
    .bTriggerSupport = 0,
    .bTriggerUsage = 0,
    .bControlSize = 1,
    .bmaControls[0][0] = 0,
    .bmaControls[1][0] = 0,
    .bmaControls[2][0] = 0,
    .bmaControls[3][0] = 0,
};

struct uvc_format_uncompressed uvc_format_yuy2 = {
    .bLength = UVC_DT_FORMAT_UNCOMPRESSED_SIZE,
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FORMAT_UNCOMPRESSED,
    .bFormatIndex = 1,
    .bNumFrameDescriptors = 1,
    .guidFormat = {'N', 'V', '1', '6', 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
    .bBitsPerPixel = 16,
    .bDefaultFrameIndex = 1,
    .bAspectRatioX = 0,
    .bAspectRatioY = 0,
    .bmInterfaceFlags = 0,
    .bCopyProtect = 0,
};

struct uvc_format_uncompressed uvc_format_nv12 = {
    .bLength = UVC_DT_FORMAT_UNCOMPRESSED_SIZE,
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FORMAT_UNCOMPRESSED,
    .bFormatIndex = 2,
    .bNumFrameDescriptors = 1,
    .guidFormat = {'N', 'V', '1', '2', 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
    .bBitsPerPixel = 12,
    .bDefaultFrameIndex = 1,
    .bAspectRatioX = 0,
    .bAspectRatioY = 0,
    .bmInterfaceFlags = 0,
    .bCopyProtect = 0,
};

struct uvc_format_mjpeg uvc_format_mjpg = {
    .bLength = UVC_DT_FORMAT_MJPEG_SIZE,
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FORMAT_MJPEG,
    .bFormatIndex = 3,
    .bNumFrameDescriptors = 1,
    .bmFlags = 1,
    .bDefaultFrameIndex = 1,
    .bAspectRatioX = 0,
    .bAspectRatioY = 0,
    .bmInterfaceFlags = 0,
    .bCopyProtect = 0,
};

struct uvc_format_framebased uvc_format_h264 = {
    .bLength = UVC_DT_FORMAT_FRAMEBASED_SIZE,
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FORMAT_FRAME_BASED,
    .bFormatIndex = 4,
    .bNumFrameDescriptors = 1,
    .guidFormat = {'H', '2', '6', '4', 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
    .bBitsPerPixel = 12,
    .bDefaultFrameIndex = 1,
    .bAspectRatioX = 0,
    .bAspectRatioY = 0,
    .bmInterfaceFlags = 0,
    .bCopyProtect = 0,
    .bVariableSize = 1,
};

struct uvc_format_framebased uvc_format_h265 = {
    .bLength = UVC_DT_FORMAT_FRAMEBASED_SIZE,
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FORMAT_FRAME_BASED,
    .bFormatIndex = 5,
    .bNumFrameDescriptors = 1,
    .guidFormat = {'H', 'E', 'V', 'C', 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
    .bBitsPerPixel = 12,
    .bDefaultFrameIndex = 1,
    .bAspectRatioX = 0,
    .bAspectRatioY = 0,
    .bmInterfaceFlags = 0,
    .bCopyProtect = 0,
    .bVariableSize = 1,
};

#define FRAME_INTV_0 416666
#define FRAME_INTV_1 666666
#define FRAME_INTV_2 1000000

struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_yuv_480p = {
    .bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(640),
    .wHeight = cpu_to_le16(480),
    .dwMinBitRate = cpu_to_le32(7372800),
    .dwMaxBitRate = cpu_to_le32(55296000),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(460800),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_yuv_720p = {
    .bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(1280),
    .wHeight = cpu_to_le16(720),
    .dwMinBitRate = cpu_to_le32(3686400),
    .dwMaxBitRate = cpu_to_le32(27648000),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(1843200),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_yuy2_1080p = {
    .bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(MAX_W),
    .wHeight = cpu_to_le16(MAX_H),
    .dwMinBitRate = cpu_to_le32(MAX_W * MAX_H * 16 * 2),
    .dwMaxBitRate = cpu_to_le32(MAX_W * MAX_H * 16 * 15),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(MAX_W * MAX_H * 2),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_nv12_1080p = {
    .bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(MAX_W),
    .wHeight = cpu_to_le16(MAX_H),
    .dwMinBitRate = cpu_to_le32(MAX_W * MAX_H * 3),
    .dwMaxBitRate = cpu_to_le32(MAX_W * MAX_H * 45 / 2),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(MAX_W * MAX_H * 3 / 2),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_nv12_480p = {
    .bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 3,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(640),
    .wHeight = cpu_to_le16(480),
    .dwMinBitRate = cpu_to_le32(640 * 480 * 12 * 2),    // cpu_to_le32(7372800),
    .dwMaxBitRate = cpu_to_le32(640 * 480 * 12 * 15),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(460800),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_nv12_720p = {
    .bLength = UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_UNCOMPRESSED,
    .bFrameIndex = 2,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(1280),
    .wHeight = cpu_to_le16(720),
    .dwMinBitRate = cpu_to_le32(1280 * 720 * 12 * 2),
    .dwMaxBitRate = cpu_to_le32(1280 * 720 * 12 * 15),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(1280 * 720 * 1.5),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_FRAMEBASED(3) uvc_frame_h264_1080p = {
    .bLength = UVC_DT_FRAME_FRAMEBASED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_FRAME_BASED,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(MAX_W),
    .wHeight = cpu_to_le16(MAX_H),
    .dwMinBitRate = cpu_to_le32(MAX_W * MAX_H * 9),
    .dwMaxBitRate = cpu_to_le32(MAX_W * MAX_H * 27),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwBytesPerLine = cpu_to_le32(0),
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_FRAMEBASED(3) uvc_frame_h265_720p = {
    .bLength = UVC_DT_FRAME_FRAMEBASED_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_FRAME_BASED,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(MAX_W),
    .wHeight = cpu_to_le16(MAX_H),
    .dwMinBitRate = cpu_to_le32(MAX_H * MAX_W * 9),
    .dwMaxBitRate = cpu_to_le32(MAX_H * MAX_W * 27),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwBytesPerLine = cpu_to_le32(0),
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct UVC_FRAME_MJPEG(3) uvc_frame_mjpg_1080p = {
    .bLength = UVC_DT_FRAME_MJPEG_SIZE(3),
    .bDescriptorType = USB_DT_CS_INTERFACE,
    .bDescriptorSubType = UVC_VS_FRAME_MJPEG,
    .bFrameIndex = 1,
    .bmCapabilities = 0,
    .wWidth = cpu_to_le16(MAX_W),
    .wHeight = cpu_to_le16(MAX_H),
    .dwMinBitRate = cpu_to_le32(MAX_W * MAX_H * 9),
    .dwMaxBitRate = cpu_to_le32(MAX_W * MAX_H * 27),
    .dwMaxVideoFrameBufferSize = cpu_to_le32(460800),
    .dwDefaultFrameInterval = cpu_to_le32(FRAME_INTV_0),
    .bFrameIntervalType = 3,
    .dwFrameInterval[0] = cpu_to_le32(FRAME_INTV_0),
    .dwFrameInterval[1] = cpu_to_le32(FRAME_INTV_1),
    .dwFrameInterval[2] = cpu_to_le32(FRAME_INTV_2),
};

struct uvc_descriptor_header *uvc_fs_streaming_cls[] = {
    (struct uvc_descriptor_header *)&uvc_input_header,
#if UVCD_YUY2
    (struct uvc_descriptor_header *)&uvc_format_yuy2,
    (struct uvc_descriptor_header *)&uvc_frame_yuy2_1080p,
#endif
#if UVCD_NV12
    (struct uvc_descriptor_header *)&uvc_format_nv12,
    (struct uvc_descriptor_header *)&uvc_frame_nv12_1080p,
//(struct uvc_descriptor_header *) &uvc_frame_nv12_720p,
//(struct uvc_descriptor_header *) &uvc_frame_nv12_480p,
#endif
#if UVCD_MJPG
    (struct uvc_descriptor_header *)&uvc_format_mjpg,
    (struct uvc_descriptor_header *)&uvc_frame_mjpg_1080p,
#endif
#if UVCD_H264
    (struct uvc_descriptor_header *)&uvc_format_h264,
    (struct uvc_descriptor_header *)&uvc_frame_h264_1080p,
#endif
#if UVCD_H265
    (struct uvc_descriptor_header *)&uvc_format_h265,
    (struct uvc_descriptor_header *)&uvc_frame_h265_720p,
#endif
    (struct uvc_descriptor_header *)&uvc_color_matching,
    NULL,
};

struct uvc_descriptor_header *uvc_hs_streaming_cls[] = {
    (struct uvc_descriptor_header *)&uvc_input_header,
#if UVCD_YUY2
    (struct uvc_descriptor_header *)&uvc_format_yuy2,
    (struct uvc_descriptor_header *)&uvc_frame_yuy2_1080p,
#endif
#if UVCD_NV12
    (struct uvc_descriptor_header *)&uvc_format_nv12,
    (struct uvc_descriptor_header *)&uvc_frame_nv12_1080p,
//(struct uvc_descriptor_header *) &uvc_frame_nv12_720p,
//(struct uvc_descriptor_header *) &uvc_frame_nv12_480p,
#endif
#if UVCD_MJPG
    (struct uvc_descriptor_header *)&uvc_format_mjpg,
    (struct uvc_descriptor_header *)&uvc_frame_mjpg_1080p,
#endif
#if UVCD_H264
    (struct uvc_descriptor_header *)&uvc_format_h264,
    (struct uvc_descriptor_header *)&uvc_frame_h264_1080p,
#endif
#if UVCD_H265
    (struct uvc_descriptor_header *)&uvc_format_h265,
    (struct uvc_descriptor_header *)&uvc_frame_h265_720p,
#endif
    (struct uvc_descriptor_header *)&uvc_color_matching,
    NULL,
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct usb_descriptor_header *usbd_uvc_descriptors_FS[] = {
    (struct usb_descriptor_header *)&uvc_iad,
    (struct usb_descriptor_header *)&uvc_control_intf,    /////////
    (struct usb_descriptor_header *)&uvc_control_header,
    (struct usb_descriptor_header *)&uvc_camera_terminal,
    (struct usb_descriptor_header *)&uvc_processing,
    (struct usb_descriptor_header *)&uvc_extension_unit,
    (struct usb_descriptor_header *)&uvc_output_terminal,    /////////
    (struct usb_descriptor_header *)&uvc_control_ep,
    (struct usb_descriptor_header *)&uvc_control_cs_ep,
    (struct usb_descriptor_header *)&uvc_streaming_intf_alt0,    /////////
    (struct usb_descriptor_header *)&uvc_input_header,
#if UVCD_YUY2
    (struct usb_descriptor_header *)&uvc_format_yuy2,
    (struct usb_descriptor_header *)&uvc_frame_yuy2_1080p,
#endif
#if UVCD_NV12
    (struct usb_descriptor_header *)&uvc_format_nv12,
    (struct usb_descriptor_header *)&uvc_frame_nv12_1080p,
//(struct usb_descriptor_header *) &uvc_frame_nv12_720p,
//(struct usb_descriptor_header *) &uvc_frame_nv12_480p,
#endif
#if UVCD_MJPG
    (struct usb_descriptor_header *)&uvc_format_mjpg,
    (struct usb_descriptor_header *)&uvc_frame_mjpg_1080p,
#endif
#if UVCD_H264
    (struct usb_descriptor_header *)&uvc_format_h264,
    (struct usb_descriptor_header *)&uvc_frame_h264_1080p,
#endif
#if UVCD_H265
    (struct usb_descriptor_header *)&uvc_format_h265,
    (struct usb_descriptor_header *)&uvc_frame_h265_720p,
#endif
    (struct usb_descriptor_header *)&uvc_color_matching,
    (struct usb_descriptor_header *)&uvc_streaming_intf_alt1,
    (struct usb_descriptor_header *)&uvc_fs_streaming_ep,
    NULL,
};

struct usb_descriptor_header *usbd_uvc_descriptors_HS[] = {
    (struct usb_descriptor_header *)&uvc_iad,
    (struct usb_descriptor_header *)&uvc_control_intf,
    (struct usb_descriptor_header *)&uvc_control_header,    ///////
    (struct usb_descriptor_header *)&uvc_camera_terminal,
    (struct usb_descriptor_header *)&uvc_processing,
    (struct usb_descriptor_header *)&uvc_extension_unit,
    (struct usb_descriptor_header *)&uvc_output_terminal,    /////////
    (struct usb_descriptor_header *)&uvc_control_ep,
    (struct usb_descriptor_header *)&uvc_control_cs_ep,
    (struct usb_descriptor_header *)&uvc_streaming_intf_alt0,    /////////
    (struct usb_descriptor_header *)&uvc_input_header,
#if UVCD_YUY2
    (struct usb_descriptor_header *)&uvc_format_yuy2,
    (struct usb_descriptor_header *)&uvc_frame_yuy2_1080p,
#endif
#if UVCD_NV12
    (struct usb_descriptor_header *)&uvc_format_nv12,
    (struct usb_descriptor_header *)&uvc_frame_nv12_1080p,
//(struct usb_descriptor_header *) &uvc_frame_nv12_720p,
//(struct usb_descriptor_header *) &uvc_frame_nv12_480p,
#endif
#if UVCD_MJPG
    (struct usb_descriptor_header *)&uvc_format_mjpg,
    (struct usb_descriptor_header *)&uvc_frame_mjpg_1080p,
#endif
#if UVCD_H264
    (struct usb_descriptor_header *)&uvc_format_h264,
    (struct usb_descriptor_header *)&uvc_frame_h264_1080p,
#endif
#if UVCD_H265
    (struct usb_descriptor_header *)&uvc_format_h265,
    (struct usb_descriptor_header *)&uvc_frame_h265_720p,
#endif
    (struct usb_descriptor_header *)&uvc_color_matching,
    (struct usb_descriptor_header *)&uvc_streaming_intf_alt1,
    (struct usb_descriptor_header *)&uvc_hs_streaming_ep,
    NULL,
};

struct uvc_frame_info uvc_frames_mjpeg[] = {
    {MAX_W, MAX_H, {FRAME_INTV_0, FRAME_INTV_1, FRAME_INTV_2, 0}},
    {0,     0,     {0}                                          }
};

struct uvc_frame_info uvc_frames_h264[] = {
  //  25,
    {MAX_W, MAX_H, {FRAME_INTV_0, FRAME_INTV_1, FRAME_INTV_2, 0}}, //  400000, 1000000, 5000000,
    {0,     0,     {0}                                          }
};

struct uvc_frame_info uvc_frames_h265[] = {
  //  25,
    {MAX_W, MAX_H, {FRAME_INTV_0, FRAME_INTV_1, FRAME_INTV_2, 0}}, //  400000, 1000000, 5000000,
    {0,     0,     {0}                                          }
};

struct uvc_frame_info uvc_frames_yuy2[] = {
    {MAX_W, MAX_H, {FRAME_INTV_0, FRAME_INTV_1, FRAME_INTV_2, 0}}, //  666666, 10000000, 50000000,
    {0,     0,     {0}                                          }
};

struct uvc_frame_info uvc_frames_nv12[] = {
    {MAX_W, MAX_H, {FRAME_INTV_0, FRAME_INTV_1, FRAME_INTV_2, 0}}, //  666666, 10000000, 50000000,
  //{  1280, 720, { VALUE_FPS(15), VALUE_FPS(10), VALUE_FPS(2), 0 }, },//666666, 10000000, 50000000,
  //{  640, 480, { VALUE_FPS(15), VALUE_FPS(10), VALUE_FPS(2), 0 }, },//666666, 10000000, 50000000,
    {0,     0,     {0}                                          }
};

struct uvc_format_info uvc_formats[] = {
#if UVCD_YUY2
    {FORMAT_TYPE_YUY2,  uvc_frames_yuy2 },
#endif
#if UVCD_NV12
    {FORMAT_TYPE_NV12,  uvc_frames_nv12 },
#endif
#if UVCD_MJPG
    {FORMAT_TYPE_MJPEG, uvc_frames_mjpeg},
#endif
#if UVCD_H264
    {FORMAT_TYPE_H264,  uvc_frames_h264 },
#endif
#if UVCD_H265
    {FORMAT_TYPE_H265,  uvc_frames_h265 },
#endif
};
