/*

This example shows the combination of NTP with text-to-speech application using Google Translate API

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Multimedia%20AI/Text-to-Speech%20NTP.html

*/

#include "WiFi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "GenAI.h"

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password

#include "AmebaFatFS.h"

AmebaFatFS fs;
GenAI tts;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String mp3Filename = "test_play_google_tts_time.mp3";

void initWiFi()
{
    for (int i = 0; i < 2; i++) {
        WiFi.begin(ssid, pass);

        delay(1000);
        Serial.println("");
        Serial.print("Connecting to ");
        Serial.println(ssid);

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
    timeClient.update();
    String message = "Today is " + timeClient.getFormattedDate();
    Serial.println(timeClient.getFormattedTime());
    tts.googletts(mp3Filename, message, "en-US");
    delay(500);
    sdPlayMP3(mp3Filename);
}

void loop()
{
    delay(1000);
}

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
