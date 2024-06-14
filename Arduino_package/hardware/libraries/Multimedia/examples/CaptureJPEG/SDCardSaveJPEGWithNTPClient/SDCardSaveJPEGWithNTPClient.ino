/*  This example uses the camera to capture a JPEG image,
    and saves the image to SD Card.

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-jpeg-sdcard/
*/
#include "VideoStream.h"
#include "AmebaFatFS.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define CHANNEL 0

char ssid[] = "Network_SSID";
char pass[] = "Password";

char filename[] = "image";

char path[128];

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "sg.pool.ntp.org", 28800, 60000);

VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;

AmebaFatFS fs;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    timeClient.begin();
    timeClient.update();

    uint16_t year = (uint16_t)timeClient.getYear();
    uint16_t month = (uint16_t)timeClient.getMonth();
    uint16_t date = (uint16_t)timeClient.getMonthDay();
    uint16_t hour = (uint16_t)timeClient.getHours();
    uint16_t minute = (uint16_t)timeClient.getMinutes();
    uint16_t second = (uint16_t)timeClient.getSeconds();

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    fs.begin();
    sprintf(path, "%s%s%s", fs.getRootPath(), filename, ".jpg");
    File file = fs.open(path);
    delay(100);
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    file.write((uint8_t *)img_addr, img_len);
    delay(100);

    file.close();
    fs.setLastModTime(path, year, month, date, hour, minute, second);
    fs.end();
}

void loop()
{
    delay(1000);
}
