#include "httpfs_drv.h"

// httpfs module init
mm_context_t *httpfsInit(void)
{
    return mm_module_open(&httpfs_module);
}

// httpfs module deinit
mm_context_t *httpfsDeinit(mm_context_t *p)
{
    return mm_module_close(p);
}

// set httpfs module parameters
int httpfsSetParams(mm_context_t *p, httpfs_params_t *params)
{
    return mm_module_ctrl(p, CMD_HTTPFS_SET_PARAMS, (int)params);
}

// set httpfs response callback function
int httpfsSetRespCB(mm_context_t *p)
{
    return mm_module_ctrl(p, CMD_HTTPFS_SET_RESPONSE_CB, (int)httpfs_response_cb);
}

// response callback
int httpfs_response_cb(void)
{
    rt_printf("httpfs response\r\n");
    return 0;
}

// httpfs apply
int httpfsApply(mm_context_t *p)
{
    return mm_module_ctrl(p, CMD_HTTPFS_APPLY, 0);
}
