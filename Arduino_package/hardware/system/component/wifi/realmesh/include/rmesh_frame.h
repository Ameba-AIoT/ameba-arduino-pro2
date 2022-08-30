/**
  ******************************************************************************
  * @file    rmesh_frame.h
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
#ifndef _RTL_MESH_FRAME_H_
#define _RTL_MESH_FRAME_H_


/*******************************************************
 *                APIs
 *******************************************************/
/*-----------------mesh management frame -------------------*/

/* beacon functions */
int real_mesh_issue_beacon(u16 bcn_interval);
unsigned int real_mesh_on_beacon(u8 *pframe, uint len, ieee80211_frame_info_t *rtw_mesh_info);
void real_mesh_update_bcn_vendor_ie();

/* association functions */
void real_mesh_issue_assoc_req(u8 *mac_da);
int real_mesh_issue_assoc_rsp(u8 *mac_da);
unsigned int real_mesh_on_assoc_req(u8 *pframe, uint len);
unsigned int real_mesh_on_assoc_rsp(u8 *pframe, int len);

/* route table update functions */
int real_mesh_issue_route_update(u8 *add1, u8 *add2, u8 *add3, u8 action);
int real_mesh_on_route_update(u8 *pframe, int len);

void real_mesh_issue_deauth(u8 *mac_da, u8 deauth_reason_code);
void real_mesh_on_deauth(u8 *pframe, int len);

int real_mesh_issue_net_config_reset(u8 *mac_add0, u8 *mac_add1, u8 *data, int len);
int real_mesh_on_net_config_reset(u8 *pframe, int len);

int real_mesh_on_probe_req(u8 *pframe, uint len);
int real_mesh_on_probe_rsp(u8 *pframe, uint len);

int real_mesh_issue_leave_to_parent(u8 *mac_da, u8 *pframe, u32 len);
int real_mesh_on_leave_from_child(u8 *pframe, u32 len);
int real_mesh_on_poll_req(u8 *pframe, u32 len);

/*-----------------mesh data frame --------------------*/

/*
* @brief	send a packet to some node(s) in the mesh network

* @param	data: payload, not include mesh header
* @param	len: length of data
 @param	link: up-link / down-link
* @param	mac_da: destination address of this packet
* 				@ external IP network
* 				@ broadcast to the mesh network
* 				@ multicast to the mesh network
* 				@ unicast to one node in the mesh network
* @param	link: up-link / down-link
* 				@ 1: up-link
* 				@ 0: down-link

* @retval		none
*/
int real_mesh_issue_data(u8 *data, u16 len, u8 *mac_da, u8 link);


void real_mesh_issue_broadcast(u8 *data, u16 len, struct rmesh_hdr *phdr);

/*
* @brief	recv a packet over the mesh network, and transmit this packet to rmesh_data_forward.c for further processing

* @param	pframe: recved data, include MAC header and mesh header
* @param	len: length of data

* @retval		none
*/
unsigned int real_mesh_on_data(u8 *pframe, uint len, u16 type);


/* keep alive function */
int real_mesh_issue_keep_alive();
unsigned int real_mesh_on_keep_alive(u8 *pframe, u32 len);
int real_mesh_on_keep_alive_ack(u8 *pframe, u32 len);
void real_mesh_issue_keep_alive_ack(u8 *mac_da, u8 *mac_sa);

#endif //_RTL_MESH_FRAME_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
