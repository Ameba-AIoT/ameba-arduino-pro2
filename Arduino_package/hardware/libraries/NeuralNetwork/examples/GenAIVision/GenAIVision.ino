/*

This sketch shows the example of image prompts openAI Vision and Gemini Vision API

openAI Vision
https://platform.openai.com/docs/guides/vision

Gemini Vision
https://ai.google.dev/gemini-api/docs/vision

Example Guide: TBD

Credit : ChungYi Fu (Kaohsiung, Taiwan)

*/

String openAI_key = "";                // paste your generated openAI key here
String Gemini_key = "";                // paste your generated Gemini key here
char wifi_ssid[] = "Network_SSID5";    // change to your network SSID
char wifi_pass[] = "Password";         // change to your network password

#include <WiFi.h>
WiFiSSLClient client;
#include <ArduinoJson.h>
#include "Base64.h"
#include "VideoStream.h"
VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL 0

uint32_t img_addr = 0;
uint32_t img_len = 0;

void initWiFi()
{
    for (int i = 0; i < 2; i++) {
        WiFi.begin(wifi_ssid, wifi_pass);

        delay(1000);
        Serial.println("");
        Serial.print("Connecting to ");
        Serial.println(wifi_ssid);

        long int StartTime = millis();
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

String SendStillToOpenaiVision(String key, String message, bool capture)
{
    const char *myDomain = "api.openai.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");
        if (capture) {
            Camera.getImage(0, &img_addr, &img_len);
        }
        uint8_t *fbBuf = (uint8_t *)img_addr;
        size_t fbLen = img_len;

        char *input = (char *)fbBuf;
        char output[base64_enc_len(3)];
        String imageFile = "data:image/jpeg;base64,";
        for (int i = 0; i < fbLen; i++) {
            base64_encode(output, (input++), 3);
            if (i % 3 == 0) {
                imageFile += String(output);
            }
        }
        String Data = "{\"model\": \"gpt-4o-mini\", \"messages\": [{\"role\": \"user\",\"content\": [{ \"type\": \"text\", \"text\": \"" + message + "\"},{\"type\": \"image_url\", \"image_url\": {\"url\": \"" + imageFile + "\"}}]}]}";

        client.println("POST /v1/chat/completions HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Authorization: Bearer " + key);
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(Data.length()));
        client.println("Connection: close");
        client.println();

        int Index;
        for (Index = 0; Index < Data.length(); Index = Index + 1024) {
            client.print(Data.substring(Index, Index + 1024));
        }

        int waitTime = 10000;
        long startTime = millis();
        boolean state = false;
        boolean markState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (String(c) == "{") {
                    markState = true;
                }
                if (state == true && markState == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        Serial.println();
        client.stop();

        JsonObject obj;
        DynamicJsonDocument doc(4096);
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        getResponse = obj["choices"][0]["message"]["content"].as<String>();
        if (getResponse == "null") {
            getResponse = obj["error"]["message"].as<String>();
        }
    } else {
        getResponse = "Connected to " + String(myDomain) + " failed.";
        Serial.println("Connected to " + String(myDomain) + " failed.");
    }

    return getResponse;
}

String SendStillToGeminiVision(String key, String message, bool capture)
{
    const char *myDomain = "generativelanguage.googleapis.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");
        if (capture) {
            Camera.getImage(0, &img_addr, &img_len);
        }
        uint8_t *fbBuf = (uint8_t *)img_addr;
        size_t fbLen = img_len;

        char *input = (char *)fbBuf;
        char output[base64_enc_len(3)];
        String imageFile = "";
        for (int i = 0; i < fbLen; i++) {
            base64_encode(output, (input++), 3);
            if (i % 3 == 0) {
                imageFile += String(output);
            }
        }
        String Data = "{\"contents\": [{\"parts\": [{\"text\": \"" + message + "\"}, {\"inline_data\": {\"mime_type\":\"image/jpeg\",\"data\":\"" + imageFile + "\"}}]}]}";

        client.println("POST /v1beta/models/gemini-1.5-flash-latest:generateContent?key=" + key + " HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(Data.length()));
        client.println("Connection: close");
        client.println();

        int Index;
        for (Index = 0; Index < Data.length(); Index = Index + 1024) {
            client.print(Data.substring(Index, Index + 1024));
        }

        int waitTime = 10000;
        long startTime = millis();
        boolean state = false;
        boolean markState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (String(c) == "{") {
                    markState = true;
                }
                if (state == true && markState == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        Serial.println();
        client.stop();

        JsonObject obj;
        DynamicJsonDocument doc(4096);
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        getResponse = obj["candidates"][0]["content"]["parts"][0]["text"].as<String>();
        if (getResponse == "null") {
            getResponse = obj["error"]["message"].as<String>();
        }
    } else {
        getResponse = "Connected to " + String(myDomain) + " failed.";
        Serial.println("Connected to " + String(myDomain) + " failed.");
    }

    return getResponse;
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
    Serial.println((SendStillToOpenaiVision(openAI_key, "Please describe the image, and if there is text, please summarize the content", 0)));
    Serial.println((SendStillToGeminiVision(Gemini_key, "Please describe the image, and if there is text, please summarize the content", 0)));

    /*
    // Vision prompt using different image
    Serial.println((SendStillToOpenaiVision(openAI_key, "Please describe the image, and if there is text, please summarize the content", 1)));
    delay(5000);
    Serial.println((SendStillToGeminiVision(Gemini_key, "Please describe the image, and if there is text, please summarize the content", 1)));
    */
}

void loop()
{
    // do nothing
}
