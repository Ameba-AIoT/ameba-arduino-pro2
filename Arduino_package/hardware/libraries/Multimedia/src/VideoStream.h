#ifndef __VIDEO_STREAM_H__
#define __VIDEO_STREAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "video_drv.h"

#ifdef __cplusplus
}
#endif

#define DEFAULT_PRESET -1

#define VIDEO_ENABLE  1
#define VIDEO_DISABLE 0

#define VIDEO_SNAPSHOT_ENABLE  1
#define VIDEO_SNAPSHOT_DISABLE 0

/*****************************************************************************
ISP CHANNEL
    0: HEVC
    1: JPEG
    2: NV12
    4: only RGB
*****************************************************************************/
#define V1_CHANNEL 0
#define V2_CHANNEL 1
#define V3_CHANNEL 2

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

// #define	VIDEO_QCIF  0   // Quarter Common Intermediate Format(QCIF) 176*144
// #define	VIDEO_CIF   1   // Common Intermediate Format(CIF)          352*288
#define VIDEO_WVGA 2    // 360p                                     640*360
#define VIDEO_VGA  3    // Standard Definition(SD) 480p             640*480
#define VIDEO_D1   4    // Full D1(D1)                              720*480
#define VIDEO_HD   5    // High Definition(HD)                      1280*720
#define VIDEO_FHD  6    // Full HD(FHD)                             1920*1080
// #define	VIDEO_3M    7   // 3M pixels                                1536*2048
// #define	VIDEO_5M    8   // 5M pixels                                2592*1944
// #define	VIDEO_2K    9   // Quad HD(QHD)                             2560*1400
#define VIDEO_CUSTOM 10

// define video resolution
#define VIDEO_FHD_WIDTH   1920
#define VIDEO_FHD_HEIGHT  1080
#define VIDEO_HD_WIDTH    1280
#define VIDEO_HD_HEIGHT   720
#define VIDEO_D1_WIDTH    720
#define VIDEO_D1_HEIGHT   480
#define VIDEO_VGA_WIDTH   640
#define VIDEO_VGA_HEIGHT  480
#define VIDEO_WVGA_WIDTH  640
#define VIDEO_WVGA_HEIGHT 360

// define video frame rate
#define CAM_FPS    30
#define CAM_NN_FPS 10

// define video group of pictures
#define CAM_GOP    30
#define CAM_NN_GOP 10

// define default video bit rate
#define CAM_BPS    4 * 1024 * 1024
#define CAM_NN_BPS 1 * 1024 * 1024

// define video rate control
#define CAM_RCMODE 2    // 1: CBR, 2: VBR

// define stream id
#define v1_STREAMING_ID 0
#define v2_STREAMING_ID 1
#define v3_STREAMING_ID 2
#define v4_STREAMING_ID 4

// ISP control max and min values
#define BRIGHTNESS_MIN   -64
#define BRIGHTNESS_MAX   64
#define CONTRAST_MIN     0
#define CONTRAST_MAX     100
#define SATURATION_MIN   0
#define SATURATION_MAX   100
#define SHARPNESS_MIN    0
#define SHARPNESS_MAX    100
#define EXPOSURETIME_MAX 33333
#define AEGAIN_MIN       256
#define AEGAIN_MAX       32768
#define REDBALANCE_MIN   256
#define REDBALANCE_MAX   2047
#define BLUEBALANCE_MIN  256
#define BLUEBALANCE_MAX  2047

class MMFModule {
    friend class StreamIO;
    friend class Video;

public:

protected:
    mm_context_t* _p_mmf_context = NULL;
};

class CameraSetting {
    friend class Video;

public:
    void reset(void);
    void setBrightness(int value);
    void getBrightness(void);
    void setContrast(int value);
    void getContrast(void);
    void setSaturation(int value);
    void getSaturation(void);
    void setSharpness(int value);
    void getSharpness(void);
    void setLDC(int enable);
    void getLDC(void);
    void setWDR(int enable);
    void getWDR(void);
    void setWDRLevel(int value);
    void getWDRLevel(void);
    void setExposureMode(int enable);
    void getExposureMode(void);
    void setExposureTime(int time);
    void getExposureTime(void);
    void setAEGain(int value);
    void getAEGain(void);
    void setPowerLineFreq(int enable);
    void getPowerLineFreq(void);
    void setAWB(int enable);
    void getAWB(void);
    void getWBTemp(void);
    void setRedBalance(int value);
    void getRedBalance(void);
    void setBlueBalance(int value);
    void getBlueBalance(void);
    void setGrayMode(int enable);
    void getGrayMode(void);
    void setDayNightMode(int enable);
    void getDayNightMode(void);

private:
    int ret = 0;
};

class VideoSetting {
    friend class Video;

public:
    VideoSetting(uint8_t preset = 0);
    VideoSetting(uint8_t resolution, uint8_t fps, uint8_t encoder, uint8_t snapshot);
    VideoSetting(uint16_t w, uint16_t h, uint8_t fps, uint8_t encoder, uint8_t snapshot);

    void setBitrate(uint32_t bitrate);
    void setJpegQuality(uint8_t quality);
    void setRotation(int angle);

    uint16_t width(void);
    uint16_t height(void);
    uint16_t fps(void);

    uint8_t _resolution;
    uint16_t _w;
    uint16_t _h;
    uint16_t _fps;
    uint32_t _bps;
    uint8_t _encoder;
    // 0: none; 1: full; 2: crop;
    uint8_t _snapshot;
    uint8_t _jpeg_qlevel;
    int _rotation;

private:
    int8_t _preset = -1;
};

class Video {
public:
    void configVideoChannel(int ch, VideoSetting& config);
    //    void configVideoChannel(int ch, VideoSetting& config, int snapshot_xmin, int snapshot_ymin, int snapshot_xmax, int snapshot_ymax);
    void camInit(CameraSetting& config);
    void camDeinit(void);
    void videoInit(void);
    void videoInit(int ch);
    void videoDeinit(void);
    void videoDeinit(int ch);
    void channelBegin(int ch = 0);
    void channelEnd(int ch = 0);
    MMFModule getStream(int ch = 0);

    void getImage(int ch, uint32_t* addr, uint32_t* len);

    void setFPS(int fps);
    void printInfo(void);

private:
    void setSnapshotCallback(int ch);
    static int snapshotCB0(uint32_t jpeg_addr, uint32_t jpeg_len);
    static int snapshotCB1(uint32_t jpeg_addr, uint32_t jpeg_len);
    static int snapshotCB2(uint32_t jpeg_addr, uint32_t jpeg_len);
    static int snapshotCB3(uint32_t jpeg_addr, uint32_t jpeg_len);
    MMFModule videoModule[4];

    int channelEnable[4] = {0};
    int channel[4] = {v1_STREAMING_ID, v2_STREAMING_ID, v3_STREAMING_ID, v4_STREAMING_ID};
    int resolution[4] = {0};
    uint16_t w[4] = {0};
    uint16_t h[4] = {0};
    uint16_t fps[4] = {0};
    uint32_t bps[4] = {0};
    uint8_t encoder[4] = {0};
    uint8_t snapshot[3][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    uint8_t jpeg_qlevel[4] = {0};
    int video_rotation[4] = {0};
    typedef struct roi_param_s {
        uint32_t xmin;
        uint32_t ymin;
        uint32_t xmax;
        uint32_t ymax;
    } roi_param_t;
    String encoderArray[8] = {"HEVC", "H264", "JPEG", "NV12", "RGB", "NV16", "HEVC+JPEG", "H264+JPEG"};
    String resolutionArray[11] = {"VIDEO_QCIF", "VIDEO_CIF", "VIDEO_WVGA", "VIDEO_VGA", "VIDEO_D1", "VIDEO_HD", "VIDEO_FHD", "VIDEO_3M", "VIDEO_5M", "VIDEO_2K", "VIDEO_CUSTOM"};

    static uint32_t image_addr[4];
    static uint32_t image_len[4];
    int MD_En;
    int _heap_size = 0;
};

extern Video Camera;

#endif
