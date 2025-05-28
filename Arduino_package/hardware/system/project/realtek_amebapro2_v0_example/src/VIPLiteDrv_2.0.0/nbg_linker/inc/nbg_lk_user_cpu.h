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

#include <nbg_lk_cpu.h>

#ifndef _NBG_LK_USER_CPU_H
#define _NBG_LK_USER_CPU_H
#include "nbg_lk.h"
#include "nbg_lk_network.h"

#if vpmdENABLE_SUPPORT_CPU_LAYER


vip_status_e nbglk_do_user_layer(
	vip_network_t *network,
	nbglk_segment_t *segment
);

#endif

#endif
