/**************************************************************************//**
 * @file     utility.h
 * @brief    The misc. utility functions definition.
 * @version  V1.00
 * @date     2016-09-30
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _UTILITY_H_
#define _UTILITY_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @addtogroup 8710c_util Utilities
 * @{
 * @brief Utility API.
 */

#include "cmsis_compiler.h"

/**
 * @addtogroup util_memory Memory
 * @{
 */

/// @cond DOXYGEN_EXCLUDED

/**
  \brief  The data structure of the stubs functions of the utility API in ROM.
*/
typedef struct utility_func_stubs_s {
	uint32_t *config_debug_err;
	uint32_t *config_debug_warn;
	uint32_t *config_debug_info;

	int (*memcmp)(const void *av, const void *bv, size_t len);
	void *(*memcpy)(void *s1, const void *s2, size_t n);
	void *(*memmove)(void *destaddr, const void *sourceaddr, unsigned length);
	void *(*memset)(void *dst0, int val,  size_t length);

	void (*dump_bytes)(u8 *pdata, u32 len);
	void (*dump_words)(u8 *src, u32 len);
	int (*memcmp_s)(const void *av, const void *bv, size_t len);

	uint32_t reserved[7];  // reserved space for next ROM code version function table extending.
} utility_func_stubs_t;

/// @endcond /* end of condition DOXYGEN_EXCLUDED */

#if !defined(ROM_REGION)

extern utility_func_stubs_t utility_stubs;
#if !defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_NONSECURE)
extern utility_func_stubs_t __rom_stubs_utility_ns;
#endif

/**
  \brief   Memory dumps.
  \details Byte by byte to dumps a block of memory with specified address and size.
  \param[in]   src      The memory address to dump.
  \param[in]   len      The size (in byte) the memory to dump.
  \return   void.
*/
__STATIC_INLINE void dump_bytes(u8 *src, u32 len)
{
	utility_stubs.dump_bytes(src, len);
}

/**
  \brief   Memory dumps.
  \details Word by word to dumps a block of memory with specified address and size.
  \param[in]   src      The memory address to dump.
  \param[in]   len      The size (in byte) the memory to dump.
  \return   void.
*/

__STATIC_INLINE void dump_words(u8 *src, u32 len)
{
	utility_stubs.dump_words(src, len);
}
#else // defined ROM_REGION

void dump_for_one_bytes(u8 *pdata, u32 len);
void dump_for_one_words(u8 *src, u32 len);

#endif  // end of "#if !defined(ROM_REGION)"

/** @} */ /* End of group util_memory */

/** @} */ /* End of group 8710c_util */
#ifdef  __cplusplus
}
#endif

#endif  // _UTILITY_H_

