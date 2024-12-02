#include "NNGenAIVision.h"
#include <ArduinoJson.h>
#include "Base64.h"

NNGenAIVision::NNGenAIVision()
{
}

NNGenAIVision::~NNGenAIVision()
{
}

// Model: gpt-4o-mini, Server: openAI Platform
String NNGenAIVision::openaivision(String key, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client)
{
    const char *myDomain = "api.openai.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

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

// Model: gemini-1.5, Server: Google AI Studio
String NNGenAIVision::geminivision(String key, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client)
{
    const char *myDomain = "generativelanguage.googleapis.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

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
        // String Data = "{\"contents\": [{\"parts\": [{\"text\": \""+message+"\"}]}]}";

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

// Model: llama-3.2-90b-vision-preview, Server: groq
String NNGenAIVision::llamavision(String key, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client)
{
    const char *myDomain = "api.groq.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

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
        String Data = "{\"model\": \"llama-3.2-90b-vision-preview\", \"messages\": [{\"role\": \"user\",\"content\": [{ \"type\": \"text\", \"text\": \"" + message + "\"},{\"type\": \"image_url\", \"image_url\": {\"url\": \"" + imageFile + "\"}}]}]}";

        client.println("POST /openai/v1/chat/completions HTTP/1.1");
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
