/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-rtsp/
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "RTSP.h"

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1280 x 720  30FPS MJPEG

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

VideoSetting configV1(VIDEO_FHD, CAM_FPS, VIDEO_H264, 0);
VideoSetting configV2(VIDEO_HD, CAM_FPS, VIDEO_H264, 0);
AudioSetting configA(0);
Audio audio;
AAC aac;
RTSP rtsp1;
RTSP rtsp2;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(3, 2);    // 3 Input Video1 + Video2 + Audio -> 2 Output RTSP1 + RTSP2

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure both camera video channels with corresponding video format information
    // Adjust the bitrate based on your WiFi network quality
    // configV1.setBitrate(2 * 1024 * 1024);     // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    // configV2.setBitrate(2 * 1024 * 1024);     // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    Camera.configVideoChannel(0, configV1);
    Camera.configVideoChannel(1, configV2);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure both RTSP with corresponding video format information
    rtsp1.configVideo(configV1);
    rtsp1.configAudio(configA, CODEC_AAC);
    rtsp1.begin();

    rtsp2.configVideo(configV2);
    rtsp2.configAudio(configA, CODEC_AAC);
    rtsp2.begin();

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channels and AAC encoder to rtsp outputs
    avMixStreamer.registerInput1(Camera.getStream(0));
    avMixStreamer.registerInput2(Camera.getStream(1));
    avMixStreamer.registerInput3(aac);
    avMixStreamer.registerOutput1(rtsp1);
    avMixStreamer.registerOutput2(rtsp2);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channels
    Camera.channelBegin(0);
    Camera.channelBegin(1);

    delay(1000);
    printInfo();
}

void loop()
{
    // do nothing
}

void printInfo(void)
{
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");

    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP Information -");
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp1.printInfo();

    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp2.printInfo();

    Serial.println("- Audio Information -");
    audio.printInfo();
}
