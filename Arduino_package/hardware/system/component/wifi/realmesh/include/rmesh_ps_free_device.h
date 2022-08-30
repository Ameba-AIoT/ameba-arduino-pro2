/**
  ******************************************************************************
  * @file    rmesh_ps_free_device.h
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

#ifndef _RTL_MESH_PS_FREE_DEVICE_H_
#define _RTL_MESH_PS_FREE_DEVICE_H_

#include "device.h"
#include "rmesh.h"

#define SEQUENCE_LEN		4

enum RMESH_CHECKING {
	NO_CHECKING = 0,
	NEED_CHECKING,
};

struct rmesh_free_node_buffer_data {
	u8 *data;
	u16 data_len;
	u32 tsf_low;
	u32 tsf_high;
	u32 seq;		//mesh hdr seq->ctl
	struct rmesh_free_node_buffer_data *next;
};

struct rmesh_free_node_buffer_table {
	u8 mac[6];
	u32 tsf_low;	// time of reporting to cloud
	u32 tsf_high;
	struct rmesh_free_node_buffer_data *pdata;			// unsent data
	struct rmesh_free_node_buffer_data *psent_data;		// has sent and wait ack from free node
	struct rmesh_free_node_buffer_table *next;
};

struct rmesh_free_node_seq_item {
	u32 seq;
};

struct rmesh_free_node_seq_table {
	struct rmesh_free_node_seq_item *pitem;
	struct rmesh_free_node_seq_item *pnext;
	struct rmesh_free_node_seq_item *ppre;
};


//uplink
void rmesh_free_node_tx(u8 *data, u32 len);
void rmesh_buffered_node_on_free_node_bc_processing(u8 *pframe, u32 len, struct rmesh_hdr *prmesh_hdr);

//downlink
void rmesh_free_node_enter_power_save(u32 time);
void rmesh_free_node_issue_bc_trigger();
void rmesh_buffered_node_issue_buffered_info(u8 *data, signed char rssi);
void rmesh_buffered_node_issue_data_to_free_node(u8 *mac_da, struct rmesh_free_node_buffer_data *pdata, u8 more_data);
void rmesh_buffered_node_on_bc_triggering(u8 *pframe, u32 len, struct rmesh_hdr *prmesh_hdr, signed char rssi);
void rmesh_buffered_node_on_downlink_free_node_data(u8 *pframe, u32 len);
void rmesh_free_node_rx();

bool rmesh_free_node_seq_check(u32 seq);
void rmesh_free_node_seq_list_init();
void rmesh_free_node_seq_list_deinit();

bool real_mesh_compare_tsf(u32 cur_high, u32 cur_low, u32 last_high, u32 last_low, u8 time);
int real_mesh_buffered_table_init(struct rmesh_free_node_buffer_table **ptable);
int real_mesh_buffered_table_add_device(struct rmesh_free_node_buffer_table **first_node, u8 *mac, u32 tsf0_high, u32 tsf0_low);
bool real_mesh_buffered_table_add_data(struct rmesh_free_node_buffer_table *first_node, u8 *mac, u8 *data, u16 len, u32 seq);
bool real_mesh_buffered_table_add_sent_data(struct rmesh_free_node_buffer_table *first_node, u8 *mac, struct rmesh_free_node_buffer_data *sent_data);
struct rmesh_free_node_buffer_table *real_mesh_buffered_table_find_device(struct rmesh_free_node_buffer_table *first_node, u8 *mac);
int real_mesh_buffered_table_find_data_num(struct rmesh_free_node_buffer_table *first_node, u8 *mac);
struct rmesh_free_node_buffer_data *real_mesh_buffered_table_get_data(struct rmesh_free_node_buffer_table *first_node, u8 *mac);


#endif //_RTL_MESH_PS_FREE_DEVICE_H_
