#include "rtsp_drv.h"
#include "mmf2_link.h"
#include "mmf2_siso.h"
#include "mmf2_module.h"
#include "sensor.h"
#include "rtsp/rtsp_api.h"
#include "module_rtsp2.h"
#include "queue.h"

#define DEBUG 0

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n"fmt"\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

extern void rtp_stream_statistics_sync(struct stream_context *stream_ctx);

static rtsp2_params_t rtsp_params = {
    .type = 0,
    .u = {
        .v = {
            .codec_id = 0,
            .fps      = 0,
            .bps      = 0
        }
    }
};

mm_context_t* RTSP_Init (void) { 
    mm_context_t *rtsp_data = (mm_context_t *)rtw_malloc(sizeof(mm_context_t));
    if (!rtsp_data) {
        return NULL;
    }
    memset(rtsp_data, 0, sizeof(mm_context_t));
    rtsp_data->queue_num = 1;		// default 1 queue, can set multiple queue by command MM_CMD_SET_QUEUE_NUM
    rtsp_data->module = &rtsp2_module; 
    rtsp_data->priv = rtsp2_module.create(rtsp_data); // rtsp_data->priv = p->create(rtsp_data);
    if (!rtsp_data->priv) {
        CAMDBG("fail------");
        if (rtsp_data->priv) {
            rtsp2_module.destroy(rtsp_data->priv);
        }
        if (rtsp_data) {
            free(rtsp_data);
        }
        return NULL;
    }
    CAMDBG("module open - free heap %d", xPortGetFreeHeapSize());

    return rtsp_data;
}

// Select channel index 0 or 1
int RTSP_Select_Stream (void *p, int channel_idx) {
    return rtsp2_control(p, CMD_RTSP2_SELECT_STREAM, channel_idx);
}

// Apply parameters set
int RTSP_Set_Apply (void *p) {
    return rtsp2_control(p, CMD_RTSP2_SET_APPLY, 0);
}

// Decide to on or off streaming
void RTSP_Set_Streaming (void *p, int arg) { 
    CAMDBG("Set Streaming");
    mm_module_ctrl((mm_context_t *)p, CMD_RTSP2_SET_STREAMMING, ON);
}

// Set parameters for RTSP
int RTSP_Set_Params (void *p, uint32_t video_type, uint32_t rtsp_fps, uint32_t rtsp_bps, uint32_t video_codec) {
    rtsp_params.type = video_type;
    rtsp_params.u.v.fps = rtsp_fps;
    rtsp_params.u.v.bps = rtsp_bps;
    rtsp_params.u.v.codec_id = video_codec;
    return rtsp2_control(p, CMD_RTSP2_SET_PARAMS, (int)&rtsp_params);
}

// deinit and release all resources for RTSP
mm_context_t* RTSP_DeInit (void *p){
    mm_queue_item_t *tmp_item;
    mm_context_t *rtsp_data = (mm_context_t *)rtw_malloc(sizeof(mm_context_t));
    rtsp_data = p;
    for (int i = 0; i < rtsp_data->queue_num; i++) {
        if (rtsp_data->port[i].output_recycle && rtsp_data->port[i].output_ready) {
            while (xQueueReceive(rtsp_data->port[i].output_ready, (void *)&tmp_item, 0) == pdTRUE) {
                xQueueSend(rtsp_data->port[i].output_recycle, (void *)&tmp_item, 0);
            }
            CAMDBG("module close - move item to recycle");
            while (xQueueReceive(rtsp_data->port[i].output_recycle, (void *)&tmp_item, 0) == pdTRUE) {
                CAMDBG("module close - tmp_item %x", tmp_item);
                if (tmp_item) {
                    CAMDBG("module close - data_addr %x", tmp_item->data_addr);
                    if (i == 0) {
                        // if (tmp_item->data_addr && ctx->module->del_item) {
                        //     ctx->module->del_item(ctx->priv, (void *)tmp_item->data_addr);
                        // }
                    } else {
                        if (tmp_item->data_addr) {
                            free((void *)tmp_item->data_addr);
                        }
                    }
                    tmp_item->data_addr = 0;
                    free(tmp_item);
                    tmp_item = NULL;
                }
                xQueueSend(rtsp_data->port[i].output_ready, (void *)&tmp_item, 0);
            }
            CAMDBG("module close - clean resource in recycle");
            // create port
            vQueueDelete(rtsp_data->port[i].output_recycle);
            vQueueDelete(rtsp_data->port[i].output_ready);
            CAMDBG("module close - free port");
        }
    }
    // call module destory, cannot delete item after destory
    rtsp2_destroy(rtsp_data->priv);

    free(rtsp_data);
    CAMDBG("module close - free context");
    CAMDBG("module close - free heap %d", xPortGetFreeHeapSize());
    
    return NULL;
}