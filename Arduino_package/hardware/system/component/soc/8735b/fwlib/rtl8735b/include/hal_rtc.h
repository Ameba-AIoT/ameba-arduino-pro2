/**************************************************************************//**
 * @file     hal_rtc.h
 * @brief    The HAL API implementation for the RTC device.
 * @version  V1.00
 * @date     2016-07-15
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

#ifndef _HAL_RTC_H_
#define _HAL_RTC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_rtc RTC
 * @ingroup rtl8735b
 * @{
 * @brief The RTC HAL module of the LS platform.
 */

/**
  * @brief The stubs functions table to exports RTC HAL functions in ROM.
  */

extern const hal_rtc_func_stubs_t hal_rtc_stubs;

void hal_rtc_irq_handler(void);
void hal_rtc_comm_irq_reg(irq_handler_t irq_handler);
void hal_rtc_comm_irq_unreg(void);
hal_status_t hal_rtc_init(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_deinit(hal_rtc_adapter_t *prtc_adp);
void hal_rtc_enable(hal_rtc_adapter_t *prtc_adp);
void hal_rtc_disable(hal_rtc_adapter_t *prtc_adp);
//int hal_rtc_isenable (hal_rtc_adapter_t *prtc_adp);
void hal_rtc_wait_ctrl_ready(hal_rtc_adapter_t *prtc_adp);
void hal_rtc_write(hal_rtc_adapter_t *prtc_adp, u16 addr, u32 data);
u32 hal_rtc_read(hal_rtc_adapter_t *prtc_adp, u16 addr);
hal_status_t hal_rtc_set_time(hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
u32 hal_rtc_read_time(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_set_alarm(hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
u32 hal_rtc_read_alarm(hal_rtc_adapter_t *prtc_adp);
void hal_rtc_reg_alarm_irq(hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
void hal_rtc_unreg_alarm_irq(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_set_cnt_alarm(hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
hal_status_t hal_rtc_set_comp(hal_rtc_adapter_t *prtc_adp, u8 func_en);
void hal_rtc_set_leap_year(hal_rtc_adapter_t *prtc_adp);

/** @} */ /* End of group ls_hal_rtc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_RTC_H_"
