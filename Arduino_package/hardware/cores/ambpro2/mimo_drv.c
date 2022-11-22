#include "mimo_drv.h"
#include "mmf2_link.h"
#include "mmf2_mimo.h"

uint8_t numIn = 0;

/**
  * @brief  allocate memory for a mimo object
  * @param  none
  * @retval  pointer to the mimo object
  */
uint32_t mimoCreate(void) {
    //create MIMO object to be used across input and output module
    mm_mimo_t *context = NULL;
    context  = mimo_create();
    if (context == NULL) {
        printf("MIMO create failed/r/n");
    }
    return ((uint32_t)context);
}

/**
  * @brief  free the memory from a mimo object and stop mimo task
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoDestroy(void *ctx) {
    //delete the MIMO object created and stop the mimo task
    if(NULL != mimo_delete((mm_mimo_t *)ctx)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to mimo object
  * @retval :0 for success, -1 for fail
  */
int mimoStart(void *ctx) {
    return mimo_start((mm_mimo_t *)ctx);
}

/**
  * @brief  stop the mimo task and put it in suspended state
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoStop(void *ctx) {
    mimo_stop((mm_mimo_t *)ctx);
}

/**
  * @brief  pause the mimo task and put it in suspended state
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoPause(void *ctx) {
    mimo_pause((mm_mimo_t *)ctx, MM_OUTPUT);
}

/**
  * @brief  start the mimo task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoResume(void *ctx) {
    mimo_resume((mm_mimo_t *)ctx);
}

/**
  * @brief  api to register input source to MIMO
  * @param  obj: mimo object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void mimoRegIn1(void *ctx, mm_context_t *arg1) {
    mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_INPUT0, (uint32_t)arg1, 0);
}

void mimoRegIn2(void *ctx, mm_context_t *arg1) {
    mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_INPUT1, (uint32_t)arg1, 0);
}

void mimoRegIn3(void *ctx, mm_context_t *arg1) {
    mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_INPUT2, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output sources to MIMO
  * @param  obj: mimo object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void mimoRegOut1(void *ctx, mm_context_t *arg1) {
    if (numIn == 2){
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0);
//        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0 | MMIC_DEP_INPUT1);
    }
    else if (numIn == 3){
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0 | MMIC_DEP_INPUT2);
    }
}

void mimoRegOut2(void *ctx, mm_context_t *arg1) {
    if (numIn == 2){
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, MMIC_DEP_INPUT1);
//        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT1,(uint32_t)arg1,  MMIC_DEP_INPUT1 | MMIC_DEP_INPUT0);
    }
    else if (numIn == 3){
        mimo_ctrl((mm_mimo_t *)ctx, MMIC_CMD_ADD_OUTPUT1,(uint32_t)arg1, MMIC_DEP_INPUT1 | MMIC_DEP_INPUT2);
    }
}

void getInput(uint8_t numInput){
    numIn = numInput;
}