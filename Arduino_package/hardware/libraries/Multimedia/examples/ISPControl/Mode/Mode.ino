/*
  Example guide: https://www.amebaiot.com/en/amebapro2-arduino-multimedia-isp-control/

  // "DAYNIGHT="  Set Day/Night Mode: 0: Day, 1: Night
  // "DAYNIGHT"   Get value of DayNight Mode to determine whether is day or night mode
  // "GRAY="      Set Gray Mode:  0: Color Mode, 1: Gray Mode
  // "GRAY"       Get value of Gray Mode to determine whether if it is gray mode
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

        if (input.startsWith(String("DAYNIGHT="))) {
            String value = input.substring(9);
            int val = value.toInt();
            configCam.setDayNightMode(val);
        } else if (input.startsWith(String("DAYNIGHT"))) {
            configCam.getDayNightMode();
        } else if (input.startsWith(String("GRAY="))) {
            String value = input.substring(5);
            int val = value.toInt();
            configCam.setGrayMode(val);
        } else if (input.startsWith(String("GRAY"))) {
            configCam.getGrayMode();
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
