#include "miso_drv.h"
#include "mmf2_link.h"
#include "mmf2_miso.h"

static mm_miso_t *miso_arduino = NULL;

/**
  * @brief  allocate memory for a miso object
  * @param  none
  * @retval  pointer to the miso object
  */
void misoCreate(void) {
    //create MISO object to be used across input and output module
    miso_arduino = miso_create();
}

/**
  * @brief  free the memory from a miso object and stop miso task
  * @param  pointer to the miso object
  * @retval none
  */
void misoDestroy(void) {
    //delete the MISO object created and stop the miso task
    if (NULL != miso_delete(miso_arduino)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  api to register input source to MISO
  * @param  obj: miso object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void misoRegIn1(mm_context_t *arg1) {
    miso_ctrl(miso_arduino, MMIC_CMD_ADD_INPUT0, (uint32_t)arg1, 0);
}

void misoRegIn2(mm_context_t *arg1) {
    miso_ctrl(miso_arduino, MMIC_CMD_ADD_INPUT1, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output sources to MISO
  * @param  obj: miso object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void misoRegOut(mm_context_t *arg1) {
    miso_ctrl(miso_arduino, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to miso object
  * @retval :0 for success, -1 for fail
  */
int misoStart(void) {
    return miso_start(miso_arduino);
}

/**
  * @brief  stop the miso task and put it in suspended state
  * @param  pointer to the miso object
  * @retval none
  */
void misoStop(void) {
    miso_stop(miso_arduino);
}

/**
  * @brief  pause the miso task and put it in suspended state
  * @param  pointer to the miso object
  * @retval none
  */
void misoPause(void) {
    miso_pause(miso_arduino, MM_OUTPUT);
}

/**
  * @brief  start the miso task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the miso object
  * @retval none
  */
void misoResume(void) {
    miso_resume(miso_arduino);
}
