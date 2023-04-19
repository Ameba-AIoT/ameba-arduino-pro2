/*

 Example guide:

 */

#include "WiFi.h"
#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "AudioDecoder.h"
#include "RTSP.h"
#include "RTP.h"

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

AudioSetting configA(0);
Audio audio;
AAC encoder;
AAD decoder;
RTSP rtsp;
RTP rtp;
StreamIO audioStreamer0(1, 1);   // 1 Input Audio -> 1 Output AAC
StreamIO audioStreamer1(1, 1);   // 1 Input Audio -> 1 Output AAC
StreamIO audioStreamer2(1, 1);   // 1 Input Audio -> 1 Output AAC
StreamIO audioStreamer3(1, 1);   // 1 Input Audio -> 1 Output AAC

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;
uint16_t value;

void setup() {
    Serial.begin(115200);

    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    audio.configAudio(configA);
    audio.configMicAEC(1);      // Enable echo cancellation to remove audio feedback from RTP stream
    audio.begin();

    encoder.configAudio(configA);
    encoder.begin();

    rtsp.configAudio(configA, CODEC_AAC);
    rtsp.begin();

    audioStreamer0.registerInput(audio);
    audioStreamer0.registerOutput(encoder);
    audioStreamer0.begin();

    audioStreamer1.registerInput(encoder);
    audioStreamer1.registerOutput(rtsp);
    audioStreamer1.begin();

    decoder.configAudio(configA);
    decoder.begin();

    rtp.begin();

    audioStreamer2.registerInput(rtp);
    audioStreamer2.registerOutput(decoder);
    audioStreamer2.begin();

    audioStreamer3.registerInput(decoder);
    audioStreamer3.registerOutput(audio);
    audioStreamer3.begin();
}

void loop() {
}
