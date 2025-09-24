/*
 Please adjust VideoSetting to get better video quality when streaming to V7RC APP:
     VideoSetting config(VIDEO_D1, CAM_FPS, VIDEO_H264, 0);

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/RTSP%20Streaming%20with%20OSD%20Image.html
*/

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "VideoStreamOverlay.h"
#include "osd_pict.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1280 x 720  30FPS MJPEG

VideoSetting config(CHANNEL);
RTSP rtsp;
StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output RTSP

unsigned char *osd_pic_0[MAX_OSD_CH_COUNT] = {NULL};
unsigned char *osd_pic_1[MAX_OSD_CH_COUNT] = {NULL};
osd_pict_st posd2_pic_0, posd2_pic_1;

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

    OSD.begin(config, CHANNEL);
    int resize_width_0 = OSD.resizeWidth(PIC0_WIDTH, 7, 6);       // width get from osd_pict.h
    int resize_height_0 = OSD.resizeHeight(PIC0_HEIGHT, 7, 6);    // height get from osd_pict.h
    unsigned int heapsize_0 = OSD.heapsizeCal(resize_width_0, resize_height_0, PIC0_BLK_FMT);

    int resize_width_1 = OSD.resizeWidth(PIC1_WIDTH, 7, 6);       // width get from osd_pict.h
    int resize_height_1 = OSD.resizeHeight(PIC1_HEIGHT, 7, 6);    // height get from osd_pict.h
    unsigned int heapsize_1 = OSD.heapsizeCal(resize_width_1, resize_height_1, PIC1_BLK_FMT);

    OSD.drawImage(CHANNEL, osd_pic_0, posd2_pic_0, heapsize_0, PIC0_NAME, PIC0_WIDTH, PIC0_HEIGHT, PIC0_BLK_FMT, resize_width_0, resize_height_0, 150, 200, 0);
    OSD.drawImage(CHANNEL, osd_pic_1, posd2_pic_1, heapsize_1, PIC1_NAME, PIC1_WIDTH, PIC1_HEIGHT, PIC1_BLK_FMT, resize_width_1, resize_height_1, 150 + resize_width_0 + 50, 200, 1);
    OSD.displayImage(CHANNEL);
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
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp.printInfo();
}
