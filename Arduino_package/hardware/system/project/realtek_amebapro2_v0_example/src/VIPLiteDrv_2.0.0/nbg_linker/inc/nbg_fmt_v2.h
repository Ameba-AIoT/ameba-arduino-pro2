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

#ifndef _NBG_FORMAT_V2_H_
#define _NBG_FORMAT_V2_H_

#include <vip_lite_common.h>
#include <nbg_fmt_util.h>

#define CONSTRUCT_U64(high, low) (((vip_uint64_t)(high) << 32) | (low))

typedef enum _nbg_section_type {
	/*
	* nbg need works fine with backward compatibity, the section type could not be deleted or change order.
	*/
	NBG_SECTION_NONE = 0,
	NBG_SECTION_INPUT = 1,
	NBG_SECTION_OUTPUT = 2,
	NBG_SECTION_LAYER = 3,
	NBG_SECTION_OPERATIONS = 4,
	NBG_SECTION_COEF_HEADER_TABLE = 5,
	NBG_SECTION_COEF_HEADER = 6,
	NBG_SECTION_NN = 7,
	NBG_SECTION_TP = 8,
	NBG_SECTION_SH = 9,
	NBG_SECTION_PATCH = 10,
	NBG_SECTION_LAYER_PARAM = 11,
	NBG_SECTION_SW = 12,
	NBG_SECTION_HWINITOPERATIONS = 13,
	NBG_SECTION_ICDT = 14,
	NBG_SECTION_ICD = 15,
	NBG_SECTION_PPU_PARAM = 16,
	NBG_SECTION_OPSYNC = 17,
	NBG_SECTION_DMA_SBI_INFO = 18,
	NBG_SECTION_PPU_INSTR = 19,
	NBG_SECTION_DYNAIO = 20,
	NBG_SECTION_LOADSTATE = 21,
	NBG_SECTION_DMA_SBI_ADDITION = 22,
	NBG_SECTION_COEF_DATA_TABLE = 23,
	NBG_SECTION_COEF_DATA = 24,
	NBG_SECTION_PPU_INSTR_TABLE = 25,
	NBG_SECTION_DYNAIO_TABLE = 26,
	NBG_SECTION_LOADSTATE_TABLE = 27,

	NBG_SECTION_LAYER_DUMP_OPERATION = 28,
	NBG_SECTION_LAYER_DUMP_OUTPUTS = 29,
	NBG_SECTION_LAYER_DUMP_PATCH_DATA = 30,
	NBG_SECTION_LAYER_DUMP_INSTR_TABLE = 31,
	NBG_SECTION_LAYER_DUMP_INSTR = 32,
	NBG_SECTION_LAYER_DUMP_LOADSTATE_TABLE = 33,
	NBG_SECTION_LAYER_DUMP_LOADSTATE = 34,

	NBG_SECTION_NETWORK_INFO = 35,
	NBG_SECTION_CUSTOMER_DATA = 36,
	NBG_SECTION_MEMORY_POOL = 37,
	NBG_SECTION_VIP_SRAM = 38,
	NBG_SECTION_AXI_SRAM = 39,
	NBG_SECTION_CHECKSUM = 40,

	NBG_SECTION_MAX,
} nbg_section_type_e;

typedef struct _nbg_network_attribute_t {
	vip_uint32_t change_ppu_param: 1; /* 1: the NBG supports change PPU param, 0: not supports */
	vip_uint32_t nn_command_size: 2; /* the size of NN command, 0: 128bytes, 1: 192bytes */
	vip_uint32_t tp_command_size: 2; /* the size of TP command, 0: 128bytes, 1: 192bytes */
	vip_uint32_t support_dma: 2;    /* 0, not support, 1 support dma */
	vip_uint32_t reserved: 25;

	vip_uint32_t vsi_reserved[31];  /* reserved */
} nbg_network_attribute_t;

typedef struct _nbg_section_network_info {
	vip_char_t                name[NETWORK_NAME_SIZE];
	vip_uint32_t              input_count;
	vip_uint32_t              output_count;
	vip_uint32_t              layer_count;
	vip_uint32_t              abs_op_count;
	/* hw run instruction count, it maybe bigger than saved instruction command count, such as share command*/
	vip_uint32_t              operation_count;
	vip_uint32_t              core_count;
	/* the maximum  patch address width of bits used for this network. Used to select patch_table. */
	vip_uint32_t              address_width;
	nbg_network_attribute_t   attribute;
} nbg_section_network_info_t;

typedef struct _nbg_section_checksum {
	vip_uint32_t              sd_type;
	vip_uint32_t              checksum_value;
} nbg_section_checksum_t;

typedef struct _nbg_section_input_output {
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
} nbg_section_input_output_t;

typedef struct _nbg_section_layer {
	vip_char_t      name[LAYER_NAME_SIZE];
	vip_uint32_t    node_id;
	vip_uint32_t    operation_count;
	vip_uint32_t    uid;
} nbg_section_layer_t;

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
} nbg_section_patch_table_t;

typedef struct _nbg_section_patch_table_40bit {
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
} nbg_section_patch_table_40bit_t;

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

typedef struct _nbg_section_memory_pool {
	vip_uint32_t               used_size_low;
	vip_uint32_t               used_size_high;
} nbg_section_memory_pool_t;

typedef struct _nbg_section_vip_sram {
	vip_uint32_t               used_size;
} nbg_section_vip_sram_t;

typedef struct _nbg_section_axi_sram {
	vip_uint32_t               used_size;
} nbg_section_axi_sram_t;

/* use for 32bit NBG section entry */
typedef struct _nbg_section_entry_32bit {
	vip_uint32_t    offset;
	vip_uint32_t    size;
} nbg_section_entry_32bit_t;

/* use for 64bit NBG section entry */
typedef struct _nbg_section_entry_64bit {
	vip_uint64_t    offset;
	vip_uint64_t    size;
} nbg_section_entry_64bit_t;

typedef struct _nbg_format_header {
	vip_char_t      magic[4]; /* Magic no: 'V', 'P', 'M', 'N'. */
	vip_uint32_t    version;
	vip_uint32_t    target;
	vip_uint32_t    crc_sum;
	vip_uint32_t    total_size_low; /* total size of file */
	vip_uint32_t    total_size_high;
	vip_uint32_t    sub_header_offset; /* the start offset in file of sub header of one nbg */
	vip_uint32_t    sub_header_size; /* the total size of sub header of one nbg */
	vip_uint32_t    sub_header_count;
	vip_uint32_t    class: 1;   /* 0: 32bit format, 1: 64bit format */
	vip_uint32_t    reserved1: 31;
	vip_uint32_t    reserved2;
	vip_uint32_t    reserved3;
} nbg_format_header_t;

typedef struct _nbg_sub_header {
	vip_uint32_t    sh_offset; /* the start offset in file of section header of one nbg*/
	vip_uint32_t    sh_size; /* the size of one section header struct */
	vip_uint32_t    sh_count; /* section header count of one nbg */
} nbg_sub_header_t;

typedef struct _nbg_section_header {
	vip_uint32_t    sd_type; /* the type of section data */
	vip_uint32_t    sd_offset_low; /* section data offset in file */
	vip_uint32_t    sd_offset_high;
	vip_uint32_t    sd_size_low; /* the total size of section data */
	vip_uint32_t    sd_size_high;
	/* If the nbg is executable, the address of this section data should be load in address space */
	vip_uint32_t    sd_addr_low;
	vip_uint32_t    sd_addr_high;
	vip_uint32_t    sd_alignsize; /* section data start offset align size */
	vip_uint32_t    sd_entsize; /* the entry size of one section data */
	vip_uint32_t    reserved1;
	vip_uint32_t    reserved2;
} nbg_section_header_t;

typedef struct _nbg_header {
	nbg_format_header_t       header;
	nbg_sub_header_t          sub_header;
	nbg_section_header_t      *section_header;
} nbg_header_t;

vip_status_e nbg_fmt_read_header(
	nbg_fmt_reader_t *reader,
	nbg_header_t *nbg_header,
	nbg_fmt_descriptor_t *nbg_desc
);

vip_status_e nbg_fmt_read_section(
	nbg_fmt_reader_t *reader,
	nbg_header_t *nbg_header,
	nbg_fmt_descriptor_t *nbg_desc
);

#endif
