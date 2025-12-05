/*
This example shows how to upload an image to Google Drive using Google Apps Scripts.

Example guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/HTTP/HTTP%20Upload%20Image%20Google%20Drive.html
*/

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "VideoStream.h"
#include "Base64.h"

#define CHANNEL 0

VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);

char ssid[] = "Network_SSID";
const char password[] = "Password";

// Enter your Google Script details
String myScript = "/macros/s/YOUR_SCRIPT_URL/exec";    // Create your Google Apps Script and replace the "myScript" path.
String myFoldername = "&myFoldername=AMB82-mini";      // Set the Google Drive folder name to store your file
String myImage = "&myFile=";

uint32_t img_addr = 0;
uint32_t img_len = 0;

WiFiSSLClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup()
{
    Serial.begin(115200);

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

    timeClient.begin();

    Camera.getImage(0, &img_addr, &img_len);

    uploadToGoogleDrive();
}

void uploadToGoogleDrive()
{

    uint8_t *imgBuf = (uint8_t *)img_addr;
    uint32_t imgLen = img_len;

    char *input = (char *)imgBuf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base32,";
    for (uint32_t i = 0; i < imgLen; i++) {
        base64_encode(output, (input++), 3);
        if (i % 3 == 0) {
            imageFile += urlencode(String(output));
        }
    }

    String timestamp = getTimestamp();

    String myFilename = "&myFilename=" + timestamp + ".jpg";

    Serial.println("Uploading file to Google Drive...");
    String Data = myFoldername + myFilename + myImage;
    const char *myDomain = "script.google.com";
    String getAll = "", getBody = "";
    Serial.println("Connect to " + String(myDomain));

    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

        client.println("POST " + myScript + " HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Content-Length: " + String(Data.length() + imageFile.length()));
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.println("Connection: keep-alive");
        client.println();

        client.print(Data);
        for (unsigned int Index = 0; Index < imageFile.length(); Index = Index + 1000) {
            client.print(imageFile.substring(Index, Index + 1000));
        }

        int waitTime = 10000;    // timeout 10 seconds
        unsigned int startTime = millis();
        boolean state = false;

        while ((startTime + waitTime) > millis()) {
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (state == true) {
                    getBody += String(c);
                }
                if (c == '\n') {
                    if (getAll.length() == 0) {
                        state = true;
                    }
                    getAll = "";
                } else if (c != '\r') {
                    getAll += String(c);
                }
                startTime = millis();
            }
            if (getBody.length() > 0) {
                break;
            }
        }
        client.stop();
        Serial.println(getBody);
    } else {
        getBody = "Connected to " + String(myDomain) + " failed";
        Serial.println("Connected to " + String(myDomain) + " failed");
    }
    Serial.println("File uploading done");
}

String getTimestamp()
{
    char buf[32];

    timeClient.update();

    sprintf(buf, "%04d%02d%02d_%02d%02d%02d",
            timeClient.getYear(),
            timeClient.getMonth(),
            timeClient.getMonthDay(),
            timeClient.getHours(),
            timeClient.getMinutes(),
            timeClient.getSeconds());

    return String(buf);
}

// https://www.arduino.cc/reference/en/libraries/urlencode/
String urlencode(String str)
{
    const char *msg = str.c_str();
    const char *hex = "0123456789ABCDEF";
    String encodedMsg = "";
    while (*msg != '\0') {
        if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~') {
            encodedMsg += *msg;
        } else {
            encodedMsg += '%';
            encodedMsg += hex[(unsigned char)*msg >> 4];
            encodedMsg += hex[*msg & 0xf];
        }
        msg++;
    }
    return encodedMsg;
}

void loop()
{
}
