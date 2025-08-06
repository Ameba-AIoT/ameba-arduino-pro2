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

#ifndef _NBG_LK_GROUP_H
#define _NBG_LK_GROUP_H

#include <vip_lite_config.h>
#include <vip_lite.h>


#define NBGLK_CHECK_GROUP()                      \
    if (VIP_NULL == group) {                     \
        vip_error("group object is NULL\n");     \
        return VIP_ERROR_INVALID_NETWORK;        \
    }

typedef struct _nbglk_group_item {
	nbglk_object_t      object;
	vip_ptr             task;
} nbglk_group_item_t;

typedef struct _vip_group {
	nbglk_group_item_t    *tasks;
	vip_uint32_t           max_task_num;
	vip_uint32_t           add_task_num;
	vip_uint32_t           run_task_num;
#if vpmdENABLE_MULTIPLE_TASK
	void                  *mutex;
#endif

	/* belong to which context */
	nbglk_context          context;
	/* which device runs on */
	nbglk_device_t         *device;

	vip_uint32_t           core_index;

	vip_uint32_t           wait_timeout;
	viphal_file_t          capture_file;
	vip_uint32_t           task_id;
	vip_bool_e             need_schedule;
} vip_group_t;

#if vpmdENABLE_GROUP_MODE
vip_status_e nbglk_group_item_get_command(
	const nbglk_group_item_t *item,
	nbglk_videomemory_t **cmd_ptr
);
#endif

#endif

