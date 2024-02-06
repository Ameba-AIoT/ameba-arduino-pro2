/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-rtsp/
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

VideoSetting config(CHANNEL);
RTSP rtsp1;
RTSP rtsp2;
StreamIO videoStreamer(1, 2);    // 1 Input Video -> 2 Output RTSP1 + RTSP2

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

    // Configure both RTSP with identical video format information
    rtsp1.configVideo(config);
    rtsp1.begin();
    rtsp2.configVideo(config);
    rtsp2.begin();

    // Configure StreamIO object to stream data from video channel to both rtsp outputs
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput1(rtsp1);
    videoStreamer.registerOutput2(rtsp2);
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
    // Do nothing
}

void printInfo(void)
{
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");

    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP Information -");
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp1.printInfo();

    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp2.printInfo();
}
