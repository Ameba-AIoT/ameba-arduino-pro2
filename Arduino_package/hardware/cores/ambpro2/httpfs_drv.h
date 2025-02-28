#ifndef HTTPFS_DRV_H
#define HTTPFS_DRV_H

#include "mmf2_module.h"
#include "module_httpfs.h"

mm_context_t *httpfsInit(void);

mm_context_t *httpfsDeinit(mm_context_t *p);

int httpfsSetParams(mm_context_t *p, httpfs_params_t *params);

int httpfsSetRespCB(mm_context_t *p);

int httpfsApply(mm_context_t *p);

int httpfs_response_cb(void);

#endif
