/**************************************************************************//**
 * @file     memory.h
 * @brief    The memory utility functions definition.
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

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "platform_conf.h"
#include "utility.h"

/**
 * @addtogroup util_memory Memory
 * @ingroup 8710c_util
 * @{
 * @brief The memory utility API.
 */

#if defined(ROM_REGION)
#if defined ( __CC_ARM ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
// _memset function name conflict with ARMCC Lib. So rename it
#define _memset         __memset
#endif

int _memcmp(const void *av, const void *bv, size_t len);
void *_memcpy(void *s1, const void *s2, size_t n);
void *_memmove(void *destaddr, const void *sourceaddr, unsigned length);
void *_memset(void *dst0, int val, size_t length);
int _memcmp_s(const void *av, const void *bv, size_t len);

#else   // else of "#if defined(ROM_REGION)"
/**
  \brief   Memeory compare
  \details Compares contents of 2 memory block with a given size.
           To check whether all the memory contents are the same or not.
  \param[in]   av    The first memory address for the comparison.
  \param[in]   bv    The second memory address for the comparison.
  \param[in]   len   The lentg, in byte, of the memory to compare.
  \retval   0  All the contents for the comparison are the same.
  \return   !=0  At least 1 byte of data is not equivalent.
*/
__STATIC_INLINE int rt_memcmp(const void *av, const void *bv, size_t len)
{
	return utility_stubs.memcmp(av, bv, len);
}

/**
  \brief   Memeory copys
  \details Copy a given size of memory block from the specific
           source address to the given destination address.
  \param[in]   s1   The destination address.
  \param[in]   s2   The source address.
  \param[in]   n    The size, in byte, of the memory to copy.
  \return   A poiner to the desination memory address.
*/
__STATIC_INLINE void *rt_memcpy(void *s1, const void *s2, size_t n)
{
	return utility_stubs.memcpy(s1, s2, n);
}

/**
  \brief   Memeory move
  \details Copies n bytes from memory area sourceaddr to memory
           area destaddr. The memory areas may overlap: copying
           takes place as though the bytes in sourceaddr are first
           copied into a temporary array that does not overlap
           sourceaddr or destaddr, and the bytes are then copied from the
           temporary array to destaddr.
           source address to the given destination address.
  \param[in]   destaddr   The destination memory address.
  \param[in]   sourceaddr The source memory address.
  \param[in]   length    The length, in byte, of the memory movement.
  \return   A poiner to the desination memory address.
*/
__STATIC_INLINE void *rt_memmove(void *destaddr, const void *sourceaddr, unsigned length)
{
	return utility_stubs.memmove(destaddr, sourceaddr, length);
}

/**
  \brief   Memeory set
  \details Fills the first n bytes of the memory area
           pointed to by dst0 with the constant byte val.
  \param[in]   dst0     The destination memory address.
  \param[in]   val      The value to fill the memory.
  \param[in]   length   The length, in byte, of the memory to be filled.
  \return   A poiner to the desination memory address.
*/
__STATIC_INLINE void *rt_memset(void *dst0, int val, size_t length)
{
	return utility_stubs.memset(dst0, val, length);
}

/**
  \brief   Memeory compare (Secure version, no timing side-channel leakage)
  \details Compares contents of 2 memory block with a given size.
           To check whether all the memory contents are the same or not.
  \param[in]   av    The first memory address for the comparison.
  \param[in]   bv    The second memory address for the comparison.
  \param[in]   len   The lentg, in byte, of the memory to compare.
  \retval   0  All the contents for the comparison are the same.
  \return   !=0  At least 1 byte of data is not equivalent.
*/
__STATIC_INLINE int rt_memcmp_s(const void *av, const void *bv, size_t len)
{
	return utility_stubs.memcmp_s(av, bv, len);
}

#define memcmp          rt_memcmp
#define memcpy          rt_memcpy
#define memmove         rt_memmove
#define memset          rt_memset
#endif  // end of else of "#if defined(ROM_REGION)"

/** @} */ /* End of group util_memory */

#endif  // _MEMORY_H_

