/*  This example uses the camera to capture JPEG images at regular intervals,
    and saves the images to SD Card.

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-jpeg-sdcard/
*/
#include "VideoStream.h"
#include "AmebaFatFS.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define CHANNEL  0
#define INTERVAL 1000

char ssid[] = "Network_SSID";
char pass[] = "Password";

char filename[] = "image";

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "sg.pool.ntp.org", 28800, 60000);

// Use a pre-defined resolution, or choose to configure your own resolution
VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;
uint32_t count = 0;
char path[128];

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

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    fs.begin();
}

void loop()
{
    timeClient.update();
    uint16_t year = (uint16_t)timeClient.getYear();
    uint16_t month = (uint16_t)timeClient.getMonth();
    uint16_t date = (uint16_t)timeClient.getMonthDay();
    uint16_t hour = (uint16_t)timeClient.getHours();
    uint16_t minute = (uint16_t)timeClient.getMinutes();
    uint16_t second = (uint16_t)timeClient.getSeconds();

    sprintf(path, "%s%s%s%s", fs.getRootPath(), filename, String(count).c_str(), ".jpg");
    File file = fs.open(path);
    delay(100);
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    file.write((uint8_t *)img_addr, img_len);
    delay(100);
    printf("Saved %s\r\n", file.name());
    file.close();
    fs.setLastModTime(path, year, month, date, hour, minute, second);
    count++;
    delay(INTERVAL);
}
