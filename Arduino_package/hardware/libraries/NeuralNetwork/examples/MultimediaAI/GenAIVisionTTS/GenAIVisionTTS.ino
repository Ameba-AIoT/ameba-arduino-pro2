/*

This sketch shows the combination examples of GenAIVision, Google TTS and SD card play MP3.

Contributed by: geofrancis

*/

String Gemini_key = "";                // paste your generated Gemini API key here
char wifi_ssid[] = "Network_SSID5";    // change to your network SSID
char wifi_pass[] = "Password";         // change to your network password

#include "GenAI.h"
#include "VideoStream.h"
#include <WiFi.h>
WiFiSSLClient client;
GenAI llm;
VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL 0

uint32_t img_addr = 0;
uint32_t img_len = 0;

#include "AmebaFatFS.h"

AmebaFatFS fs;
GenAI tts;

String mp3Filename = "test_play_google_tts.mp3";
String prompt_msg = "describe what you see in one sentence";

void initWiFi()
{
    for (int i = 0; i < 2; i++) {
        WiFi.begin(wifi_ssid, wifi_pass);

        delay(1000);
        Serial.println("");
        Serial.print("Connecting to ");
        Serial.println(wifi_ssid);

        uint32_t StartTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            if ((StartTime + 5000) < millis()) {
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

    config.setRotation(0);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);
    Camera.printInfo();

    delay(5000);

    // take picture
    Camera.getImage(0, &img_addr, &img_len);

    delay(5000);

    tts.googletts(mp3Filename, llm.geminivision(Gemini_key, "gemini-flash-latest", prompt_msg, img_addr, img_len, client), "en-US");

    delay(5000);

    sdPlayMP3(mp3Filename);
}

void loop()
{}

void sdPlayMP3(String filename)
{
    fs.begin();
    String filepath = String(fs.getRootPath()) + filename;
    File file = fs.open(filepath, MP3);
    file.setMp3DigitalVol(120);
    file.playMp3();
    file.close();
    fs.end();
}
