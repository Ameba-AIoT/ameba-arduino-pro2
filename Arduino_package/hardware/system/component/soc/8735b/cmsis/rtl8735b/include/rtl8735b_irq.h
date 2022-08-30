/**************************************************************************//**
 * @file     rtl8735b_irq.h
 * @brief    CMSIS Device System Header File for the Rtl8195B High Power platform.
 *           Defines the IRQ number for the System interrupts and Peripheral
 *           interrupts.
 * @version  V1.00
 * @date     2020-08-13
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation. All rights reserved.
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

#ifndef _RTL8735B_IRQ_H_
#define _RTL8735B_IRQ_H_


#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup hs_hal_irq IRQ
 * @ingroup 8195bh_hal
 * @{
 * @brief The IRQ APIs of the HS platform.
 */

/// Number of interrupt for the system level, it's defined by the ARM Cortex-M CPU.
#define MAX_SYSTEM_IRQ_NUM                  16
/// Number of interrupt for peripheral devices on this platform.
#define MAX_PERIPHERAL_IRQ_NUM              64
/// Total number of interrupt on this platform.
#define MAX_VECTOR_TABLE_NUM                (MAX_SYSTEM_IRQ_NUM + MAX_PERIPHERAL_IRQ_NUM)

/* -------------------------  Interrupt Priority Definition  ------------------------ */
/**
  \brief  Default interrupt priority for external(peripheral devices) interrupts.
*/
enum IRQ_Priority {
	SystemOn_IRQPri             = 0,       /*!< 0 SystemOn Interrupt Priority            */
	TimerGroup0_IRQPri          = 9,       /*!< 1 TimerGroup0 Interrupt Priority         */
	TimerGroup1_IRQPri          = 9,       /*!< 2 TimerGroup1 Interrupt Priority         */
	TimerGroup2_IRQPri          = 9,       /*!< 3 TimerGroup2 Interrupt Priority         */
	TimerGroup3_IRQPri          = 9,       /*!< 4 TimerGroup3 Interrupt Priority         */
	GPIO_IRQPri                 = 9,       /*!< 5 GPIO Interrupt Priority                */
	PWM_IRQPri                  = 9,       /*!< 6 PWM Interrupt Priority                 */
	ADC_IRQPri                  = 9,       /*!< 7 ADC Interrupt Priority                 */
	SGPIO_IRQPri                = 9,       /*!< 8 SGPIO Interrupt Priority               */
	UART0_IRQPri                = 9,       /*!< 9 UART0 Interrupt Priority               */
	UART1_IRQPri                = 9,       /*!< 10 UART1 Interrupt Priority              */
	UART2_IRQPri                = 9,       /*!< 11 UART2 Interrupt Priority              */
	UART3_IRQPri                = 9,       /*!< 12 UART3 Interrupt Priority              */
	BTUART_IRQPri               = 9,       /*!< 13 BTUART Interrupt Priority             */
	I2C0_IRQPri                 = 9,       /*!< 14 I2C0 Interrupt Priority               */
	I2C1_IRQPri                 = 9,       /*!< 15 I2C1 Interrupt Priority               */
	I2C2_IRQPri                 = 9,       /*!< 16 I2C2 Interrupt Priority               */
	I2C3_IRQPri                 = 9,       /*!< 17 I2C3 Interrupt Priority               */
	SPI0_IRQPri                 = 9,       /*!< 18 SPI0 Interrupt Priority               */
	SPI1_IRQPri                 = 9,       /*!< 19 SPI1 Interrupt Priority               */
	HSPI0_IRQPri                = 9,       /*!< 20 HSPI0 Interrupt Priority              */
	HSPI1_IRQPri                = 9,       /*!< 21 HSPI1 Interrupt Priority              */
	I2S0_IRQPri                 = 9,       /*!< 22 I2S0 Interrupt Priority               */
	I2S1_IRQPri                 = 9,       /*!< 23 I2S1 Interrupt Priority               */
	SPORT_IRQPri                = 9,       /*!< 24 SPORT Interrupt Priority              */
	USB_IRQPri                  = 9,       /*!< 25 USB Interrupt Priority                */
	SDIOH_IRQPri                = 9,       /*!< 26 SDIOH Interrupt Priority              */
	SDH_IRQPri                  = 9,       /*!< 27 SDH Interrupt Priority                */
	MII_IRQPri                  = 9,       /*!< 28 MII Interrupt Priority                */
	WLAN_IRQPri                 = 9,       /*!< 29 WLAN Interrupt Priority               */
	WLAN_PWR_IRQPri             = 9,       /*!< 30 WLAN_PWR Interrupt Priority           */
	RSA_IRQPri                  = 9,       /*!< 31 RSA Interrupt Priority                */
	SPIC_NAND_IRQPri            = 9,       /*!< 32 SPIC_NAND Interrupt Priority          */
	GDMA0_IRQPri                = 9,       /*!< 33 GDMA0 Interrupt Priority              */
	GDMA1_IRQPri                = 9,       /*!< 34 GDMA1 Interrupt Priority              */
	Crypto_IRQPri               = 9,       /*!< 35 Crypto Interrupt Priority             */
	FlashCtrl_IRQPri            = 9,       /*!< 36 FlashCtrl Interrupt Priority          */
	AON_IRQPri                  = 9,       /*!< 37 AON Interrupt Priority                */
	ISP_IRQPri                  = 9,       /*!< 38 ISP Interrupt Priority                */
	ENC_IRQPri                  = 9,       /*!< 39 ENC Interrupt Priority                */
	VOE_IRQPri                  = 9,       /*!< 40 VOE Interrupt Priority                */
	NN_IRQPri                   = 9,       /*!< 41 NN Interrupt Priority                 */
	SGDMA0_IRQPri               = 9,       /*!< 42 SGDMA0 Interrupt Priority             */
	SGDMA1_IRQPri               = 9,       /*!< 43 SGDMA1 Interrupt Priority             */
	SCrypto_IRQPri              = 9,       /*!< 44 SCrypto Interrupt Priority            */
	ECDSA_IRQPri                = 9,       /*!< 45 ECDSA Interrupt Priority              */
	ED25519_IRQPri              = 9,       /*!< 46 ED25519 Interrupt Priority            */
	SRXI_IRQPri                 = 9,       /*!< 47 SRXI Interrupt Priority               */
	RXI_IRQPri                  = 9,       /*!< 48 RXI Interrupt Priority                */
	WDT_VOE_IRQPri              = 9,       /*!< 49 WDT_VOE Interrupt Priority            */
	WDT_WL_IRQPri               = 9,       /*!< 50 WDT_WL Interrupt Priority             */
	SRC_OCP_OUT_L_IRQPri        = 9,       /*!< 51 SRC_OCP_OUT_L Interrupt Priority      */
	OCP_OUT_L_IRQPri            = 9,       /*!< 52 OCP_OUT_L Interrupt Priority          */
	PonGPIO_IRQPri              = 9,       /*!< 53 PonGPIO Interrupt Priority            */
	TRNG_IRQPri                 = 9,       /*!< 54 TRNG Interrupt Priority               */
	BOD_IRQPri                  = 9,       /*!< 55 BOD Interrupt Priority                */
	RTC_IRQPri                  = 9,       /*!< 56 RTC Interrupt Priority                */
	Comparator_IRQPri           = 9,       /*!< 57 Comparator Interrupt Priority         */
	Flash_SEC_IRQPri            = 9,       /*!< 58 Flash_SEC Interrupt Priority          */
	FEPHY_IRQPri                = 9,       /*!< 59 FEPHY Interrupt Priority              */
};

/**
  \brief  The data structure of the IRQ API function table.
          For RAM code can hook another optional IRQ APIs for ROM HAL code.
*/
typedef struct hal_irq_api_s {
	void (*irq_enable)(int32_t irqn);               /*!< enable interrupt */
	void (*irq_disable)(int32_t irqn);              /*!< disable interrupt */
	void (*irq_set_vector)(int32_t irqn, uint32_t vector);          /*!< set interrupt vector */
	uint32_t (*irq_get_vector)(int32_t irqn);       /*!< get interrupt vector */
	void (*irq_set_priority)(int32_t irqn, uint32_t priority);      /*!< set interrupt priority */
	uint32_t (*irq_get_priority)(int32_t irqn);     /*!< get interrupt priority */
	void (*irq_set_pending)(int32_t irqn);          /*!< set pending interrupt */
	uint32_t (*irq_get_pending)(int32_t irqn);      /*!< get pending interrupt */
	void (*irq_clear_pending)(int32_t irqn);        /*!< clear pending interrupt */
	void (*interrupt_enable)(void);                 /*!< enable all interrupts */
	void (*interrupt_disable)(void);                /*!< disable all interrupts */
} hal_irq_api_t;

/**
  \brief  Function type of interrupt handler.
*/
typedef void (*int_vector_t)(void);

/**
  \brief  User application call back function for an interrupt.
*/
typedef void (*irq_handler_t)(void *data);

typedef struct irq_config_s {
	irq_handler_t   irq_fun;
	void            *data;
	int16_t         irq_num;
	uint16_t        priority;
} irq_config_t, *pirq_config_t;

/**
  \brief  The structure of the handler for stack back trace.
          It is used to list of the call trace when a hard fault is occurred.
*/
typedef struct fault_handler_back_trace_s {
	uint32_t msp_top;         /*!< the Top address of the MSP */
	uint32_t msp_limit;       /*!< the Limit address of the MSP */
	uint32_t ps_max_size;     /*!< the maximum stack size of PSP */
	uint32_t *ptxt_range_list;  /*!< point to the array for the list of text code range */
	uint32_t trace_depth;   /*!< the size of the trace buffer */
	uint32_t *ptrace_buf;   /*!< point to the trace buffer */
	uint32_t *poffset_buf;   /*!< point to the buffer for offset from SP in trace */
} fault_handler_back_trace_t, *pfault_handler_back_trace_t;


/**
  \brief  The stubs function table type of the IRQ HAL functions in ROM.
*/
typedef struct hal_int_vector_func_stubs_s {
	int_vector_t *ram_vector_table;
	hal_irq_api_t *pirq_api_tbl;
	pfault_handler_back_trace_t *ppbk_trace_hdl;
	pfault_handler_back_trace_t *ppbk_trace_hdl_ns;

	void (*hal_vector_table_init)(uint32_t stack_ptr, int_vector_t *vector_tbl);
	void (*hal_irq_api_init)(hal_irq_api_t *pirq_api);
	void (*hal_irq_enable)(int32_t irqn);
	void (*hal_irq_disable)(int32_t irqn);
	void (*hal_irq_set_vector)(int32_t irqn, uint32_t vector);
	uint32_t (*hal_irq_get_vector)(int32_t irqn);
	void (*hal_irq_set_priority)(int32_t irqn, uint32_t priority);
	uint32_t (*hal_irq_get_priority)(int32_t irqn);
	void (*hal_irq_set_pending)(int32_t irqn);
	uint32_t (*hal_irq_get_pending)(int32_t irqn);
	void (*hal_irq_clear_pending)(int32_t irqn);
	void (*hal_irq_unreg)(int32_t irqn);

	uint32_t reserved[4];  // reserved space for next ROM code version function table extending.
} hal_int_vector_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_irq_rom_func IRQ ROM APIs.
 * @{
 */

void hal_rtl_vector_table_init(uint32_t stack_ptr, int_vector_t *vector_tbl);

void _default_handler(void);
void hal_rtl_irq_api_init(hal_irq_api_t *pirq_api);
void hal_rtl_irq_enable(int32_t irqn);
void hal_rtl_irq_disable(int32_t irqn);
void hal_rtl_irq_set_vector(int32_t irqn, uint32_t vector);
uint32_t hal_rtl_irq_get_vector(int32_t irqn);
void hal_rtl_irq_set_priority(int32_t irqn, uint32_t priority);
uint32_t hal_rtl_irq_get_priority(int32_t irqn);
void hal_rtl_irq_set_pending(int32_t irqn);
uint32_t hal_rtl_irq_get_pending(int32_t irqn);
void hal_rtl_irq_clear_pending(int32_t irqn);
void hal_rtl_irq_unreg(int32_t irqn);
void hal_rtl_interrupt_enable(void);
void hal_rtl_interrupt_disable(void);

/** @} */ /* End of group hs_hal_irq_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/** @} */ /* End of group hs_hal_irq */

#ifdef __cplusplus
}
#endif

#endif //_RTL8735B_IRQ_H_


