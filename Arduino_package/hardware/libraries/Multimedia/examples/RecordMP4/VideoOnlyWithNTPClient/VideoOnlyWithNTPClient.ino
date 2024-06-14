/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-mp4/
 */

#include "StreamIO.h"
#include "VideoStream.h"
#include "MP4Recording.h"

#include "AmebaFatFS.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define CHANNEL 0

char path[128];

char ssid[] = "Network_SSID";
char pass[] = "Password";

WiFiUDP ntpUDP;

AmebaFatFS fs;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "sg.pool.ntp.org", 28800, 60000);

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

VideoSetting config(CHANNEL);
MP4Recording mp4;
StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output RTSP
bool updatemodifiedtime = false;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    timeClient.begin();

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(config);
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingVideoOnly");
    mp4.setRecordingDataType(STORAGE_VIDEO);    // Set MP4 to record video only

    // Configure StreamIO object to stream data from video channel to MP4 recording
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(mp4);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);
    // Start recording MP4 data to SD card
    mp4.begin();

    delay(1000);
    printInfo();
}

void loop()
{
    // For updating last modified time after recording stop
    int state = (int)mp4.getRecordingState();
    if (state == 0 && updatemodifiedtime == false) {
        timeClient.update();

        uint16_t year = (uint16_t)timeClient.getYear();
        uint16_t month = (uint16_t)timeClient.getMonth();
        uint16_t date = (uint16_t)timeClient.getMonthDay();
        uint16_t hour = (uint16_t)timeClient.getHours();
        uint16_t minute = (uint16_t)timeClient.getMinutes();
        uint16_t second = (uint16_t)timeClient.getSeconds();

        sprintf(path, "%s%s%s", fs.getRootPath(), mp4.getRecordingFileName().c_str(), ".mp4");
        fs.begin();
        fs.setLastModTime(path, year, month, date, hour, minute, second);
        fs.end();
        updatemodifiedtime = true;
    } else if (state == 1 && updatemodifiedtime == true) {
        updatemodifiedtime = false;
    }
    delay(100);
}

void printInfo(void)
{
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}
