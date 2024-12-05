/*

This sketch shows the example of image prompts using APIs.

openAI platform - openAI vision
https://platform.openai.com/docs/guides/vision

Google AI Studio - Gemini vision
https://ai.google.dev/gemini-api/docs/vision

GroqCloud - Llama vision
https://console.groq.com/docs/overview

Example Guide: https://ameba-arduino-doc.readthedocs.io/en/latest/amebapro2/Example_Guides/Neural%20Network/Generative%20AI%20Vision.html

Credit : ChungYi Fu (Kaohsiung, Taiwan)

*/

String openAI_key = "";                // paste your generated openAI API key here
String Gemini_key = "";                // paste your generated Gemini API key here
String Llama_key = "";                 // paste your generated Llama API key here
char wifi_ssid[] = "Network_SSID5";    // change to your network SSID
char wifi_pass[] = "Password";         // change to your network password

#include <WiFi.h>
#include "NNGenAIVision.h"
#include "VideoStream.h"
WiFiSSLClient client;
NNGenAIVision llm;
VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL 0

uint32_t img_addr = 0;
uint32_t img_len = 0;

String prompt_msg = "Please describe the image, and if there is a text, please summarize the content";

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

    // Vision prompt using same taken image
    Camera.getImage(0, &img_addr, &img_len);

    // openAI vision prompt
    // llm.openaivision(openAI_key, prompt_msg, img_addr, img_len, client);

    // Gemini vision prompt
    llm.geminivision(Gemini_key, prompt_msg, img_addr, img_len, client);

    // Llama vision prompt
    // llm.llamavision(Llama_key, prompt_msg, img_addr, img_len, client);
}

void loop()
{
    // do nothing
}
