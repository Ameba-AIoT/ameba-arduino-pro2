/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-video-rtsp/
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "Videostream.h"
#include "AudioStream.h"
#include "RTSP.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1920 x 1080 30FPS MJPEG

VideoSetting configV(CHANNEL);
Audio audio;
AAC aac;
RTSP rtsp;
StreamIO audioStreamer(1, 1);   // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);   // 2 Input Video + Audio -> 1 Output RTSP

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;

void setup() {
    Serial.begin(115200);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, configV);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.begin();
    // Configure AAC audio encoder
    aac.begin();

    // Configure RTSP with identical video format information and enable audio streaming
    rtsp.enableAudio();
    rtsp.configVideo(configV);
    rtsp.begin();

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channel and AAC encoder to rtsp output
    avMixStreamer.registerInput1(Camera.getStream(CHANNEL));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput(rtsp);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);

    delay(1000);
    printInfo();
}

void loop() {
    // Do nothing
}

void printInfo(void) {
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP -");
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp.printInfo();

    Serial.println("- Audio -");
    audio.printInfo();
    Serial.println("- AAC -");
    aac.printInfo();
}
