#include "rtsp_drv.h"
#include "mmf2_module.h"
#include "module_rtsp2.h"

mm_context_t *RTSPInit(void)
{
    return mm_module_open(&rtsp2_module);
}

mm_context_t *RTSPDeinit(mm_context_t *p)
{
    return mm_module_close(p);
}

int RTSPSelectStream(void *p, int channel_idx)
{
    return rtsp2_control(p, CMD_RTSP2_SELECT_STREAM, channel_idx);
}

int RTSPSetApply(void *p)
{
    return rtsp2_control(p, CMD_RTSP2_SET_APPLY, 0);
}

void RTSPSetStreaming(void *p, int arg)
{
    mm_module_ctrl((mm_context_t *)p, CMD_RTSP2_SET_STREAMMING, arg);
}

int RTSPSetParamsVideo(void *p, uint32_t RTSP_fps, uint32_t RTSP_bps, uint32_t AV_Codec)
{
    rtsp2_params_t rtsp_params = {
        .type = AVMEDIA_TYPE_VIDEO,
        .u = {.v = {.codec_id = AV_Codec, .fps = RTSP_fps, .bps = RTSP_bps}},
    };

    return rtsp2_control(p, CMD_RTSP2_SET_PARAMS, (int)&rtsp_params);
}

int RTSPSetParamsAudio(void *p, uint32_t channel, uint32_t sample_rate, uint32_t AV_Codec)
{
    rtsp2_params_t rtsp_param_audio = {
        .type = AVMEDIA_TYPE_AUDIO,
        .u = {.a = {.codec_id = AV_Codec, .channel = channel, .samplerate = sample_rate}},
    };

    return rtsp2_control(p, CMD_RTSP2_SET_PARAMS, (int)&rtsp_param_audio);
}

int RTSPGetPort(void *p)
{
    rtsp2_ctx_t *ctx = (rtsp2_ctx_t *)p;
    struct rtsp_context *rtsp = ctx->rtsp;
    return (rtsp->connect_ctx.server_port);
}
