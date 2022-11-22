#include "miso_drv.h"
#include "mmf2_link.h"
#include "mmf2_miso.h"

/**
  * @brief  allocate memory for a miso object
  * @param  none
  * @retval  pointer to the miso object
  */
uint32_t misoCreate(void) {
    //create MISO object to be used across input and output module
    mm_miso_t *context = NULL;
    context  = miso_create();
    if (context == NULL) {
        printf("MISO create failed/r/n");
    }
    return ((uint32_t)context);
}

/**
  * @brief  free the memory from a miso object and stop miso task
  * @param  pointer to the miso object
  * @retval none
  */
void misoDestroy(void *ctx) {
    //delete the MISO object created and stop the miso task
    if(NULL != miso_delete((mm_miso_t *)ctx)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to miso object
  * @retval :0 for success, -1 for fail
  */
int misoStart(void *ctx) {
    return miso_start((mm_miso_t *)ctx);
}

/**
  * @brief  stop the miso task and put it in suspended state
  * @param  pointer to the miso object
  * @retval none
  */
void misoStop(void *ctx) {
    miso_stop((mm_miso_t *)ctx);
}

/**
  * @brief  pause the miso task and put it in suspended state
  * @param  pointer to the miso object
  * @retval none
  */
void misoPause(void *ctx) {
    miso_pause((mm_miso_t *)ctx, MM_OUTPUT);
}

/**
  * @brief  start the miso task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the miso object
  * @retval none
  */
void misoResume(void *ctx) {
    miso_resume((mm_miso_t *)ctx);
}

/**
  * @brief  api to register input source to MISO
  * @param  obj: miso object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void misoRegIn1(void *ctx, mm_context_t *arg1) {
    miso_ctrl((mm_miso_t *)ctx, MMIC_CMD_ADD_INPUT0, (uint32_t)arg1, 0);
}

void misoRegIn2(void *ctx, mm_context_t *arg1) {
    miso_ctrl((mm_miso_t *)ctx, MMIC_CMD_ADD_INPUT1, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output sources to MISO
  * @param  obj: miso object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void misoRegOut(void *ctx, mm_context_t *arg1) {
    miso_ctrl((mm_miso_t *)ctx, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}