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


#ifndef _NBG_LK_CAPTURE_H
#define _NBG_LK_CAPTURE_H

#include <vip_lite_config.h>
#include <vip_lite.h>
#include <vip_hal_os_port.h>
#include <nbg_lk_debug.h>


#define CHECK_CAPTURE_FUNC_CONFIG(network)                       \
{                                                                \
  nbglk_context_t* context_t = nbglk_get_context();         \
  if (network != VIP_NULL) {                                     \
      if ((network->occur_hang != vip_true_e) &&                 \
          (context_t->func_config.enable_capture == vip_false_e)){ \
          return VIP_SUCCESS;                                    \
      }                                                          \
  }                                                              \
  else {                                                         \
      if (context_t->func_config.enable_capture == vip_false_e) {\
          return VIP_SUCCESS;                                    \
      }                                                          \
  }                                                              \
}


#if (vpmdENABLE_HANG_DUMP > 1) || vpmdENABLE_CAPTURE
typedef enum _nbglk_capture_type {
	NBGLK_CAPTURE_TYPE_CAP    = 0,
	NBGLK_CAPTURE_TYPE_HANG   = 1,
	NBGLK_CAPTURE_TYPE_GROUP  = 2,
} nbglk_capture_type_e;

typedef enum _nbglk_capture_buf_type {
	NBGLK_CAPTURE_BUF_COMMAND = 0,
	NBGLK_CAPTURE_BUF_STATES,
	NBGLK_CAPTURE_BUF_POOL,
	NBGLK_CAPTURE_BUF_INPUT,
	NBGLK_CAPTURE_BUF_VERIFY,
	NBGLK_CAPTURE_BUF_MEMORY,
}   nbglk_capture_buf_type_e;

void nbglk_capture_buffer(
	viphal_file_t fp,
	void  *buffers,
	vip_uint64_t physical,
	vip_size_t size,
	nbglk_capture_buf_type_e type
);
#endif


#if (vpmdENABLE_CAPTURE > 1) || (vpmdENABLE_HANG_DUMP > 1)
vip_status_e nbglk_capture_hang_dump(
	vip_network_t *network
);

vip_status_e nbglk_capture_network_output(
	viphal_file_t capture_file,
	vip_network_t *network
);

vip_status_e nbglk_capture_network_input(
	viphal_file_t capture_file,
	vip_network network
);
#endif


#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
void nbglk_capture_record_list(
	viphal_file_t capture_file,
	vip_network_t *network
);

vip_status_e nbglk_capture_dump_states(
	viphal_file_t capture_file,
	vip_network_t *network,
	nbglk_segment_t *segment
);

vip_status_e nbglk_capture_header_info(
	viphal_file_t capture_file,
	vip_network network
);

vip_status_e nbglk_capture_register_info(
	viphal_file_t capture_file,
	vip_network network
);

vip_status_e nbglk_capture_init_command(
	viphal_file_t capture_file,
	vip_network network
);

#if vpmdPRELOAD_COEFF > 1
vip_status_e nbglk_capture_npu_preload_coeff(
	viphal_file_t capture_file,
	vip_network network
);
#endif

#if vpmdENABLE_CAPTURE_MMU
vip_status_e nbglk_capture_mmu_info(
	viphal_file_t capture_file,
	vip_network network
);
#endif

vip_status_e nbglk_capture_init(
	vip_network network,
	vip_group group,
	nbglk_capture_type_e type
);

vip_status_e nbglk_capture_uninit(
	vip_network network,
	vip_group group
);
#endif

#if vpmdENABLE_GROUP_MODE && ((vpmdENABLE_HANG_DUMP > 1) || (vpmdENABLE_CAPTURE > 1))
vip_status_e nbglk_capture_group(
	vip_group group,
	vip_bool_e is_hang
);
#endif


#if vpmdENABLE_CAPTURE
vip_status_e nbglk_capture_network(
	vip_network network
);
#endif

#endif
