#include "siso_drv.h"
#include "mmf2_link.h"
#include "mmf2_siso.h"

mm_siso_t *siso_arduino = NULL;


/**
  * @brief  allocate memory for a siso object
  * @param  none
  * @retval  pointer to the siso object
  */
void* sisoCreate(void) {
    //create SISO object to be used across input and output module
    siso_arduino = siso_create();
    return (void*)siso_arduino;
}


/**
  * @brief  free the memory from a siso object and stop siso task
  * @param  pointer to the siso object
  * @retval none
  */
void sisoDestroy(void *obj) {
    //delete the SISO object created and stop the siso task
    if(NULL != siso_delete((mm_siso_t *)obj)) {
        printf("Camera IO linker destroy failed..");
    }
}


/**
  * @brief  api to register input source to SISO
  * @param  obj: siso object
  * @param  arg1: this argument is an input source
  * @retval  none
  */
void sisoRegIn(void *obj, void *arg1) {
    siso_ctrl((mm_siso_t *)obj, MMIC_CMD_ADD_INPUT, (uint32_t)arg1, 0);
}


/**
  * @brief  api to register output source to SISO
  * @param  obj: siso object
  * @param  arg1: this argument is output source
  * @retval  none
  */
void sisoRegOut(void *obj, void *arg1) {
    siso_ctrl((mm_siso_t *)obj, MMIC_CMD_ADD_OUTPUT, (uint32_t)arg1, 0);
}


/**
  * @brief  create a pumper task that send and receive data between input and output
  * @param  obj: pointer to siso object
  * @retval :0 for success, -1 for fail
  */
int sisoStart(void *obj) {
    return siso_start((mm_siso_t *)obj);
}


/**
  * @brief  stop the siso task and put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoStop(void *obj) {
    siso_stop((mm_siso_t *)obj);
}


/**
  * @brief  pause the siso task and put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoPause(void *obj) {
    siso_pause((mm_siso_t *)obj);
}


/**
  * @brief  start the siso task if it's not already started, or set the task to running state
            if the task already created but not in running state, else put it in suspended state
  * @param  pointer to the siso object
  * @retval none
  */
void sisoResume(void *obj) {
    siso_resume((mm_siso_t *)obj);
}

