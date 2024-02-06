#ifndef VIDEO_DRV_H
#define VIDEO_DRV_H

#include "mmf2_module.h"

typedef struct {
    int Brightness;
    int Contrast;
    int Saturation;
    int Sharpness;
    int LDC;
    int WDRMode;
    int WDRLevel;
    int ExposureMode;
    int ExposureTime;
    int AWB;
    int RedBalance;
    int BlueBalance;
    int AEGain;
    int GrayMode;
    int PowerLineFreq;
    int DayNightMode;
} isp_control;

void ISPControlReset(void);

int cameraConfig(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_snapshot,
                 int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_snapshot,
                 int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_snapshot,
                 int v4_enable, int v4_w, int v4_h);

mm_context_t *cameraInit(void);

void cameraOpen(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int rc_mode, int snapshot, int jpeg_qlevel, int video_rotation);

void cameraOpenNN(mm_context_t *p, void *p_priv, int stream_id, int type, int res, int w, int h, int bps, int fps, int gop, int direct_output);

void cameraSetQLen(mm_context_t *p, int length);

void cameraSetQItem(mm_context_t *p);

void cameraStart(void *p, int channel);

void cameraYUV(void *p);

void cameraSnapshot(void *p, int channel);

void cameraSnapshotRegCB(mm_context_t *p, int (*ssCB)(uint32_t, uint32_t));

void cameraStopVideoStream(void *p, int channel);

mm_context_t *cameraDeinit(mm_context_t *);

// Functions externed from module_video
extern void *video_create(void *parent);
extern void *video_destroy(void *p);
extern int video_control(void *p, int cmd, int arg);
extern int video_close(int ch);
extern void *video_del_item(void *p, void *d);
extern void *video_deinit(void);
extern void video_set_framerate(int fps);

#endif
