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
#ifndef _BT_DISTANCE_DETECTOR_APP_TASK_H_
#define _BT_DISTANCE_DETECTOR_APP_TASK_H_

#include <app_msg.h>
#include <bt_distance_detector_handle_message.h>

bool bt_distance_detector_send_msg_to_apptask(uint16_t subtype);
bool bt_distance_detector_send_msg_to_transfertask(device_msg_t p_msg);

/**
 * @brief  Initialize App task
 * @return void
 */
void bt_distance_detector_app_task_init();
void bt_distance_detector_app_task_deinit(void);

void bt_distance_detector_transfer_task_init();
void bt_distance_detector_transfer_task_deinit(void);

#endif

