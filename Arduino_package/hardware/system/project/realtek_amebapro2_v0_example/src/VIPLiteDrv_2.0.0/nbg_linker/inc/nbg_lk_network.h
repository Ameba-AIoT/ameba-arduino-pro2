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


#ifndef _NBG_LK_NETWORK_H
#define _NBG_LK_NETWORK_H

#include <vip_lite_config.h>
#include <nbg_lk.h>
#include <nbg_lk_buffer.h>
#include <vip_hal.h>
#include <vip_lite_version.h>
#include <vip_hal_os.h>
#include <nbg_fmt_descriptor.h>
#include <nbg_lk_util.h>
#include <nbg_lk_coeff.h>
#include <nbg_lk_context.h>
#include <nbg_lk_list.h>

#define LAYER_IO_COUNT          64

#if ((256 % vpmdCPU_CACHE_LINE_SIZE) != 0)
#define vipdSH_ALIGN_SIZE    VIP_ALIGN(VIP_ALIGN(256, vpmdCPU_CACHE_LINE_SIZE), 256)
#else
#define vipdSH_ALIGN_SIZE   256
#endif


#define NBGLK_CHECK_NETWORK()                       \
    if (VIP_NULL == network) {                      \
        vip_error("network object is NULL\n");      \
        return VIP_ERROR_INVALID_NETWORK;           \
    }

#define NBGLK_CHECK_NETWORK_DYNA_IS_NULL(network)   \
    if (vip_true_e == network->nbg_desc.corrupted) {                           \
        vip_warning("nbg info is corrupted, should create network again\n");   \
        return VIP_ERROR_FAILURE;                                              \
    }

#if vpmdENABLE_CHECKSUM
typedef enum _nbglk_checksum_type {
	NBGLK_CHECKSUM_NN_COMMAND          = 0,
	NBGLK_CHECKSUM_TP_COMMAND          = 1,
	NBGLK_CHECKSUM_SH_COMMAND          = 2,
	NBGLK_CHECKSUM_NN_WEIGHT           = 3,
	NBGLK_CHECKSUM_TP_WEIGHT           = 4,
	NBGLK_CHECKSUM_SH_WEIGHT           = 5,
	NBGLK_CHECKSUM_NN_WEIGHT_BITSTREAM = 6,
	NBGLK_CHECKSUM_STATE_LOAD          = 7,
	NBGLK_CHECKSUM_SP_WEIGHT           = 8,
	NBGLK_CHECKSUM_SP_WEIGHT_BITSTREAM = 9,
	NBGLK_CHECKSUM_MAX                 = 10,
} nbglk_checksum_type_e;
#endif

typedef enum _nbglk_section_checksum_type {
	NBGLK_SECTION_CHECKSUM_LOAD_STATES     = 0,
	NBGLK_SECTION_CHECKSUM_PPU_INSTR       = 1,
	NBGLK_SECTION_CHECKSUM_COEFF_DATA      = 2,
	NBGLK_SECTION_CHECKSUM_MAX,
} nbglk_section_checksum_type_e;

typedef enum _nbglk_dup_type {
	/*!< \brief Indicates the network is created directly */
	NBGLK_DUP_NONE                  = 0,
	/*!< \brief
	 Indicates the network is duplicated from network(vip_dup_network with type VIP_DUP_FOR_CMD_BY_NETWORK).
	 duplicated commands and shared weight with original network. also means weak duplicate network feature
	 share: weight, ppu instr.
	 no-share: load states, nn cmd, tp cmd, dyna_io, memory pool(shoudl set_network(memory_pool)).
	 */
	NBGLK_FROM_NETWORK_DUP_COMMAND  = 0x01,

	/*!< \brief Indicates the network is created by vip_dup_network() with VIP_DUP_FOR_CMD_BY_NBG.
	duplicate command for sharing weight and shared weight with difference network(NBGs).
	example:
	Network 1 and Network 2 only the input/output shape is different, and have the same network structure,
	they can share weight through vip_dup_network()/vip_prepare_network */
	NBGLK_FROM_NBG_DUP_COMMAND      = 0x02,

} nbglk_dup_type_e;

typedef enum _nbglk_patch_belong {
	NBGLK_PATCH_BELONG_OTHER      = 0,
	NBGLK_PATCH_BELONG_SH         = 0x01,
	NBGLK_PATCH_BELONG_NN         = 0x02,
	NBGLK_PATCH_BELONG_TP         = 0x04,
	NBGLK_PATCH_BELONG_SP         = 0x08,
	NBGLK_PATCH_BELONG_NN_LUT     = 0x10,
	NBGLK_PATCH_BELONG_NT         = 0x20,
} nbglk_patch_belong_e;

/*
 * @brief
 * This struct records the input/output patch information.
 * When patch_index >= 0, it means an index to the nbglk_op_patch_t array,
        which is saved as a member in vip_network_t.
 * And then slice_num means how many patches are needed for the SH operation.
 * Otherwise, it means an in/out address patch for NN/TP command.
 * The slice_num then means the memory address of the adress to patch in the command buffer.
*/
typedef struct _nbglk_io_patch_info {
	vip_uint32_t     slice_num;       /* If it is a basem, what's the reference count. */
	vip_address_t    *logical_in_cmd; /* The logical address in the command buffer. */
	vip_uint32_t     *physical_in_cmd;/* The physical address in the command buffer. */
	nbg_desc_patch_t **patch;         /* The patch information for each command. */
	vip_uint32_t     counter;         /* As a per buffer input iterator counter. */

	vip_address_t    physical;        /* The physical of the buffer, set by app. */
	vip_uint8_t      *logical;        /* The logical of the buffer, set by app. */

	vip_uint8_t      **sw_op_buffer;

	vip_buffer       buffer;
	vip_uint32_t     patch_belong;    /* This path belongs to which operation/operations */
} nbglk_io_patch_info_t;

typedef struct _vip_ppu_param_patch_info {
	vip_address_t *glooffset_x_logic;
	vip_address_t *glooffset_y_logic;
	vip_address_t *glooffset_z_logic;
	vip_address_t *gloscale_x_logic;
	vip_address_t *gloscale_y_logic;
	vip_address_t *gloscale_z_logic;
	vip_address_t *grosize_x_logic;
	vip_address_t *grosize_y_logic;
	vip_address_t *grosize_z_logic;
	vip_address_t *grocount_x_logic;
	vip_address_t *grocount_y_logic;
	vip_address_t *grocount_z_logic;
} vip_ppu_param_patch_info_t;

typedef struct _nbglk_memory_pool_info {
	/* the logical address of command, memory pool should be fill in here */
	vip_uint8_t *cmd_logical;
	/* sw layer or not; sw layer need logical address */
	vip_uint8_t sw_layer;
	union {
		nbg_desc_patch_t *patch;
		/* the offset of memory pool base address for sw */
		vip_uint32_t pool_offset;
	} info;
} nbglk_memory_pool_info_t;

typedef struct _nbglk_segment_base {
	vip_uint32_t          segment_type;
	vip_char_t            *name;
	nbg_desc_operation_t *operation;
} nbglk_segment_base_t;

typedef struct _nbglk_npd_t {
	vip_bool_e      enable_npd;
	nbglk_videomemory_t  npd_buffer;
	vip_uint64_t    index;
} nbglk_ndp_t;

typedef struct _nbglk_op_id_segment {
	/* the abs id of opeeration */
	vip_uint32_t start_id;
	vip_uint32_t end_id;
} nbglk_op_id_segment_t;

typedef struct _nbg_segment {
	nbglk_segment_base_t  *base;
	vip_uint32_t        index; /* the index of segment in network */
	vip_char_t          *name;
	nbglk_videomemory_t  sh_cmd_buffer;  /* The video memory of the sh command buffer. */
	nbglk_videomemory_t  states_buffer;  /* including commands and ctrl states (trigger & wait_event)*/
	vip_uint32_t         command_size; /* the size of command after append cmds */

	volatile vip_uint32_t segm_start_id;  /* the start layer or operation id for segment */
	volatile vip_uint32_t segm_end_id;    /* the end layer or operation id for segment */

	volatile vip_bool_e  is_sw_segm;

	vip_uint32_t         *operation_pos;
	volatile vip_uint32_t split_num;
	vip_uint32_t         *split_pos_table;   /* patch command buffer position */
	vip_uint32_t         *split_size_table;  /* split command buffer size of each patch */

#if vpmdENABLE_RECORD_INFO
	/* record information used by this segment(network) */
	nbglk_hashmap_t     record_list;
#endif
#if vpmdENABLE_CNN_PROFILING
	vip_uint64_t        start_time;
	vip_uint64_t        end_time;
	vip_uint8_t         core_id_mask;
#endif

#if vpmdENABLE_CAPTURE || vpmdENABLE_CNN_PROFILING
	vip_uint32_t        uid;
#endif
#if vpmdENABLE_CANCELATION > 1
	vip_uint32_t       bp_count;
	vip_uint32_t       *bp_pos_table;
#endif
	vip_uint32_t       patch_count; /* the patch count for multi-core */
} nbglk_segment_t;

#if vpmdENABLE_LAYER_DUMP
typedef struct _nbglk_nld_t {
	vip_uint32_t                status; /* 1:nbg has layer dump info */
	vip_uint32_t                enable; /* true:application has set output to dump */
	vip_uint32_t                count; /* dump layer count */
	nbglk_list_head_t           layer_head;
	nbglk_list_head_t           operation_head;
	nbglk_list_head_t           link_info_head;
	nbglk_list_head_t           output_head;
	nbglk_list_head_t           instr_head;
	nbglk_videomemory_t         state_memory;
	nbglk_videomemory_t         instr_memory;
	vip_uint32_t                insert_flag;
	vip_uint32_t                nn_event_id[vipdMAX_CORE];
	vip_nld_output_t            nld_output; /* collect output information for app dump */
} nbglk_nld_t;
#endif

typedef struct _vip_network {
	nbglk_object_t                  object;

	/* belong to which context */
	nbglk_context                   context;

	/* which device runs on */
	nbglk_device_t                  *device;

	/* this network will start with which core of cur device */
	vip_uint32_t                    core_index;

	/* need schedule this network in vip_driver or not */
	vip_bool_e                      need_schedule;

	nbg_fmt_descriptor_t            nbg_desc;

	nbglk_videomemory_t             coeff_header;
	nbglk_videomemory_t             coeff_data;
	nbglk_videomemory_t             nnCmds;
	nbglk_videomemory_t             tpCmds;
	nbglk_videomemory_t             ppu_instr;
	nbglk_videomemory_t             dyna_io;
	/* Initialize Config Data */
	nbglk_videomemory_t             ICD;
	vip_uint8_t                    *load_states;
	/* Memory pool allocated in driver */
	nbglk_videomemory_t             pool;

	/* Memory pool buffer specify by application */
	vip_buffer                      memory_pool;

#if vpmdDYNAMIC_CHANGE_MEM_POOL
	vip_uint32_t                    pool_patch_count;
	nbglk_memory_pool_info_t       *pool_patch_info;
#endif

#if vpmdPRELOAD_COEFF
	nbglk_coeff_property_t         *coeff_property;
	vip_uint32_t                    coeff_count;
	/* the size of nn coeff header */
	vip_uint32_t                    nn_header_size;

	/* Coeff buffer specify by applicatoin */
	nbglk_videomemory_t             *app_preload_coeff;
	vip_uint8_t                     app_preload_in_axisram;
#if vpmdPRELOAD_COEFF > 1
	/* NPU preload coeff command buffer */
	nbglk_videomemory_t             preload_instr;
	nbglk_videomemory_t             preload_cmd;
	vip_uint32_t                    preload_cmd_size;
#endif
#endif
	vip_uint32_t                    max_vipsram_offset;

	/* Where the inputs are in command buffer,  use to patch the input buffer addresses by calling vip_set_input()*/
	nbglk_io_patch_info_t          *network_inputs;
	/* Where the outputs are in command buffer, use to patch the output buffer addresses by calling vip_set_output()*/
	nbglk_io_patch_info_t          *network_outputs;
	volatile vip_uint8_t            input_dirty;
	volatile vip_uint8_t            output_dirty;

	/*
	vip lite segments, this is for supporting CPU operation in viplite.
	layer index in network: | | |  O | | | , (| means this layer can be run on VIP, O means this layer be run on CPU)
	segment index in viplite: X    O   X      (X means: merge '| | |' a segment in viplite)
	*/
	nbglk_segment_t            *segments;
	/* the number of viplite segments */
	vip_uint32_t                    segment_num;

	/* initialize PPU,NN,TP */
	nbglk_videomemory_t             init_commands;

	/* The nbg file in flash device video memory object.
	   When VIP's MMU is enabled, wrap nbg flash(memory) to VIP's virtual.
	*/
	nbglk_videomemory_t             flash;

#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
	/* mark to capture complete, don't need capture again*/
	volatile vip_uint8_t            capture_done;
#endif

#if vpmdENABLE_CNN_PROFILING
	vip_uint64_t                    total_time;
#endif

#if vpmdENABLE_LAYER_DUMP
	nbglk_nld_t                     nld;
#endif

	volatile vip_bool_e             prepared_network;
	volatile vip_uint8_t            prepare_count;

	vip_create_network_type_e       create_type;
	volatile nbglk_dup_type_e       dup_type;
	volatile vip_bool_e             realloc_sh_buff;

#if vpmdENABLE_CHANGE_PPU_PARAM
	volatile vip_bool_e             change_ppu_param;
	vip_ppu_param_patch_info_t      *ppu_param_info;
	vip_uint8_t                     ppu_work_dim;
#endif

#if vpmdENABLE_CANCELATION > 1
	nbglk_videomemory_t             stop_cmds;
#endif
#if vpmdENABLE_MULTIPLE_VIP
	vip_uint32_t                    *multivip_sync_cmd;
	vip_uint32_t                    sync_cmd_size;
#endif
#if vpmdENABLE_HANG_DUMP > 1
	viphal_file_t                    capture_file;
#endif
#if vpmdTASK_CMD_DUMP
	viphal_file_t                    dump_file;
#endif
	/* Mark the network hangs occur or not */
	vip_bool_e                      occur_hang;
	vip_uint8_t                     priority;
	vip_uint32_t                    wait_timeout;
#if vpmdENABLE_CHECKSUM
	vip_uint32_t                    checksum[NBGLK_CHECKSUM_MAX];
	vip_uint8_t                     check_status[NBGLK_CHECKSUM_MAX];
#endif
	vip_uint8_t                     check_sect_status[NBGLK_SECTION_CHECKSUM_MAX];
	/* Mark the network added into group or not */
	vip_bool_e                      belong_to_group;

	/* the friend_network is sharing weight with this network */
	vip_network                     friend_network;

	/* network per nn profile data(NPD)  */
	nbglk_ndp_t                     npd;

	vip_uint32_t                    task_id;

	/* for debugging bypass operation */
	nbglk_op_id_segment_t           op_segm;
} vip_network_t;

/******************** END of binary file data structure. *********/


/******************* Internel apis **********************/
/*
@brief Patch network's input address
*/
vip_status_e nbglk_patch_network_inputs(
	vip_network_t *network
);
/*
@brief Patch network's output address
*/
vip_status_e nbglk_patch_network_outputs(
	vip_network_t *network
);

/*
@brief Link two command buffer together
*/
vip_status_e nbglk_link_command(
	nbglk_videomemory_t *pre_cmd,
	nbglk_videomemory_t *cur_cmd
);

/******************* Network apis **********************/
vip_status_e nbg_create_network_from_file(
	IN viphal_file_t file,
	OUT vip_network_t *network
);

vip_status_e nbg_create_network_from_memory(
	vip_network_t *network,
	const void *data,
	vip_size_t size
);

vip_status_e nbg_create_network_from_network(
	IN vip_network_t *network_base,
	OUT vip_network_t *network
);

vip_status_e nbglk_query_network(
	IN vip_network_t *network,
	IN vip_enum property,
	OUT void  *value
);

vip_status_e nbglk_set_network(
	IN vip_network_t *network,
	IN vip_enum property,
	IN void *value
);

vip_status_e nbglk_prepare_network(
	vip_network_t *network
);

vip_status_e nbglk_prepare_network_from_friend(
	vip_network_t *network
);

vip_status_e nbglk_run_network(
	IN vip_network_t *network
);

vip_status_e nbglk_trigger_network(
	IN vip_network_t *network
);

vip_status_e nbglk_wait_network(
	IN vip_network_t *network
);

#if vpmdENABLE_CANCELATION
vip_status_e nbglk_cancel_network(
	IN vip_network_t *network
);
#endif

vip_status_e nbglk_finish_network(
	IN vip_network_t *network
);

vip_status_e nbglk_destroy_network(
	IN vip_network network
);

vip_status_e nbglk_set_input(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_buffer input
);

vip_status_e nbglk_set_output(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_buffer output
);

vip_status_e nbglk_query_input(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_enum property,
	OUT void *value
);

vip_status_e nbglk_query_output(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_enum property,
	OUT void *value
);

vip_uint32_t nbglk_get_segment_handle(
	nbglk_segment_t *segment
);
#endif
