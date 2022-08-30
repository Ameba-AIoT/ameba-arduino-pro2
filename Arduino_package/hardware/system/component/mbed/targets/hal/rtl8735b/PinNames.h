/**************************************************************************//**
 * @file     PinNames.h
 * @brief    Mbed HAL API pin naming definition.
 * @version  V1.00
 * @date     2020-10-19
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
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

#ifndef _PINNAMES_H_
#define _PINNAMES_H_

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif


#define RTL_PIN_PERI(FUN, IDX, SEL)     ((int)(((FUN) << 8) | ((IDX)<<4) | (SEL)))

#define RTL_GET_PERI_SEL(peri)          ((int)((peri)&0x0F))
#define RTL_GET_PERI_IDX(peri)          ((int)(((peri) >> 4)&0x0F))


#define RTL_PIN_FUNC(FUN, SEL)          ((int)(((FUN) << 7) | (SEL)))

typedef enum {
	PIN_INPUT   = 0,
	PIN_OUTPUT
} PinDirection;

typedef enum {
	PA_0  = PIN_A0,
	PA_1  = PIN_A1,
	PA_2  = PIN_A2,
	PA_3  = PIN_A3,
	PA_4  = PIN_A4,
	PA_5  = PIN_A5,

	PB_0  = PIN_B0,
	PB_1  = PIN_B1,
	PB_2  = PIN_B2,

	PC_0  = PIN_C0,
	PC_1  = PIN_C1,
	PC_2  = PIN_C2,
	PC_3  = PIN_C3,
	PC_4  = PIN_C4,
	PC_5  = PIN_C5,

	PD_0  = PIN_D0,
	PD_1  = PIN_D1,
	PD_2  = PIN_D2,
	PD_3  = PIN_D3,
	PD_4  = PIN_D4,
	PD_5  = PIN_D5,
	PD_6  = PIN_D6,
	PD_7  = PIN_D7,
	PD_8  = PIN_D8,
	PD_9  = PIN_D9,
	PD_10 = PIN_D10,
	PD_11 = PIN_D11,
	PD_12 = PIN_D12,
	PD_13 = PIN_D13,
	PD_14 = PIN_D14,
	PD_15 = PIN_D15,
	PD_16 = PIN_D16,
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	PD_17 = PIN_D17,
	PD_18 = PIN_D18,
	PD_19 = PIN_D19,
	PD_20 = PIN_D20,
#endif

	PE_0  = PIN_E0,
	PE_1  = PIN_E1,
	PE_2  = PIN_E2,
	PE_3  = PIN_E3,
	PE_4  = PIN_E4,
	PE_5  = PIN_E5,
	PE_6  = PIN_E6,
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	PE_7  = PIN_E7,
	PE_8  = PIN_E8,
	PE_9  = PIN_E9,
	PE_10 = PIN_E10,
#endif

	PF_0  = PIN_F0,
	PF_1  = PIN_F1,
	PF_2  = PIN_F2,
	PF_3  = PIN_F3,
	PF_4  = PIN_F4,
	PF_5  = PIN_F5,
	PF_6  = PIN_F6,
	PF_7  = PIN_F7,
	PF_8  = PIN_F8,
	PF_9  = PIN_F9,
	PF_10 = PIN_F10,
	PF_11 = PIN_F11,
	PF_12 = PIN_F12,
	PF_13 = PIN_F13,
	PF_14 = PIN_F14,
	PF_15 = PIN_F15,
	PF_16 = PIN_F16,
	PF_17 = PIN_F17,

	PS_0  = PIN_S0,
	PS_1  = PIN_S1,
	PS_2  = PIN_S2,
	PS_3  = PIN_S3,
	PS_4  = PIN_S4,
	PS_5  = PIN_S5,
	PS_6  = PIN_S6,


	// Arduino connector namings
	/*
	    A0          = PA_0,
	    A1          = PA_1,
	    A2          = PA_4,
	    A3          = PB_0,
	    A4          = PC_1,
	    A5          = PC_0,
	    D0          = PA_3,
	    D1          = PA_2,
	    D2          = PA_10,
	    D3          = PB_3,
	    D4          = PB_5,
	    D5          = PB_4,
	    D6          = PB_10,
	    D7          = PA_8,
	    D8          = PA_9,
	    D9          = PC_7,
	    D10         = PB_6,
	    D11         = PA_7,
	    D12         = PA_6,
	    D13         = PA_5,
	    D14         = PB_9,
	    D15         = PB_8,
	*/

	// Not connected
	NC = (uint32_t)0xFFFFFFFF
} PinName;

typedef enum {
	PullNone    = 0,
	PullUp      = 1,
	PullDown    = 2,
	OpenDrain   = 3,
	PullDefault = PullNone
} PinMode;

#if 0
#define PORT_NUM(pin)       (((uint8_t)(pin) >> 5) & 0x7)
#define PIN_NUM(pin)        ((uint8_t)(pin) & 0x1F)
#endif

#ifdef __cplusplus
}
#endif

#endif
