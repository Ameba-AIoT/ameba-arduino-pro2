#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "camera_drv.h"


#ifdef __cplusplus
}
#endif

/*****************************************************************************
ISP CHANNEL
    0: HEVC
    1: JPEG
    2: NV12
    4: only RGB
*****************************************************************************/
#define V1_CHANNEL 0


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

#define V1_ENABLE   1
#define V1_DISABLE   0

#define V1_SNAPSHOT_ENABLE 1
#define V1_SNAPSHOT_DISABLE 0
// define video resolution
#define V1_RESOLUTION VIDEO_FHD
// define video frame rate
#define V1_FPS 30
// define video group of pictures
#define V1_GOP 30
// define video bit rate
#define V1_BPS 2*1024*1024
// define video rate control
#define V1_RCMODE 2 // 1: CBR, 2: VBR
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
// define video resolution
#if V1_RESOLUTION == VIDEO_FHD
#define V1_WIDTH	1920
#define V1_HEIGHT	1080
#endif

class CameraClass {
    public:
        CameraClass(void);
        ~CameraClass();

        void init(void);
        void init(int w, int h, int bps);
        void init(int enable, int w, int h, int bps, int snapshot);
        void deInit(void);

        void open(void);
        void open(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode);
        void start(void);
        void close(void);
        mm_context_t *getIO(void);
        

    private:
        mm_context_t *video_data;
        
};
#endif
