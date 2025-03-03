#ifndef HTTP_FS_DRV_H
#define HTTP_FS_DRV_H

#include "mmf2_module.h"
#include "module_httpfs.h"

mm_context_t *http_fs_Init(void);

mm_context_t *http_fs_Deinit(mm_context_t *p);

int http_fs_SetParams(mm_context_t *p, httpfs_params_t *params);

int http_fs_SetRespCB(mm_context_t *p);

int http_fs_Apply(mm_context_t *p);

int http_fs_response_cb(void);

#endif
