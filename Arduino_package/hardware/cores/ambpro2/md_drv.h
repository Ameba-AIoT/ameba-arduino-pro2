#ifndef md_drv_h
#define md_drv_h

#include "mmf2_module.h"
#include "md_api.h"

mm_context_t* MDInit(void);

mm_context_t* MDDeinit(mm_context_t *p);

void setMDParams(void *p, md_param_t* md_param);

void setMDThreshold(void *p, motion_detect_threshold_t* md_thr);

void setMDMask(void *p, char* md_mask);

void setMDDisppost(void *p, void (*md_postprocess)(char*));

void setMDTrigBlock(void *p, uint16_t count);

void getMDResult(void *p, char* md_result);

extern int md_control(void *p, int cmd, int arg);

#endif
