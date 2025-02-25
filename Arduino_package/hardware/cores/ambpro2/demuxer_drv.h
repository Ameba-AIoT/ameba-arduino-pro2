#ifndef DEMUXER_DRV_H
#define DEMUXER_DRV_H

#include "mmf2_module.h"

mm_context_t *demuxerInit(void);
mm_context_t *demuxerDeinit(mm_context_t *p);
void demuxerOpen(mm_context_t *p, const char *file_name, uint8_t stream_type, uint32_t loop_mode, uint32_t start_time);
void demuxerStart(mm_context_t *p);
void demuxerPause(mm_context_t *p);
void demuxerResume(mm_context_t *p);

#endif
