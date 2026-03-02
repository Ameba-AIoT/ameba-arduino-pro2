/*
This example shows how to upload an image to Telegram using a bot.

Example guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/HTTP/HTTP%20Upload%20Image%20Telegram.html
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiSSLClient.h>
#include <NTPClient.h>
#include "VideoStream.h"

#define CHANNEL 0

VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;

char ssid[] = "Network_SSID";
const char password[] = "Password";

// Telegram
String botToken = "123456789:ABCdefYOUR_BOT_TOKEN";    // set your bot token here
String chatID = "123456789";                           // set your chat ID here

unsigned long lastUpdateID = 0;
unsigned long lastPoll = 0;

// Separate SSL clients for sending & polling
WiFiSSLClient pollClient;
WiFiSSLClient sendClient;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void forceClose(WiFiSSLClient &c)
{
    if (c.connected()) {
        c.stop();
        delay(50);
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Connecting WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }
    Serial.println("WiFi connected");

    // Initialize camera
    config.setRotation(0);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);
    Camera.printInfo();

    delay(3000);

    timeClient.begin();

    Serial.println("Type /capture in your Telegram bot.");
}

void loop()
{
    unsigned long now = millis();
    if (now - lastPoll > 3000) {    // poll every 3s
        checkTelegramCommands();
        lastPoll = now;
    }
}

void captureImage()
{
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    Serial.println("Image captured");
}

void sendPhotoToTelegram()
{

    forceClose(sendClient);    // reset SSL session

    if (!sendClient.connect("api.telegram.org", 443)) {
        Serial.println("Send connect failed");
        return;
    }
    Serial.println("Connected to Telegram");

    // Timestamp caption
    String timestamp = getTimestamp();
    String caption = "Captured at " + timestamp;

    String boundary = "----AMB82_Boundary";
    String url = "/bot" + botToken + "/sendPhoto";

    uint8_t *imgBuf = (uint8_t *)img_addr;
    uint32_t imgLenVal = img_len;

    String head =
        "--" + boundary + "\r\n"
                          "Content-Disposition: form-data; name=\"chat_id\"\r\n\r\n"
        + chatID + "\r\n" + "--" + boundary + "\r\n"
                                              "Content-Disposition: form-data; name=\"caption\"\r\n\r\n"
        + caption + "\r\n" + "--" + boundary + "\r\n"
                                               "Content-Disposition: form-data; name=\"photo\"; filename=\"img.jpg\"\r\n"
                                               "Content-Type: image/jpeg\r\n\r\n";

    String tail = "\r\n--" + boundary + "--\r\n";
    uint32_t contentLength = head.length() + imgLenVal + tail.length();

    // HTTP header
    sendClient.println("POST " + url + " HTTP/1.1");
    sendClient.println("Host: api.telegram.org");
    sendClient.println("Content-Type: multipart/form-data; boundary=" + boundary);
    sendClient.println("Content-Length: " + String(contentLength));
    sendClient.println("Connection: close");
    sendClient.println();

    sendClient.print(head);
    sendImageChunks(sendClient, imgBuf, imgLenVal);
    sendClient.print(tail);

    Serial.println("Image send");
    sendClient.stop();
}

void sendImageChunks(WiFiSSLClient &client, uint8_t *buf, uint32_t len)
{
    const size_t CHUNK = 4096;
    uint32_t sent = 0;

    while (sent < len) {
        size_t n = min(CHUNK, len - sent);
        client.write(buf + sent, n);
        sent += n;
        delay(5);    // prevents SSL overrun
    }
}

String getTimestamp()
{
    timeClient.update();

    char buf[32];
    sprintf(buf, "%04d-%02d-%02d_%02d:%02d:%02d",
            timeClient.getYear(),
            timeClient.getMonth(),
            timeClient.getMonthDay(),
            timeClient.getHours(),
            timeClient.getMinutes(),
            timeClient.getSeconds());

    return String(buf);
}

void checkTelegramCommands()
{

    forceClose(pollClient);

    if (!pollClient.connect("api.telegram.org", 443)) {
        Serial.println("Poll connect failed");
        return;
    }

    String url =
        "/bot"
        + botToken + "/getUpdates?timeout=2&offset=" + String(lastUpdateID + 1);

    pollClient.println("GET " + url + " HTTP/1.1");
    pollClient.println("Host: api.telegram.org");
    pollClient.println("Connection: close");
    pollClient.println();

    unsigned long t0 = millis();
    while (!pollClient.available()) {
        if (millis() - t0 > 3000) {
            pollClient.stop();
            return;
        }
        delay(10);
    }

    String payload;
    while (pollClient.available()) {
        payload += (char)pollClient.read();
    }
    pollClient.stop();

    int jsonStart = payload.indexOf("\r\n\r\n");
    if (jsonStart < 0) {
        return;
    }

    String json = payload.substring(jsonStart + 4);

    if (json.indexOf("\"result\":[]") != -1) {
        return;
    }

    // Parse update_id
    int idIndex = json.indexOf("\"update_id\":");
    if (idIndex < 0) {
        return;
    }
    int start = json.indexOf(":", idIndex) + 1;
    int end = json.indexOf(",", start);
    lastUpdateID = json.substring(start, end).toInt();

    // Parse text
    int tIdx = json.indexOf("\"text\":");
    if (tIdx < 0) {
        return;
    }
    int tstart = json.indexOf("\"", tIdx + 7) + 1;
    int tend = json.indexOf("\"", tstart);
    String text = json.substring(tstart, tend);

    Serial.print("Command: ");
    Serial.println(text);

    if (text == "/capture") {
        captureImage();
        sendPhotoToTelegram();
    }
}
