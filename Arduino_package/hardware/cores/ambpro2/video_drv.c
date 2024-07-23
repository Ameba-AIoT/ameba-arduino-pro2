#include "video_drv.h"
#include "hal_video.h"
#include "video_api.h"
#include "module_video.h"
#include "isp_ctrl_api.h"

extern int incb[5];
extern int enc_queue_cnt[5];

uint32_t image_addr = 0;
uint32_t image_len = 0;
int voe_heap_size = 0;

static isp_control ISPCtrl = {
    .Brightness = 0,
    .Contrast = 50,
    .Saturation = 50,
    .Sharpness = 50,
    .LDC = 0,
    .WDRMode = 0,
    .WDRLevel = 50,
    .ExposureMode = 1,
    .AWB = 1,
    .GrayMode = 0,
    .PowerLineFreq = 3,
    .DayNightMode = 0,
};

static video_params_t video_params = {
    .stream_id = 0,
    .type = 0,
    .resolution = 0,
    .width = 0,
    .height = 0,
    .bps = 0,
    .fps = 0,
    .gop = 0,
    .rc_mode = 0,
    .jpeg_qlevel = 5,
    .use_static_addr = 1,
    .rotation = 0,
    .jpeg_crop_parm = {
                       .enable = 0,
                       .xmin = 0,
                       .ymin = 0,
                       .xmax = 0,
                       .ymax = 0,
                       },
};

static video_params_t video_v4_params = {
    .stream_id = 0,
    .type = 0,
    .resolution = 0,
    .width = 0,
    .height = 0,
    .bps = 0,
    .fps = 0,
    .gop = 0,
    .direct_output = 0,
    .use_static_addr = 1,
    .use_roi = 1,
    .roi = {
            .xmin = 0,
            .ymin = 0,
            .xmax = 0,
            .ymax = 0,
            },
};

void ISPControlReset(void)
{
    isp_set_brightness(ISPCtrl.Brightness);
    isp_set_contrast(ISPCtrl.Contrast);
    isp_set_saturation(ISPCtrl.Saturation);
    isp_set_sharpness(ISPCtrl.Sharpness);
    isp_set_ldc(ISPCtrl.LDC);
    isp_set_wdr_mode(ISPCtrl.WDRMode);
    isp_set_exposure_mode(ISPCtrl.ExposureMode);
    isp_set_awb_ctrl(ISPCtrl.AWB);
    isp_set_gray_mode(ISPCtrl.GrayMode);
    isp_set_power_line_freq(ISPCtrl.PowerLineFreq);
    isp_set_day_night(ISPCtrl.DayNightMode);
}

int cameraConfig(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_snapshot,
                 int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_snapshot,
                 int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_snapshot,
                 int v4_enable, int v4_w, int v4_h)
{
    isp_info_t info;
    info.sensor_width = 1920;
    info.sensor_height = 1080;
    info.sensor_fps = 30;
    info.osd_enable = 1;
    info.md_enable = 1;
    info.hdr_enable = 1;

    video_set_isp_info(&info);

    voe_heap_size = video_voe_presetting(v1_enable, v1_w, v1_h, v1_bps, v1_snapshot,
                                         v2_enable, v2_w, v2_h, v2_bps, v2_snapshot,
                                         v3_enable, v3_w, v3_h, v3_bps, v3_snapshot,
                                         v4_enable, v4_w, v4_h);
    // printf("\r\n[INFO] voe_heap_size assigned.\n");
    return voe_heap_size;
}

mm_context_t *cameraInit(void)
{
    mm_context_t *videoData = (mm_context_t *)rtw_malloc(sizeof(mm_context_t));
    if (!videoData) {
        return NULL;
    }
    memset(videoData, 0, sizeof(mm_context_t));
    videoData->queue_num = 1;    // default 1 queue, can set multiple queue by command MM_CMD_SET_QUEUE_NUM
    videoData->module = &video_module;
    videoData->priv = video_module.create(videoData);
    if (!videoData->priv) {
        printf("\r\n[ERROR] cameraInit failed\n");
        if (videoData->priv) {
            video_module.destroy(videoData->priv);
        }
        if (videoData) {
            free(videoData);
        }
        return NULL;
    }
    // printf("\r\n[INFO] module open - free heap %d\n", xPortGetFreeHeapSize());

    return videoData;
}

void cameraOpen(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode, int snapshot, int jpeg_qlevel, int video_rotation)
{
    // assign value parsing from user level
    video_params.stream_id = stream_id;
    // check if there is video with snapshot
    if (snapshot == 1) {
        if (type == VIDEO_HEVC) {
            type = VIDEO_HEVC_JPEG;
        } else if (type == VIDEO_H264) {
            type = VIDEO_H264_JPEG;
        }
    }

    video_params.type = type;
    video_params.resolution = res;
    video_params.width = w;
    video_params.height = h;
    video_params.bps = bps;
    video_params.fps = fps;
    video_params.gop = gop;
    video_params.rc_mode = rc_mode;
    video_params.jpeg_qlevel = jpeg_qlevel;
    video_params.rotation = video_rotation;

    // printf("\r\n[INFO] %d    %d    %d    %d    %d    %d    %d    %d    %d\n", stream_id, type, res, w, h, bps, fps, gop, rc_mode);

    if (p) {
        // include CMD_VIDEO_SET_VOE_HEAP?
        // mm_module_ctrl(p, CMD_VIDEO_SET_VOE_HEAP, voe_heap_size);
        video_control(p_priv, CMD_VIDEO_SET_PARAMS, (int)&video_params);
        mm_module_ctrl(p, MM_CMD_SET_QUEUE_LEN, fps * 3);
        mm_module_ctrl(p, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        if ((type == VIDEO_JPEG) || (type == VIDEO_HEVC_JPEG) || (type == VIDEO_H264_JPEG)) {
            mm_module_ctrl(p, CMD_VIDEO_SNAPSHOT, 0);
        }
        // printf("\r\n[INFO] cameraOpen done\n");
    } else {
        // printf("\r\n[ERROR] cameraOpen fail\n");
    }
}

void cameraOpenNN(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int direct_output)
{
    // assign value parsing from user level
    video_v4_params.stream_id = stream_id;
    video_v4_params.type = type;
    video_v4_params.resolution = res;
    video_v4_params.width = w;
    video_v4_params.height = h;
    video_v4_params.bps = bps;
    video_v4_params.fps = fps;
    video_v4_params.gop = gop;
    video_v4_params.direct_output = direct_output;
    video_v4_params.use_static_addr = 1;

    // define NN region of interest
    video_v4_params.use_roi = 1;
    video_v4_params.roi.xmin = 0;
    video_v4_params.roi.ymin = 0;
    video_v4_params.roi.xmax = 1920;
    video_v4_params.roi.ymax = 1080;

    // printf("\r\n[INFO] V4 %d    %d    %d    %d    %d    %d    %d    %d    %d\n", stream_id, type, res, w, h, bps, fps, gop, direct_output);

    if (p) {
        video_control(p_priv, CMD_VIDEO_SET_PARAMS, (int)&video_v4_params);
        mm_module_ctrl(p, MM_CMD_SET_QUEUE_LEN, 2);
        mm_module_ctrl(p, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        // printf("\r\n[INFO] cameraOpen done\n");
    } else {
        // printf("\r\n[ERROR] cameraOpen fail\n");
    }
}

// set VOE heapsize
void cameraSetHeapSize(void *p)
{
    mm_module_ctrl(p, CMD_VIDEO_SET_VOE_HEAP, voe_heap_size);
}

// set the queue length of video object
void cameraSetQLen(mm_context_t *p, int length)
{
    mm_module_ctrl(p, MM_CMD_SET_QUEUE_LEN, length);
}

// set the queue item of video object
void cameraSetQItem(mm_context_t *p)
{
    mm_module_ctrl(p, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
}

void cameraStart(void *p, int channel)
{
    video_control(p, CMD_VIDEO_APPLY, channel);
}

void cameraYUV(void *p)
{
    video_control(p, CMD_VIDEO_YUV, 2);
}

void cameraSnapshot(void *p, int arg)
{
    video_control(p, CMD_VIDEO_SNAPSHOT, arg);
}

void cameraSnapshotRegCB(mm_context_t *p, int (*ssCB)(uint32_t, uint32_t))
{
    mm_module_ctrl(p, CMD_VIDEO_SNAPSHOT_CB, (int)ssCB);
}

mm_context_t *cameraDeinit(mm_context_t *p)
{
    mm_queue_item_t *tmp_item;
    mm_context_t *video_data = (mm_context_t *)rtw_malloc(sizeof(mm_context_t));
    video_data = p;
    for (int i = 0; i < video_data->queue_num; i++) {
        if (video_data->port[i].output_recycle && video_data->port[i].output_ready) {
            while (xQueueReceive(video_data->port[i].output_ready, (void *)&tmp_item, 0) == pdTRUE) {
                xQueueSend(video_data->port[i].output_recycle, (void *)&tmp_item, 0);
            }
            // printf("\r\n[INFO] module close - move item to recycle\n");
            while (xQueueReceive(video_data->port[i].output_recycle, (void *)&tmp_item, 0) == pdTRUE) {
                // printf("\r\n[INFO] module close - tmp_item %x\n",(unsigned int)tmp_item);
                if (tmp_item) {
                    // printf("\r\n[INFO] module close - data_addr %x\n", (unsigned int)tmp_item->data_addr);
                    if (i == 0) {
                        if (tmp_item->data_addr) {
                            video_del_item(video_data->priv, (void *)tmp_item->data_addr);
                        }
                    } else {
                        if (tmp_item->data_addr) {
                            free((void *)tmp_item->data_addr);
                        }
                    }
                    tmp_item->data_addr = 0;
                    free(tmp_item);
                    tmp_item = NULL;
                }
                xQueueSend(video_data->port[i].output_ready, (void *)&tmp_item, 0);
            }
            // printf("\r\n[INFO] module close - clean resource in recycle\n");
            //  create port
            vQueueDelete(video_data->port[i].output_recycle);
            vQueueDelete(video_data->port[i].output_ready);

            // printf("\r\n[INFO] module close - free port\n");
        }
    }
    // cannot delete item after destroy
    video_destroy(video_data->priv);
    free(video_data);
    // printf("\r\n[INFO] module close - free context\n");
    // printf("\r\n[INFO] module close - free heap %d\n", xPortGetFreeHeapSize());
    video_deinit();
    return NULL;
}

void cameraStopVideoStream(void *p, int channel)
{
    video_control(p, CMD_VIDEO_STREAM_STOP, channel);
}
