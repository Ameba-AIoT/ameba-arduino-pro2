/**
  ******************************************************************************
  * @file    rmesh_connect.h
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

#ifndef _RTL_MESH_CONNECT_H_
#define _RTL_MESH_CONNECT_H_

#define CONNECT_TIMEOUT       2 // 2s


/*******************************************************
 *                Enumerations
 *******************************************************/

/**
 * @brief mesh connect state
 */
enum RMESH_CONNECT_STATE {
	RMESH_CONNECT_IDLE = 0,
	RMESH_CONNECT_START,
	RMESH_CONNECT_ING,
	RMESH_CONNECT_SUCCESS,
	RMESH_CONNECT_FAIL,
};


/**
 * @brief mesh deauth reason code
 */
enum RMESH_DEAUTH_REASON {
	RMESH_KEEP_ALIVE_FAIL = 0,
	RMESH_CHILD_LIST_NOT_FOUND = 1,
};

/**
 * @brief mesh disconnect reason code
 */
enum RMESH_DISCONNECT_REASON {
	RMESH_PARENT_NODE_TYPE_CHANGE = 0,		/* parent node type changed to leaf /idle */
	RMESH_ASSOC_REQ_FROM_PARENT = 1,		/* recv assoc req from parent node: cycle formed */
	RMESH_ROUTE_UPDATE_FROM_PARENT = 2,	/* recv route update from parent node: cycle formed */
	RMESH_DEAUTH = 3,							/* recv deauth from parent node */
	RMESH_KEEP_ALIVE_DISCONNECT = 4,			/* check that disconnected with parent via keep alive mechanism */

	RMESH_ROOT_RESTRICT			= 5,
};

enum RMESH_DISCONNECT_STATE {
	RMESH_START_CONNECT = 0,
	RMESH_COMMON_DISCONNECT = 1,
	RMESH_ROOT_DISCONNECT_VIA_ROOT_CONTROL = 2,
};


/*******************************************************
 *                Structures
 *******************************************************/

/**
 * @brief mesh connect
 */
struct rmesh_connect_priv {
	_timer	connect_timer;
	int		connect_state;
};


/*******************************************************
 *                APIs
 *******************************************************/

/* *
* @brief: after node finished network config, it entered connect stage

* @attention

* @param	none

* @retval	none
*/
void real_mesh_start_connect();

void real_mesh_scan();

int real_mesh_connect();
void real_mesh_disconnect(u8 disconnect_reason);
void real_mesh_idle_update_bcn();
int real_mesh_get_disconnect_state();
void real_mesh_set_disconnect_state(bool val);
void real_mesh_unlock_scan_sema();

#endif //_RTL_MESH_CONNECT_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
