/** mbed Microcontroller Library
  ******************************************************************************
  * @file    analogin_api.c
  * @author
  * @version V1.0.0
  * @date    2017-08-01
  * @brief   This file provides mbed API for ADC.
  ******************************************************************************
  * @attention
  *
  * Copyright(c) 2017 - 2022 Realtek Corporation. All rights reserved.
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

#include "objects.h"
#include "PinNames.h"
#include "analogin_api.h"

#include "pinmap.h"
#include "analogin_ex_api.h"
#include "platform_stdlib.h"
#include "hal_adc.h"
#include "hal_otp.h"
#include "hal_otp_nsc.h"



#if (defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1))

extern void *memset(void *dst0, int Val, size_t length);
static uint8_t analogin_init_flag = 0;
static hal_adc_adapter_t analogin_con_adpt;
static hal_gdma_adaptor_t analogin_dma_adpt;


static const PinMap PinMap_analogin[] = {
	{PF_0,  RTL_PIN_PERI(PID_ADC0, 0, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
	{PF_1,  RTL_PIN_PERI(PID_ADC1, 1, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
	{PF_2,  RTL_PIN_PERI(PID_ADC2, 2, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
	{PF_3,  RTL_PIN_PERI(PID_ADC3, 3, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
	{PA_0,  RTL_PIN_PERI(PID_COMP_ADC, 4, 0), RTL_PIN_FUNC(PID_COMP_ADC, 0)},
	{PA_1,  RTL_PIN_PERI(PID_COMP_ADC, 5, 0), RTL_PIN_FUNC(PID_COMP_ADC, 0)},
	{PA_2,  RTL_PIN_PERI(PID_COMP_ADC, 6, 0), RTL_PIN_FUNC(PID_COMP_ADC, 0)},
	{PA_3,  RTL_PIN_PERI(PID_COMP_ADC, 7, 0), RTL_PIN_FUNC(PID_COMP_ADC, 0)},
	{NC,    NC,     0}
};

/**
  * @brief  Initializes the ADC device, include clock/function/ADC registers.
  * @param  obj: adc object define in application software.
  * @param  pin: adc PinName according to pinmux spec.
  * @retval none
  */
void analogin_init(analogin_t *obj, PinName pin)
{
	uint32_t analogin_peri = (uint32_t)pinmap_peripheral(pin, PinMap_analogin);
	obj->idx = RTL_GET_PERI_IDX(analogin_peri);

	if (!analogin_init_flag) {
		memset(&analogin_con_adpt, 0x00, sizeof(analogin_con_adpt));
		hal_adc_load_default(&analogin_con_adpt);
		/* set pin enable flag */
		analogin_con_adpt.plft_dat.pin_en.w |= ((uint32_t)0x1 << obj->idx);
		if (hal_adc_init(&analogin_con_adpt) != HAL_OK) {
			printf("analogin initialization failed\n");
		} else {
			analogin_init_flag = 1;
			hal_delay_ms(20);
			hal_adc_set_in_type_all((hal_adc_adapter_t *)&analogin_con_adpt, HP_ADC_INPUT_ALL_SINGLE);
			hal_adc_set_cvlist((hal_adc_adapter_t *)&analogin_con_adpt, (uint8_t *)&analogin_init_flag, 1);
		}
	} else {
		/* module initialized but pin was NOT */
		if ((analogin_con_adpt.plft_dat.pin_en.w & ((uint32_t)0x1 << obj->idx)) == 0) {
			printf("module initialized; now initializing pin for ADC%d\r\n", obj->idx);
			analogin_con_adpt.plft_dat.pin_en.w |= ((uint32_t)0x1 << obj->idx);
			hal_adc_pin_init(&analogin_con_adpt);

		}

	}
}

/**
  * @brief  Deinitializes the ADC device, include clock/function/ADC registers.
  * @param  obj: none
  * @retval none
  */
void analogin_deinit(analogin_t *obj)
{
	if (analogin_init_flag) {
		/* all pin should be turn off therefore module should be turn off, too */
		hal_adc_deinit(&analogin_con_adpt);
		analogin_init_flag = 0;
	} else {
		dbg_printf("analogin module has been deinited.  \r\n");
	}
}

/**
  * @brief  Deinitializes the ADC pin
  * @param  obj: adc object define in application software.
  * @retval none
  */
void analogin_pin_deinit(analogin_t *obj)
{
	hal_status_t retv = 0x0;

	if (analogin_init_flag) {
		retv = hal_adc_pin_deinit(&analogin_con_adpt);
		if (retv == HAL_OK) {
			analogin_con_adpt.plft_dat.pin_en.w &= (~((uint32_t)1 << obj->idx));
		}
	} else {
		dbg_printf("analogin module has been deinited.  \r\n");
	}

}

/**
  * @brief  Reads data from the specified adc channel fifo.
  * @param  obj: adc object define in application software.
  * @retval : adc channel data(float)
  */
float analogin_read(analogin_t *obj)
{
	uint16_t anain16;
	uint16_t ana_full;
	float retv_ana;


	anain16 = hal_adc_single_read(&analogin_con_adpt, obj->idx);
	ana_full = 0xFFF;

	retv_ana = anain16 / ana_full;

	return retv_ana;
}

/**
  * @brief  Reads data from the specified adc channel fifo.
  * @param  obj: adc object define in application software.
  * @retval : 16bit adc channel data(int)
  */
uint16_t analogin_read_u16(analogin_t *obj)
{
	uint16_t anain16;
	uint16_t data_ideal_val;
	uint32_t data_diff;

	anain16 = hal_adc_single_read(&analogin_con_adpt, obj->idx);
	return anain16;
}

/**
  * @brief  Set user callback function
  * @param  obj: adc object define in application software.
  * @param  analogin_cb:  callback type
  * @param  analogin_callback:  callback function
  * @retval : none
  */
void analogin_set_user_callback(analogin_t *obj, AnalogInCallback analogin_cb, void(*analogin_callback)(void *))
{
	switch (analogin_cb) {
	case ANALOGIN_RX_DMA_COMPLETE:
		analogin_con_adpt.usr_cb.rxc.cb = analogin_callback;
		break;
	default:
		break;
	}
}

/**
  * @brief  Clear user callback function
  * @param  obj: adc object define in application software.
  * @param  analogin_cb:  callback type
  * @retval : none
  */
void analogin_clear_user_callback(analogin_t *obj, AnalogInCallback analogin_cb)
{
	switch (analogin_cb) {
	case ANALOGIN_RX_DMA_COMPLETE:
		analogin_con_adpt.usr_cb.rxc.cb = NULL;
		break;
	default:
		break;
	}
}

/**
  * @brief  Analog input transfer by DMA
  * @param  obj: adc object define in application software.
  * @param  buf:  data buffer.
  * @param  length:  data length.
  * @retval : 0: success, 1: failed
  */
uint8_t analogin_read_u16_dma(analogin_t *obj, uint16_t *buf, uint16_t length)
{
	uint8_t ana_idx;

	ana_idx = obj->idx;
	hal_adc_set_cvlist(&analogin_con_adpt, &ana_idx, 1);
	hal_adc_dma_init(&analogin_con_adpt, &analogin_dma_adpt);
	if (hal_adc_read_dma(&analogin_con_adpt, length, buf, ADCAutoMod) != HAL_OK) {
		return 1;
	}

	return 0;
}

/**
  * @brief  Read OTP ADC Internal R Data
  * @param  NA
  * @retval : ADC Internal R Data
  */
uint16_t analogin_read_intl_r(void)
{
	return (uint16_t)hal_adc_rd_inter_r();
}


#endif //end of #if (defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1))

