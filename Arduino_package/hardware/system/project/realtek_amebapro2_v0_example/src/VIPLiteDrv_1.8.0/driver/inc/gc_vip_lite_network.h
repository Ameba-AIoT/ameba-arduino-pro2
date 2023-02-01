/******************************************************************************\
|* Copyright (c) 2017-2022 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/


#ifndef _VIP_LITE_NETWORK_H
#define _VIP_LITE_NETWORK_H

#include <gc_vip_common.h>
#include <gc_vip_lite.h>
#include <gc_vip_user.h>
#include <gc_vip_version.h>
#include <gc_vip_user_os.h>
#include <gc_vip_nbg_format.h>
#include <gc_vip_kernel_share.h>

#define LAYER_IO_COUNT          64
#define OLD_NBG_MAX_DIMS        4

#if ((256 % vpmdCPU_CACHE_LINE_SIZE) != 0)
#define gcdVIP_SH_ALIGN_SIZE    GCVIP_ALIGN(GCVIP_ALIGN(256, vpmdCPU_CACHE_LINE_SIZE), 256)
#else
#define gcdVIP_SH_ALIGN_SIZE   256
#endif


#define GCVIP_CHECK_NETWORK() \
    if (VIP_NULL == network) {  \
        gcvip_error("network object is NULL\n");    \
        return VIP_ERROR_INVALID_NETWORK;   \
    }

typedef enum _gcvip_buffer_type {
	GCVIP_BUFFER_TYPE_TENSOR      = 0,
	GCVIP_BUFFER_TYPE_IMAGE       = 1,
	GCVIP_BUFFER_TYPE_ARRAY       = 2,
	GCVIP_BUFFER_TYPE_SCALAR      = 3,
} gcvip_buffer_type_e;

typedef enum _gcvip_create_network_from {
	GCVIP_CREATE_NETWORK_FROM_NONE    = 0,
	GCVIP_CREATE_NETWORK_FROM_FILE    = 1,
	GCVIP_CREATE_NETWORK_FROM_MEMORY  = 2,
	GCVIP_CREATE_NETWORK_FROM_FLASH   = 3,
} gcvip_create_network_from_e;

typedef enum _gcvip_patch_belong {
	GCVIP_PATCH_BELONG_OTHER      = 0,
	GCVIP_PATCH_BELONG_SH         = 1,
	GCVIP_PATCH_BELONG_NN         = 2,
	GCVIP_PATCH_BELONG_TP         = 4,
} gcvip_patch_belong_e;

typedef struct _data_reader {
	vip_uint32_t    offset;
	vip_uint32_t    total_size;
	vip_char_t      *data;
	vip_char_t      *current_data;
	gcvip_file_t    file;
	vip_uint32_t    create_from; /* see gcvip_create_network_from_e */
} gcvip_data_reader;

/*
 * @brief
 * This struct records the input/output patch information.
 * When patch_index >= 0, it means an index to the gcvip_op_patch_t array,
        which is saved as a member in vip_network_t.
 * And then slice_num means how many patches are needed for the SH operation.
 * Otherwise, it means an in/out address patch for NN/TP command.
 * The slice_num then means the memory address of the adress to patch in the command buffer.
*/
typedef struct _vip_io_patch_info {
	vip_uint32_t     slice_num;       /* If it is a basem, what's the reference count. */
	vip_address_t    *logical_in_cmd; /* The logical address in the command buffer. */
	vip_uint32_t     *physical_in_cmd;/* The physical address in the command buffer. */
	vip_uint32_t     *offsets;        /* The offset to the buffer base for each command. */
	vip_uint32_t     counter;         /* As a per buffer input iterator counter. */

	vip_uint32_t     physical;        /* The physical of the buffer, set by app. */
	vip_uint8_t      *logical;        /* The logical of the buffer, set by app. */

	vip_uint8_t      **sw_op_buffer;

	vip_buffer       buffer;
	vip_uint32_t     patch_belong;    /* This path belongs to which operation/operations */
} gcvip_io_patch_info_t;

typedef struct _vip_ppu_param_patch_info_t {
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

typedef struct _gcvip_lite_segment_base_s {
	vip_uint32_t        segment_type;
	vip_char_t          *name;
} gcvip_lite_segment_base_s;

typedef struct _gcvip_lite_segment {
	gcvip_lite_segment_base_s  *base;
	vip_char_t          *name;
	gcvip_videomemory_t  sh_cmd_buffer;  /* The video memory of the sh command buffer. */
	gcvip_videomemory_t  states_buffer;  /* including commands and ctrl states (trigger & wait_event). */
	vip_uint32_t         command_size; /* the size of command after append cmds */

	volatile vip_uint32_t segm_start_id;  /* the start layer or operation id for segment */
	volatile vip_uint32_t segm_end_id;    /* the end layer or operation id for segment */

	volatile vip_bool_e is_sw_segm;

	vip_uint32_t        *operation_pos;

	volatile vip_uint32_t split_num;
	vip_uint32_t         *split_pos_table;   /* patch command buffer position */
	vip_uint32_t         *split_size_table;  /* split command buffer size of each patch */

#if vpmdENABLE_LAYER_DUMP
	vip_uint32_t        out_count;
	vip_uint32_t        out_sizes[LAYER_IO_COUNT];
	void                *out_buffers[LAYER_IO_COUNT];
#endif

#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
	gcvip_command_dump_t *cmd_dump;
	gcvip_command_dump_t *lp1;
	gcvip_command_dump_t *lp2;
#endif

#if vpmdENABLE_CNN_PROFILING
	vip_uint64_t        start_time;
	vip_uint64_t        end_time;
#endif

#if vpmdENABLE_CAPTURE || vpmdENABLE_CNN_PROFILING || vpmdENABLE_LAYER_DUMP
	vip_uint32_t        uid;
#endif
#if vpmdENABLE_CANCELATION > 1
	vip_uint32_t       bp_count;
	vip_uint32_t       *bp_pos_table;
#endif
} gcvip_lite_segment_t;

typedef struct _vip_network {
	gcvip_object_t                  object;

	/* Fixed part of the bin. */
	gcvip_bin_fixed_t               fixed;

	/* Dynamic data part of the bin. */
	gcvip_bin_inout_entry_t        *inputs;
	gcvip_bin_inout_entry_t        *outputs;

	/* original layers info, loading from binary graph */
	gcvip_bin_layer_t              *orig_layers;
	gcvip_bin_operation_t          *operations;
	gcvip_bin_entry_t              *LCDT;
	gcvip_videomemory_t             LCD;
	void                           *nn_ops;
	void                           *tp_ops;
	gcvip_bin_sh_operation_t       *sh_ops;
	/* Patch Data for Shader Commands. */
	gcvip_bin_patch_data_entry_t   *pd_entries;
	gcvip_bin_layer_parameter_t    *lp_entries;
	gcvip_bin_sw_operation_info_t  *sw_ops;
	gcvip_bin_hw_init_operation_info_entry_t *init_ops;
	/* Initialize Config Data Table */
	gcvip_bin_entry_t              *ICDT;

	gcvip_ppu_param_data_t         *ppu_param;

	vip_uint32_t                    n_inputs;
	vip_uint32_t                    n_outputs;

	/* the number of original layers */
	vip_uint32_t                    n_orig_layers;
	vip_uint32_t                    n_operations;
	vip_uint32_t                    n_LCDT;
	vip_uint32_t                    n_nn_ops;
	vip_uint32_t                    n_tp_ops;
	vip_uint32_t                    n_sh_ops;
	vip_uint32_t                    n_pd_entries;
	vip_uint32_t                    n_layer_param;
	vip_uint32_t                    n_sw_ops;
	vip_uint32_t                    n_hw_init_ops;
	vip_uint32_t                    n_ICDT;
	vip_uint32_t                    n_ppu_param;

	void                           *dyna_data;
	void                           *dyna_data_two;

	/* Memory pool for VIP to use. */
	gcvip_videomemory_t             pool;

	/* Where the inputs are in command buffer,  use to patch the input buffer addresses by calling vip_set_input(). */
	gcvip_io_patch_info_t          *network_inputs;
	/* Where the outputs are in command buffer, use to patch the output buffer addresses by calling vip_set_output(). */
	gcvip_io_patch_info_t          *network_outputs;
	/* Indicate whether the command buffer is synced with the network. */
	volatile vip_uint32_t           cmd_dirty;
	volatile vip_uint8_t            input_dirty;
	volatile vip_uint8_t            output_dirty;

	/*
	vip lite segments, this is for supporting CPU operation in viplite.
	layer index in network: | | |  O | | | , (| means this layer can be run on VIP, O means this layer be run on CPU)
	segment index in viplite: X    O   X      (X means: merge '| | |' a segment in viplite)
	*/
	gcvip_lite_segment_t            *segments;
	/* the number of viplite segments */
	vip_uint32_t                    segment_num;

	/* initialize SRAM */
	gcvip_videomemory_t             init_states;
	vip_uint32_t                    init_states_size;

#if vpmdCREATE_NETWORK_FROM_FLASH
	gcvip_videomemory_t             flash;
#endif

#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
	/* mark to capture complete, don't need capture again*/
	volatile vip_uint8_t            capture_done;
#endif

#if vpmdENABLE_CNN_PROFILING
	vip_uint64_t                    total_time;
#if vpmdENABLE_BW_PROFILING
	gcvip_videomemory_t             probe_start_Cmds;
	gcvip_videomemory_t             probe_end_Cmds;
	gcvip_videomemory_t             probe_buffer;
#endif
#endif
	/* Initialize Config Data */
	gcvip_videomemory_t             ICD;
	/* initialize PPU,NN,TP */
	gcvip_videomemory_t             init_commands;

	gcvip_videomemory_t             nnCmds;
	gcvip_videomemory_t             tpCmds;

	volatile vip_bool_e             prepared_network;
	volatile vip_uint8_t            prepare_count;

	/* memory pool buffer specify by application */
	vip_buffer                      memory_pool;

#if vpmdENABLE_SECURE
	/* normal mode or secure mode, see vip_create_network_type_e */
	volatile vip_uint8_t            work_mode;
#endif

	volatile vip_bool_e             weak_dup;
	volatile vip_bool_e             realloc_sh_buff;

#if vpmdENABLE_CHANGE_PPU_PARAM
	volatile vip_bool_e             change_ppu_param;
	vip_ppu_param_patch_info_t      *ppu_param_info;
	vip_uint8_t                     ppu_work_dim;
#endif
	/* this network will be submited to this vip device */
	vip_uint32_t                    device_id;
#if vpmdENABLE_CANCELATION > 1
	gcvip_videomemory_t             stop_cmds;
#endif
#if vpmdENABLE_MULTIPLE_VIP
	vip_uint32_t                    *multivip_sync_cmd;
	vip_uint32_t                    sync_cmd_size;
#endif
#if vpmdENABLE_HANG_DUMP > 1
	gcvip_file_t                    capture_file;
#endif
	vip_bool_e                      occur_hang;
	vip_uint8_t                     priority;
} vip_network_t;

/******************** END of binary file data structure. *********/


/******************* Internel apis **********************/
gcvip_lite_context_t *gcvip_get_context(void);

vip_status_e gcvip_wait_network_segment(
	vip_network network,
	gcvip_lite_segment_t *segment
);

/*
@brief Submit a command buffer to hardware.
@param command command buffer video memory object.
@param command_size, the size of command buffer be commited.
*/
vip_status_e gcvip_commit_command(
	gcvip_videomemory_t *command,
	vip_uint32_t command_size,
	vip_uint32_t device_id,
	vip_uint8_t priority
);

/*
@brief Submit multiple command buffer to hardware.
@param command command buffer video memory object.
@param last_cmd_size the size of last command buffer.
*/
vip_status_e gcvip_commit_multiple_command(
	gcvip_videomemory_t *pre_command,
	gcvip_videomemory_t *last_command,
	vip_uint32_t last_cmd_size,
	vip_uint32_t device_id
);

/******************* Network apis **********************/
vip_status_e gcvip_create_network_from_file(
	IN gcvip_file_t file,
	OUT vip_network_t *network
);

vip_status_e gcvip_create_network_from_memory(
	vip_network_t *network,
	const void *data,
	vip_uint32_t size
);

vip_status_e gcvip_create_network(
	OUT vip_network_t *network,
	IN gcvip_data_reader *reader
);

vip_status_e gcvip_query_network(
	IN vip_network_t *network,
	IN vip_enum property,
	OUT void  *value
);

vip_status_e gcvip_set_network(
	IN vip_network_t *network,
	IN vip_enum property,
	IN void *value
);

vip_status_e gcvip_prepare_network(
	vip_network_t *network
);
vip_status_e gcvip_run_network(
	IN vip_network_t *network
);

vip_status_e gcvip_trigger_network(
	IN vip_network_t *network
);

vip_status_e gcvip_wait_network(
	IN vip_network_t *network
);

#if vpmdENABLE_CANCELATION
vip_status_e gcvip_cancel_network(
	IN vip_network_t *network
);
#endif

vip_status_e gcvip_finish_network(
	IN vip_network_t *network
);

vip_status_e gcvip_destroy_network(
	IN vip_network network
);

vip_status_e gcvip_set_input(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_buffer input
);

vip_status_e gcvip_set_output(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_buffer output
);

vip_status_e gcvip_query_input(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_enum property,
	OUT void *value
);

vip_status_e gcvip_query_output(
	IN vip_network_t *network,
	IN vip_uint32_t index,
	IN vip_enum property,
	OUT void *value
);

vip_status_e gcvip_init(
	IN vip_uint32_t sys_mem_size,
	IN vip_uint32_t video_mem_size
);

vip_status_e gcvip_destroy(void);

#if vpmdENABLE_POWER_MANAGEMENT
vip_status_e gcvip_check_power_status(
	vip_network network
);
#endif

#if vpmdENABLE_GROUP_MODE
vip_status_e gcvip_link_command(
	gcvip_videomemory_t *pre_cmd,
	gcvip_videomemory_t *cur_cmd
);

vip_status_e gcvip_run_group(
	vip_group group,
	vip_uint32_t num
);

vip_status_e gcvip_wait_group(
	vip_group group
);

vip_status_e gcvip_group_item_get_command(
	const gcvip_group_item_t *item,
	gcvip_videomemory_t **cmd,
	vip_uint32_t *cmd_size
);

vip_status_e gcvip_update_group_io(
	vip_group group,
	vip_uint32_t num
);

vip_status_e gcvip_weak_dup_network(
	vip_network network,
	vip_network copy
);
#endif

#endif
