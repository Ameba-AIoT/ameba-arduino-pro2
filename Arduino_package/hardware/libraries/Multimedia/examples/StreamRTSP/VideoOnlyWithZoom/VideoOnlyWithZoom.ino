/*
 Example guide:
 TBC
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "VideoStreamOverlay.h"

#define CHANNEL 0

// 0: SCALE_DOWN_MODE, 1: SCALE_UP_MODE
#define DYN_ZOOM_MODE SCALE_UP_MODE

VideoSetting config(CHANNEL);
RTSP rtsp;
StreamIO videoStreamer(1, 1);

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

IPAddress ip;
int rtsp_portnum;
int maxWidth, maxHeight, minWidth, minHeight;
int xmin, ymin, xmax, ymax;

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
    ip = WiFi.localIP();

    // setup roi max, min width
    maxWidth = (Camera.getSensorWidth() & ~15);         // align 16
    maxHeight = (Camera.getSensorHeight() & ~3);        // align 4
    minWidth = (Camera.getSensorWidth() / 2 & ~15);     // align 16
    minHeight = (Camera.getSensorHeight() / 2 & ~3);    // align 4

    int newWidth = (maxWidth + minWidth) / 2 & ~15;      // align 16
    int newHeight = (maxHeight + minHeight) / 2 & ~3;    // align 4

    config.setWidth(newWidth);
    config.setHeight(newHeight);
    config.enableROI(newWidth, newHeight);

    // Configure camera video channels with video format information
    // Adjust the bitrate based on your WiFi network quality
    config.setBitrate(2 * 1024 * 1024);    // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    // Configure RTSP with corresponding video format information
    rtsp.configVideo(config);
    rtsp.begin();
    rtsp_portnum = rtsp.getPort();

    // Configure StreamIO object to stream data from video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start OSD drawing on RTSP video channel
    OSD.configVideo(CHANNEL, config);
    OSD.begin();

#if DYN_ZOOM_MODE == SCALE_DOWN_MODE
    Camera.setDynScaleDown(CHANNEL);
#else
    Camera.setDynScaleUp(CHANNEL);
#endif

    Camera.channelBegin(CHANNEL);
}

void loop()
{
#if DYN_ZOOM_MODE == SCALE_DOWN_MODE
    scaleDown();
#else
    scaleUp();
#endif
}

void showOSDZoomInfo(int ch, int input_w, int input_h)
{
    OSD.createBitmap(CHANNEL);
#if DYN_ZOOM_MODE == SCALE_DOWN_MODE
    char text_str[32] = "scale down";
#else
    char text_str[32] = "scale up";
#endif
    OSD.drawText(CHANNEL, 50, 50, text_str, OSD_COLOR_CYAN);
    snprintf(text_str, sizeof(text_str), "roi %dx%d", input_w, input_h);
    OSD.drawText(CHANNEL, 50, 100, text_str, OSD_COLOR_CYAN);
    OSD.update(CHANNEL);
    delay(500);
}

void scaleDown(void)
{
    isp_crop_t crop_info;
    const int steps = 20;

    for (int i = 0; i <= 2 * steps; i++) {
        int input_width, input_height;
        if (i <= steps) {
            // 1:1 -> scale down
            input_width = config.width() + (maxWidth - config.width()) * i / steps;
            input_height = config.height() + (maxHeight - config.height()) * i / steps;
        } else {
            // scale down -> 1:1
            input_width = maxWidth - (maxWidth - config.width()) * (i - steps) / steps;
            input_height = maxHeight - (maxHeight - config.height()) * (i - steps) / steps;
        }
        input_width = (input_width + 1) & ~1;      // force 2 aligned
        input_height = (input_height + 1) & ~1;    // force 2 aligned

        // set dynamic zoom to ch0
        Camera.crop_info_update(&crop_info, 0, 0, input_width, input_height);
        Camera.setROI(CHANNEL, &crop_info);
        printf("scale down %dx%d->%dx%d\n", input_width, input_height, config.width(), config.height());

        showOSDZoomInfo(CHANNEL, input_width, input_height);
    }
}

void scaleUp(void)
{
    isp_crop_t crop_info;
    const int steps = 20;

    for (int i = 0; i <= 2 * steps; i++) {
        int input_width, input_height;
        if (i <= steps) {
            // 1:1 -> scale up
            input_width = config.width() - (config.width() - minWidth) * i / steps;
            input_height = config.height() - (config.height() - minHeight) * i / steps;
        } else {
            // scale up -> 1:1
            input_width = minWidth + (config.width() - minWidth) * (i - steps) / steps;
            input_height = minHeight + (config.height() - minHeight) * (i - steps) / steps;
        }
        input_width = (input_width + 1) & ~1;      // force 2 aligned
        input_height = (input_height + 1) & ~1;    // force 2 aligned

        // set dynamic zoom to ch0
        Camera.crop_info_update(&crop_info, 0, 0, input_width, input_height);
        Camera.setROI(CHANNEL, &crop_info);
        printf("scale up %dx%d->%dx%d\n", input_width, input_height, config.width(), config.height());
        showOSDZoomInfo(CHANNEL, input_width, input_height);
    }
}
