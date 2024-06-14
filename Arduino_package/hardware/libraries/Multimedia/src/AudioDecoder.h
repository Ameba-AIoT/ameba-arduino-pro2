#ifndef __AUDIODECODER_H__
#define __AUDIODECODER_H__

#include "VideoStream.h"
#include "AudioStream.h"

#include "faac.h"
#include "faaccfg.h"
#include "module_aad.h"
#include "module_g711.h"

class AAD: public MMFModule {
public:
    AAD(void);
    ~AAD(void);

    void configAudio(AudioSetting& config);
    void begin(void);
    void end(void);

private:
    aad_params_t _aadParams = {
        .trans_type = AAD_TYPE_RTP_RAW,
        .object_type = AAD_AOT_LC,
        .sample_rate = 8000,
        .channel = 1,
    };
};

class G711D: public MMFModule {
public:
    G711D(void);
    ~G711D(void);

    void configAudio(AudioSetting& config);
    void configCodec(Audio_Codec_T codec);
    void begin(void);
    void end(void);

private:
    g711_params_t _g711Params = {
        .codec_id = AV_CODEC_ID_PCMU,
        .buf_len = 2048,
        .mode = G711_DECODE,
    };
};

#endif
