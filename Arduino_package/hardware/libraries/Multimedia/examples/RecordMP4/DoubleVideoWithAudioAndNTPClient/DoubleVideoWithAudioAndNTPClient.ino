/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-mp4/
 */

#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"

#include "AmebaFatFS.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define CHANNEL 0

char path1[128];
char path2[128];

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

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

VideoSetting configV1(0);
VideoSetting configV2(1);
AudioSetting configA(0);
Audio audio;
AAC aac;
MP4Recording mp4_1;
MP4Recording mp4_2;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(3, 2);    // 3 Input Video1 + Video2 + Audio -> 2 Output MP4_1 + MP4_2
bool updatemodifiedtime1 = false;
bool updatemodifiedtime2 = false;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    timeClient.begin();

    // Configure both camera video channels with corresponding video format information
    Camera.configVideoChannel(0, configV1);
    Camera.configVideoChannel(1, configV2);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure MP4 with corresponding video format information
    // Configure MP4 recording settings
    mp4_1.configVideo(configV1);
    mp4_1.configAudio(configA, CODEC_AAC);
    mp4_1.setRecordingDuration(15);
    mp4_1.setRecordingFileCount(1);
    mp4_1.setRecordingFileName("TestRecordingAudioVideo1");

    mp4_2.configVideo(configV2);
    mp4_2.configAudio(configA, CODEC_AAC);
    mp4_2.setRecordingDuration(30);
    mp4_2.setRecordingFileCount(1);
    mp4_2.setRecordingFileName("TestRecordingAudioVideo2");

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channels and AAC encoder to MP4 outputs
    avMixStreamer.registerInput1(Camera.getStream(0));
    avMixStreamer.registerInput2(Camera.getStream(1));
    avMixStreamer.registerInput3(aac);
    avMixStreamer.registerOutput1(mp4_1);
    avMixStreamer.registerOutput2(mp4_2);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channels
    Camera.channelBegin(0);
    Camera.channelBegin(1);
    // Start recording MP4 data to SD card
    mp4_1.begin();
    mp4_2.begin();

    fs.begin();
    delay(1000);
    printInfo();
}

void loop()
{
    uint16_t year, month, date, hour, minute, second;

    // For updating last modified time after recording stop
    int state1 = (int)(mp4_1.getRecordingState());
    if (state1 == 0 && updatemodifiedtime1 == false) {
        timeClient.update();

        year = (uint16_t)timeClient.getYear();
        month = (uint16_t)timeClient.getMonth();
        date = (uint16_t)timeClient.getMonthDay();
        hour = (uint16_t)timeClient.getHours();
        minute = (uint16_t)timeClient.getMinutes();
        second = (uint16_t)timeClient.getSeconds();

        sprintf(path1, "%s%s%s", fs.getRootPath(), mp4_1.getRecordingFileName().c_str(), ".mp4");
        fs.begin();
        fs.setLastModTime(path1, year, month, date, hour, minute, second);
        updatemodifiedtime1 = true;
    } else if (state1 == 1 && updatemodifiedtime1 == true) {
        updatemodifiedtime1 = false;
    }

    int state2 = (int)(mp4_2.getRecordingState());
    if (state2 == 0 && updatemodifiedtime2 == false) {
        timeClient.update();

        year = (uint16_t)timeClient.getYear();
        month = (uint16_t)timeClient.getMonth();
        date = (uint16_t)timeClient.getMonthDay();
        hour = (uint16_t)timeClient.getHours();
        minute = (uint16_t)timeClient.getMinutes();
        second = (uint16_t)timeClient.getSeconds();

        sprintf(path2, "%s%s%s", fs.getRootPath(), mp4_2.getRecordingFileName().c_str(), ".mp4");
        fs.begin();
        fs.setLastModTime(path2, year, month, date, hour, minute, second);
        updatemodifiedtime2 = true;
    } else if (state2 == 1 && updatemodifiedtime2 == true) {
        updatemodifiedtime2 = false;
    }
    delay(100);
}

void printInfo(void)
{
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");

    Camera.printInfo();

    Serial.println("- Audio Information -");
    audio.printInfo();
    Serial.println("- MP4 Recording Information 1-");
    mp4_1.printInfo();
    Serial.println("- MP4 Recording Information 2-");
    mp4_2.printInfo();
}
