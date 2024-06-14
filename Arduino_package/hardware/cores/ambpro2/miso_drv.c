#include "miso_drv.h"
#include "mmf2_link.h"
#include "mmf2_miso.h"

uint32_t misoCreate(void)
{
    // create MISO object to be used across input and output module
    mm_miso_t *context = NULL;
    context = miso_create();
    if (context == NULL) {
        printf("\r\n[ERROR] MISO create failed\n");
    }
    return ((uint32_t)context);
}

void misoDestroy(void *ctx)
{
    // delete the MISO object created and stop the miso task
    if (NULL != miso_delete((mm_miso_t *)ctx)) {
        printf("\r\n[ERROR] MISO linker destroy failed\n");
    }
}

int misoStart(void *ctx)
{
    return miso_start((mm_miso_t *)ctx);
}

void misoStop(void *ctx)
{
    miso_stop((mm_miso_t *)ctx);
}

void misoPause(void *ctx)
{
    miso_pause((mm_miso_t *)ctx, MM_OUTPUT);
}

void misoResume(void *ctx)
{
    miso_resume((mm_miso_t *)ctx);
}

void misoRegIn1(void *ctx, mm_context_t *arg1)
{
    miso_ctrl((mm_miso_t *)ctx, MMIC_CMD_ADD_INPUT0, (uint32_t)arg1, 0);
}

void misoRegIn2(void *ctx, mm_context_t *arg1)
{
    miso_ctrl((mm_miso_t *)ctx, MMIC_CMD_ADD_INPUT1, (uint32_t)arg1, 0);
}

void misoRegOut(void *ctx, mm_context_t *arg1)
{
    miso_ctrl((mm_miso_t *)ctx, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}
