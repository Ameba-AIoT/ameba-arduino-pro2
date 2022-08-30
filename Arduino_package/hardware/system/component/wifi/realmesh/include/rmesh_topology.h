/**
  ******************************************************************************
  * @file    rmesh_topology.h
  * @author
  * @version V1.0.0
  * @date    2016-05-17
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

#ifndef _RTL_MESH_TOPOLOGY_H_
#define _RTL_MESH_TOPOLOGY_H_

#include "rmesh.h"

int real_mesh_topology_table_init(struct rmesh_topo_node **topo_table);
int real_mesh_topology_table_add(struct rmesh_topo_node **first_node, u8 *mac_parent, u8 *mac);
int real_mesh_topology_table_del(struct rmesh_topo_node **first_node, u8 *mac_parent, u8 *mac);
struct rmesh_topo_node *real_mesh_topology_table_find(struct rmesh_topo_node *first_node, u8 *mac);
void real_mesh_topology_table_get(struct rmesh_topo_node *first_node, u8 *pframe, u32 *len);
void real_mesh_topology_table_destroy(struct rmesh_topo_node **first_node);
u8 real_mesh_topology_table_size(struct rmesh_topo_node *first_node);

#endif //_RTL_MESH_TOPOLOGY_H_
