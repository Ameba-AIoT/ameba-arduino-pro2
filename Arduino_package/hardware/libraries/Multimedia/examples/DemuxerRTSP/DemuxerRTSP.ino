/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/RTSP%20Demuxer.html

 Default preset configurations for each video channel:
 Channel 0 : 1920 x 1080 30FPS H264
 Channel 1 : 1280 x 720  30FPS H264
 Channel 2 : 1280 x 720  30FPS MJPEG

 Default audio preset configurations:
 0 :  8kHz Mono Analog Mic
 1 : 16kHz Mono Analog Mic
 2 :  8kHz Mono Digital PDM Mic
 3 : 16kHz Mono Digital PDM Mic

 LOOP_MODE:
 0 : No looping of MP4 file
 1 : Looping of MP4 file
*/

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "Demuxer.h"
#include "RTSP.h"
#include "AudioStream.h"
#include "AudioEncoder.h"

#define CHANNEL   0
#define LOOP_MODE 1

VideoSetting config(CHANNEL);
AudioSetting configA(0);
RTSP rtsp;
Demuxer demuxer;
StreamIO demuxerRTSPStreamer(1, 1);    // 1 Input Demuxer -> 1 Output RTSP

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

const char* MP4FileName = "filename.mp4";

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

    demuxer.begin(MP4FileName, LOOP_MODE);

    // Configure RTSP with identical video and audio format information
    rtsp.configVideo(config);
    rtsp.configAudio(configA, CODEC_AAC);
    rtsp.begin();

    // Configure StreamIO object to stream data from recorded MP4 to RTSP
    demuxerRTSPStreamer.registerInput(demuxer);
    demuxerRTSPStreamer.registerOutput(rtsp);
    if (demuxerRTSPStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
}

void loop()
{
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();

        if (input.startsWith(String("pause"))) {
            demuxer.pause();
        } else if (input.startsWith(String("resume"))) {
            demuxer.resume();
        }
    }
}
