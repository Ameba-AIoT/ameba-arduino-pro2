#ifndef camera_drv_h
#define camera_drv_h

#include <stdint.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <diag.h>
#include "mmf2_module.h"

int cameraConfig(int enable, int w, int h, int bps, int snapshot, int preset);

mm_context_t *cameraInit(void);

void cameraOpen(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode);

void cameraStart(void *p, int channel);

void cameraStopVideoStream(void *p, int channel);

mm_context_t *cameraDeInit(mm_context_t *);

// Functions externed from module_video
extern void *video_create(void *parent);
extern void *video_destroy(void *p);
extern int video_control(void *p, int cmd, int arg);
extern int video_close(int ch);
extern void *video_del_item(void *p, void *d);
extern void *video_deinit(void);

#endif
