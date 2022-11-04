#include <Arduino.h>
#include "rtsp.h"

#define ON  1
#define OFF 0
#define DEBUG 0

#define VID_CH_IDX 0
#define RTSP_VIDEO_TYPE AVMEDIA_TYPE_VIDEO
#define RTSP_BPS CAM_BPS

#define AUDIO_CH_IDX 1
#define RTSP_AUDIO_TYPE AVMEDIA_TYPE_AUDIO
#define AUDIO_SAMPLE_RATE 8000
#define AUDIO_CODEC_ID AV_CODEC_ID_MP4A_LATM

static int AUDIO_EN = 0;

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n" fmt "\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

RTSPClass::RTSPClass(void) {
    rtspData = NULL;
};
RTSPClass::~RTSPClass() {};

/**
  * @brief  Initialization for RTSP module by setting up RTSP paramters. 
  * @param  obj  : object pointer to Camera Settings
  * @retval none
  */
void RTSPClass::init(CameraSetting *obj) {
    rtspData = RTSPInit();
    CAMDBG("RTSP_Init done\r\n");

    uint32_t RTSP_fps = obj->_fps;
    uint32_t AV_Codec_ID = obj->_decoder;
    uint32_t RTSP_bps = RTSP_BPS;

    if (AV_Codec_ID == VIDEO_H264) {
        AV_Codec_ID = AV_CODEC_ID_H264;
    } else if (AV_Codec_ID == VIDEO_JPEG) {
        AV_Codec_ID = AV_CODEC_ID_MJPEG;
        RTSP_bps = 0;
    }
    CAMDBG("AUDIO_EN Status: %d", AUDIO_EN);
    RTSPSelectStream(rtspData->priv, VID_CH_IDX);
    RTSPSetParamsVideo(rtspData->priv, RTSP_fps, RTSP_bps, AV_Codec_ID);
    RTSPSetApply(rtspData->priv);
    if (AUDIO_EN == 1) {
        RTSPSelectStream(rtspData->priv,AUDIO_CH_IDX);
        RTSPSetParamsAudio(rtspData->priv,AUDIO_CH_IDX, AUDIO_SAMPLE_RATE, AUDIO_CODEC_ID);
        RTSPSetApply(rtspData->priv);
    }
}

/**
  * @brief  Deinit and release all the resources set for RTSP 
  * @param  none
  * @retval none
  */
void RTSPClass::deInit(void) {
    if (RTSPDeInit(rtspData) == NULL) {
        CAMDBG("RTSP DeInit.\r\n");
    } else {
        CAMDBG("RTSP need to be DeInit.\r\n");
    }
}

/**
  * @brief  Start RTSP streaming
  * @param  none
  * @retval none
  */
void RTSPClass::open (void) {
    if (rtspData == NULL) {
        printf("Streaming failed, RTSP not initialised yet.\r\n");
    } else {
        CAMDBG("Start Streaming\r\n");
        RTSPSetStreaming ((void *)rtspData, ON);
    }
}

/**
  * @brief  Stop RTSP streaming
  * @param  none
  * @retval none
  */
void RTSPClass::close(void) {
    RTSPSetStreaming((void *)rtspData, OFF);
}

/**
  * @brief  Get RTSP data pointer
  * @param  none
  * @retval data pointer
  */
mm_context_t *RTSPClass::getIO(void) {
    // To check if rtsp init is done
    if (rtspData == NULL) {
        printf("Streaming failed, please init RTSP first.\r\n");	
        return NULL;
    } else {
        return rtspData;
    }
}

/**
  * @brief  Enable RTSP settings for Audio Video streaming
  * @param  none
  * @retval AUDIO_EN status as a integer
  */
int RTSPClass::enableAudio(void) {
    AUDIO_EN = 1;
    return AUDIO_EN;
}

/**
  * @brief  Get RTSP port value for RTSP address
  * @param  none
  * @retval port value as a integer
  */
int RTSPClass::getPort(void) {
    int port_val;
    port_val = RTSPGetPort(rtspData->priv);
    return port_val;
}
