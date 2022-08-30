/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      app_task.h
   * @brief     Routines to create App task and handle events & messages
   * @author    jane
   * @date      2017-06-02
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _BT_ANCS_APP_TASK_H_
#define _BT_ANCS_APP_TASK_H_


/** @defgroup PERIPH_APP_TASK Peripheral App Task
  * @brief Peripheral App Task
  * @{
  */

extern void driver_init(void);

/**
 * @brief  Initialize App task
 * @return void
 */
void bt_ancs_app_task_init(void);
void bt_ancs_app_task_deinit(void);

/** End of PERIPH_APP_TASK
* @}
*/


#endif

