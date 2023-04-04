/*

 Example guide:

 */

#include "WiFi.h"
#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioDecoder.h"
#include "RTP.h"

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

// Choose between using AAC or G711 audio decoder
AAD decoder;
//G711E decoder;

AudioSetting configA(0);
Audio audio;
RTP rtp;
StreamIO audioStreamer1(1, 1);   // 1 Input RTP -> 1 Output decoder
StreamIO audioStreamer2(1, 1);   // 1 Input decoder -> 1 Output Audio

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;

void setup() {
    Serial.begin(115200);

    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();

    // Configure audio decoder
    // For G711 audio decoder, choose between u-law and a-law algorithm
    decoder.configAudio(configA);
//    decoder.configCodec(CODEC_G711_PCMU);
//    decoder.configCodec(CODEC_G711_PCMA);
    decoder.begin();

    rtp.begin();

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer1.registerInput(rtp);
    audioStreamer1.registerOutput(decoder);
    audioStreamer1.begin();

    audioStreamer2.registerInput(decoder);
    audioStreamer2.registerOutput(audio);
    audioStreamer2.begin();
}

void loop() {
}
