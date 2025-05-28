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


#ifndef _NBG_LK_H
#define _NBG_LK_H

#include <vip_lite_config.h>
#include <vip_lite.h>
#include <vip_hal.h>
#include <nbg_lk_util.h>
#include <nbg_fmt_descriptor.h>

#define NBGLK_SET_VALUE(x, y) \
{   \
    if ((x) != VIP_NULL) {  \
        *((vip_uint32_t*)(x)) = (vip_uint32_t)(y);  \
    }   \
    else {   \
        vip_error("fail to set value=%d, x=%p\n", x);   \
        vipGoOnError(VIP_ERROR_NOT_SUPPORTED);   \
    }   \
}

#if vpmdENABLE_USE_AGENT_TRIGGER
/* vip_input_output_info_t and vip_address_info_t should be defined into agent driver
*/

/*! \brief network's inputs/outputs address in command buffer. it only used by Agent driver.
 */
typedef struct _vip_input_output_info {
	/*!< the logical address of input/output in command buffer */
	void                *logical_in_cmd;
	/*!< the physical address of input/output in command buffer */
	vip_uint32_t        *physical_in_cmd;
	/*!< the offset for every slice */
	nbg_desc_patch_t    **patch;
	/*!< the number of input/output slice */
	vip_uint32_t        slice_num;
	/*!< the physical address of input/output buffer */
	vip_address_t       physical;
} vip_input_output_info_t;

/*! \brief address infromation of network's buffers, it only used by Agent driver.
 */
typedef struct _vip_address_info {
	/*!< the logical address of wait-link buffer */
	void                *waitlink_logical;
	/*!< the physical address of wait-link buffer */
	vip_uint32_t        waitlink_physical;
	/*!< the size of wait-link buffer */
	vip_uint32_t        waitlink_size;

	/*!< the logical address of command buffer */
	void                *commandbuffer_logical;
	/*!< the physical address of command buffer */
	vip_uint32_t        commandbuffer_physical;
	/*!< the size of commands */
	vip_uint32_t        commandbuffer_size;

	/*!< network's input information */
	vip_input_output_info_t *input_info;
	/*!< the number of inputs */
	vip_uint32_t            input_num;

	/*!< network's output information */
	vip_input_output_info_t *output_info;
	/*!< the number of outputs */
	vip_uint32_t            output_num;
} vip_address_info_t;
#endif

#endif
