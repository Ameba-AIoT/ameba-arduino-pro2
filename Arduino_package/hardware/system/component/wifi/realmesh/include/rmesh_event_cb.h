/**
  ******************************************************************************
  * @file    rmesh_event_cb.h
  * @author
  * @version V1.0.0
  * @date    2019-09-16
  * @brief   This file contains all the functions prototypes for the realmesh.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */

#ifndef _RTL_MESH_EVENT_CB_H_
#define _RTL_MESH_EVENT_CB_H_
#include "rmesh.h"

#ifndef CONFIG_EVENT_QUEUE_NUM
#define CONFIG_EVENT_QUEUE_NUM          (20)
#endif  /**< CONFIG_EVENT_QUEUE_NUM */
#define EVENT_QUEUE_NUM CONFIG_EVENT_QUEUE_NUM

/**
 * @brief  Application specified event callback function

 * @param	event: Event type defined in this file
 * @param	buf:	   Reserved for user

 * @retval	RMESH_SUCCESS
 *     		RMESH_FAIL
 */
typedef u32(*rmesh_event_cb_t)(u32 event, void *buf);

typedef struct {
	u32 event;
	void *buf;
} rmesh_event_data;


/*******************************************************
 *                APIs
 *******************************************************/

/**
 * @brief  Initialize event loop, create the event handler and task

 * @attention

 * @param	cb: Application specified event callback

 * @retval	RMESH_SUCCESS
 *     		RMESH_FAIL
 */
int real_mesh_event_callback_init(rmesh_event_cb_t cb);


/**
 * @brief  Deinitialize event loop, delete the event handler and task

 * @attention

 * @param	none

 * @retval	RMESH_SUCCESS
 *     		RMESH_FAIL
 */
int real_mesh_event_callback_deinit();


/**
 * @brief  send the event to the event queue

 * @param	event: Generated events
 * @param	buf:   Reserved for user
 *
 * @retval	RMESH_SUCCESS
 *     		RMESH_FAIL
 */
int real_mesh_event_indication(u32 event, void *buf);

#endif //_RTL_MESH_EVENT_CB_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/




