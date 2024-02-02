/******************************************************************************\
|* Copyright (c) 2017-2023 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/


#ifndef _GC_VIP_USER_H
#define _GC_VIP_USER_H

#include <gc_vip_common.h>
#include <gc_vip_user_os.h>

typedef void *gcvip_file_t;

typedef enum _gcvip_file_mode {
	FILE_CREATE    = 0,
	FILE_APPEND,
	FILE_READ,
	FILE_CREATETEXT,
	FILE_APPENDTEXT,
	FILE_READTEXT,
} gcvip_file_mode_e;

typedef enum _gcvip_file_seek {
	GCVIP_FILE_CUR = 0,
	GCVIP_FILE_SET,
	GCVIP_FILE_END
} gcvip_file_seek_e;

typedef struct _gcvip_submit_param {
	/* command buffer user space logical pointer */
	vip_uint8_t *cmd_logical;
	/* the physical address of command buffer */
	vip_uint32_t cmd_physical;
	/* the size of command buffer */
	vip_uint32_t cmd_size;
	/* command buffer video memory handle */
	void        *cmd_handle;

	/* the last command buffer logical address with this submitting */
	vip_uint8_t *last_cmd_logical;
	/* the last command buffer physical address with this submitting */
	vip_uint32_t last_cmd_physical;
	/* the size of last command buffer with this submitting */
	vip_uint32_t last_cmd_size;
	/* the last command buffer handle with this submitting */
	void        *last_cmd_handle;

	/* device id for vip multi-device */
	vip_uint32_t device_id;
#if vpmdENABLE_PREEMPTION
	/* priority of current cmd */
	vip_uint8_t  priority;
#endif
	vip_uint32_t time_out;
} gcvip_submit_param_t;

/*
@Brief Initialize resource in user layer.
@param sys_mem_size The size of system memory heap.
@param video_mem_size The size of video memory heap.
@param version The version of viplite.
*/
vip_status_e gcvip_user_init(
	IN vip_uint32_t sys_mem_size,
	IN vip_uint32_t video_mem_size,
	IN vip_uint32_t version
);

/*
@Brief Free resources at user layer.
*/
vip_status_e gcvip_user_destroy(void);

/*
@Brief Wait VIP to finsh current jobs (job is in the handle object pointer).
@param, handle, the video memory hendle of command buffer.
*/
vip_status_e gcvip_user_wait(
	IN void *handle,
	vip_uint32_t device_id,
	vip_uint32_t time_out
);

/*
@Brief Cancle this command run on vip hardware.
@param, handle, the video memory hendle of command buffer.
@param, hw_canel, true indicate that hardware canellation.
                  flase indicate that software canellation.
*/
#if vpmdENABLE_CANCELATION
vip_status_e gcvip_user_cancel(
	IN void *handle,
	vip_uint32_t device_id,
	vip_bool_e hw_cancel
);
#endif

/*
@ Brief Allocate a buffer, which could be used for command, intermediate pools, input/output and so on.
@param handle video memory handle.
@param memory, user space logical address.
@param physical, the virtual address of VIP when MMU is enabled, otherwise it is physical address.
@param size, the size of of user memory should be unwraped.
@param align, The alignment size of the video memory.
@param alloc_flag, The alloc flag of the video memory. see gckvip_video_mem_alloc_flag_e.
*/
vip_status_e gcvip_user_allocate_videomemory(
	vip_uint8_t **logical,
	void **handle,
	vip_uint32_t *physical,
	vip_uint32_t size,
	vip_uint32_t align,
	vip_uint32_t alloc_flag
);

/*
@ Brief Free a video memory buffer.
@param handle video memory handle.
*/
vip_status_e gcvip_user_free_videomemory(
	void *handle
);

/*
@Brief Allocate a system memory.
@param size The size of memory.
@param memory Allocate memory object.
*/
vip_status_e gcvip_user_allocate_memory(
	IN vip_uint32_t size,
	OUT void **memory
);

/*
@Brief Free system memory.
@param memory The memory object should be free.
*/
vip_status_e gcvip_user_free_memory(
	IN void *Memory
);

/*
@Brief mapping user space logical address
@param handle video memory handle.
@param physical, the virtual address of VIP or physical address.
@param vip_virtual, indicate the physical address is vip virtual address or not.
@logical, OUT. the logical address of this video memory.
*/
vip_status_e gcvip_user_map_userlogical(
	void *handle,
	vip_uint64_t physical,
	vip_bool_e vip_virtual,
	vip_uint8_t **logical
);

/*
@Brief unmapping user space logical address
@param handle video memory handle.
*/
vip_status_e gcvip_user_unmap_userlogical(
	void *handle
);

/*
@brief create a buffer from user contiguous or scatter non-contiguous physical address.
@param physical_table Physical address table. should be wraped for VIP hardware.
@param size_table The size of physical memory for each physical_table element.
@param physical_num The number of physical table element. physical_num is 1 when create buffer from contiguous phyiscal.
@param alloc_flag the flag of this video memroy. see gckvip_video_mem_alloc_flag_e.
@param memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param virtual_addr The VIP hardware virtual address mapped by MMU.
@param handle The handle of video memory.
*/
vip_status_e gcvip_user_wrap_userphysical(
	IN const vip_address_t *physical_table,
	IN const vip_uint32_t *size_table,
	IN vip_uint32_t physical_num,
	IN vip_uint32_t alloc_flag,
	IN vip_uint32_t memory_type,
	OUT vip_uint32_t *virtual_addr,
	OUT vip_uint8_t **logical,
	OUT void **handle
);

/*
@Brief UnWrap a user physical.
@param handle video memory handle.
@param physical, the virtual address of VIP.
*/
vip_status_e gcvip_user_unwrap_userphysical(
	IN void *handle,
	IN vip_uint32_t physical
);

/*
@Brief Wrap a user memory.
@param logical, user space logical address.
@param size, the size of of user memory should be unwraped.
@param memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param virtual_addr The VIP virtual address mapped from logical/physical address.
@param handle video memory handle.
*/
vip_status_e gcvip_user_wrap_usermemory(
	IN vip_ptr logical,
	IN vip_uint32_t size,
	IN vip_uint32_t memory_type,
	OUT vip_uint32_t *virtual_addr,
	OUT void **handle
);

/*
@Brief UnWrap a user memory.
@param handle video memory handle.
@param physical, the virtual address of VIP.
*/
vip_status_e gcvip_user_unwrap_usermemory(
	IN void *handle,
	IN vip_uint32_t physical
);

/*
@Brief Wrap a user memory fd.
@param fd the user memory file descriptor.
@param size, the size of of user memory should be unwraped.
@param memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param virtual_addr The VIP virtual address mapped from logical/physical address.
@param handle video memory handle.
*/
#if vpmdENABLE_CREATE_BUF_FD
vip_status_e gcvip_user_wrap_userfd(
	IN vip_uint32_t fd,
	IN vip_uint32_t size,
	IN vip_uint32_t memory_type,
	OUT vip_uint32_t *virtual_addr,
	OUT vip_uint8_t **logical,
	OUT void **handle
);

/*
@Brief UnWrap a user memory from fd(file descriptor).
@param handle video memory handle.
@param physical, the virtual address of VIP.
*/
vip_status_e gcvip_user_unwrap_userfd(
	IN void *handle,
	IN vip_uint32_t physical
);
#endif

/*
@Brief Copy memory data from src to dst.
@param dst Destination memory.
@param src Source memory.
@param size The size of memory shoule be copy.
*/
vip_status_e gcvip_user_memcopy(
	IN void *dst,
	IN const void *src,
	IN vip_uint32_t size
);

/*
brief fill zero to memory
param memory
param size The size of memory should be fill zero.
*/
vip_status_e gcvip_user_zero_memory(
	IN void *memory,
	IN vip_uint32_t size
);

/*
@Brief Submit the commands (network) to HW to run.
@param param The submit param structure.
*/
vip_status_e gcvip_user_submit(
	IN gcvip_submit_param_t *param
);

/*
brief read a hardware register
param core_id the index of hardware core.
param address the address read.
param data data read to address.
*/
vip_status_e gcvip_user_read_reg(
	IN vip_uint32_t core_id,
	IN  vip_uint32_t address,
	OUT vip_uint32_t *data
);

/*
brief write a hardware register
param core_id the index of hardware core.
param address the address write.
param data data write to address.
*/
vip_status_e gcvip_user_write_reg(
	IN  vip_uint32_t core_id,
	IN  vip_uint32_t address,
	IN  vip_uint32_t data
);

/*
brief print string to file.
param stream the object stream.  FILE * pointer.
param buffer string store in buffer object.
*/
vip_status_e gcvip_user_print_string(
	IN void *stream,
	IN vip_char_t *buffer
);

/*
brief Query address infomation. wait-link buffer address for Agent driver.
param data, query address info stucture.
*/
vip_status_e gcvip_user_query_address_info(
	IN void *data
);

/*
brief Query power infomation. power status.
param data, query power info stucture.
*/
vip_status_e gcvip_user_query_power_info(
	IN void *data
);

/*
brief Query feature database.
param data, query database stucture.
*/
vip_status_e gcvip_user_query_database(
	IN void *data
);

/*
brief Query MMU page table infomation for dumping capture file.
param data, query mmu info stucture.
*/
vip_status_e gcvip_user_query_mmu_info(
	IN void *data
);

/*
brief Query profiling data, such as inference time, total cycle.
@param data, query profiling stucture. gckvip_query_profiling_t.
*/
vip_status_e gcvip_user_query_profiling(
	IN void *data
);

/*
brief Query kernel space driver status.
@param data, query driver status stucture. gckvip_query_driver_status_t.
*/
vip_status_e gcvip_user_query_driver_status(
	IN void *data
);

/*
@brief Flush video memory CPU cache.
@param hanlde, the video memory handle be flush.
@param physical, the physical base address be flush.
@param logical, the logical base address be flush.
@param size, the size of memory should be flush. So flush memory address range is physical to physical+size.
@param type, the type of flush cache. see gckvip_cache_type_e.
*/
vip_status_e gcvip_user_flush_cache(
	IN void *handle,
	IN vip_uint32_t physical,
	IN void *logical,
	IN vip_uint32_t size,
	IN vip_uint8_t type
);

/*
@brief Give user applications more control over power management for VIP cores.
@perperty Control VIP core frequency and power status by property. see vip_power_property_e.
@value The value for vip_power_property_e property.
@device_id, The index of device.
*/
vip_status_e gcvip_user_power_management(
	IN vip_enum property,
	IN void *value,
	IN vip_uint32_t device_id
);

/*
@brief dump buffer in hex format. only dump buffer for debugging.
@param buffer, data buffer address.
@param size, the size of the buffer.
*/
vip_status_e gcvip_user_dump_data(
	vip_uint32_t *buffer,
	vip_uint32_t size
);


vip_status_e gcvip_user_query_register_dump(
	void **handle,
	phy_address_t *physical,
	vip_uint32_t *count
);

#if vpmdREGISTER_NETWORK
vip_status_e gcvip_user_register_network(
	void *network_handle,
	vip_char_t_ptr network_name,
	vip_uint32_t segment_count
);

vip_status_e gcvip_user_register_segment(
	void *segment_handle,
	void *network_handle,
	vip_uint32_t segment_index,
	vip_uint32_t operation_start,
	vip_uint32_t operation_end
);

vip_status_e gcvip_user_unregister_network(
	void *network_handle
);

vip_status_e gcvip_user_unregister_segment(
	void *segment_handle
);
#endif
#endif
