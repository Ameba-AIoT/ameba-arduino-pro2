/*
This example acts as a Security System based on Motion Detection, which would start to record a
 30 seconds long MP4 video every time motion is detected. (Alarm function could be initiated as well, but on default disabled)

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-motion-mp4/
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

#define CHANNELVID 0    // Channel for RTSP streaming & MP4 recording
#define CHANNELMD  3    // RGB format video for motion detection only available on channel 3

// Pin Definition
#define GREEN_LED 4
// #define BUZZER_PIN 7

AudioSetting configA(0);
VideoSetting configV(VIDEO_FHD, CAM_FPS, VIDEO_H264, 0);
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);    // Low resolution RGB video for motion detection
Audio audio;
AAC aac;
MP4Recording mp4;
RTSP rtsp;
MotionDetection MD;
StreamIO videoStreamerMD(1, 1);    // 1 Input RGB Video -> 1 Output MD
StreamIO audioStreamer(1, 1);      // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 2);      // 2 Input Video + Audio -> 2 Output MP4 + RTSP

int recordingCount = 0;

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    // GPIO Initialization
    pinMode(GREEN_LED, OUTPUT);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNELVID, configV);
    Camera.configVideoChannel(CHANNELMD, configMD);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure RTSP with identical video format information and enable audio streaming
    rtsp.configVideo(configV);
    rtsp.configAudio(configA, CODEC_AAC);
    rtsp.begin();

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configMD);
    MD.begin();
    MD.setDetectionMask(mask);

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(configV);
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixStreamer.registerInput1(Camera.getStream(CHANNELVID));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput1(rtsp);
    avMixStreamer.registerOutput2(mp4);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNELVID);

    // Configure StreamIO object to stream data from low res video channel to motion detection
    videoStreamerMD.registerInput(Camera.getStream(CHANNELMD));
    videoStreamerMD.setStackSize();
    videoStreamerMD.registerOutput(MD);
    if (videoStreamerMD.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from low resolution video channel
    Camera.channelBegin(CHANNELMD);

    // Configure OSD for drawing on video stream
    OSD.configVideo(CHANNELVID, configV);
    OSD.begin();
}

void loop()
{
    // Motion detection results is expressed as an array
    // With 0 or 1 in each element indicating presence of motion
    // Iterate through all elements to check for motion
    // and calculate largest rectangle containing motion
    std::vector<MotionDetectionResult> md_results = MD.getResult();

    OSD.createBitmap(CHANNELVID);
    if (MD.getResultCount() > 0) {
        digitalWrite(GREEN_LED, HIGH);

        for (uint16_t i = 0; i < MD.getResultCount(); i++) {
            MotionDetectionResult result = md_results[i];
            int xmin = (int)(result.xMin() * configV.width());
            int xmax = (int)(result.xMax() * configV.width());
            int ymin = (int)(result.yMin() * configV.height());
            int ymax = (int)(result.yMax() * configV.height());
            // printf("%d:\t%d %d %d %d\n\r", i, xmin, xmax, ymin, ymax);
            OSD.drawRect(CHANNELVID, xmin, ymin, xmax, ymax, 3, COLOR_GREEN);
        }
        if (!mp4.getRecordingState()) {    // if not MP4 not in recording mode
            recordingCount++;
            mp4.setRecordingFileName("MotionDetection" + String(recordingCount));
            mp4.begin();
            // tone(BUZZER_PIN, 1000, 500);
        }
    } else {
        digitalWrite(GREEN_LED, LOW);    // GREEN LED turn off when no motion detected
    }

    OSD.update(CHANNELVID);
    delay(100);
}
