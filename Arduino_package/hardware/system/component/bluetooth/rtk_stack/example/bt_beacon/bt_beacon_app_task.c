/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      app_task.c
   * @brief     Routines to create App task and handle events & messages
   * @author    jane
   * @date      2017-06-02
   * @version   v1.0
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */

/*============================================================================*
 *                              Header Files
 *============================================================================*/
#include <platform_opts_bt.h>
#if defined(CONFIG_BT_BEACON) && CONFIG_BT_BEACON
#include <osdep_service.h>
#include <os_msg.h>
#include <os_task.h>
#include <gap.h>
#include <gap_le.h>
#include "bt_beacon_app_task.h"
#include <app_msg.h>
#include "bt_beacon_app.h"
#include "platform_stdlib.h"
#include <gap_msg.h>

/** @defgroup  PERIPH_APP_TASK Peripheral App Task
    * @brief This file handles the implementation of application task related functions.
    *
    * Create App task and handle events & messages
    * @{
    */
/*============================================================================*
 *                              Macros
 *============================================================================*/
#define APP_TASK_PRIORITY             1         //!< Task priorities
#define APP_TASK_STACK_SIZE           256 * 4   //!<  Task stack size
#define MAX_NUMBER_OF_GAP_MESSAGE     0x20      //!<  GAP message queue size
#define MAX_NUMBER_OF_IO_MESSAGE      0x20      //!<  IO message queue size
#define MAX_NUMBER_OF_EVENT_MESSAGE   (MAX_NUMBER_OF_GAP_MESSAGE + MAX_NUMBER_OF_IO_MESSAGE)    //!< Event message queue size

/*============================================================================*
 *                              Variables
 *============================================================================*/
static void *app_task_handle;   //!< APP Task handle
static void *evt_queue_handle;  //!< Event queue handle
static void *io_queue_handle;   //!< IO queue handle

extern T_GAP_DEV_STATE bt_beacon_gap_dev_state;

/*============================================================================*
 *                              Functions
 *============================================================================*/
void bt_beacon_app_main_task(void *p_param);

/**
 * @brief  Initialize App task
 * @return void
 */
void bt_beacon_app_task_init()
{
	os_task_create(&app_task_handle, "bt_beacon_app", bt_beacon_app_main_task, 0, APP_TASK_STACK_SIZE,
				   APP_TASK_PRIORITY);
}

/**
 * @brief        App task to handle events & messages
 * @param[in]    p_param    Parameters sending to the task
 * @return       void
 */
void bt_beacon_app_main_task(void *p_param)
{
	(void)p_param;
	uint8_t event;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	osif_create_secure_context(configMINIMAL_SECURE_STACK_SIZE + 100);
#endif

	os_msg_queue_create(&io_queue_handle, MAX_NUMBER_OF_IO_MESSAGE, sizeof(T_IO_MSG));
	os_msg_queue_create(&evt_queue_handle, MAX_NUMBER_OF_EVENT_MESSAGE, sizeof(uint8_t));

	gap_start_bt_stack(evt_queue_handle, io_queue_handle, MAX_NUMBER_OF_GAP_MESSAGE);

	bt_beacon_driver_init();
	while (true) {
		if (os_msg_recv(evt_queue_handle, &event, 0xFFFFFFFF) == true) {
			if (event == EVENT_IO_TO_APP) {
				T_IO_MSG io_msg;
				if (os_msg_recv(io_queue_handle, &io_msg, 0) == true) {
					bt_beacon_app_handle_io_msg(io_msg);
				}
			} else {
				gap_handle_msg(event);
			}
		}
	}
}

void bt_beacon_app_task_deinit(void)
{
	//gap_stop_bt_stack
	if (app_task_handle) {
		os_task_delete(app_task_handle);
	}
	if (io_queue_handle) {
		os_msg_queue_delete(io_queue_handle);
	}
	if (evt_queue_handle) {
		os_msg_queue_delete(evt_queue_handle);
	}
	io_queue_handle = NULL;
	evt_queue_handle = NULL;
	app_task_handle = NULL;

	bt_beacon_gap_dev_state.gap_init_state = 0;
	bt_beacon_gap_dev_state.gap_adv_sub_state = 0;
	bt_beacon_gap_dev_state.gap_adv_state = 0;
	bt_beacon_gap_dev_state.gap_scan_state = 0;
	bt_beacon_gap_dev_state.gap_conn_state = 0;
}


/** @} */ /* End of group PERIPH_APP_TASK */
#endif

