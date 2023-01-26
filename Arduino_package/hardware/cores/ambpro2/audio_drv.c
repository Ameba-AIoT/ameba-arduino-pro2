#include "audio_drv.h"
#include "module_audio.h"
#include "module_aac.h"

#define DEFAULT_AUDIO_SETTINGS 0

static audio_params_t audio_params = {
    .sample_rate = 0,
    .word_length = 0,
    .mic_gain    = 0,
    .dmic_l_gain    = 0,
    .dmic_r_gain    = 0,
    .use_mic_type   = 0,
    .channel     = 0,
    .ADC_gain = 0x64
    // ,
    //.enable_aec  = 0
};

static aac_params_t aac_params = {
    .sample_rate = 0,
    .channel = 0,
    .bit_length = 0,
    .output_format = 0,
    .mpeg_version = 0,
    .mem_total_size = 0,
    .mem_block_size = 0,
    .mem_frame_size = 0
};

mm_context_t* audioInit(void) {
    return mm_module_open(&audio_module);
}

mm_context_t* audioDeinit (mm_context_t *p) {
    return mm_module_close(p);
}

void audioClose(mm_context_t *p) {
    mm_module_ctrl(p, CMD_AUDIO_SET_TRX, 0);
}

void audioOpen(mm_context_t *p, int sample_rate, int word_length, int mic_gain, int dmic_l_gain, int dmic_r_gain, int use_mic_type, int channel, int enable_aec) {
    audio_params.sample_rate = sample_rate;
    audio_params.word_length = word_length;
    audio_params.mic_gain    = mic_gain;
    audio_params.dmic_l_gain    = dmic_l_gain;
    audio_params.dmic_r_gain    = dmic_r_gain;
    audio_params.use_mic_type   = use_mic_type;
    audio_params.channel     = channel;
    //audio_params.enable_aec  = enable_aec;
    (void)enable_aec; // TBD

    if (p) {
#if !DEFAULT_AUDIO_SETTINGS
        mm_module_ctrl(p, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
#endif
        mm_module_ctrl(p, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(p, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(p, CMD_AUDIO_APPLY, 0);
        //printf("audio opened");
    } else {
        //printf("audio open fail");
    }
}

mm_context_t* AACInit(void) { 
    return mm_module_open(&aac_module);
}

mm_context_t* AACDeinit(void *p) {
    return mm_module_close ((mm_context_t *)p);
}

void AACOpen(mm_context_t *p, uint32_t sample_rate, uint32_t channel, uint32_t bit_length, uint32_t output_format, uint32_t mpeg_version, uint32_t mem_total_size, uint32_t mem_block_size, uint32_t mem_frame_size) {
    AACSetParams(p->priv,sample_rate,channel,bit_length,output_format,mpeg_version,mem_total_size, mem_block_size, mem_frame_size);
    AACSetQueueLength(p);
    AACInitQueueItems(p);
    AACInitMemPool(p->priv);
    AACApply(p->priv);
}

void AACStop(mm_context_t *p) {
    mm_module_ctrl(p, CMD_AAC_STOP, 0);
}

int AACSetParams(void *p, uint32_t sample_rate, uint32_t channel, uint32_t bit_length, uint32_t output_format, uint32_t mpeg_version, uint32_t mem_total_size, uint32_t mem_block_size, uint32_t mem_frame_size) {
    aac_params.sample_rate = sample_rate;
    aac_params.channel = channel;
    aac_params.bit_length = bit_length;
    aac_params.output_format = output_format;
    aac_params.mpeg_version = mpeg_version;
    aac_params.mem_total_size = mem_total_size;
    aac_params.mem_block_size = mem_block_size;
    aac_params.mem_frame_size = mem_frame_size;
    return aac_control(p, CMD_AAC_SET_PARAMS, (int)&aac_params);
}

int AACSetQueueLength(void *p) {
    return mm_module_ctrl(p, MM_CMD_SET_QUEUE_LEN, 6);
}

int AACInitQueueItems(void *p) {
    return mm_module_ctrl(p, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
}

int AACInitMemPool(void *p) {
    return aac_control(p, CMD_AAC_INIT_MEM_POOL, 0);
}

int AACApply(void *p) {
    return aac_control(p, CMD_AAC_APPLY, 0);
}
