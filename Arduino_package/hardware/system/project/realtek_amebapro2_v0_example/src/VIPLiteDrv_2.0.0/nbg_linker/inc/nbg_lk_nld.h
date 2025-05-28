/******************************************************************************\
|* Copyright (c) 2017-2024 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/


#ifndef _NBG_LK_NLD_H
#define _NBG_LK_NLD_H

#include <vip_lite_common.h>
#include <nbg_lk_network.h>

#define SET_NLD_INSERT_FLAG() \
do \
{ \
    if (network->nld.enable && i == insert_index && nld_operation) { \
        network->nld.insert_flag = vip_true_e; \
    } \
    else { \
        network->nld.insert_flag = vip_false_e; \
    } \
} while(0)

typedef struct _nbglk_nld_layer_t {
	nbglk_list_head_t           list;
	vip_uint32_t                index;
	vip_uint32_t                node_id; /* layer id */
	vip_uint32_t                index_in_table; /* index of layet info table */
} nbglk_nld_layer_t;

typedef struct _nbglk_nld_operation_t {
	nbglk_list_head_t           list;
	vip_uint32_t                index;
	vip_uint32_t                insert_index; /* which op of nbg insert this layerdump operation*/
	vip_uint32_t                abs_op_id; /* dumped op's abs op id */
	vip_uint32_t                node_id; /* dumped node id */
	vip_uint32_t                uid;
	vip_uint32_t                output_table_index; /* dump output index in output info table */
	vip_uint32_t                core_id; /* dumped op's core id */
	vip_uint32_t                wait_count; /* add wait event command count before this sh copy process */
	vip_uint32_t                event_id;

	vip_uint32_t                link_pos;
	vip_uint32_t                link_size;

	nbglk_videomemory_t         state;
	nbglk_videomemory_t         instr;
} nbglk_nld_operation_t;
typedef struct _nbglk_nld_link_info_t {
	nbglk_list_head_t           list;
	vip_uint32_t                index;
	vip_uint32_t                nld_op_index;

} nbglk_nld_link_info_t;

typedef struct _nbglk_nld_output_t {
	nbglk_list_head_t           list;
	vip_uint32_t                index;
	vip_uint32_t                abs_op_id; /* dumped op's abs op id */
	vip_uint32_t                index_in_table; /* index in output info table */
	vip_uint32_t                index_in_op; /* output index of the abs op */
	vip_uint32_t                index_in_node; /* output index of the node */
	vip_uint32_t                node_id;
	vip_uint32_t                uid;
	nbg_desc_input_output_t     info;
	vip_char_t                  layer_name[LAYER_NAME_SIZE];
	vip_uint32_t                size; /* allocate buffer size, it include align buffer size */
	vip_uint32_t                used_size; /* object used size */
	nbglk_videomemory_t         memory;
} nbglk_nld_output_t;

typedef struct _nbglk_nld_instr_t {
	nbglk_list_head_t           list;
	vip_uint32_t                index;
	vip_uint32_t                offset; /* offset in ldump instr data */
	vip_uint32_t                op_index; /* which dump operation's instr */
	nbglk_videomemory_t         memory;
} nbglk_nld_instr_t;

vip_status_e nbglk_nld_init(
	vip_network network,
	vip_int32_t *layer_id,
	vip_int32_t layer_count
);

vip_status_e nbglk_nld_get_output(
	vip_network network,
	vip_uint32_t *count,
	vip_nld_output_info_t **info
);

vip_status_e nbglk_nld_destroy(
	vip_network network
);

nbg_desc_ldump_operation_t *nbglk_get_ldump_operation_ptr_by_index(
	vip_network_t *network,
	vip_int32_t index
);

nbg_desc_patch_t *nbglk_get_ldump_patch_data_ptr_by_index(
	vip_network_t *network,
	vip_int32_t index
);

vip_uint32_t get_nld_instr_size(
	vip_network_t *network
);

vip_uint32_t get_nld_pool_patch_count(
	vip_network_t *network
);

vip_uint32_t nbglk_nld_states_size(
	vip_network_t *network,
	nbglk_segment_t *segment
);

vip_status_e nbglk_nld_show_operation(
	vip_network_t *network
);

vip_status_e nbglk_nld_first_dump_op(
	vip_network_t *network,
	nbglk_segment_t *segment,
	vip_uint8_t **nld_states_buffer_ptr,
	nbglk_nld_operation_t **nld_operation_ptr,
	vip_uint32_t *insert_index_ptr
);

vip_status_e patch_nld_output(
	vip_network network,
	nbglk_segment_t *segment,
	nbglk_nld_operation_t *nld_operation,
	vip_uint8_t *states,
	nbg_desc_patch_t *pd_entry
);

vip_status_e patch_nld(
	vip_network_t *network,
	nbglk_nld_operation_t *nld_operation,
	vip_uint8_t *state_buf,
	vip_uint32_t *state_bufSize,
	nbglk_segment_t *segment
);

vip_status_e nbglk_nld_patch(
	vip_network_t *network,
	nbglk_segment_t *segment,
	nbg_desc_operation_t *operation,
	vip_uint8_t **states_buffer_ptr,
	vip_uint32_t *states_size_ptr,
	vip_uint32_t op_index,
	vip_uint32_t *insert_index_ptr,
	nbglk_nld_operation_t **nld_operation_ptr,
	vip_uint8_t **nld_states_buffer_ptr,
	vip_uint8_t *nld_states_base,
	vip_uint32_t states_physical_base,
	vip_uint8_t *states_base
);
#endif
