#include <Arduino.h>
#include "Video.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "video_drv.h"

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

Video Camera;

/**
  * @brief  initialize video stream settings for the camera sensor
  * @param  preset: select one out of 3 preset video stream settings. default preset is 1
  * @retval none
  */
VideoSetting::VideoSetting(uint8_t preset) {
    switch (preset) {
        case 0: {
            _resolution = VIDEO_FHD;
            _fps = CAM_FPS;
            _bps = CAM_BPS;
            _encoder = VIDEO_H264;
            _snapshot = 0;
            break;
        }
        case 1: {
            _resolution = VIDEO_HD;
            _fps = CAM_FPS;
            _bps = CAM_BPS;
            _encoder = VIDEO_H264;
            _snapshot = 0;
            break;
        }
        case 2: {
            _resolution = VIDEO_FHD;
            _fps = CAM_FPS;
            _bps = 0;
            _encoder = VIDEO_JPEG;
            _snapshot = 0;
            break;
        }
        default: {
            printf("Invalid VideoSetting preset!\r\n");
            return;
            break;
        }
    }
    _preset = preset;

    if (_resolution == VIDEO_FHD) {
       _w = VIDEO_FHD_WIDTH;
       _h = VIDEO_FHD_HEIGHT;
    } else if (_resolution == VIDEO_HD) {
       _w = VIDEO_HD_WIDTH;
       _h = VIDEO_HD_HEIGHT;
    }
}

/**
  * @brief  initialize video settings for the camera sensor
  * @param  resolution: video resolution
            fps: frame rate in frames per second
            encoder: video encoder format to use
            snapshot: enable or disable snapshot function
  * @retval none
  */
VideoSetting::VideoSetting(uint8_t resolution, uint8_t fps, uint8_t encoder, uint8_t snapshot) {
    _resolution = resolution;
    _fps = fps;
    _bps = CAM_BPS;
    _encoder = encoder;
    _snapshot = snapshot;
    
    if (_resolution == VIDEO_FHD) {
        _w = VIDEO_FHD_WIDTH;
        _h = VIDEO_FHD_HEIGHT;
    } else if (_resolution == VIDEO_HD) {
          _w = VIDEO_HD_WIDTH;
          _h = VIDEO_HD_HEIGHT;
    }
}

/**
  * @brief  configure video stream channel
  * @param  ch : channel to configure
            config : VideoSetting object
  * @retval none
  */
void Video::configVideoChannel(int ch, VideoSetting& config) {
    // Copy in video stream settings for specified stream channel
    channelEnable[ch]   = 1;
    resolution[ch]      = config._resolution;
    w[ch]               = config._w;
    h[ch]               = config._h;
    fps[ch]             = config._fps;
    bps[ch]             = config._bps;
    encoder[ch]         = config._encoder;
    snapshot[ch]        = config._snapshot;

    // Video stream channel 2 requires setting bps = 0
    if (ch == 2) {
        bps[ch] = 0;
    }

   CAMDBG("1 %d    %d    %d    %d    %d    %d",channelEnable[0], w[0], h[0], bps[0], snapshot[0], fps[0]);
   CAMDBG("2 %d    %d    %d    %d    %d    %d",channelEnable[1], w[1], h[1], bps[1], snapshot[1], fps[1]);
   CAMDBG("3 %d    %d    %d    %d    %d    %d", channelEnable[2], w[2], h[2], bps[2], snapshot[2], fps[2]);
}

/**
  * @brief  initialization of camera sensor using existing configurations
  * @param  none
  * @retval none
  */
void Video::camInit(CameraSetting& config) {
    // To be done
}

/**
  * @brief  Deinitialization of camera sensor
  * @param  none
  * @retval none
  */
void Video::camDeinit(void) {
    // To be done
}

/**
  * @brief  initialization of video streams from camera using existing configurations
  * @param  none
  * @retval none
  */
void Video::videoInit(void) {
    int heapSize = cameraConfig(channelEnable[0], w[0], h[0], bps[0], snapshot[0],
                                channelEnable[1], w[1], h[1], bps[1], snapshot[1],
                                channelEnable[2], w[2], h[2], bps[2], snapshot[2],
                                channelEnable[3], w[3], h[3]);

    printf("\r\n[%s] VOE heap size is: %d\r\n", __FUNCTION__, heapSize);

    if (channelEnable[0]) {
        CAMDBG("0 %d    %d    %d    %d    %d    %d    %d", resolution[0], channelEnable[0], w[0], h[0], bps[0], encoder[0], fps[0]);
        videoModule[0]._p_mmf_context = cameraInit();
        cameraOpen(videoModule[0]._p_mmf_context, videoModule[0]._p_mmf_context->priv, 
                    channel[0],
                    encoder[0],
                    resolution[0],
                    w[0],
                    h[0],
                    bps[0],
                    fps[0],
                    CAM_GOP,
                    CAM_RCMODE,
                    snapshot[0]);
    }
    if (channelEnable[1]) {
        CAMDBG("1 %d    %d    %d    %d    %d    %d    %d", resolution[1], channelEnable[1], w[1], h[1], bps[1], encoder[1], fps[1]);
        videoModule[1]._p_mmf_context = cameraInit();
        cameraOpen(videoModule[1]._p_mmf_context, videoModule[1]._p_mmf_context->priv, 
                    channel[1],
                    encoder[1],
                    resolution[1],
                    w[1],
                    h[1],
                    bps[1],
                    fps[1],
                    CAM_GOP,
                    CAM_RCMODE,
                    snapshot[1]);
    }
    if (channelEnable[2]) {
        videoModule[2]._p_mmf_context = cameraInit();
        CAMDBG("2 %d    %d    %d    %d    %d    %d    %d", resolution[2], channelEnable[2], w[2], h[2], bps[2], encoder[2], fps[2]);
        cameraOpen(videoModule[2]._p_mmf_context, videoModule[2]._p_mmf_context->priv, 
                    channel[2],
                    encoder[2],
                    resolution[2],
                    w[2],
                    h[2],
                    bps[2],
                    fps[2],
                    0,
                    0,
                    snapshot[2]);
    }
}

/**
  * @brief  deinitialization of video stream module for a specific channel
  * @param  none
  * @retval none
  */
void Video::videoDeinit() {
    uint8_t i;
    for (i = 0; i < 4; i++) {
        if (videoModule[i]._p_mmf_context != NULL) {
            cameraDeinit(videoModule[i]._p_mmf_context);
        }
    }
}

/**
  * @brief  Start video streaming on a specific channel
  * @param  ch : channel to start streaming
  * @retval none
  */
void Video::channelBegin(int ch) {
    switch (ch) {
        case 0: {
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            break;
        }
        case 1: {
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            break;
        }
        case 2: {
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            getImage();   // enable snapshot function and cb func
            break;
        }
        default: {
            break;
        }
    }
}

/**
  * @brief  Stop video streaming on a specific channel
  * @param  ch : channel to stop streaming
  * @retval none
  */
void Video::channelEnd(int ch) {
    if (ch > 3) {
        ch = 0;
    }
    cameraStopVideoStream(videoModule[ch]._p_mmf_context->priv, channel[ch]);
}

/**
  * @brief  Get video stream module
  * @param  ch : channel
  * @retval video stream module of channel
  */
MMFModule Video::getStream(int ch) {
    if (ch > 3) {
        ch = 0;
    }
    return (videoModule[ch]);
}

/**
  * @brief  Enable snapshot function
  * @param  p       : void pointer to video object
            cb_flag : whether enable snapshot call back function
  * @retval none
  */
void Video::getImage(void) {
    printf("SS Enabled\r\n");
    cameraSnapshotCB(videoModule[2]._p_mmf_context);
}

/**
  * @brief  Set camera video max FPS
  * @param  fps     : max FPS
  * @retval none
  */
void Video::setFPS(int fps) {
    video_set_framerate(fps);
}

/**
  * @brief  Print out current configuration of video channels.
  * @param  none
  * @retval none
  */
void Video::printInfo(void) {
    for (int ch = 0; ch < 4; ch++) {
        if (channelEnable[ch] == 1) {
            printf("Channel: %d\r\n", channel[ch]);
            printf("Encoder type: %s\r\n", encoderArray[encoder[ch]].c_str());
            printf("Resolution: %s\r\n", resolutionArray[resolution[ch]].c_str());
            printf("Video width: %d\r\n", w[ch]);
            printf("Video height: %d\r\n", h[ch]);
            printf("fps: %d\r\n", fps[ch]);
            printf("bps: %d\r\n", bps[ch]);
            printf("Snapshot EN/DIS: %s\r\n", enablesnapshotArray[snapshot[ch]].c_str());
            printf("\r\n");
        }
    }
}
