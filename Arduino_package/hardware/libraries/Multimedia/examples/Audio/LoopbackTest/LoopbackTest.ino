/*

 Example guide:

 */

#include "WiFi.h"
#include "StreamIO.h"
#include "AudioStream.h"

#define PRESET 0

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

AudioSetting configA(PRESET);
Audio audio;
StreamIO audioStreamer(1, 1);   // 1 Input Audio -> 1 Output Audio

void setup() {
    Serial.begin(115200);

    // Configure audio peripheral for audio data format
    audio.configAudio(configA);
    audio.begin();

    // Configure StreamIO object to stream data from audio mic input to audio speaker output
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(audio);
    audioStreamer.begin();
}

void loop() {
}
