#include "mimo_drv.h"
#include "mmf2_link.h"
#include "mmf2_mimo.h"

static mm_mimo_t *mimo_arduino = NULL;
uint8_t numIn = 0;

/**
  * @brief  allocate memory for a mimo object
  * @param  none
  * @retval  pointer to the mimo object
  */
void mimoCreate(void) {
    //create MIMO object to be used across input and output module
    mimo_arduino = mimo_create();
}

/**
  * @brief  free the memory from a mimo object and stop mimo task
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoDestroy(void) {
    //delete the MIMO object created and stop the mimo task
    if(NULL != mimo_delete(mimo_arduino)) {
        printf("Camera IO linker destroy failed..");
    }
}

/**
  * @brief  api to register input source to MIMO
  * @param  obj: mimo object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void mimoRegIn1(mm_context_t *arg1) {
    mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_INPUT0, (uint32_t)arg1, 0);
}

void mimoRegIn2(mm_context_t *arg1) {
    mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_INPUT1, (uint32_t)arg1, 0);
}

void mimoRegIn3(mm_context_t *arg1) {
    mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_INPUT2, (uint32_t)arg1, 0);
}

/**
  * @brief  api to register output sources to MIMO
  * @param  obj: mimo object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void mimoRegOut1(mm_context_t *arg1) {
    if (numIn == 2) {
        printf("2 Inputs /r/n");
        mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0);
//        mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0 | MMIC_DEP_INPUT1);
    } else if (numIn == 3) {
        printf("3 Inputs /r/n");
        mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_OUTPUT0, (uint32_t)arg1, MMIC_DEP_INPUT0 | MMIC_DEP_INPUT2);
    }
}

void mimoRegOut2(mm_context_t *arg1) {
    if (numIn == 2) {
        printf("2 Inputs /r/n");
        mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_OUTPUT1, (uint32_t)arg1, MMIC_DEP_INPUT1);
//        mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_OUTPUT1,(uint32_t)arg1,  MMIC_DEP_INPUT1 | MMIC_DEP_INPUT0);
    } else if (numIn == 3) {
        printf("3 Inputs /r/n");
        mimo_ctrl(mimo_arduino, MMIC_CMD_ADD_OUTPUT1,(uint32_t)arg1, MMIC_DEP_INPUT1 | MMIC_DEP_INPUT2);
    }
}

/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to mimo object
  * @retval :0 for success, -1 for fail
  */
int mimoStart(void) {
    return mimo_start(mimo_arduino);
}

/**
  * @brief  stop the mimo task and put it in suspended state
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoStop(void) {
    mimo_stop(mimo_arduino);
}

/**
  * @brief  pause the mimo task and put it in suspended state
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoPause(void) {
    mimo_pause(mimo_arduino, MM_OUTPUT);
}

/**
  * @brief  start the mimo task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the mimo object
  * @retval none
  */
void mimoResume(void) {
    mimo_resume(mimo_arduino);
}

void getInput(uint8_t numInput) {
    numIn = numInput;
}
