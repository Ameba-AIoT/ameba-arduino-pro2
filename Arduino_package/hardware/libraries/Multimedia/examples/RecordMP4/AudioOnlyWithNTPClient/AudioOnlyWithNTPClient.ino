/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/MP4%20Recording.html
*/

#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"

#include "AmebaFatFS.h"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

char path[128];

char ssid[] = "Network_SSID";
char pass[] = "Password";

WiFiUDP ntpUDP;

AmebaFatFS fs;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "sg.pool.ntp.org", 28800, 60000);

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

AudioSetting configA(0);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer1(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO audioStreamer2(1, 1);    // 1 Input AAC -> 1 Output MP4

#define TOTAL_FILES          1
#define RECORDING_DURATION_S 30

volatile uint32_t fileCloseCount = 0;
volatile unsigned long fileCloseTimestamps[TOTAL_FILES];
bool timestampsWritten = false;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    timeClient.begin();

    Serial.println("Synchronizing NTP...");

    while (!timeClient.forceUpdate()) {
        Serial.println("NTP sync failed, retrying...");
        delay(1000);
    }

    Serial.println("NTP synchronized");

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure MP4 recording settings
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(RECORDING_DURATION_S);
    mp4.setRecordingFileCount(TOTAL_FILES);
    mp4.setRecordingFileName("TestRecordingAudioOnly");
    mp4.setRecordingDataType(STORAGE_AUDIO);    // Set MP4 to record audio only
    mp4.setRecordingStopCallback(MP4FileClosedCb);

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer1.registerInput(audio);
    audioStreamer1.registerOutput(aac);
    if (audioStreamer1.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from AAC encoder to MP4
    audioStreamer2.registerInput(aac);
    audioStreamer2.registerOutput(mp4);
    if (audioStreamer2.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start recording MP4 data to SD card
    mp4.begin();

    if (!fs.begin()) {
        Serial.println("ERROR: FATFS initialization failed");

        while (1) {
            delay(1000);
        }
    }

    Serial.print("FATFS root: ");
    Serial.println(fs.getRootPath());

    delay(1000);
    printInfo();
}

void loop()
{
    if ((fileCloseCount >= TOTAL_FILES) && (mp4.getRecordingState() == 0) && (timestampsWritten == false)) {

        Serial.println();
        Serial.println("Updating timestamps...");

        for (uint32_t i = 0; i < TOTAL_FILES; i++) {

            unsigned long timestamp = fileCloseTimestamps[i];

            updateFileTimestamp(i, timestamp);
        }

        timestampsWritten = true;

        fs.end();
    }

    delay(20);
}

void printInfo(void)
{
    Serial.println(" ");
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Serial.println("- Audio Information -");
    audio.printInfo();
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}

int MP4FileClosedCb(void *param)
{
    uint32_t index = fileCloseCount;

    if (fileCloseCount < TOTAL_FILES) {

        // Capture NTP-synchronized clock at actual MP4 stop event
        fileCloseTimestamps[index] = timeClient.getEpochTime();

        fileCloseCount = index + 1;
    }

    return 0;
}

void updateFileTimestamp(uint32_t index, unsigned long epoch)
{
    time_t fileTime = (time_t)epoch;
    struct tm *timeinfo = gmtime(&fileTime);

    if (timeinfo == NULL) {
        Serial.println("ERROR: Time conversion failed");
        return;
    }

    uint16_t year = timeinfo->tm_year + 1900;
    uint16_t month = timeinfo->tm_mon + 1;
    uint16_t day = timeinfo->tm_mday;
    uint16_t hour = timeinfo->tm_hour;
    uint16_t minute = timeinfo->tm_min;
    uint16_t second = timeinfo->tm_sec;

    String baseFileName = mp4.getRecordingFileName();
    uint32_t fileCount = mp4.getRecordingFileCount();

    if (fileCount == 1) {
        snprintf(
            path,
            sizeof(path),
            "%s%s.mp4",
            fs.getRootPath(),
            baseFileName.c_str());
    } else {
        snprintf(
            path,
            sizeof(path),
            "%s%s_%lu.mp4",
            fs.getRootPath(),
            baseFileName.c_str(),
            (unsigned long)index);
    }

    Serial.print("Updating: ");
    Serial.println(path);

    char timeBuffer[64];

    snprintf(
        timeBuffer,
        sizeof(timeBuffer),
        "Close time: %04u-%02u-%02u %02u:%02u:%02u",
        year,
        month,
        day,
        hour,
        minute,
        second);

    Serial.println(timeBuffer);

    if (!fs.exists(path)) {
        Serial.println("ERROR: File not found");
        return;
    }

    int ret = fs.setLastModTime(
        path,
        year,
        month,
        day,
        hour,
        minute,
        second);

    if (ret == 0) {
        Serial.println("Timestamp updated successfully");
    } else {
        Serial.print("setLastModTime failed: ");
        Serial.println(ret);
    }
}
