/**************************************************************************//**
 * @file     gpio_irq_api.c
 * @brief    This file implements the mbed HAL API for GPIO pin with interrupt function.
 *
 * @version  V1.00
 * @date     2017-07-24
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

#include "gpio_irq_api.h"
#include "gpio_irq_ex_api.h"

// The following 4 global variables are declared in gpio_api.c
extern hal_aon_gpio_comm_adapter_t mbd_aon_gpio_comm_adp;
extern hal_pon_gpio_comm_adapter_t mbd_pon_gpio_comm_adp;
extern hal_gpio_comm_adapter_t mbd_gpio_comm_adp;

static uint32_t is_mbd_aon_gpio_comm_inited1;
static uint32_t is_mbd_pon_gpio_comm_inited1;
static uint32_t is_mbd_gpio_comm_inited1;

/**
  * @brief  Initializes the GPIO device interrupt mode, include mode/trigger/polarity registers.
  * @param  obj: gpio irq object define in application software.
  * @param  pin: PinName according to pinmux spec.
  * @note this API only works for Port A pins
  * @param  handler: Interrupt handler to be assigned to the specified pin.
  * @param  id: handler id.
  * @retval none
  */
int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id)
{
	u8 ret;
	uint8_t port_idx = PIN_NAME_2_PORT(pin);
	// Weide: No longer required, we can pass pin_name, e.g. PIN_A1, directly into hal_pinmux_register() if required to do pinmux registration here.
	/*_pin_t pin_list[2];
	pin_list[0].pin_name = pin;
	pin_list[1].pin_name = 0xFF;*/

	if (port_idx >= PORT_MAX_NUM) {
		DBG_GPIO_ERR("Invalid GPIO port(%u)\n", port_idx);
		return HAL_ERR_PARA;
	}

	if (port_idx == PORT_A && !is_mbd_aon_gpio_comm_inited1) {
		//dbg_printf("AON GPIO comm init done\r\n");
		hal_aon_gpio_comm_init(&mbd_aon_gpio_comm_adp);
		is_mbd_aon_gpio_comm_inited1 = 1;

	} else if (port_idx == PORT_F && !is_mbd_pon_gpio_comm_inited1) {
		//dbg_printf("PON GPIO comm init done\r\n");
		hal_pon_gpio_comm_init(&mbd_pon_gpio_comm_adp);
		is_mbd_pon_gpio_comm_inited1 = 1;

	} else if ((port_idx == PORT_B && !is_mbd_gpio_comm_inited1) ||
			   (port_idx == PORT_C && !is_mbd_gpio_comm_inited1) ||
			   (port_idx == PORT_D && !is_mbd_gpio_comm_inited1) ||
			   (port_idx == PORT_E && !is_mbd_gpio_comm_inited1)) {

		//dbg_printf("GPIO comm init done\r\n");
		hal_gpio_comm_init(&mbd_gpio_comm_adp);
		is_mbd_gpio_comm_inited1 = 1;
	}

	// Weide: hal_pinmux_register() will be handled in hal_gpio_irq_init()
	/*ret = hal_pinmux_register((io_pin_t *)&pin_list[0], (PID_GPIO));
	if (ret != HAL_OK) {
	    DBG_GPIO_ERR ("gpio_irq_init: Pin Reg Failed(0x%x)\r\n", ret);
	    return ret;
	}*/

	ret = hal_gpio_irq_init(&obj->gpio_irq_adp, pin, (gpio_irq_callback_t)handler, id);
	if (ret == HAL_OK) {
		dbg_printf("GPIO IRQ init OK!\r\n");
		return 0;
	} else {
		dbg_printf("GPIO IRQ init FAIL!\r\n");
		return -1;
	}
}

/**
  * @brief  Deinitializes the GPIO device interrupt mode, include mode/trigger/polarity registers.
  * @param  obj: gpio irq object define in application software.
  * @note this API only works for Port A pins
  * @retval none
  */
void gpio_irq_free(gpio_irq_t *obj)
{
	// Weide: No longer required, we can pass pin_name, e.g. PIN_A1, directly into hal_pinmux_register() if required to do pinmux un-registration here.
	/*io_pin_t pin_list[2];

	pin_list[0].pin_name = obj->gpio_irq_adp.pin_name;
	pin_list[1].pin_name = 0xFF;*/
	// Weide: hal_pinmux_unregister() will be handled in hal_gpio_irq_deinit()
	//hal_pinmux_unregister((io_pin_t *)&pin_list[0], PID_GPIO);
	//hal_gpio_irq_deinit(&obj->gpio_irq_adp); // why got repeat one?
}

/**
  * @brief  Enable/Disable gpio interrupt.
  * @param  obj: gpio irq object define in application software.
  * @param  event: gpio interrupt event, this parameter can be one of the following values:
  *     @arg IRQ_RISE: rising edge interrupt event
  *     @arg IRQ_FALL: falling edge interrupt event
  *     @arg IRQ_LOW: low level interrupt event
  *     @arg IRQ_HIGH: high level interrupt event
  *     @arg IRQ_NONE: no interrupt event
  * @param  enable: this parameter can be one of the following values:
  *     @arg 0 disable gpio interrupt
  *     @arg 1 enable gpio interrupt
  * @retval none
  */
void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable)
{
	gpio_int_trig_type_t int_type;

	int_type = (gpio_int_trig_type_t)event;

	if (int_type > IRQ_FALL_RISE) {
		DBG_GPIO_ERR("Invalid GPIO IRQ Event(%u)\n", event);
		return;
	}

	hal_gpio_irq_set_trig_type(&obj->gpio_irq_adp, int_type);

	if (enable) {
		hal_gpio_irq_enable(&obj->gpio_irq_adp);
	} else {
		hal_gpio_irq_disable(&obj->gpio_irq_adp);
	}

}

/**
  * @brief  Enable gpio interrupt.
  * @param  obj: gpio irq object define in application software.
  * @retval none
  */
void gpio_irq_enable(gpio_irq_t *obj)
{
	hal_gpio_irq_enable(&obj->gpio_irq_adp);
}

/**
  * @brief  Disable gpio interrupt.
  * @param  obj: gpio irq object define in application software.
  * @retval none
  */
void gpio_irq_disable(gpio_irq_t *obj)
{
	hal_gpio_irq_disable(&obj->gpio_irq_adp);
}

/**
  * @brief  Deinitializes the GPIO device interrupt mode, include mode/trigger/polarity registers.
  * @param  obj: gpio irq object define in application software.
  * @retval none
  */
void gpio_irq_deinit(gpio_irq_t *obj)
{
	uint8_t port_idx = PIN_NAME_2_PORT(obj->gpio_irq_adp.pin_name);
	dbg_printf("port_idx: %x\r\n", port_idx);

	if (port_idx == PORT_A && is_mbd_aon_gpio_comm_inited1) {
		//dbg_printf("AON GPIO comm DEinit done\r\n");
		is_mbd_aon_gpio_comm_inited1 = 0;

	} else if (port_idx == PORT_F && is_mbd_pon_gpio_comm_inited1) {
		//dbg_printf("PON GPIO comm DEinit done\r\n");
		is_mbd_pon_gpio_comm_inited1 = 0;

	} else if ((port_idx == PORT_B && is_mbd_gpio_comm_inited1) |
			   (port_idx == PORT_C && is_mbd_gpio_comm_inited1) |
			   (port_idx == PORT_D && is_mbd_gpio_comm_inited1) |
			   (port_idx == PORT_E && is_mbd_gpio_comm_inited1)) {

		//dbg_printf("GPIO comm DEinit done\r\n");
		is_mbd_gpio_comm_inited1 = 0;
	}

	hal_gpio_irq_deinit(&obj->gpio_irq_adp);
}

/**
  * @brief  Sets pull type to the selected interrupt pin.
  * @param  obj: gpio irq object define in application software.
  * @param  pull_type: this parameter can be one of the following values:
  *     @arg PullNone: HighZ, user can input high or low use this pin
  *     @arg OpenDrain(is OpenDrain output): no pull + OUT + GPIO[gpio_bit] = 0
  *     @arg PullDown: pull down
  *     @arg PullUp: pull up
  * @retval none
  */
void gpio_irq_pull_ctrl(gpio_irq_t *obj, PinMode pull_type)
{
	pin_pull_type_t pull_ctrl;

	switch (pull_type) {
	case PullNone:
	case PullDown:
	case PullUp:
		pull_ctrl = pull_type;
		break;

	case OpenDrain:/* No driver -> Output Low */
	default:
		pull_ctrl = Pin_PullNone;
		break;
	}

	hal_gpio_pull_ctrl(obj->gpio_irq_adp.pin_name, pull_ctrl);
}

/**
  * @brief  Enable the specified gpio interrupt event.
  * @param  obj: gpio irq object define in application software.
  * @param  event: gpio interrupt event, this parameter can be one of the following values:
  *     @arg IRQ_RISE: rising edge interrupt event
  *     @arg IRQ_FALL: falling edge interrupt event
  *     @arg IRQ_LOW: low level interrupt event
  *     @arg IRQ_HIGH: high level interrupt event
  *     @arg IRQ_NONE: no interrupt event
  * @retval none
  */
void gpio_irq_set_event(gpio_irq_t *obj, gpio_irq_event event)
{
	gpio_int_trig_type_t int_type;

	int_type = (gpio_int_trig_type_t)event;
	if (int_type > IRQ_FALL_RISE) {
		DBG_GPIO_ERR("Invalid GPIO IRQ Event(%u)\n", event);
		return;
	}

	hal_gpio_irq_set_trig_type(&obj->gpio_irq_adp, int_type);
}

/**
 *  @brief To enables or disable the debounce function of the given GPIO IRQ pin.
 *         The debounce resource(circuit) is limited, not all GPIO pin
 *         can has debounce function.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *  @param[in]  debounce_us  The time filter for the debounce, in micro-second.
 *                           But the time resolution is 31.25us (1/32K) and the
 *                           maximum time is 512 ms.
 * @param[in]  enable: this parameter can be one of the following values:
 *     @arg 0 disable gpio debounce interrupt
 *     @arg 1 enable gpio debounce interrupt
 *  @return     0:  Setting Succeed.
 *  @return     -1:  Setting Fail.
 */
int gpio_irq_debounce_set(gpio_irq_t *obj, uint32_t debounce_us, u8 enable)
{
	u8 ret = 0;
	if (enable) {
		ret = hal_gpio_irq_debounce_enable(&obj->gpio_irq_adp, debounce_us);
		if (ret == HAL_OK) {
			return 0;
		} else {
			return -1;
		}
	} else {
		hal_gpio_irq_debounce_disable(&obj->gpio_irq_adp);
		return 0;
	}
}

/**
  * @brief  Reads the input level of the given GPIO IRQ pin.
  *         If a debounce function is enabled on this GPIO IRQ pin,
  *         then reads the de-bounced input level.
  * @param  obj: gpio irq object define in application software.
  * @retval Value of the GPIO IRQ pin - Low = 0; High = 1
  */
int gpio_irq_read(gpio_irq_t *obj)
{
	return hal_gpio_irq_read(&obj->gpio_irq_adp);
}
