/**************************************************************************//**
 * @file     rtl8195bhp_spic.h
 * @brief    The header file of rtl8195bhp_spic.c.
 * @version  1.00
 * @date     2017-08-22
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

#ifndef RTL8735B_SPIC_H
#define RTL8735B_SPIC_H

#include "rtl8735b_spic_type.h"

/**

        \addtogroup hal_spic Flash Controller
        \ingroup 8735b_hal
        \brief The Flash Controller (SPIC) module of the HS platform.
        @{
*/


#define MAX_DELAY_LINE 99               //!< Define maximum delay line level, fine-tune with digital PHY
#define CPU_CLK_TYPE_NO 6               //!< Define the number of clock options for CPU
#define MIN_BAUD_RATE 0x01              //!< Define minimum baud rate of flash controller
#define MAX_BAUD_RATE 0x05              //!< Define maximum baud rate of flash controller
#define MAX_AUTO_LENGTH 0x14            //!< Define maximum dummy cycle levels for timing tuning by flash controller(not PHY)
#define SPI_FLASH_BASE 0x8000000       //!< Define flash memory address base

/**
  \brief  Enumeration to define flash IO mode
*/
enum spic_io_mode_e {
	SpicOneIOMode = 0,                  //!< Define One IO mode, 1-1-1
	SpicDualOutputMode = 1,             //!< Define Dual Output mode, 1-1-2
	SpicDualIOMode = 2,                 //!< Define Dual IO mode, 1-2-2
	SpicQuadOutputMode = 3,             //!< Define Quad Output mode, 1-1-4
	SpicQuadIOMode = 4,                 //!< Define Quad IO mode, 1-4-4
	SpicQuadIODtrMode = 5,              //!< Define Quad IO DTR mode, 1-4D-4D
	SpicQpiMode = 6,                    //!< Define QPI mode, 4-4-4
	SpicQpiDtrMode = 7,                 //!< Define QPI DTR mode, 4-4D-4D / 4D-4D-4D
};
typedef uint8_t spic_io_mode_t;

/**
  \brief  Enumeration to define transfer mode
*/
enum spic_tmod_mode_e {
	TxMode = 0,                         //!< Transmit mode
	RxMode = 3                          //!< Receive mode
};
typedef uint8_t spic_tmod_mode_t;

/**
  \brief  Enumeration to define the channle number used by the controller to access flash
*/
enum spic_channel_number_e {
	SingleChnl = 0,                     //!< Single channel
	DualChnl = 1,                       //!< Dual channel
	QuadChnl = 2                        //!< Quad channel
};
typedef uint8_t spic_channel_number_t;

/**
  \brief  Enumeration to define the byte number of address phase
*/
enum spic_address_phase_length_e {
	FourBytesLength = 0,                //!< Four bytes length
	OneByteLength = 1,                  //!< One byte length
	TwoBytesLength = 2,                 //!< Two bytes length
	ThreeBytesLength = 3                //!< Three bytes length
};
typedef uint8_t spic_address_phase_length_t;

/**
  \brief  Enumeration to define pinmux selection
*/
enum spic_pin_sel_e {
	SpicDualIOPin = 0,                  //!< Dual IO pin selection, with two data pins
	SpicQuadIOPin = 1                   //!< Quad IO pin selection, with four data pins
};
typedef uint8_t spic_pin_sel_t;

/**
  \brief  Enumeration to define SPIC source clock
*/
enum spic_clk_sel_e {
	Clk300MHz = 0,                      //!< 300 MHz Clock
	Clk200MHz = 1,                      //!< 200 MHz Clock
	Clk150MHz = 2,                      //!< 150 MHz Clock
	Clk100MHz = 3,                      //!< 100 MHz Clock
	Clk4MHz = 4,                        //!< 4 MHz Clock
	Clk2MHz = 5                         //!< 2 MHz Clock
};
typedef uint8_t spic_clk_sel_t;

/**
  \brief  The data struct of calibration setting
*/
typedef struct _spic_init_para_s {
	u8  baud_rate;                      //!< Valid baud rate setting
	u8  rd_dummy_cycle;                 //!< Valid flash controller's dummy cycle setting
	u8  delay_line;                     //!< Valid DPHY delay setting
	u8  valid;                          //!< Indicate data stored in the struct is valid or not
} spic_init_para_t, *pspic_init_para_t;

/**
  \brief  The data struct of SPIC adaptor
*/
typedef struct _hal_spic_adaptor_s {
	irq_config_t irq_handle;                                //!< Interrupt handler, reserved
	SPIC_TypeDef *spic_dev;                                    //!< The register base of SPIC
	spic_init_para_t spic_init_data[8][CPU_CLK_TYPE_NO];   //!< Calibration settings for various IO mode with different CPU clock
	pflash_cmd_t cmd;                                       //!< The pointer pointing to flash commands
	pflash_dummy_cycle_t dummy_cycle;                       //!< The pointer pointing to various dummy cycles
	u16  read_cmd;                                          //!< Flash read command for current IO mode
	u8   write_delay;                                       //!< Number of NOP delay to prevent FIFO overflow
	u8   quad_pin_sel;                                      //!< Record if the quad IO pins are used
	spic_pin_sel_t flash_pin_sel;                           //!< Pinmux selection
	u8   interrupt_mask;                                    //!< Reserved
	u8   flash_id[3];                                       //!< Flash ID
	u8   flash_type;                                        //!< Flash type
	u8   cmd_byte_num;                                      //!< The byte number of command phase
	u8   addr_byte_num;                                     //!< The byte number of address phase
	u8   spic_bit_mode;                                     //!< Current IO mode used by the adaptor
	u8   spic_send_cmd_mode;                                //!< IO mode to send flash commands
	u8   dtr_en;                                            //!< Indicate whether DTR mode is enabled
	u8   cmd_chnl;                                          //!< The channel number of command phase used by SPIC
	u8   addr_chnl;                                         //!< The channel number of address phase used by SPIC
	u8   data_chnl;                                         //!< The channel number of data phase used by SPIC
} hal_spic_adaptor_t, *phal_spic_adaptor_t;

/**
  \brief  The data struct of valid windows for flash calibration
*/
typedef struct _valid_windows_s {
	u16 baud_rate;                      //!< Temporarily baud rate setting for calibration
	u16 auto_length;                    //!< Temporarily dummy cycle setting for calibration
	u32 dly_line_sp;                    //!< Temporarily available window of DPHY delay line starting point
	u32 dly_line_ep;                    //!< Temporarily available window of DPHY delay line ending point
} valid_windows_t, *pvalid_windows_t;

/**
  \brief  The data struct of flash controller stub functions. ROM code functions are accessed in RAM code through stub functions.
*/
typedef struct hal_spic_func_stubs_s {
	void (*spic_load_default_setting)(pspic_init_para_t pspic_init_data);
	u8(*spic_query_system_clk)(void);
	void (*spic_clock_ctrl)(u8 ctl);
	hal_status_t (*spic_init_setting)(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode);
	void (*spic_config_dtr_read)(phal_spic_adaptor_t phal_spic_adaptor);
	void (*spic_config_auto_mode)(phal_spic_adaptor_t phal_spic_adaptor);
	void (*spic_config_user_mode)(phal_spic_adaptor_t phal_spic_adaptor);
	BOOL (*spic_verify_calibration_para)(void);
	void (*spic_set_chnl_num)(phal_spic_adaptor_t phal_spic_adaptor);
	void (*spic_set_delay_line)(u8 delay_line);
	void (*spic_rx_cmd)(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
	void (*spic_tx_cmd_no_check)(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
	void (*spic_tx_cmd)(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
	void (*spic_wait_ready)(SPIC_TypeDef *spic_dev);
	void (*spic_flush_fifo)(SPIC_TypeDef *spic_dev);
	uint32_t reserved[9];  // reserved space for next ROM code version function table extending.
} hal_spic_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_spic_rtl_func Flash Controller HAL ROM APIs
        @{
*/

/** \brief Description of spic_rtl_enable
 *
 *    spic_rtl_enable is used to enable flash controller.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
static inline void spic_rtl_enable(SPIC_TypeDef *spic_dev)
{
	spic_dev->SPIC_SSIENR = ENABLE;
}

/** \brief Description of spic_rtl_disable
 *
 *    spic_rtl_disable is used to disable flash controller.
 *    Some registers should call this funciton first to disable the flash controller so that values can be correctly set to registers.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
static inline void spic_rtl_disable(SPIC_TypeDef *spic_dev)
{
	spic_dev->SPIC_SSIENR = DISABLE;
}


/** \brief Description of spic_rtl_set_ctrl1
 *
 *    spic_rtl_set_ctrl1 is used to set number of data frames (data length)expect to receive in user mode.
 *    The chip select line does not de-assert until the number of data received reaches the data length.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *   \param u32 length:      data length, the unit is byte.
 *
 *   \return void.
 */
static inline void spic_rtl_set_ctrl1(SPIC_TypeDef *spic_dev, u32 length)
{
	spic_dev->SPIC_CTRLR1 = length;
}

/** \brief Description of spic_rtl_set_baudr
 *
 *    spic_rtl_set_baudr is used to flush FIFO of the flash controller.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *   \param u8 baudr:      The value of baud rate divider.
 *
 *   \return void.
 */
static inline void spic_rtl_set_baudr(SPIC_TypeDef *spic_dev, u8 baudr)
{
	spic_dev->SPIC_BAUDR = baudr;
}

/** \brief Description of spic_rtl_set_fbaudr
 *
 *    spic_rtl_set_fbaudr is used to set baud rate of the flash controller for fast read.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *   \param u8 fbaudr:      The value of baud rate divider.
 *
 *   \return void.
 */
static inline void spic_rtl_set_fbaudr(SPIC_TypeDef *spic_dev, u8 fbaudr)
{
	spic_dev->SPIC_FBAUDR = fbaudr;
}

/** \brief Description of spic_rtl_set_dummy_cycle
 *
 *    spic_rtl_set_dummy_cycle is used to tune timing to receive data correctly.
 *    This dummy cycle adjustment mechanism is implemented in the flash controller.
 *    The unit of dummy cycle is bus clock.
 *    The flash controller should be disabled to set the register correctly.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *   \param u8 dummy_cycle:      The level of dummy cycles, can be up to MAX_AUTO_LENGTH.
 *
 *   \return void.
 */
static inline void spic_rtl_set_dummy_cycle(SPIC_TypeDef *spic_dev, u8 dummy_cycle)
{
	spic_dev->SPIC_AUTO_LENGTH &= ~SPIC_MASK_RD_DUMMY_LENGTH;
	spic_dev->SPIC_AUTO_LENGTH |= (u16)dummy_cycle;
}

/** \brief Description of spic_rtl_get_baudr
 *
 *    spic_rtl_get_baudr is used to get baud rate setting of the flash controller.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return u8: value of baud rate divider.
 */
static inline u8 spic_rtl_get_baudr(SPIC_TypeDef *spic_dev)
{
	u8 baudr = 0;

	baudr = (u8)spic_dev->SPIC_BAUDR;
	return baudr;
}

/** \brief Description of spic_rtl_get_fbaudr
 *
 *    spic_rtl_get_fbaudr is used to get baud rate setting of the flash controller for fast read.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return u8: value of baud rate divider.
 */
static inline u8 spic_rtl_get_fbaudr(SPIC_TypeDef *spic_dev)
{
	u8 fbaudr = 0;

	fbaudr = (u8)spic_dev->SPIC_FBAUDR;
	return fbaudr;
}

void spic_rtl_load_default_setting(pspic_init_para_t pspic_init_data);
u8 spic_rtl_query_system_clk(void);
void spic_rtl_clock_ctrl(u8 ctl);
void spic_rtl_pin_ctrl(u8 io_pin_sel, u8 ctl);
hal_status_t spic_rtl_init_setting(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode);
void spic_rtl_config_dtr_read(phal_spic_adaptor_t phal_spic_adaptor);
void spic_rtl_config_auto_mode(phal_spic_adaptor_t phal_spic_adaptor);
void spic_rtl_config_user_mode(phal_spic_adaptor_t phal_spic_adaptor);
BOOL spic_rtl_verify_calibration_para(void);
void spic_rtl_set_chnl_num(phal_spic_adaptor_t phal_spic_adaptor);
void spic_rtl_set_delay_line(u8 delay_line);
void spic_rtl_rx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rtl_tx_cmd_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rtl_tx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rtl_wait_ready(SPIC_TypeDef *spic_dev);
void spic_rtl_flush_fifo(SPIC_TypeDef *spic_dev);

/** *@} */ /* End of group hal_spic_rtl_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/** *@} */ /* End of group hal_spic */

#endif /* RTL8195BHP_SPIC_H */
