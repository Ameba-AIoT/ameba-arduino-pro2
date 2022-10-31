#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "camera_drv.h"

#ifdef __cplusplus
}
#endif

#define DEFAULT_PRESET          -1

#define VIDEO_ENABLE            1
#define VIDEO_DISABLE           0

#define VIDEO_SNAPSHOT_ENABLE   1
#define VIDEO_SNAPSHOT_DISABLE  0

/*****************************************************************************
ISP CHANNEL
    0: HEVC
    1: JPEG
    2: NV12
    4: only RGB
*****************************************************************************/
#define V1_CHANNEL              0
#define V2_CHANNEL              1
#define V3_CHANNEL              2

/****************************************************************************
ENCODE TYPE
   0:HEVC 
   1:H264 
   2:JPEG 
   3:NV12 
   4:RGB 
   5:HEVC+JPEG 
   6:H264+JPEG
*****************************************************************************/
enum encode_type {
    VIDEO_HEVC = 0,
    VIDEO_H264,
    VIDEO_JPEG,
    VIDEO_NV12,
    VIDEO_RGB,
    VIDEO_NV16,
    VIDEO_HEVC_JPEG,
    VIDEO_H264_JPEG
};

#define	VIDEO_QCIF  0
#define	VIDEO_CIF   1
#define	VIDEO_WVGA  2
#define	VIDEO_VGA   3
#define	VIDEO_D1    4
#define	VIDEO_HD    5
#define	VIDEO_FHD   6
#define	VIDEO_3M    7
#define	VIDEO_5M    8
#define	VIDEO_2K    9

// define video resolution
//#define VIDEO_2K_WIDTH    2560
//#define VIDEO_2K_HEIGHT   1440
#define VIDEO_FHD_WIDTH     1920
#define VIDEO_FHD_HEIGHT    1080
#define VIDEO_HD_WIDTH      1280
#define VIDEO_HD_HEIGHT     720
#define VIDEO_VGA_WIDTH     640
#define VIDEO_VGA_HEIGHT    480

// define video frame rate
#define CAM_FPS             30
// define video group of pictures
#define CAM_GOP             30
// define video bit rate
#define CAM_BPS             2*1024*1024
// define video rate control
#define CAM_RCMODE          2 // 1: CBR, 2: VBR

// define video codec
#define USE_H265 0
#if USE_H265
#include "sample_h265.h"
#define VIDEO_TYPE VIDEO_HEVC
#define VIDEO_CODEC AV_CODEC_ID_H265
#else
#include "sample_h264.h"
#define VIDEO_TYPE VIDEO_H264
#define VIDEO_CODEC AV_CODEC_ID_H264
#endif

class CameraSetting{
    public:
        CameraSetting(void);
        CameraSetting(uint8_t preset);
        CameraSetting(uint8_t resolution, uint8_t fps, uint8_t decoder , uint8_t snapshot);

        int8_t _preset = -1;
        uint8_t _resolution;
        uint8_t _fps;
        uint8_t _decoder;
        uint8_t _snapshot;
        int _w;
        int _h;
        
        friend class CameraClass;
};

class CameraClass{
    public:
        CameraClass(void);
        ~CameraClass();

        void init(CameraSetting *obj);
        void init(int w, int h, int bps, int preset);
        void init(int enable, int w, int h, int bps, int snapshot, int preset);

        void deInit(void);

        void open(void);
        void open(CameraSetting *obj);
        void open(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode);
        void start(CameraSetting *obj);
        void close(void);
        mm_context_t *getIO(void);
   
    private:
        mm_context_t *video_data;
        
};
#endif
