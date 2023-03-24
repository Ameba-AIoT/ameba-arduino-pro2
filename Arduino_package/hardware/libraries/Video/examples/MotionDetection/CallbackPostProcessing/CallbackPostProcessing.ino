/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-video-motion/

 For recommended setting to achieve better video quality, please refer to our Ameba FAQ: https://forum.amebaiot.com/t/ameba-faq/1220
 */

#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

#define CHANNEL 0       // High resolution video channel for streaming
#define CHANNELMD 3     // RGB format video for motion detection only avaliable on channel 3

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);      // High resolution video for streaming
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);     // Low resolution RGB video for motion detection
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD;

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;

void mdPostProcess(md_result_t* md_result) {
    // Motion detection results is expressed as an array
    // With 0 or 1 in each element indicating presence of motion
    // Iterate through all elements to check for motion
    // and calculate rectangles containing motion

    for (int i = 0; i < 4; i++) {
        OSD.createBitmap(CHANNEL, i);
        if (i < md_result->motion_cnt) {
            int xmin = (int)(md_result->md_pos[i].xmin * config.width());
            int ymin = (int)(md_result->md_pos[i].ymin * config.height());
            int xmax = (int)(md_result->md_pos[i].xmax * config.width());
            int ymax = (int)(md_result->md_pos[i].ymax * config.height());
            //printf("%d: x(%d,%d), y(%d,%d)\r\n",i,xmin,xmax,ymin,ymax);
            OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, COLOR_GREEN, i);
        }
        OSD.update(CHANNEL, i);
    }
}

void setup() {
    Serial.begin(115200);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure camera video channels for required resolutions and format outputs
    // Adjust the bitrate based on your WiFi network quality
    //config.setBitrate(2 * 1024 * 1024);     // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(CHANNELMD, configMD);
    Camera.videoInit();

    // Configure RTSP for high resolution video stream information
    rtsp.configVideo(config);
    rtsp.begin();

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configMD);
    MD.setResultCallback(mdPostProcess);
    MD.begin();

    // Configure StreamIO object to stream data from high res video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from high resolution video channel
    Camera.channelBegin(CHANNEL);
    Serial.println("Video RTSP Streaming Start");

    // Configure StreamIO object to stream data from low res video channel to motion detection
    videoStreamerMD.registerInput(Camera.getStream(CHANNELMD));
    videoStreamerMD.setStackSize();
    videoStreamerMD.registerOutput(MD);
    if (videoStreamerMD.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from low resolution video channel
    Camera.channelBegin(CHANNELMD);

    // Configure OSD for drawing on high resolution video stream
    OSD.configVideo(CHANNEL, config);
    OSD.begin();
}

void loop() {
    // Do nothing
}
