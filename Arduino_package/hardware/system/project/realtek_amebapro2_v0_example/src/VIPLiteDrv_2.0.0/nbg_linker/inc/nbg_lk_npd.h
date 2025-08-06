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


#ifndef _NBG_LK_NPD_H
#define _NBG_LK_NPD_H

#include <vip_lite_common.h>
#include <nbg_lk_network.h>

/*  NPD(Network Profile Data) file version */
#define NPD_FORMAT_VERSION                  0x00000002

/* bit for node id and core id */
#define  NPD_ITEM_HEADER_SIZE_BITS          128
/* sel[0 ~ 5] + sel15 = 7 */
#define  NPD_TOTAL_SEL_COUNT                7
/* bit */
#define  NPD_ONE_SEL_SIZE_BITS              128
/* byte */
#define  NPD_ITEM_SIZE ((NPD_ITEM_HEADER_SIZE_BITS + NPD_TOTAL_SEL_COUNT * NPD_ONE_SEL_SIZE_BITS) / 8)


/* profile_enable + [chip_enable] + start_cmd
 * profile_enable + [chip_enable] + end_cmd */
#define ONE_OP_PROFILE_CMD_SIZE(core_count, one_profile_cmd_size)                     \
{  vip_uint32_t start_cmd_size = 0, end_cmd_size = 0;                                 \
    start_cmd_size = (sizeof(vip_uint32_t) * ((core_count > 1 ? 4 : 0) +              \
                4 * NPD_TOTAL_SEL_COUNT)) + 2 * sizeof(vip_uint32_t);       \
    end_cmd_size = (sizeof(vip_uint32_t) * ((core_count > 1 ? 4 : 0) +                \
                4 * NPD_TOTAL_SEL_COUNT)) + 8 * sizeof(vip_uint32_t);       \
    one_profile_cmd_size = start_cmd_size + end_cmd_size;                             \
}

#define ONE_OP_PROFILE_START_CMD_SIZE(core_count, one_op_profile_start_cmd_size)        \
{   one_op_profile_start_cmd_size = (sizeof(vip_uint32_t) * ((core_count > 1 ? 4 : 0) + \
                4 * NPD_TOTAL_SEL_COUNT)) + 2 * sizeof(vip_uint32_t);         \
}


typedef enum _nbglk_npd_proflie_cmd {
	NBGLK_NPDCMD_BEGIN = 0,
	NBGLK_NPDCMD_PAUSE = 1,
	NBGLK_NPDCMD_RESUME = 2,
	NBGLK_NPDCMD_END = 3,
} nbglk_npd_proflie_cmd_e;


typedef struct _nbglk_npd_header_t {
	vip_char_t magic[4];
	vip_uint32_t version;
	vip_uint32_t hw_cid;
	vip_uint32_t network_count;
	vip_uint32_t vip_core_count;
	vip_char_t reserved[236];
} nbglk_npd_header_t;

typedef struct _nbglk_npd_network_info_t {
	vip_char_t network_name[64];
	vip_uint32_t data_offset;
	vip_uint32_t data_size;
	vip_uint32_t profile_item_count;
	vip_uint32_t profile_item_size;
	vip_uint32_t core_count;
	vip_char_t reserved[44];
} nbglk_npd_network_info_t;


vip_status_e nbglk_npd_generate_header_info(
	vip_network_t *network
);

vip_status_e nbglk_npd_generate_command(
	vip_uint8_t *buffer,
	vip_network_t *network,
	nbglk_segment_t *segment,
	nbg_desc_operation_t *operation,
	nbglk_npd_proflie_cmd_e cmd
);

vip_status_e nbglk_npd_save_file(
	vip_network_t *network
);

vip_uint32_t nbglk_npd_states_size(
	vip_network_t *network,
	nbglk_segment_t *segment
);

vip_status_e nbglk_npd_init(
	vip_network_t *network
);

vip_status_e nbglk_npd_uninit(
	vip_network_t *network
);

#endif
