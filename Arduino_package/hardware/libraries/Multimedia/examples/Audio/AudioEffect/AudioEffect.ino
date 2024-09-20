/*

 Example guide: https://www.amebaiot.com/en/amebapro2-arduino-audio-effects/
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
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output Audio

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;
int value;

void setup()
{
    Serial.begin(115200);

    while (status != WL_CONNECTED) {
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    // Configure audio peripheral for audio data format
    audio.configAudio(configA);

    // Modify the code below to enable the ASP algorithms and hear the effects
    // ASP algorithms are only effective at 8kHz and 16kHz sample rates

    // Noise suppression algorithm for microphone and speaker
    // Noise suppression algorithm can help reduce background noise level, but will introduce echo
    // Reduce the noise suppression level to reduce the echo effect
    // Noise suppression level can be adjusted from 0 to 12
    audio.configMicNS(0);    // Change to 1 to enable NS on microphone input

    // Automatic Gain Control algorithm for microphone and speaker
    // AGC can dynamically adjust the gain to maintain the audio loudness at a reference level
    // Reference loudness can be adjusted from 0 dBFS to -30 dBFS
    audio.configMicAGC(0);    // Change to 1 to enable AGC on microphone input
    audio.configSpkAGC(0);    // Change to 1 to enable AGC on speaker output
                              //    audio.configMicAGC(0, 30);   // Target loudness level of -30 dBFS
                              //    audio.configSpkAGC(0, 30);   // Target loudness level of -30 dBFS

    audio.begin();

    // Configure StreamIO object to stream data from audio mic input to audio speaker output
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(audio);
    audioStreamer.begin();

    delay(1000);
}

void loop()
{
    // Increasing boost level will increase mic sensitivity and background noise

    value = map(analogRead(A0), 0, 1020, 0, 3);
    audio.setAMicBoost(value);
    //    audio.setDMicBoost(value);
    delay(1000);
}
