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
#ifndef _GC_VIP_KERNEL_COMMAND_H
#define _GC_VIP_KERNEL_COMMAND_H

#include <gc_vip_kernel.h>

/*
@brief To run any initial commands once in the beginning.
*/
vip_status_e gckvip_cmd_submit_init(
	gckvip_context_t *context,
	gckvip_device_t *device
);

/*
@brief To run any initial commands once in the beginning.
*/
vip_status_e gckvip_cmd_prepare_init(
	gckvip_context_t *context,
	gckvip_device_t *device
);

/*
@brief commit commands to hardware.
*/
vip_status_e gckvip_cmd_submit(
	gckvip_context_t *context,
	void *data
);

/*
@brief wait hardware interrupt return.
*/
vip_status_e gckvip_cmd_wait(
	gckvip_context_t *context,
	gckvip_wait_cmd_t *info,
	gckvip_device_t *device
);

#if vpmdENABLE_MULTIPLE_TASK
vip_status_e gckvip_cmd_thread_handle(
	gckvip_context_t *context,
	gckvip_queue_t *queue
);
#endif

vip_status_e gckvip_cmd_do_submit(
	gckvip_context_t *context,
	gckvip_commit_t *commit
);

vip_status_e gckvip_cmd_do_wait(
	gckvip_context_t *context,
	gckvip_wait_t *info
);

#if vpmdENABLE_CANCELATION
vip_status_e gckvip_cmd_do_cancel(
	gckvip_context_t *context,
	gckvip_cancel_t *info
);
#endif

#endif
