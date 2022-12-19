/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2017 - 2022 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _GC_VIP_KERNEL_H
#define _GC_VIP_KERNEL_H

#include <gc_vip_common.h>
#include <gc_vip_kernel_heap.h>
#include <gc_vip_kernel_util.h>
#include <gc_vip_kernel_share.h>
#include <gc_vip_kernel_port.h>

#define GCKVIP_CHECK_CORE(core)                                                                 \
{                                                                                               \
    gckvip_context_t *kcontext = gckvip_get_context();                                          \
    if ((core) > kcontext->core_count) {                                                        \
        PRINTK_E("failed core=%d is larger than core count=%d\n", core, kcontext->core_count);  \
        GCKVIP_DUMP_STACK();                                                                    \
        gcGoOnError(VIP_ERROR_FAILURE);                                                         \
    }                                                                                           \
}

#define GCKVIP_CHECK_DEV(dev)                                                         \
{                                                                                     \
    gckvip_context_t *kcontext = gckvip_get_context();                                \
    if ((dev) > kcontext->device_count) {                                             \
        PRINTK_E("failed device id =%d is larger than device count=%d\n",             \
                  dev, kcontext->device_count);                                       \
        GCKVIP_DUMP_STACK();                                                          \
        gcGoOnError(VIP_ERROR_FAILURE);                                               \
    }                                                                                 \
}

/*
@brief define loop fun for each vip core
*/
#define GCKVIP_LOOP_HARDWARE_START                                  \
{  vip_uint32_t core = 0;                                           \
   gckvip_context_t *kcontext = gckvip_get_context();               \
   for (core = 0 ; core < kcontext->core_count; core++) {           \
       gckvip_hardware_t *hardware = gckvip_get_hardware(core);     \
       if (hardware != VIP_NULL) {                                  \

#define GCKVIP_LOOP_HARDWARE_END }}}

/*
@brief define loop fun for each vip device
*/
#define GCKVIP_LOOP_DEVICE_START                          \
{  vip_uint32_t dev = 0;                                  \
   gckvip_context_t *kcontext = gckvip_get_context();     \
   for (dev = 0 ; dev < kcontext->device_count; dev++) {    \
        gckvip_device_t *device = &kcontext->device[dev];

#define GCKVIP_LOOP_DEVICE_END }}


typedef struct _gckvip_submit {
	/* first command buffer */
	void            *cmd_handle;
	vip_uint8_t     *cmd_logical;
	vip_uint32_t    cmd_physical;
	vip_uint32_t    cmd_size;

	/*
	last command buffer. it is used to support submit multiple command buffer.
	If only one command buffer submit, you can set cmd_xxx equal to last_cmd_xxx.
	*/
	void            *last_cmd_handle;
	vip_uint8_t     *last_cmd_logical;
	vip_uint32_t    last_cmd_physical;
	vip_uint32_t    last_cmd_size;
	/*
	submit command and sync multiple core when combine mode
	*/
	vip_bool_e      wait_event;
	vip_uint32_t    device_id;
} gckvip_submit_t;

typedef struct _gckvip_wait_cmd {
	void            *cmd_handle;
	vip_uint32_t    mask;
	vip_uint32_t    time_out;
} gckvip_wait_cmd_t;

#if vpmdENABLE_MULTIPLE_TASK
typedef enum _gckvip_submit_status_e {
	GCKVIP_SUBMIT_NONE           = 0,
	GCKVIP_SUBMIT_EMPTY          = 1,
	GCKVIP_SUBMIT_WITH_DATA      = 2,
	GCKVIP_SUBMIT_INFER_START    = 3,
	GCKVIP_SUBMIT_INFER_END      = 4,
	GCKVIP_SUBMIT_MAX,
} gckvip_submit_status_e;
typedef struct _gckvip_multi_thread_submit {
	gckvip_submit_t                   submit_handle;
	gckvip_queue_data_t               *queue_data;
	gckvip_signal                     wait_signal;
	volatile gckvip_submit_status_e   status;
} gckvip_multi_thread_submit_t;
#endif

#if vpmdENABLE_APP_PROFILING
typedef struct _gckvip_profiling_data {
	vip_uint32_t          total_cycle;
	vip_uint32_t          total_idle_cycle;
	vip_uint64_t          start_time;
	vip_uint64_t          end_time;
} gckvip_profiling_data_t;
#endif

typedef struct _gckvip_video_memory {
	void            *handle;
	vip_uint32_t    physical;
	void            *logical;
	vip_uint32_t    size;
} gckvip_video_memory_t;

typedef struct _gckvip_video_memory_ext {
	/* the video memory handle */
	void            *handle;
	/* vip virtual address when mmu is enabled*/
	vip_uint32_t    physical;
	/* the kernel space logical address */
	void            *logical;
	vip_uint32_t    size;
	/* the id of video memory managment by video memory database */
	vip_uint32_t     handle_id;
} gckvip_video_memory_ext_t;

typedef struct _gckvip_tlb_memory {
	/* the video memory handle */
	void            *handle;
	/* vip physical address */
	phy_address_t    physical;
	/* the kernel space logical address */
	void            *logical;
	vip_uint32_t    size;
#if vpmdENABLE_CAPTURE_MMU
	/* the id of video memory managment by video memory database */
	vip_uint32_t     handle_id;
#endif
} gckvip_tlb_memory_t;

typedef struct _gckvip_hardware {
	vip_uint32_t    core_id;
	/* register base memory address */
	volatile void  *reg_base;
	/* interrupt sync object */
	vip_uint32_t   *irq_queue;
	/* interrupt flag */
	volatile vip_uint32_t *volatile irq_flag;

#if vpmdENABLE_MULTIPLE_TASK
	/* mutex for read/write register */
	gckvip_mutex    reg_mutex;
#endif

#if vpmdENABLE_WAIT_LINK_LOOP
	/* wait link buffer. */
	vip_uint32_t   *waitlinkbuf_handle;
	vip_uint32_t   *waitlinkbuf_logical;
	vip_uint32_t    waitlinkbuf_physical;
	vip_uint32_t    waitlinkbuf_size;
	vip_uint32_t   *waitlink_handle;
	vip_uint32_t   *waitlink_logical;
	vip_uint32_t    waitlink_physical;
#endif
#if vpmdENABLE_MMU
	gckvip_video_memory_t MMU_flush;
	gckvip_atomic         flush_mmu;
#endif
#if vpmdENABLE_CLOCK_SUSPEND
	vip_uint8_t     clock_suspend;
#endif
} gckvip_hardware_t;

typedef struct _gckvip_pm {
	gckvip_atomic          status; /* atomic */
	gckvip_recursive_mutex mutex; /* mutex object */
#if vpmdENABLE_SUSPEND_RESUME
	/* A signal for waiting system resume, then submit a new task to hardware */
	gckvip_signal          resume_signal;
	/* A flag for resume signal in waiting status */
	volatile vip_uint8_t   wait_resume_signal;
	gckvip_atomic          force_idle;
#endif
#if vpmdPOWER_OFF_TIMEOUT
	gckvip_timer     timer; /* timer object */
	gckvip_signal    signal; /* signal object */
	void             *thread; /* thread object*/
	gckvip_atomic    thread_running; /* atomic object */

	gckvip_atomic    user_query; /* atomic object */
	gckvip_atomic    enable_timer;
#endif
#if vpmdENABLE_USER_CONTROL_POWER
	gckvip_atomic    user_power_off;
	gckvip_atomic    user_power_stop;
#endif
} gckvip_pm_t;

typedef struct _gckvip_device {
	vip_uint32_t       device_id;

	vip_uint32_t       hardware_count;
	gckvip_hardware_t *hardware;
	gckvip_video_memory_ext_t init_command;
	vip_uint32_t     init_command_size;

	gckvip_atomic    device_idle; /* atomic */
#if vpmdENABLE_CLOCK_SUSPEND
	/* flag device's clock can be suspend or not */
	gckvip_atomic    disable_clock_suspend;
	/* flag the device's clock has suspend or not.
	   true is suspended, false is not suspend */
	gckvip_atomic    clock_suspended;
#endif

#if !vpmdONE_POWER_DOMAIN
	gckvip_pm_t dp_management;
#endif

#if vpmdENABLE_MULTIPLE_VIP && vpmdONE_POWER_DOMAIN && vpmdENABLE_POWER_MANAGEMENT
	gckvip_signal         resume_done;
#endif
#if vpmdENABLE_MULTIPLE_TASK
	gckvip_queue_t  mt_input_queue;
	gckvip_atomic   mt_thread_running;  /* atomic object for multiple task thread is running */
	gckvip_mutex    mt_mutex;           /* mutex for multiple task */
	gckvip_mutex    mt_mutex_expand;    /* mutex for multiple task expand */
	void            *mt_thread_handle;  /* thread object. multiple task thread process handle */
	gckvip_signal   mt_thread_signal;   /* signal for destroy multiple task thread */
	volatile gckvip_multi_thread_submit_t *mt_submit;
	gckvip_hashmap_t                      mt_hashmap;
#endif
	volatile vip_uint32_t execute_count;
#if vpmdENABLE_RECOVERY
	volatile vip_int8_t   recovery_times;
#endif
#if vpmdENABLE_HANG_DUMP
	volatile vip_uint8_t dump_finish;
#endif
#if vpmdENABLE_HANG_DUMP || vpmdENABLE_WAIT_LINK_LOOP
	gckvip_submit_t      curr_command;
#endif
#if vpmdENABLE_APP_PROFILING
	gckvip_profiling_data_t  *profile_data;
	gckvip_hashmap_t          profile_hashmap;
	gckvip_mutex              profile_mutex;
#endif
} gckvip_device_t;

/* Kernel space global context. */
typedef struct _gckvip_context {
	volatile vip_int32_t  initialize;
	volatile vip_uint32_t process_id[SUPPORT_MAX_TASK_NUM];
	/* the real number of vip core */
	vip_uint32_t          core_count;
	/* the logical vip device number */
	vip_uint32_t          device_count;
	gckvip_device_t       *device;

	vip_uint32_t    chip_ver1;
	vip_uint32_t    chip_ver2;
	vip_uint32_t    chip_cid;
	vip_uint32_t    chip_date;

#if vpmdENABLE_VIDEO_MEMORY_HEAP
	/* video memory heap management object */
	gckvip_heap_t   video_mem_heap;
	/* cpu virtual base address in user space */
	void            *heap_user;
	/* cpu virtual base address in kernel space */
	void            *heap_kernel;
	/* vip physical base address */
	phy_address_t   heap_physical;
	/* video memory memory size */
	vip_uint32_t    heap_size;
	/* The virtual base address of VIP when MMU enabled */
	vip_uint32_t    heap_virtual;
#endif
#if vpmdENABLE_SYS_MEMORY_HEAP
	/* the size of system heap memory */
	vip_uint32_t    sys_heap_size;
#endif
#if vpmdENABLE_RESERVE_PHYSICAL
	phy_address_t   reserve_phy_base;
	vip_uint32_t    reserve_phy_size;
	vip_uint32_t    reserve_virtual;
#endif
#if vpmdENABLE_MMU
	gckvip_tlb_memory_t  MTLB;
	gckvip_tlb_memory_t  STLB_1M;
	gckvip_tlb_memory_t  STLB_4K;
	gckvip_tlb_memory_t  MMU_entry;
	/* page table pointer */
	gckvip_tlb_memory_t  *ptr_STLB_1M;
	gckvip_tlb_memory_t  *ptr_STLB_4K;
	gckvip_video_memory_t  *ptr_MMU_flush;
	volatile vip_uint8_t   *bitmap_1M;
	volatile vip_uint8_t   *bitmap_4K;
#if vpmdENABLE_SECURE
	volatile vip_uint8_t   work_mode;
#endif
	gckvip_tlb_memory_t    default_mem;
#endif

#if vpmdONE_POWER_DOMAIN
	gckvip_pm_t     sp_management;
#endif
	gckvip_atomic   init_done; /* did init command or not */
	vip_uint32_t    vip_sram_size;
	/* the physical or VIP's virtual address of VIP SRAM */
	vip_uint32_t    vip_sram_address;
	/* the total size of axi sram */
	vip_uint32_t    axi_sram_size;
	/* the physical or VIP's virtual address of AXI SRAM */
	vip_uint32_t    axi_sram_address;

#if vpmdENABLE_MULTIPLE_TASK
	/* mutex for flush the CPU cache of video memory */
	gckvip_mutex          flush_cache_mutex;
	/* mutex for initialize kernel space driver */
	gckvip_mutex          initialize_mutex;
#if vpmdENABLE_MMU
	/* mutex for mmu page table */
	gckvip_mutex          mmu_mutex;
#endif
#endif
	/* mutex for allocate/free video memory */
	gckvip_mutex          memory_mutex;
	/* maintain video memory heandle pointer(kernel space) and handle id(user space) */
	gckvip_database_t     videomem_database;

#if vpmdENABLE_MMU || vpmdENABLE_CREATE_BUF_FD
	void                 **wrap_handles;
	gckvip_hashmap_t       wrap_hashmap;
#if vpmdENABLE_MULTIPLE_TASK
	gckvip_mutex           wrap_mutex; /* mutex object */
#endif
#endif

	gckvip_atomic            core_fscale_percent;
	gckvip_atomic            last_fscale_percent;
	gckvip_feature_config    func_config;
#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
	gckvip_video_memory_t    register_dump_buffer;
	vip_uint32_t             register_dump_count;
#endif
} gckvip_context_t;


/************ EXPOSED APIs  ***************/
/*
@brief Destroy kernel space resource.
       This function only use on Linux/Andorid system when used ctrl+c
       to exit application or application crash happend.
       When the appliction exits abnormally, gckvip_destroy() used
       to free all kenerl space resource.
*/
vip_status_e gckvip_destroy(void);

/*
@brief  initialize driver
*/
vip_status_e gckvip_init(void);

/*
@brief Get kernel context object.
*/
gckvip_context_t *gckvip_get_context(void);

/*
@brief Get hardware object from core id.
*/
gckvip_hardware_t *gckvip_get_hardware(
	vip_uint32_t core_id
);

/*
@brief  dispatch kernel command
@param  command, command type.
@param  data, the data for command type.
*/
vip_status_e gckvip_kernel_call(
	gckvip_command_id_e command,
	void *data
);

#endif
