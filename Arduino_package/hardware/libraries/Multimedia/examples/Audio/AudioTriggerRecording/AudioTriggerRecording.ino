/*
 This example demonstrates the trigger of MP4 recording based on sound detection level of microphone.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/Audio/Audio%20Trigger%20Recording.html
*/

#include "WiFi.h"
#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"

#define CHANNEL 0

#define TRIGGER_VOL 7000

// Define States
enum AppState {
    STATE_LISTENING,
    STATE_RECORDING,
    STATE_SAVING
};

AppState currentState = STATE_LISTENING;

#define PRESET 0

int recordingCounter = 1;

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic
VideoSetting configV(CHANNEL);
AudioSetting configA(PRESET);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output Audio
StreamIO audioToAAC(1, 1);
StreamIO avMixStreamer(2, 1);    // 2 Input Video + Audio -> 1 Output MP4

void setup()
{
    Serial.begin(115200);

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, configV);
    Camera.videoInit();

    // Configure audio peripheral for audio data format
    audio.configAudio(configA);

    // Configure AAC audio encoder
    aac.configAudio(configA);

    // Configure MP4 recording settings
    mp4.configVideo(configV);
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(5);
    mp4.setRecordingFileCount(1);

    // Configure StreamIO object to stream data from audio mic input to audio speaker output
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(audio);

    audioToAAC.registerInput(audio);
    audioToAAC.registerOutput(aac);

    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixStreamer.registerInput1(Camera.getStream(CHANNEL));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput(mp4);

    audio.begin();
}

void loop()
{
    if (currentState == STATE_LISTENING) {
        doListening();
    } else if (currentState == STATE_RECORDING) {
        doRecording();
    }
}

void doListening()
{
    Serial.println("[State] Listening...");

    if (audioStreamer.begin() != 0) {
        Serial.println("Error starting audioStreamer");
    }

    while (currentState == STATE_LISTENING) {
        delay(100);    // To avoid flooding the Serial monitor

        int currentVol = audio.micLevel();

        static int count = 0;
        if (count++ > 10) {
            Serial.print("Mic Level: ");
            Serial.println(currentVol);
            count = 0;
        }

        if (currentVol > TRIGGER_VOL) {
            Serial.print("Mic Level: ");
            Serial.println(currentVol);
            Serial.println(">>> TRIGGERED <<<");
            currentState = STATE_RECORDING;
        }
    }

    audioStreamer.end();

    Serial.println("[State] Listening Stopped.");
}

void doRecording(void)
{
    Serial.println("[State] Recording Setup");

    char filename[32];    // Create a buffer to hold the name

    snprintf(filename, sizeof(filename), "Recording_%d", recordingCounter);

    mp4.setRecordingFileName(filename);

    aac.begin();
    audioToAAC.begin();

    Camera.channelBegin(CHANNEL);

    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO avMixStreamer link start failed");
    }

    mp4.begin();

    while (mp4.getRecordingState() == 1) {
        // do nothing
        delay(100);
    }

    Serial.println("[State] Recording Done");

    mp4.end();
    avMixStreamer.end();

    Camera.channelEnd(CHANNEL);

    audioToAAC.end();
    aac.end();

    recordingCounter++;

    // Reset State
    currentState = STATE_LISTENING;
    Serial.println("[State] Returning to Listen Mode");
    delay(1000);
}
