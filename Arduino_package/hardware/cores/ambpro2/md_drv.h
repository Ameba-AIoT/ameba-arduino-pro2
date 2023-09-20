#ifndef MD_DRV_H
#define MD_DRV_H

#include "mmf2_module.h"
#include "md_api.h"

mm_context_t* MDInit(void);

mm_context_t* MDDeinit(mm_context_t *p);

void setMDParams(void *p, md_param_t* md_param);

void setMDMask(void *p, char* md_mask);

void setMDDisppost(void *p, void (*md_postprocess)(md_result_t*));

void setMDTrigBlock(void *p, uint16_t count);

void getMDResult(void *p, md_result_t* md_result);

extern int md_control(void *p, int cmd, int arg);

#endif
