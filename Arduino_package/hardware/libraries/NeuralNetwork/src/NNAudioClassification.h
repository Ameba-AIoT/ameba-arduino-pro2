#ifndef __NN_AUDIOCLASSIFICATION_H__
#define __NN_AUDIOCLASSIFICATION_H__

#include "NNModelSelection.h"
#include "AudioStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "module_vipnn.h"

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

class AudioClassificationResult {
    friend class NNAudioClassification;
public:
    int classID(void);
    int score(void);

private:
    yamnet_res_t result = {0};
};

class NNAudioClassification: public NNModelSelection {
public:
    NNAudioClassification(void);
    ~NNAudioClassification(void);

    void configAudio(AudioSetting &config, uint16_t bitDepth = 16);
    void begin(void);
    void end(void);

    void setResultCallback(void (*ac_callback)(std::vector<AudioClassificationResult>));
    uint16_t getResultCount(void);
    AudioClassificationResult getResult(uint16_t index);
    std::vector<AudioClassificationResult> getResult(void);

private:
    static void ACResultCallback(void *p, void *img_param);
    static std::vector<AudioClassificationResult> audio_result_vector;
    static void (*AC_user_CB)(std::vector<AudioClassificationResult>);

    nn_data_param_t audio_nn_params = {0};
};
#endif
