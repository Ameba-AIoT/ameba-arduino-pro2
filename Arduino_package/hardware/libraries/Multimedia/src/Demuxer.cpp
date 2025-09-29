#include <Arduino.h>
#include "Demuxer.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "demuxer_drv.h"

#ifdef __cplusplus
}
#endif

Demuxer::Demuxer(void)
{
}

Demuxer::~Demuxer(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (demuxerDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Demuxer deinit failed\n");
    }
}

void Demuxer::begin(const char* MP4FileName, uint32_t loopMode, uint32_t startTime)
{
    _p_mmf_context = demuxerInit();

    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need Demuxer init first\n");
    } else {
        demuxerOpen(_p_mmf_context, MP4FileName, MEDIA_STREAM_TYPE, loopMode, startTime);
        demuxerStart(_p_mmf_context);
    }
}

void Demuxer::pause()
{
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need Demuxer init first\n");
    } else {
        demuxerPause(_p_mmf_context);
    }
}

void Demuxer::resume()
{
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need Demuxer init first\n");
    } else {
        demuxerResume(_p_mmf_context);
    }
}

void Demuxer::end(void)
{
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need Demuxer init first\n");
    }
    demuxerDeinit(_p_mmf_context);
}
