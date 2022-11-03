#include "simo_drv.h"
#include "mmf2_link.h"
#include "mmf2_simo.h"

/**
  * @brief  allocate memory for a simo object
  * @param  none
  * @retval  pointer to the simo object
  */
void simoCreate(void) {
    //create SIMO object to be used across input and output module
    simo_arduino = simo_create();
}

/**
  * @brief  free the memory from a simo object and stop simo task
  * @param  pointer to the simo object
  * @retval none
  */
void simoDestroy() {
    //delete the SIMO object created and stop the simo task
    if(NULL != simo_delete(simo_arduino)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  api to register input source to SIMO
  * @param  obj: simo object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void simoRegIn(mm_context_t *arg1) {
    simo_ctrl(simo_arduino, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output sources to SIMO
  * @param  obj: simo object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void simoRegOut1(mm_context_t *arg1) {
    simo_ctrl(simo_arduino, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, 0);
}

void simoRegOut2(mm_context_t *arg1) {
    simo_ctrl(simo_arduino, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, 0);
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to simo object
  * @retval :0 for success, -1 for fail
  */
int simoStart(void) {
    return simo_start(simo_arduino);
}

/**
  * @brief  stop the simo task and put it in suspended state
  * @param  pointer to the simo object
  * @retval none
  */
void simoStop(void) {
    simo_stop(simo_arduino);
}

/**
  * @brief  pause the simo task and put it in suspended state
  * @param  pointer to the simo object
  * @retval none
  */
void simoPause(void) {
    simo_pause(simo_arduino, MM_OUTPUT0);
  simo_pause(simo_arduino, MM_OUTPUT1);
}

/**
  * @brief  start the simo task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the simo object
  * @retval none
  */
void simoResume(void) {
    simo_resume(simo_arduino);
}