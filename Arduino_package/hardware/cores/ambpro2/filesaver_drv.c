#include "Arduino.h"

#include "filesaver_drv.h"

// filesaver module init
mm_context_t *filesaver_Init(void)
{
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] filesaver module init\n");
    return mm_module_open(&filesaver_module);
}

// filesaver module deinit
mm_context_t *filesaver_Deinit(mm_context_t *p)
{
    return mm_module_close(p);
}

// Set filesaver module parameters
int filesaver_SetParams(mm_context_t *p, filesaver_params_t *params)
{
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] filesaver module set params\n");
    return mm_module_ctrl(p, CMD_FILESAVER_SET_PARAMS, (int)params);
}

int filesaver_SetTypeHandler(mm_context_t *p, void (*fsCB)(char *, uint32_t, uint32_t))
{
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] filesaver module set type handler\n");
    return mm_module_ctrl(p, CMD_FILESAVER_SET_TYPE_HANDLER, (int)fsCB);
}

int filesaver_Apply(mm_context_t *p)
{
    return mm_module_ctrl(p, CMD_FILESAVER_APPLY, 0);
}

int filesaver_SetFilePath(mm_context_t *p, const char *filename)
{
    return mm_module_ctrl(p, CMD_FILESAVER_SET_SAVE_FILE_PATH, (int)filename);
}

// int filesaver_cb(void)
// {
//     amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] filesaver response\n");
//     return 0;
// }
