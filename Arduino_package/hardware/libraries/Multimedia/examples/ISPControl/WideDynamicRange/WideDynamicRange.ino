/*
  Example guide: https://www.amebaiot.com/en/amebapro2-arduino-multimedia-isp-control/

  // "WDR="       Set Wide Dynamic Range, 0: Disabled, 1: Manual, 2: Auto
  // "WDR"        Get value of WDR
  // "LEVEL="     Set WDR level: Range from 50 to 100
  // "LEVEL"      Get WDR level
  // "RESET"      Reset to default
*/

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1280 x 720  30FPS MJPEG
CameraSetting configCam;
VideoSetting config(CHANNEL);
RTSP rtsp;
StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output RTSP

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure camera video channel with video format information
    // Adjust the bitrate based on your WiFi network quality
    // config.setBitrate(2 * 1024 * 1024);     // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    // Configure RTSP with identical video format information
    rtsp.configVideo(config);
    rtsp.begin();

    // Configure StreamIO object to stream data from video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);

    delay(1000);
    printInfo();
}

void loop()
{
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();

        if (input.startsWith(String("WDR="))) {
            String value = input.substring(4);
            int val = value.toInt();
            configCam.setWDR(val);
        } else if (input.startsWith(String("WDR"))) {
            configCam.getWDR();
        } else if (input.startsWith(String("LEVEL="))) {    // Preferred Wide Dynamic Range level take effect only if WDR is set to Manual
            String value = input.substring(6);
            int val = value.toInt();
            configCam.setWDRLevel(val);
        } else if (input.startsWith(String("LEVEL"))) {
            configCam.getWDRLevel();
        } else if (input.startsWith(String("RESET"))) {
            configCam.reset();
        }
    }
}

void printInfo(void)
{
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP -");
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp.printInfo();
}
