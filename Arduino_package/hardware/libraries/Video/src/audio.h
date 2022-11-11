#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "audio_drv.h"
#include "avcodec.h"
#include "audio_api.h"
#include "faac.h"
#include "faaccfg.h"

#ifdef __cplusplus
}
#endif

#include "camera.h"

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

class AudioClass {
    public:
        AudioClass(void);
        ~AudioClass(void);

        void init(void);
        void deinit(void);
        void open(void);
        void open(mm_context_t *p, uint32_t sample_rate, uint32_t word_length, audio_mic_gain mic_gain, audio_dmic_gain dmic_l_gain, audio_dmic_gain dmic_r_gain, uint8_t use_mic_type, int channel, uint32_t enable_aec);
        void close(void);
        mm_context_t *getIO(void);

    private:
        mm_context_t *audioData;
};

class AACClass {
    public:
        AACClass(void);
        ~AACClass(void);

        void init(void);
        void deinit(void);
        void close(void);
        mm_context_t *getIO(void);

    private:
        mm_context_t *AACData;
};

#endif