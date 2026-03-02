/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/MP4%20Recording%20with%20MP3%20Prompts.html
*/

#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "AmebaFatFS.h"

#define CHANNEL 0

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

VideoSetting configV(CHANNEL);
AudioSetting configA(0);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);    // 2 Input Video + Audio -> 1 Output MP4
AmebaFatFS fs;

#define BUTTON_PIN 5
#define INTERVAL   1000

String rec_start = "rec_start.mp3";
String rec_end = "rec_end.mp3";
bool buttonState = false;
int lastRecordingState = -1;    // store previous state
bool buttonPressed = false;     // flag for pre-start message

void setup()
{
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT);

    if (fs.begin() != 0) {
        Serial.println("FATFS mount failed!");
    }

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, configV);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);

    // Configure AAC audio encoder
    aac.configAudio(configA);

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(configV);
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(10);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingAudioVideo");

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);

    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixStreamer.registerInput1(Camera.getStream(CHANNEL));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput(mp4);

    Serial.println("Press button to start recording...");
}

void loop()
{
    buttonState = digitalRead(BUTTON_PIN);
    int currentState = mp4.getRecordingState();

    // Button pressed, recording started
    if (buttonState == HIGH) {
        buttonPressed = true;
        if (currentState == 0) {
            playPrompt(rec_start);
            startRecording();
        }
    }

    if (currentState != lastRecordingState) {
        if (currentState == 1) {
            Serial.println("MP4 recording started.");
            // buttonPressed = false;
        } else if (currentState == 0 && lastRecordingState == 1) {
            stopRecording();
        }
        lastRecordingState = currentState;
    }

    if (buttonState == LOW) {
        buttonPressed = false;    // ready for next press
    }
    delay(10);
}

void playPrompt(const String& name)
{
    File file = fs.open(String(fs.getRootPath()) + name, MP3);
    file.playMp3();
    file.close();
}

void startRecording(void)
{
    audio.begin();
    aac.begin();

    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    Camera.channelBegin(CHANNEL);
    mp4.begin();
    Serial.println("Start recording...");
}

void stopRecording()
{
    mp4.end();
    avMixStreamer.end();
    audioStreamer.end();
    aac.end();
    audio.end();
    Camera.channelEnd(CHANNEL);

    playPrompt(rec_end);
    Serial.println("MP4 recording ended.");
}

void printInfo(void)
{
    Serial.println(" ");
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

    Serial.println("- Audio Information -");
    audio.printInfo();
    Serial.println("- MP4 Recording Information -");
    mp4.printInfo();
}
