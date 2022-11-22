#include "simo_drv.h"
#include "mmf2_link.h"
#include "mmf2_simo.h"

/**
  * @brief  allocate memory for a simo object
  * @param  none
  * @retval  pointer to the simo object
  */
uint32_t simoCreate(void) {
    //create SIMO object to be used across input and output module
    mm_simo_t *context = NULL;
    context  = simo_create();
    if (context == NULL) {
        printf("SIMO create failed/r/n");
    }
    return ((uint32_t)context);
}

/**
  * @brief  free the memory from a simo object and stop simo task
  * @param  pointer to the simo object
  * @retval none
  */
void simoDestroy(void *ctx) {
    //delete the SIMO object created and stop the simo task
    if(NULL != simo_delete((mm_simo_t *)ctx)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to simo object
  * @retval :0 for success, -1 for fail
  */
int simoStart(void *ctx) {
    return simo_start((mm_simo_t *)ctx);
}

/**
  * @brief  stop the simo task and put it in suspended state
  * @param  pointer to the simo object
  * @retval none
  */
void simoStop(void *ctx) {
    simo_stop((mm_simo_t *)ctx);
}

/**
  * @brief  pause the simo task and put it in suspended state
  * @param  pointer to the simo object
  * @retval none
  */
void simoPause(void *ctx) {
    simo_pause((mm_simo_t *)ctx, MM_OUTPUT0);
    simo_pause((mm_simo_t *)ctx, MM_OUTPUT1);
}

/**
  * @brief  start the simo task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the simo object
  * @retval none
  */
void simoResume(void *ctx) {
    simo_resume((mm_simo_t *)ctx);
}

/**
  * @brief  api to register input source to SIMO
  * @param  obj: simo object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void simoRegIn(void *ctx, mm_context_t *arg1) {
    simo_ctrl((mm_simo_t *)ctx, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output sources to SIMO
  * @param  obj: simo object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void simoRegOut1(void *ctx, mm_context_t *arg1) {
    simo_ctrl((mm_simo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, 0);
}

void simoRegOut2(void *ctx, mm_context_t *arg1) {
    simo_ctrl((mm_simo_t *)ctx, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, 0);
}