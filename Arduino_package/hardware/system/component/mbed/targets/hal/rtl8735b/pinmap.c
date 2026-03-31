/**************************************************************************//**
 * @file     pinmap.c
 * @brief    This file implements the Mbed HAL API for IO pin function control.
 *
 * @version  V1.00
 * @date     2017-05-03
 *
 * @note
 *
 ******************************************************************************
 * @attention
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
 ******************************************************************************
 */
//#include "mbed_assert.h"
#include "objects.h"
#include "pinmap.h"
//#include "error.h"
#include "hal_gpio.h"

/* map mbed pin mode definition to RTK HAL pull control type */
#define MAX_PIN_MODE            4

extern const uint8_t mbed_pinmode_map[];

/**
 * Configure pin enable and function
 */
void pin_function(PinName pin, int function)
{
	// MBED_ASSERT(pin != (PinName)NC);
	//1 Our HAL API cannot support  to configure the pin function by this way
	/* the pin function (pin mux) is depends on each IP On/Off and priority, so we cannot
	   set the pin function directly */
}

/**
 * Configure pin pull-up/pull-down
 */
void pin_mode(PinName pin, PinMode mode)
{
	pin_pull_type_t pull_type;

//    MBED_ASSERT(pin != (PinName)NC);

	if (mode >= MAX_PIN_MODE) {
		mode = PullNone;
	}
	pull_type = mbed_pinmode_map[(uint8_t)mode];
	hal_gpio_pull_ctrl(pin, pull_type);
}




