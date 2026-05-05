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

/* AMB82-Zero (RTL8735B) */

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

//#include "us_ticker_api.h"
#include "wiring_digital.h"
#include "video_boot.h"
#include "mmf2_mediatime_8735b.h"

extern void video_get_fcs_info(void *isp_fcs_info);

__weak void _init(void) { }
void __libc_init_array(void);

/*
 * Pins descriptions
 */

PinDescription g_APinDescription[TOTAL_GPIO_PIN_NUM]=
{
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D0   Not-in-use
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D1   Not-in-use  VDD33
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D2   Not-in-use  V_USB
    {PE_4,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                                | PIO_I2C | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D3                            *SERIAL3_CTS  I2C2_SDA  SPI_SS
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D4   Not-in-use  V_USB
    {PE_3,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                                | PIO_I2C | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D5                            *SERIAL3_RTS  I2C2_SCL  SPI_MOSI
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D6   Not-in-use  GND
    {PA_0,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // AMB_D7                            *SWD_DATA     I2C_SCL
    {PE_1,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                     | PIO_UART           | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D8                            SERIAL3_TX              SPI_SCLK
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D9   Not-in-use  GND
    {PE_2,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                     | PIO_UART           | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D10                           SERIAL3_RX              SPI_MISO
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D11  Not-in-use  NC
    {PF_13, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D12                           *LOG_TX                 I2S0_CLK
    {PA_1,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // AMB_D13                           *SWD_CLK      I2C_SDA
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D14  Not-in-use  GND
    {PA_2,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D15                           SERIAL1_TX
    {PA_3,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D16                           SERIAL1_RX
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D17  Not-in-use  VDD33
    {PD_15, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D18                           SERIAL2_TX
    {PF_7,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D19                                                   SPI1_MOSI
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D20  Not-in-use  GND
    {PF_5,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                                          | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D21                                                   SPI1_MISO
    {PD_16, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // AMB_D22                           SERIAL2_RX
    {PF_6,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D23                                                   SPI1_SCLK
    {PF_8,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                | PIO_SPI, MODE_NOT_INITIAL}, // AMB_D24                                                   SPI1_SS0
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D25  Not-in-use  GND
    {PF_10, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                                                   , MODE_NOT_INITIAL}, // AMB_D26                                                   SPI1_SS2
    {PF_2,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // AMB_D27   connected   AMB_D33     *LOG_CTS      I2C1_SDA
    {PF_1,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // AMB_D28   connected   AMB_D37     *LOG_RTS      I2C1_SCL
    {PD_17, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, // AMB_D29                           *SERIAL2_CTS
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D30  Not-in-use  GND
    {PF_11, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D31                                                   I2S0_MCK
    {PF_0,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, // AMB_D32   connected   AMB_D36
    {PF_2,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // *AMB_D33  R103        AMB_D27     *LOG_CTS      I2C1_SDA
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D34  Not-in-use  GND
    {PF_15, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D35                                                   I2S0_WS
    {PF_0,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, // *AMB_D36  R102        AMB_D32
    {PF_1,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC            | PIO_I2C          , MODE_NOT_INITIAL}, // *AMB_D37  R104        AMB_D28     *LOG_RTS      I2C1_SCL
    {PF_12, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D38                           *LOG_RX                 I2S0_SD_RX
    {NC  ,  TYPE_DIGITAL              , NOT_INITIAL                                                                  , MODE_NOT_INITIAL}, // *AMB_D39  Not-in-use  GND
    {PF_14, TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // AMB_D40                                                   I2S0_SD_TX0
    {PF_4,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // *AMB_D41                          LOG_TX
#ifdef A3
    {PF_3,  TYPE_DIGITAL | TYPE_ANALOG, PIO_GPIO    | PIO_GPIO_IRQ           | PIO_ADC                               , MODE_NOT_INITIAL}, //
#else
    {PF_3,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                     | PIO_UART                    , MODE_NOT_INITIAL}, // *AMB_D42                          LOG_RX
#endif
    {PF_9,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ | PIO_PWM                                         , MODE_NOT_INITIAL}, // *AMB_D43  onboard     LED1 blue
    {PE_6,  TYPE_DIGITAL              , PIO_GPIO    | PIO_GPIO_IRQ                                                   , MODE_NOT_INITIAL}  // *AMB_D44  onboard     LED2 green
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

void set_initial_tick_count(void)
{
    // Check DWT_CTRL(0xe0001000) CYCCNTENA(bit 0). If DWT cycle counter is enabled, set tick count initial value based on DWT cycle counter.
    if ((*((volatile uint32_t *) 0xe0001000)) & 1) {
        (*((volatile uint32_t *) 0xe0001000)) &= (~((uint32_t) 1)); // stop DWT cycle counter
        uint32_t dwt_cyccnt = (*((volatile uint32_t *) 0xe0001004));
        uint32_t systick_load = (configCPU_CLOCK_HZ / configTICK_RATE_HZ) - 1UL;
        initial_tick_count = dwt_cyccnt / systick_load;
    }

    // Auto set the media time offset
    video_boot_stream_t *isp_fcs_info;
    video_get_fcs_info(&isp_fcs_info);  //Get the fcs info
    uint32_t media_time_ms = initial_tick_count + isp_fcs_info->fcs_start_time;
    mm_set_mediatime_in_ms(media_time_ms);
}

void ameba_init(void)
{
    // Initialize C library
    __libc_init_array();

    // Initialize micro ticker
//    us_ticker_init();

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
