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
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n" fmt "\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

extern void rtp_stream_statistics_sync(struct stream_context *stream_ctx);

//video output
static rtsp2_params_t rtsp_params = {
    .type = AVMEDIA_TYPE_VIDEO,
    .u = {
        .v = {
            .codec_id = 0,
            .fps      = 0,
            .bps      = 0
        }
    }
};

//audio output
static rtsp2_params_t rtsp_param_audio = {
    .type = AVMEDIA_TYPE_AUDIO,
    .u = {
        .a = {
            .codec_id   = 0,
            .channel    = 0,
            .samplerate = 0
        }
    }
};

// RTSP init
mm_context_t* RTSPInit (void) { 
    return mm_module_open(&rtsp2_module);
}

// Select channel index 0 (video) or 1 (audio) etc
int RTSPSelectStream (void *p, int channel_idx) {
    return rtsp2_control(p, CMD_RTSP2_SELECT_STREAM, channel_idx);
}

// Apply parameters set
int RTSPSetApply (void *p) {
    return rtsp2_control(p, CMD_RTSP2_SET_APPLY, 0);
}

// Decide to on or off streaming
void RTSPSetStreaming (void *p, int arg) { 
    CAMDBG("Set Streaming");
    mm_module_ctrl((mm_context_t *)p, CMD_RTSP2_SET_STREAMMING, arg);	
}

// Set parameters for RTSP Video
int RTSPSetParamsVideo (void *p, uint32_t RTSP_fps, uint32_t RTSP_bps, uint32_t AV_Codec) {
    rtsp_params.u.v.fps = RTSP_fps;
    rtsp_params.u.v.bps = RTSP_bps;
    rtsp_params.u.v.codec_id = AV_Codec;

    return rtsp2_control(p, CMD_RTSP2_SET_PARAMS, (int)&rtsp_params);
}

// Set parameters for RTSP Audio
int RTSPSetParamsAudio (void *p, uint32_t channel, uint32_t sample_rate, uint32_t AV_Codec) {
    rtsp_param_audio.u.a.channel = channel;
    rtsp_param_audio.u.a.samplerate = sample_rate;
    rtsp_param_audio.u.a.codec_id = AV_Codec;

    return rtsp2_control(p, CMD_RTSP2_SET_PARAMS, (int)&rtsp_param_audio);
}

// deinit and release all resources for RTSP
mm_context_t* RTSPDeInit (void *p){
    return mm_module_close((mm_context_t *)p);
}