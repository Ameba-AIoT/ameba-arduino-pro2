/******************************************************************************\
|* Copyright (c) 2017-2023 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/

#ifndef _GC_VIP_NBG_H
#define _GC_VIP_NBG_H
#include <gc_vip_lite_network.h>
#include <gc_vip_nbg_format.h>

#if vpmdCREATE_NETWORK_FROM_FLASH
#define GCVIP_CHECK_DYNA_IS_NULL()
#else
#define GCVIP_CHECK_DYNA_IS_NULL()  \
    if ((VIP_NULL == network->dyna_data_two) || (VIP_NULL == network->dyna_data)) { \
        gcvip_warning("fail dynamic data is NULL, should create network again\n");   \
        return VIP_ERROR_FAILURE; \
    }
#endif

#if vpmdENABLE_CANCELATION > 1
#define APPEND_BREAKPOINT_CMDS(logical)                         \
if (i < (network->n_operations - 1)) {                          \
    vip_uint32_t tmp_size = 0;                                  \
    gcvip_bin_operation_t *next_operation = VIP_NULL;           \
    next_operation = gcvip_get_operation_ptr_by_index(network, network->operations, i+1); \
    if (operation->layer_id != next_operation->layer_id) {      \
        segment->bp_pos_table[bp_index] = (vip_uint32_t)(logical - (vip_uint8_t *)states_base);  \
        tmp_size = gcvip_append_breakpoint((vip_uint32_t*)logical);      \
        states_size += tmp_size;                                \
        states_buffer += tmp_size;                              \
        bp_index++;                                             \
    }                                                           \
}
#else
#define APPEND_BREAKPOINT_CMDS(logical)
#endif

#if vpmdENABLE_QUICK_RESET
#define APPEND_QUICKRST_CMDS(logical)                           \
{                                                               \
    vip_uint32_t count = 0;                                     \
    vip_uint32_t *tmp_data = (vip_uint32_t*)logical;            \
    tmp_data[count++] = 0x08010429;                             \
    tmp_data[count++] = 0x00000000;                             \
    tmp_data[count++] = 0x08010E5A;                             \
    tmp_data[count++] = 0x00000001;                             \
    count = count * sizeof(vip_uint32_t);                       \
    if (count > QUICK_RESET_SIZE) {                             \
        gcvip_info("fail to insert quickly reset cmd\n");       \
    }                                                           \
    states_size += QUICK_RESET_SIZE;                            \
    states_buffer += QUICK_RESET_SIZE;                          \
}
#else
#define APPEND_QUICKRST_CMDS(logical)
#endif

#if vpmdENABLE_LAYER_DUMP
#define CHECK_OPERATION_IN_SEGMENT(operation, segment, op_index)  \
{                                                                 \
    if (((operation->type != GCVIP_OPERATION_TYPE_INIT) ||        \
        (segment->segm_start_id != 0)) &&                         \
        ((operation->type != GCVIP_OPERATION_TYPE_END) ||         \
         (segment->segm_end_id != network->n_orig_layers)) &&     \
        ((operation->layer_id >= segment->segm_end_id) ||         \
        (operation->layer_id < segment->segm_start_id))) {        \
        continue;                                                 \
    }                                                             \
}
#elif vpmdENABLE_CNN_PROFILING
#define CHECK_OPERATION_IN_SEGMENT(operation, segment, op_index)                          \
{                                                                                         \
  gcvip_lite_context_t *t_context = gcvip_get_context();                                  \
  if (t_context->func_config.enable_cnn_profile == vip_true_e) {                          \
        if ((operation->type == GCVIP_OPERATION_TYPE_INIT) ||                             \
            (operation->type == GCVIP_OPERATION_TYPE_END) ||                              \
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

#if (vpmdHARDWARE_BYPASS_MODE & 0x7)
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

#define CACHE_CMD_SIZE              48

enum gcvip_lcdt_type_e {
	GCVIP_LCDT_TYPE_NONE           = 0,
	GCVIP_LCDT_TYPE_WEIGHT         = 1,
	GCVIP_LCDT_TYPE_PPU_INSTR      = 2,
	GCVIP_LCDT_TYPE_DYNA_IO        = 3,
	GCVIP_LCDT_TYPE_LOAD_STATES    = 4,
	GCVIP_LCDT_TYPE_MAX
};

enum gcvip_patch_transformation_e {
	GCVIP_PATCH_TRANSFORMATION_ORIGINAL = 0,
	GCVIP_PATCH_TRANSFORMATION_RIGHT_SHIFT_6,
};

enum gcvip_patch_type_e {
	GCVIP_PATCH_TYPE_STATE   = 0,     /* Patch state stream. */
	GCVIP_PATCH_TYPE_COMMAND = 1,     /* Patch for NN/TP command. */
	GCVIP_PATCH_TYPE_KERNEL  = 2,     /* Patch coeff(kernel) for NN */
};

enum gcvip_nn_command_size_e {
	GCVIP_NN_COMMAND_SIZE_128 = 0,
	GCVIP_NN_COMMAND_SIZE_192 = 1,
};

enum gcvip_tp_command_size_e {
	GCVIP_TP_COMMAND_SIZE_128 = 0,
	GCVIP_TP_COMMAND_SIZE_192 = 1,
};

typedef enum _gcvip_cmd_type {
	GCVIP_OPERATION_TYPE_NONE       = 0,
	GCVIP_OPERATION_TYPE_SH         = 1,
	GCVIP_OPERATION_TYPE_NN         = 2,
	GCVIP_OPERATION_TYPE_TP         = 3,
	GCVIP_OPERATION_TYPE_SW         = 4,
	GCVIP_OPERATION_TYPE_SC         = 5,
	GCVIP_OPERATION_TYPE_SP         = 6,
	GCVIP_OPERATION_TYPE_END        = 0xFFFE,
	GCVIP_OPERATION_TYPE_INIT       = 0xFFFF,
} gcvip_cmd_type_e;

enum gcvip_source_type_e {
	GCVIP_SOURCE_COMMAND        = 0,
	GCVIP_SOURCE_INPUT          = 1,
	GCVIP_SOURCE_OUTPUT         = 2,
	GCVIP_SOURCE_MEMORY_POOL    = 3,
	GCVIP_SOURCE_AXI_SRAM       = 4,
	GCVIP_SOURCE_MISC_DYNA_GENERIC = 5,
	GCVIP_SOURCE_MISC_DYNA_INPUT   = 6,
	GCVIP_SOURCE_MISC_DYNA_OUTPUT  = 7,
	GCVIP_SOURCE_VIP_SRAM          = 8,
	GCVIP_SOURCE_KERNEL_BITSTREAM  = 9,    /* patch kernel's bit stream */
	GCVIP_SOURCE_MULTIVIP_CHIPID    = 100, /* for multiVIP only */
	GCVIP_SOURCE_MULTIVIP_SYNC_CMDS = 101,
};

typedef enum _gcvip_create_network_from {
	GCVIP_CREATE_NETWORK_FROM_NONE    = 0,
	GCVIP_CREATE_NETWORK_FROM_FILE    = 1,
	GCVIP_CREATE_NETWORK_FROM_MEMORY  = 2,
	GCVIP_CREATE_NETWORK_FROM_FLASH   = 3,
} gcvip_create_network_from_e;

typedef struct _data_reader {
	vip_uint32_t    offset;
	vip_uint32_t    total_size;
	vip_char_t      *data;
	vip_char_t      *current_data;
	gcvip_file_t    file;
	vip_uint32_t    create_from; /* see gcvip_create_network_from_e */
} gcvip_data_reader;

vip_status_e gvip_read_nbg(
	vip_network_t *network,
	void *data,
	vip_uint32_t size,
	gcvip_file_t file
);

vip_status_e gcvip_patch_init_states(
	vip_network_t *network
);

vip_status_e gcvip_patch_init_command(
	vip_network_t *network
);
vip_status_e patch_source_misc_data(
	vip_network_t *network,
	gcvip_lite_segment_t *segment,
	gcvip_bin_operation_t *operation,
	vip_uint8_t *command,
	gcvip_bin_patch_data_entry_t *pd_entry,
	vip_uint32_t op_index
);

vip_status_e patch_source_mempool(
	vip_network_t *network,
	vip_uint8_t *command,
	gcvip_bin_patch_data_entry_t *patch
);

#if vpmdENABLE_MULTIPLE_VIP
vip_status_e patch_multivip_chipid(
	vip_network network,
	vip_uint8_t *states_buffer,
	gcvip_bin_patch_data_entry_t *pd_entry
);

vip_status_e patch_multivip_sync_cmd(
	vip_network network,
	vip_uint8_t *states_buffer,
	gcvip_bin_patch_data_entry_t *pd_entry
);
#endif

vip_status_e patch_source_sram(
	vip_network_t *network,
	vip_uint8_t *command,
	gcvip_bin_patch_data_entry_t *patch,
	vip_uint32_t type
);

gcvip_bin_patch_data_entry_t *gcvip_get_patch_ptr_by_index(
	vip_network_t *network,
	gcvip_bin_patch_data_entry_t *patch_ptr,
	vip_int32_t index
);

gcvip_bin_operation_t *gcvip_get_operation_ptr_by_index(
	vip_network_t *network,
	gcvip_bin_operation_t *op_ptr,
	vip_int32_t index
);

void *gcvip_get_io_ptr_by_index(
	vip_network_t *network,
	gcvip_bin_inout_entry_t *io_ptr,
	vip_int32_t index
);

void *gcvip_get_nn_op_ptr_by_index(
	vip_network_t *network,
	void *nn_op,
	vip_uint32_t index
);

void *gcvip_get_tp_op_ptr_by_index(
	vip_network_t *network,
	void *tp_op,
	vip_uint32_t index
);

void *gcvip_get_sh_op_ptr_by_index(
	vip_network_t *network,
	void *sh_op,
	vip_uint32_t index
);

vip_uint32_t gcvip_get_nn_command_size(
	vip_network_t *network
);

vip_uint32_t gcvip_get_tp_command_size(
	vip_network_t *network
);

vip_char_t *gcvip_get_layer_name(
	vip_network_t *network,
	vip_uint32_t layer_id
);

vip_uint32_t gcvip_get_layer_uid(
	vip_network_t *network,
	vip_uint32_t layer_id
);

/*
@brief Get the byte of buffer format.
@param format
*/
vip_uint32_t gcvip_get_format_byte(
	vip_enum format
);

/*
@brief Get the bit of buffer format.
@param format
*/
vip_uint32_t gcvip_get_format_bit(
	vip_enum format
);

vip_uint32_t gcvip_get_io_buffer_size(
	gcvip_bin_inout_entry_t *entry
);

#if vpmdENABLE_CANCELATION > 1
vip_uint32_t gcvip_append_breakpoint(
	vip_uint32_t *command
);

vip_uint32_t gcvip_breakpoint_get_count(
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);

vip_status_e gcvip_breakpoint_change_p(
	vip_network_t *network
);

vip_status_e gcvip_breakpoint_change_n(
	vip_network_t *network
);

vip_status_e gcvip_breakpoint_init(
	vip_network_t *network
);

vip_status_e gcvip_breakpoint_uninit(
	vip_network_t *network
);
#endif

void gcvip_open_reader(
	gcvip_data_reader *reader,
	void *data,
	vip_uint32_t size,
	void *file
);

void gcvip_close_reader(
	gcvip_data_reader *reader
);

/*
@ brief
    insert link command in command buffer
*/
vip_status_e gcvip_insert_link(
	gcvip_lite_segment_t *segment
);

vip_uint32_t *gcvip_append_link(
	vip_uint32_t *command,
	vip_uint32_t bytes,
	vip_uint32_t address
);

vip_status_e gcvip_append_cmds(
	gcvip_videomemory_t *cmd_memory,
	vip_uint32_t *cmd_size,
	vip_bool_e with_event,
	vip_bool_e is_multi,
	vip_uint32_t id
);

vip_status_e gcvip_generate_command(
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);

#endif
