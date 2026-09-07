/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/MP4%20Recording.html
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

#define TOTAL_FILES_1 1
#define TOTAL_FILES_2 1
#define RECORDING_DURATION_S_1 15
#define RECORDING_DURATION_S_2 30

volatile uint32_t fileCloseCount1 = 0;
volatile uint32_t fileCloseCount2 = 0;

volatile unsigned long fileCloseTimestamps1[TOTAL_FILES_1];
volatile unsigned long fileCloseTimestamps2[TOTAL_FILES_2];

bool timestampsWritten1 = false;
bool timestampsWritten2 = false;
bool fsEnded = false;

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
    mp4_1.setRecordingDuration(RECORDING_DURATION_S_1);
    mp4_1.setRecordingFileCount(TOTAL_FILES_1);
    mp4_1.setRecordingFileName("TestRecordingAudioVideo1");
    mp4_1.setRecordingStopCallback(MP4FileClosedCb1);

    mp4_2.configVideo(configV2);
    mp4_2.configAudio(configA, CODEC_AAC);
    mp4_2.setRecordingDuration(RECORDING_DURATION_S_2);
    mp4_2.setRecordingFileCount(TOTAL_FILES_2);
    mp4_2.setRecordingFileName("TestRecordingAudioVideo2");
    mp4_2.setRecordingStopCallback(MP4FileClosedCb2);

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
    if ((fileCloseCount1 >= TOTAL_FILES_1) && (mp4_1.getRecordingState() == 0) && (timestampsWritten1 == false)) {

        Serial.println();
        Serial.println("Updating timestamps (recording 1)...");

        for (uint32_t i = 0; i < TOTAL_FILES_1; i++) {
            updateFileTimestamp(mp4_1, path1, i, fileCloseTimestamps1[i]);
        }

        timestampsWritten1 = true;
    }

    // Update last modified time for recording 2 after it stops
    if ((fileCloseCount2 >= TOTAL_FILES_2) && (mp4_2.getRecordingState() == 0) && (timestampsWritten2 == false)) {

        Serial.println();
        Serial.println("Updating timestamps (recording 2)...");

        for (uint32_t i = 0; i < TOTAL_FILES_2; i++) {
            updateFileTimestamp(mp4_2, path2, i, fileCloseTimestamps1[i]);
        }

        timestampsWritten2 = true;
    }

    // Unmount the SD card once both recordings' timestamps are updated
    if ((timestampsWritten1 == true) && (timestampsWritten2 == true) && (fsEnded == false)) {

        fs.end();
        fsEnded = true;
    }

    delay(20);
}

void printInfo(void)
{
    Serial.println(" ");
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

int MP4FileClosedCb1(void *param)
{
    uint32_t index = fileCloseCount1;

    if (index < TOTAL_FILES_1) {

        // Capture NTP-synchronized clock at actual MP4 stop event
        fileCloseTimestamps1[index] = timeClient.getEpochTime();

        fileCloseCount1 = index + 1;
    }

    return 0;
}

int MP4FileClosedCb2(void *param)
{
    uint32_t index = fileCloseCount2;

    if (index < TOTAL_FILES_2) {

        // Capture NTP-synchronized clock at actual MP4 stop event
        fileCloseTimestamps2[index] = timeClient.getEpochTime();

        fileCloseCount2 = index + 1;
    }

    return 0;
}

void updateFileTimestamp(MP4Recording &recorder, char *path, uint32_t index, unsigned long epoch)
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

    String baseFileName = recorder.getRecordingFileName();
    uint32_t fileCount = recorder.getRecordingFileCount();

    if (fileCount == 1) {
        snprintf(
            path,
            128,
            "%s%s.mp4",
            fs.getRootPath(),
            baseFileName.c_str()
        );
    } else {
        snprintf(
            path,
            128,
            "%s%s_%lu.mp4",
            fs.getRootPath(),
            baseFileName.c_str(),
            (unsigned long)index
        );
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
