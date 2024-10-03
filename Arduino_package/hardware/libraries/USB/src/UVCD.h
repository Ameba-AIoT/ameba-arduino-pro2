#ifndef __UVCD_H__
#define __UVCD_H__

#include <Arduino.h>
#include "VideoStream.h"

#include "module_uvcd.h"

#include "UVCD_pram.h"

#include "video_drv.h"

class UVCD: public MMFModule {
public:
    UVCD(void);
    UVCD(const char *usb_uvcd_driver_name);
    ~UVCD(void);
    void configVideo(VideoSetting &config);
    void begin(const MMFModule &module_videocam, void *module_videolinker, int uvcd_channel);
    void nnbegin(const MMFModule &module_videocam, void *module_videolinker, int uvcd_channel, int nn_channel);
    // void videoDeinit(void);
    // void videoDeinit(int ch);
    int isUsbUvcConnected(void);
    int get_usb_status();
private:
    // void setSnapshotCallback(int ch);
    // static int snapshotCB0(uint32_t jpeg_addr, uint32_t jpeg_len);
    // static int snapshotCB1(uint32_t jpeg_addr, uint32_t jpeg_len);
    // static int snapshotCB2(uint32_t jpeg_addr, uint32_t jpeg_len);
    // static int snapshotCB3(uint32_t jpeg_addr, uint32_t jpeg_len);
    unsigned char _uuid[16] = {0xc7, 0x98, 0x2c, 0x28, 0x0a, 0xfc, 0x49, 0xe6, 0xaa, 0xe4, 0x7f, 0x8f, 0x64, 0xee, 0x65, 0x01};
    int _uvcd_channel = 0;
    int _nn_channel = 3;
    // MMFModule videoModule[4];
    // int channel[4] = {v1_STREAMING_ID, v2_STREAMING_ID, v3_STREAMING_ID, v4_STREAMING_ID};
    // uint8_t snapshot[3][5] = {
    //     {0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0}
    // };
    // uint8_t encoder[4] = {0};
};
#endif
