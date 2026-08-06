#include "UVCH.h"

#define USBH_UVC_FORMAT_TYPE UVC_FORMAT_MJPEG
#define USBH_UVC_WIDTH       1280
#define USBH_UVC_HEIGHT      720
#define USBH_UVC_FRAME_RATE  15

UVCH uvc (USBH_UVC_WIDTH, USBH_UVC_HEIGHT, USBH_UVC_FRAME_RATE, USBH_UVC_FORMAT_TYPE);

void setup()
{
    Serial.begin(115200);
    delay(2000);

    printf("Starting UVC camera test\n");
    uvc.initUSB();
    uvc.initUVC();
    uvc.initSD();
    uvc.startStream();
}

void loop()
{
    uvc.captureFrameStart();
}
