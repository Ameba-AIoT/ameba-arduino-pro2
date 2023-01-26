#include <Arduino.h>
#include "AudioStream.h"
#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "audio_drv.h"

#ifdef __cplusplus
}
#endif

AudioSetting::AudioSetting(uint8_t preset) {
    switch (preset) {
        case 0: {
            break;
        }
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        default: {
            printf("Invalid AudioSetting preset!\r\n");
            return;
            break;
        }
    }
    _preset = preset;
}

Audio::Audio(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = audioInit();
    }
    if (_p_mmf_context == NULL) {
        printf("Audio init failed\r\n");
        return;
    }
}

Audio::~Audio(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (audioDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("Audio deinit failed\r\n");
    }
}

void Audio::configAudio(AudioSetting& config) {
    //TBD
}

void Audio::begin(void) {
    if (_p_mmf_context == NULL) {
        printf("Need Audio init first\r\n");
        return;
    }
    int channel = AUDIO_CH;
    uint8_t use_mic_type        = AUDIO_MIC_TYPE;
    uint32_t enable_aec         = AUDIO_AEC_FLAG; 
    uint32_t sample_rate        = AUDIO_SAMPLERATE;
    uint32_t word_length        = AUDIO_WORD_LEN;
    audio_mic_gain mic_gain     = AUDIO_MIC_GAIN;
    audio_dmic_gain dmic_l_gain = AUDIO_DMIC_L_GAIN;
    audio_dmic_gain dmic_r_gain = AUDIO_DMIC_R_GAIN;

    begin(_p_mmf_context, sample_rate, word_length, mic_gain, dmic_l_gain, dmic_r_gain, use_mic_type, channel, enable_aec);
}

void Audio::begin(mm_context_t *p, uint32_t sample_rate, uint32_t word_length, audio_mic_gain mic_gain, audio_dmic_gain dmic_l_gain, audio_dmic_gain dmic_r_gain, uint8_t use_mic_type, int channel, uint32_t enable_aec) {
    audioOpen(p, sample_rate, word_length, mic_gain, dmic_l_gain, dmic_r_gain, use_mic_type, channel, enable_aec);
}

void Audio::end(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    audioClose(_p_mmf_context);
}

void Audio::printInfo(void) {
    uint8_t use_mic_type        = AUDIO_MIC_TYPE;
    uint32_t sample_rate        = AUDIO_SAMPLERATE;
    uint32_t word_length        = AUDIO_WORD_LEN;
    audio_mic_gain mic_gain     = AUDIO_MIC_GAIN;
    audio_dmic_gain dmic_l_gain = AUDIO_DMIC_L_GAIN;
    audio_dmic_gain dmic_r_gain = AUDIO_DMIC_R_GAIN;

    printf("Mic type: %s\r\n", micTypeArray[use_mic_type].c_str());
    if (sample_rate == ASR_8KHZ) {
        printf("Sample rate: 8000 Hz\r\n");
    }
    else if (sample_rate == ASR_16KHZ) {
        printf("Sample rate: 16000 Hz\r\n");
    }
    else if (sample_rate == ASR_32KHZ) {
        printf("Sample rate: 32000 Hz\r\n");
    }
    else if (sample_rate == ASR_44p1KHZ) {
        printf("Sample rate: 44100 Hz\r\n");
    }
    else if (sample_rate == ASR_48KHZ) {
        printf("Sample rate: 48000 Hz\r\n");
    }
    else if (sample_rate == ASR_88p2KHZ) {
        printf("Sample rate: 88200 Hz\r\n");
    }
    else if (sample_rate == ASR_96KHZ) {
        printf("Sample rate: 96000 Hz\r\n");
    }
    printf("Word length: %s\r\n", wordLengthArray[word_length].c_str());
    printf("Mic gain: %s\r\n", micGainArray[mic_gain].c_str());
    printf("dmic left gain: %s\r\n", dMicBoostArray[dmic_l_gain].c_str());
    printf("dmic right gain: %s\r\n",dMicBoostArray[dmic_r_gain].c_str());
    printf("\r\n");
}


AAC::AAC(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = AACInit();
    }
    if (_p_mmf_context == NULL) {
        printf("AAC init failed\r\n");
        return;
    }
}

AAC::~AAC(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (AACDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("AAC deinit failed\r\n");
    }
}

void AAC::configAudio(AudioSetting& config) {
    //TBD
}

void AAC::begin(void) {
    AACOpen(_p_mmf_context, AAC_SAMPLERATE, AAC_CH, AAC_BIT_LENGTH, AAC_OUTPUT_FORMAT, AAC_MPEG_VER, AAC_MEM_TOTAL_SIZE, AAC_MEM_BLOCK_SIZE, AAC_MEM_FRAME_SIZE);
}

void AAC::end(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    AACStop(_p_mmf_context);
}

void AAC::printInfo(void) {
    printf("Sample rate: %d Hz\r\n", AAC_SAMPLERATE);
    printf("AAC Bit Length: %s\r\n", AACBitLengthArray[AAC_BIT_LENGTH].c_str());
    printf("MPEG version: %s\r\n", AACMpegVerArray[AAC_MPEG_VER].c_str());
    printf("Total AAC memory size: %d\r\n", AAC_MEM_TOTAL_SIZE);
    printf("Total AAC memory block size: %d\r\n", AAC_MEM_BLOCK_SIZE);
    printf("Total AAC memory frame size: %d\r\n", AAC_MEM_FRAME_SIZE);
    printf("\r\n");
}
