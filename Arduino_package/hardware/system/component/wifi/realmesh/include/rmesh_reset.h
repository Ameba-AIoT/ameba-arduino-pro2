/**
  ******************************************************************************
  * @file    rmesh_reset.h
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
#ifndef _RTL_MESH_RESET_H_
#define _RTL_MESH_RESET_H_

#include "rmesh.h"

struct rmesh_reset_child_info {
	u8 mac[ETH_ALEN];		//mac_child
	u8 *mac_list;			//mac_sub_child_list
	u8 mac_list_num;		//number of sub child need to be reset of each child
	u8 reset_flag;			//mac_child need to be reset or not
	u8 on_ack_flag;			//receive response from mac_child or not
};

struct rmesh_reset_info {
	struct rmesh_reset_child_info reset_list_child[MAX_CHILD_NUM];
	u8 self_reset_flag;		//self node need to be reset or not
	u8 child_num;			//number of child
};
#endif //_RTL_MESH_RESET_H_
