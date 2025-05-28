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

#ifndef _NBG_FORMAT_DESCRIPTOR_H_
#define _NBG_FORMAT_DESCRIPTOR_H_

#include <vip_lite_config.h>

#define NETWORK_NAME_SIZE           64
#define LAYER_NAME_SIZE             64
#define MAX_SW_LAYER_NAME_LENGTH    64
#define MAX_LAYER_PARAM_NAME_LENGTH 16
#define MAX_IO_NAME_LEGTH           64
#define CMD_SIZE_128                128
#define CMD_SIZE_192                192
#define MAX_NUM_DIMS                6
#define OLD_MAX_NUM_DIMS            4
#define SIZE_CHECK_ERROR            0

typedef struct _nbg_desc_operation_128 {
	vip_uint8_t    cmd[CMD_SIZE_128];
} nbg_desc_operation_128_t;

typedef struct _nbg_desc_operation_192 {
	vip_uint8_t    cmd[CMD_SIZE_192];
} nbg_desc_operation_192_t;

typedef struct _nbg_desc_header {
	vip_uint32_t    version;
	vip_uint32_t    hw_target;
	vip_uint32_t    nbg_crc_sum;         /* CRC32 checksum  for NBG file, not include the checksum field */
	vip_uint32_t    class: 1;   /* 0: 32bit format, 1: 64bit format */
	vip_uint32_t    reserved1: 31;
} nbg_desc_header_t;

typedef struct _nbg_desc_entry {
	vip_size_t    offset;
	vip_size_t    size;
} nbg_desc_entry_t;

typedef struct _nbg_desc_data_table {
	vip_size_t    offset;
	vip_size_t    size;
} nbg_desc_data_table_t;

typedef struct _nbg_desc_sh_operation {
	vip_uint32_t    instr_index;
	/* the index of nbg_section_ppu_param_t for changing PPU parameter */
	vip_uint32_t    ppu_param_index;
} nbg_desc_sh_operation_t;

typedef struct _nbg_desc_layer_parameter {
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
} nbg_desc_layer_parameter_t;

typedef struct _nbg_desc_sw_operation {
	vip_uint32_t    sw_peration_type;
	vip_char_t      name[MAX_SW_LAYER_NAME_LENGTH];
} nbg_desc_sw_operation_t;

typedef struct _nbg_desc_patch {
	vip_uint32_t    type;
	/* destination offset inside the state or command */
	vip_uint32_t    dest_offset;
	vip_uint32_t    source_type;
	vip_int32_t     index;
	/* the offset of new address */
	vip_size_t      src_offset;
	vip_uint32_t    transformed;
	vip_uint32_t    name;
	/* only for address >= 4G */
	vip_uint32_t    dest_offset_h;
	vip_uint32_t    mask_h;
} nbg_desc_patch_t;

typedef struct _nbg_desc_layer {
	vip_char_t      name[LAYER_NAME_SIZE];
	vip_uint32_t    node_id;
	vip_uint32_t    operation_count;
	vip_uint32_t    uid;
} nbg_desc_layer_t;

typedef struct _nbg_desc_operation {
	vip_uint32_t    type;
	vip_uint32_t    index;
	vip_uint32_t    layer_id;
	vip_uint32_t    state_id;    /* States buffer index in state load table. */
	vip_uint32_t    patch_index;
	vip_uint32_t    patch_count;
	vip_uint32_t    preempt: 4;
	vip_uint32_t    abs_share_id: 28; /* sharing coeff between multi-networks id. since 0x0001001f version */
	vip_uint32_t    abs_op_id;       /* absolute operation index */
} nbg_desc_operation_t;

typedef struct _nbg_desc_fixed_header {
	nbg_desc_header_t      header;

	/* section data entry table deinfes  */
	nbg_desc_entry_t       load_states;
	nbg_desc_entry_t       nn_op_data_table;
	nbg_desc_entry_t       tp_op_data_table;
	nbg_desc_entry_t       ICD; /* Initialize Config Data */
	nbg_desc_entry_t       ppu_instr;
	nbg_desc_entry_t       dyna_io;
	nbg_desc_entry_t       coeff_header; /* coeff header Data */
	nbg_desc_entry_t       coeff_data;

	/* layer dump */
	nbg_desc_entry_t       ldump_operation;
	nbg_desc_entry_t       ldump_instr_table;
	nbg_desc_entry_t       ldump_load_states_table;
	nbg_desc_entry_t       ldump_patch_data;
	nbg_desc_entry_t       ldump_outputs;
	nbg_desc_entry_t       ldump_instr;
	nbg_desc_entry_t       ldump_load_states;
} nbg_desc_fixed_header_t;

typedef struct _nbg_desc_network_attribute_t {
	vip_uint32_t change_ppu_param;/* 1: the NBG supports change PPU param, 0: not supports */
	vip_uint32_t nn_command_size; /* the size of NN command, 0: 128bytes, 1: 192bytes */
	vip_uint32_t tp_command_size; /* the size of TP command, 0: 128bytes, 1: 192bytes */
	vip_uint32_t support_dma;     /* 0, not support, 1 support dma */
	vip_uint32_t reserved;

	vip_uint32_t vsi_reserved[31];  /* reserved */
} nbg_desc_network_attribute_t;

typedef struct _nbg_desc_network_info {
	vip_char_t                name[NETWORK_NAME_SIZE];
	vip_uint32_t              input_count;
	vip_uint32_t              output_count;
	vip_uint32_t              layer_count;
	vip_uint32_t              abs_op_count;
	/* hw run instruction count, it maybe bigger than saved instruction command count, such as share command*/
	vip_uint32_t              operation_count;
	vip_uint8_t               core_count;
	/* the maximum  patch address width of bits used for this network. Used to select patch_table. */
	vip_uint32_t              address_width;

	nbg_desc_network_attribute_t   attribute;
} nbg_desc_network_info_t;

typedef struct _nbg_desc_memory_info {
	/* the size of memory pool used by the network */
	vip_size_t             pool_size;
	/* the size of axi-sram used by the network */
	vip_uint32_t           axi_sram_size;
	/* the size of vip-sram be used */
	vip_uint32_t           vip_sram_size;
} nbg_desc_memory_info_t;

typedef struct _nbg_desc_section_checksum {
	vip_uint32_t              load_states;
	vip_uint32_t              coeff_data;
	vip_uint32_t              ppu_instr;
} nbg_desc_section_checksum_t;

typedef struct _nbg_desc_hw_init_operation {
	vip_uint32_t    state_id;       /* States buffer index in state load table. */
	vip_uint32_t    patch_index;    /* the first index in patch table */
	vip_uint32_t    patch_count;    /* the total patch count in patch table */
} nbg_desc_hw_init_operation_t;

typedef struct _nbg_desc_input_output {
	/*The number of dimensions specified in *sizes*/
	vip_uint32_t          dim_count;
	/*The pointer to an array of dimension */
	vip_uint32_t          dim_size[MAX_NUM_DIMS];
	/*Data format for the tensor */
	vip_uint32_t          data_format;
	vip_uint32_t          data_type;
	/*Quantized format */
	vip_uint32_t          quant_format;
	/*The union of quantization information */
	union {
		struct {
			/* Indicates the fixed point position for dynamic fix point quantization format. */
			vip_int32_t   fixed_point_pos;
		} dfp;
		struct {
			/*Scale value for the quantized value */
			vip_float_t   tf_scale;
			/* Indicates the zero point for quantization format. */
			vip_int32_t   tf_zero_point;
		} affine;
	} quant_data;
	vip_char_t            name[MAX_IO_NAME_LEGTH];
} nbg_desc_input_output_t;

typedef struct _nbg_desc_ppu_param {
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
} nbg_desc_ppu_param_t;

typedef struct _nbg_desc_ldump_operation {
	vip_uint32_t    insert_index;
	vip_uint32_t    loadstate_index;
	vip_uint32_t    start_patch_index;
	vip_uint32_t    patch_count;
	vip_uint32_t    core_id;
	vip_uint32_t    wait_count;
} nbg_desc_ldump_operation_t;

typedef struct _nbg_desc_ldump_output {
	nbg_desc_input_output_t     info;
} nbg_desc_ldump_output_t;

typedef struct _nbg_fmt_descriptor {
	/* header of NBG */
	nbg_desc_fixed_header_t       fixed;

	/* section data of NBG */
	nbg_desc_network_info_t       net_info;
	nbg_desc_memory_info_t        mem_info;
	nbg_desc_section_checksum_t   check_sum;

	nbg_desc_input_output_t       *inputs;
	nbg_desc_input_output_t       *outputs;
	nbg_desc_layer_t              *orig_layers;
	nbg_desc_operation_t          *operations;

	nbg_desc_data_table_t         *coeff_header_table;
	nbg_desc_data_table_t         *coeff_data_table;
	nbg_desc_data_table_t         *ppu_instr_table;
	nbg_desc_data_table_t         *dyna_io_table;
	nbg_desc_data_table_t         *load_states_table;
	nbg_desc_ppu_param_t          *ppu_param;
	nbg_desc_sh_operation_t       *sh_ops;
	nbg_desc_sw_operation_t       *sw_ops;
	nbg_desc_patch_t              *pd_sections;
	nbg_desc_layer_parameter_t    *lp_entries;
	nbg_desc_hw_init_operation_t  *init_ops;
	/* Initialize Config Data Table */
	nbg_desc_data_table_t         *ICDT;

	/* layerdump */
	nbg_desc_patch_t              *ldump_patch_data;
	nbg_desc_ldump_output_t       *ldump_outputs;
	nbg_desc_ldump_operation_t    *ldump_operation;
	nbg_desc_data_table_t         *ldump_instr_table;
	nbg_desc_data_table_t         *ldump_load_states_table;
	void                          *ldump_load_states_logical;
	void                          *ldump_instr_logical;

	/* the number of items in the dynamic section */
	vip_uint32_t                    n_inputs;
	vip_uint32_t                    n_outputs;
	vip_uint32_t                    n_orig_layers;
	vip_uint32_t                    n_operations;
	vip_uint32_t                    n_coeff_header;
	vip_uint32_t                    n_coeff_data;
	vip_uint32_t                    n_load_state;
	vip_uint32_t                    n_ppu_instr;
	vip_uint32_t                    n_dyna_io;
	vip_uint32_t                    n_nn_ops;
	vip_uint32_t                    n_tp_ops;
	vip_uint32_t                    n_sh_ops;
	vip_uint32_t                    n_pd_sections;
	vip_uint32_t                    n_layer_param;
	vip_uint32_t                    n_sw_ops;
	vip_uint32_t                    n_hw_init_ops;
	vip_uint32_t                    n_ICDT;
	vip_uint32_t                    n_ppu_param;
	vip_bool_e                      coeff_data_writable;
	/* 1: the nbg_desc part memory has been freed */
	vip_bool_e                      corrupted;

	vip_uint32_t                    n_ldump_patch_data;
	vip_uint32_t                    n_ldump_outputs;
	vip_uint32_t                    n_ldump_operation;
	vip_uint32_t                    n_ldump_instr_table;
	vip_uint32_t                    n_ldump_load_states_table;
} nbg_fmt_descriptor_t;
#endif
