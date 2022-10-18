#include <Arduino.h>
#include "camera.h"

#define DEBUG 0

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: "fmt"", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "camera_drv.h"

#ifdef __cplusplus
}
#endif

CameraClass::CameraClass(){
    video_data = NULL;
};

CameraClass::~CameraClass(){};

/**
  * @brief  initialization for the camera sensor
  * @param  none
  * @retval  none
  */
void CameraClass::init(){
    int w = 1920;
    int h = 1080;
    int bps = 2*1024*1024;
    
    return init(w, h, bps);
}

/**
  * @brief  initialization for the camera sensor
  * @param  w       : width
            h       : height
            bps     : bit rate in bits per second
  * @retval  none
  */
void CameraClass::init(int w, int h, int bps){
    int enable = 1;
    int snapshot = 0;
    
    return init(enable, w, h, bps, snapshot);
}

/**
  * @brief  initialization for the camera sensor
  * @param  enable  : sensor enable status
            w       : width
            h       : height
            bps     : bit rate in bits per second
            snapshot: eanble or disable snapshot function
  * @retval  none
  */
void CameraClass::init(int enable, int w, int h, int bps, int snapshot) {
    int heapSize = cameraConfig(enable, w, h, bps, snapshot);
    printf("[%s] VOE heap size is: %d", __FUNCTION__, heapSize);
    video_data = cameraInit();
}

/**
  * @brief  deinitialization for the camera sensor
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::deInit(void){
    if (cameraDeInit(video_data) == NULL) {
        printf("RTSP DeInit Done.");
    }
    else {
        printf("RTSP DeInit Failed.");
    }
}

/**
  * @brief  open camera with default value setting
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::open(){
    int stream_id = V1_CHANNEL;
    int type =VIDEO_TYPE; 
    int res =V1_RESOLUTION; 
    int w=V1_WIDTH;
    int h=V1_HEIGHT;
    int bps=V1_BPS;
    int fps=V1_FPS;
    int gop=V1_GOP;
    int rc_mode=V1_RCMODE;
    cameraOpen(video_data, video_data->priv, stream_id, type, res, w, h, bps, fps, gop, rc_mode);
}

/**
  * @brief  open camera with default value setting
  * @param  stream_id: 
            type     : video or audio type 
            res      : video resolution
            w        : width
            h        : hight
            bps      : bit rate in bits per second
            fps      : frame rate in frames per second
            gop      ： group of pictures
            rc_mode  : enable or disable constant rate mode
  * @retval  none
  */
void CameraClass::open(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode) {
    cameraOpen(p, p_priv, stream_id, type, res, w, h, bps, fps, gop, rc_mode);
}

/**
  * @brief  start camera upon camera settings were defined
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::start(){
    cameraStart(video_data->priv, V1_CHANNEL);
}


/**
  * @brief  Get video data pointer
  * @param  none
  * @retval data pointer
  */
mm_context_t *CameraClass::getIO(void) {
    //TODO : add a if check 
    return video_data;
}


/**
  * @brief  close camera while transmision is finished
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::close(){
    cameraStopVideoStream(video_data->priv, V1_CHANNEL);
}