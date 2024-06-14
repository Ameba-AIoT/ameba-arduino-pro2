/*
 This sketch shows how to use the camera JXF37 on the AMB82-Mini to scan for QR Code and get the result string and length.

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-qrcode/
 */

#undef DEFAULT

#include "VideoStream.h"
#include "QRCodeScanner.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

VideoSetting config(CHANNEL);
QRCodeScanner Scanner;

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);
    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    Scanner.StartScanning();
}

void loop()
{
    // User can use the result string and length from here.
    // You can modify the delay to the rate of retrieving the result string and result length.
    // Currently, third successful scan will allow you to get the result string and length reliably.
    // Note that this loop may not be optimised, you are to do your own conditional checks to get your application working.
    // This is to illustrate how to retrieve the qr code scanning results.

    delay(1000);
    Scanner.GetResultString();
    Scanner.GetResultLength();
    if (Scanner.ResultString != nullptr) {
        Serial.print("Result String is:");
        Serial.println(Scanner.ResultString);
    }
    if (Scanner.ResultLength != 0) {
        Serial.print("Result Length is:");
        Serial.println(Scanner.ResultLength);
    }
}
