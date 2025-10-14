/*

This sketch shows the example of understanding video content using Gemini API.

Gemini platform -
server: generativelanguage.googleapis.com
endpoint: /v1beta/models
model: gemini
https://cloud.google.com/vertex-ai/generative-ai/docs/multimodal/video-understanding

Example guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Multimedia%20AI/Generative%20AI%20Video.html

Credit : ChungYi Fu (Kaohsiung, Taiwan)

*/

#include <WiFi.h>
WiFiSSLClient client;
#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "GenAI.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

GenAI llm;
VideoSetting configV(CHANNEL);
AudioSetting configA(1);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);    // 2 Input Video + Audio -> 1 Output MP4

#include "AmebaFatFS.h"
AmebaFatFS fs;
File file;
char *file_list;

#include "Base64.h"
#include <ArduinoJson.h>

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password

String apiKey = "";
String fileName = "gemini_video_audio";
int recordSeconds = 10;    // 10s

void initWiFi()
{

    for (int i = 0; i < 2; i++) {
        WiFi.begin(ssid, pass);

        delay(1000);
        Serial.println("");
        Serial.print("Connecting to ");
        Serial.println(ssid);

        long int StartTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            if ((StartTime + 5000) < (long int)millis()) {
                break;
            }
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("");
            Serial.println("STAIP address: ");
            Serial.println(WiFi.localIP());
            Serial.println("");

            break;
        }
    }
}

void setup()
{
    Serial.begin(115200);
    initWiFi();

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
    mp4.setRecordingDuration(recordSeconds);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName(fileName);

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
    delay(1000);

    pinMode(2, INPUT);
    pinMode(LED_B, OUTPUT);
}

void loop()
{
    if ((digitalRead(2)) == 1) {
        // Start MP4 recording after 3 seconds of blinking
        for (int count = 0; count < 3; count++) {
            digitalWrite(LED_B, HIGH);
            delay(500);
            digitalWrite(LED_B, LOW);
            delay(500);
        }
        String text = llm.geminivideo(apiKey, fileName, "gemini-2.5-flash", mp4, "Please describe the video and audio content", client);
        Serial.println(text);
    }
}
