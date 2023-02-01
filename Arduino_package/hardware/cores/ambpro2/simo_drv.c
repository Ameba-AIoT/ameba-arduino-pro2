#include "simo_drv.h"
#include "mmf2_link.h"
#include "mmf2_simo.h"

uint32_t simoCreate(void) {
    //create SIMO object to be used across input and output module
    mm_simo_t *context = NULL;
    context  = simo_create();
    if (context == NULL) {
        printf("SIMO create failed/r/n");
    }
    return ((uint32_t)context);
}

void simoDestroy(void *ctx) {
    //delete the SIMO object created and stop the simo task
    if(NULL != simo_delete((mm_simo_t *)ctx)) {
        printf("SIMO linker destroy failed\r\n");
    }
}

int simoStart(void *ctx) {
    return simo_start((mm_simo_t *)ctx);
}

void simoStop(void *ctx) {
    simo_stop((mm_simo_t *)ctx);
}

void simoPause(void *ctx) {
    simo_pause((mm_simo_t *)ctx, MM_OUTPUT0);
    simo_pause((mm_simo_t *)ctx, MM_OUTPUT1);
    simo_pause((mm_simo_t *)ctx, MM_OUTPUT2);
    simo_pause((mm_simo_t *)ctx, MM_OUTPUT3);
}

void simoResume(void *ctx) {
    simo_resume((mm_simo_t *)ctx);
}

void simoRegIn(void *ctx, mm_context_t *arg1) {
    simo_ctrl((mm_simo_t *)ctx, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}

void simoRegOut1(void *ctx, mm_context_t *arg1) {
    simo_ctrl((mm_simo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, 0);
}

void simoRegOut2(void *ctx, mm_context_t *arg1) {
    simo_ctrl((mm_simo_t *)ctx, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, 0);
}