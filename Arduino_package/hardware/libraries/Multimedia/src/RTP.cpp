#include <Arduino.h>
#include "RTP.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
extern mm_module_t rtp_module;

#ifdef __cplusplus
}
#endif

RTP::RTP(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&rtp_module);
    }
    if (_p_mmf_context == NULL) {
        printf("RTP init failed\r\n");
        return;
    }
}

RTP::~RTP(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("RTP deinit failed\r\n");
    }
}

void RTP::configPort(uint16_t port) {
    _rtpParams.port = port;
}

void RTP::begin(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    mm_module_ctrl(_p_mmf_context, CMD_RTP_SET_PARAMS, (int)&_rtpParams);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 6);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    mm_module_ctrl(_p_mmf_context, CMD_RTP_APPLY, 0);
    mm_module_ctrl(_p_mmf_context, CMD_RTP_STREAMING, 1);
}

void RTP::end(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    mm_module_ctrl(_p_mmf_context, CMD_RTP_STREAMING, 0);
}

uint16_t RTP::getPort(void) {
    return _rtpParams.port;
}

