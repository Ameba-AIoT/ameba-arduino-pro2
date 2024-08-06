#ifndef __UVCD_H__
#define __UVCD_H__

#include <Arduino.h>
#include "VideoStream.h"

#include "module_uvcd.h"

#include "UVCD_pram.h"

class UVCD: public MMFModule {
public:
    UVCD(void);
    UVCD(const char *usb_uvcd_driver_name);
    ~UVCD(void);
    void configVideo(VideoSetting &config);
    void begin(const MMFModule &module_videocam, void *module_videolinker, int uvcd_channel);

private:
    unsigned char _uuid[16] = {0xc7, 0x98, 0x2c, 0x28, 0x0a, 0xfc, 0x49, 0xe6, 0xaa, 0xe4, 0x7f, 0x8f, 0x64, 0xee, 0x65, 0x01};
    int _uvcd_channel = 0;
};
#endif
