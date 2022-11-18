#include <Arduino.h>
#include "audio.h"

#define DEBUG 0

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n" fmt "\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

AudioRawClass::AudioRawClass(void) {
    audioData = NULL;
};
AudioRawClass::~AudioRawClass(){};

AACClass::AACClass(void) {
    AACData = NULL;
};
AACClass::~AACClass(){};

/**
  * @brief  Init audio module
  * @param  none
  * @retval none
  */
void AudioRawClass::init(void) {
    audioData = audioInit();
}

/**
  * @brief  deinit audio module
  * @param  none
  * @retval none
  */
void AudioRawClass::deinit(void) {
    audioDeInit(audioData);
}

/**
  * @brief  Open audio module, parameters can be adjust in audio.h
  * @param  none
  * @retval none
  */
void AudioRawClass::open(void) {
    int channel = AUDIO_CH;
    uint8_t use_mic_type        = AUDIO_MIC_TYPE;
    uint32_t enable_aec         = AUDIO_AEC_FLAG; 
    uint32_t sample_rate        = AUDIO_SAMPLERATE;
    uint32_t word_length        = AUDIO_WORD_LEN;
    audio_mic_gain mic_gain     = AUDIO_MIC_GAIN;
    audio_dmic_gain dmic_l_gain = AUDIO_DMIC_L_GAIN;
    audio_dmic_gain dmic_r_gain = AUDIO_DMIC_R_GAIN;

    open(audioData, sample_rate, word_length, mic_gain, dmic_l_gain, dmic_r_gain, use_mic_type, channel, enable_aec);
}

/**
  * @brief  Open the audio module
  * @param  p           : pointer to audio object 
            sample_rate : audio data sampling rate
            word_length : word length
            mic gain    : gain of the analog microphone
            dmic_l_gain : gain of the left digital microphone
            dmic_r_gain : gain of the right digital microphone
            use_mic_type: digital or analog microphone 
            channel     : channel name
            enable_aec  : enable or disable Acoustic Echo Cancelling
  * @retval none
  */
void AudioRawClass::open(mm_context_t *p, uint32_t sample_rate, uint32_t word_length, audio_mic_gain mic_gain, audio_dmic_gain dmic_l_gain, audio_dmic_gain dmic_r_gain, uint8_t use_mic_type, int channel, uint32_t enable_aec) {
    audioOpen(p, sample_rate, word_length, mic_gain, dmic_l_gain, dmic_r_gain, use_mic_type, channel, enable_aec);
}

/**
  * @brief  Close the audio module
  * @param  pointer to audio object 
  * @retval none
  */
void AudioRawClass::close(void) {
    audioClose(audioData);
}

/**
  * @brief  Get Audio module data pointer
  * @param  none
  * @retval pointer to Audio module
  */
mm_context_t *AudioRawClass::getIO(void) {
    if (audioData == NULL) {
        printf("Failed, please init audio first.\r\n");	
        return NULL;
    } else {
        return audioData;
    }
}

/**
  * @brief  Init AAC (Advanced Audio Codec) module as audio encoder
  * @param  none
  * @retval none
  */
void AACClass::init(void) {
    AACData = AACInit();
    AACOpen(AACData, AAC_SAMPLERATE, AAC_CH, AAC_BIT_LENGTH, AAC_OUTPUT_FORMAT, AAC_MPEG_VER, AAC_MEM_TOTAL_SIZE, AAC_MEM_BLOCK_SIZE, AAC_MEM_FRAME_SIZE);
}

/**
  * @brief  deinit AAC (Advanced Audio Codec) module
  * @param  none
  * @retval none
  */
void AACClass::deinit(void) {
    if (AACDeInit(AACData) == NULL) {
        CAMDBG("AAC deinit.\r\n");
    } else {
        CAMDBG("AAC need to be deinit.\r\n");
    }
}

/**
  * @brief  Stop AAC module while transmision is finished
  * @param  none
  * @retval none
  */
void AACClass::close(void) {
    AACStop(AACData);
}

/**
  * @brief  Get AAC module data pointer
  * @param  none
  * @retval none
  */
mm_context_t *AACClass::getIO(void) {
    if (AACData == NULL) {
        printf("[AAC] Failed, please init AAC first.");
        return NULL;
    } else {
        return AACData;
    }
}
