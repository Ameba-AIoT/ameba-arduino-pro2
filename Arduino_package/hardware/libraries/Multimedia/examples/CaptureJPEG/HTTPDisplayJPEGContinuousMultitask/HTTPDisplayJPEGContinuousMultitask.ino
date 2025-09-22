/*  This example uses the camera to capture a JPEG image repeatedly,
 *  and sends the images to a browser continuously using HTTP, creating the effect of a video.
 *  Use browsers(Chrome/Edge) by access the server IP to view the streaming
 *  or use the APP like VLC/Potplayer

 Example guide:
 TBD
*/

#include <WiFi.h>
#include "VideoStream.h"

#define CHANNEL 0
#define PART_BOUNDARY "123456789000000000000987654321"

// Video configuration (lower resolution + FPS for stability)
VideoSetting config(800, 448, 20, VIDEO_JPEG, 1);

char ssid[] = "Network_SSID5";
char pass[] = "Password";
int status = WL_IDLE_STATUS;

WiFiServer server(80, TCP_MODE, NON_BLOCKING_MODE);

// -------------------- HTTP header --------------------
void sendHeader(WiFiClient &client) {
    client.print("HTTP/1.1 200 OK\r\n");
    client.print("Cache-Control: no-cache\r\n");
    client.print("Pragma: no-cache\r\n");
    client.print("Connection: keep-alive\r\n");
    client.print("Content-Type: multipart/x-mixed-replace; boundary=");
    client.println(PART_BOUNDARY);
    client.print("\r\n");
}

// -------------------- Wi-Fi Connect --------------------
void connectWiFi() {
    Serial.print("Connecting to Wi-Fi");
    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(5000);
    }
    Serial.println();
    Serial.print("Connected! IP: "); Serial.println(WiFi.localIP());
}

// -------------------- Streaming Task --------------------
void streamTask(void *parameter) {
    server.begin();

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    while (true) {
        WiFiClient client = server.available();
        if (!client) {
            vTaskDelay(50 / portTICK_PERIOD_MS);
            continue;
        }

        Serial.println("New client connected");

        // -------------------- Read HTTP request --------------------
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                // Print full request info
                Serial.write(c);

                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // End of HTTP request headers
                        sendHeader(client);
                        client.print("--" PART_BOUNDARY "\r\n");
                        break;
                    } else currentLine = "";
                } else if (c != '\r') currentLine += c;
            } else {
                vTaskDelay(1 / portTICK_PERIOD_MS);
            }
        }

        // -------------------- Stream frames --------------------
        while (client.connected()) {
            uint32_t addr = 0, len = 0;
            Camera.getImage(CHANNEL, &addr, &len);

            if (!addr || !len) {
                vTaskDelay(1 / portTICK_PERIOD_MS);
                continue;
            }

            char header[64];
            snprintf(header, sizeof(header),
                     "Content-Type: image/jpeg\r\nContent-Length: %lu\r\n\r\n", len);

            // Break loop if client disconnected
            if (client.write((uint8_t *)header, strlen(header)) == 0) break;
            if (client.write((uint8_t *)addr, len) == 0) break;
            if (client.write((uint8_t *)"\r\n--" PART_BOUNDARY "\r\n",
                             strlen("\r\n--" PART_BOUNDARY "\r\n")) == 0) break;

            // Yield to FreeRTOS to avoid Wi-Fi stack hang
            vTaskDelay(50 / portTICK_PERIOD_MS); // ~20 FPS
        }

        client.stop();
        Serial.println("Client disconnected");
    }
}

// -------------------- Setup --------------------
void setup() {
    Serial.begin(115200);
    connectWiFi();

    // Create FreeRTOS task for streaming
    xTaskCreate(streamTask, "StreamTask", 6144, NULL, 1, NULL);
}

void loop() {
    // Nothing here; streaming handled in FreeRTOS task
}
