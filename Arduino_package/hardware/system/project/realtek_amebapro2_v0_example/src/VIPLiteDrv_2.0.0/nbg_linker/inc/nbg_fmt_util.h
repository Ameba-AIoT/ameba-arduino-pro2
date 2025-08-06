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

#ifndef _NBG_FORMAT_UTIL_H_
#define _NBG_FORMAT_UTIL_H_
#include <nbg_fmt_descriptor.h>
#include <vip_hal_os_port.h>

#if SIZE_CHECK_ERROR
vip_uint32_t size_check_error(void);
#define SIZE_CAST(T, V) ((0xffffffff00000000 & (vip_uint64_t)(V)) ? size_check_error() : (T)(V))
#else
#define SIZE_CAST(T, V) ((T)(V))
#endif

#define BITS_PER_BYTE       8

enum nbg_patch_transformation_e {
	NBG_PATCH_TRANSFORMATION_ORIGINAL = 0,
	NBG_PATCH_TRANSFORMATION_RIGHT_SHIFT_6,
};

enum nbg_patch_type_e {
	NBG_PATCH_TYPE_STATE   = 0,     /* Patch state stream. */
	NBG_PATCH_TYPE_COMMAND = 1,     /* Patch for NN/TP command. */
	NBG_PATCH_TYPE_KERNEL  = 2,     /* Patch coeff(kernel) for NN */
};

enum nbg_nn_command_size_e {
	NBG_NN_COMMAND_SIZE_128 = 0,
	NBG_NN_COMMAND_SIZE_192 = 1,
};

enum nbg_tp_command_size_e {
	NBG_TP_COMMAND_SIZE_128 = 0,
	NBG_TP_COMMAND_SIZE_192 = 1,
};

typedef enum _nbg_operation_type {
	NBG_OPERATION_TYPE_NONE       = 0,
	NBG_OPERATION_TYPE_SH         = 1,
	NBG_OPERATION_TYPE_NN         = 2,
	NBG_OPERATION_TYPE_TP         = 3,
	NBG_OPERATION_TYPE_SW         = 4,
	NBG_OPERATION_TYPE_SC         = 5,
	NBG_OPERATION_TYPE_SP         = 6,
	NBG_OPERATION_TYPE_NN_LUT     = 7, /* NN LUT operation */
	NBG_OPERATION_TYPE_NT         = 8, /* NN Transpose operation */
	NBG_OPERATION_TYPE_END        = 0xFFFE,
	NBG_OPERATION_TYPE_INIT       = 0xFFFF,
} nbg_operation_type_e;

/*
the source type of network operation
*/
enum nbg_source_type_e {
	NBG_SOURCE_COMMAND            = 0,
	NBG_SOURCE_INPUT              = 1,
	NBG_SOURCE_OUTPUT             = 2,
	NBG_SOURCE_MEMORY_POOL        = 3,
	NBG_SOURCE_AXI_SRAM           = 4,
	NBG_SOURCE_MISC_DYNA_GENERIC  = 5,
	NBG_SOURCE_MISC_DYNA_INPUT    = 6,
	NBG_SOURCE_MISC_DYNA_OUTPUT   = 7,
	NBG_SOURCE_VIP_SRAM           = 8,
	NBG_SOURCE_KERNEL_BITSTREAM   = 9,   /* patch kernel's bit stream */
	NBG_SOURCE_LAYER_DUMP_OUTPUT  = 10,
	NBG_SOURCE_MULTIVIP_CHIPID    = 100, /* for multiVIP only */
	NBG_SOURCE_MULTIVIP_SYNC_CMDS = 101,
};

typedef enum _nbg_create_network_from {
	NBG_CREATE_NETWORK_FROM_NONE    = 0,
	NBG_CREATE_NETWORK_FROM_FILE    = 1,
	NBG_CREATE_NETWORK_FROM_MEMORY  = 2,
	NBG_CREATE_NETWORK_FROM_FLASH   = 3,
} nbg_create_network_from_e;

typedef struct _nbg_fmt_reader {
	/* the offset of current position */
	vip_size_t      offset;
	vip_size_t      total_size;
	/* the poiner of base data */
	vip_char_t      *data;
	vip_char_t      *current_data;
	viphal_file_t   file;
	vip_uint32_t    create_from; /* see nbg_create_network_from_e */
} nbg_fmt_reader_t;

typedef struct _nbg_section_info {
	vip_uint32_t index;
	vip_char_t type_name[64];
	vip_char_t section_name[64];
	vip_uint32_t version; /*which version add this section*/
} nbg_section_info_s;

void nbg_fmt_reader_open(
	nbg_fmt_reader_t *reader,
	void *data,
	vip_size_t size,
	void *file,
	vip_uint32_t creat_type
);

void nbg_fmt_reader_close(
	nbg_fmt_reader_t *reader
);

void nbg_fmt_reader_rewind(
	nbg_fmt_reader_t *reader
);

vip_status_e nbg_fmt_reader_forward(
	nbg_fmt_reader_t *reader,
	vip_size_t step
);

vip_status_e nbg_fmt_reader_backward(
	nbg_fmt_reader_t *reader,
	vip_size_t step
);

vip_status_e nbg_fmt_reader_locate(
	nbg_fmt_reader_t *reader,
	vip_size_t location
);

vip_int8_t nbg_fmt_read_byte(
	nbg_fmt_reader_t *reader,
	vip_uint32_t auto_move
);

vip_uint32_t nbg_fmt_read_uInt(
	nbg_fmt_reader_t *reader,
	vip_uint32_t auto_move
);

vip_status_e nbg_fmt_read_data(
	nbg_fmt_reader_t *reader,
	vip_uint8_t **memory,
	vip_size_t size,
	const vip_char_t *name
);

vip_status_e nbg_fmt_read_data_copy(
	nbg_fmt_reader_t *reader,
	void *memory,
	vip_size_t size,
	const vip_char_t *name
);

/*
@brief Get the byte of buffer format.
@param format
*/
vip_uint32_t nbg_get_buf_format_byte(
	vip_enum format
);

/*
@brief Get the bit of buffer format.
@param format
*/
vip_uint32_t nbg_get_buf_format_bit(
	vip_enum format
);

vip_uint32_t nbg_get_nn_command_size(
	nbg_fmt_descriptor_t *nbg_desc
);

vip_uint32_t nbg_get_tp_command_size(
	nbg_fmt_descriptor_t *nbg_desc
);

vip_char_t *nbg_get_operation_name(
	vip_uint32_t type
);

vip_size_t nbg_get_input_size(
	nbg_fmt_descriptor_t *nbg_desc,
	vip_uint32_t input_index
);

vip_size_t nbg_get_output_size(
	nbg_fmt_descriptor_t *nbg_desc,
	vip_uint32_t output_index
);

vip_bool_e nbg_operation_is_nn_engine(
	vip_uint32_t op_type
);

vip_status_e nbg_fmt_read(
	nbg_fmt_reader_t *reader,
	nbg_fmt_descriptor_t *nbg_desc
);

vip_status_e nbg_fmt_read_v1(
	nbg_fmt_reader_t *reader,
	nbg_fmt_descriptor_t *nbg_desc
);

vip_status_e nbg_fmt_read_v2(
	nbg_fmt_reader_t *reader,
	nbg_fmt_descriptor_t *nbg_desc
);
#endif
