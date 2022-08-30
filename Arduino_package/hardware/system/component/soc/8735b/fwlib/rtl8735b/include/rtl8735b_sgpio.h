/**************************************************************************//**
 * @file     rtl8195bh_sgpio.h
 * @brief    The HAL related definition and macros for the SGPIO device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2016-07-20
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

#ifndef _RTL8195BHP_SGPIO_H_
#define _RTL8195BHP_SGPIO_H_

/**
 * @addtogroup hs_hal_sgpio SGPIO
 * @{
 */

#include "basic_types.h"
#include "rtl8735b_sgpio_type.h"


#define REG_PERI_MULFDATA   0x074

#define SGPIO_HP_SCLK_NS    12.5f // ASIC: 12.5f, FPGA: 50.0f

/**
  \brief  Define the SGPIO port ID.
*/
enum  sgpio_index_sel_e {
	Sgpio0_Sel    =   0x0,
	Sgpio1_Sel    =   0x1,
	Sgpio2_Sel    =   0x2,
	Sgpio_Max_Id  =   0x3
};
typedef uint8_t sgpio_index_sel_t;

/**
  \brief Define the input methold to start rx timer counter.
*/
enum  sgpio_rxtc_input_start_e {
	Rxtc_None           = 0,
	Rxtc_InputRiseEg    = 1,
	Rxtc_InputFallEg    = 2,
	Rxtc_InputBothEg    = 3
};
typedef uint8_t sgpio_rxtc_input_start_t;

/**
  \brief Define the rxtc match event ID.
*/
enum  sgpio_rxtc_match_event_e {
	Rxtc_MatchEvent0   = 0,
	Rxtc_MatchEvent1   = 1,
	Rxtc_MatchEvent2   = 2,
};
typedef uint8_t sgpio_rxtc_match_event_t;

/**
  \brief Define the methold to work the capture.
*/
enum  sgpio_capture_type_e {
	Cap_None                = 0,
	Cap_InputRiseEg         = 1,
	Cap_InputFallEg         = 2,
	Cap_InputBothEg         = 3,
	Cap_MultcMatchEvent0    = 4
};
typedef uint8_t sgpio_capture_type_t;

/**
  \brief Define multc is timer or counter mode
*/
enum  sgpio_multc_mode_e {
	Multc_Timer_Mode            = 0,
	Multc_Counter_InputRiseEg   = 1,
	Multc_Counter_InputFallEg   = 2,
	Multc_Counter_InputBothEg   = 3
};
typedef uint8_t sgpio_multc_mode_t;

/**
  \brief Define the input methold to count.
*/
enum  sgpio_counter_edge_e {
	Input_None       = 0,
	Input_RiseEdge   = 1,
	Input_FallEdge   = 2,
	Input_BothEdge   = 3
};
typedef uint8_t sgpio_counter_edge_t;


/**
  \brief Define the multc match event ID.
*/
enum  sgpio_multc_match_event_e {
	Multc_MatchEvent0   = 0,
	Multc_MatchEvent1   = 1,
	Multc_MatchEvent2   = 2,
	Multc_MatchEvent3   = 3
};
typedef uint8_t sgpio_multc_match_event_t;

/**
  \brief Define the multc group ID.
*/
enum  sgpio_multc_match_group_e {
	Multc_MatchGroup0   = 0,
	Multc_MatchGroup1   = 1
};
typedef uint8_t sgpio_multc_match_group_t;

/**
  \brief Define the output state when happen the match event.
*/
enum  sgpio_external_output_e {
	External_None   = 0,
	External_Low    = 1,
	External_High   = 2,
	External_Toggle = 3
};
typedef uint8_t sgpio_external_output_t;

/**
  \brief Define the rx is only input or in-out.
*/
enum  sgpio_rx_inoutput_e {
	Rx_Input_Only   = 0,
	Rx_In_And_Output = 1
};
typedef uint8_t sgpio_rx_inoutput_t;

/**
  \brief Define the output is low or high.
*/
enum  sgpio_output_value_e {
	Output_Is_Low   = 0,
	Output_Is_High  = 1
};
typedef uint8_t sgpio_output_value_t;

/**
  \brief Define the data is MSB or LSB.
*/
enum  sgpio_first_msb_or_lsb_e {
	First_Data_LSB = 0,
	First_Data_MSB = 1
};
typedef uint8_t sgpio_first_msb_or_lsb_t;

/**
  \brief Define the compare result is 0 or 1 when the capture value is bigger than the compare value.
*/
enum  sgpio_cmp_result_bit_e {
	Compare_Result_Bit0 = 0,
	Compare_Result_Bit1 = 1
};
typedef uint8_t sgpio_cmp_result_bit_t;

/**
  \brief Define the time unit.
*/
enum  sgpio_time_unit_e {
	Time_unit_us = 0,
	Time_unit_ns = 1
};
typedef uint8_t sgpio_time_unit_t;

/**
  \brief Define the time source and unit.
*/
enum  sgpio_unit_e {
	Timer_mode_unit_us = 0,
	Timer_mode_unit_ns = 1,
	Countr_mode_unit_cnt = 2
};
typedef uint8_t sgpio_source_unit_t;

/**
  \brief Define sgpio irq bit shift.
*/
enum  sgpio_irq_shift_e {
	Rx_Mr0_Sft          = 0,
	Rx_Mr1_Sft          = 1,
	Rx_Mr2_Sft          = 2,
	Mul_Mr0_Sft         = 3,
	Cap_Sft             = 4,
	Rxsft_Sft           = 5,
	Mulsft_Sft          = 6,
	Rxload_Sft          = 7,
	Mulload_Sft         = 8,
	Pattern_Match_Sft   = 9,
	Mulmcnt_Sft         = 10,
	Mul_Dma_Unfl_Sft    = 11,
	Max_Sgpio_Sft       = 12
};
typedef uint8_t sgpio_irq_shift_t;

/**
  \brief  SGPIO call back function for the interrupt event.
*/
typedef void (*sgpio_irq_user_cb_t)(void *);

/**
  \brief Define the rx timer counter event.
*/
typedef struct hal_sgpio_rxtc_event_s {
	u32 rxtc_match_event0   : 1;        /*!< This event is that the rx timer value matches rx match register 0. */
	u32 rxtc_match_event1   : 1;        /*!< This event is that the rx timer value matches rx match register 1. */
	u32 rxtc_match_event2   : 1;        /*!< This event is that the rx timer value matches rx match register 2. */
	u32 multc_match_event0  : 1;        /*!< This event is that the multc timer value matches Multiple Match Register 0. */
	u32 rx_postc_zero       : 1;        /*!< This event is that the rxpostc register becomes 0. */
	u32 capture_event       : 1;        /*!< This event is that happen the capture.  */
} hal_sgpio_rxtc_event_t, *phal_sgpio_event_t;

/**
  \brief Define the multi timer counter event.
*/
typedef struct hal_sgpio_multc_event_s {
	u32 multc_match_event0  : 1;        /*!< This event is that the multc timer value matches multiple match register 0. */
	u32 rxtc_match_event0   : 1;        /*!< This event is that the rx timer value matches rx match register 0. */
	u32 multc_mcnt_zero     : 1;        /*!< This event is that the mul_mcnt register becomes 0. */
} hal_sgpio_multc_event_t, *phal_sgpio_multc_event_t;

/**
  \brief Define the rx sampling event.
*/
typedef struct hal_sgpio_sampling_event_s {
	u32 rxtc_match_event0  : 1;     /*!< This event is that the rx timer value matches rx match register 0. */
	u32 rxtc_match_event1  : 1;     /*!< This event is that the rx timer value matches rx match register 1. */
	u32 rxtc_match_event2  : 1;     /*!< This event is that the rx timer value matches rx match register 2. */
} hal_sgpio_sampling_event_t, *phal_sgpio_sampling_event_t;

/**
  \brief Define the data structure for the multc FIFO mode.
*/
typedef struct hal_sgpio_fifo_value_s {
	u16 multc_match_event0_val;     /*!< The multc match register 0. */
	u16 multc_match_event1_val;     /*!< The multc match register 1. */
	u16 multc_match_event2_val;     /*!< The multc match register 2. */
	u16 multc_match_event3_val;     /*!< The multc match register 3. */
} hal_sgpio_fifo_value_t, *phal_sgpio_fifo_value_t;

/**
  \brief The parameter structure for initializing the interrupt event.
*/
typedef struct hal_sgpio_set_irq_s {
	BOOL int_en;                    /*!< 0: disbale this event interrupt, 1: enable. */
	BOOL imr_en;                    /*!< 0: disbale mask event interrupt, 1: enable.  */
	BOOL callback_reg_en;           /*!< 0: don't register this callback function, 1: register this callback function. */
	sgpio_irq_user_cb_t callback;   /*!< The callback function. */
	void *arg;                      /*!< The callback argument. */
} hal_sgpio_set_irq_t, *phal_sgpio_set_irq_t;

/**
  \brief Record the rx processing information.
*/
typedef struct hal_sgpio_rx_info_s {
	sgpio_first_msb_or_lsb_t first_data_flag; /*!< Record to use MSB or LSB. */
	u8 rx_bit_length_copy;                    /*!< Record the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing. */
} hal_sgpio_rx_info_t, *phal_sgpio_rx_info_t;

/**
  \brief Record the tx processing information.
*/
typedef struct hal_sgpio_tx_info_s {
	u32 *ptxdata_pointer_copy;      /*!< The txdata pointer. */
	u16 bit_length_copy;            /*!< The output bit number.  */
	u16 output_bit_counts_copy;     /*!< Copy the output bit number.  */
	u16 bit_counts_quot_irq_source; /*!< Record the processing information.  */
	u16 bit_counts_quot_irq;        /*!< Record the processing information.  */
	u32 *ptxdata_pointer_irq;       /*!< Record the processing information.  */
} hal_sgpio_tx_info_t, *phal_sgpio_tx_info_t;

/**
  \brief Record the dma processing information.
*/
typedef struct hal_sgpio_dma_info_s {
	u8  match_reset_counter_copy;           /*!< Record the processing information.  */
	sgpio_irq_user_cb_t irq_user_dma_cb;    /*!< The dma callback function. */
	void *user_dma_arg;                     /*!< The dma callback argument. */
} hal_sgpio_dma_info_t, *phal_sgpio_dma_info_t;

typedef struct hal_sgpio_adapter_s {
	sgpio_index_sel_t sgpio_index;              /*!< The SGPIO port ID. */
	SGPIO_Type *base_addr;                     /*!< The SGPIO common register base address */
	float sgpio_sclk_ns;                        /*!< Record SGPIO sclk */
	u16 *pmemory_addr;                          /*!< Record the tx memory address */
	hal_sgpio_rx_info_t sgpio_rx_info;          /*!< Record the rx processing information.   */
	hal_sgpio_tx_info_t sgpio_tx_info;          /*!< Record the tx processing information.   */
	hal_sgpio_dma_info_t sgpio_dma_info;        /*!< Record the dma processing information.   */
	hal_gdma_adaptor_t *phal_gdma_adaptor;      /*!< The GDMA adapter. */
	sgpio_irq_user_cb_t irq_user_cb[12];        /*!< The SGPIO call back function for the interrupt event */
	void *user_arg[12];                         /*!< The argument of call back function */

	u8 dcache_memory_en;                        /*!< Check the memory is cache or not  */

	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);    /*!< Callback function to do the D-cache clean  */
} hal_sgpio_adapter_t, *phal_sgpio_adapter_t;

/**
  \brief  The data structure to handle multiple SGPIO adapters.
*/
typedef struct hal_sgpio_group_adapter_s {
	volatile uint32_t critical_lv;                      /*!< to record SGPIO HAL enter critical section level */
	hal_sgpio_adapter_t *psgpio_adapter[Sgpio_Max_Id];  /*!< All the SGPIO adapters of this platform */
	irq_handler_t   irq_fun[Sgpio_Max_Id];              /*!< the IRQ handler for different SGPIO adapters */
} hal_sgpio_group_adapter_t, *phal_sgpio_group_adapter_t;

//====== Normal Function Parameter======

/**
  \brief  The parameter structure of the rxtc timer mode.
*/
typedef struct hal_sgpio_rxtc_timer_mode_s {
	BOOL timer_once_en;                     /*!< Enable that matching event is executed once. */
	sgpio_time_unit_t time_unit;            /*!< Select the time unit. */
	u32 match_value1_time;                  /*!< Matching this time 1 generates the interrupt. */
	sgpio_irq_user_cb_t match_value1_cb;    /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pmatch_value1_arg;                /*!< User defined IRQ callback parameter.  */
	u32 match_value2_time;                  /*!< Matching this time 2 generates the interrupt. */
	sgpio_irq_user_cb_t match_value2_cb;    /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pmatch_value2_arg;                /*!< User defined IRQ callback parameter.  */
	u32 match_reset_value_time;             /*!< This match time is able to make the timer reset and stop. */
	sgpio_irq_user_cb_t reset_value_cb;     /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *preset_value_arg;                 /*!< User defined IRQ callback parameter. */
} hal_sgpio_rxtc_timer_mode_t, *phal_sgpio_rxtc_timer_mode_t;

/**
  \brief  The parameter structure of the multc timer mode.
*/
typedef struct hal_sgpio_multc_timer_mode_s {
	BOOL timer_once_en;                     /*!< Enable that matching event is executed once. */
	sgpio_time_unit_t time_unit;            /*!< Select the time unit. */
	u32 match_reset_value_time;             /*!< This match time is able to make the timer reset and stop. */
	sgpio_irq_user_cb_t reset_value_cb;     /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *preset_value_arg;                 /*!< User defined IRQ callback parameter. */
} hal_sgpio_multc_timer_mode_t, *phal_sgpio_multc_timer_mode_t;

/**
  \brief  The parameter structure of the multc counter mode.
*/
typedef struct hal_sgpio_multc_counter_mode_s {
	BOOL counter_en;                        /*!< To enable or disable. */
	sgpio_counter_edge_t input_edge;        /*!< Select the edge of the trigger event. */
	u16 match_counter_value;                /*!< When the counter value is equal to match_value, generate an interrupt. */
	BOOL match_counter_reset_en;            /*!< When the counter value is equal to match_value, reset the counter. */
	BOOL match_counter_disable_en;          /*!< When the counter value is equal to match_value, make counter_en become disable(0).  */
	sgpio_time_unit_t time_unit;            /*!< Select the time unit. */
	u32 counter_reset_timeout_value;        /*!< Set the monitor period. */
	sgpio_irq_user_cb_t match_counter_cb;   /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pmatch_counter_arg;               /*!< User defined IRQ callback parameter. */
} hal_sgpio_multc_counter_mode_t, *phal_sgpio_multc_counter_mode_t;

/**
  \brief  The parameter structure of the rxtc external output.
*/
typedef struct hal_sgpio_rxtc_timer_match_output_s {
	sgpio_external_output_t match_value1_output;        /*!< Set the output value when match the time 1. */
	sgpio_external_output_t match_value2_output;        /*!< Set the output value when match the time 2. */
	sgpio_external_output_t match_reset_value_output;   /*!< Set the output value when match the reset time. */
} hal_sgpio_rxtc_timer_match_output_t, *phal_sgpio_rxtc_timer_match_output_t;

/**
  \brief  The parameter structure of the multc external output.
*/
typedef struct hal_sgpio_multc_timer_counter_match_output_s {
	sgpio_source_unit_t source_unit;                /*!< Select the time unit.   */
	sgpio_external_output_t match_value1_output;    /*!< Set the output value when happen the multc match event 1.  */
	u32 match_value1;                               /*!< The match value 1 of the multc timer counter.  */
	sgpio_external_output_t match_value2_output;    /*!< Set the output value when happen the multc match event 2.  */
	u32 match_value2;                               /*!< The match value 2 of the multc timer counter.  */
	sgpio_external_output_t match_value3_output;    /*!< Set the output value when happen the multc match event 3.  */
	u32 match_value3;                               /*!< The match value 3 of the multc timer counter.  */
} hal_sgpio_multc_timer_counter_match_output_t, *phal_sgpio_multc_timer_counter_match_output_t;

/**
  \brief  The parameter structure of the rxtc capture mode.
*/
typedef struct hal_sgpio_rxtc_capture_mode_s {
	BOOL capture_en;                            /*!< To enable or disable. */
	sgpio_rxtc_input_start_t start_timer_edge;  /*!< Select the trigger edge for starting the rxtc timer. */
	sgpio_capture_type_t input_capture_edge;    /*!< Select the capture edge for capturing the time. */
	BOOL capture_timer_reset_en;                /*!< When happen the capture event, reset the rxtc timer. */
	BOOL capture_timer_disable_en;              /*!< When happen the capture event, stop the rxtc timer. */
	u32 max_capture_range_us;                   /*!< Set the maximum possible measurement value for making the prescale of the timer automatically. */
	sgpio_irq_user_cb_t capture_cb;             /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pcapture_arg;                         /*!< User defined IRQ callback parameter. */
} hal_sgpio_rxtc_capture_mode_t, *phal_sgpio_rxtc_capture_mode_t;

/**
  \brief  The parameter structure of the rxtc capture timeout.
*/
typedef struct hal_sgpio_rxtc_capture_timeout_s {
	BOOL capture_timeout_en;                    /*!< To enable or disable. */
	BOOL capture_timer_reset_en;                /*!< Reset the capture timer when the timer value is equal to timeout_value. */
	BOOL capture_timer_disable_en;              /*!< Stop the capture timer when the timer value is equal to timeout_value. */
	sgpio_time_unit_t time_unit;                /*!< Select the time unit. */
	u32 timeout_value;                          /*!< Matching this timeout value generates the interrupt. */
	sgpio_irq_user_cb_t capture_timeout_cb;     /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pcapture_timeout_arg;                 /*!< User defined IRQ callback parameter.  */
} hal_sgpio_rxtc_capture_timeout_t, *phal_sgpio_rxtc_capture_timeout_t;

/**
  \brief  The parameter structure of the rxtc capture monitor.
*/
typedef struct hal_sgpio_rxtc_capture_monitor_s {
	BOOL capture_monitor_en;                    /*!< To enable or disable. */
	sgpio_time_unit_t time_unit;                /*!< Select the time unit.  */
	u32 monitor_time;                           /*!< The monitor value. */
	u8 monitor_count;                           /*!< Set the continuous numbers of the successful condition. Value: 1 ~ 32, 0: do nothing. */
	sgpio_irq_user_cb_t capture_monitor_cb;     /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pcapture_monitor_arg;                 /*!< User defined IRQ callback parameter.  */
} hal_sgpio_rxtc_capture_monitor_t, *phal_sgpio_rxtc_capture_monitor_t;

/**
  \brief  The parameter structure of the sampling rxdata.
*/
typedef struct hal_sgpio_sampling_rxdata_s {
	BOOL sampling_en;                           /*!< To enable or disable. */
	sgpio_rxtc_input_start_t start_timer_edge;  /*!< Select the trigger edge for starting the rxtc timer. */
	sgpio_time_unit_t time_unit;                /*!< Select the time unit. */
	u32 sampling_time1_time;                    /*!< The sampling time 1 needs less than the sampling end time. Set to 0 when not in use. */
	u32 sampling_time2_time;                    /*!< The sampling time 2 needs less than the sampling end time. Set to 0 when not in use. */
	u32 sampling_time_end_time;                 /*!< The sampling end time. Matching this time is to make the timer reset and stop. */
	u8 sampling_bit_length;                     /*!< Set the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing. */
	sgpio_first_msb_or_lsb_t first_msb_or_lsb;  /*!< Putting in the register is LSB or MSB. */
	sgpio_irq_user_cb_t sampling_finish_cb;     /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *psampling_finish_arg;                 /*!< User defined IRQ callback parameter. */
} hal_sgpio_sampling_rxdata_t, *phal_sgpio_sampling_rxdata_t;

/**
  \brief  The parameter structure of the capture compare rxdata.
*/
typedef struct hal_sgpio_capture_compare_rxdata_s {
	BOOL capture_en;                            /*!< To enable or disable. */
	sgpio_rxtc_input_start_t start_timer_edge;  /*!< Select the trigger edge for starting the rxtc timer.   */
	sgpio_capture_type_t input_capture_edge;    /*!< Select the capture edge for capturing the time. */
	u32 max_capture_range_us;                   /*!< Set the maximum possible measurement value for making the prescale of the timer automatically.  */
	sgpio_time_unit_t time_unit;                /*!< Select the time unit. */
	u32 capture_compare_value_time;             /*!< Set the compare time. */
	sgpio_cmp_result_bit_t compare_result_bit;  /*!< Deciding the value of the result bit is "0" or "1".  */
	u8 compare_bit_length;                      /*!< Set the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing.   */
	sgpio_first_msb_or_lsb_t first_msb_or_lsb;  /*!< Putting in the register is LSB or MSB. */
	sgpio_irq_user_cb_t compare_finish_cb;      /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pcompare_finish_arg;                  /*!< User defined IRQ callback parameter.  */
} hal_sgpio_capture_compare_rxdata_t, *phal_sgpio_capture_compare_rxdata_t;

/**
  \brief  The parameter structure of the txdata bit symbol.
*/
typedef struct hal_sgpio_txdata_bit_symbol_s {
	sgpio_output_value_t initial_output_value;  /*!< Set the initial output value. */
	sgpio_time_unit_t time_unit;                /*!< Select the time unit. */
	u32 bit0_middle_change_time;                /*!< The time is to change the output value for the bit 0. */
	u32 bit0_duration_time;                     /*!< The duration of the bit 0. */
	u32 bit1_middle_change_time;                /*!< The time is to change the output value for the bit 1. */
	u32 bit1_duration_time;                     /*!< The duration of the bit 1. */
} hal_sgpio_txdata_bit_symbol_t, *phal_sgpio_txdata_bit_symbol_t;

/**
  \brief  The parameter structure of the txdata.
*/
typedef struct hal_sgpio_txdata_s {
	BOOL txdata_en;                         /*!< To enable or disable. */
	BOOL rx_direction_output_en;            /*!< Control the output behavior of the bidirectional Rx. */
	u16 output_bit_counts;                  /*!< Set the output bit number.  */
	u32 *ptxdata_pointer;                   /*!< Set the output data pointer. */
	sgpio_irq_user_cb_t txdata_finish_cb;   /*!< When finish the TX output, generate the interrupt.  */
	void *ptxdata_finish_arg;               /*!< User defined IRQ callback parameter.   */
} hal_sgpio_txdata_t, *phal_sgpio_txdata_t;

/**
  \brief  The parameter structure of the monitor rxdata.
*/
typedef struct hal_sgpio_monitor_rxdata_s {
	BOOL monitor_en;                        /*!< To enable or disable. */
	u32 monitor_data;                       /*!< Set the monitor data. */
	u32 monitor_input_data_mask;            /*!< Set the bit mask of the monitor data. */
	sgpio_irq_user_cb_t monitor_rxdata_cb;  /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pmonitor_rxdata_arg;              /*!< User defined IRQ callback parameter.  */
} hal_sgpio_monitor_rxdata_t, *phal_sgpio_monitor_rxdata_t;

/**
  \brief  The parameter structure of the dma match output.
*/
typedef struct hal_sgpio_dma_match_output_s {
	sgpio_external_output_t match_value1_output;    /*!< Set the output value when match value 1. */
	sgpio_external_output_t match_value2_output;    /*!< Set the output value when match value 2. */
	sgpio_external_output_t match_value3_output;    /*!< Set the output value when match value 3. */
	u16 *pmatch_value_ptr;                          /*!< The pointer is the memory address of setting the match time. */
	u8  match_reset_counter;                        /*!< Set the number of reset times. An interrupt will be generated when the number of times is reached. */
	sgpio_irq_user_cb_t counter_finish_cb;          /*!< User defined IRQ callback function. Using "NULL" will not generate this interrupt. */
	void *pcounter_finish_arg;                      /*!< User defined IRQ callback parameter. */
} hal_sgpio_dma_match_output_t, *phal_sgpio_dma_match_output_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_sgpio_rom_func SGPIO HAL ROM APIs.
 * @{
 */

void hal_rom_sgpio_irq_handler(void *hid);
void hal_rom_sgpio_irq_reg(void);
void hal_rom_sgpio_unreg(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_reg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_user_cb_t callback, void *arg, sgpio_irq_shift_t irq_shift);
void hal_rom_sgpio_unreg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_shift_t irq_shift);
HAL_Status hal_rom_sgpio_en_ctrl(sgpio_index_sel_t sgpio_index, BOOL en);
HAL_Status hal_rom_sgpio_init(hal_sgpio_adapter_t *psgpio_adp, sgpio_index_sel_t sgpio_index);
void hal_rom_sgpio_deinit(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_enter_critical(void);
void hal_rom_sgpio_exit_critical(void);
void hal_rom_sgpio_set_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_rom_sgpio_get_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_rom_sgpio_set_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_rom_sgpio_get_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_rom_sgpio_set_rxtc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 match_value);
void hal_rom_sgpio_set_rxtc_int(hal_sgpio_adapter_t *psgpio_adp,  sgpio_rxtc_match_event_t match_event, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_set_capture_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_capture_type_t capture_type, BOOL cap_en);
void hal_rom_sgpio_set_capture_compare(hal_sgpio_adapter_t *psgpio_adp, u8 cap_cmpval_sel, u16 cap_cmpval);
void hal_rom_sgpio_set_capture_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_set_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_rom_sgpio_get_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_rom_sgpio_set_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_rom_sgpio_get_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_rom_sgpio_set_multc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
		u16 match_value);
void hal_rom_sgpio_set_multc_match_event0_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_set_multc_match_group(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group);
void hal_rom_sgpio_set_multc_fifo_value(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_fifo_value_t *pfifo_value);
void hal_rom_sgpio_set_rxtc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, sgpio_external_output_t external_output);
void hal_rom_sgpio_set_multc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_event_t match_event, sgpio_external_output_t external_output);
void hal_rom_sgpio_set_multc_match_event0_cnt_int(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_set_multc_match_event0_cnt(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt);
void hal_rom_sgpio_init_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_event_t *psampling_event);
void hal_rom_sgpio_deinit_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_init_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, u16 cap_cmpval);
void hal_rom_sgpio_deinit_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp);
HAL_Status hal_rom_sgpio_set_rxdata_load_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_set_rxdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_reset_rxdata(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_set_rxdata_match_int(hal_sgpio_adapter_t *psgpio_adp, BOOL rxdata_match_en, u32 match_value, hal_sgpio_set_irq_t *psgpio_set_irq);
HAL_Status hal_rom_sgpio_set_txdata_bit_length_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_set_txdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_rom_sgpio_reset_txdata(hal_sgpio_adapter_t *psgpio_adp);
u32 hal_rom_sgpio_set_time_to_rxtc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value);
u32 hal_rom_sgpio_set_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value);
u32 hal_rom_sgpio_set_rxtc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_unit, sgpio_time_unit_t time_unit);
u32 hal_rom_sgpio_set_multc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 multc_unit, sgpio_time_unit_t time_unit);
void hal_rom_sgpio_clean_status(hal_sgpio_adapter_t *psgpio_adp, u32 sgpio_is);
void hal_rom_sgpio_update_rxtcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 old_prescale);
void hal_rom_sgpio_update_multcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
								  u16 old_prescale);
void hal_rom_sgpio_rxtc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_mode_t *psgpio_rxtc_timer_mode);
void hal_rom_sgpio_multc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_timer_mode_t *psgpio_multc_timer_mode);
void hal_rom_sgpio_multc_counter_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_counter_mode_t *psgpio_multc_counter_mode);
void hal_rom_sgpio_rxtc_timer_match_output(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_match_output_t *psgpio_rxtc_timer_match_output);
void hal_rom_sgpio_multc_timer_counter_match_output(hal_sgpio_adapter_t *psgpio_adp,
		hal_sgpio_multc_timer_counter_match_output_t *psgpio_multc_timer_counter_match_output);
void hal_rom_sgpio_rxtc_capture_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_mode_t *psgpio_rxtc_capture_mode);
void hal_rom_sgpio_rxtc_capture_timeout(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_timeout_t *psgpio_rxtc_capture_timeout);
void hal_rom_sgpio_rxtc_capture_monitor(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_monitor_t *psgpio_rxtc_capture_monitor);
u32 hal_rom_sgpio_get_rxtc_capture_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit);
void hal_rom_sgpio_init_rxdata_capture_compare_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, sgpio_time_unit_t time_unit,
		u32 cap_cmpval_time);
void hal_rom_sgpio_sampling_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_rxdata_t *psgpio_sampling_data);
u32 hal_rom_sgpio_get_input_rxdata(hal_sgpio_adapter_t *psgpio_adp);
u32 hal_rom_sgpio_get_arrange_rxdata(hal_sgpio_adapter_t *psgpio_adp, u32 rxdata_tp);
void hal_rom_sgpio_capture_compare_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_capture_compare_rxdata_t *psgpio_compare_data);
void hal_rom_sgpio_txdata_bit_symbol(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_bit_symbol_t *psgpio_txdata_bit_symbol);
void hal_rom_sgpio_txdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_t *psgpio_txdata);
void hal_rom_sgpio_txdata_bit_length_irq(void *data);
void hal_rom_sgpio_send_txdata(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_reset_receive_rxdata(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_disable_rxdata_match(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_monitor_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_monitor_rxdata_t *pmonitor_rxdata);
void hal_rom_sgpio_multc_fifo_reset(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_dma_match_output_irq_handle(void *data);
HAL_Status hal_rom_sgpio_dma_match_output_init(hal_sgpio_adapter_t *psgpio_adp, hal_gdma_adaptor_t *pgdma_adaptor,
		hal_sgpio_dma_match_output_t *pdma_match_output);
HAL_Status hal_rom_sgpio_dma_match_output_deinit(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_dma_handshake_init(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_dma_match_output_t *pdma_match_output);
void hal_rom_sgpio_dma_preload_data(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_dma_send_start(hal_sgpio_adapter_t *psgpio_adp);
void hal_rom_sgpio_dma_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, u16 *pmemory_addr, u8 reset_cnt, sgpio_time_unit_t time_unit);

/**
 *  @brief  Rxtc and rxprtc are synchronously reset.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxtc_rst(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmr_crst = 1;
}

/**
 *  @brief  Set the rx timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] rxtc_value Rx timer counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxtc_value(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_value)
{
	psgpio_adp->base_addr->rxtc_b.rxtc = rxtc_value;
}

/**
 *  @brief  Get the rx timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Rx timer counter value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_rxtc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->rxtc_b.rxtc);
}

/**
 *  @brief  Set the maximum value of the rx prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] prescale Maximum value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxtc_prescale(hal_sgpio_adapter_t *psgpio_adp, u16 prescale)
{
	psgpio_adp->base_addr->rxprval_b.rxprval = prescale;
}

/**
 *  @brief  Get the maximum value of the rx prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Rx timer counter value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_rxtc_prescale(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->rxprval_b.rxprval);
}

/**
 *  @brief  Set the rx prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] prerxtc_value Rx prescale counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_prerxtc_value(hal_sgpio_adapter_t *psgpio_adp, u16 prerxtc_value)
{
	psgpio_adp->base_addr->rxprtc_b.rxprtc = prerxtc_value;
}

/**
 *  @brief  Get the rx prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Rx prescale counter value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_prerxtc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->rxprtc_b.rxprtc);
}

/**
 *  @brief  Control the capture function.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] cap_en To enable or disable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_capture_en(hal_sgpio_adapter_t *psgpio_adp, BOOL cap_en)
{
	psgpio_adp->base_addr->cap_ctrl_b.cap_en = cap_en;
}

/**
 *  @brief  Get the capture value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The capture value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_capture_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->capr_b.capr);
}

/**
 *  @brief  Control the rxtc timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] start_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxtc_start_en(hal_sgpio_adapter_t *psgpio_adp, BOOL start_en)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmr_cen = start_en;
}

/**
 *  @brief  Control the input methold to start rx timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] rxtc_input_start Select the input methold.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxtc_input_start_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_input_start_t rxtc_input_start)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmredge_sel = rxtc_input_start;
}

/**
 *  @brief  Multc and mulprtc are synchronously reset.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_multc_rst(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->multmr_ctrl_b.multmr_crst = 1;
}

/**
 *  @brief  Set the multiple timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] multc_value Multiple timer counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_multc_value(hal_sgpio_adapter_t *psgpio_adp, u16 multc_value)
{
	psgpio_adp->base_addr->multc_b.multc = multc_value;
}

/**
 *  @brief  Get the multiple timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Multiple timer counter value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_multc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->multc_b.multc);
}

/**
 *  @brief  Set the maximum value of the multiple prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] prescale Maximum value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_multc_prescale(hal_sgpio_adapter_t *psgpio_adp, u16 prescale)
{
	psgpio_adp->base_addr->mulprval_b.mulprval = prescale;
}

/**
 *  @brief  Get the maximum value of the multiple prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Multiple timer counter value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_multc_prescale(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->mulprval_b.mulprval);
}

/**
 *  @brief  Set the multiple prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] premultc_value Multiple prescale counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_premultc_value(hal_sgpio_adapter_t *psgpio_adp, u16 prerxtc_value)
{
	psgpio_adp->base_addr->mulprtc_b.mulprtc = prerxtc_value;
}

/**
 *  @brief  Get the multiple prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Multiple prescale counter value.
 */
__STATIC_INLINE
u16 hal_rom_sgpio_get_premultc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->mulprtc_b.mulprtc);
}

/**
 *  @brief  Control the multiple timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] start_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_multc_start_en(hal_sgpio_adapter_t *psgpio_adp, BOOL start_en)
{
	psgpio_adp->base_addr->multmr_ctrl_b.multmr_cen = start_en;
}

/**
 *  @brief  Select the mode of the multiple timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] multc_mode Select timer or counter mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_multc_mode_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_mode_t multc_mode)
{
	psgpio_adp->base_addr->multmr_ctrl_b.mulmode_en = multc_mode;
}

/**
 *  @brief  Control the multiple timer counter to use the FIFO mode.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] fifo_mode_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_multc_fifo_mode(hal_sgpio_adapter_t *psgpio_adp, BOOL fifo_mode_en)
{
	psgpio_adp->base_addr->mulmc_b.mul_fmode_en = fifo_mode_en;
}

/**
 *  @brief  Get the countdown counter value for counting the multc match event0.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The countdown counter value.
 */
__STATIC_INLINE
u8 hal_rom_sgpio_get_multc_match_event0_cnt_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->mul_mcnt_b.mul_mcnt + 1);
}

/**
 *  @brief  Get the rxdata value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The rxdata value.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->rxdata_dp);
}

/**
 *  @brief  Get the rxdata value being processed.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The rxdata value being processed.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_rxdata_prebuf(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->rxdata);
}

/**
 *  @brief  Mask the match pattern for monitoring rxdata.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] match_mask The bit mask.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxdata_match_mask(hal_sgpio_adapter_t *psgpio_adp, u32 match_mask)
{
	psgpio_adp->base_addr->rxdatamask = match_mask;
}

/**
 *  @brief  Get the mask value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The mask value.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_rxdata_match_mask(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->rxdatamask);
}

/**
 *  @brief  Select the input direction of the rxdata.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] direction Select the input is MSB or LSB.
 *                      -0: input data from msb.
 *                      -1: input data from lsb.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rxdata_direction(hal_sgpio_adapter_t *psgpio_adp, u8 direction)
{
	psgpio_adp->base_addr->data_ctrl_b.rxdata_dir = direction;
}

/**
 *  @brief  Control the rx to become the bi-direction.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] inoutput Select the input or bi-direction.
 *                      -0: Only input.
 *                      -1: Bi-direction.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_rx_in_out_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_rx_inoutput_t inoutput)
{
	psgpio_adp->base_addr->mulemr_b.biout_en = inoutput;
}

/**
 *  @brief  Control the txdata to work
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] txdata_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_init_txdata_en(hal_sgpio_adapter_t *psgpio_adp, BOOL txdata_en)
{
	psgpio_adp->base_addr->mulmc_b.mul_mr0sclk_en = txdata_en;
}

/**
 *  @brief  Set the txdata value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] txdata The txdata value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_txdata(hal_sgpio_adapter_t *psgpio_adp, u32 txdata)
{
	psgpio_adp->base_addr->muldata_dp = txdata;
}

/**
 *  @brief  Set the txdata value being processed.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] txdata The txdata value being processed.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_txdata_prebuf(hal_sgpio_adapter_t *psgpio_adp, u32 txdata)
{
	psgpio_adp->base_addr->muldata = txdata;
}

/**
 *  @brief  Get the txdata value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The txdata value.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_txdata(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->muldata_dp);
}

/**
 *  @brief  Get the txdata value being processed.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The txdata value being processed.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_txdata_prebuf(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->muldata);
}

/**
 *  @brief  Select the output direction of the txdata.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] direction Select the output is MSB or LSB.
 *                      -0: output data from msb.
 *                      -1: output data from lsb.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_txdata_direction(hal_sgpio_adapter_t *psgpio_adp, u8 direction)
{
	psgpio_adp->base_addr->data_ctrl_b.txdata_dir = direction;
}

/**
 *  @brief  Control to drive the output state by setting this bit.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] value Set the output is low or high.
 *                      -0: output is low.
 *                      -1: output is high.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_output_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_output_value_t value)
{
	psgpio_adp->base_addr->output_b.output = value;
}

/**
 *  @brief  Get the output state.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The output state.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_output_value(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->output_b.output);
}

/**
 *  @brief  Make the output state inverse.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_rom_sgpio_set_output_inverse(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->output_b.output = ~psgpio_adp->base_addr->output_b.output;
}

/**
 *  @brief  Get the SGPIO interrupt status.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The interrupt status.
 */
__STATIC_INLINE
u32 hal_rom_sgpio_get_status(hal_sgpio_adapter_t *psgpio_adp)
{
	return (psgpio_adp->base_addr->is);
}

/** @} */ /* End of group hs_hal_sgpio_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/**
  \brief  The data structure of the stubs function for the Timer HAL functions in ROM
*/
typedef struct hal_sgpio_func_stubs_s {
	hal_sgpio_group_adapter_t *psgpio_group_adapter;
	const uint8_t *psgpio_pin;
	void (*hal_sgpio_irq_handler)(void *hid);
	void (*hal_sgpio_irq_reg)(void);
	void (*hal_sgpio_unreg)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_reg_cb)(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_user_cb_t callback, void *arg, sgpio_irq_shift_t irq_shift);
	void (*hal_sgpio_unreg_cb)(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_shift_t irq_shift);
	HAL_Status(*hal_sgpio_en_ctrl)(sgpio_index_sel_t sgpio_index, BOOL en);
	HAL_Status(*hal_sgpio_init)(hal_sgpio_adapter_t *psgpio_adp, sgpio_index_sel_t sgpio_index);
	void (*hal_sgpio_deinit)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_enter_critical)(void);
	void (*hal_sgpio_exit_critical)(void);
	void (*hal_sgpio_set_rxtc_stop_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
	void (*hal_sgpio_get_rxtc_stop_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
	void (*hal_sgpio_set_rxtc_reset_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
	void (*hal_sgpio_get_rxtc_reset_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
	void (*hal_sgpio_set_rxtc_match_value)(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 match_value);
	void (*hal_sgpio_set_rxtc_int)(hal_sgpio_adapter_t *psgpio_adp,  sgpio_rxtc_match_event_t match_event, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_set_capture_ctrl)(hal_sgpio_adapter_t *psgpio_adp, sgpio_capture_type_t capture_type, BOOL cap_en);
	void (*hal_sgpio_set_capture_compare)(hal_sgpio_adapter_t *psgpio_adp, u8 cap_cmpval_sel, u16 cap_cmpval);
	void (*hal_sgpio_set_capture_int)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_set_multc_stop_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
	void (*hal_sgpio_get_multc_stop_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
	void (*hal_sgpio_set_multc_reset_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
	void (*hal_sgpio_get_multc_reset_ctrl)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
	void (*hal_sgpio_set_multc_match_value)(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
											u16 match_value);
	void (*hal_sgpio_set_multc_match_event0_int)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_set_multc_match_group)(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group);
	void (*hal_sgpio_set_multc_fifo_value)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_fifo_value_t *pfifo_value);
	void (*hal_sgpio_set_rxtc_external_match)(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, sgpio_external_output_t external_output);
	void (*hal_sgpio_set_multc_external_match)(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_event_t match_event, sgpio_external_output_t external_output);
	void (*hal_sgpio_set_multc_match_event0_cnt_int)(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_set_multc_match_event0_cnt)(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt);
	void (*hal_sgpio_init_rxdata_time_sampling)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_event_t *psampling_event);
	void (*hal_sgpio_deinit_rxdata_time_sampling)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_init_rxdata_capture_compare)(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, u16 cap_cmpval);
	void (*hal_sgpio_deinit_rxdata_capture_compare)(hal_sgpio_adapter_t *psgpio_adp);
	HAL_Status(*hal_sgpio_set_rxdata_load_int)(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_set_rxdata_prebuf_bit_shift_int)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_reset_rxdata)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_set_rxdata_match_int)(hal_sgpio_adapter_t *psgpio_adp, BOOL rxdata_match_en, u32 match_value, hal_sgpio_set_irq_t *psgpio_set_irq);
	HAL_Status(*hal_sgpio_set_txdata_bit_length_int)(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_set_txdata_prebuf_bit_shift_int)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
	void (*hal_sgpio_reset_txdata)(hal_sgpio_adapter_t *psgpio_adp);
	u32(*hal_sgpio_set_time_to_rxtc)(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value);
	u32(*hal_sgpio_set_time_to_multc)(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value);
	u32(*hal_sgpio_set_rxtc_to_time)(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_unit, sgpio_time_unit_t time_unit);
	u32(*hal_sgpio_set_multc_to_time)(hal_sgpio_adapter_t *psgpio_adp, u16 multc_unit, sgpio_time_unit_t time_unit);
	void (*hal_sgpio_clean_status)(hal_sgpio_adapter_t *psgpio_adp, u32 sgpio_is);
	void (*hal_sgpio_update_rxtcmr)(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 old_prescale);
	void (*hal_sgpio_update_multcmr)(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
									 u16 old_prescale);
	void (*hal_sgpio_rxtc_timer_mode)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_mode_t *psgpio_rxtc_timer_mode);
	void (*hal_sgpio_multc_timer_mode)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_timer_mode_t *psgpio_multc_timer_mode);
	void (*hal_sgpio_multc_counter_mode)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_counter_mode_t *psgpio_multc_counter_mode);
	void (*hal_sgpio_rxtc_timer_match_output)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_match_output_t *psgpio_rxtc_timer_match_output);
	void (*hal_sgpio_multc_timer_counter_match_output)(hal_sgpio_adapter_t *psgpio_adp,
			hal_sgpio_multc_timer_counter_match_output_t *psgpio_multc_timer_counter_match_output);
	void (*hal_sgpio_rxtc_capture_mode)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_mode_t *psgpio_rxtc_capture_mode);
	void (*hal_sgpio_rxtc_capture_timeout)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_timeout_t *psgpio_rxtc_capture_timeout);
	void (*hal_sgpio_rxtc_capture_monitor)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_monitor_t *psgpio_rxtc_capture_monitor);
	u32(*hal_sgpio_get_rxtc_capture_time)(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit);
	void (*hal_sgpio_init_rxdata_capture_compare_time)(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, sgpio_time_unit_t time_unit,
			u32 cap_cmpval_time);
	void (*hal_sgpio_sampling_rxdata)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_rxdata_t *psgpio_sampling_data);
	u32(*hal_sgpio_get_input_rxdata)(hal_sgpio_adapter_t *psgpio_adp);
	u32(*hal_sgpio_get_arrange_rxdata)(hal_sgpio_adapter_t *psgpio_adp, u32 rxdata_tp);
	void (*hal_sgpio_capture_compare_rxdata)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_capture_compare_rxdata_t *psgpio_compare_data);
	void (*hal_sgpio_txdata_bit_symbol)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_bit_symbol_t *psgpio_txdata_bit_symbol);
	void (*hal_sgpio_txdata)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_t *psgpio_txdata);
	void (*hal_sgpio_txdata_bit_length_irq)(void *data);
	void (*hal_sgpio_send_txdata)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_reset_receive_rxdata)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_disable_rxdata_match)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_monitor_rxdata)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_monitor_rxdata_t *pmonitor_rxdata);
	void (*hal_sgpio_multc_fifo_reset)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_dma_match_output_irq_handle)(void *data);
	HAL_Status(*hal_sgpio_dma_match_output_init)(hal_sgpio_adapter_t *psgpio_adp, hal_gdma_adaptor_t *pgdma_adaptor,
			hal_sgpio_dma_match_output_t *pdma_match_output);
	HAL_Status(*hal_sgpio_dma_match_output_deinit)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_dma_handshake_init)(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_dma_match_output_t *pdma_match_output);
	void (*hal_sgpio_dma_preload_data)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_dma_send_start)(hal_sgpio_adapter_t *psgpio_adp);
	void (*hal_sgpio_dma_time_to_multc)(hal_sgpio_adapter_t *psgpio_adp, u16 *pmemory_addr, u8 reset_cnt, sgpio_time_unit_t time_unit);
	uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_sgpio_func_stubs_t;

/** @} */ /* End of group hs_hal_sgpio */

#endif  // end of "#define _RTL8195BHP_SGPIO_H_"

