/*
 This example shows the audio configuration of the I2S mic.
 Example guide:
 TBD
*/

#include "StreamIO.h"
#include "I2S.h"
#include "AudioStream.h"

#define PRESET 1

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

I2SSetting configI2S(16000);
I2S i2s;

AudioSetting configA(PRESET);
Audio audio;
StreamIO i2sAudio(1, 1);
StreamIO AudioI2S(1, 1);    // 1 Input Audio -> 1 Output Audio

void setup()
{
    Serial.begin(115200);

    // Configure I2S
    i2s.configI2S(configI2S);
    i2s.begin();

    // Configure audio peripheral for audio data format
    audio.configAudio(configA);
    audio.begin();

    i2sAudio.registerInput(i2s);
    i2sAudio.registerOutput(audio);
    i2sAudio.begin();

    AudioI2S.registerInput(audio);
    AudioI2S.registerOutput(i2s);
    AudioI2S.begin();
}

void loop()
{
}
