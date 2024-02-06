#ifndef MP4_DRV_H
#define MP4_DRV_H

#include "mmf2_module.h"
#include "mp4_muxer.h"

#ifdef __cplusplus
extern "C" {
#endif

mm_context_t *mp4Init(void);

mm_context_t *mp4Deinit(mm_context_t *p);

int mp4SetParams(void *p, mp4_params_t *params);

int mp4SetLoopMode(void *p, int enable);

int mp4RecordingStart(void *p, mp4_params_t *params);

int mp4RecordingStop(void *p);

uint8_t mp4RecordingState(void *p);

// extern function
extern void *mp4_create(void *parent);
extern void *mp4_destroy(void *p);
extern int mp4_control(void *p, int cmd, int arg);
extern int mp4_handle(void *p, void *input, void *output);

#ifdef __cplusplus
}
#endif

#endif
