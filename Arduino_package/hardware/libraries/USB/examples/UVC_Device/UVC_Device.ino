/*
 * This example describes how to use USB UVCD api.
 * In this example, the device is setup to function as a USB camera.
 * Connect to PC and use the device as a USB camera.

 * Example guide: https://www.amebaiot.com/en/amebapro2-arduino-usb-uvc/
 */

#include "StreamIO.h"
#include "VideoStream.h"
#include "UVCD.h"

#define STREAM_CHANNEL 0

VideoSetting stream_config(USB_UVCD_STREAM_PRESET);
Video camera_uvcd;

UVCD usb_uvcd;

StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output USB_CAM

void setup()
{
    Serial.begin(115200);

    // Configure camera video channel with video format information
    camera_uvcd.configVideoChannel(STREAM_CHANNEL, stream_config);
    camera_uvcd.videoInit(STREAM_CHANNEL);

    // Configure usb_uvcd with identical video format information
    usb_uvcd.configVideo(stream_config);

    // Configure StreamIO object to stream data from camera video channel to usb_uvcd
    videoStreamer.registerInput(camera_uvcd.getStream(STREAM_CHANNEL));
    videoStreamer.registerOutput(usb_uvcd);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    camera_uvcd.channelBegin(STREAM_CHANNEL);

    // Start usb uvcd
    usb_uvcd.begin(camera_uvcd.getStream(STREAM_CHANNEL), videoStreamer.linker, STREAM_CHANNEL);
}

void loop()
{
    delay(1000);
}
