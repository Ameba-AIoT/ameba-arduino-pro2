#ifndef __VIDEO_H__
#define __VIDEO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "video_drv.h"

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
#define VIDEO_WVGA_WIDTH    640
#define VIDEO_WVGA_HEIGHT   360

// define video frame rate
#define CAM_FPS             30
#define CAM_NN_FPS          10

// define video group of pictures
#define CAM_GOP             30
#define CAM_NN_GOP          10

// define video bit rate
#define CAM_BPS             2*1024*1024
#define CAM_NN_BPS          1*1024*1024

// define video rate control
#define CAM_RCMODE          2 // 1: CBR, 2: VBR

// define stream id
#define v1_STREAMING_ID 0
#define v2_STREAMING_ID 1
#define v3_STREAMING_ID 2
#define v4_STREAMING_ID 4

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

class MMFModule {
    friend class StreamIO;
    friend class Video;

    public:

    protected:
        mm_context_t* _p_mmf_context = NULL;
};

class CameraSetting {
    // To be done
};

class VideoSetting {
    friend class Video;

    public:
        VideoSetting(uint8_t preset = 0);
        VideoSetting(uint8_t resolution, uint8_t fps, uint8_t encoder, uint8_t snapshot);
        int8_t _preset = -1;

        uint8_t _resolution;
        uint16_t _w;
        uint16_t _h;
        uint16_t _fps;
        uint32_t _bps;
        uint8_t _encoder;
        uint8_t _snapshot;

    private:

};

class Video {
    public:
        void configVideoChannel(int ch, VideoSetting& config);
        void camInit(CameraSetting& config);
        void camDeinit(void);
        void videoInit(void);
        void videoDeinit(void);
        void channelBegin(int ch = 0);
        void channelEnd(int ch = 0);
        MMFModule getStream(int ch = 0);
		
        void setSnapshotCallback(int ch);
        static int snapshotCB(uint32_t jpeg_addr, uint32_t jpeg_len);
        void getImage(int ch);

        void setFPS(int fps);
        void printSnapshotInfo(void);
        void printInfo(void);

    private:
        MMFModule videoModule[4];

        int channelEnable[4] = {0};
        const int channel[4] = {v1_STREAMING_ID, v2_STREAMING_ID, v3_STREAMING_ID, v4_STREAMING_ID};
        int resolution[4] = {0};
        uint16_t w[4] = {0};
        uint16_t h[4] = {0};
        uint16_t fps[4] = {0};
        uint32_t bps[4] = {0};
        uint8_t encoder[4] = {0};
        uint8_t snapshot[4] = {0};

        String encoderArray [8] = {"HEVC", "H264", "JPEG","NV12", "RGB","NV16", "HEVC+JPEG", "H264+JPEG"};
        String resolutionArray [10] = {"VIDEO_QCIF", "VIDEO_CIF", "VIDEO_WVGA","VIDEO_VGA", "VIDEO_D1", "VIDEO_HD", "VIDEO_FHD", "VIDEO_3M", "VIDEO_5M", "VIDEO_2K"};

        static uint32_t image_addr;
        static uint32_t image_len;   
};

extern Video Camera;

#endif
