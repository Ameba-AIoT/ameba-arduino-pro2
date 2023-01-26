/*  This example uses the camera to capture a JPEG image repeatedly,
 *  and sends the images to a browser continuously using HTTP, creating the effect of a video.
 *  Use Firefox to connect to the board's IP address after it has connected to WiFi,
 *  or use the APP V7RC.
*/

#include <WiFi.h>
#include "VideoStream.h"

#define CHANNEL 0

// Use a pre-defined resolution, or choose to configure your own resolution
// Depending on your WiFi network quality, using HD resolution may lead to an inconsistent frame rate
//VideoSetting config(VIDEO_HD, CAM_FPS, VIDEO_JPEG, 1);
//VideoSetting config(VIDEO_VGA, CAM_FPS, VIDEO_JPEG, 1);
VideoSetting config(1024, 576, CAM_FPS, VIDEO_JPEG, 1);

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;
WiFiServer server(80);

uint32_t img_addr = 0;
uint32_t img_len = 0;

#define PART_BOUNDARY "123456789000000000000987654321"
char* STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
char* IMG_HEADER = "Content-Type: image/jpeg\r\nContent-Length: %lu\r\n\r\n";

void sendHeader(WiFiClient& client) {
  client.print("HTTP/1.1 200 OK\r\nContent-type: multipart/x-mixed-replace; boundary=");
  client.println(PART_BOUNDARY);
  client.print("Transfer-Encoding: chunked\r\n");
  client.print("\r\n");
}

void sendChunk(WiFiClient& client, uint8_t* buf, uint32_t len) {
  uint8_t chunk_buf[64] = {0};
  uint8_t chunk_len = snprintf((char*)chunk_buf, 64, "%lX\r\n", len);
  client.write(chunk_buf, chunk_len);
  client.write(buf, len);
  client.print("\r\n");
}

void setup() {
  Serial.begin(115200);
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    //status = WiFi.apbegin("AmebaVideoAP", "1");
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
            sendHeader(client);
            while (client.connected()) {
              Camera.getImage(CHANNEL, &img_addr, &img_len);
              uint8_t chunk_buf[64] = {0};
              uint8_t chunk_len = snprintf((char*)chunk_buf, 64, IMG_HEADER, img_len);
              sendChunk(client, chunk_buf, chunk_len);
              sendChunk(client, (uint8_t*)img_addr, img_len);
              sendChunk(client, (uint8_t*)STREAM_BOUNDARY, strlen(STREAM_BOUNDARY));
              delay(5);   // Increase this delay for higher resolutions to get a more consistent, but lower frame rate
            }
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
    Serial.println("client disonnected");
  } else {
    Serial.println("waiting for client connection");
    delay(1000);
  }
}