/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* AMB82 (RTL8735B) */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "us_ticker_api.h"
#include "wiring_digital.h"
__weak void _init(void) { }
void __libc_init_array(void);

/*
 * Pins descriptions
 */
PinDescription g_APinDescription[TOTAL_GPIO_PIN_NUM]=
{
    {PF_5,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                          | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D0                          SPI1_MISO
    {PF_6,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D1                          SPI1_SCLK
    {PF_7,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D2                          SPI1_MOSI
    {PF_8,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D3                          SPI1_SS
    {PF_11, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D4
    {PF_12, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D5   *LOG_RX
    {PF_13, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D6   *LOG_TX
    {PF_14, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D7
    {PF_15, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D8
    {PF_2,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // AMB_D9   *LOG_CTS      I2C1_SDA
    {PF_1,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // AMB_D10  *LOG_RTS      I2C1_SCL
    {PF_0,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, // AMB_D11
    {PE_4,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                | PIO_I2C | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D12  *SERIAL3_CTS  I2C_SDA  SPI_SS
    {PE_3,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                | PIO_I2C | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D13  *SERIAL3_RTS  I2C_SCL  SPI_MOSI
    {PE_2,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                     | PIO_UART           | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D14  SERIAL3_RX             SPI_MISO
    {PE_1,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                     | PIO_UART           | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D15  SERIAL3_TX             SPI_SCLK
    {PD_18, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                                   , MODE_NOT_INITIAL}, // AMB_D16  *SERIAL2_RTS
    {PD_17, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, // AMB_D17  *SERIAL2_CTS
    {PD_16, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D18  SERIAL2_RX
    {PD_15, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D19  SERIAL2_TX
    {PD_14, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                                   , MODE_NOT_INITIAL}, // AMB_D20
    {PA_2,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D21  SERIAL1_TX
    {PA_3,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D22  SERIAL1_RX
    {PF_9,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // *AMB_D23 onboard LED blue
    {PE_6,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                                   , MODE_NOT_INITIAL}, // *AMB_D24 onboard LED green
    {PF_4,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // *AMB_D25 LOG_TX
#ifdef A3
    {PF_3,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, //
#else
    {PF_3,  TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // *AMB_D26 LOG_RX
#endif
    {PA_1,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // *AMB_D27 SWD_CLK       I2C2_SDA
    {PA_0,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // *AMB_D28 SWD_DATA      I2C2_SCL
    {PF_10, TYPE_DIGITAL              , PIO_GPIO | PIO_GPIO_IRQ                                                   , MODE_NOT_INITIAL}  // *AMB_D29 onboard Button
};

void *gpio_pin_struct[TOTAL_GPIO_PIN_NUM] = {NULL};
void *gpio_irq_handler_list[TOTAL_GPIO_PIN_NUM] = {NULL};

#ifdef __cplusplus
} // extern C
#endif

void serialEvent() __attribute__((weak));
bool Serial_available() __attribute__((weak));

// ----------------------------------------------------------------------------

void serialEventRun(void)
{
    if (Serial_available && serialEvent && Serial_available()) serialEvent();
}

void ameba_init(void)
{
    // Initialize C library
    __libc_init_array();

    // Initialize micro ticker
    us_ticker_init();

    // Initialize onboard LED
    pinMode(LED_B, OUTPUT);
    pinMode(LED_G, OUTPUT);
}
// ----------------------------------------------------------------------------

void wait_for_debug(void) {
    while (((CoreDebug->DHCSR) & CoreDebug_DHCSR_C_DEBUGEN_Msk) == 0) {
        asm("nop");
    }
    delay(1000);
}
