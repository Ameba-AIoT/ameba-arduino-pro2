#include "siso_drv.h"
#include "mmf2_link.h"
#include "mmf2_siso.h"

/**
  * @brief  allocate memory for a siso object
  * @param  none
  * @retval  pointer to the siso object
  */
uint32_t sisoCreate(void) {
    //create SISO object to be used across input and output module
    mm_siso_t *context = NULL;
    context  = siso_create();
    if (context == NULL) {
        printf("SISO create failed/r/n");
    }
    return ((uint32_t)context);
}

/**
  * @brief  free the memory from a siso object and stop siso task
  * @param  pointer to the siso object
  * @retval none
  */
void sisoDestroy(void *ctx) {
    //delete the SISO object created and stop the siso task
    if(NULL != siso_delete((mm_siso_t *)ctx)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to siso object
  * @retval :0 for success, -1 for fail
  */
int sisoStart(void *ctx) {
    return siso_start((mm_siso_t *)ctx);
}

/**
  * @brief  stop the siso task and put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoStop(void *ctx) {
    siso_stop((mm_siso_t *)ctx);
}

/**
  * @brief  pause the siso task and put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoPause(void *ctx) {
    siso_pause((mm_siso_t *)ctx);
}

/**
  * @brief  start the siso task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoResume(void *ctx) {
    siso_resume((mm_siso_t *)ctx);
}

/**
  * @brief  api to register input source to SISO
  * @param  obj: siso object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void sisoRegIn(void *ctx, mm_context_t *arg1) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output source to SISO
  * @param  obj: siso object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void sisoRegOut(void *ctx, mm_context_t *arg1) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  
  * @param  none
  * @retval none
  */
void sisoSetStackSize(void *ctx) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_SET_STACKSIZE, (uint32_t)1024 * 64, 0);
}

/**
  * @brief  
  * @param  none
  * @retval none
  */
void sisoSetTaskPriority(void *ctx) {
    siso_ctrl((mm_siso_t *)ctx, MMIC_CMD_SET_TASKPRIORITY, 3, 0);
}

