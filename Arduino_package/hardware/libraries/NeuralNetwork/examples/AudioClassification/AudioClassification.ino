/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-neuralnework-face-audio-classification/
*/

#include "WiFi.h"
#include "StreamIO.h"
#include "NNAudioClassification.h"
#include "AudioClassList.h"

// NN audio classification requires 16KHz
AudioSetting configA(16000, 1, USE_AUDIO_AMIC);    // Sample rate, Channel count, Mic type
Audio audio;
NNAudioClassification audioNN;
StreamIO audioStreamerNN(1, 1);    // 1 Input Audio -> 1 Output Audio Classification

void setup()
{
    // Configure audio peripheral for audio data format
    audio.configAudio(configA);
    audio.begin();

    audioNN.configAudio(configA);
    audioNN.setResultCallback(ACPostProcess);
    audioNN.modelSelect(AUDIO_CLASSIFICATION, NA_MODEL, NA_MODEL, NA_MODEL, DEFAULT_YAMNET);
    audioNN.begin();

    // Configure StreamIO object to stream data from audio to audio classification
    audioStreamerNN.registerInput(audio);
    audioStreamerNN.registerOutput(audioNN);
    if (audioStreamerNN.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
}

void loop()
{
    // Do nothing
}

// User callback function
void ACPostProcess(std::vector<AudioClassificationResult> results)
{
    printf("No of Audio Detected = %d\r\n", audioNN.getResultCount());

    if (audioNN.getResultCount() > 0) {
        for (int i = 0; i < audioNN.getResultCount(); i++) {
            AudioClassificationResult audio_item = results[i];
            int class_id = (int)audio_item.classID();
            if (audioNames[class_id].filter) {
                int prob = audio_item.score();
                printf("%d class %d, score: %d, audio name: %s\r\n", i, class_id, prob, audioNames[class_id].audioName);
            }
        }
    }
}
