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

uint32_t Video::image_addr = 0;
uint32_t Video::image_len = 0;

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
            _bps = CAM_BPS;
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

    if((_snapshot == 1)) {
        if ((_encoder != VIDEO_H264_JPEG) && (_encoder != VIDEO_HEVC_JPEG)) {
            printf("snapshot function not supported on selected encoder!\n\r");
            _snapshot = 0;
        }
    }
    
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

    // Video stream using VIDEO_JPEG requires setting bps = 0
    //if (encoder[ch] == VIDEO_JPEG) {
    //    bps[ch] = 0;
    //}
   
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

    for (int ch = 0; ch < 4; ch++) {
        if (channelEnable[ch]) {
            CAMDBG("%d  %d    %d    %d    %d    %d    %d    %d", ch, resolution[ch], channelEnable[ch], w[ch], h[ch], bps[ch], encoder[ch], fps[ch]);
            videoModule[ch]._p_mmf_context = cameraInit();
        
            if (encoder[ch] == VIDEO_JPEG) {
				 bps[ch] = 0;
                cameraOpen(videoModule[ch]._p_mmf_context, videoModule[ch]._p_mmf_context->priv, 
                            channel[ch],
                            encoder[ch],
                            resolution[ch],
                            w[ch],
                            h[ch],
                            bps[ch],
                            fps[ch],
                            0,
                            0,
                            snapshot[ch]);
            } else {
            cameraOpen(videoModule[ch]._p_mmf_context, videoModule[ch]._p_mmf_context->priv, 
                        channel[ch],
                        encoder[ch],
                        resolution[ch],
                        w[ch],
                        h[ch],
                        bps[ch],
                        fps[ch],
                        CAM_GOP,
                        CAM_RCMODE,
                        snapshot[ch]);
            }
        }
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
            if (encoder[ch] == VIDEO_JPEG) {
                cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 2);
            }
            if (snapshot[ch] == 1) {
                setSnapshotCallback(ch);
            }
            break;
        }
        case 1: {
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            if (encoder[ch] == VIDEO_JPEG) {
                cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 2);
            }
            if (snapshot[ch] == 1) {
                setSnapshotCallback(ch);
            }
            break;
        }
        case 2: {
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            if (encoder[ch] == VIDEO_JPEG) {
                cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 2);
            }
            if (snapshot[ch] == 1) {
                setSnapshotCallback(ch);
            }
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
  * @brief  Set channel for snapshot callback
  * @param  ch: channel to call snapshot callback
  * @retval none
  */
void Video::setSnapshotCallback(int ch) {
    cameraSnapshotRegCB(videoModule[ch]._p_mmf_context, &snapshotCB);
}

/**
  * @brief  Get snapshot info
  * @param  jpeg_addr: image address
            jpeg_len : image length
  * @retval none
  */
int Video::snapshotCB(uint32_t jpeg_addr, uint32_t jpeg_len) {
    image_addr = jpeg_addr;
    image_len = jpeg_len;
    printf("snapshot addr=%d,\n\rsnapshot size=%d\n\r", (int)jpeg_addr, (int)jpeg_len);

    return 0;
}

/**
  * @brief  Take a snapshot
  * @param  ch: channel to take a snapshot from
  * @retval none
  */
void Video::getImage(int ch) {
    if (snapshot[ch] == 1) {
        CAMDBG("Taking snapshot channel = %d\r\n", ch);
        cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 1); // 1 does not represent ch, it represents mode
        printSnapshotInfo();
    } else {
        printf("Snapshot disabled\r\n");
    }
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
  * @brief  Print out snapshot info in hexadecimal to convert it into an image using online tool (temp method).
  * @param  none
  * @retval none
  */
void Video::printSnapshotInfo(void) {
    image_addr = 0;
    image_len = 0;
    
    while ((image_addr == 0) || (image_len == 0)) {
        //wait for jpeg data to arrive
        printf("wait for jpeg data......\r\n");
        delay(10);
    }
    
    uint8_t* addr = (uint8_t *)image_addr;
    for (int i = 0; i < image_len; i++) {
        if (i % 16 == 0) {
            printf("\r\n");
        }
        printf("%02x", addr[i]);
    }
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
            printf("\r\n");
        }
    }
}
