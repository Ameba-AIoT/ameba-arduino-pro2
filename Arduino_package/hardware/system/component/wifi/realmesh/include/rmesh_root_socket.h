/**
  ******************************************************************************
  * @file    rmesh_root_socket.h
  * @author
  * @version V1.0.0
  * @date    2019-09-24
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
#ifndef _RTL_MESH_ROOT_SOCKET_H_
#define _RTL_MESH_ROOT_SOCKET_H_

#include "rmesh.h"
#include "rmesh_data_forward.h"

/* *
* @brief: root node create tcp socket and do some initial operation

* @attention: 	this func can only called by root node

* @param	none

* @retval		RMESH_SUCCESS: connect success
			RMESH_FAIL: connect fail
*/
int real_mesh_root_init();


/* *
* @brief: root node recved downlink data from external IP network via socket

* @attention: 	this func can only called by root node

* @param	data: recved data
* @param	size:  recved data size

* @retval		RMESH_SUCCESS: read success
			RMESH_FAIL: read fail
*/
int real_mesh_socket_read(u8 *data, int *size);


/* *
* @brief: root node sent uplink data to external IP network via socket

* @attention: 	this func can only called by root node

* @param	data: sent data (TCP payload, include rmesh_app_hdr)
* @param	size:  sent data size

* @retval	RMESH_SUCCESS: read success
			RMESH_FAIL: read fail
*/
int real_mesh_socket_write(u8 *data, int size);

/* *
* @brief: root node process socket_data_queue to send data to server, and recv data from socket

* @attention: 	this func can only called by root node

* @param	data: read data

* @retval	RMESH_SUCCESS: write/read success
			RMESH_FAIL: write/read fail
			RMESH_CLOSED: socket is closed
*/
int real_mesh_socket_process(u8 *recv_data);


/* *
* @brief: root node create socket in order to establish TCP connection with cloud

* @attention: 	this func can only called by root node

* @param	server_ip: ip address of TCP server
* @param	port:  port of TCP server

* @retval		RMESH_SUCCESS: connect success
			RMESH_FAIL: connect fail
*/
int root_app_start_socket(uint8_t *server_ip, uint16_t port);


/* *
* @brief: root node close TCP connection

* @attention: 	this func can only called by root node

* @param	none

* @retval		none
*/
void root_app_close_socket(u8 flag);
static void root_app_close_socket_internal();


int rmesh_write_ip_info_to_flash(u8 *data, int len);
bool rmesh_read_ip_info_from_flash(struct ServerInfo *server_info);
void rmesh_erase_server_info();

#endif //_RTL_MESH_ROOT_SOCKET_H_
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/

