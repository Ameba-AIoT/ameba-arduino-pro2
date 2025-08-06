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

#ifndef _NBG_FORMAT_V1_H_
#define _NBG_FORMAT_V1_H_

#include <vip_lite_common.h>

/* The vip lite binary data (file) is composed as following layout:
1. Fixed section.
    Where fixed information is stored, such as header, pool info, and data entries.

2. Dynamic section.
    Where the real data is stored, or indexed.
*/
/********************** The fixed part of the binary file *************************/

typedef struct _nbg_feature_database {
	vip_uint32_t hi_reorder_fix: 1; /* gcFEATURE_BIT_HI_REORDER_FIX */
	vip_uint32_t ocb_counter: 1;    /* gcFEATURE_BIT_OCB_COUNTER */
	vip_uint32_t nn_command_size: 2; /* the size of NN command, 0: 128bytes, 1: 192bytes */
	vip_uint32_t change_ppu_param: 1; /* 1: the NBG supports change PPU param, 0: not supports */
	vip_uint32_t tp_command_size: 2; /* the size of TP command, 0: 128bytes, 1: 192bytes */
	vip_uint32_t support_dma: 2; /* 0, not support, 1 support dma */
	vip_uint32_t nbg_40bit_va: 2;   /* 0:32bit va version va nbg, 1:40bit va version nbg */
	vip_uint32_t isp_emulator: 1;   /* 0: not support, 1: supports isp emulator */
	/* select the coeff base address to be used in relative address offset table */
	vip_uint32_t relat_addr_ker_id: 2;
	/* select the input image base address to be used in relative address offset table */
	vip_uint32_t relat_addr_inimage_id: 2;
	/* select the second input image base address to be used in relative address offset table */
	vip_uint32_t relat_addr_secinimage_id: 2;
	/* select the output image base address to be used in relative address offset table */
	vip_uint32_t relat_addr_outimage_id: 2;
	vip_uint32_t denoise_bypass: 1; /* 1: is denoise bypass network, , 0: not is denoise bypass network*/
	vip_uint32_t command_loop: 1; /* 1: support command loop, 0: not support*/
	vip_uint32_t job_cancel: 1; /* 1: support job cancellation, 0: not support*/
	vip_uint32_t nn_tp_probe: 1; /* 1: support tp/nn probe mode, 0: not support */
	vip_uint32_t kernel_descriptor: 1; /* 1: support nn single postmult fields in bitstream, 0, not support */
	vip_uint32_t nn_transpose_phase2: 1; /* 1: support transpose phase2, 0, not support */

	vip_uint32_t reserved: 6;      /* reserved bits */

	vip_uint32_t num_pixel_pipes;   /* NOT used */
	vip_uint8_t  core_count;        /* core count for this network */
	vip_uint8_t  device_index;         /* not use*/
	vip_uint8_t  axi_bus_width_index;/* 1:64bits, 2:128bits, 4:256bits */
	vip_uint8_t  cluster_id_width;  /* cluster id width */
	vip_uint8_t  nn_core_count;     /* nn core count */
	vip_uint8_t  tp_core_count;     /* tp core count */
	vip_uint8_t  reserved2;
	vip_uint8_t  reserved3;

	vip_uint32_t nbg_crc_sum;       /* CRC32 checksum  for NBG file, not include the checksum field */
	vip_uint32_t vip_sram_width;

	vip_uint32_t vsi_reserved[10];  /* reserved for  verisilicon */

	vip_uint32_t customer_reserved[48]; /* reserved for customer */
} nbg_feature_database_t;

typedef struct _nbg_header {
	vip_char_t      magic[4];
	vip_uint32_t    version;
	vip_uint32_t    hw_target;
	vip_char_t      network_name[NETWORK_NAME_SIZE];
	vip_uint32_t    layer_count;
	vip_uint32_t    operation_count;
	vip_uint32_t    input_count;
	vip_uint32_t    output_count;
	nbg_feature_database_t feature_db;
} nbg_header_t;

typedef struct _nbg_memory_pool {
	vip_uint32_t    size;
	vip_uint32_t    alignment;
	vip_uint32_t    base;
} nbg_memory_pool_t;

typedef struct _nbg_section_entry {
	vip_uint32_t    offset;
	vip_uint32_t    size;
} nbg_section_entry_t;

typedef struct _nbg_fixed_header {
	nbg_header_t        header;
	nbg_memory_pool_t          pool;
	vip_uint32_t              axi_sram_base;
	vip_uint32_t              axi_sram_size;
	vip_uint32_t              vip_sram_base;
	/* the size of vip-sram be used */
	vip_uint32_t              vip_sram_size;
	nbg_section_entry_t       layer_table;
	nbg_section_entry_t       operation_table;
	nbg_section_entry_t       coeff_header_table;
	nbg_section_entry_t       coeff_header; /* coeff header Data */
	nbg_section_entry_t       nn_op_data_table;
	nbg_section_entry_t       tp_op_data_table;
	nbg_section_entry_t       sh_op_data_table;
	nbg_section_entry_t       input_table;
	nbg_section_entry_t       output_table;
	nbg_section_entry_t       patch_data_table;
	nbg_section_entry_t       layer_param_table;
	nbg_section_entry_t       sw_op_data_table;
	nbg_section_entry_t       hw_init_op_table;
	nbg_section_entry_t       ICD_table;
	nbg_section_entry_t       ICD; /* Initialize Config Data */
	nbg_section_entry_t       ppu_param_table;
	nbg_section_entry_t       op_sync_Table;
	nbg_section_entry_t       dma_sbi_info;
	nbg_section_entry_t       dma_sbi_addition;
	nbg_section_entry_t       ppu_instr_table;
	nbg_section_entry_t       ppu_instr;
	nbg_section_entry_t       load_states_table;
	nbg_section_entry_t       load_states;
	nbg_section_entry_t       dyna_io_table;
	nbg_section_entry_t       dyna_io;
	nbg_section_entry_t       coeff_data_table;
	nbg_section_entry_t       coeff_data;

	/* layer dump */
	nbg_section_entry_t       ldump_operation;
	nbg_section_entry_t       ldump_outputs;
	nbg_section_entry_t       ldump_patch_data;
	nbg_section_entry_t       ldump_instr_table;
	nbg_section_entry_t       ldump_instr;
	nbg_section_entry_t       ldump_load_states_table;
	nbg_section_entry_t       ldump_load_states;
} nbg_fixed_header_t;

typedef struct _nbg_section_input_output {
	vip_uint32_t    dim_count;
	vip_uint32_t    dim_size[MAX_NUM_DIMS];
	vip_uint32_t    data_format;
	vip_uint32_t    data_type;
	vip_uint32_t    quan_format;
	vip_int32_t     fixed_pos;
	vip_float_t     tf_scale;
	vip_int32_t     tf_zerop;
	vip_char_t      name[MAX_IO_NAME_LEGTH];
} nbg_section_input_output_t;

typedef struct _nbg_section_input_output_old {
	vip_uint32_t    dim_count;
	vip_uint32_t    dim_size[OLD_MAX_NUM_DIMS];
	vip_uint32_t    data_format;
	vip_uint32_t    data_type;
	vip_uint32_t    quan_format;
	vip_int32_t     fixed_pos;
	vip_float_t     tf_scale;
	vip_int32_t     tf_zerop;
	vip_char_t      name[MAX_IO_NAME_LEGTH];
} nbg_section_input_output_old_t;

typedef struct _nbg_section_layer {
	vip_char_t      name[LAYER_NAME_SIZE];
	vip_uint32_t    node_id;
	vip_uint32_t    operation_count;
	vip_uint32_t    uid;
} nbg_section_layer_t;

/*
    0x0001001f: preempt | abs_share_id
    0x00010017: add abs_op_id
    0x00010011: add preempt
*/
typedef struct _nbg_section_operation {
	vip_uint32_t    type;
	vip_uint32_t    index;
	vip_uint32_t    layer_id;
	vip_uint32_t    state_id;    /* States buffer index in state load table. */
	vip_uint32_t    patch_index;
	vip_uint32_t    patch_count;
	vip_uint32_t    preempt: 4;
	vip_uint32_t    abs_share_id: 28; /* sharing coeff between multi-networks id. since 0x0001001f version */
	vip_uint32_t    abs_op_id;       /* absolute operation index */
} nbg_section_operation_t;

typedef struct _nbg_section_sh_operation {
	vip_uint32_t    instr_index;
	/* the index of nbg_section_ppu_param_t for changing PPU parameter */
	vip_uint32_t    ppu_param_index;
} nbg_section_sh_operation_t;

typedef struct _nbg_section_patch_table {
	vip_uint32_t    type;
	/* destination offset inside the state or command */
	vip_uint32_t    dest_offset;
	vip_uint32_t    source_type;
	vip_int32_t     index;
	/* the offset of new address */
	vip_uint32_t    src_offset;
	vip_uint32_t    transformed;
	vip_uint32_t    name;
	/* only for 40bit virtual address */
	vip_uint32_t    dest_offset_h;
	vip_uint32_t    src_offset_h;
	vip_uint32_t    mask_h;
} nbg_section_patch_table_t;

typedef struct _nbg_section_layer_parameter {
	vip_char_t      param_name[MAX_LAYER_PARAM_NAME_LENGTH];
	vip_uint32_t    dim_count;
	vip_uint32_t    dims[MAX_NUM_DIMS];
	vip_uint32_t    data_format;
	vip_uint32_t    data_type;
	vip_uint32_t    quant_format;
	vip_int32_t     fixpoint_zeropoint;
	vip_float_t     tfscale;
	vip_int32_t     index;
	vip_uint32_t    address_offset;
	vip_uint32_t    source_type;
} nbg_section_layer_parameter_t;

typedef struct _nbg_section_layer_parameter_old {
	vip_char_t      param_name[MAX_LAYER_PARAM_NAME_LENGTH];
	vip_uint32_t    dim_count;
	vip_uint32_t    dims[OLD_MAX_NUM_DIMS];
	vip_uint32_t    data_format;
	vip_uint32_t    data_type;
	vip_uint32_t    quant_format;
	vip_uint32_t    fixpoint_zeropoint;
	vip_float_t     tfscale;
	vip_int32_t     index;
	vip_uint32_t    address_offset;
	vip_uint32_t    source_type;
} nbg_section_layer_parameter_old_t;

typedef struct _nbg_section_sw_operation {
	vip_uint32_t    sw_peration_type;
	vip_char_t      name[MAX_SW_LAYER_NAME_LENGTH];
} nbg_section_sw_operation_t;

typedef struct _nbg_section_hw_init_operation {
	vip_uint32_t    state_id;       /* States buffer index in state load table. */
	vip_uint32_t    patch_index;    /* the first index in patch table */
	vip_uint32_t    patch_count;    /* the total patch count in patch table */
} nbg_section_hw_init_operation_t;

typedef struct _nbg_section_ppu_param {
	vip_uint32_t    global_offset_x;
	vip_uint32_t    global_offset_y;
	vip_uint32_t    global_offset_z;
	vip_uint32_t    global_scale_x;
	vip_uint32_t    global_scale_y;
	vip_uint32_t    global_scale_z;
	vip_uint32_t    group_size_x;
	vip_uint32_t    group_size_y;
	vip_uint32_t    group_size_z;
	vip_uint32_t    group_count_x;
	vip_uint32_t    group_count_y;
	vip_uint32_t    group_count_z;
} nbg_section_ppu_param_t;

typedef struct _nbg_ldump_operation {
	vip_uint32_t    insert_index;
	vip_uint32_t    loadstate_index;
	vip_uint32_t    start_patch_index;
	vip_uint32_t    patch_count;
	vip_uint32_t    core_id;
	vip_uint32_t    wait_count;
} nbg_ldump_operation_t;

typedef struct _nbg_ldump_output_t {
	nbg_section_input_output_t     info;
} nbg_ldump_output_t;

#endif
