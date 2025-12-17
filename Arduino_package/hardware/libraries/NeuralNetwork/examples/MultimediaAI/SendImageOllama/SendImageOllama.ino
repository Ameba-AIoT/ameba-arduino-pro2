/*
This example demonstrates how to capture an image from the camera and send it to Ollama (a local server for Llava Vision).

Credit: geofrancis
*/

#include <WiFi.h>
#include "VideoStream.h"
#include "Base64.h"
WiFiClient client;
VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL 0

uint32_t img_addr = 0;
uint32_t img_len = 0;

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;     // Indicator of Wifi status

String ollama_key = "";
String message = "Please describe the image, and if there is a text, please summarize the content";

void setup()
{
    Serial.begin(115200);

    // Attempt to connect to WiFi network
    while (status != WL_CONNECTED) {
        Serial.print("\r\nAttempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }

    config.setRotation(0);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);
    Camera.printInfo();
    delay(5000);
    sendollama();
}

void loop()
{
    // do nothing
}

void sendollama()
{
    String model = "llava:34b";
    const char *myDomain = "10.0.0.190";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 11434)) {
        Serial.println("Connection successful");
        Camera.getImage(0, &img_addr, &img_len);
        Serial.println("Image Capture");
        uint8_t *fbBuf = (uint8_t *)img_addr;
        uint32_t fbLen = img_len;
        char *input = (char *)fbBuf;
        char output[base64_enc_len(3)];
        String imageFile = "data:image/jpeg;base64,";
        for (uint32_t i = 0; i < fbLen; i++) {
            base64_encode(output, (input++), 3);
            if (i % 3 == 0) {
                imageFile += String(output);
            }
        }

        String Data = "{\"model\": \"" + model + "\", \"messages\": [{\"role\": \"user\",\"content\": [{ \"type\": \"text\", \"text\": \"" + message + "\"},{\"type\": \"image_url\", \"image_url\": {\"url\": \"" + imageFile + "\"}}]}]}";
        Serial.println("POST");
        client.println("POST /v1/chat/completions HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Authorization: Bearer " + ollama_key);
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(Data.length()));
        client.println("Connection: close");
        Serial.println("Close");
        client.println();

        unsigned int Index;
        for (Index = 0; Index < Data.length(); Index = Index + 1024) {
            client.print(Data.substring(Index, Index + 1024));
        }

        Serial.println("Receive");
        uint32_t waitTime = 10000;
        uint32_t startTime = millis();
        boolean state = false;
        boolean markState = false;

        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(1000);
        }

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
        }

        if (Feedback.length() > 0) {
        }
        Serial.println();
        client.stop();
    }
}
