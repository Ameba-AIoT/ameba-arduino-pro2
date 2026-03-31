/**************************************************************************//**
 * @file     gpio_api.c
 * @brief    This file implements the GPIO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-03
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
#include "objects.h"
#include "pinmap.h"
#include "gpio_api.h"
#include "hal_gpio.h"

/* map mbed pin mode definition to RTK HAL pull control type */
#define MAX_PIN_MODE            4

const uint8_t mbed_pinmode_map[MAX_PIN_MODE] = {
	Pin_PullNone,       // 0: PullNone
	Pin_PullUp,         // 1: PullUp
	Pin_PullDown,       // 2: PullDown
	Pin_PullNone        // 3: OpenDrain
};

hal_aon_gpio_comm_adapter_t mbd_aon_gpio_comm_adp;
hal_pon_gpio_comm_adapter_t mbd_pon_gpio_comm_adp;
hal_gpio_comm_adapter_t mbd_gpio_comm_adp;

uint32_t is_mbd_aon_gpio_comm_inited;
uint32_t is_mbd_pon_gpio_comm_inited;
uint32_t is_mbd_gpio_comm_inited;

/**
  * @brief  Set the given pin as GPIO.
  * @param  pin: PinName according to pinmux spec.
  * @retval The given pin with GPIO function
  */
uint32_t gpio_set(PinName pin)
{
	uint32_t ip_pin;

	DIAG_ASSERT(pin != (PinName)NC);
	pin_function(pin, 0);
	ip_pin = pin;

	return ip_pin;
}

/**
  * @brief  Initializes the GPIO device, include mode/direction/pull control registers.
  * @param  obj: gpio object define in application software.
  * @param  pin: PinName according to pinmux spec.
  * @retval none
  */
void gpio_init(gpio_t *obj, PinName pin)
{
	uint8_t port_idx = PIN_NAME_2_PORT(pin);

	// Weide commented out because only when initializing GPIO as an IRQ pin will the *_comm_adp be needed

	/*if (!is_mbd_gpio_comm_inited) {
	    if (port_idx == PORT_A) {
	        hal_aon_gpio_comm_init (&mbd_aon_gpio_comm_adp);
	    } else if (port_idx == PORT_F) {
	        hal_pon_gpio_comm_init (&mbd_pon_gpio_comm_adp);
	    } else if (port_idx == PORT_B | port_idx == PORT_C | port_idx == PORT_D | port_idx == PORT_E) {
	        hal_gpio_comm_init (&mbd_gpio_comm_adp);
	    } else {
	        DBG_GPIO_ERR ("Invalid GPIO port(%u)\n", port_idx);
	    }
	    is_mbd_gpio_comm_inited = 1;
	}*/

	hal_gpio_init(&obj->adapter, pin);
}

/**
  * @brief  Set GPIO mode.
  * @param  obj: gpio object define in application software.
  * @param  mode: this parameter can be one of the following values:
  *     @arg PullNone: HighZ, user can input high or low use this pin
  *     @arg OpenDrain(is OpenDrain output): no pull + OUT + GPIO[gpio_bit] = 0
  *     @arg PullDown: pull down
  *     @arg PullUp: pull up
  * @retval none
  */
void gpio_mode(gpio_t *obj, PinMode mode)
{
	pin_pull_type_t pull_type;

	if (mode < MAX_PIN_MODE) {
		pull_type = mbed_pinmode_map[mode];
	} else {
		// invalid pin mode
		pull_type = Pin_PullNone;
	}

	hal_gpio_pull_ctrl(obj->adapter.pin_name, pull_type);

	if (mode == OpenDrain) {
		/* our IO pad didn't support open-drain,
		 * however we use normal GPIO output pin to simulate it */
		hal_gpio_set_dir(&obj->adapter, GPIO_OUT);
		hal_gpio_write(&obj->adapter, 0);
	}
}

/**
  * @brief  Set GPIO direction.
  * @param  obj: gpio object define in application software.
  * @param  direction: this parameter can be one of the following values:
  *     @arg PIN_INPUT: this pin is input
  *     @arg PIN_OUTPUT: this pin is output
  * @retval none
  */
void gpio_dir(gpio_t *obj, PinDirection direction)
{
	hal_gpio_set_dir(&obj->adapter, direction);
}

/**
  * @brief  Set GPIO direction.
  * @param  obj: gpio object define in application software.
  * @param  direction: this parameter can be one of the following values:
  *     @arg PIN_INPUT: this pin is input
  *     @arg PIN_OUTPUT: this pin is output
  * @retval none
  */
void gpio_change_dir(gpio_t *obj, PinDirection direction)
{
	hal_gpio_set_dir(&obj->adapter, direction);
}

/**
  * @brief  Sets value to the selected output port pin.
  * @param  obj: gpio object define in application software.
  * @param  value: specifies the value to be written to the selected pin
  *     This parameter can be one of the following values:
  *     @arg 0: Pin state set to low
  *     @arg 1: Pin state set to high
  * @retval none
  */
void gpio_write(gpio_t *obj, int value)
{
	hal_gpio_write(&obj->adapter, value);
}

/**
  * @brief  Sets value to the selected output port pin.
  * @param  obj: gpio object define in application software.
  * @param  value: specifies the value to be written to the selected pin
  *     This parameter can be one of the following values:
  *     @arg 0: Pin state set to low
  *     @arg 1: Pin state set to high
  * @retval none
  */
void gpio_direct_write(gpio_t *obj, BOOL value)
{
	hal_gpio_write(&obj->adapter, value);
}

/**
  * @brief  Reads the specified gpio port pin.
  * @param  obj: gpio object define in application software.
  * @retval state of the specified gpio port pin
  *          - 1: pin state is high
  *          - 0: pin state is low
  */
int gpio_read(gpio_t *obj)
{
	return hal_gpio_read(&obj->adapter);
}

/**
  * @brief  Sets pull type to the selected pin.
  * @param  obj: gpio object define in application software.
  * @param  pull_type: this parameter can be one of the following values:
  *     @arg PullNone: HighZ, user can input high or low use this pin
  *     @arg OpenDrain(is OpenDrain output): no pull + OUT + GPIO[gpio_bit] = 0
  *     @arg PullDown: pull down
  *     @arg PullUp: pull up
  * @retval none
  */
void gpio_pull_ctrl(gpio_t *obj, PinMode pull_type)
{
	pin_pull_type_t io_pull_type;

	if (pull_type < MAX_PIN_MODE) {
		io_pull_type = (pin_pull_type_t)mbed_pinmode_map[pull_type];
	} else {
		// invalid pin mode
		io_pull_type = Pin_PullNone;
	}

	hal_gpio_pull_ctrl(obj->adapter.pin_name, io_pull_type);
}

/**
  * @brief  Deinitializes the GPIO device, include mode/direction/pull control registers.
  * @param  obj: gpio object define in application software.
  * @retval none
  */
void gpio_deinit(gpio_t *obj)
{
	hal_gpio_deinit(&obj->adapter);
}


#if 0
/**
  * @brief  Sets schmitt trigger on/off control on the given GPIO pin .
  * @param  pin: PinName according to pinmux spec.
  * @param  ctrl  The on/off control:
  *                      - 0: disable the schmitt trigger.
  *                      - 1: enable the schmitt trigger.
  * @param  v_h3l1  The GPIO Group Voltage Select:
  *                      - 0: 1.8V.
  *                      - 1: 3V.
  * @retval none
  */
void gpio_schmitt_ctrl(PinName pin, BOOLEAN ctrl, uint8_t v_h3l1)
{
	hal_gpio_schmitt_ctrl(pin, ctrl, v_h3l1);
}

#endif
