/**
  ******************************************************************************
  * @file    rmesh_route.h
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

#ifndef _RTL_MESH_ROUTE_H_
#define _RTL_MESH_ROUTE_H_

#include "rmesh.h"

/*******************************************************
 *                APIs
 *******************************************************/

/* *
* @brief: init route table

* @attention

* @param	route_table: pointer to route table header

* @retval		RMESH_SUCCESS
*     			RMESH_FAIL
*/
int real_mesh_route_table_init(struct rmesh_route_node **route_table);

/* *
* @brief: print route table

* @attention

* @param	first_node: pointer to route table header

* @retval		none
*/
void real_mesh_route_table_print(struct rmesh_route_node *first_node);

/* *
* @brief: get the number of nodes in the route table

* @attention

* @param	first_node: pointer to route table header

* @retval		the number of nodes in the route table
*/
u8 real_mesh_route_table_size(struct rmesh_route_node *first_node);

int real_mesh_route_table_modify(struct rmesh_route_node **first_node, u8 *mac_next_hop, u8 *mac, u8 *mac_parent);

/* *
* @brief: add a new node to the end of route table

* @attention

* @param	first_node: pointer to route table header
* @param	mac_next_hop: mac address of next hop of current node
* @param	mac: mac address of current node

* @retval		RMESH_SUCCESS: add success
*     			RMESH_FAIL: add fail
*/
int real_mesh_route_table_add(struct rmesh_route_node **first_node, u8 *mac_next_hop, u8 *mac, u8 *mac_parent);

/* *
* @brief: delete a specified node from the route table

* @attention

* @param	first_node: pointer to route table header
* @param	mac: mac address of current node

* @retval		RMESH_SUCCESS: add success
*     			RMESH_FAIL: add fail
*/
int real_mesh_route_table_del(struct rmesh_route_node **first_node, u8 *mac_next_hop, u8 *mac, u8 *mac_parent);

/* *
* @brief: find a specified node from the route table

* @attention

* @param	first_node: pointer to route table header
* @param	mac: mac address of current node

* @retval		rmesh_route_node
*/
struct rmesh_route_node *real_mesh_route_table_find(struct rmesh_route_node *first_node, u8 *mac);

/* *
* @brief: check whether node is child or not

* @attention

* @param	first_node: pointer to route table header
* @param	mac: mac address of node

* @retval		_TRUE
*			_FALSE
*/
bool real_mesh_route_table_find_child(struct rmesh_route_node *first_node, u8 *mac_next_hop);

/* *
* @brief: find all the nodes in the route table

* @attention

* @param	first_node: pointer to route table header
* @param	data: summary of last three bytes of mac address

* @retval		the number of nodes that had found
*/
u8 real_mesh_route_table_find_all(struct rmesh_route_node *first_node, u8 *data);

/* *
* @brief: delete route table and free space

* @attention

* @param	first_node: pointer to route table header

* @retval		none
*/
void real_mesh_route_table_destroy(struct rmesh_route_node **first_node);

void real_mesh_topo_table_get_from_rt(struct rmesh_route_node *first_node, u8 *pframe, u32 *len);


int real_mesh_child_list_init(struct rmesh_sta_priv **child_list);
int real_mesh_child_list_add(struct rmesh_sta_priv **first_node, u8 *mac);
int real_mesh_child_list_del(struct rmesh_sta_priv **first_node, u8 *mac);
struct rmesh_sta_priv *real_mesh_child_list_find(struct rmesh_sta_priv *first_node, u8 *mac);
u8 real_mesh_child_list_find_all(struct rmesh_sta_priv *first_node, u8 *data);
u8 real_mesh_child_list_size(struct rmesh_sta_priv *first_node);
void real_mesh_child_list_destroy(struct rmesh_sta_priv **first_node);

#endif //_RTL_MESH_ROUTE_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/

