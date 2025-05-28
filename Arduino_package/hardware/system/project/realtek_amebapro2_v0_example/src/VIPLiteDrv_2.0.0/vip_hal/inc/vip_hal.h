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


#ifndef _VIP_HAL_H_
#define _VIP_HAL_H_

#include <vip_lite_config.h>
#include <vip_hal_os.h>

typedef void *viphal_file_t;

typedef enum _viphal_file_mode {
	FILE_CREATE    = 0,
	FILE_APPEND,
	FILE_READ,
	FILE_CREATETEXT,
	FILE_APPENDTEXT,
	FILE_READTEXT,
} viphal_file_mode_e;

typedef enum _viphal_file_seek {
	VIPHAL_FILE_CUR      = 0x0,
	VIPHAL_FILE_SET      = 0x1,
	VIPHAL_FILE_END      = 0x2,
	VIPHAL_FILE_BACKWARD = 0x4,
} viphal_file_seek_e;

typedef struct _viphal_task_param {
	vip_uint32_t task_id;
	vip_uint32_t subtask_count;
	vip_uint32_t subtask_index;
	/* device index for vip multi-device */
	vip_uint32_t device_index;
	/* start core index for cur device */
	vip_uint32_t core_index;
	/* core cnt of cur submit */
	vip_uint32_t core_cnt;
	/* priority of current cmd */
	vip_uint8_t priority;
	vip_uint32_t time_out;
	vip_uint8_t need_schedule;
} viphal_task_param_t;

/*
@Brief Initialize resource in vip-hal layer.
@param sys_mem_size The size of system memory heap.
@param video_mem_size The size of video memory heap.
@param version The version of viplite.
*/
vip_status_e viphal_init(
	IN vip_uint32_t sys_mem_size,
	IN vip_uint32_t video_mem_size,
	IN vip_uint32_t version
);

/*
@Brief Free resources at vip-hal layer.
*/
vip_status_e viphal_destroy(void);

/*
@Brief Wait VIP to finsh the task_id task.
@param, task_id, the id of task should be wait complete.
*/
vip_status_e viphal_wait_task(
	IN vip_uint32_t task_id,
	IN vip_uint32_t subtask_index
);

/*
@Brief Cancle this command run on vip hardware.
@param, task_id, the id of task should be cancel.
@param, subtask_index, the id of subtask in task.
*/
#if vpmdENABLE_CANCELATION
vip_status_e viphal_cancel_task(
	IN vip_uint32_t task_id,
	IN vip_uint32_t subtask_index
);
#endif

/*
@ Brief Allocate a buffer, which could be used for command, intermediate pools, input/output and so on.
@param mem_id the id of video memory.
@param memory, user space logical address.
@param physical, the virtual address of VIP when MMU is enabled, otherwise it is physical address.
@param size, the size of of user memory should be unwraped.
@param align, The alignment size of the video memory.
@param alloc_flag, The alloc flag of the video memory. see vipdrv_video_mem_alloc_flag_e.
*/
vip_status_e viphal_allocate_videomemory(
	OUT vip_uint8_t **logical,
	OUT vip_uint32_t *mem_id,
	OUT vip_address_t *physical,
	IN vip_size_t size,
	IN vip_uint32_t align,
	IN vip_uint32_t alloc_flag
);

/*
@ Brief Free a video memory buffer.
@param mem_id the id of video memory.
*/
vip_status_e viphal_free_videomemory(
	IN vip_uint32_t mem_id
);

/*
@Brief Allocate a system memory.
@param size The size of memory.
@param memory Allocate memory object.
*/
vip_status_e viphal_allocate_memory(
	IN vip_size_t size,
	OUT void **memory
);

/*
@Brief Free system memory.
@param memory The memory object should be free.
*/
vip_status_e viphal_free_memory(
	IN void *Memory
);

/*
@Brief mapping user space logical address
@param mem_id the id of video memory.
@logical, OUT. the logical address of this video memory.
*/
vip_status_e viphal_map_userlogical(
	IN vip_uint32_t mem_id,
	OUT vip_uint8_t **logical
);

/*
@Brief unmapping user space logical address
@param mem_id the id of video memory.
*/
vip_status_e viphal_unmap_userlogical(
	IN vip_uint32_t mem_id
);

/*
@brief create a buffer from user contiguous or scatter non-contiguous physical address.
@param physical_table Physical address table. should be wraped for VIP hardware.
@param size_table The size of physical memory for each physical_table element.
@param physical_num The number of physical table element.
 physical_num is 1 when create buffer from contiguous phyiscal.
@param alloc_flag the flag of this video memroy. see vipdrv_video_mem_alloc_flag_e.
@param memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param virtual_addr The VIP hardware virtual address mapped by MMU.
@param mem_id the id of video memory.
*/
vip_status_e viphal_wrap_userphysical(
	IN const vip_address_t *physical_table,
	IN const vip_uint32_t *size_table,
	IN vip_uint32_t physical_num,
	IN vip_uint32_t alloc_flag,
	IN vip_uint32_t memory_type,
	OUT vip_address_t *virtual_addr,
	OUT vip_uint8_t **logical,
	OUT vip_uint32_t *mem_id
);

/*
@Brief UnWrap a user physical.
@param mem_id the id of video memory.
*/
vip_status_e viphal_unwrap_userphysical(
	IN vip_uint32_t mem_id
);

/*
@Brief Wrap a user memory.
@param logical, user space logical address.
@param size, the size of of user memory should be unwraped.
@param memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param virtual_addr The VIP virtual address mapped from logical/physical address.
@param mem_id the id of video memory.
*/
vip_status_e viphal_wrap_usermemory(
	IN vip_ptr logical,
	IN vip_size_t size,
	IN vip_uint32_t memory_type,
	OUT vip_address_t *virtual_addr,
	OUT vip_uint32_t *mem_id
);

/*
@Brief UnWrap a user memory.
@param mem_id the id of video memory.
*/
vip_status_e viphal_unwrap_usermemory(
	IN vip_uint32_t mem_id
);

/*
@Brief Wrap a user memory fd.
@param fd the user memory file descriptor.
@param size, the size of of user memory should be unwraped.
@param memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param virtual_addr The VIP virtual address mapped from logical/physical address.
@param mem_id the id of video memory.
*/
#if vpmdENABLE_CREATE_BUF_FD
vip_status_e viphal_wrap_userfd(
	IN vip_uint32_t fd,
	IN vip_size_t size,
	IN vip_uint32_t memory_type,
	OUT vip_address_t *virtual_addr,
	OUT vip_uint8_t **logical,
	OUT vip_uint32_t *mem_id
);

/*
@Brief UnWrap a user memory from fd(file descriptor).
@param mem_id the id of video memory.
*/
vip_status_e viphal_unwrap_userfd(
	IN vip_uint32_t mem_id
);
#endif

/*
@Brief Copy memory data from src to dst.
@param dst Destination memory.
@param src Source memory.
@param size The size of memory shoule be copy.
*/
vip_status_e viphal_copy_memory(
	IN void *dst,
	IN const void *src,
	IN vip_size_t size
);

/*
brief fill zero to memory
param memory
param size The size of memory should be fill zero.
*/
vip_status_e viphal_zero_memory(
	IN void *memory,
	IN vip_size_t size
);

/*
@Brief Submit the commands (network) to HW to run.
@param param The submit param structure.
*/
vip_status_e viphal_submit_task(
	IN viphal_task_param_t *param
);


/*
brief read a hardware register
param dev_index, the index of device.
param core_index the index of hardware core belong to device.
param address the address read.
param data data read to address.
*/
vip_status_e viphal_read_reg(
	IN  vip_uint32_t dev_index,
	IN  vip_uint32_t core_index,
	IN  vip_uint32_t address,
	OUT vip_uint32_t *data
);

/*
brief write a hardware register
param dev_index, the index of device.
param core_index the index of hardware core belong to device.
param address the address write.
param data data write to address.
*/
vip_status_e viphal_write_reg(
	IN  vip_uint32_t dev_index,
	IN  vip_uint32_t core_index,
	IN  vip_uint32_t address,
	IN  vip_uint32_t data
);

/*
brief print string to file.
param stream the object stream.  FILE * pointer.
param buffer string store in buffer object.
*/
vip_status_e viphal_print_string(
	IN void *stream,
	IN vip_char_t *buffer
);

/*
brief Query address infomation. wait-link buffer address for Agent driver.
param data, query address info stucture.
*/
vip_status_e viphal_query_address_info(
	IN void *data
);

/*
brief Query feature database.
param data, query database stucture.
*/
vip_status_e viphal_query_database(
	IN void *data
);

/*
brief Query MMU page table infomation for dumping capture file.
param data, query mmu info stucture.
*/
vip_status_e viphal_query_mmu_info(
	IN void *data
);

/*
brief Query profiling data, such as inference time, total cycle.
@param data, query profiling stucture. vipdrv_query_profiling_t.
*/
vip_status_e viphal_query_profiling(
	IN void *data
);

/*
brief Query vip-drv space driver status.
@param data, query driver status stucture. vipdrv_query_driver_status_t.
*/
vip_status_e viphal_query_driver_status(
	IN void *data
);

/*
@brief Flush video memory CPU cache.
@param mem_id, the id of video memory be flush.
@param type, the type of flush cache. see vipdrv_cache_type_e.
*/
vip_status_e viphal_flush_cache(
	IN vip_uint32_t mem_id,
	IN vip_uint8_t type
);

/*
@brief Give user applications more control over power management for VIP cores.
@perperty Control VIP core frequency and power status by property. see vip_power_property_e.
@value The value for vip_power_property_e property.
@device_index, The index of device.
*/
vip_status_e viphal_power_management(
	IN vip_enum property,
	IN void *value,
	IN vip_uint32_t device_index
);

/*
@brief dump buffer in hex format. only dump buffer for debugging.
@param buffer, data buffer address.
@param size, the size of the buffer.
*/
vip_status_e viphal_dump_data(
	IN vip_uint32_t *buffer,
	IN vip_uint32_t size
);


vip_status_e viphal_query_register_dump(
	OUT vip_uint32_t *mem_id,
	OUT vip_physical_t *physical,
	OUT vip_uint32_t *count
);

vip_status_e viphal_task_create(
	IN vip_char_t_ptr task_name,
	IN vip_uint32_t subtask_count,
	OUT vip_uint32_t *task_id
);

vip_status_e viphal_task_set_property(
	IN vip_uint32_t task_id,
	IN vip_uint32_t type,
	IN vip_uint32_t subtask_index,
	IN vip_uint32_t subtask_id,
	IN vip_uint32_t size,
	IN vip_uint32_t patch_cnt
);

#if vpmdTASK_SCHEDULE
vip_status_e viphal_task_set_patch_info(
	IN vip_uint32_t task_id,
	IN vip_uint32_t type,
	IN vip_uint32_t subtask_index,
	IN vip_uint32_t patch_index,
	IN vip_uint32_t patch_type,
	IN vip_uint32_t offset,
	IN vip_uint32_t size,
	IN vip_uint32_t core_index,
	IN vip_uint32_t core_count
);

vip_status_e viphal_task_dup_info(
	IN vip_uint32_t task_id,
	IN vip_uint32_t type,
	IN vip_uint32_t subtask_index,
	IN vip_uint32_t task_id_dup,
	IN vip_uint32_t type_dup,
	IN vip_uint32_t subtask_index_dup
);
#endif

vip_status_e viphal_task_destroy(
	IN vip_uint32_t task_id
);

vip_uint32_t viphal_query_hw_feature(
	IN vip_uint32_t feature
);
#endif
