/**************************************************************************//**
 * @file     rtl8735b_rtc.h
 * @brief    The HAL related definition and macros for the RTC device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2016-06-14
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

#ifndef _RTL8735B_RTC_H_
#define _RTL8735B_RTC_H_

#include "rtl8735b_rtc_type.h"
#include "rtl8735b_vndr_type.h"


#ifdef  __cplusplus
extern "C"
{
#endif





/**
 * @addtogroup ls_hal_rtc RTC
 * @{
 */

/**
  * \brief The RTC register parameter
**/

enum  rtc_reg_sel_e {
	Rtc_Fen       = 0x00,   //!< REG_RTC_FEN
	Rtc_Cmp       = 0x08,   //!< REG_RTC_CMP
	Rtc_Imr       = 0x10,   //!< REG_RTC_IMR
	Rtc_Isr       = 0x14,   //!< REG_RTC_ISR
	Rtc_Tim0      = 0x20,   //!< REG_RTC_TIM0
	Rtc_Tim1      = 0x24,   //!< REG_RTC_TIM1
	Rtc_Tim2      = 0x28,   //!< REG_RTC_TIM2
	Rtc_Ctrl0     = 0x30,   //!< REG_RTC_ALRM_CTRL0
	Rtc_Ctrl1     = 0x34,   //!< REG_RTC_ALRM_CTRL1
	Rtc_Ctrl2     = 0x38    //!< REG_RTC_ALRM_CTRL2

};
typedef uint8_t rtc_reg_sel_t;

/**
  * \brief The RTC wake-up register parameter
**/

enum  rtc_wake_event_e {
	RTC_Wake     = 0x04,            //!< 1: enable RTC wake, BIT2
	RTC_Rst      = (0x20000UL),     //!< 1: enable RTC RST, BIT17
	AON_Wakeup   = (0x20000000UL)   //!< 1: enable AON Wakeup event, BIT29

};
typedef uint32_t rtc_wake_event_t;

/*! define RTC interrupt call back function */
typedef void (*rtc_alarm_callback_t)(void *);

/**
  * \brief The tm structure with the time information filled in.
**/

typedef struct hal_tm_reg_s {
	int sec;         //!< seconds,  range 0 to 59
	int min;         //!< minutes, range 0 to 59
	int hour;        //!< hours, range 0 to 23
	int mday;        //!< day of the month, range 1 to 31
	int mon;         //!< month, range 0 to 11
	int year;        //!< The number of years since 1900
	int wday;        //!< day of the week, range 0 to 6
	int yday;        //!< day in the year, range 0 to 365
	int isdst;       //!< daylight saving time
} hal_tm_reg_t, *phal_tm_reg_t;

/**
  * \brief The RTC alarm structure
**/

typedef struct hal_rtc_alarm_s {
	uint32_t yday;   //!< day in the year, range 1 to 366
	uint32_t hour;   //!< hours, range 0 to 23
	uint32_t min;    //!< minutes, range 0 to 59
	uint32_t sec;    //!< seconds,  range 0 to 59
} hal_rtc_alarm_t, *phal_rtc_alarm_t;


/**
  \brief  The data structure of the RTC adapter
*/
typedef struct hal_rtc_adapter_s {
	RTC_Type *base_addr;    //!< The RTC registers base address
	RTC_TYPE_TypeDef rtc_reg;  //!< The data structure to control the RTC register.
	rtc_alarm_callback_t  alarm_callback;      //!< User callback function for RTC Alarm
	void *rtc_cb_para;   //!< the argument for RTC callback function
} hal_rtc_adapter_t, *phal_rtc_adapter_t;


/**
  \brief  The data structure of the stubs function for the RTC HAL functions in ROM
*/
typedef struct hal_rtc_func_stubs_s {
	phal_rtc_adapter_t *prtc_adp;
	void (*hal_rtc_irq_handler)(void);
	void (*hal_rtc_comm_irq_reg)(irq_handler_t irq_handler);
	void (*hal_rtc_comm_irq_unreg)(void);
	hal_status_t (*hal_rtc_init)(hal_rtc_adapter_t *prtc_adp);
	hal_status_t (*hal_rtc_deinit)(hal_rtc_adapter_t *prtc_adp);
	void (*hal_rtc_enable)(hal_rtc_adapter_t *prtc_adp);
	void (*hal_rtc_disable)(hal_rtc_adapter_t *prtc_adp);
	void (*hal_rtc_wait_ctrl_ready)(hal_rtc_adapter_t *prtc_adp);
	void (*hal_rtc_write)(hal_rtc_adapter_t *prtc_adp, u16 addr, u32 data);
	u32(*hal_rtc_read)(hal_rtc_adapter_t *prtc_adp, u16 addr);
	hal_status_t (*hal_rtc_set_time)(hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
	u32(*hal_rtc_read_time)(hal_rtc_adapter_t *prtc_adp);
	hal_status_t (*hal_rtc_set_alarm)(hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
	u32(*hal_rtc_read_alarm)(hal_rtc_adapter_t *prtc_adp);
	void (*hal_rtc_reg_alarm_irq)(hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
	void (*hal_rtc_unreg_alarm_irq)(hal_rtc_adapter_t *prtc_adp);
	hal_status_t (*hal_rtc_set_cnt_alarm)(hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
	hal_status_t (*hal_rtc_set_comp)(hal_rtc_adapter_t *prtc_adp, u8 func_en);
	uint32_t reserved[5];  // reserved space for next ROM code version function table extending.
} hal_rtc_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_rtc_rom_func RTC HAL ROM APIs.
 * @{
 */

void hal_rtl_rtc_comm_irq_reg(irq_handler_t irq_handler);
void hal_rtl_rtc_comm_irq_unreg(void);
hal_status_t hal_rtl_rtc_init(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtl_rtc_deinit(hal_rtc_adapter_t *prtc_adp);
void hal_rtl_rtc_enable(hal_rtc_adapter_t *prtc_adp);
void hal_rtl_rtc_disable(hal_rtc_adapter_t *prtc_adp);
//int hal_rtc_isenable_rtl8735b (hal_rtc_adapter_t *prtc_adp);
void hal_rtl_rtc_wait_ctrl_ready(hal_rtc_adapter_t *prtc_adp);
void hal_rtl_rtc_write(hal_rtc_adapter_t *prtc_adp, u16 addr, u32 data);
u32 hal_rtl_rtc_read(hal_rtc_adapter_t *prtc_adp, u16 addr);
hal_status_t hal_rtl_rtc_set_time(hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
u32 hal_rtl_rtc_read_time(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtl_rtc_set_alarm(hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
u32 hal_rtl_rtc_read_alarm(hal_rtc_adapter_t *prtc_adp);
void hal_rtl_rtc_reg_alarm_irq(hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
void hal_rtl_rtc_unreg_alarm_irq(hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtl_rtc_set_cnt_alarm(hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
hal_status_t hal_rtl_rtc_set_comp(hal_rtc_adapter_t *prtc_adp, u8 func_en);

/** @} */ /* End of group ls_hal_rtc_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_rtc */

#endif  // end of "#define _RTL8195BLP_RTC_H_"
