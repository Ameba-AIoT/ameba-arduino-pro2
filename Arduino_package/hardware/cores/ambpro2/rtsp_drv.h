#ifndef rtsp_drv_h
#define rtsp_drv_h

#include <stdint.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <diag.h>
#include "mmf2_module.h"

mm_context_t* RTSPInit(void);

int RTSPSelectStream(void *p, int arg);

int RTSPSetApply(void *p);

void RTSPSetStreaming(void *p, int arg);

int RTSPSetParamsVideo(void *p, uint32_t RTSP_fps, uint32_t RTSP_bps, uint32_t AV_Codec);

int RTSPSetParamsAudio(void *p, uint32_t channel, uint32_t sample_rate, uint32_t AV_Codec);

mm_context_t* RTSPDeInit(void *p);

int RTSPGetPort(void *p);

// extern function
extern void *rtsp2_create (void *parent);
extern void *rtsp2_destroy(void *p);
extern int rtsp2_control(void *p, int cmd, int arg);
extern int rtsp2_handle(void *p, void *input, void *output);

#endif
