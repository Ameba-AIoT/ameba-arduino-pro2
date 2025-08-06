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


#ifndef _VIP_HAL_OS_PORT_H_
#define _VIP_HAL_OS_PORT_H_

#include <vip_hal.h>

#define VIPPTR_TO_UINT32(p) \
( \
    (vip_uint32_t) (viphal_uintptr_t) (p)\
)

#define VIPUINT32_TO_PTR(u) \
( \
    (vip_ptr) (viphal_uintptr_t) (u)\
)

#define VIPPTR_TO_UINT64(p) \
( \
    (vip_uint64_t) (viphal_uintptr_t) (p)\
)

#define VIPUINT64_TO_PTR(u) \
( \
    (vip_ptr) (viphal_uintptr_t) (u)\
)

#if defined(__ANDROID__)
#define PRINTF(level, ...)  viphal_os_print(level,__VA_ARGS__);
#else
#define PRINTF(level, ...)  viphal_os_print(level,"[0x%x]%s[%d], ", viphal_os_get_tid(), __FUNCTION__, __LINE__); \
                            viphal_os_print(level,__VA_ARGS__);
#endif

#define vip_print(...)    viphal_os_print(VIP_LOG_PRINT, __VA_ARGS__)

#if (vpmdENABLE_DEBUG_LOG == 4)
#define vip_debug(...)    PRINTF(VIP_LOG_DEBUG, __VA_ARGS__)
#define vip_info(...)     PRINTF(VIP_LOG_INFO, __VA_ARGS__)
#define vip_warning(...)  PRINTF(VIP_LOG_WARN, __VA_ARGS__)
#define vip_error(...)    PRINTF(VIP_LOG_ERROR, __VA_ARGS__)
#elif (vpmdENABLE_DEBUG_LOG == 3)
#define vip_debug(...)
#define vip_info(...)     PRINTF(VIP_LOG_INFO, __VA_ARGS__)
#define vip_warning(...)  PRINTF(VIP_LOG_WARN, __VA_ARGS__)
#define vip_error(...)    PRINTF(VIP_LOG_ERROR, __VA_ARGS__)
#elif (vpmdENABLE_DEBUG_LOG == 2)
#define vip_debug(...)
#define vip_info(...)
#define vip_warning(...)  PRINTF(VIP_LOG_WARN, __VA_ARGS__)
#define vip_error(...)    PRINTF(VIP_LOG_ERROR, __VA_ARGS__)
#elif (vpmdENABLE_DEBUG_LOG == 1)
#define vip_debug(...)
#define vip_info(...)
#define vip_warning(...)
#define vip_error(...)    PRINTF(VIP_LOG_ERROR, __VA_ARGS__)
#else
#define vip_debug(...)
#define vip_info(...)
#define vip_warning(...)
#define vip_error(...)
#endif


#if vpmdENABLE_FUNC_TRACE
#define VIP_FUNC_ENTER      \
    viphal_os_print(VIP_LOG_PRINT,"[0x%x]%s[%d] +++start\n", viphal_os_get_tid(), __FUNCTION__, __LINE__);
#define VIP_FUNC_EXIT       \
    viphal_os_print(VIP_LOG_PRINT,"[0x%x]%s[%d] ---exit\n", viphal_os_get_tid(), __FUNCTION__, __LINE__);
#else
#define VIP_FUNC_ENTER
#define VIP_FUNC_EXIT
#endif

#define CHECK_STATUS(string)  \
    if (status != VIP_SUCCESS) {    \
        vip_error("fail to check %s status=%d\n", string, status);    \
        vipGoOnError(status);  \
    }

/*
@brief initialize OS env.
@param mem_size, the size of video memory.
*/
vip_status_e viphal_os_init(
	void **os
);

/*
@brief uninitialize OS env.
@param os, os object.
*/
vip_status_e viphal_os_uninit(
	void **os
);

/*
@brief open a file.
@param name, file name.
@param mode, opem mode.
*/
viphal_file_t viphal_os_open_file(
	vip_char_t *name,
	viphal_file_mode_e mode
);

vip_status_e viphal_os_read_file(
	void *dst,
	vip_size_t size,
	viphal_file_t file
);

vip_status_e viphal_os_write_file(
	void *data,
	vip_size_t size,
	viphal_file_t file
);

/*
@brief seek file location.
*/
vip_status_e viphal_os_seek_file(
	vip_size_t offset,
	viphal_file_seek_e pos,
	viphal_file_t file
);

void viphal_os_close_file(
	viphal_file_t file
);

/*
@brief allocate memory from system.
@param size, the size of memory.
@param memory, memory object.
*/
vip_status_e viphal_os_allocate_memory(
	IN  vip_size_t Size,
	OUT void **memory
);

/*
@brief free memory.
@param memory, memory object.
*/
vip_status_e viphal_os_free_memory(
	IN void *memory
);

/*
@brief copy src to dst.
@param size the size of memory should be copy.
*/
vip_status_e viphal_os_copy_memory(
	IN void *dst,
	IN const void *src,
	IN vip_size_t size
);

/*
@brief zero memory.
@param size the size of memory should be zero.
*/
vip_status_e viphal_os_zero_memory(
	IN void *memory,
	IN vip_size_t size
);

/*
@brief print message on console
@param message, which message should be print.
*/
vip_status_e viphal_os_print(
	vip_log_level log_level,
	IN const vip_char_t *message,
	...
);

/*
@brief print message to buffer.
@param the buffer is stored message.
@param the size of message.
@param message, which message should be print.
*/
vip_status_e viphal_os_snprint(
	OUT vip_char_t *buffer,
	IN const vip_uint32_t size,
	IN  const vip_char_t *message,
	...
);

/*
@brief print string into a file(stream).
@param os object, create in viphal_os_init().
@param buffer, which memory should be print.
*/
vip_status_e viphal_os_print_string(
	IN void *os,
	IN void *stream,
	IN vip_char_t *buffer
);

/*
@brief create mutex.
@param mutex. mutex object
*/
vip_status_e viphal_os_create_mutex(
	vip_ptr *mutex
);

/*
@brief lock mutex.
@param mutex. mutex object
*/
vip_status_e viphal_os_lock_mutex(
	vip_ptr mutex
);

/*
@brief unlock mutex.
@param mutex. mutex object
*/
vip_status_e viphal_os_unlock_mutex(
	vip_ptr mutex
);

/*
@brief destroy mutex.
@param mutex. mutex object
*/
vip_status_e viphal_os_destroy_mutex(
	vip_ptr mutex
);

/*
@brief compare two strings.
@param s1, string one.
@param s2, string two.
*/
vip_int32_t viphal_os_strcmp(
	vip_char_t *s1,
	vip_char_t *s2
);

/*
@brief copy string src to dest.
@param dest, destation buffer.
@param src, resource buffer.
*/
vip_char_t *viphal_os_strcpy(
	vip_char_t *dest,
	vip_char_t *src
);

/*
@brief get the current system time.
return the time of day in microseconds.
*/
vip_uint64_t viphal_os_get_time(void);

/*
@brief get process id.
*/
vip_uint32_t viphal_os_get_pid(void);

/*
@brief get thread id.
*/
vip_uint32_t viphal_os_get_tid(void);


#endif /* __GC_VIP_USER_OS_H__ */
