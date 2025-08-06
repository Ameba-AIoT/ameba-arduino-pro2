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

#ifndef _NBG_LK_RELOCATE_H
#define _NBG_LK_RELOCATE_H
#include <nbg_lk_network.h>

#define CACULATE_NN_NUM_IN_NETWORK(network, nn_operation_count)                                       \
{   vip_int32_t x = 0;                                                                                \
    for (x = 0; x < (vip_int32_t)network->nbg_desc.n_operations; x++) {                               \
        nbg_desc_operation_t *op = &network->nbg_desc.operations[x];                                 \
        if (nbg_operation_is_nn_engine(op->type)) {             \
            nn_operation_count++;                                                                     \
        }                                                                                             \
    }                                                                                                 \
}

#define CACULATE_NN_NUM_IN_SEGMENT(segment, nn_operation_count)                                       \
{   vip_int32_t x = 0;                                                                                \
    for (x = segment->segm_start_id; x < (vip_int32_t)segment->segm_end_id + 1; x++) {                \
        nbg_desc_operation_t *op = &network->nbg_desc.operations[x];                                 \
        if (nbg_operation_is_nn_engine(op->type)) {             \
            nn_operation_count++;                                                                     \
        }                                                                                             \
    }                                                                                                 \
}

#if vpmdENABLE_CANCELATION > 1
#define APPEND_BREAKPOINT_CMDS(logical)                                                          \
if (i < (network->nbg_desc.n_operations - 1)) {                                                  \
    vip_uint32_t tmp_size = 0;                                                                   \
    nbg_desc_operation_t *next_operation = VIP_NULL;                                            \
    next_operation = &network->nbg_desc.operations[i + 1];                                       \
    if (operation->layer_id != next_operation->layer_id) {                                       \
        segment->bp_pos_table[bp_index] = (vip_uint32_t)(logical - (vip_uint8_t *)states_base);  \
        tmp_size = nbglk_append_breakpoint((vip_uint32_t*)logical);                              \
        states_size += tmp_size;                                                                 \
        states_buffer += tmp_size;                                                               \
        bp_index++;                                                                              \
    }                                                                                            \
}
#else
#define APPEND_BREAKPOINT_CMDS(logical)
#endif

#if vpmdENABLE_QUICK_RESET
#define APPEND_QUICKRST_CMDS(logical, event_id)                 \
{                                                               \
    vip_uint32_t count = 0;                                     \
    vip_uint32_t *tmp_data = (vip_uint32_t*)logical;            \
    tmp_data[count++] = 0x08010429;                             \
    tmp_data[count++] = event_id;                               \
    tmp_data[count++] = 0x08010E5A;                             \
    tmp_data[count++] = 0x00000001;                             \
    count = count * sizeof(vip_uint32_t);                       \
    if (count > QUICK_RESET_SIZE) {                             \
        vip_info("fail to insert quickly reset cmd\n");       \
    }                                                           \
    states_size += QUICK_RESET_SIZE;                            \
    states_buffer += QUICK_RESET_SIZE;                          \
}
#else
#define APPEND_QUICKRST_CMDS(logical, event_id)
#endif

#if vpmdENABLE_STALL_FE
#define APPEND_STALL_FE_CMDS(logical, event_id)                 \
{                                                               \
    vip_uint32_t count = 0;                                     \
    vip_uint32_t *tmp_data = (vip_uint32_t*)logical;            \
    tmp_data[count++] = 0x08010429;                             \
    tmp_data[count++] = event_id;                               \
    tmp_data[count++] = 0x08010e02;                             \
    tmp_data[count++] = 0x30000701;                             \
    tmp_data[count++] = 0x48000000;                             \
    tmp_data[count++] = 0x30000701;                             \
    count = count * sizeof(vip_uint32_t);                       \
    if (count > STALL_FE_SIZE) {                                \
        vip_info("fail to insert stall fe cmd size=%d\n", count); \
    }                                                           \
    states_size += STALL_FE_SIZE;                               \
    states_buffer += STALL_FE_SIZE;                             \
}
#else
#define APPEND_STALL_FE_CMDS(logical, event_id)
#endif


#if vpmdENABLE_CNN_PROFILING
#define CHECK_OPERATION_IN_SEGMENT(operation, segment, op_index)                          \
{                                                                                         \
  nbglk_context_t *t_context = nbglk_get_context();                                  \
  if (t_context->func_config.enable_cnn_profile == vip_true_e) {                          \
        if ((operation->type == NBG_OPERATION_TYPE_INIT) ||                             \
            (operation->type == NBG_OPERATION_TYPE_END) ||                              \
            (op_index != segment->segm_end_id)) {                                         \
            continue;                                                                     \
        }                                                                                 \
    }                                                                                     \
    else {                                                                                \
        if ((op_index >= segment->segm_end_id) || (op_index < segment->segm_start_id)) {  \
            continue;                                                                     \
        }                                                                                 \
    }                                                                                     \
}
#else
#define CHECK_OPERATION_IN_SEGMENT(operation, segment, op_index)                          \
{                                                                                         \
    if ((op_index >= segment->segm_end_id) || (op_index < segment->segm_start_id)) {      \
        continue;                                                                         \
    }                                                                                     \
}
#endif

/* 0x1000 for bypass specify operation id segment mode */
#if (vpmdHARDWARE_BYPASS_MODE & 0x1007)
/* used the NOP cmd to instead of engine's command to skip the operation execute */
#define APPEND_NOP_CMDS(buffer, size)                           \
/* replace load state with nop cmd */                           \
{                                                               \
    vip_uint32_t* nop_buffer = (vip_uint32_t*)buffer;           \
    vip_uint32_t nop_size = size;                               \
    while (NOP_CMD_SIZE <= nop_size) {                          \
        nop_size -= NOP_CMD_SIZE;                               \
        nop_buffer[0] = (3 << 27);                              \
        nop_buffer[1] = 0;                                      \
        nop_buffer += (NOP_CMD_SIZE / sizeof(vip_uint32_t));    \
    }                                                           \
}
#else
#define APPEND_NOP_CMDS(buffer, size)
#endif

#define CHECK_OPERATION_BYPASS(buffer, size)                    \
{                                                               \
    if ((operation->abs_op_id < network->op_segm.start_id) ||   \
        (operation->abs_op_id > network->op_segm.end_id)) {     \
        APPEND_NOP_CMDS(buffer, size);                          \
    }                                                           \
}

#define CACHE_CMD_SIZE              48
#define WORD_BIT0_TO_BIT25_MASK     0x03FFFFFF


enum nbglk_relocate_type_e {
	NBGLK_RELCAT_TYPE_NONE                = 0,
	NBGLK_RELCAT_TYPE_WEIGHT_HEADER       = 1,
	NBGLK_RELCAT_TYPE_WEIGHT_BITSTREAM    = 2,
	NBGLK_RELCAT_TYPE_PPU_INSTR           = 3,
	NBGLK_RELCAT_TYPE_DYNA_IO             = 4,
	NBGLK_RELCAT_TYPE_LOAD_STATES         = 5,
	NBGLK_RELCAT_TYPE_MAX
};

typedef struct _nbg_physical_value {
	vip_uint32_t low;
	vip_uint32_t high;
} nbg_physical_value_t;

vip_uint32_t get_start_bit(
	vip_uint32_t mask
);

vip_status_e nbglk_patch_init_command(
	vip_network_t *network
);

vip_status_e patch_source_misc_data(
	vip_network_t *network,
	nbglk_segment_t *segment,
	nbg_desc_operation_t *operation,
	vip_uint8_t *command,
	nbg_desc_patch_t *pd_entry,
	vip_uint32_t op_index
);

vip_status_e patch_source_mempool(
	vip_network_t *network,
	vip_uint8_t *command,
	nbg_desc_patch_t *patch
);

#if vpmdENABLE_MULTIPLE_VIP
vip_status_e patch_multivip_chipid(
	vip_network network,
	nbglk_segment_t *segment,
	vip_uint8_t *states_buffer,
	nbg_desc_patch_t *pd_entry
);

vip_status_e patch_multivip_sync_cmd(
	vip_network network,
	nbglk_segment_t *segment,
	vip_uint8_t *states_buffer,
	nbg_desc_patch_t *pd_entry
);

vip_uint32_t nbglk_append_chip_enable(
	vip_uint32_t *command,
	vip_uint32_t core_id,
	vip_bool_e   is_enable_all
);
#endif

vip_status_e patch_source_sram(
	vip_network_t *network,
	vip_uint8_t *command,
	nbg_desc_patch_t *patch,
	vip_uint32_t type
);

#if vpmdENABLE_CANCELATION > 1
vip_uint32_t nbglk_append_breakpoint(
	vip_uint32_t *command
);

vip_uint32_t nbglk_breakpoint_get_count(
	vip_network_t *network,
	nbglk_segment_t *segment
);

vip_status_e nbglk_breakpoint_change_p(
	vip_network_t *network
);

vip_status_e nbglk_breakpoint_change_n(
	vip_network_t *network
);

vip_status_e nbglk_breakpoint_init(
	vip_network_t *network
);

vip_status_e nbglk_breakpoint_uninit(
	vip_network_t *network
);
#endif

/*
@ brief
    insert link command in command buffer
*/
vip_status_e nbglk_insert_link(
	nbglk_segment_t *segment
);

vip_uint32_t *nbglk_append_link(
	vip_uint32_t *command,
	vip_uint32_t address
);

vip_uint32_t nbglk_append_nop(
	vip_uint32_t *command
);

vip_status_e nbglk_append_cmds(
	nbglk_videomemory_t *cmd_memory,
	vip_uint32_t *cmd_size,
	vip_bool_e with_event,
	vip_bool_e is_multi,
	vip_uint32_t id
);

vip_status_e nbglk_generate_command(
	vip_network_t *network,
	nbglk_segment_t *segment
);

#if vpmdDYNAMIC_CHANGE_MEM_POOL
vip_status_e nbglk_patch_memory_pool(
	vip_network_t *network,
	vip_buffer buffer
);
#endif

#endif
