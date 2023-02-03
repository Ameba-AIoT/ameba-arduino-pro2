/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-video-mp4/
 */

#include "StreamIO.h"
#include "AudioStream.h"
#include "VideoStream.h"
#include "MP4Recording.h"

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

VideoSetting configV1(0);
VideoSetting configV2(1);
Audio audio;
AAC aac;
MP4Recording mp4_1;
MP4Recording mp4_2;
StreamIO audioStreamer(1, 1);  // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(3, 2);  // 3 Input Video1 + Video2 + Audio -> 2 Output MP4_1 + MP4_2

void setup() {
    Serial.begin(115200);

    // Configure both camera video channels with corresponding video format information
    Camera.configVideoChannel(0, configV1);
    Camera.configVideoChannel(1, configV2);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.begin();
    // Configure AAC audio encoder
    aac.begin();

    // Configure MP4 with corresponding video format information
    // Configure MP4 recording settings
    mp4_1.configVideo(configV1);
    mp4_1.setRecordingDuration(15);
    mp4_1.setRecordingFileCount(1);
    mp4_1.setRecordingFileName("TestRecordingAudioVideo1");

    mp4_2.configVideo(configV2);
    mp4_2.setRecordingDuration(30);
    mp4_2.setRecordingFileCount(1);
    mp4_2.setRecordingFileName("TestRecordingAudioVideo2");

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channels and AAC encoder to MP4 outputs
    avMixStreamer.registerInput1(Camera.getStream(0));
    avMixStreamer.registerInput2(Camera.getStream(1));
    avMixStreamer.registerInput3(aac);
    avMixStreamer.registerOutput1(mp4_1);
    avMixStreamer.registerOutput2(mp4_2);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channels
    Camera.channelBegin(0);
    Camera.channelBegin(1);
    // Start recording MP4 data to SD card
    mp4_1.begin();
    mp4_2.begin();

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

    Serial.println("- Audio Information -");
    audio.printInfo();
    Serial.println("- AAC Information -");
    aac.printInfo();
    Serial.println("- MP4 Recording Information 1-");
    mp4_1.printInfo();
    Serial.println("- MP4 Recording Information 2-");
    mp4_2.printInfo();
}