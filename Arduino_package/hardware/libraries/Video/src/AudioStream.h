#ifndef __AUDIOSTREAM_H__
#define __AUDIOSTREAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "audio_api.h"
#include "faac.h"
#include "faaccfg.h"
#include "module_audio.h"

#ifdef __cplusplus
}
#endif

#include "VideoStream.h"

// define Audio parameters
// reference to audio_api.h
#define AUDIO_SAMPLERATE    ASR_8KHZ
#define AUDIO_WORD_LEN      WL_16BIT
#define AUDIO_MIC_GAIN      MIC_0DB
#define AUDIO_DMIC_L_GAIN   DMIC_BOOST_24DB
#define AUDIO_DMIC_R_GAIN   DMIC_BOOST_24DB
#define AUDIO_MIC_TYPE      USE_AUDIO_AMIC
#define AUDIO_CH            1
#define AUDIO_AEC_FLAG      0               // Acoustic Echo Cancellation
// define AAC parameters
#define AAC_SAMPLERATE      8000
#define AAC_CH              1
#define AAC_BIT_LENGTH      FAAC_INPUT_16BIT
#define AAC_OUTPUT_FORMAT   1
#define AAC_MPEG_VER        MPEG4
#define AAC_MEM_TOTAL_SIZE  10 * 1024
#define AAC_MEM_BLOCK_SIZE  128
#define AAC_MEM_FRAME_SIZE  1024

class AudioSetting {
    friend class Audio;

    public:
        AudioSetting(uint8_t preset = 0);
        int8_t _preset = -1;

    private:
};

class Audio:public MMFModule {
    public:
        Audio(void);
        ~Audio(void);

        void configAudio(AudioSetting& config);
        void begin(void);
        void begin(mm_context_t *p, uint32_t sample_rate, uint32_t word_length, audio_mic_gain mic_gain, audio_dmic_gain dmic_l_gain, audio_dmic_gain dmic_r_gain, uint8_t use_mic_type, int channel, uint32_t enable_aec);
        void end(void);
        void printInfo(void);

        String micTypeArray[4] = {"USE_AUDIO_AMIC", "USE_AUDIO_LEFT_DMIC", "USE_AUDIO_RIGHT_DMIC", "USE_AUDIO_STEREO_DMIC"};
        String sampleRateArray[7] = {"8kHz", "16kHz", "32kHz", "44.1kHz", "88.2kHz", "96kHz"};
        String wordLengthArray[2] = {"16 bit", "24 bit"};
        String micGainArray[4] = {"0dB", "20dB", "30dB", "40dB"};
        String dMicBoostArray[4] = {"0dB", "12dB", "24dB", "36dB"};
    private:
};

class AAC:public MMFModule {
    public:
        AAC(void);
        ~AAC(void);

        void configAudio(AudioSetting& config);
        void begin(void);
        void end(void);
        void printInfo(void);

        String AACBitLengthArray[5] = {"0 bit", "16 bit", "24 bit", "32 bit", "Float"};
        String AACMpegVerArray[2] = {"MPEG4", "MPEG2"};
    private:
};

#endif
