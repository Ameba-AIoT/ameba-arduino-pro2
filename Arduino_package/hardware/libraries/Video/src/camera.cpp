#include <Arduino.h>
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "camera_drv.h"

#ifdef __cplusplus
}
#endif

#define DEBUG 0

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n" fmt "\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

CameraSetting::CameraSetting(void) {
    _preset         = 1;
    _snapshot       = 0;
    _decoder        = VIDEO_H264;
    _resolution     = VIDEO_FHD;
    _w              = VIDEO_FHD_WIDTH;
    _h              = VIDEO_FHD_HEIGHT;
    _fps            = CAM_FPS;
}

CameraSetting::CameraSetting(uint8_t preset) {
    _preset = preset;

    switch (_preset) {
        case 1:
            _resolution = VIDEO_FHD;
            _fps = CAM_FPS;
            _decoder = VIDEO_H264;
            _snapshot = 0;
            break;
        case 2:
            _resolution = VIDEO_HD;
            _fps = CAM_FPS;
            _decoder = VIDEO_H264;
            _snapshot = 0;
            break;

        case 3:
            _resolution = VIDEO_FHD;
            _fps = CAM_FPS;
            _decoder = VIDEO_JPEG;
            _snapshot = 0;
            break;

        default:
            printf("Error with preset\r\n");
            break;
   }
    
    switch (_resolution) {
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

CameraSetting::CameraSetting(uint8_t resolution, uint8_t fps, uint8_t decoder, uint8_t snapshot) {
    _resolution = resolution;
    _fps = fps;
    _decoder = decoder;
    _snapshot = snapshot;
    CAMDBG("res: %d. fps: %d. dec: %d. snap: %d.", _resolution, _fps, _decoder, _snapshot);
    switch (_resolution) {
        case VIDEO_FHD:
            _w = VIDEO_FHD_WIDTH;
            _h = VIDEO_FHD_HEIGHT;
            switch (_decoder) {
                case VIDEO_H264:
                    if (_snapshot == 0) {
                        _preset = 1;
                    } else {
                        _preset = 5; // _preset 5 means H264 with snapshot call back functions, goes to voe(1)
                    }
                    break;
                case VIDEO_JPEG:
                    if (_snapshot == 0) {
                        _preset = 3;
                    }
                    break;
                default:
                    printf("Error with video decoder type\r\n");
                    break;
            }
            break;
        case VIDEO_HD:
            _w = VIDEO_HD_WIDTH;
            _h = VIDEO_HD_HEIGHT;
            switch (_decoder) {
                case VIDEO_H264:
                    if (_snapshot == 0) {
                        _preset = 2;
                    }
                default:
                    printf("Error with video decoder type\r\n");
                    break;
            }
            break;
        default:
            printf("Error with video resolution\r\n");
            break;
    }
    CAMDBG("H: %d. W: %d. Preset: %d.", _w, _h, _preset);
}

CameraClass::CameraClass() {
    video_data = NULL;
};

CameraClass::~CameraClass() {};

/**
  * @brief  initialization for the camera sensor
  * @param  obj        : object pointer of CameraSetting Class
  * @retval none
  */

void CameraClass::init(CameraSetting *obj) {
    int bps = CAM_BPS;
    CAMDBG("H: %d. W: %d. Preset: %d.", obj->_w, obj->_h, obj->_preset);
    if(obj->_preset != -1){
        return init(obj->_w, obj->_h, bps, obj->_preset);
    }
    else{
        CAMDBG("[ERROR] Init failed, cannot allocate preset video settings");
    }
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
void CameraClass::init(int w, int h, int bps, int preset) {
    int enable   = VIDEO_ENABLE;
    int snapshot = VIDEO_SNAPSHOT_DISABLE;

    return init(enable, w, h, bps, snapshot, preset);
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
void CameraClass::init(int enable, int w, int h, int bps, int snapshot, int preset) {
    int heapSize = cameraConfig(enable, w, h, bps, snapshot, preset);
    printf("[%s] VOE heap size is: %d\r\n", __FUNCTION__, heapSize);
    video_data = cameraInit();
}

/**
  * @brief  deinitialization for the camera sensor
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::deInit(void) {
    if (cameraDeInit(video_data) == NULL) {
        printf("Camera Sensor DeInit Done.\r\n");
    } else {
        printf("Camera Sensor DeInit Failed.\r\n");
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
    cameraOpen(video_data, video_data->priv, stream_id, type, res, w, h, bps, fps, gop, rc_mode);
}

/**
  * @brief  open camera with default value setting
  * @param  void pointer to video obj
  * @retval  none
  */
void CameraClass::open(CameraSetting *obj) {
    CAMDBG("H: %d. W: %d. Preset: %d.", obj->_w, obj->_h, obj->_preset);

    int stream_id = obj->_preset - 1;
    int type = obj->_decoder;
    int res = obj->_resolution;
    int w = obj->_w;
    int h = obj->_h;
    int fps = obj->_fps;
    int bps = CAM_BPS;
    int gop = -1;
    int rc_mode = -1;

    if (obj->_preset == 1) {
        gop = CAM_GOP;
        rc_mode = CAM_RCMODE;
    } else if (obj->_preset == 2) {
        gop = CAM_GOP;
        rc_mode = CAM_RCMODE;
    } else if (obj->_preset == 3) {
        gop = 0;
        rc_mode = 0;
    }
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
void CameraClass::start(CameraSetting *obj) {
    if (obj->_preset == 1) {
        cameraStart(video_data->priv, obj->_preset - 1);
    } else if (obj->_preset == 2) {
        cameraStart(video_data->priv, obj->_preset - 1);
    }
    if (obj->_preset == 3) { // v3 example, with snapshot feature
        cameraStart(video_data->priv, obj->_preset - 1);
        cameraSnapshot(video_data->priv, obj->_preset - 1);
    }
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
