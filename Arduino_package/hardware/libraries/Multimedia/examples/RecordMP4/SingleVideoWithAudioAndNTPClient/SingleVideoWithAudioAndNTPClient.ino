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

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

VideoSetting configV(CHANNEL);
AudioSetting configA(0);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);    // 2 Input Video + Audio -> 1 Output MP4
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
    Camera.configVideoChannel(CHANNEL, configV);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(configV);
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingAudioVideo");

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixStreamer.registerInput1(Camera.getStream(CHANNEL));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput(mp4);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);
    // Start recording MP4 data to SD card
    mp4.begin();

    // Print information
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

    Serial.println("- Audio Information -");
    audio.printInfo();
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}
