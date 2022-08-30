/**************************************************************************//**
 * @file     hal_rtc_nsc.h
 * @brief    The header file of hal_rtc_ns.c.
 * @version  1.00
 * @date     2021-2-4
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
#ifndef _HAL_RTC_NSC_H_
#define _HAL_RTC_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_BUILD_SECURE)
hal_status_t NS_ENTRY hal_rtc_init_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t NS_ENTRY hal_rtc_deinit_nsc(hal_rtc_adapter_t *prtc_adp);
void  NS_ENTRY hal_rtc_enable_nsc(hal_rtc_adapter_t *prtc_adp);
void NS_ENTRY hal_rtc_disable_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t NS_ENTRY hal_rtc_set_time_nsc(hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
u32 NS_ENTRY hal_rtc_read_nsc(hal_rtc_adapter_t *prtc_adp, u16 addr);
u32 NS_ENTRY hal_rtc_read_time_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t NS_ENTRY hal_rtc_set_alarm_nsc(hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
u32 NS_ENTRY hal_rtc_read_alarm_nsc(hal_rtc_adapter_t *prtc_adp);
void NS_ENTRY hal_rtc_reg_alarm_irq_nsc(hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
void NS_ENTRY hal_rtc_unreg_alarm_irq_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t NS_ENTRY hal_rtc_set_cnt_alarm_nsc(hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
hal_status_t NS_ENTRY hal_rtc_set_comp_nsc(hal_rtc_adapter_t *prtc_adp, u8 func_en);
void NS_ENTRY hal_rtc_set_leap_year_nsc(hal_rtc_adapter_t *prtc_adp);
#endif

#if defined(CONFIG_BUILD_NONSECURE)
hal_status_t hal_rtc_init_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t  hal_rtc_deinit_nsc(hal_rtc_adapter_t *prtc_adp);
void hal_rtc_enable_nsc(hal_rtc_adapter_t *prtc_adp);
void hal_rtc_disable_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_set_time_nsc(hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
u32 hal_rtc_read_nsc(hal_rtc_adapter_t *prtc_adp, u16 addr);
u32 hal_rtc_read_time_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_set_alarm_nsc(hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
u32 hal_rtc_read_alarm_nsc(hal_rtc_adapter_t *prtc_adp);
void NS_ENTRY hal_rtc_reg_alarm_irq_nsc(hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
void NS_ENTRY hal_rtc_unreg_alarm_irq_nsc(hal_rtc_adapter_t *prtc_adp);
hal_status_t NS_ENTRY hal_rtc_set_cnt_alarm_nsc(hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
hal_status_t NS_ENTRY hal_rtc_set_comp_nsc(hal_rtc_adapter_t *prtc_adp, u8 func_en);
void NS_ENTRY hal_rtc_set_leap_year_nsc(hal_rtc_adapter_t *prtc_adp);

#define hal_rtc_init                hal_rtc_init_nsc
#define hal_rtc_deinit              hal_rtc_deinit_nsc
#define hal_rtc_enable              hal_rtc_enable_nsc
#define hal_rtc_disable             hal_rtc_disable_nsc
#define hal_rtc_set_time            hal_rtc_set_time_nsc
#define hal_rtc_read                hal_rtc_read_nsc
#define hal_rtc_read_time           hal_rtc_read_time_nsc
#define hal_rtc_set_alarm           hal_rtc_set_alarm_nsc
#define hal_rtc_read_alarm          hal_rtc_read_alarm_nsc
#define hal_rtc_reg_alarm_irq       hal_rtc_reg_alarm_irq_nsc
#define hal_rtc_unreg_alarm_irq     hal_rtc_unreg_alarm_irq_nsc
#define hal_rtc_set_cnt_alarm       hal_rtc_set_cnt_alarm_nsc
#define hal_rtc_set_comp            hal_rtc_set_comp_nsc
#define hal_rtc_set_leap_year       hal_rtc_set_leap_year_nsc
#endif

/** @} */ /* End of group rtc_nsc */

#ifdef  __cplusplus
}
#endif

#endif  // #ifndef _HAL_RTC_NSC_H_



