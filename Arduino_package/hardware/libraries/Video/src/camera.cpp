#include <Arduino.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "camera_drv.h"

#ifdef __cplusplus
}
#endif

#define DEBUG 1

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n" fmt "\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

/**
  * @brief  initialize camera settings for the camera sensor
            with defualt preset, same as CameraSetting(1)
  * @param  none
  * @retval none
  */
CameraSetting :: CameraSetting(void) {
    _preset         = 1;
    _snapshot       = 0;
    _decoder        = VIDEO_H264;
    _resolution     = VIDEO_FHD;
    _w              = VIDEO_FHD_WIDTH;
    _h              = VIDEO_FHD_HEIGHT;
    _fps            = CAM_FPS;
}

/**
  * @brief  initialize camera settings for the camera sensor
  * @param  preset: select one out of 3 preset video settings
  * @retval none
  */
CameraSetting :: CameraSetting(uint8_t preset) {
    _preset = preset;

    switch(_preset) {
        case 1: //v1
            _resolution = VIDEO_FHD;
            _fps = CAM_FPS;
            _decoder = VIDEO_H264;
            _snapshot = 0;
            _w = VIDEO_FHD_WIDTH;
            _h = VIDEO_FHD_HEIGHT;
            break;
        case 2: //v2
            _v2_resolution = VIDEO_HD;
            _v2_fps = CAM_FPS;
            _v2_decoder = VIDEO_H264;
            _v2_snapshot = 0;
            _v2_w = VIDEO_HD_WIDTH;
            _v2_h = VIDEO_HD_HEIGHT;
            break;
        case 3: //v3
            _v3_resolution = VIDEO_FHD;
            _v3_fps = CAM_FPS;
            _v3_decoder = VIDEO_JPEG;
            _v3_snapshot = 0;
            _v3_w = VIDEO_FHD_WIDTH;
            _v3_h = VIDEO_FHD_HEIGHT;
            break;
        default:
            printf("Error with preset\r\n");
            break;
   }
    
    switch(_resolution) {
        case VIDEO_FHD:
            _w = VIDEO_FHD_WIDTH;
            _h = VIDEO_FHD_HEIGHT;
            break;
        case VIDEO_HD:
            _w = VIDEO_HD_WIDTH;
            _h = VIDEO_HD_HEIGHT;
            break;
        default:
            printf("Error with video resolution\r\n");
            break;
    }
}

/**
  * @brief  initialize camera settings for the camera sensor
  * @param  resolution:
            fps:
            decoder:
            snapshot:
  * @retval none
  */
CameraSetting::CameraSetting(uint8_t resolution, uint8_t fps, uint8_t decoder, uint8_t snapshot,
                                    uint8_t v2_resolution, uint8_t v2_fps, uint8_t v2_decoder, uint8_t v2_snapshot,
                                    uint8_t v3_resolution, uint8_t v3_fps, uint8_t v3_decoder, uint8_t v3_snapshot,
                                    uint8_t v4_resolution, uint8_t v4_fps) {
    _resolution = resolution;
    _fps = fps;
    _decoder = decoder;
    _snapshot = snapshot;
    _w = VIDEO_FHD_WIDTH;
    _h = VIDEO_FHD_HEIGHT;

    _v2_resolution = v2_resolution;
    _v2_fps = v2_fps;
    _v2_decoder = v2_decoder;
    _v2_snapshot = v2_snapshot;
    _v2_w = VIDEO_HD_WIDTH;
    _v2_h = VIDEO_HD_HEIGHT;

    _v3_resolution = v3_resolution;
    _v3_fps = v3_fps;
    _v3_decoder = v3_decoder;
    _v3_snapshot = v3_snapshot;
    _v3_w = VIDEO_FHD_WIDTH;
    _v3_h = VIDEO_FHD_HEIGHT;
}

CameraClass::CameraClass(){
    video_data = NULL;
};

CameraClass::~CameraClass(){};

/**
  * @brief  initialization for the camera sensor
  * @param  obj        : object pointer of CameraSetting Class
  * @retval none
  */
void CameraClass::init(CameraSetting& obj) {
    int bps = CAM_BPS;
    // update bps for v3
    if (obj._v3_decoder == VIDEO_JPEG){
        bps = 0;
    }
    CAMDBG("1 %d    %d    %d    %d    %d    %d    %d",obj._resolution,obj._fps,obj._decoder,obj._snapshot,obj._w, obj._h, bps);
    CAMDBG("2 %d    %d    %d    %d    %d    %d    %d",obj._v2_resolution,obj._v2_fps,obj._v2_decoder,obj._v2_snapshot,obj._v2_w, obj._v2_h, bps);
    CAMDBG("3 %d    %d    %d    %d    %d    %d    %d",obj._v3_resolution,obj._v3_fps,obj._v3_decoder,obj._v3_snapshot,obj._v3_w, obj._v3_h, bps);
    CAMDBG("Preset: %d",obj._preset);

    return init(obj._w, obj._h, bps,
                obj._v2_w, obj._v2_h, bps,
                obj._v3_w, obj._v3_h, bps,
                0, 0);

////    if(obj->_preset != -1){
//////        return init(obj->_w, obj->_h, bps, obj->_preset);
////        return init(obj->_w, obj->_h, bps,
////                    0,0,0,
////                    0,0,0,
////                    0,0);
////    }
////    else{
////        printf("[ERROR] Init failed, cannot allocate preset video settings");
////    }
}



/**
  * @brief  initialization for the camera sensor
  * @param  w       : width
            h       : height
            bps     : bit rate in bits per second
            preset  : configure voe heap size according to
                      different camera presets
  * @retval  none
  */
void CameraClass::init(int v1_w, int v1_h, int v1_bps,
                         int v2_w, int v2_h, int v2_bps,
                         int v3_w, int v3_h, int v3_bps,
                         int v4_w, int v4_h) {
    int enable   = VIDEO_ENABLE;
    int snapshot = VIDEO_SNAPSHOT_DISABLE;
    CAMDBG("1 %d    %d    %d    %d    %d",enable, v1_w, v1_h, v1_bps, snapshot);
    CAMDBG("2 %d    %d    %d    %d    %d",enable, v2_w, v2_h, v2_bps, snapshot);
    CAMDBG("3 %d    %d    %d    %d    %d",enable, v3_w, v3_h, v3_bps, snapshot);
    
    return init_new(enable, v1_w, v1_h, v1_bps, snapshot,
                    enable, v2_w, v2_h, v2_bps, snapshot,
                    enable, v3_w, v3_h, v3_bps, snapshot,
                    enable, v4_w, v4_h);
}


/**
  * @brief  initialization for the camera sensor, supports v1~v4 four channels
  * @param  enable  : sensor enable status
            w       : width
            h       : height
            bps     : bit rate in bits per second
            snapshot: eanble or disable snapshot function
  * @retval  none
  */
void CameraClass::init_new(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_snapshot, 
                               int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_snapshot, 
                               int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_snapshot, 
                               int v4_enable, int v4_w, int v4_h) {
//    int enable   = VIDEO_ENABLE;
//    int snapshot = VIDEO_SNAPSHOT_DISABLE;
    CAMDBG("1 %d    %d    %d    %d    %d    %d",v1_enable, v1_w, v1_h, v1_bps, v1_snapshot);
    CAMDBG("2 %d    %d    %d    %d    %d    %d",v2_enable, v2_w, v2_h, v2_bps, v2_snapshot);
    CAMDBG("3 %d    %d    %d    %d    %d    %d",v3_enable, v3_w, v3_h, v3_bps, v3_snapshot);
    int heapSize = cameraConfigNew(v1_enable, v1_w, v1_h, v1_bps, v1_snapshot, 
                                   v2_enable, v2_w, v2_h, v2_bps, v2_snapshot, 
                                   v3_enable, v3_w, v3_h, v3_bps, v3_snapshot, 
                                   v4_enable, v4_w, v4_h);
    printf("\r\n[%s] VOE heap size is: %d\r\n", __FUNCTION__, heapSize);
//    video_data = cameraInit();
}

/**
  * @brief  deinitialization for the camera sensor
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::deinit(void) {
    if (cameraDeInit(video_data) == NULL) {
        printf("Camera Sensor deinit Done.\r\n");
    } else {
        printf("Camera Sensor deinit Failed.\r\n");
    }
}

/**
  * @brief  open camera with default value setting
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::open(void) {
    int stream_id   = V1_CHANNEL;
    int type        = VIDEO_TYPE; 
    int res         = VIDEO_FHD; 
    int w           = VIDEO_FHD_WIDTH;
    int h           = VIDEO_FHD_HEIGHT;
    int bps         = CAM_BPS;
    int fps         = CAM_FPS;
    int gop         = CAM_GOP;
    int rc_mode     = CAM_RCMODE;
	int snapshot    = 0;
    cameraOpen(video_data, video_data->priv, stream_id, type, res, w, h, bps, fps, gop, rc_mode, snapshot);
}

/**
  * @brief  open camera with default value setting
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::open(CameraSetting& obj) {

    video_data = cameraInit();
    
    CAMDBG("1 %d    %d    %d    %d    %d    %d    %d",obj._resolution,obj._fps,obj._decoder,obj._snapshot,obj._w, obj._h);
    CAMDBG("2 %d    %d    %d    %d    %d    %d    %d",obj._v2_resolution,obj._v2_fps,obj._v2_decoder,obj._v2_snapshot,obj._v2_w, obj._v2_h);
    CAMDBG("3 %d    %d    %d    %d    %d    %d    %d",obj._v3_resolution,obj._v3_fps,obj._v3_decoder,obj._v3_snapshot,obj._v3_w, obj._v3_h);
    CAMDBG("Preset: %d",obj._preset);

    if(obj._resolution){
        CAMDBG("Run open(v1)");
        cameraOpen(video_data, video_data->priv, 
                    obj._streaming_id, 
                    obj._decoder, 
                    obj._resolution, 
                    obj._w, 
                    obj._h, 
                    CAM_BPS, 
                    obj._fps, 
                    CAM_GOP, 
                    CAM_RCMODE, 
                    obj._snapshot);
    }

    if(obj._v2_resolution){
        CAMDBG("Run open(v2)");
        cameraOpen(video_data, video_data->priv, 
                    obj._v2_streaming_id, 
                    obj._v2_decoder, 
                    obj._v2_resolution, 
                    obj._v2_w, 
                    obj._v2_h, 
                    CAM_BPS, 
                    obj._v2_fps, 
                    CAM_GOP, 
                    CAM_RCMODE, 
                    obj._v2_snapshot);
    }

    if(obj._v3_resolution){
        CAMDBG("Run open(v3)");
        cameraOpen(video_data, video_data->priv, 
                    obj._v3_streaming_id, 
                    obj._v3_decoder, 
                    obj._v3_resolution, 
                    obj._v3_w, 
                    obj._v3_h, 
                    0, 
                    obj._v3_fps, 
                    0, 
                    0, 
                    obj._v3_snapshot);
    }
//    if (obj->_preset % 4 == 1) {
//        gop = CAM_GOP;
//        rc_mode = CAM_RCMODE;
//        if (obj->_snapshot == 1) {
//            CAMDBG("snapshot flag set to 1");
//            snapshot = 1;
//        }
//    }
//    else if (obj->_preset == 2) {
//        gop = CAM_GOP;
//        rc_mode = CAM_RCMODE;
//    }
//    else if (obj->_preset == 3) {
//        gop = 0;
//        rc_mode = 0;
//    }
//    cameraOpen(video_data, video_data->priv, stream_id, type, res, w, h, bps, fps, gop, rc_mode, snapshot);
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
void CameraClass::open(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode, int snapshot) {
    cameraOpen(p, p_priv, stream_id, type, res, w, h, bps, fps, gop, rc_mode, snapshot);
}

/**
  * @brief  start camera upon camera settings were defined
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::start(CameraSetting& obj) {

    if(obj._resolution) {
        cameraStart(video_data->priv, obj._streaming_id);
    }

    if(obj._v2_resolution) {
        cameraStart(video_data->priv, obj._v2_streaming_id);
    }

    if(obj._v3_resolution) { // V3
        cameraStart(video_data->priv, obj._v3_streaming_id);
        getP(obj, 0);   // enable snapshot function
    }

    if(obj._resolution && obj._snapshot) { //V1_snapshot
        cameraStart(video_data->priv, obj._v3_streaming_id);
        getP(obj, 1);   // enable call back snapshot function
    }
//    if (obj->_preset == 1){
//        printf("\r\n\r\n1 obj->preset: %d\r\n\r\n", obj->_preset);
//        cameraStart(video_data->priv, obj->_preset - 1);
//    } 
//    else if (obj->_preset == 2){
//        printf("\r\n\r\n2 obj->preset: %d\r\n\r\n", obj->_preset);
//        cameraStart(video_data->priv, obj->_preset - 1);
//    }
//    else if (obj->_preset == 3){                             // v3: JPEG snapshot
//        cameraStart(video_data->priv, obj->_preset - 1);
//        //cameraSnapshot(video_data->priv, 2);
//        getP(obj, 0); // enable snapshot function
//    }
//    else if (obj->_preset == 5) {                            // v5: v1_snaphot callback
//        cameraStart(video_data->priv, obj->_preset - 5);
//        getP(obj, 1); // enable call back snapshot function
//    }
}

/**
  * @brief  Get video data pointer
  * @param  none
  * @retval data pointer
  */
mm_context_t *CameraClass::getIO(void) {
    //To check if camera sensor init is done
    if (video_data == NULL) {
        printf("\r\nPlease init camera sensor first.\r\n");
        return NULL;
    } else {
         return video_data;
    }
}

/**
  * @brief  Stop camera streaming while transmision is finished
  * @param  none
  * @retval none
  */
void CameraClass::close(void) {
    cameraStopVideoStream(video_data->priv, V1_CHANNEL);
}

/**
  * @brief  Enable snapshot function
  * @param  p       : void pointer to video object
            cb_flag : whether enable snapshot call back function
  * @retval none
  */
void CameraClass::getP(CameraSetting& obj, bool cb_flag) {
    if (cb_flag == 0){
        CAMDBG("snapshot cb disabled\r\n");
        cameraSnapshot(video_data->priv, obj._v3_streaming_id);
        
    } else {
        CAMDBG("snapshot cb enabled\r\n");
        cameraSnapshotCB(video_data);
    }
}

/**
  * @brief  Enable snapshot function
  * @param  p       : void pointer to video object
            cb_flag : whether enable snapshot call back function
  * @retval none
  */
void CameraClass::setFPS(int fps) {
    video_set_framerate(fps);
}

