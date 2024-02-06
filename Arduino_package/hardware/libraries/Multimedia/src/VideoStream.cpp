#include <Arduino.h>
#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "video_drv.h"
#include "isp_ctrl_api.h"

#ifdef __cplusplus
}
#endif

Video Camera;

uint32_t Video::image_addr[4] = {0};
uint32_t Video::image_len[4] = {0};

// (Image Tuning)
void CameraSetting::setBrightness(int value)
{
    if (value >= BRIGHTNESS_MIN && value <= BRIGHTNESS_MAX) {
        isp_set_brightness(value);
        printf("\r\n[INFO] Brightness is set to %d.\n", value);
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getBrightness(void)
{
    isp_get_brightness(&ret);
    printf("\r\n[INFO] Brightness = %d\n", ret);
}

void CameraSetting::setContrast(int value)
{
    if (value >= CONTRAST_MIN && value <= CONTRAST_MAX) {
        isp_set_contrast(value);
        printf("\r\n[INFO] Contrast is set to %d.\n", value);
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getContrast(void)
{
    isp_get_contrast(&ret);
    printf("\r\n[INFO] Contrast = %d \n", ret);
}

void CameraSetting::setSaturation(int value)
{
    if (value >= SATURATION_MIN && value <= SATURATION_MAX) {
        isp_set_saturation(value);
        printf("\r\n[INFO] Saturation is set to %d.\n", value);
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getSaturation(void)
{
    isp_get_saturation(&ret);
    printf("\r\n[INFO] Saturation = %d\n", ret);
}

void CameraSetting::setSharpness(int value)
{
    if (value >= SHARPNESS_MIN && value <= SHARPNESS_MAX) {
        isp_set_sharpness(value);
        printf("\r\n[INFO] Sharpness is set to %d.\n", value);
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getSharpness(void)
{
    isp_get_sharpness(&ret);
    printf("\r\n[INFO] Sharpness = %d \n", ret);
}

// Len Distortion Correction
void CameraSetting::setLDC(int enable)
{
    isp_set_ldc(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Len Distortion Correction is Disabled.\n");
    } else if (enable == 1) {
        printf("[INFO] Len Distortion Correction is Enabled.\n");
    } else {
        printf("\r\n[ERROR] Invalid Input. \n");
    }
}

void CameraSetting::getLDC(void)
{
    isp_get_ldc(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Len Distortion Correction is Disabled.\n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Len Distortion Correction is Enabled.\n");
    }
}

// Wide Dynamic Range
void CameraSetting::setWDR(int enable)
{
    isp_set_wdr_mode(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Wide Dynamic Range is Disabled.\n");
    } else if (enable == 1) {
        printf("\r\n[INFO] Wide Dynamic Range is set to Manual.\n");
    } else if (enable == 2) {
        printf("\r\n[INFO] Wide Dynamic Range is set to Auto.\n");
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getWDR(void)
{
    isp_get_wdr_mode(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Wide Dynamic Range = Disabled \n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Wide Dynamic Range = Manual \n");
    } else if (ret == 2) {
        printf("\r\n[INFO] Wide Dynamic Range = Auto \n");
    }
}

void CameraSetting::setWDRLevel(int value)
{
    getWDR();
    if (ret == 1) {
        if (value >= 50 && value <= 100) {
            isp_set_wdr_level(value);
            printf("\r\n[INFO] WDR level is set to %d.\n", value);
        } else {
            printf("\r\n[INFO] Invalid value. WDR level value should be between 50 to 100.\n");
        }
    } else {
        printf("\r\n[ERROR] Please set WDR to Manual to set the WDR level manually.\n");
    }
}

void CameraSetting::getWDRLevel(void)
{
    isp_get_wdr_level(&ret);
    printf("\r\n[INFO] WDR level = %d\n", ret);
}

// AE (Auto Exposure)
void CameraSetting::setExposureMode(int enable)
{
    isp_set_exposure_mode(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Exposure Mode is set to Manual.\n");
    } else if (enable == 1) {
        printf("\r\n[INFO] Exposure Mode is set to Auto.\n");
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getExposureMode(void)
{
    isp_get_exposure_mode(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Exposure Mode = Manual\n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Exposure Mode = Auto\n");
    }
}

void CameraSetting::setExposureTime(int time)
{    // duration in us
    getExposureMode();
    if (ret == 0) {
        if (time <= EXPOSURETIME_MAX) {
            isp_set_exposure_time(time);
            printf("\r\n[INFO] Exposure time is set to %dus.\n", time);
        } else {
            printf("\r\n[ERROR] Exposure Time should be less than or equals to 33333us.\n");
        }
    } else {
        printf("\r\n[ERROR] Please set Exposure Mode to Manual to set the Exposure Time manually.\n");
    }
}

void CameraSetting::getExposureTime(void)
{    // duration in us
    isp_get_exposure_time(&ret);
    printf("\r\n[INFO] Exposure time = %dus\n", ret);
}

void CameraSetting::setAEGain(int value)
{
    getExposureMode();
    if (ret == 0) {
        if (value >= AEGAIN_MIN && value <= AEGAIN_MAX) {
            isp_set_ae_gain(value);
            printf("\r\n[INFO] AE Gain is set to %d.\n", value);
        } else {
            printf("\r\n[ERROR] Invalid Input.\n");
        }
    } else if (ret == 1) {
        printf("\r\n[ERROR] Please set Exposure Mode to Manual to set the AE Gain manually.\n");
    }
}

void CameraSetting::getAEGain(void)
{
    isp_get_ae_gain(&ret);
    printf("\r\n[INFO] AE Gain = %d\n", ret);
}

void CameraSetting::setPowerLineFreq(int enable)
{
    isp_set_power_line_freq(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Power Line Frequency is disabled.\n");
    } else if (enable == 1) {
        printf("\r\n[INFO] Power Line Frequency is 50Hz.\n");
    } else if (enable == 2) {
        printf("\r\n[INFO] Power Line Frequency is 60Hz.\n");
    } else if (enable == 3) {
        printf("\r\n[INFO] Power Line Frequency is Auto.\n");
    }
}

void CameraSetting::getPowerLineFreq(void)
{
    isp_get_power_line_freq(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Power Line Frequency = disabled.\n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Power Line Frequency = 50Hz.\n");
    } else if (ret == 2) {
        printf("\r\n[INFO] Power Line Frequency = 60Hz.\n");
    } else if (ret == 3) {
        printf("\r\n[INFO] Power Line Frequency = Auto.\n");
    }
}

// AWB (Auto White Balance)
void CameraSetting::setAWB(int enable)
{
    isp_set_awb_ctrl(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Auto White Balance is set to Manual.\n");
    } else if (enable == 1) {
        printf("\r\n[INFO] Auto White Balance is set to Auto.\n");
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getAWB(void)
{
    isp_get_awb_ctrl(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Auto White Balance = Manual.\n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Auto White Balance = Auto.\n");
    }
}

void CameraSetting::getWBTemp(void)
{
    isp_get_wb_temperature(&ret);
    printf("\r\n[INFO] White Balance Temperature = %d\n", ret);
}

void CameraSetting::setRedBalance(int value)
{
    getAWB();
    if (ret == 0) {
        if (value >= REDBALANCE_MIN && value <= REDBALANCE_MAX) {
            isp_set_red_balance(value);
            printf("\r\n[INFO] Red balance is set to %d.\n", value);
        } else {
            printf("\r\n[ERROR] Invalid Input.\n");
        }
    } else {
        printf("\r\n[ERROR] Please set AWB to Manual to adjust the temperature manually.\n");
    }
}

void CameraSetting::getRedBalance(void)
{
    isp_get_red_balance(&ret);
    printf("\r\n[INFO] Red balance = %d\n", ret);
}

void CameraSetting::setBlueBalance(int value)
{
    getAWB();
    if (ret == 0) {
        if (value >= BLUEBALANCE_MIN && value <= BLUEBALANCE_MAX) {
            isp_set_blue_balance(value);
            printf("\r\n[INFO] Blue balance is set to %d.\n", value);
        } else {
            printf("\r\n[ERROR] Invalid Input.\n");
        }
    } else if (ret == 1) {
        printf("\r\n[ERROR] Please set AWB to Manual to adjust the temperature manually.\n");
    }
}

void CameraSetting::getBlueBalance(void)
{
    isp_get_blue_balance(&ret);
    printf("\r\n[INFO] Blue balance = %d\n", ret);
}

// Mode
void CameraSetting::setGrayMode(int enable)
{
    isp_set_gray_mode(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Not Gray Mode\n");
    } else if (enable == 1) {
        printf("\r\n[INFO] Gray Mode\n");
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getGrayMode(void)
{
    isp_get_gray_mode(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Not Gray Mode\n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Gray Mode\n");
    }
}

void CameraSetting::setDayNightMode(int enable)
{
    isp_set_day_night(enable);
    if (enable == 0) {
        printf("\r\n[INFO] Day Mode\n");
    } else if (enable == 1) {
        printf("\r\n[INFO] Night Mode\n");
    } else {
        printf("\r\n[ERROR] Invalid Input.\n");
    }
}

void CameraSetting::getDayNightMode(void)
{
    isp_get_day_night(&ret);
    if (ret == 0) {
        printf("\r\n[INFO] Day Mode\n");
    } else if (ret == 1) {
        printf("\r\n[INFO] Night Mode\n");
    }
}

void CameraSetting::reset(void)
{
    ISPControlReset();
    printf("\r\n[INFO] ISP Control Reset.\n");
}

VideoSetting::VideoSetting(uint8_t preset)
{
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
            printf("\r\n[ERROR] Invalid VideoSetting preset!\n");
            return;
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

VideoSetting::VideoSetting(uint8_t resolution, uint8_t fps, uint8_t encoder, uint8_t snapshot)
{
    _resolution = resolution;
    _fps = fps;
    _bps = CAM_BPS;
    _encoder = encoder;
    _snapshot = snapshot;
    _jpeg_qlevel = 5;

    if ((_snapshot == 1)) {
        if ((_encoder != VIDEO_H264_JPEG) && (_encoder != VIDEO_HEVC_JPEG) && (_encoder != VIDEO_JPEG)) {
            printf("\r\n[ERROR] snapshot function not supported on selected encoder!\n");
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
    } else if (_resolution == VIDEO_D1) {
        _w = VIDEO_D1_WIDTH;
        _h = VIDEO_D1_HEIGHT;
    }
}

VideoSetting::VideoSetting(uint16_t w, uint16_t h, uint8_t fps, uint8_t encoder, uint8_t snapshot)
{
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
        printf("\r\n[INFO] Maximum resolution 1920 x 1080 \n");
    }
    if (_h > 1080) {
        _h = 1080;
        printf("\r\n[INFO] Maximum resolution 1920 x 1080 \n");
    }

    // Check resolution minimums
    if (encoder == VIDEO_JPEG) {
        _jpeg_qlevel = 2;

        if (_w < 352) {
            _w = 352;
            printf("\r\n[INFO] Minimum JPEG resolution 352 x 288 \n");
        }
        if (_h < 288) {
            _h = 288;
            printf("\r\n[INFO] Minimum JPEG resolution 352 x 288 \n");
        }
    } else {
        if (_w < 176) {
            _w = 176;
            printf("\r\n[INFO] Minimum resolution 176 x 144 \n");
        }
        if (_h < 144) {
            _h = 144;
            printf("\r\n[INFO] Minimum resolution 176 x 144 \n");
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
        printf("\r\n[INFO] Custom resolution must be a multiple of 16, new resolution: %d X %d\n", _w, _h);
    }
    if (((_h % 16) != 0) && (_h != 360) && (_h != 1080)) {
        _h -= (_h % 16);
        if ((_h + 16) <= 1080) {
            _h += 16;
        }
        printf("\r\n[INFO] Custom resolution must be a multiple of 16, new resolution: %d X %d\n", _w, _h);
    }

    if ((_snapshot == 1)) {
        if ((_encoder != VIDEO_H264_JPEG) && (_encoder != VIDEO_HEVC_JPEG) && (_encoder != VIDEO_JPEG)) {
            printf("\r\n[ERROR] snapshot function not supported on selected encoder!\n");
            _snapshot = 0;
        }
    }
}

void VideoSetting::setBitrate(uint32_t bitrate)
{
    if (bitrate < (1 * 1024 * 1024)) {
        bitrate = (1 * 1024 * 1024);
    }
    if (bitrate > (50 * 1024 * 1024)) {
        bitrate = (50 * 1024 * 1024);
    }
    _bps = bitrate;
}

void VideoSetting::setJpegQuality(uint8_t quality)
{
    if (quality < 1) {
        quality = 1;
    }
    if (quality > 9) {
        quality = 9;
    }
    _jpeg_qlevel = quality;
}

// 0 (default): 0 degree
// 1: 90 degree (Rotate Right)
// 2: 90 degree (Rotate Left)
// 3: 180 degree
void VideoSetting::setRotation(int angle)
{
    _rotation = angle;
}

uint16_t VideoSetting::width(void)
{
    return _w;
}

uint16_t VideoSetting::height(void)
{
    return _h;
}

uint16_t VideoSetting::fps(void)
{
    return _fps;
}

void Video::configVideoChannel(int ch, VideoSetting& config)
{
    // Copy in video stream settings for specified stream channel
    channelEnable[ch] = 1;
    resolution[ch] = config._resolution;
    w[ch] = config._w;
    h[ch] = config._h;
    fps[ch] = config._fps;
    bps[ch] = config._bps;
    encoder[ch] = config._encoder;
    snapshot[ch] = config._snapshot;
    jpeg_qlevel[ch] = config._jpeg_qlevel;
    video_rotation[ch] = config._rotation;

    // Video stream using VIDEO_JPEG requires setting bps = 0
    // if (encoder[ch] == VIDEO_JPEG) {
    //     bps[ch] = 0;
    // }

    // printf("\r\n[INFO] V1 %d    %d    %d    %d    %d    %d\n", channelEnable[0], w[0], h[0], bps[0], snapshot[0], fps[0]);
    // printf("\r\n[INFO] V2 %d    %d    %d    %d    %d    %d\n", channelEnable[1], w[1], h[1], bps[1], snapshot[1], fps[1]);
    // printf("\r\n[INFO] V3 %d    %d    %d    %d    %d    %d\n", channelEnable[2], w[2], h[2], bps[2], snapshot[2], fps[2]);
    // printf("\r\n[INFO] V4 %d    %d    %d    %d    %d    %d\n", channelEnable[3], w[3], h[3]);
}

void Video::camInit(CameraSetting& config)
{
    // To be done
}

void Video::camDeinit(void)
{
    // To be done
}

void Video::videoInit(void)
{
    int heapSize = cameraConfig(channelEnable[0], w[0], h[0], bps[0], snapshot[0],
                                channelEnable[1], w[1], h[1], bps[1], snapshot[1],
                                channelEnable[2], w[2], h[2], bps[2], snapshot[2],
                                channelEnable[3], w[3], h[3]);
    (void)heapSize;
    // printf("\r\n[INFO] %s VOE heap size is: %d\n", __FUNCTION__, heapSize);

    for (int ch = 0; ch < 4; ch++) {
        if (channelEnable[ch]) {
            // printf("\r\n[INFO] %d  %d    %d    %d    %d    %d    %d    %d\n", ch, resolution[ch], channelEnable[ch], w[ch], h[ch], bps[ch], encoder[ch], fps[ch]);
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
                           jpeg_qlevel[ch],
                           video_rotation[ch]);
            } else if (ch == 3) {
                // printf("\r\n[INFO] V4 %d    %d    %d    %d\n", resolution[3], channelEnable[3], w[3], h[3]);
                bps[3] = 1 * 1024 * 1024;
                cameraOpenNN(videoModule[3]._p_mmf_context, videoModule[3]._p_mmf_context->priv,
                             channel[3],
                             encoder[3],
                             resolution[3],
                             w[3],
                             h[3],
                             bps[3],
                             CAM_NN_FPS,
                             CAM_NN_GOP,
                             0);    // direct output flag
            } else {
                // printf("\r\n[INFO] %d  %d    %d    %d    %d    %d    %d    %d\n", ch, resolution[ch], channelEnable[ch], w[ch], h[ch], bps[ch], encoder[ch], fps[ch]);
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
                           jpeg_qlevel[ch],
                           video_rotation[ch]);
            }
        }
    }
}

void Video::videoDeinit(void)
{
    uint8_t i;
    for (i = 0; i < 4; i++) {
        if (videoModule[i]._p_mmf_context != NULL) {
            cameraDeinit(videoModule[i]._p_mmf_context);
        }
    }
}

void Video::channelBegin(int ch)
{
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
        case 3: {    // for NN channel processing
            cameraStart(videoModule[ch]._p_mmf_context->priv, channel[ch]);
            cameraYUV(videoModule[ch]._p_mmf_context->priv);
            break;
        }
        default: {
            break;
        }
    }
}

void Video::channelEnd(int ch)
{
    if (ch > 3) {
        ch = 0;
    }
    cameraStopVideoStream(videoModule[ch]._p_mmf_context->priv, channel[ch]);
}

MMFModule Video::getStream(int ch)
{
    if (ch > 3) {
        ch = 0;
    }
    return (videoModule[ch]);
}

void Video::setSnapshotCallback(int ch)
{
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

int Video::snapshotCB0(uint32_t jpeg_addr, uint32_t jpeg_len)
{
    image_addr[0] = jpeg_addr;
    image_len[0] = jpeg_len;
    // printf("\r\n[INFO] snapshot 0 addr=%X, size=%d\n", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

int Video::snapshotCB1(uint32_t jpeg_addr, uint32_t jpeg_len)
{
    image_addr[1] = jpeg_addr;
    image_len[1] = jpeg_len;
    // printf("\r\n[INFO] snapshot 1 addr=%X, size=%d\n", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

int Video::snapshotCB2(uint32_t jpeg_addr, uint32_t jpeg_len)
{
    image_addr[2] = jpeg_addr;
    image_len[2] = jpeg_len;
    // printf("\r\n[INFO] snapshot 2 addr=%X, size=%d\n", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

int Video::snapshotCB3(uint32_t jpeg_addr, uint32_t jpeg_len)
{
    image_addr[3] = jpeg_addr;
    image_len[3] = jpeg_len;
    // printf("\r\n[INFO] snapshot 3 addr=%X, size=%d\n", (int)jpeg_addr, (int)jpeg_len);
    return 0;
}

void Video::getImage(int ch, uint32_t* addr, uint32_t* len)
{
    if (snapshot[ch] == 1) {
        // printf("\r\n[INFO] Taking snapshot channel = %d\n", ch);
        image_addr[ch] = 0;
        image_len[ch] = 0;
        cameraSnapshot(videoModule[ch]._p_mmf_context->priv, 1);    // 1 does not represent ch, it represents mode
        while ((image_addr[ch] == 0) || (image_len[ch] == 0)) {
            // wait for jpeg data to arrive
            // printf("\r\n[INFO] wait for jpeg data......\n");
            delay(10);
        }
        *addr = image_addr[ch];
        *len = image_len[ch];
        // printSnapshotInfo();
    } else {
        // printf("\r\n[ERROR] Snapshot disabled\n");
        *addr = (uint32_t)NULL;
        *len = (uint32_t)NULL;
    }
}

void Video::setFPS(int fps)
{
    video_set_framerate(fps);
}

void Video::printInfo(void)
{
    for (int ch = 0; ch < 4; ch++) {
        if (channelEnable[ch] == 1) {
            printf("\r\n[INFO] Channel: %d\n", channel[ch]);
            printf("\r\n[INFO] Encoder type: %s\n", encoderArray[encoder[ch]].c_str());
            printf("\r\n[INFO] Resolution: %s\n", resolutionArray[resolution[ch]].c_str());
            printf("\r\n[INFO] Video width: %d\n", w[ch]);
            printf("\r\n[INFO] Video height: %d\n", h[ch]);
            printf("\r\n[INFO] fps: %d\n", fps[ch]);
            printf("\r\n[INFO] bps: %ld\n", bps[ch]);
        }
    }
}
