/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-video-mp4/

 For recommended setting to achieve better video quality, please refer to our Ameba FAQ: https://forum.amebaiot.com/t/ameba-faq/1220
 */

#include "StreamIO.h"
#include "VideoStream.h"
#include "MP4Recording.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

VideoSetting config(CHANNEL);
MP4Recording mp4;
StreamIO videoStreamer(1, 1);  // 1 Input Video -> 1 Output RTSP

void setup() {
    Serial.begin(115200);

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(config);
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingVideoOnly");
    mp4.setRecordingDataType(STORAGE_VIDEO);    // Set MP4 to record video only

    // Configure StreamIO object to stream data from video channel to MP4 recording
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(mp4);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);
    // Start recording MP4 data to SD card
    mp4.begin();

    delay(1000);
    printInfo();
}

void loop() {
    // do nothing
}

void printInfo(void) {
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}
