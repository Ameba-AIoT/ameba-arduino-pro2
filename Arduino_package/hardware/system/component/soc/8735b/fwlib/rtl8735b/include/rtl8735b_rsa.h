/**************************************************************************//**
 * @file     rtl8735b_rsa.h
 * @brief    The HAL related definition and macros for the RSA device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2021-03-26
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

#ifndef _RTL8735B_RSA_H_
#define _RTL8735B_RSA_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "rtl8735b_rsa_type.h"


typedef enum {
	RSA_KEY_SEL_2048 = 0,
	RSA_KEY_SEL_1024 = 2,
	RSA_KEY_SEL_3072 = 5,
} RSA_KEY_SEL_TYPE;

typedef enum {
	RSA_ENDIAN_LITTLE = 0,
	RSA_ENDIAN_BIG,
} RSA_ENDIAN_TYPE;

typedef enum {
	RSA_ERR_NONE            = 0x0,
	RSA_ERR_EXP             = -0x1,
	RSA_ERR_M_RANGE         = -0x3,
	RSA_ERR_NPINV           = -0x5,
	RSA_ERR_UNFINISHED      = -0x7,
} RSA_ERR_CODE;

typedef struct {
	uint32_t M[96];       // 0x000-0x17F, message
	uint32_t X[96];       // 0x180-0x2FF, result
	uint32_t RSVD[96];    // 0x300-0x47F, reserved
	uint32_t N[96];       // 0x480-0x5FF, modular value
	uint32_t e[96];       // 0x600-0x77F, exponent
} RSA_DataBuffer_Type;


typedef struct {
	uint32_t M[96];       // 0x000-0x17F, message
	uint32_t X[96];       // 0x180-0x2FF, result
	uint32_t RSVD[96];    // 0x300-0x47F, reserved
	uint32_t N[96];       // 0x480-0x5FF, modular value
	uint32_t e[96];       // 0x600-0x77F, exponent
	uint32_t rsvd0[480];
	union { /* 0xF00 */
		__IO uint32_t Mode_control;
		struct {
			__IO uint32_t Key_size_sel: 3;  /* 0x0: 2048, 0x2: 1024, 0x5: 3072 */
			__IO uint32_t Byte_swap: 1;     /* Byte swapping in a word, 0x0: little, 0x1: big */
			__IO uint32_t Endian: 1;        /* 0x0: little, 0x1: big */
			__IO uint32_t Reserved: 27;
		} Mode_control_field;
	};

	__IO uint32_t rsvd1; // 0xF04

	union { /* 0xF08 */
		__IO uint32_t Start_and_interrupt_control;
		struct {
			__IO uint32_t Interrupt_status_clear: 1; /* 0x0: no interrupt, 0x1: interrupt active, Write 1 to clear interrupt */
			__IO uint32_t Interrupt_enable: 1;       /* Enable interrupt */
			__IO uint32_t Reserved: 29;
			__IO uint32_t Go: 1;                     /* Write 1 to start engine */
		} Start_and_interrupt_control_field;
	};

	union { /* 0xF0C */
		__IO uint32_t Status;
		struct {
			__I  uint32_t rsvd0: 4;
			__I  uint32_t RSA_finish: 1;    /* RSA finish */
			__I  uint32_t rsvd1: 1;
			__I  uint32_t Exp_error: 1;     /* Exponent error (e.g. all zero)  */
			__I  uint32_t M_range_error: 1; /* M > N error */
			__I  uint32_t rsvd2: 4;
			__I  uint32_t NPINV_error: 1;   /* NPINV generate error */
			__I  uint32_t rsvd3: 19;
		} Status_field;
	};

	__IO uint32_t rsvd2[6]; // 0xF10 ~ 0xF28

	union { /* 0xF2C */
		__IO uint32_t  Clock_gating_control;
		struct {
			__IO uint32_t Clock_getting_enable : 1; /* Enable auto clock gating */
			__IO uint32_t rsvd: 31;
		} Clock_gating_control_field;
	};
	uint32_t reserved[5];
} HW_RSA_TypeDef;


/**
  * \brief  The data structure to handle a PWM device, it includes the configuration, register base address
          and interrupt call back functions.
*/
typedef struct hal_rsa_adapter_s {
	RSA_TypeDef *base_addr;      /*!< The PWM registers base address */
	RSA_KEY_SEL_TYPE key_type;
	RSA_ENDIAN_TYPE byte_endian;
	RSA_ENDIAN_TYPE endian;
	RSA_ERR_CODE status;
	uint32_t *result;
	uint32_t *Message;
	uint32_t *Exponent;
	uint32_t *Modulus;
	uint8_t rsa_key_word_cnt;
	uint8_t exp_word_cnt;
	uint32_t reserved[2];
} hal_rsa_adapter_t, *phal_rsa_adapter_t;


/**
  \brief  The data structure of the stubs function for the PWM HAL functions in ROM
*/
typedef struct hal_rsa_func_stubs_s {
	phal_rsa_adapter_t *rsa_comm_adp;

	int (*hal_rsa_set_key_size)(hal_rsa_adapter_t *rsa_adp);
	int (*hal_rsa_set_byte_swap)(hal_rsa_adapter_t *rsa_adp);
	int (*hal_rsa_set_endian)(hal_rsa_adapter_t *rsa_adp);
	int (*hal_rsa_set_operands)(hal_rsa_adapter_t *rsa_adp);
	RSA_ERR_CODE(*hal_rsa_check_status)(hal_rsa_adapter_t *rsa_adapter);
	RSA_ERR_CODE(*hal_rsa_compute)(hal_rsa_adapter_t *rsa_adp, uint32_t *result);
	int (*hal_rsa_process)(hal_rsa_adapter_t *rsa_adp, uint32_t *result);
	void (*hal_rsa_clock_init)(int en);
	int (*hal_rsa_config)(hal_rsa_adapter_t *rsa_adp, RSA_KEY_SEL_TYPE type, RSA_ENDIAN_TYPE byte_endian, RSA_ENDIAN_TYPE endian,
						  uint32_t *M, uint32_t *e, uint32_t *N, uint32_t exp_word_cnt);

	uint32_t reserved[6];  // reserved space for next ROM code version function table extending.

} hal_rsa_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

int hal_rtl_rsa_set_key_size(hal_rsa_adapter_t *rsa_adp);
int hal_rtl_rsa_set_byte_swap(hal_rsa_adapter_t *rsa_adp);
int hal_rtl_rsa_set_endian(hal_rsa_adapter_t *rsa_adp);
int hal_rtl_rsa_set_operands(hal_rsa_adapter_t *rsa_adp);
RSA_ERR_CODE hal_rtl_rsa_check_status(hal_rsa_adapter_t *rsa_adp);
RSA_ERR_CODE hal_rtl_rsa_compute(hal_rsa_adapter_t *rsa_adp, uint32_t *result);
int hal_rtl_rsa_process(hal_rsa_adapter_t *rsa_adp, uint32_t *result);
void hal_rtl_rsa_clock_init(int en);
int hal_rtl_rsa_config(hal_rsa_adapter_t *rsa_adp, RSA_KEY_SEL_TYPE type, RSA_ENDIAN_TYPE byte_endian, RSA_ENDIAN_TYPE endian,
					   uint32_t *M, uint32_t *e, uint32_t *N, uint32_t exp_word_cnt);




/** @} */ /* End of group hs_hal_pwm_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group hs_hal_pwm */

#endif  // end of "#define _RTL8195BH_PWM_H_"

