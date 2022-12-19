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

#ifndef _GC_VIP_USER_HARDWARE_H
#define _GC_VIP_USER_HARDWARE_H
#include <gc_vip_common.h>
#if vpmdENABLE_MULTIPLE_VIP

/*
@brief generate multi-vip sync commands.
@param buffer, sync command buffer.
@param size, the size of this sync command buffer.
@param core_count, the number of vip cores in this devices.
@param core_id, the index of vip core in this devcies.
*/
vip_status_e gcvip_hardware_multivip_sync(
	vip_uint32_t *buffer,
	vip_uint32_t *size,
	vip_uint32_t core_count,
	vip_uint32_t *core_id
);

#endif

#if vpmdENABLE_CNN_PROFILING && vpmdENABLE_BW_PROFILING

#define MODULE_FRONT_END_COUNTER_NUM                    0x5
#define MODULE_VERTEX_SHADER_COUNTER_NUM                0x9
#define MODULE_PRIMITIVE_ASSEMBLY_COUNTER_NUM           0xC
#define MODULE_SETUP_COUNTER_NUM                        0xD
#define MODULE_RASTERIZER_COUNTER_NUM                   0xE
#define MODULE_PIXEL_SHADER_COUNTER_NUM                 0x9
#define MODULE_TEXTURE_COUNTER_NUM                      0x8
#define MODULE_PIXEL_ENGINE_COUNTER_NUM                 0x8
#define MODULE_MEMORY_CONTROLLER_COLOR_COUNTER_NUM      0xC
#define MODULE_MEMORY_CONTROLLER_DEPTH_COUNTER_NUM      0xC
#define MODULE_HOST_INTERFACE0_COUNTER_NUM              0x9
#define MODULE_HOST_INTERFACE1_COUNTER_NUM              0x7
#define MODULE_GPUL2_CACHE_COUNTER_NUM                  0xE
#define TOTAL_PROBE_NUMBER (MODULE_FRONT_END_COUNTER_NUM + MODULE_VERTEX_SHADER_COUNTER_NUM \
                              + MODULE_PRIMITIVE_ASSEMBLY_COUNTER_NUM + MODULE_SETUP_COUNTER_NUM \
                              + MODULE_RASTERIZER_COUNTER_NUM + MODULE_PIXEL_SHADER_COUNTER_NUM \
                              + MODULE_TEXTURE_COUNTER_NUM + MODULE_PIXEL_ENGINE_COUNTER_NUM \
                              + MODULE_MEMORY_CONTROLLER_COLOR_COUNTER_NUM \
                              + MODULE_MEMORY_CONTROLLER_DEPTH_COUNTER_NUM + MODULE_HOST_INTERFACE0_COUNTER_NUM \
                              + MODULE_HOST_INTERFACE1_COUNTER_NUM + MODULE_GPUL2_CACHE_COUNTER_NUM)

#define   TOTAL_VIP_MODULE_NUMBER    2
#define   NN_CORE_NUM       32
#define   MODULE_NN_BASE_COUNTER_NUM               0x6
#define   MODULE_NN_RESERVED_COUNTER_NUM           0x9
#define   MODULE_NN_IDLE_COUNTER_OVFL_NUM          0x1
#define   MODULE_NN_IDLE_COUNTER_NUM               0x8
#define   MODULE_NN_COUNTER_NUM            (MODULE_NN_BASE_COUNTER_NUM + MODULE_NN_RESERVED_COUNTER_NUM \
                                              + MODULE_NN_IDLE_COUNTER_OVFL_NUM + MODULE_NN_IDLE_COUNTER_NUM)
#define   TP_CORE_NUM       16
#define   MODULE_TP_BASE_COUNTER_NUM               0x6
#define   MODULE_TP_IDLE_COUNTER_NUM               0x8
#define   MODULE_TP_COUNTER_NUM      (MODULE_TP_BASE_COUNTER_NUM + MODULE_TP_IDLE_COUNTER_NUM)
#define   TOTAL_VIP_PROBE_NUMBER (MODULE_NN_COUNTER_NUM + MODULE_TP_COUNTER_NUM)
/* 128 bit register */
#define   DATA_PER_REGISTER 4

typedef enum _gcvip_probe_proflie_cmd {
	GCVIP_PROBECMD_BEGIN = 0,
	GCVIP_PROBECMD_PAUSE = 1,
	GCVIP_PROBECMD_RESUME = 2,
	GCVIP_PROBECMD_END = 3,
} gcvip_probe_proflie_cmd_e;

typedef struct _gcvip_probe_param {
	/* the physical address to store counter */
	vip_uint32_t physical;
	/* how many cores in cluster */
	vip_uint32_t clusterIDWidth;
	/* the type of cmd */
	gcvip_probe_proflie_cmd_e cmd;
} gcvip_probe_param;
/*
@brief generate profiling start/end commands.
@param buffer, command buffer.
@param size, the size of this command buffer.
@param core_count, the number of vip cores in this devices.
@param core_id, the index of vip core in this devcies.
@param probe_param, parameters.
*/
vip_status_e gcvip_hardware_probe_cmd(
	vip_uint32_t *buffer,
	vip_uint32_t *size,
	vip_uint32_t core_count,
	vip_uint32_t *core_id,
	gcvip_probe_param *probe_param
);
#endif
#endif
