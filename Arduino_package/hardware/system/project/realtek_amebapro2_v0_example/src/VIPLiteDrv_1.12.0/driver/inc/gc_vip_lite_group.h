/******************************************************************************\
|* Copyright (c) 2017-2023 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/

#ifndef _VIP_LITE_GROUP_H
#define _VIP_LITE_GROUP_H

#include <gc_vip_common.h>
#include <vip_lite.h>


#define GCVIP_CHECK_GROUP()                      \
    if (VIP_NULL == group) {                     \
        gcvip_error("group object is NULL\n");   \
        return VIP_ERROR_INVALID_NETWORK;        \
    }

typedef struct _gcvip_group_item {
	gcvip_object_t      object;
	vip_ptr             task;
} gcvip_group_item_t;

typedef struct _vip_group {
	gcvip_group_item_t    *tasks;
	vip_uint32_t           max_task_num;
	vip_uint32_t           add_task_num;
	vip_uint32_t           run_task_num;
#if vpmdENABLE_MULTIPLE_TASK
	void                  *mutex;
#endif
	/* the index of device run this group */
	vip_uint32_t           device_id;
	vip_uint32_t           wait_timeout;
	gcvip_file_t           capture_file;
} vip_group_t;

#if vpmdENABLE_GROUP_MODE
vip_status_e gcvip_group_item_get_command(
	const gcvip_group_item_t *item,
	gcvip_videomemory_t **cmd_ptr,
	vip_uint32_t *cmd_size
);
#endif

#endif

