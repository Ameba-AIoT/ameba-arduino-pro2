/* External NV12 -> hardware JPEG -> MMF source.
 * Adapted from the supplied Realtek thermal_camera/module_mi48 example.
 * Copyright(c) 2007 - 2021 Realtek Corporation. All rights reserved.
 * SDK headers stay in this C translation unit to avoid C++ linkage issues. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "platform_stdlib.h"
#include "osdep_service.h"
#include "avcodec.h"
#include "mmf2_module.h"
#include "module_video.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "MI48Encoder.h"

static mm_context_t *video_ctx;
static mm_context_t *mi48_ctx;
static SemaphoreHandle_t jpeg_done;
static uint32_t jpeg_address, jpeg_length;
static int attempted;
static uint16_t output_width, output_height;
static uint8_t output_fps;
static uint32_t nv12_bytes;

static int jpeg_callback(uint32_t address, uint32_t length)
{
    jpeg_address = address;
    jpeg_length = length;
    xSemaphoreGive(jpeg_done);
    return 0;
}

int mi48_stream_encode(uint8_t *nv12)
{
    mm_queue_item_t *item;
    
    if (!mi48_ctx || !nv12) {
        return -1;
    }

    if (xQueueReceive(mi48_ctx->output_recycle, &item, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return 0;
    }
    
    dcache_clean_by_addr((uint32_t *)nv12, (int32_t)nv12_bytes);
    
    while (xSemaphoreTake(jpeg_done, 0) == pdTRUE) {
    }
    jpeg_address = jpeg_length = 0;
    int ret = mm_module_ctrl(video_ctx, CMD_VIDEO_SET_EXT_INPUT, (int)nv12);
    if (ret < 0 || xSemaphoreTake(jpeg_done, pdMS_TO_TICKS(3000)) != pdTRUE) {
        printf("MI48 RTSP: JPEG failed (%d); reset board\r\n", ret);
        xQueueSend(mi48_ctx->output_recycle, &item, portMAX_DELAY);
        return -1;
    }
    if (!jpeg_address || !jpeg_length) {
        xQueueSend(mi48_ctx->output_recycle, &item, portMAX_DELAY);
        return 0;
    }
    item->type = AV_CODEC_ID_MJPEG;
    item->timestamp = mm_read_mediatime_ms();
    item->data_addr = jpeg_address;
    item->size = jpeg_length;
    if (xQueueSend(mi48_ctx->output_ready, &item, 0) != pdTRUE) {
        xQueueSend(mi48_ctx->output_recycle, &item, portMAX_DELAY);
        return 0;
    }
    return 1;
}

static void *tip_create(void *parent)
{
    return parent;
}
static void *tip_destroy(void *context)
{
    (void)context;
    /* No runtime teardown in this hardware-test example. Reset to stop. */
    return NULL;
}
static int tip_control(void *context, int command, int argument)
{
    (void)context;
    (void)command;
    (void)argument;
    return 0;
}
static int tip_handle(void *context, void *input, void *output)
{
    (void)context;
    (void)input;
    (void)output;
    return 0;
}
static void *tip_new_item(void *context)
{
    (void)context;
    return NULL;
}
static void *tip_del_item(void *context, void *item)
{
    (void)context;
    (void)item;
    return NULL;
}
static mm_module_t tip_module = {
    .create = tip_create,
    .destroy = tip_destroy,
    .control = tip_control,
    .handle = tip_handle,
    .new_item = tip_new_item,
    .del_item = tip_del_item,
    .output_type = MM_TYPE_ASINK | MM_TYPE_ADSP | MM_TYPE_VSINK | MM_TYPE_VDSP,
    .module_type = MM_TYPE_ASRC | MM_TYPE_VSRC,
    .name = "TIP"};

void *mi48_stream_open(uint16_t width, uint16_t height, uint8_t fps, uint8_t channel, uint32_t bps, uint32_t type, uint32_t resolution, uint32_t ext_fmt)
{
    if (attempted || !width || !height || width > 1920 || height > 1080 || (width & 1) || (height & 1) || !fps || fps > 30) {
        return NULL;
    }

    output_width = width;
    output_height = height;
    output_fps = fps;
    nv12_bytes = (uint32_t)width * height * 3 / 2;
    attempted = 1;
    jpeg_done = xSemaphoreCreateBinary();

    if (!jpeg_done) {
        return NULL;
    }

    video_params_t parameters;
    memset(&parameters, 0, sizeof(parameters));
    parameters.stream_id = channel;
    parameters.type = type;
    parameters.bps = bps;
    parameters.use_static_addr = 1;
    parameters.out_mode = MODE_EXT;
    parameters.ext_fmt = ext_fmt;
    parameters.resolution = resolution;
    parameters.width = output_width;
    parameters.height = output_height;
    parameters.fps = output_fps;

    int heap = video_voe_presetting(0, 0, 0, 0, 0,
                                    1, output_width, output_height, bps, 1,
                                    0, 0, 0, 0, 0,
                                    0, 0, 0);

    printf("VOE heap = %d\r\n", heap);

    video_ctx = mm_module_open(&video_module);
    if (!video_ctx) {
        return NULL;
    }
    if (mm_module_ctrl(video_ctx, CMD_VIDEO_SET_PARAMS, (int)&parameters) < 0
        || mm_module_ctrl(video_ctx, CMD_VIDEO_SNAPSHOT_CB, (int)jpeg_callback) < 0
        || mm_module_ctrl(video_ctx, CMD_VIDEO_APPLY, channel) < 0) {
        printf("MI48 RTSP: external JPEG initialization failed\r\n");
        return NULL;
    }

    mi48_ctx = mm_module_open(&tip_module);

    if (!mi48_ctx) {
        return NULL;
    }

    if (mm_module_ctrl(mi48_ctx, MM_CMD_SET_QUEUE_LEN, 1) < 0 || mm_module_ctrl(mi48_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC) < 0) {
        return NULL;
    }

    return mi48_ctx;
}