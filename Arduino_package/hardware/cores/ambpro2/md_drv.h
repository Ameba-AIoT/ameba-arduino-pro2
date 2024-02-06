#ifndef MD_DRV_H
#define MD_DRV_H

#include "mmf2_module.h"
#include "md_api.h"

mm_context_t *MDInit(void);

mm_context_t *MDDeinit(mm_context_t *p);

void setMDParams(mm_context_t *p, eip_param_t *md_eip_param);

void setMDMask(mm_context_t *p, char *md_mask);

void setMDDisppost(mm_context_t *p, void (*md_postprocess)(md_result_t *));

void setMDTrigBlock(mm_context_t *p, uint16_t count);

void getMDResult(mm_context_t *p, md_result_t *md_result);

void MDBegin(mm_context_t *p, int start);

void setMDStatus(mm_context_t *p);

// extern int md_control(mm_context_t *p, int cmd, int arg);

#endif
