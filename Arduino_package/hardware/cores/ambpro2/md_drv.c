#include "md_drv.h"
#include "md_api.h"
#include "module_md.h"
#include "module_eip.h"

mm_context_t *MDInit(void)
{
    return mm_module_open(&eip_module);
}

mm_context_t *MDDeinit(mm_context_t *p)
{
    mm_module_ctrl(p, CMD_EIP_SET_STATUS, EIP_STATUS_STOP);
    return mm_module_close(p);
}

void setMDParams(mm_context_t *p, eip_param_t *md_eip_param)
{
    mm_module_ctrl(p, CMD_MD_SET_PARAMS, (int)md_eip_param);
}

void setMDMask(mm_context_t *p, char *md_mask)
{
    mm_module_ctrl(p, CMD_EIP_SET_MD_MASK, (int)md_mask);
}

void setMDDisppost(mm_context_t *p, void (*md_postprocess)(md_result_t *))
{
    mm_module_ctrl(p, CMD_EIP_SET_MD_DISPPOST, (int)md_postprocess);
}

void setMDTrigBlock(mm_context_t *p, uint16_t count)
{
    mm_module_ctrl(p, CMD_MD_SET_TRIG_BLK, count);
}

void getMDResult(mm_context_t *p, md_result_t *md_result)
{
    mm_module_ctrl(p, CMD_EIP_GET_MD_RESULT, (int)md_result);
}

void MDBegin(mm_context_t *p, int start)
{
    mm_module_ctrl(p, CMD_EIP_SET_MD_EN, start);
}

void setMDStatus(mm_context_t *p)
{
    mm_module_ctrl(p, CMD_EIP_SET_STATUS, EIP_STATUS_START);
}
