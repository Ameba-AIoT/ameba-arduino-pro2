/**************************************************************************//**
 * @file    trng_api.c
 * @brief    main function example.
 * @version  V1.00
 * @date     2021 8 2
 *
 * @note
 *
 ******************************************************************************
 * @attention
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

#include "hal_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "hal_trng.h"
#include "device.h"
#if defined(CONFIG_BUILD_NONSECURE)

#include "hal_trng_sec_nsc.h"

#endif



#if DEVICE_TRNG


void trng_init(void)
{
	hal_trng_sec_init();
}
void trng_deinit(void)
{
	hal_trng_sec_deinit();
}

u32 trng_get_rand(void)
{
	volatile uint32_t rng_v = 0x0;
	rng_v  =  hal_trng_sec_get_rand();
	return rng_v;
}
#endif //#if DEVICE_TRNG
