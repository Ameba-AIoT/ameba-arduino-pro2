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

#include <gc_vip_cpu.h>

#ifndef _GC_VIP_USER_CPU_H
#define _GC_VIP_USER_CPU_H
#include "gc_vip_lite.h"
#include "gc_vip_lite_network.h"

#if vpmdENABLE_SUPPORT_CPU_LAYER


vip_status_e gcvip_do_user_layer(
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);

#endif

#endif
