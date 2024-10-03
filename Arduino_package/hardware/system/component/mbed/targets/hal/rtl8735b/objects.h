/**************************************************************************//**
 * @file     objects.h
 * @brief    Mbed HAL API Object structure definition.
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
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
//#include "PeripheralNames.h"
#include "PinNames.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(CONFIG_GPIO_EN) && (CONFIG_GPIO_EN == 1)
struct gpio_irq_s {
	hal_gpio_irq_adapter_t gpio_irq_adp;
};

typedef struct gpio_irq_s gpio_irq_t;

struct gpio_s {
	hal_gpio_adapter_t adapter;
};

typedef struct gpio_s gpio_t;

struct port_s {
	hal_gpio_port_adapter_t hal_port;
};
#endif  // end of "#ifdef CONFIG_GPIO_EN"


#if defined(CONFIG_UART_EN) && (CONFIG_UART_EN == 1)
struct serial_s {
	hal_uart_adapter_t uart_adp;
	hal_gdma_adaptor_t tx_gdma;
	hal_gdma_adaptor_t rx_gdma;
	uint32_t irq_en;
	void *tx_irq_handler;
	uint32_t tx_irq_id;
};
#endif  // end of "#ifdef CONFIG_UART_EN"


#if defined(CONFIG_PWM_EN) && (CONFIG_PWM_EN == 1)
struct pwmout_s {
	uint8_t pwm_idx;
	uint8_t pin_sel;
	uint8_t is_init; // 1: Initialize Success
	uint32_t period;
	uint32_t pulse;
	uint32_t offset_us;
	uint32_t polarity;
	hal_pwm_adapter_t  pwm_hal_adp;
	hal_gdma_adaptor_t pwm_gdma_adp;
};
#endif

#if defined(CONFIG_I2C_EN) && (CONFIG_I2C_EN == 1)
struct i2c_s {
	hal_i2c_adapter_t i2c_adp;
};
#endif

#if defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1)
struct analogin_s {
	uint8_t idx;
};
#endif

#if defined(CONFIG_GTIMER_EN) && (CONFIG_GTIMER_EN == 1)
struct gtimer_s {
	hal_timer_adapter_t timer_adp;
};
#endif

#if defined(CONFIG_I2S_EN) && (CONFIG_I2S_EN == 1)
struct i2s_s {
	hal_i2s_adapter_t i2s_adapter;
	BOOL i2s_initialized;
};

#endif

#if defined(CONFIG_PCM_EN) && (CONFIG_PCM_EN == 1)
struct pcm_s {
	hal_pcm_adapter_t pcm_adapter;
};

#endif


#if defined(CONFIG_DAC_EN) && (CONFIG_DAC_EN == 1)
struct dac_s {
	void *dummy;
};
#endif


#if defined(CONFIG_GDMA_EN) && (CONFIG_GDMA_EN == 1)
struct gdma_s {
	hal_gdma_adaptor_t hal_gdma_adaptor;
};
#endif

#if defined(CONFIG_SPI_FLASH_EN) && (CONFIG_SPI_FLASH_EN == 1)
struct flash_s {
	hal_spic_adaptor_t *phal_spic_adaptor;
};
#endif

#if defined(CONFIG_SGPIO_EN) && (CONFIG_SGPIO_EN == 1)
struct sgpio_s {
	hal_sgpio_adapter_t sgpio_adapter;
#if defined(CONFIG_GDMA_EN) && (CONFIG_GDMA_EN == 1)
	hal_gdma_adaptor_t gdma_adaptor;
#endif
};
#endif

#if defined(CONFIG_SPI_EN) && (CONFIG_SPI_EN == 1)
struct spi_s {
	hal_ssi_adaptor_t hal_ssi_adaptor;
	volatile u32 state;
	u32 irq_handler;
	u32 irq_id;
	u32 bus_tx_done_handler;
	u32 bus_tx_done_irq_id;
	u32 dma_en;
	u32 sclk;
#if defined(CONFIG_GDMA_EN) && (CONFIG_GDMA_EN == 1)
	hal_gdma_adaptor_t spi_gdma_adp_tx;
	hal_gdma_adaptor_t spi_gdma_adp_rx;
#endif
};
#endif

#if defined(CONFIG_AUDIO_EN) && (CONFIG_AUDIO_EN == 1)
struct audio_s {
	hal_audio_adapter_t audio_adapter;
	BOOL audio_initialized;
	BOOL dac_l_dmute_en;
	BOOL adc_l_dmute_en;
	BOOL adc_r_dmute_en;
};
#endif

#if defined(CONFIG_ECDSA_EN) && (CONFIG_ECDSA_EN == 1)
struct ecdsa_s {
	hal_ecdsa_adapter_t ecdsa_adapter;
};
#endif

#if defined(CONFIG_SPORT_EN) && (CONFIG_SPORT_EN == 1)
struct sport_s {
	hal_sport_adapter_t sport_adapter;
};
#endif

#if defined(CONFIG_SNAND_FLASH_EN) && (CONFIG_SNAND_FLASH_EN == 1)
struct snand_s {
	hal_snafc_adaptor_t *psnand_adapter;
};
#endif

#ifdef __cplusplus
}
#endif

#endif  // end of "#ifndef MBED_OBJECTS_H"

