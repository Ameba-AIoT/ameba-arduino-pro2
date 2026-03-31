/**************************************************************************//**
 * @file     hal_trng.c
 * @brief    This TRNG HAL API functions.
 *
 * @version  V1.00
 * @date     2021-03-8
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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
 ******************************************************************************/
#define DEBUG_TRNG 1


#include "hal_trng.h"
#include "hal_sys_ctrl.h"


#if defined(CONFIG_BUILD_NONSECURE)
#include "hal_sys_ctrl_nsc.h"
#endif

#if CONFIG_TRNG_EN
/**
 * @addtogroup ls_hal_trng TRNG
 * @{
 */




/**
 *  @brief To initial a TRNG devices adapter.
 *
 *  @param[in]  The TRNG devices adapter.
 *
 *  @returns HAL_OK: Initial succeed.
 */
hal_status_t hal_trng_init(hal_trng_sec_adapter_t *ptrng_adp)
{

#if TRNG_DEBUG
	dbg_printf("hal_trng.c line 159 hal_trng_init  \n\r ");//gigi test
#endif

	if (IS_AFTER_CUT_C(hal_sys_get_rom_ver())) { // C-cut and beyond

		hal_rtl_trng_sec_init(ptrng_adp);

	} else { // before C -Cut

#if TRNG_DEBUG
		dbg_printf("hal_trng.c line 165  hal_trng_init\n\r "); //gigi test
#endif
		hal_rtl_trng_sec_init_patch(ptrng_adp);
#if TRNG_DEBUG
		dbg_printf("hal_trng.c line 168 hal_trng_init \n\r "); //gigi test
#endif

	}
}

/**
 *  @brief To deinitial a TRNG devices adapter.
 *
 *  @param[in]  The TRNG devices adapter.
 *
 *  @returns HAL_OK: Initial succeed.
 */
hal_status_t hal_trng_deinit(hal_trng_sec_adapter_t *ptrng_adp)
{

#if TRNG_DEBUG
	dbg_printf("hal_trng.c line 193 hal_trng_deinit  \n\r ");//gigi test
#endif

	if (IS_AFTER_CUT_C(hal_sys_get_rom_ver())) { // C-cut and beyond

		hal_rtl_trng_sec_init(ptrng_adp);

	} else { // before C -Cut
#if TRNG_DEBUG
		dbg_printf("hal_trng.c line 200  hal_trng_deinit\n\r "); //gigi test
#endif
		hal_rtl_trng_sec_init_patch(ptrng_adp);
#if TRNG_DEBUG
		dbg_printf("hal_trng.c line 204 hal_trng_deinit \n\r "); //gigi test
#endif
	}
}

/**
 *  \brief read data of the TRNG
 *
 *  \param[in] ptrng_adp The TRNG device adapter.

 *   *  @param[in]   information data
 *
 *  \returns     trng data
 */

u32 hal_trng_get_rand(hal_trng_sec_adapter_t *ptrng_adp)
{
	volatile uint32_t rng_v = 0x0;

#if TRNG_DEBUG
	dbg_printf("hal_trng.c  line 355 hal_trng_get_rand  \n\r ");
#endif

	if (IS_AFTER_CUT_C(hal_sys_get_rom_ver())) { // C-cut and beyond
		rng_v = hal_rtl_trng_sec_get_rand(ptrng_adp);
	} else { // before C -Cut
		rng_v = hal_rtl_trng_sec_get_rand_patch(ptrng_adp);
	}

	return rng_v ;
}

#endif

