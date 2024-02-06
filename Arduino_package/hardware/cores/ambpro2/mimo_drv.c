#include "mimo_drv.h"
#include "mmf2_link.h"
#include "mmf2_mimo.h"

static uint8_t numIn = 0;

uint32_t mimoCreate(void)
{
    // create MIMO object to be used across input and output module
    mm_mimo_t *context = NULL;
    context = mimo_create();
    if (context == NULL) {
        printf("\r\n[ERROR] MIMO create failed\n");
    }
    return ((uint32_t)context);
}

void mimoDestroy(void *ctx)
{
    // delete the MIMO object created and stop the mimo task
    if (NULL != mimo_delete((mm_mimo_t *)ctx)) {
        printf("\r\n[ERROR] MIMO linker destroy failed\n");
    }
}

int mimoStart(void *ctx)
{
    return mimo_start((mm_mimo_t *)ctx);
}

void mimoStop(void *ctx)
{
    mimo_stop((mm_mimo_t *)ctx);
}

void mimoPause(void *ctx)
{
    mimo_pause((mm_mimo_t *)ctx, MM_OUTPUT0);
    mimo_pause((mm_mimo_t *)ctx, MM_OUTPUT1);
    mimo_pause((mm_mimo_t *)ctx, MM_OUTPUT2);
    mimo_pause((mm_mimo_t *)ctx, MM_OUTPUT3);
}

void mimoResume(void *ctx)
{
    mimo_resume((mm_mimo_t *)ctx);
}

void mimoRegIn1(void *ctx, mm_context_t *arg1)
{
    mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_INPUT0, (uint32_t)arg1, 0);
}

void mimoRegIn2(void *ctx, mm_context_t *arg1)
{
    mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_INPUT1, (uint32_t)arg1, 0);
}

void mimoRegIn3(void *ctx, mm_context_t *arg1)
{
    mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_INPUT2, (uint32_t)arg1, 0);
}

void mimoRegOut1(void *ctx, mm_context_t *arg1)
{
    if (numIn == 2) {
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0 | MMIC_DEP_INPUT1);
    } else if (numIn == 3) {
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0 | MMIC_DEP_INPUT2);
    }
}

void mimoRegOut2(void *ctx, mm_context_t *arg1)
{
    if (numIn == 2) {
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, MMIC_DEP_INPUT1 | MMIC_DEP_INPUT0);
    } else if (numIn == 3) {
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, MMIC_DEP_INPUT1 | MMIC_DEP_INPUT2);
    }
}

void getInput(uint8_t numInput)
{
    numIn = numInput;
}
