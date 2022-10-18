#include <Arduino.h>
#include "rtsp.h"

#define ON  1
#define OFF 0
#define DEBUG 0

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n"fmt"\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

RTSPClass::RTSPClass(){
    rtspData = NULL;
};
RTSPClass::~RTSPClass(){};

/**
  * @brief  Initialization for RTSP module by setting up RTSP paramters. 
  Default value: channel_idx : 0
                   video type: AVMEDIA_TYPE_VIDEO
                   fps: 30
                   bps: 2*1024*1024
                   video_codec: AV_CODEC_ID_H264
  * @param  none
  * @retval none
  */
void RTSPClass::init(void) {
    rtspData = RTSP_Init();
    CAMDBG("RTSP_Init done");
    RTSP_Select_Stream(rtspData->priv, ch_idx);
    CAMDBG("RTSP_Select_Stream done");
    RTSP_Set_Params(rtspData->priv, video_type, fps, bps, VC);
    CAMDBG("RTSP_Set_Params done");
    RTSP_Set_Apply(rtspData->priv);
    CAMDBG("RTSP_Set_Apply done");
}

/**
  * @brief  Start RTSP streaming
  * @param  void pointer to rtsp obj
  * @retval none
  */
void RTSPClass::open (){
    
    if (rtspData->priv == NULL) {
        CAMDBG("Streaming failed, RTSP not initialised yet.");
    }
    else {
        CAMDBG("Start Streaming");
        RTSP_Set_Streaming ((void *)rtspData, ON);
    }
}


/**
  * @brief  Get RTSP data pointer
  * @param  none
  * @retval data pointer
  */
mm_context_t *RTSPClass::getIO(void) {
    // TODO : add a if check
    return rtspData;
}


/**
  * @brief  Stop RTSP streaming
  * @param  void pointer to rtsp obj
  * @retval none
  */
void RTSPClass::close(){
    RTSP_Set_Streaming(rtspData->priv, OFF);
}

/**
  * @brief  Deinit and release all the resources set for RTSP 
  * @param  void pointer to rtsp obj
  * @retval none
  */
void RTSPClass::deInit(){
    if (RTSP_DeInit(rtspData->priv) == NULL) {
        CAMDBG("RTSP DeInit.");
    }
    else {
        CAMDBG("RTSP need to be DeInit.");
    }
}