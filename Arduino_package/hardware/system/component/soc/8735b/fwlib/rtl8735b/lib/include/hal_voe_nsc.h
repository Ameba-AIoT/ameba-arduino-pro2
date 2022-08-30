/**************************************************************************//**
 * @file     hal_voe.h
 * @brief    The HAL API implementation for the VOE module
 * @version  V1.00
 * @date     2020-11-26
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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
 ******************************************************************************/

#ifndef HAL_VOE_NSC_H
#define HAL_VOE_NSC_H
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_BUILD_SECURE)

void NS_ENTRY hal_voe_set_kmfw_base_addr_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_kmfw_base_addr_nsc(void);

void NS_ENTRY hal_voe_set_kmfw_len_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_kmfw_len_nsc(void);

void NS_ENTRY hal_voe_set_send_msg_ext_ctrl_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_send_msg_ext_ctrl_nsc(void);

void NS_ENTRY hal_voe_set_read_msg_ext_ctrl_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_read_msg_ext_ctrl_nsc(void);

void NS_ENTRY hal_voe_set_int_status_ext_cpu_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_int_status_ext_cpu_nsc(void);

void NS_ENTRY hal_voe_set_wtd_ctrl_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_wtd_ctrl_nsc(void);

void NS_ENTRY hal_voe_set_int_mask_ext_cpu_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_int_mask_ext_cpu_nsc(void);

void NS_ENTRY hal_voe_set_voe_sys_ctrl_nsc(u32 val);

u32 NS_ENTRY hal_voe_get_voe_sys_ctrl_nsc(void);

void NS_ENTRY hal_voe_set_km_initvtor_nsc(void);

int NS_ENTRY hal_voe_check_voe_power_on_nsc(void);

void NS_ENTRY hal_voe_mem_cpy_nsc(void *dest, void *src, size_t len);

int NS_ENTRY hal_voe_get_voe_version(int *addr, int len);

#endif

#if defined(CONFIG_BUILD_NONSECURE)

void hal_voe_set_kmfw_base_addr_nsc(u32 val);

u32 hal_voe_get_kmfw_base_addr_nsc(void);

void hal_voe_set_kmfw_len_nsc(u32 val);

u32 hal_voe_get_kmfw_len_nsc(void);

void hal_voe_set_send_msg_ext_ctrl_nsc(u32 val);

u32 hal_voe_get_send_msg_ext_ctrl_nsc(void);

void hal_voe_set_read_msg_ext_ctrl_nsc(u32 val);

u32 hal_voe_get_read_msg_ext_ctrl_nsc(void);

void hal_voe_set_int_status_ext_cpu_nsc(u32 val);

u32 hal_voe_get_int_status_ext_cpu_nsc(void);

void hal_voe_set_wtd_ctrl_nsc(u32 val);

u32 hal_voe_get_wtd_ctrl_nsc(void);

void hal_voe_set_int_mask_ext_cpu_nsc(u32 val);

u32 hal_voe_get_int_mask_ext_cpu_nsc(void);

void hal_voe_set_voe_sys_ctrl_nsc(u32 val);

u32 hal_voe_get_voe_sys_ctrl_nsc(void);

void hal_voe_set_km_initvtor_nsc(void);

int hal_voe_check_voe_power_on_nsc(void);

void hal_voe_mem_cpy_nsc(void *dest, void *src, size_t len);

int hal_voe_get_voe_version(int *addr, int len);


#define hal_voe_set_kmfw_base_addr          hal_voe_set_kmfw_base_addr_nsc
#define hal_voe_get_kmfw_base_addr          hal_voe_get_kmfw_base_addr_nsc
#define hal_voe_set_kmfw_len                hal_voe_set_kmfw_len_nsc
#define hal_voe_get_kmfw_len                hal_voe_get_kmfw_len_nsc
#define hal_voe_set_send_msg_ext_ctrl       hal_voe_set_send_msg_ext_ctrl_nsc
#define hal_voe_get_send_msg_ext_ctrl       hal_voe_get_send_msg_ext_ctrl_nsc
#define hal_voe_set_read_msg_ext_ctrl       hal_voe_set_read_msg_ext_ctrl_nsc
#define hal_voe_get_read_msg_ext_ctrl       hal_voe_get_read_msg_ext_ctrl_nsc
#define hal_voe_set_int_status_ext_cpu      hal_voe_set_int_status_ext_cpu_nsc
#define hal_voe_get_int_status_ext_cpu      hal_voe_get_int_status_ext_cpu_nsc
#define hal_voe_set_wtd_ctrl                hal_voe_set_wtd_ctrl_nsc
#define hal_voe_get_wtd_ctrl                hal_voe_get_wtd_ctrl_nsc
#define hal_voe_set_int_mask_ext_cpu        hal_voe_set_int_mask_ext_cpu_nsc
#define hal_voe_get_int_mask_ext_cpu        hal_voe_get_int_mask_ext_cpu_nsc
#define hal_voe_set_voe_sys_ctrl            hal_voe_set_voe_sys_ctrl_nsc
#define hal_voe_get_voe_sys_ctrl            hal_voe_get_voe_sys_ctrl_nsc
#define hal_voe_set_km_initvtor             hal_voe_set_km_initvtor_nsc
#define hal_voe_check_voe_power_on          hal_voe_check_voe_power_on_nsc
#define hal_voe_mem_cpy                     hal_voe_mem_cpy_nsc
#define hal_voe_get_voe_version             hal_voe_get_voe_version_nsc

#endif

#ifdef __cplusplus
}
#endif

#endif

