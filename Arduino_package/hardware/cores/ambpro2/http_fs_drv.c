#include "http_fs_drv.h"

// http_fs module init
mm_context_t *http_fs_Init(void)
{
    printf("\r\n[INFO] http_fs module init\r\n");
    return mm_module_open(&httpfs_module);
}

// http_fs module deinit
mm_context_t *http_fs_Deinit(mm_context_t *p)
{
    return mm_module_close(p);
}

// Set http_fs module parameters
int http_fs_SetParams(mm_context_t *p, httpfs_params_t *params)
{
    printf("\r\n[INFO] http_fs module set params\r\n");
    return mm_module_ctrl(p, CMD_HTTPFS_SET_PARAMS, (int)params);
}

int http_fs_SetRespCB(mm_context_t *p)
{
    return mm_module_ctrl(p, CMD_HTTPFS_SET_RESPONSE_CB, (int)http_fs_response_cb);
}

int http_fs_response_cb(void)
{
    rt_printf("[INFO] http_fs response\r\n");
    return 0;
}

int http_fs_Apply(mm_context_t *p)
{
    return mm_module_ctrl(p, CMD_HTTPFS_APPLY, 0);
}
