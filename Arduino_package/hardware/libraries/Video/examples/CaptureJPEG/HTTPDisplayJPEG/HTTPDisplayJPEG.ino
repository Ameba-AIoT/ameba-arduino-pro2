/*  This example uses the camera to capture a JPEG image,
 *  and sends the image to a browser using HTTP.
 *  Use any browser and connect to the board's IP address after it has connected to WiFi
*/
#include <WiFi.h>
#include "VideoStream.h"

#define CHANNEL 0

// Use a pre-defined resolution, or choose to configure your own resolution
VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);
//VideoSetting config(1072, 1072, CAM_FPS, VIDEO_JPEG, 1);

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;
WiFiServer server(80);

uint32_t img_addr = 0;
uint32_t img_len = 0;

void sendImage(WiFiClient& client, uint8_t* buf, uint32_t len) {
  uint8_t header_buf[128] = {0};
  uint8_t header_len = snprintf((char*)header_buf, 128, "HTTP/1.1 200 OK\r\nContent-type: image/jpeg\r\nContent-Length: %lu\r\n\r\n", len);
  client.write(header_buf, header_len);
  client.write(buf, len);
  client.print("\r\n");
}

void setup() {
  Serial.begin(115200);
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Camera.configVideoChannel(CHANNEL, config);
  Camera.videoInit();
  Camera.channelBegin(CHANNEL);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client connected");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            Camera.getImage(CHANNEL, &img_addr, &img_len);
            sendImage(client, (uint8_t*)img_addr, img_len);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("client disconnected");
  } else {
    Serial.println("waiting for client connection");
    delay(1000);
  }
}