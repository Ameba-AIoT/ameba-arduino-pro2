#ifndef FILESAVER_H
#define FILESAVER_H

#include "mmf2_module.h"
#include "module_filesaver.h"
#include "fatfs_sdcard_api.h"

mm_context_t *filesaver_Init(void);
mm_context_t *filesaver_Deinit(mm_context_t *p);

int filesaver_SetParams(mm_context_t *p, filesaver_params_t *params);
int filesaver_SetTypeHandler(mm_context_t *p, void (*fsCB)(char *, uint32_t, uint32_t));

int filesaver_Apply(mm_context_t *p);
int filesaver_SetFilePath(mm_context_t *p, const char *filename);

// int filesaver_cb(void);

#endif
