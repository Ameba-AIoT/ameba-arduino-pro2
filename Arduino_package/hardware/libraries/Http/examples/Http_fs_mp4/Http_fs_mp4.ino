/*
 This example demonstrates the feature of HTTP file server in AMB82 Mini and its usage in accessing MP4 recordings over HTTP.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/HTTP/HTTP%20File%20Server%20and%20MP4.html
*/

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "Http_fs.h"

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
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);    // 2 Input Video + Audio -> 1 Output MP4
Http_fs http_fs;

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
    mp4.setRecordingFileCount(10);
    mp4.setRecordingFileName("HTTP_FS_VIDEO/AmebaPro2_Recording");
    mp4.setLoopRecording(1);

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
    http_fs.mp4DirectoryInit();
    mp4.begin();
    http_fs.begin();
}

void loop()
{
    // do nothing
}
