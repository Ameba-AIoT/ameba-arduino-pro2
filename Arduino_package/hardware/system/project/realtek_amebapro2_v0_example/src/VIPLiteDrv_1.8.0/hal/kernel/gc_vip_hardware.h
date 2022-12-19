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

#ifndef _GC_VIP_HARDWARE_H
#define _GC_VIP_HARDWARE_H

#include <gc_vip_kernel.h>


#define SETBIT(value, bit, data) \
    (((value) & (~(1 << (bit)))) | ((data) << (bit)))

/*
@ brief
    Initializae HW.
*/
vip_status_e gckvip_hw_init(
	gckvip_context_t *context,
	gckvip_device_t *device
);

/*
@ brief
    Destroy and free HW resource.
*/
vip_status_e gckvip_hw_destroy(
	gckvip_context_t *context
);


/*
@ brief
    Do a software HW reset.
*/
vip_status_e gckvip_hw_reset(
	gckvip_context_t *context,
	gckvip_device_t *device
);

#if vpmdENABLE_WAIT_LINK_LOOP
/*
@ brief
    Trigger hardware, NPU start to run.
*/
vip_status_e gckvip_hw_trigger(
	gckvip_context_t *context,
	gckvip_hardware_t *hardware
);
#endif

/*
@ brief
    Submit command buffer to hardware.
*/
vip_status_e gckvip_hw_submit(
	gckvip_context_t *context,
	gckvip_device_t *device,
	gckvip_submit_t  *submit
);

/*
@ brief
    hardware go back to WL.
*/
vip_status_e gckvip_hw_idle(
	gckvip_context_t *context,
	gckvip_device_t *device
);

vip_status_e gckvip_hw_read_info(
	gckvip_context_t *context
);

/*
@brief  read a hardware register.
@param  address, the address of hardware register.
@param  data, read data from register.
*/
vip_status_e gckvip_read_register(
	gckvip_hardware_t *hardware,
	vip_uint32_t address,
	vip_uint32_t *data
);

/*
@brief  write a hardware register.
@param  address, the address of hardware register.
@param  data, write data to register.
*/
vip_status_e gckvip_write_register(
	gckvip_hardware_t *hardware,
	vip_uint32_t address,
	vip_uint32_t data
);

/*
@brief  write a hardware register.
@param  address, the address of hardware register.
@param  data, write data to register.
*/
vip_status_e gckvip_write_register_ext(
	gckvip_hardware_t *hardware,
	vip_uint32_t address,
	vip_uint32_t data
);

/*
@brief query hardware is idle.
*/
vip_bool_e gckvip_hw_query_idle(
	gckvip_hardware_t *hardware
);

#if vpmdENABLE_POLLING
/*
@brief poll to waiting hardware going to idle.
@param timeout the number of milliseconds this waiting.
*/
vip_status_e gckvip_hw_wait_poll(
	gckvip_hardware_t *hardware,
	gckvip_device_t   *device,
	vip_uint32_t timeout
);
#endif

/*
@brief waiting for hardware going to idle.
@param context, the contect of kernel space.
@param timeout the number of milliseconds this waiting.
@param is_fast true indicate that need udelay for poll hardware idle or not.
*/
vip_status_e gckvip_hw_wait_idle(
	gckvip_context_t *context,
	gckvip_hardware_t *hardware,
	vip_uint32_t timeout,
	vip_uint8_t is_fast
);

/*
@brief recover hardware when hang occur.
@param context, the contect of kernel space.
@param device, recover device.
*/
#if vpmdENABLE_RECOVERY
vip_status_e gckvip_hw_recover(
	gckvip_context_t *context,
	gckvip_device_t *device
);
#endif
#endif
