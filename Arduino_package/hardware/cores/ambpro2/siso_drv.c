#include "siso_drv.h"
#include "mmf2_link.h"
#include "mmf2_siso.h"

static mm_siso_t *siso_arduino = NULL;

/**
  * @brief  allocate memory for a siso object
  * @param  none
  * @retval  pointer to the siso object
  */
void sisoCreate(void) {
    //create SISO object to be used across input and output module
    siso_arduino = siso_create();
}

/**
  * @brief  free the memory from a siso object and stop siso task
  * @param  pointer to the siso object
  * @retval none
  */

void sisoDestroy(void) {
    //delete the SISO object created and stop the siso task
    if(NULL != siso_delete(siso_arduino)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  api to register input source to SISO
  * @param  obj: siso object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void sisoRegIn(mm_context_t *arg1) {
    siso_ctrl(siso_arduino, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output source to SISO
  * @param  obj: siso object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void sisoRegOut(mm_context_t *arg1) {
    siso_ctrl(siso_arduino, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to siso object
  * @retval :0 for success, -1 for fail
  */
int sisoStart(void) {
    return siso_start(siso_arduino);
}

/**
  * @brief  stop the siso task and put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoStop(void) {
    siso_stop(siso_arduino);
}

/**
  * @brief  pause the siso task and put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoPause(void) {
    siso_pause(siso_arduino);
}

/**
  * @brief  start the siso task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoResume(void) {
    siso_resume(siso_arduino);
}

/**
  * @brief  
  * @param  none
  * @retval none
  */
void sisoSetStackSize(void) {
    siso_ctrl(siso_arduino, MMIC_CMD_SET_STACKSIZE, (uint32_t)1024 * 64, 0);
}

/**
  * @brief  
  * @param  none
  * @retval none
  */
void sisoSetTaskPriority(void) {
    siso_ctrl(siso_arduino, MMIC_CMD_SET_TASKPRIORITY, 3, 0);
}

