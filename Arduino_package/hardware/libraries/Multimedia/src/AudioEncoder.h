#ifndef __AUDIOENCODER_H__
#define __AUDIOENCODER_H__

#include "VideoStream.h"
#include "AudioStream.h"

#include "faac.h"
#include "faaccfg.h"
#include "module_aac.h"
#include "module_g711.h"

class AAC:public MMFModule {
    public:
        AAC(void);
        ~AAC(void);

        void configAudio(AudioSetting& config);
        void begin(void);
        void end(void);

    private:
        aac_params_t _aacParams = {
            .sample_rate = 8000,
            .channel = 1,
            .bit_length = FAAC_INPUT_16BIT,
            .output_format = 1,
            .mpeg_version = MPEG4,
            .mem_total_size = 10 * 1024,
            .mem_block_size = 128,
            .mem_frame_size = 1024,
        };
};

class G711E:public MMFModule {
    public:
        G711E(void);
        ~G711E(void);

        void configAudio(AudioSetting& config);
        void configCodec(Audio_Codec_T codec);
        void begin(void);
        void end(void);

    private:
        g711_params_t _g711Params = {
            .codec_id = AV_CODEC_ID_PCMU,
            .buf_len  = 2048,
            .mode     = G711_ENCODE,
        };
};

#endif
