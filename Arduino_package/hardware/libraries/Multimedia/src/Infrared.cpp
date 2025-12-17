#include <Arduino.h>
#include "Infrared.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sensor_service.h"

#ifdef __cplusplus
}
#endif


Infrared::Infrared(void)
{
}

Infrared::~Infrared(void)
{
}


void Infrared::cutInit(void)
{
    ir_cut_init(NULL);
    return;
}

void Infrared::setCut(int value)
{
    ir_cut_enable(value);
    ir_cut_value = value;
    return;
}

int Infrared::getCut(void)
{
    return ir_cut_value;
}

void Infrared::ledInit(void)
{
    ir_ctrl_init(NULL);
    return;
}
void Infrared::setLedBrightness(int value)
{
    ir_ctrl_set_brightness_d(value);
    ir_led_brightness = value;
    return;
}
int Infrared::getLedBrightness(void)
{
    return ir_led_brightness;
}
