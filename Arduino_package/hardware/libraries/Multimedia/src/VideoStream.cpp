#include <Arduino.h>
#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "video_drv.h"

#ifdef __cplusplus
}
#endif

Video Camera;

uint32_t Video::image_addr[4] = {0};
uint32_t Video::image_len[4] = {0};

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
            _resolution = VIDEO_HD;
            _fps = CAM_FPS;
            _bps = CAM_BPS;
            _encoder = VIDEO_JPEG;
            _snapshot = 0;
            _jpeg_qlevel = 2;
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

VideoSetting::VideoSetting(uint8_t resolution, uint8_t fps, uint8_t encoder, uint8_t snapshot) {
    _resolution = resolution;
    _fps = fps;
    _bps = CAM_BPS;
    _encoder = encoder;
    _snapshot = snapshot;
    _jpeg_qlevel = 5;

    if ((_snapshot == 1)) {
        if ((_encoder != VIDEO_H264_JPEG) && (_encoder != VIDEO_HEVC_JPEG) && (_encoder != VIDEO_JPEG)) {
            printf("snapshot function not supported on selected encoder!\n\r");
            _snapshot = 0;
        }
    }

    if (encoder == VIDEO_JPEG) {
        _jpeg_qlevel = 2;
    }

    if (_resolution == VIDEO_FHD) {
        _w = VIDEO_FHD_WIDTH;
        _h = VIDEO_FHD_HEIGHT;
    } else if (_resolution == VIDEO_HD) {
        _w = VIDEO_HD_WIDTH;
        _h = VIDEO_HD_HEIGHT;
    } else if (_resolution == VIDEO_VGA) {
        _w = VIDEO_VGA_WIDTH;
        _h = VIDEO_VGA_HEIGHT;
    }
}

VideoSetting::VideoSetting(uint16_t w, uint16_t h, uint8_t fps, uint8_t encoder, uint8_t snapshot) {
    _resolution = VIDEO_CUSTOM;
    _fps = fps;
    _bps = CAM_BPS;
    _encoder = encoder;
    _snapshot = snapshot;
    _w = w;
    _h = h;
    _jpeg_qlevel = 5;

    // Check resolution maximums
    if (_w > 1920) {
        _w = 1920;
        printf("Maximum resolution 1920 x 1080 \r\n");
    }
    if (_h > 1080) {
        _h = 1080;
        printf("Maximum resolution 1920 x 1080 \r\n");
    }

    // Check resolution minimums
    if (encoder == VIDEO_JPEG) {
        _jpeg_qlevel = 2;

        if (_w < 352) {
            _w = 352;
            printf("Minimum JPEG resolution 352 x 288 \r\n");
        }
        if (_h < 288) {
            _h = 288;
            printf("Minimum JPEG resolution 352 x 288 \r\n");
        }
    } else {
        if (_w < 176) {
            _w = 176;
            printf("Minimum resolution 176 x 144 \r\n");
        }
        if (_h < 144) {
            _h = 144;
            printf("Minimum resolution 176 x 144 \r\n");
        }
    }

    // Check custom resolution is a multiple of 16
    if ((_w % 16) != 0) {
        // Round down to nearest multiple of 16
        _w -= (_w % 16);
        // Round up if it does not exceed maximum resolution
        if ((_w + 16) <= 1920) {
            _w += 16;
        }
        printf("Custom resolution must be a multiple of 16, new resolution: %d X %d\r\n", _w, _h);
    }
    if ( ((_h % 16) != 0) && (_h != 360) && (_h != 1080) ) {
        _h -= (_h % 16);
        if ((_h + 16) <= 1080) {
            _h += 16;
        }
        printf("Custom resolution must be a multiple of 16, new resolution: %d X %d\r\n", _w, _h);
    }

    if((_snapshot == 1)) {
        if ((_encoder != VIDEO_H264_JPEG) && (_encoder != VIDEO_HEVC_JPEG) && (_encoder != VIDEO_JPEG)) {
            printf("snapshot function not supported on selected encoder!\n\r");
            _snapshot = 0;
        }
    }
}

void VideoSetting::setBitrate(uint32_t bitrate) {
    if (bitrate < (1 * 1024 * 1024)) {
        bitrate = (1 * 1024 * 1024);
    }
    if (bitrate > (50 * 1024 * 1024)) {
        bitrate = (50 * 1024 * 1024);
    }
    _bps = bitrate;
}

void VideoSetting::setJpegQuality(uint8_t quality) {
    if (quality < 1) {
        quality = 1;
    }
    if (quality > 9) {
        quality = 9;
    }
    _jpeg_qlevel = quality;
}

uint16_t VideoSetting::width(void) {
    return _w;
}

uint16_t VideoSetting::height(void) {
    return _h;
}

uint16_t VideoSetting::fps(void) {
    return _fps;
}

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
    jpeg_qlevel[ch]     = config._jpeg_qlevel;

    // Video stream using VIDEO_JPEG requires setting bps = 0
    // if (encoder[ch] == VIDEO_JPEG) {
    //     bps[ch] = 0;
    // }

    //printf("V1 %d    %d    %d    %d    %d    %d", channelEnable[0], w[0], h[0], bps[0], snapshot[0], fps[0]);
    //printf("V2 %d    %d    %d    %d    %d    %d", channelEnable[1], w[1], h[1], bps[1], snapshot[1], fps[1]);
    //printf("V3 %d    %d    %d    %d    %d    %d", channelEnable[2], w[2], h[2], bps[2], snapshot[2], fps[2]);
    //printf("V4 %d    %d    %d    %d    %d    %d", channelEnable[3], w[3], h[3]);
}

void Video::camInit(CameraSetting& config) {
    // To be done
}

void Video::camDeinit(void) {
    // To be done
}

void Video::videoInit(void) {
    int heapSize = cameraConfig(channelEnable[0], w[0], h[0], bps[0], snapshot[0],
                                channelEnable[1], w[1], h[1], bps[1], snapshot[1],
                                channelEnable[2], w[2], h[2], bps[2], snapshot[2],
                                channelEnable[3], w[3], h[3]);
    (void)heapSize;
    //printf("\r\n[%s] VOE heap size is: %d\r\n", __FUNCTION__, heapSize);

    for (int ch = 0; ch < 4; ch++) {
        if (channelEnable[ch]) {
            //printf("%d  %d    %d    %d    %d    %d    %d    %d", ch, resolution[ch], channelEnable[ch], w[ch], h[ch], bps[ch], encoder[ch], fps[ch]);
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
                            snapshot[ch],
                            jpeg_qlevel[ch]);
            } else if (ch == 3) {
                //printf("V4 %d    %d    %d    %d", resolution[3], channelEnable[3], w[3], h[3]);
                bps[3] = 1*1024*1024;
                cameraOpenNN(videoModule[3]._p_mmf_context, videoModule[3]._p_mmf_context->priv,
                    channel[3],
                    encoder[3],
                    resolution[3],
                    w[3],
                    h[3],
                    bps[3],
                    CAM_NN_FPS,
                    CAM_NN_GOP,
                    0);     // direct output flag
            } else {
                //printf("%d  %d    %d    %d    %d    %d    %d    %d", ch, resolution[ch], channelEnable[ch], w[ch], h[ch], bps[ch], encoder[ch], fps[ch]);
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
                            snapshot[ch],
                            jpeg_qlevel[ch]);
            }
        }
    }
}

void Video::videoDeinit(void) {
    uint8_t i;
    for (i = 0; i < 4; i++) {
        if (videoModule[i]._p_mmf_context != NULL) {
            cameraDeinit(videoModule[i]._p_mmf_context);
        }
    }
}

void Video::channelBegin(int ch) {
    switch (ch) {
        case 0:
        case 1:
        case 2: {
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            if ((encoder[ch] == VIDEO_JPEG) && (snapshot[ch] == 0)) {
                // Enable continuous JPEG capture for MJPEG video
                cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 2);
            }
            if (snapshot[ch] == 1) {
                setSnapshotCallback(ch);
            }
            break;
        }
        case 3: { // for NN channel processing
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            cameraYUV(videoModule[ch]._p_mmf_context->priv);
            break;
        }
        default: {
            break;
        }
    }
}

void Video::channelEnd(int ch) {
    if (ch > 3) {
        ch = 0;
    }
    cameraStopVideoStream(videoModule[ch]._p_mmf_context->priv, channel[ch]);
}

MMFModule Video::getStream(int ch) {
    if (ch > 3) {
        ch = 0;
    }
    return (videoModule[ch]);
}

void Video::setSnapshotCallback(int ch) {
    switch (ch) {
        case 0: {
            cameraSnapshotRegCB(videoModule[ch]._p_mmf_context, &snapshotCB0);
            break;
        }
        case 1: {
            cameraSnapshotRegCB(videoModule[ch]._p_mmf_context, &snapshotCB1);
            break;
        }
        case 2: {
            cameraSnapshotRegCB(videoModule[ch]._p_mmf_context, &snapshotCB2);
            break;
        }
        case 3: {
            cameraSnapshotRegCB(videoModule[ch]._p_mmf_context, &snapshotCB3);
            break;
        }
    }
}

int Video::snapshotCB0(uint32_t jpeg_addr, uint32_t jpeg_len) {
    image_addr[0] = jpeg_addr;
    image_len[0] = jpeg_len;
    //printf("snapshot 0 addr=%X, size=%d", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

int Video::snapshotCB1(uint32_t jpeg_addr, uint32_t jpeg_len) {
    image_addr[1] = jpeg_addr;
    image_len[1] = jpeg_len;
    //printf("snapshot 1 addr=%X, size=%d", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

int Video::snapshotCB2(uint32_t jpeg_addr, uint32_t jpeg_len) {
    image_addr[2] = jpeg_addr;
    image_len[2] = jpeg_len;
    //printf("snapshot 2 addr=%X, size=%d", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

int Video::snapshotCB3(uint32_t jpeg_addr, uint32_t jpeg_len) {
    image_addr[3] = jpeg_addr;
    image_len[3] = jpeg_len;
    //printf("snapshot 3 addr=%X, size=%d", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

void Video::getImage(int ch, uint32_t* addr, uint32_t* len) {
    if (snapshot[ch] == 1) {
        //printf("Taking snapshot channel = %d\r\n", ch);
        image_addr[ch] = 0;
        image_len[ch] = 0;
        cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 1); // 1 does not represent ch, it represents mode
        while ((image_addr[ch] == 0) || (image_len[ch] == 0)) {
            //wait for jpeg data to arrive
            //printf("wait for jpeg data......\r\n");
            delay(10);
        }
        *addr = image_addr[ch];
        *len = image_len[ch];
//        printSnapshotInfo();
    } else {
        //printf("Snapshot disabled\r\n");
        *addr = (uint32_t)NULL;
        *len = (uint32_t)NULL;
    }
}

void Video::setFPS(int fps) {
    video_set_framerate(fps);
}

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