/*

 Example guide: https://www.amebaiot.com/en/amebapro2-arduino-audio-rtsp/
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "RTSP.h"

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

// Choose between using AAC or G711 audio encoder
AAC encoder;
// G711E encoder;

AudioSetting configA(1);
Audio audio;
RTSP rtsp;
StreamIO audioStreamer1(1, 1);    // 1 Input Audio -> 1 Output encoder
StreamIO audioStreamer2(1, 1);    // 1 Input encoder -> 1 Output RTSP

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();

    // Configure audio encoder
    // For G711 audio encoder, choose between u-law and a-law algorithm
    encoder.configAudio(configA);
    // encoder.configCodec(CODEC_G711_PCMU);
    // encoder.configCodec(CODEC_G711_PCMA);
    encoder.begin();

    // Configure RTSP with identical audio format information and codec
    rtsp.configAudio(configA, CODEC_AAC);
    // rtsp.configAudio(configA, CODEC_G711_PCMU);
    // rtsp.configAudio(configA, CODEC_G711_PCMA);
    rtsp.begin();

    audioStreamer1.registerInput(audio);
    audioStreamer1.registerOutput1(encoder);
    audioStreamer1.begin();

    audioStreamer2.registerInput(encoder);
    audioStreamer2.registerOutput(rtsp);
    audioStreamer2.begin();
}

void loop()
{
}
