/*  This example uses the camera to capture a JPEG image repeatedly,
 *  and sends the images to a browser continuously using HTTP, creating the effect of a video.
 *  Use browsers(Chrome/Edge) by access the server IP to view the streaming
 *  or use the APP like VLC/Potplayer

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/CaptureJPEG/Capture%20JPEG%20display%20over%20HTTP%20Continuous.html
*/

#include <WiFi.h>
#include "VideoStream.h"

#define CHANNEL       0
#define PART_BOUNDARY "123456789000000000000987654321"

// Use a pre-defined resolution, or choose to configure your own resolution
// Depending on your WiFi network quality, using HD resolution may lead to an inconsistent frame rate
#define STREAM_FPS 15
// VideoSetting config(VIDEO_HD, STREAM_FPS, VIDEO_JPEG, 1);
// VideoSetting config(1024, 576, STREAM_FPS, VIDEO_JPEG, 1);
VideoSetting config(VIDEO_VGA, STREAM_FPS, VIDEO_JPEG, 1);

// Convert FPS into FreeRTOS tick delay
#define FRAME_INTERVAL (1000 / STREAM_FPS / portTICK_PERIOD_MS)

char ssid[] = "Network_SSID";
char pass[] = "Password";
int status = WL_IDLE_STATUS;

WiFiServer server(80, TCP_MODE, NON_BLOCKING_MODE);

static char headerBuf[64];

// -------------------- HTTP header --------------------
void sendHeader(WiFiClient &client)
{
    client.print("HTTP/1.1 200 OK\r\n");
    client.print("Cache-Control: no-cache\r\n");
    client.print("Pragma: no-cache\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Type: multipart/x-mixed-replace; boundary=");
    client.println(PART_BOUNDARY);
    client.print("\r\n");
}

// -------------------- Wi-Fi Connect --------------------
void connectWiFi()
{
    Serial.print("Connecting to Wi-Fi");
    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, pass);
        Serial.print(".");
        delay(5000);
    }
    Serial.println();
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP());
}

// -------------------- Streaming Task --------------------
void streamTask(void *parameter)
{
    server.begin();

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    char lineBuf[128];    // buffer for request lines
    int linePos = 0;

    while (true) {
        WiFiClient client = server.available();
        if (!client) {
            vTaskDelay(50 / portTICK_PERIOD_MS);
            continue;
        }

        Serial.println("New client connected");

        // -------------------- Read HTTP request --------------------
        linePos = 0;
        memset(lineBuf, 0, sizeof(lineBuf));

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                if (c == '\n') {
                    if (linePos == 0) {
                        // End of headers
                        sendHeader(client);
                        client.print("--" PART_BOUNDARY "\r\n");
                        break;
                    } else {
                        // Print collected request header line
                        Serial.println(lineBuf);
                        linePos = 0;
                        memset(lineBuf, 0, sizeof(lineBuf));
                    }
                } else if (c != '\r' && linePos < (int)sizeof(lineBuf) - 1) {
                    lineBuf[linePos++] = c;
                }
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

            snprintf(headerBuf, sizeof(headerBuf), "Content-Type: image/jpeg\r\nContent-Length: %lu\r\n\r\n", len);

            if (client.write((uint8_t *)headerBuf, strlen(headerBuf)) == 0) {
                break;
            }
            if (client.write((uint8_t *)addr, len) == 0) {
                break;
            }
            if (client.write((uint8_t *)"\r\n--" PART_BOUNDARY "\r\n", strlen("\r\n--" PART_BOUNDARY "\r\n")) == 0) {
                break;
            }

            vTaskDelay(FRAME_INTERVAL);
        }

        client.stop();
        Serial.println("Client disconnected");
    }
}

void setup()
{
    Serial.begin(115200);
    connectWiFi();

    xTaskCreate(streamTask, "StreamTask", (8 * 1024), NULL, 1, NULL);
}

void loop()
{
    // Nothing here
}
