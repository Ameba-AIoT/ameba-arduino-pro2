/**
  ******************************************************************************
  * @file    rmesh_data_forward.h
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
#ifndef _RTL_MESH_DATA_FORWARD_H_
#define _RTL_MESH_DATA_FORWARD_H_

#include "rmesh.h"
#include "rmesh_frame.h"

/*******************************************************
 *                Enumerations
 *******************************************************/

/**
 * @brief mesh_app_data type control & RMESH_APP_CTRL = 0
 */
enum MESH_APP_MGNT_DATA_TYPE {

	// encrypt with aes key
	MESH_TOPO_REQ					= 0,	//recv from cloud
	MESH_TOPO_RSP					= 0x1,
	MESH_ROUTE_UPDATE_TO_CLOUD		= 0x2,

	MESH_RESET_STATUS				= 0x3,		//root report cloud that some devices ready to disconnect, encrypt with aes key

	MESH_WIFI_CONFIG				= 0x4,		//APP send config info to socket client, no encrypt

	// key frame, no need encrypt
	MESH_AES_KEY_REQUEST			= 0x5,
	MESH_AES_KEY_RESPONSE			= 0x6,

	MESH_NETCONFIG_RESET			= 0x7,		//recv from app, encryot with group key

	MESH_HELP_CONFIG_REQUST_APP		= 0xc,		//no need encrypt

	// what to do? encrypt with aes key
	MESH_APINFO_REQ					= 0xd,
	MESH_APINFO_RSP					= 0xe,

	MESH_RESET						= 0xf,		//recv from app, used for test, no encrypt

	// auto switch channel frame, ignore, no encrypt
	MESH_SWITCH_ROOT				= 0x11,
	MESH_SWITCH_RSP					= 0x12,
	MESH_INFO_REQ					= 0x13,
	MESH_INFO_RSP					= 0x14,

#if RMESH_POWER_SAVE
	MESH_POWER_SAVE_DW				= 0x15,		//encrypt with aes key
#endif
};

/**
 * @brief mesh_app_data type control bit0 = 1
 */
enum MESH_APP_DATA_TYPE {
#if RMESH_FREE_NODE
	MESH_FREE_NODE_KEY_REQUEST	= 0x2,		// no encrypt
	MESH_FREE_NODE_KEY_RESPONSE	= 0x3,		// no encrypt
	MESH_FREE_NODE_APPLICATION	= 0x4,		// encrypt with free node's aes key
	MESH_BUFFERED_INFO			= 0X5,		// encrypt with buffered node's aes key
#endif

	// encrypt with aes key
	MESH_LED_APPLICATION		= 0x6,
	MESH_BUTTON_APPLICATION		= 0x7,

	MESH_APP_KEEP_ALIVE			= 0xf,		// recved from app, encrypt with aes key

	MESH_USER_TYPE				= 0X10,		// according to mac add, if unicast, encrypt with aes key, else encrypt with group key

	//used for test, no encrypt
#if PING_TP_TEST
	MESH_TP_CMD					= 0x11,
	MESH_TP_DATA				= 0x12,
	MESH_PING_CMD				= 0x13,
	MESH_PING_DATA				= 0x14,
	MESH_PING_DATA_ACK			= 0x15,
#endif
};

/*******************************************************
 *                Structures
 *******************************************************/

/**
 * @brief mesh app header
 */
struct rmesh_app_hdr {
	u8 mac[ETH_ALEN];
	u8 control;
	u8 type;
	u16 len;				//the total length of payload after len field
};

#define RMESH_APP_CTRL		BIT0		// 0: APP mgnt packet; 1: APP data packet
#define RMESH_APP_PROTECTED	BIT1		// app data packet protected flag

/**
 * @brief structure of TCP nagle process
 */
struct rmesh_tcp_nl_msg {
	u8 g_recv_buf[MAX_MSG_LEN * 2];		//buffer that stored uncomplete packet during last transmission
	u8 pkt_buf[MAX_MSG_LEN * 2];
	u16 g_recv_len;					// length of uncomplete packet during last transmission
	u8 flag_in_NL_proc;				// indicate whether exists uncomplete packet during last transmission (1: yes, 0: no)
};


/*******************************************************
 *                APIs
 *******************************************************/

/* *
* @brief: node-self generate uplink data to external IP networks

* @attention: 	this func can called by common node and root node as well
			if root node called this func, root node will sent data to external IP networks by socket
			if common node called this func, common node will send data to parent node by mesh stack

* @param	data: sent data
			data_len: sent data length
			timeout: enqueue block (1) or non-block (0)

* @retval	RMESH_SUCCESS / RMESH_FAIL
*/
int real_mesh_send_app_data(u8 *data, int data_len, int timeout);


/* *
* @brief: register callback function to process recved data

* @param	void (*callback)(u8 *, u32): callback function, with parameter data and data_size

* @retval	none
*/
void real_mesh_rx_callback_init(void (*callback)(u8 *, u32));




/* *
* @brief: node process application data toself

* @attention:

* @param	data: recved application data
* @param	data_len:  recved data size

* @retval	none
*/
void real_mesh_process_application_data(u8 *data, u16 data_len, struct rmesh_hdr *prmeshhdr);


/*******************************************************
 *                private funcs
 *******************************************************/

int real_mesh_poll(int *data_len);
void real_mesh_root_process_data_from_app(u8 *data, u16 data_len);
void real_mesh_process_data_toself(u8 *data, u16 data_len, struct rmesh_hdr *prmeshhdr);

/* *
* @brief: root node sent route update packet to cloud

* @attention: 	this func can only called by root node

* @param	none

* @retval		none
*/
void real_mesh_root_issue_route_update();


/* *
* @brief: root node sent topology response packet to cloud, this packet is used to draw topology figure for cloud

* @attention: 	this func can only called by root node

* @param	none

* @retval		none
*/
void real_mesh_root_issue_topo_rsp();

#endif //_RTL_MESH_DATA_FORWARD_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/

