/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-video-mp4/

 For recommended setting to achieve better video quality, please refer to our Ameba FAQ: https://forum.amebaiot.com/t/ameba-faq/1220
 */

#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

VideoSetting configV(CHANNEL);
AudioSetting configA(0);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer(1, 1);  // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);  // 2 Input Video + Audio -> 1 Output MP4

void setup() {
    Serial.begin(115200);

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, configV);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(configV);
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingAudioVideo");

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixStreamer.registerInput1(Camera.getStream(CHANNEL));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput(mp4);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);
    // Start recording MP4 data to SD card
    mp4.begin();

    // Print information
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
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}
