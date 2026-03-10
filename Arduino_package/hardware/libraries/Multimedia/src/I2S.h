#ifndef __I2SSTREAM_H__
#define __I2SSTREAM_H__

#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "audio_api.h"
#include "module_i2s.h"

#ifdef __cplusplus
}
#endif

class I2SSetting {
public:
    I2SSetting(uint32_t sampleRate = 16000);

    uint32_t _sampleRate = 8000;
    i2s_params_t _I2SParams = {
        .sample_rate = SR_8KHZ,
        .i2s_word_length = 16,
        .rx_word_length = 16,
        .tx_word_length = 16,
        .i2s_format = FORMAT_I2S,
        .i2s_role = I2S_MASTER,
        .i2s_ws_edge = WS_NEGATIVE_EDGE,
        .i2s_data_edge = NEGATIVE_EDGE,
        .rx_channel = I2S_LEFT_CHANNEL,
        .tx_channel = I2S_LEFT_CHANNEL,
        .i2s_direction = I2S_TRX_BOTH,
        .rx_byte_swap = 0,
        .tx_byte_swap = 0,
        .pin_group_num = 0,
    };
};

class I2S: public MMFModule {
public:
    I2S(void);
    ~I2S(void);

    void configI2S(I2SSetting& config);

    void begin(void);
    void end(void);

private:
    i2s_params_t* _I2SParams = NULL;
    uint8_t _I2SStarted = 0;
};

#endif
