/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-motion/
 */

#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

#define CHANNEL   0    // High resolution video channel for streaming
#define CHANNELMD 3    // RGB format video for motion detection only available on channel 3

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);     // High resolution video for streaming
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);    // Low resolution RGB video for motion detection
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD;

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

void mdPostProcess(std::vector<MotionDetectionResult> md_results)
{
    // Motion detection results is expressed as an array
    // With 0 or 1 in each element indicating presence of motion
    // Iterate through all elements to check for motion
    // and calculate rectangles containing motion

    OSD.createBitmap(CHANNEL);
    if (MD.getResultCount() > 0) {
        for (uint16_t i = 0; i < MD.getResultCount(); i++) {
            MotionDetectionResult result = md_results[i];
            int xmin = (int)(result.xMin() * config.width());
            int xmax = (int)(result.xMax() * config.width());
            int ymin = (int)(result.yMin() * config.height());
            int ymax = (int)(result.yMax() * config.height());
            // printf("%d:\t%d %d %d %d\n\r", i, xmin, xmax, ymin, ymax);
            OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, COLOR_GREEN);
        }
    }
    OSD.update(CHANNEL);
}

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

    // Configure camera video channels for required resolutions and format outputs
    // Adjust the bitrate based on your WiFi network quality
    // config.setBitrate(2 * 1024 * 1024);     // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
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

void loop()
{
    // Do nothing
}
