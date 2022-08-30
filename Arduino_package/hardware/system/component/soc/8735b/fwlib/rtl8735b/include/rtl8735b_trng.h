

/**************************************************************************//**
 * @file     rtl8735b_trng.h
 * @brief    The HAL related definition and macros for the trng device.
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

#ifndef _RTL8735B_trng_H_
#define _RTL8735B_trng_H_

#include "rtl8735b_trng_type.h"


// System level AON/PON/SYSON regions registers
#include "rtl8735b_aon_type.h"
#include "rtl8735b_pon_type.h"
#include "rtl8735b_syson_type.h"
#include "rtl8735b_vndr_type.h"



#ifdef  __cplusplus
extern "C"
{
#endif

#if !defined(CONFIG_BUILD_NONSECURE)

#undef TRNG
#define TRNG    (TRNG_S_ADDR) // Secure address

#else

#undef TRNG
#define TRNG    (TRNG_ADDR) // Non-Secure address

#endif


#define TRNG_S_BASE               0x5000B000
#define TRNG_NS_BASE              0x4000B000

#define TRNG_S_ADDR                             ((TRNG_TypeDef *)           TRNG_S_BASE)
#define TRNG_ADDR                               ((TRNG_TypeDef *)           TRNG_NS_BASE)


/**
  * \brief The structure with the TRNG control information filled in.
**/

typedef struct hal_rng_reg_s {
	int LFSR_mode2;         //!< LFSR_mode2 enable = 1, disable = 0
	int TRNG_mode;         //!< 0 is TRNG->BIAS->LFSR->self-test->buf  ,1 is TRNG->BIAS->self-test->LFSR->buf
	int selftest;        //!< self_test enable= 1, disable = 0
	int LFSR_mode;         //!< LFSR_mode enable = 1, disable = 0
	int LFSR_bypass1;        //!< LFSR1 bypass
	int TRNG_dbg1_sel;         //!<  debug signal group 1 select
	int TRNG_dbg0_sel;        //!<  debug signal group 0 select
	int TRNG_corrector_lmode;        //!< 0: 4 valid trng ,1:2 vaild trng
	int corrector_bypass;        //!< corrector_bypass = 1
	int high_speed_clock;       //!< 0 : clk_hfosc_rng: clk_hfosc_rng/2
	int RNG_SRST;       //!<  RNG software reset
} hal_rng_reg_t, *phal_rng_reg_t;

/**
  * \brief The structure with the TRNG self tes mode setting  information filled in.
**/

typedef struct hal_rng_st_reg_s {
	int thr_done_adap1;       //!<threshol for adaptive proportion test
	int thr_done_adap2;       //!<  threshol for adaptive proportion test
	int compare_rep;       //!< compare unit for repetition test
	int compare_unit_adap1; //!<compare unit for adaptive test 1
	int compare_unit_adap2; //!<compare unit for adaptive test 2
	int window_size_adap1; //!< Byte mode : 0'b = 64 ,1'b:256 ,2'b=4096,3'b= 65536   bit mode : 0'b = 512 ,1'b:1024 ,2'b=2048
	int window_size_adap2; //!< Byte mode : 0'b = 64 ,1'b:256 ,2'b=4096,3'b= 65536   bit mode : 0'b = 512 ,1'b:1024 ,2'b=2048
	int thr_err_rep; //!<error thresthold for repetitive count test
	int thr_thr_done_rep;//!< done threshold for repetition count test


} hal_rng_st_reg_t, *phal_rng_st_reg_t;

/**
  * \brief The structure with the TRNG self tes mode setting  information filled in.
**/

typedef struct hal_rng_int_reg_s {

	int ST_ERR;         //!<interrupt for self test error
	int parity;         //!<intterupt for buffer parity check
	int write_data;     //!<set write data


} hal_rng_int_reg_t, *phal_rng_int_reg_t;

/*! define trng interrupt call back function */
typedef void (*trng_callback_t)(void *);


/// @cond DOXYGEN_ROM_HAL_API
/**
  \brief  The data structure of the trng adapter
*/
typedef struct hal_trng_adapter_s {

	TRNG_Type *base_addr;    //!< The trng registers base address
	TRNG_TypeDef trng_reg;  //!< The data structure to control the trng register.
	irq_handler_t trng_callback; /*!< the callback function for NMI IRQ */
	uint32_t *trng_arg;            /*!< the application data will be back to the application*/
} hal_trng_adapter_t, *phal_trng_adapter_t;



/**
  \brief  The data structure of the stubs function for the trng HAL functions in ROM
*/
typedef struct hal_trng_func_stubs_s {

	phal_trng_adapter_t *ptrng_adp;
	void (*hal_trng_enable_128K)(hal_trng_adapter_t *ptrng_adp);
	void (*hal_trng_enable_32K)(hal_trng_adapter_t *ptrng_adp);
	void (*hal_trng_disable)(hal_trng_adapter_t *ptrng_adp);
	void (*hal_trng_reg_irq)(irq_handler_t handler, uint32_t *arg);
	hal_status_t (*hal_trng_control_setting)(hal_trng_adapter_t *ptrng_adp, hal_rng_reg_t *ptrng_reg);
	hal_status_t (*hal_trng_init)(hal_trng_adapter_t *ptrng_adp) ;
	hal_status_t (*hal_trng_deinit)(hal_trng_adapter_t *ptrng_adp);
	hal_status_t (*hal_trng_load_default)(hal_trng_adapter_t *ptrng_adp, hal_rng_st_reg_t *ptrng_st_reg,  hal_rng_reg_t *ptrng_reg);
	void (*hal_trng_reset)(hal_trng_adapter_t *ptrng_adp);
	void (*hal_trng_self_test_setting)(hal_trng_adapter_t *ptrng_adp, hal_rng_st_reg_t *ptrng_st_reg);
	hal_status_t (*hal_trng_interrupt_reg)(hal_trng_adapter_t *ptrng_adp, uint32_t *data);
	u32(*hal_trng_read_readybit)(hal_trng_adapter_t *ptrng_adp);
	u32(*hal_trng_read_parity_error_interrupt)(hal_trng_adapter_t *ptrng_adp);
	hal_status_t (*hal_trng_clear_interrupt)(hal_trng_adapter_t *ptrng_adp);
	u32(*hal_trng_read_data)(hal_trng_adapter_t *ptrng_adp);
	uint32_t reserved[16];  // reserved space for next ROM code version function table extending.

} hal_trng_func_stubs_t;

/*
 * @addtogroup ls_hal_trng_rom_func trng HAL ROM APIs.
 * @{
 */

void hal_rtl_trng_enable_128K(hal_trng_adapter_t *ptrng_adp);
void hal_rtl_trng_enable_32K(hal_trng_adapter_t *ptrng_adp);
void hal_rtl_trng_disable(hal_trng_adapter_t *prtc_adp);
void hal_rtl_trng_reg_irq(irq_handler_t handler, uint32_t *arg);
hal_status_t hal_rtl_trng_control_setting(hal_trng_adapter_t *ptrng_adp, hal_rng_reg_t *ptrng_reg);
hal_status_t hal_rtl_trng_init(hal_trng_adapter_t *ptrng_adp) ;
hal_status_t hal_rtl_trng_deinit(hal_trng_adapter_t *prtc_adp);
hal_status_t hal_rtl_trng_load_default(hal_trng_adapter_t *ptrng_adp, hal_rng_st_reg_t *ptrng_st_reg,  hal_rng_reg_t *ptrng_reg);
void hal_rtl_trng_reset(hal_trng_adapter_t *ptrng_adp);
void hal_rtl_trng_self_test_setting(hal_trng_adapter_t *ptrng_adp, hal_rng_st_reg_t *ptrng_st_reg);
hal_status_t hal_rtl_trng_interrupt_reg(hal_trng_adapter_t *ptrng_adp, uint32_t *data);
u32 hal_rtl_trng_read_readybit(hal_trng_adapter_t *ptrng_adp);
u32 hal_rtl_trng_read_parity_error_interrupt(hal_trng_adapter_t *ptrng_adp);
hal_status_t hal_rtl_trng_clear_interrupt(hal_trng_adapter_t *ptrng_adp);
u32 hal_rtl_trng_read_data(hal_trng_adapter_t *ptrng_adp);




/** @} */ /* End of group ls_hal_trng_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_trng */

#endif  // end of "#define _RTL8195BLP_trng_H_"

