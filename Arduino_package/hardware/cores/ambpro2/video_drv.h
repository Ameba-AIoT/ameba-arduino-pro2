#ifndef video_drv_h
#define video_drv_h

#include <stdint.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <diag.h>
#include "mmf2_module.h"

int cameraConfig(int enable, int w, int h, int bps, int snapshot, int preset);
int cameraConfigNew(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_snapshot, 
                        int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_snapshot, 
                        int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_snapshot, 
                        int v4_enable, int v4_w, int v4_h);

mm_context_t *cameraInit(void);

void cameraOpen(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode, int snapshot);

void cameraStart(void *p, int channel);

void cameraSnapshot(void *p, int channel);

void cameraSnapshotCB(mm_context_t *p);

int snapshot_cb(uint32_t jpeg_addr, uint32_t jpeg_len);

void snapshot_control_thread(void *param);

void cameraStopVideoStream(void *p, int channel);

mm_context_t *cameraDeInit(mm_context_t *);

void cameraSnapshot(void *p, int channel);

// Functions externed from module_video
extern void *video_create(void *parent);
extern void *video_destroy(void *p);
extern int video_control(void *p, int cmd, int arg);
extern int video_close(int ch);
extern void *video_del_item(void *p, void *d);
extern void *video_deinit(void);
extern void video_set_framerate(int fps);

#endif
