/*
 Example guide: https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/NightMode.html
*/



#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "Infrared.h"

#define CHANNEL 0
#define PWR_EN  9

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1280 x 720  30FPS MJPEG
VideoSetting config(CHANNEL);
Infrared ir;
RTSP rtsp;
CameraSetting configCam;
StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output RTSP

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    pinMode(PWR_EN, OUTPUT);
    digitalWrite(PWR_EN, HIGH);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Initialize the IR-cut filter and IR led
    // Disable IR-cut and turn on IR led to the maximum brightness
    ir.cutInit();                // Initializes GPIO Pin F12
    ir.ledInit();                // Initializes GPIO Pin F13
    ir.setCut(0);                // 0 to disable, 1 to enable
    ir.setLedBrightness(100);    // Brightness input can be from 0 to 100, [0,100]

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

    configCam.setGrayMode(1);        // 0 for RGB, 1 for Grayscale
    configCam.setDayNightMode(1);    // 0 for day mode ISP auto-tuning, 1 for night mode ISP auto-tuning

    printInfo();
}

void loop()
{
    // Do nothing
}

void printInfo(void)
{
    Serial.println(" ");
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP -");
    rtsp.printInfo(ip.get_address());
}
