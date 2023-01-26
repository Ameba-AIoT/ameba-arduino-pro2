/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-video-mp4/
 */

#include "StreamIO.h"
#include "AudioStream.h"
#include "MP4Recording.h"

#define CHANNEL 0

Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer1(1, 1);  // 1 Input Audio -> 1 Output AAC
StreamIO audioStreamer2(1, 1);  // 1 Input AAC -> 1 Output MP4

void setup() {
    Serial.begin(115200);

    // Configure audio peripheral for audio data output
    audio.begin();
    // Configure AAC audio encoder
    aac.begin();

    // Configure MP4 recording settings
    mp4.configAudio();
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingAudioOnly");
    mp4.setRecordingDataType(STORAGE_AUDIO);    // Set MP4 to record audio only

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer1.registerInput(audio);
    audioStreamer1.registerOutput(aac);
    if (audioStreamer1.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from AAC encoder to MP4
    audioStreamer2.registerInput(aac);
    audioStreamer2.registerOutput(mp4);
    if (audioStreamer2.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

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
    Serial.println("- Audio Information -");
    audio.printInfo();
    Serial.println("- AAC Information -");
    aac.printInfo();
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}
