#include <Arduino.h>
#include "I2S.h"
#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_i2s.h"

#ifdef __cplusplus
}
#endif

I2SSetting::I2SSetting(uint32_t sampleRate)
{
    _sampleRate = sampleRate;
    switch (sampleRate) {
        case 8000: {
            _I2SParams.sample_rate = SR_8KHZ;
            break;
        }
        case 16000: {
            _I2SParams.sample_rate = SR_16KHZ;
            break;
        }
        case 32000: {
            _I2SParams.sample_rate = SR_32KHZ;
            break;
        }
        case 44100: {
            _I2SParams.sample_rate = SR_44p1KHZ;
            break;
        }
        default: {
            printf("\r\n[ERROR] Invalid I2S sample rate: %ld !\n", sampleRate);
            _sampleRate = 8000;
            _I2SParams.sample_rate = SR_8KHZ;
            break;
        }
    }
}

void I2S::configI2S(I2SSetting &config)
{
    _I2SParams = &(config._I2SParams);
}


I2S::I2S(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&i2s_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] i2s init failed\n");
        return;
    }
}

I2S::~I2S(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] i2s deinit failed\n");
    }
}

void I2S::begin(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (_I2SParams == NULL) {
        printf("\r\n[ERROR] Invalid i2s Setting configuration!\n");
        return;
    }

    mm_module_ctrl(_p_mmf_context, CMD_I2S_GET_PARAMS, (int)_I2SParams);
    _I2SParams->sample_rate = SR_16KHZ;
    _I2SParams->i2s_direction = I2S_TRX_BOTH;
    mm_module_ctrl(_p_mmf_context, CMD_I2S_SET_PARAMS, (int)_I2SParams);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 120);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    mm_module_ctrl(_p_mmf_context, CMD_I2S_APPLY, 0);
    _I2SStarted = 1;
}

void I2S::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    _I2SStarted = 0;
    mm_module_ctrl(_p_mmf_context, CMD_I2S_SET_TRX, 0);
}
