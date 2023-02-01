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

#ifndef _GC_VIP_KERNEL_DEBUG_H
#define _GC_VIP_KERNEL_DEBUG_H

#include <gc_vip_common.h>
#include <vip_lite.h>
#include <gc_vip_kernel.h>

#if vpmdENABLE_HANG_DUMP
vip_status_e gckvip_dump_data(
	vip_uint32_t *data,
	vip_uint32_t physical,
	vip_uint32_t size
);

vip_status_e gckvip_dump_states(
	gckvip_context_t *context,
	gckvip_device_t *device,
	gckvip_hardware_t *hardware
);

vip_status_e gckvip_dump_command(
	gckvip_submit_t *submit,
	gckvip_hardware_t *hardware
);

vip_status_e gckvip_hang_dump(
	gckvip_device_t *device
);

vip_status_e gckvip_dump_waitlink(
	vip_uint32_t *data,
	vip_uint32_t physical
);

#if vpmdENABLE_CAPTURE_MMU
vip_status_e gckvip_dump_MMU_mapping(void);
#endif
#endif

#if vpmdENABLE_APP_PROFILING
void gckvip_start_profiling(
	gckvip_submit_t *submit,
	gckvip_device_t *device
);

vip_status_e gckvip_end_profiling(
	gckvip_context_t *context,
	gckvip_device_t *device,
	void *cmd_handle
);

void gckvip_remove_profiling(
	void *cmd_handle
);

vip_status_e gckvip_query_profiling(
	gckvip_context_t *context,
	gckvip_device_t *device,
	void *mem_handle,
	gckvip_query_profiling_t *profiling
);
#endif

#if (vpmdENABLE_DEBUG_LOG > 3) || vpmdENABLE_DEBUGFS
void gckvip_report_clock(void);

vip_status_e gckvip_dump_options(void);

vip_status_e gckvip_get_clock(
	gckvip_hardware_t *hardware,
	vip_uint64_t *clk_MC,
	vip_uint64_t *clk_SH
);
#endif

vip_status_e gckvip_check_irq_value(
	gckvip_context_t *context,
	gckvip_device_t *device
);

vip_status_e gckvip_register_dump_wrapper(
	vip_status_e(*func)(gckvip_hardware_t *hardware, ...),
	...
);

#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
vip_status_e gckvip_register_dump_init(
	gckvip_context_t *context
);

vip_status_e gckvip_register_dump_uninit(
	gckvip_context_t *context
);

vip_status_e gckvip_register_dump_action(
	gckvip_register_dump_type_e type,
	vip_uint32_t core_id,
	vip_uint32_t address,
	vip_uint32_t expect,
	vip_uint32_t data
);
#endif
#endif
