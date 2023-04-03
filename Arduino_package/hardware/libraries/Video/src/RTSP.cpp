#include <Arduino.h>
#include "RTSP.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "rtsp_drv.h"
#include "avcodec.h"

#ifdef __cplusplus
}
#endif

#define VID_CH_IDX 0
#define AUDIO_CH_IDX 1

RTSP::RTSP(void) {
}

RTSP::~RTSP(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (RTSPDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("RTSP deinit failed\r\n");
    }
}

void RTSP::configVideo(VideoSetting& config) {
    // RTSPInit if not previously done so
    if (_p_mmf_context == NULL) {
        _p_mmf_context = RTSPInit();
    }
    if (_p_mmf_context == NULL) {
        printf("RTSP init failed\r\n");
        return;
    }

    uint32_t RTSP_fps = config._fps;
    uint32_t AV_Codec_ID = config._encoder;
    uint32_t RTSP_bps = config._bps;

    if (AV_Codec_ID == VIDEO_JPEG) {
        AV_Codec_ID = AV_CODEC_ID_MJPEG;
        RTSP_bps = 0; 
    } else if ((AV_Codec_ID == VIDEO_HEVC) || (AV_Codec_ID == VIDEO_HEVC_JPEG)) {
        AV_Codec_ID = AV_CODEC_ID_H265;
    } else if ((AV_Codec_ID == VIDEO_H264) || (AV_Codec_ID == VIDEO_H264_JPEG)) {
        AV_Codec_ID = AV_CODEC_ID_H264;
    }
    RTSPSelectStream(_p_mmf_context->priv, VID_CH_IDX);
    RTSPSetParamsVideo(_p_mmf_context->priv, RTSP_fps, RTSP_bps, AV_Codec_ID);
    RTSPSetApply(_p_mmf_context->priv);
}

void RTSP::configAudio(AudioSetting& config, Audio_Codec_T codec) {
    // RTSPInit if not previously done so
    if (_p_mmf_context == NULL) {
        _p_mmf_context = RTSPInit();
    }
    if (_p_mmf_context == NULL) {
        printf("RTSP init failed\r\n");
        return;
    }

    uint32_t sample_rate = config._sampleRate;
    uint32_t channel = config._audioParams.channel;

    RTSPSelectStream(_p_mmf_context->priv, AUDIO_CH_IDX);
    RTSPSetParamsAudio(_p_mmf_context->priv, channel, sample_rate, codec);
    RTSPSetApply(_p_mmf_context->priv);
}

void RTSP::begin(void) {
    if (_p_mmf_context == NULL) {
        printf("Need RTSP init first\r\n");
    } else {
        RTSPSetStreaming((void *)_p_mmf_context, 1);
    }
}

void RTSP::end(void) {
    if (_p_mmf_context == NULL) {
        printf("Need RTSP init first\r\n");
    }
    RTSPSetStreaming((void *)_p_mmf_context, 0);
}

int RTSP::getPort(void) {
    if (_p_mmf_context == NULL) {
        printf("Need RTSP init first\r\n");
    }
    return RTSPGetPort(_p_mmf_context->priv);
}

void RTSP::printInfo(void) {
    int port = getPort();
    printf("%d\r\n", port);
    printf("\r\n");
}
