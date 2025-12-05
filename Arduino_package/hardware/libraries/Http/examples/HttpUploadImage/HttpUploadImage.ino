/*
This example shows how to upload an image to a local server using http, a copy of the uploaded image will also be saved to SD card.

Example guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/HTTP/HTTP%20Upload%20Image.html
*/

#include <WiFi.h>
#include "Base64.h"
#include "VideoStream.h"
#include "AmebaFatFS.h"

VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL  0
#define FILENAME "image_upload.jpg"

// Your WiFi credentials
char ssid[] = "Network_SSID";
const char password[] = "Password";
int status = WL_IDLE_STATUS;

// The IP address of your server
char server[] = "192.168.1.23";    // Use LAN IP of Docker host

WiFiClient wifiClient;
AmebaFatFS fs;

uint32_t img_addr = 0;
uint32_t img_len = 0;

void setup()
{
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    config.setRotation(0);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);
    Camera.printInfo();

    delay(5000);

    Camera.getImage(0, &img_addr, &img_len);
    fs.begin();
    File file = fs.open(String(fs.getRootPath()) + String(FILENAME));

    delay(1000);
    file.write((uint8_t *)img_addr, img_len);
    file.close();
    fs.end();

    sendImage();
}

void loop()
{
}

void sendImage()
{
    if (!wifiClient.connect(server, 3000)) {
        Serial.println("Connection failed");
        return;
    }

    Serial.println("Connected to server. Sending image...");

    uint8_t *imgBuf = (uint8_t *)img_addr;
    uint32_t imgLen = img_len;

    const char *boundary = "----AMB82_Boundary";

    // Build multipart header and footer
    String head = "";
    head += "--";
    head += boundary;
    head += "\r\n";
    head += "Content-Disposition: form-data; name=\"image\"; filename=\"photo.jpg\"\r\n";
    head += "Content-Type: image/jpeg\r\n\r\n";

    String tail = "\r\n--";
    tail += boundary;
    tail += "--\r\n";

    // Calculate Content-Length
    uint32_t contentLength = head.length() + imgLen + tail.length();

    // Send HTTP headers
    wifiClient.print("POST /upload HTTP/1.1\r\n");
    wifiClient.print("Host: ");
    wifiClient.print(server);
    wifiClient.print("\r\n");
    wifiClient.print("Content-Type: multipart/form-data; boundary=");
    wifiClient.print(boundary);
    wifiClient.print("\r\n");
    wifiClient.print("Content-Length: ");
    wifiClient.print(contentLength);
    wifiClient.print("\r\n\r\n");

    // Send multipart header
    wifiClient.print(head);

    // Send raw image bytes
    wifiClient.write(imgBuf, imgLen);

    // Send multipart tail
    wifiClient.print(tail);

    Serial.println("Upload finished");

    // Read server response, if there is a respond
    while (wifiClient.connected() || wifiClient.available()) {
        if (wifiClient.available()) {
            String line = wifiClient.readStringUntil('\n');
            Serial.println(line);
        }
    }

    wifiClient.stop();
}
