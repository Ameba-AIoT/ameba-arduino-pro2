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

#ifndef _VARIANT_ARDUINO_AMEBA_
#define _VARIANT_ARDUINO_AMEBA_

#include "Arduino.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C"{
#include "PinNames.h"

/*
 * Wait until enter debug mode
 *
 * Check DHCSR(0xE000EDF0) register and hold until bit C_DEBUGEN is set.
 * Use this function along with J-LINK or other debug tool
 **/
extern void wait_for_debug(void);
}
#endif

#define MAIN_THREAD_STACK_SIZE                  (4096 * 4)

#define TOTAL_GPIO_PIN_NUM                      (44) // (31)
#define TOTAL_PWM_PIN_NUM                       (9)

/* Digital pin mapping refer to g_APinDescription */
//#define AMB_D0                                  0  // N-I-U
//#define AMB_D1                                  1  // N-I-U    VDD33
//#define AMB_D2                                  2  // N-I-U    V_USB
#define AMB_D3                                  3  // PE_4
//#define AMB_D4                                  4  // N-I-U    V_USB
#define AMB_D5                                  5  // PE_3
//#define AMB_D6                                  6  // N-I-U    GND
#define AMB_D7                                  7  // PA_0
#define AMB_D8                                  8  // PE_1
//#define AMB_D9                                  9  // N-I-U    GND
#define AMB_D10                                 10 // PE_2
//#define AMB_D11                                 11 // N-I-U    NC
#define AMB_D12                                 12 // PF_13
#define AMB_D13                                 13 // PA_1
//#define AMB_D14                                 14 // N-I-U    VDD33
#define AMB_D15                                 15 // PA_2
#define AMB_D16                                 16 // PA_3
//#define AMB_D17                                 17 // N-I-U    GND
#define AMB_D18                                 18 // PD_15
#define AMB_D19                                 19 // PF_7
//#define AMB_D20                                 20 // N-I-U    GND
#define AMB_D21                                 21 // PF_5
#define AMB_D22                                 22 // PD_16
#define AMB_D23                                 23 // PF_6
#define AMB_D24                                 24 // PF_8
//#define AMB_D25                                 25 // N-I-U    GND
#define AMB_D26                                 26 // PF_10
#define AMB_D27                                 27 // PF_2       AMB_D33
#define AMB_D28                                 28 // PF_1       AMB_D37
#define AMB_D29                                 29 // PD_17
//#define AMB_D30                                 30 // N-I-U    GND
#define AMB_D31                                 31 // PF_11
#define AMB_D32                                 32 // PF_0       AMB_D36
#define AMB_D33                                 33 // PF_2
//#define AMB_D34                                 34 // N-I-U    GND
#define AMB_D35                                 35 // PF_15
#define AMB_D36                                 36 // PF_0
#define AMB_D37                                 37 // PF_1
#define AMB_D38                                 38 // PF_12
//#define AMB_D39                                 39 // N-I-U    GND
#define AMB_D40                                 40 // PF_14

#define AMB_D41                                 41 // PF_4
#define AMB_D42                                 42 // PF_3
#define AMB_D43                                 43 // PF_9
#define AMB_D44                                 44 // PE_6


/* Analog pin mapping */
#define A0                                      AMB_D32 // PF_0    3.3V    CH0
#define A1                                      AMB_D28 // PF_1    3.3V    CH1
#define A2                                      AMB_D27 // PF_2    3.3V    CH2
//#define A3                                      AMB_D42 // PF_3    3.3V    CH3    LOG_RX not recomanded to be used as ADC
#define A4                                      AMB_D7  // PA_0    3.3V    CH4
#define A5                                      AMB_D13 // PA_1    3.3V    CH5
#define A6                                      AMB_D15 // PA_2    3.3V    CH6
#define A7                                      AMB_D16 // PA_3    3.3V    CH7

/* LED pin mapping */
#define LED_B                                   AMB_D43 //  Blue
#define LED_G                                   AMB_D44 //  Green
#define LED_BUILTIN                             LED_B   //  Blue

/* Push button mapping */
//#define PUSH_BTN

/* ADC/DAC pin mapping */
#define FEATURE_ADC
//#define FEATURE_DAC

/* SPI pin mapping */ 
// Master and Slave
#define SPI_MOSI                                AMB_D5      // SPI_0_MOSI   AMB_D5
#define SPI_MISO                                AMB_D10     // SPI_0_MISO   AMB_D10
#define SPI_SCLK                                AMB_D8      // SPI_0_SCL    AMB_D8
#define SPI_SS                                  AMB_D3      // SPI_0_CS0    AMB_D3
#define SPI1_MOSI                               AMB_D19     // SPI_1_MOSI   AMB_D19
#define SPI1_MISO                               AMB_D21     // SPI_1_MISO   AMB_D21
#define SPI1_SCLK                               AMB_D23     // SPI_1_SCL    AMB_D23
#define SPI1_SS0                                AMB_D24     // SPI_1_CS0    AMB_D24
#define SPI1_SS2                                AMB_D26     // SPI_1_CS1    AMB_D26
#define SPI1_SS                                 SPI1_SS0

/* TwoWire/I2C pin mapping */
#define I2C_SDA                                 AMB_D13     // I2C0_SDA     AMB_D13
#define I2C_SCL                                 AMB_D7      // I2C0_SCL     AMB_D7
#define I2C1_SDA                                AMB_D27     // I2C1_SDA     AMB_D27 / AMB_D33
#define I2C1_SCL                                AMB_D28     // I2C1_SCL     AMB_D28 / AMB_D37
#define I2C2_SDA                                AMB_D3      // I2C2_SDA     AMB_D3
#define I2C2_SCL                                AMB_D5      // I2C2_SCL     AMB_D5

/* IR Device pin mapping */
//#define IR_TX
//#define IR_RX

/* UART pin mapping */
#define LOG_UART_MODIFIABLE_BAUD_RATE           1
#define SERIAL_ONE_UART_MODIFIABLE_BAUD_RATE    1
#define SERIAL_TWO_UART_MODIFIABLE_BAUD_RATE    1
#define SERIAL_TRI_UART_MODIFIABLE_BAUD_RATE    1
#define LOG_TX                                  AMB_D41     // UART1_OUT        AMB_D41 / AMB_D12
#define LOG_RX                                  AMB_D42     // UART1_IN         AMB_D42 / AMB_D38
//#define LOG_CTS                                 AMB_D27   // UART1_CTS        AMB_D27 / AMB_D33
//#define LOG_RTS                                 AMB_D28   // UART1_RTS        AMB_D28 / AMB_D37
#define SERIAL1_TX                              AMB_D15     // UART0_OUT        AMB_D15
#define SERIAL1_RX                              AMB_D16     // UART0_IN         AMB_D16
//#define SERIAL1_CTS
//#define SERIAL1_RTS
#define SERIAL2_TX                              AMB_D18     // UART2_OUT        AMB_D18
#define SERIAL2_RX                              AMB_D22     // UART2_IN         AMB_D22
//#define SERIAL2_CTS                             AMB_D29   // UART2_CTS        AMB_D29
//#define SERIAL2_RTS
#define SERIAL3_TX                              AMB_D8      // UART3_OUT        AMB_D8
#define SERIAL3_RX                              AMB_D10     // UART3_IN         AMB_D10
//#define SERIAL3_CTS                             AMB_D3    // UART3_CTS        AMB_D3
//#define SERIAL3_RTS                             AMB_D5    // UART3_RTS        AMB_D5

/* SWD pin mapping */
#define SWD_DATA                                AMB_D7      // AMB_D7
#define SWD_CLK                                 AMB_D13     // AMB_D13

#endif /* _VARIANT_ARDUINO_AMEBA_ */
