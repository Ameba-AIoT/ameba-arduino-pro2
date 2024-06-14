#ifndef RTSP_DRV_H
#define RTSP_DRV_H

#include "mmf2_module.h"

mm_context_t *RTSPInit(void);

mm_context_t *RTSPDeinit(mm_context_t *p);

int RTSPSelectStream(void *p, int arg);

int RTSPSetApply(void *p);

void RTSPSetStreaming(void *p, int arg);

int RTSPSetParamsVideo(void *p, uint32_t RTSP_fps, uint32_t RTSP_bps, uint32_t AV_Codec);

int RTSPSetParamsAudio(void *p, uint32_t channel, uint32_t sample_rate, uint32_t AV_Codec);

int RTSPGetPort(void *p);

// extern function
extern void *rtsp2_create(void *parent);
extern void *rtsp2_destroy(void *p);
extern int rtsp2_control(void *p, int cmd, int arg);
extern int rtsp2_handle(void *p, void *input, void *output);

#endif
