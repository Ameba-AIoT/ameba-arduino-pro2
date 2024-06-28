/******************************************************************************
 *
 * Copyright(c) 2007 - 2024 Realtek Corporation. All rights reserved.
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
 *
 ******************************************************************************/
#ifndef _LINUX_BYTEORDER_SWAB_H
#define _LINUX_BYTEORDER_SWAB_H
/*
#if !defined(CONFIG_PLATFORM_MSTAR_TITANIA12) && !defined(CONFIG_PLATFORM_8195A)
*/
#if !defined(CONFIG_PLATFORM_MSTAR_TITANIA12)

__inline static __u16  ___swab16(__u16 x)
{
	__u16 __x = x;
	return
		((__u16)(
			 (((__u16)(__x) & (__u16)0x00ffU) << 8) |
			 (((__u16)(__x) & (__u16)0xff00U) >> 8)));

}

__inline static __u32  ___swab32(__u32 x)
{
	__u32 __x = (x);
	return ((__u32)(
				(((__u32)(__x) & (__u32)0x000000ffUL) << 24) |
				(((__u32)(__x) & (__u32)0x0000ff00UL) <<  8) |
				(((__u32)(__x) & (__u32)0x00ff0000UL) >>  8) |
				(((__u32)(__x) & (__u32)0xff000000UL) >> 24)));
}

__inline static __u64  ___swab64(__u64 x)
{
	__u64 __x = (x);

	return
		((__u64)(\
				 (__u64)(((__u64)(__x) & (__u64)0x00000000000000ffULL) << 56) | \
				 (__u64)(((__u64)(__x) & (__u64)0x000000000000ff00ULL) << 40) | \
				 (__u64)(((__u64)(__x) & (__u64)0x0000000000ff0000ULL) << 24) | \
				 (__u64)(((__u64)(__x) & (__u64)0x00000000ff000000ULL) <<  8) | \
				 (__u64)(((__u64)(__x) & (__u64)0x000000ff00000000ULL) >>  8) | \
				 (__u64)(((__u64)(__x) & (__u64)0x0000ff0000000000ULL) >> 24) | \
				 (__u64)(((__u64)(__x) & (__u64)0x00ff000000000000ULL) >> 40) | \
				 (__u64)(((__u64)(__x) & (__u64)0xff00000000000000ULL) >> 56)));
	\
}
#endif // CONFIG_PLATFORM_MSTAR_TITANIA12

#ifndef __arch__swab16
__inline static __u16 __arch__swab16(__u16 x)
{
	return ___swab16(x);
}

#endif

#ifndef __arch__swab32
__inline static __u32 __arch__swab32(__u32 x)
{
	__u32 __tmp = (x) ;
	return ___swab32(__tmp);
}
#endif

#ifndef __arch__swab64

__inline static __u64 __arch__swab64(__u64 x)
{
	__u64 __tmp = (x) ;
	return ___swab64(__tmp);
}


#endif

#ifndef __swab16
#define __swab16(x) __fswab16(x)
#define __swab32(x) __fswab32(x)
#define __swab64(x) __fswab64(x)
#endif	// __swab16

__inline static __u16 __fswab16(__u16 x)
{
	return __arch__swab16(x);
}

__inline static __u32 __fswab32(__u32 x)
{
	return __arch__swab32(x);
}

#endif /* _LINUX_BYTEORDER_SWAB_H */

