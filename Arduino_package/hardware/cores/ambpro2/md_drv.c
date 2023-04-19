#include "md_drv.h"
#include "md_api.h"
#include "module_md.h"

mm_context_t *MDInit(void) {
    return mm_module_open(&md_module);
}

mm_context_t* MDDeinit(mm_context_t *p) {
    return mm_module_close(p);
}

void setMDParams(void *p, md_param_t* md_param) {
    md_control(p, CMD_MD_SET_PARAMS, (int)md_param);
}

void setMDMask(void *p, char* md_mask) {
    md_control(p, CMD_MD_SET_MD_MASK, (int)md_mask);
}

void setMDDisppost(void *p, void (*md_postprocess)(md_result_t*)) {
    md_control(p, CMD_MD_SET_DISPPOST, (int)md_postprocess);
}

void setMDTrigBlock(void *p, uint16_t count) {
    md_control(p, CMD_MD_SET_TRIG_BLK, count);
}

void getMDResult(void *p, md_result_t* md_result) {
    md_control(p, CMD_MD_GET_MD_RESULT, (int)md_result);
}