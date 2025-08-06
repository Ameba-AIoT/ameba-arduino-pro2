/*

This sketch shows the example of speech-to-text using Gemini API.

Gemini platform -
server: generativelanguage.googleapis.com
endpoint: /v1beta/models
model: gemini
https://cloud.google.com/vertex-ai/generative-ai/docs/multimodal/audio-understanding

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Multimedia%20AI/Generative%20AI%20Speech.html

Credit : ChungYi Fu (Kaohsiung, Taiwan)

*/

#include <WiFi.h>
WiFiSSLClient client;
#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "GenAI.h"
GenAI llm;
AudioSetting configA(1);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer1(1, 1);
StreamIO audioStreamer2(1, 1);
#include "AmebaFatFS.h"
AmebaFatFS fs;
File file;
char *file_list;

#include "Base64.h"
#include <ArduinoJson.h>

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password

String apiKey = "";
String fileName = "gemini_speech";
int recordSeconds = 5;    // 5s

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
            if ((StartTime + 5000) < (long int)(millis())) {
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

    audio.configAudio(configA);
    audio.begin();
    aac.configAudio(configA);
    aac.begin();
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(recordSeconds);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName(fileName);
    mp4.setRecordingDataType(STORAGE_AUDIO);
    audioStreamer1.registerInput(audio);
    audioStreamer1.registerOutput(aac);
    if (audioStreamer1.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
    audioStreamer2.registerInput(aac);
    audioStreamer2.registerOutput(mp4);
    if (audioStreamer2.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
    audio.printInfo();

    pinMode(2, INPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_G, OUTPUT);
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
        String text = llm.geminiaudio(apiKey, fileName, "gemini-2.0-flash", mp4, "Please transcribe the audio into text", client);
        Serial.println(text);
    }
}
