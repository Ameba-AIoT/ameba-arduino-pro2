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


#ifndef _NBG_LK_CONTEXT_H
#define _NBG_LK_CONTEXT_H

#include <vip_lite_config.h>
#include <vip_lite.h>
#include <nbg_lk_util.h>
#include <vip_drv_share.h>
#include <vip_hal.h>

/*
  Special Reset for HW. HW use this to clean status of each operation.
   When set to 0, disable this special reset.
   When set to 1, enable quickly reset after each NN operation command.
   Only the latest HW arch supports this feature.
*/
#ifndef vpmdENABLE_QUICK_RESET
#define vpmdENABLE_QUICK_RESET               0
#endif


#define NBGLK_INITIALIZE_CHECK(network)                  \
{                                                        \
    if ((VIP_NULL == network->context) || (network->context->initialize <= 0)) { \
        vip_error("please call vip_init() to initialize viplite, network->context=%p\n", \
                    network->context);                   \
        return VIP_ERROR_NOT_SUPPORTED;                  \
    }                                                    \
}

typedef struct _nbglk_context  *nbglk_context;

typedef struct _nbglk_device {
	/* the index of the device */
	vip_uint32_t        dev_index;
	/* the core numbers of device */
	vip_uint32_t        core_count;
	/* the core id used by this device */
	vip_uint32_t        *core_id;
} nbglk_device_t;

typedef struct _nbglk_context {
	/* cid */
	vip_uint32_t        hw_target;
	vip_virtual_t       *axi_sram_base;
	vip_uint32_t        *axi_sram_size;
	vip_uint32_t        vip_sram_base;
	vip_uint32_t        vip_sram_size;

	volatile vip_int8_t  initialize;

#if vpmdENABLE_CAPTURE
	viphal_file_t        capture_file;
#endif

#if vpmdENABLE_MULTIPLE_TASK
	/* mutex for vip_init/vip_destroy */
	void                *initialize_mutex;
#if vpmdENABLE_CAPTURE
	/* mutex for capture */
	nbglk_recursive_mutex_t capture_mutex;
#endif
#endif

	/* device number of the VIP hardware */
	vip_uint32_t        device_count;
	nbglk_device_t *devices;

	/* function config by kernel space fs node */
	vipdrv_feature_config_t func_config;
} nbglk_context_t;


nbglk_context_t *nbglk_get_context(void);

vip_status_e nbglk_init(
	vip_uint32_t sys_mem_size,
	vip_uint32_t video_mem_size
);

vip_status_e nbglk_destroy(void);


#endif
