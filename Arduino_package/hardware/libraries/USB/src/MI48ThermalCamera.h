#ifndef MI48_THERMAL_CAMERA_H
#define MI48_THERMAL_CAMERA_H
#include <stdint.h>
#include "VideoStream.h"

class MI48ThermalCamera: public MMFModule {

public:
    bool begin(uint16_t width, uint16_t height, uint8_t fps, uint8_t channel, uint32_t bps, uint32_t type, uint32_t resolution, uint32_t extFmt, bool useRainbow);
    bool start();
    bool poll();
    bool process();
    uint32_t frameCount();
    bool readTemperatures(float values[144]);
};
#endif
