#include "siso_drv.h"
#include "mmf2_link.h"
#include "mmf2_siso.h"

uint32_t sisoCreate(void) {
    //create SISO object to be used across input and output module
    mm_siso_t *context = NULL;
    context  = siso_create();
    if (context == NULL) {
        printf("\r\n[ERROR] SISO create failed\n");
    }
    return ((uint32_t)context);
}

void sisoDestroy(void *ctx) {
    //delete the SISO object created and stop the siso task
    if(NULL != siso_delete((mm_siso_t *)ctx)) {
        printf("\r\n[ERROR] SISO linker destroy failed\n");
    }
}

int sisoStart(void *ctx) {
    return siso_start((mm_siso_t *)ctx);
}

void sisoStop(void *ctx) {
    siso_stop((mm_siso_t *)ctx);
}

void sisoPause(void *ctx) {
    siso_pause((mm_siso_t *)ctx);
}

void sisoResume(void *ctx) {
    siso_resume((mm_siso_t *)ctx);
}

void sisoRegIn(void *ctx, mm_context_t *arg1) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}

void sisoRegOut(void *ctx, mm_context_t *arg1) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}

void sisoSetStackSize(void *ctx) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_SET_STACKSIZE, (uint32_t)1024 * 64, 0);
}

void sisoSetTaskPriority(void *ctx) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_SET_TASKPRIORITY, 3, 0);
}

