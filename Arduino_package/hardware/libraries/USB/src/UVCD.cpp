#include "UVCD.h"
#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "mmf2_link.h"
#include "mmf2_siso.h"
#include "isp_ctrl_api.h"
#include "video_drv.h"
#ifdef __cplusplus
}
#endif

Video video;
extern struct uvc_format *uvc_format_ptr;
struct uvc_format *uvc_format_local = NULL;
int arduino_is_output_ready = 0;
// extern mm_module_t video_module;
UVCD::UVCD(void)
{
    cameraPreConfig_usb_uvcd(_uuid, "USB UVC CLASS");
}

UVCD::UVCD(const char *usb_uvcd_driver_name)
{
    cameraPreConfig_usb_uvcd(_uuid, usb_uvcd_driver_name);
}


UVCD::~UVCD(void)
{
    if (_p_mmf_context == NULL) {

        return;
    }
    if (mm_module_close(_p_mmf_context) == NULL) {

        _p_mmf_context = NULL;
        printf("\r\n[ERROR] UVCD deinit failed\n");
    }
}

int UVCD::get_usb_status()
{
    arduino_is_output_ready = get_output_ready();
    return arduino_is_output_ready;
}
// Implementation of `isUsbUvcConnected` function
int UVCD::isUsbUvcConnected()
{
    if (_p_mmf_context == NULL) {
        return false;    // Device context not initialized
    }

    if ((uvc_format_ptr->state == 0) || (get_usb_status() == 0)) {
        return false;    // Video stream is not active
    }

    if ((uvc_format_ptr->state == 1) && (get_usb_status() == 1)) {
        return true;    // Device is connected
    }
    return false;
}

/**
 *  @brief   Start config video
 *
 *  @param   config: pointer of VideoSetting
 *  @return  None
 *
 */
void UVCD::configVideo(VideoSetting &config)
{
    _p_mmf_context = mm_module_open(&uvcd_module);
    if (_p_mmf_context == NULL) {
        printf("Failed to open module context\n");
        return;
    }

    uvc_format_ptr = (struct uvc_format *)malloc(sizeof(struct uvc_format));
    memset(uvc_format_ptr, 0, sizeof(struct uvc_format));

    uvc_format_local = (struct uvc_format *)malloc(sizeof(struct uvc_format));
    memset(uvc_format_local, 0, sizeof(struct uvc_format));

    rtw_init_sema(&uvc_format_ptr->uvcd_change_sema, 0);

    if (config._encoder == VIDEO_H264) {
        uvc_format_ptr->format = FORMAT_TYPE_H264;
        uvc_format_local->format = FORMAT_TYPE_H264;
    } else {
        // default setting
        uvc_format_ptr->format = FORMAT_TYPE_H264;
        uvc_format_local->format = FORMAT_TYPE_H264;
    }

    uvc_format_ptr->height = config._h;
    uvc_format_ptr->width = config._w;

    uvc_format_local->height = config._h;
    uvc_format_local->width = config._w;
    uvc_format_local->fps = config._fps;
}

/**
*  @brief   Begin video streaming and NN
 *
 *  @param   module_videocam: stream data from camera video
 *           module_videolinker: StreamIO object for uvcd
             uvcd_channel: video channel
             nn_channel: nn channel
 *  @return  none
 *
 */
void UVCD::nnbegin(const MMFModule &module_videocam, void *module_videolinker, int uvcd_channel, int nn_channel)
{
    _uvcd_channel = uvcd_channel;
    _nn_channel = nn_channel;
    int wdr_mode = 2;
    isp_set_wdr_mode(wdr_mode);
    rtw_down_sema(&uvc_format_ptr->uvcd_change_sema);
    if ((uvc_format_local->format != uvc_format_ptr->format) || (uvc_format_local->width != uvc_format_ptr->width) || (uvc_format_local->height != uvc_format_ptr->height) || (uvc_format_local->fps != uvc_format_ptr->fps)) {
        if (uvc_format_ptr->format == FORMAT_TYPE_YUY2) {
            cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
            vTaskDelay(1000);
            siso_pause((mm_siso_t *)(module_videolinker));
            vTaskDelay(1000);
            cameraReSetParams(module_videocam._p_mmf_context, VIDEO_NV16, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
            cameraYUV(module_videocam._p_mmf_context);
            siso_resume((mm_siso_t *)(module_videolinker));
        } else if (uvc_format_ptr->format == FORMAT_TYPE_NV12) {
            cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
            vTaskDelay(1000);
            siso_pause((mm_siso_t *)(module_videolinker));
            vTaskDelay(1000);
            cameraReSetParams(module_videocam._p_mmf_context, VIDEO_NV12, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
            cameraYUV(module_videocam._p_mmf_context);
            siso_resume((mm_siso_t *)(module_videolinker));
        } else if (uvc_format_ptr->format == FORMAT_TYPE_H264) {
            cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
            vTaskDelay(1000);
            siso_pause((mm_siso_t *)(module_videolinker));
            vTaskDelay(100);
            cameraReSetParams(module_videocam._p_mmf_context, VIDEO_H264, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
            siso_resume((mm_siso_t *)(module_videolinker));
            isUsbUvcConnected();
        } else if (uvc_format_ptr->format == FORMAT_TYPE_MJPEG) {
            cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
            vTaskDelay(1000);
            siso_pause((mm_siso_t *)(module_videolinker));
            vTaskDelay(1000);
            cameraReSetParams(module_videocam._p_mmf_context, VIDEO_JPEG, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
            cameraSnapshot(module_videocam._p_mmf_context, 2);
            siso_resume((mm_siso_t *)(module_videolinker));
        } else if (uvc_format_ptr->format == FORMAT_TYPE_H265) {
            cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
            vTaskDelay(1000);
            siso_pause((mm_siso_t *)(module_videolinker));
            vTaskDelay(100);
            cameraReSetParams(module_videocam._p_mmf_context, VIDEO_HEVC, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
            siso_resume((mm_siso_t *)(module_videolinker));
        }
        uvc_format_local->format = uvc_format_ptr->format;
        uvc_format_local->width = uvc_format_ptr->width;
        uvc_format_local->height = uvc_format_ptr->height;
        uvc_format_local->fps = uvc_format_ptr->fps;
    }
}


/**
 *  @brief   Begin video streaming
 *
 *  @param   module_videocam: stream data from camera video
 *           module_videolinker: StreamIO object for uvcd
             uvcd_channel: video channel
 *  @return  None
 *
 */
void UVCD::begin(const MMFModule &module_videocam, void *module_videolinker, int uvcd_channel)
{
    _uvcd_channel = uvcd_channel;
    int wdr_mode = 2;
    // printf("\r\n[INFO] %s. [uvcd]set wdr_mode:%d \n", __FUNCTION__, wdr_mode);
    isp_set_wdr_mode(wdr_mode);
    isp_get_wdr_mode(&wdr_mode);
    // printf("\r\n[INFO] %s. [uvcd]get wdr_mode:%d \n", __FUNCTION__, wdr_mode);

    while (1) {
        rtw_down_sema(&uvc_format_ptr->uvcd_change_sema);

        if ((uvc_format_local->format != uvc_format_ptr->format) || (uvc_format_local->width != uvc_format_ptr->width) || (uvc_format_local->height != uvc_format_ptr->height) || (uvc_format_local->fps != uvc_format_ptr->fps)) {

            if (uvc_format_ptr->format == FORMAT_TYPE_YUY2) {
                cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
                vTaskDelay(1000);
                siso_pause((mm_siso_t *)(module_videolinker));
                vTaskDelay(1000);
                cameraReSetParams(module_videocam._p_mmf_context, VIDEO_NV16, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
                cameraYUV(module_videocam._p_mmf_context);
                siso_resume((mm_siso_t *)(module_videolinker));
            } else if (uvc_format_ptr->format == FORMAT_TYPE_NV12) {
                cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
                vTaskDelay(1000);
                siso_pause((mm_siso_t *)(module_videolinker));
                vTaskDelay(1000);
                cameraReSetParams(module_videocam._p_mmf_context, VIDEO_NV12, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
                cameraYUV(module_videocam._p_mmf_context);
                siso_resume((mm_siso_t *)(module_videolinker));
            } else if (uvc_format_ptr->format == FORMAT_TYPE_H264) {
                cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
                vTaskDelay(1000);
                siso_pause((mm_siso_t *)(module_videolinker));
                vTaskDelay(100);
                cameraReSetParams(module_videocam._p_mmf_context, VIDEO_H264, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
                siso_resume((mm_siso_t *)(module_videolinker));
            } else if (uvc_format_ptr->format == FORMAT_TYPE_MJPEG) {
                cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
                vTaskDelay(1000);
                siso_pause((mm_siso_t *)(module_videolinker));
                vTaskDelay(1000);
                cameraReSetParams(module_videocam._p_mmf_context, VIDEO_JPEG, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
                cameraSnapshot(module_videocam._p_mmf_context, 2);
                siso_resume((mm_siso_t *)(module_videolinker));
            } else if (uvc_format_ptr->format == FORMAT_TYPE_H265) {
                cameraStopVideoStream(module_videocam._p_mmf_context, _uvcd_channel);
                vTaskDelay(1000);
                siso_pause((mm_siso_t *)(module_videolinker));
                vTaskDelay(100);
                cameraReSetParams(module_videocam._p_mmf_context, VIDEO_HEVC, uvc_format_ptr->fps, ((uvc_format_ptr->fps) * 3), 1, _uvcd_channel);
                siso_resume((mm_siso_t *)(module_videolinker));
            }
            uvc_format_local->format = uvc_format_ptr->format;
            uvc_format_local->width = uvc_format_ptr->width;
            uvc_format_local->height = uvc_format_ptr->height;
            uvc_format_local->fps = uvc_format_ptr->fps;
        }
    }
}
