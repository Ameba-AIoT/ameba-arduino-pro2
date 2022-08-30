/**************************************************************************//**
 * @file     rtl8735b_gpio.h
 * @brief    This file defines GPIO HAL macros and data types.
 *
 * @version  V1.00
 * @date     2021-05-20
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

/**
 * @addtogroup hs_hal_gpio GPIO
 * @ingroup 8195bh_hal
 * @{
 * @brief The GPIO HAL module of the HS platform.
 */

#ifndef RTL8735B_GPIO_H
#define RTL8735B_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

// AON/PON/SYSON GPIO IP level registers
#include "rtl8735b_gpio_type.h"

// System level AON/PON/SYSON regions registers
#include "rtl8735b_aon_type.h"
#include "rtl8735b_pon_type.h"
#include "rtl8735b_syson_type.h"

#if !defined(CONFIG_BUILD_NONSECURE)

#undef AON_GPIO
#define AON_GPIO    (AON_GPIO_S_ADDR) // Secure address
#undef PON_GPIO
#define PON_GPIO    (PON_GPIO_S_ADDR) // Secure address
#undef SYSON_GPIO
#define SYSON_GPIO  (SYSON_GPIO_S_ADDR) // Secure address

#else

#undef AON_GPIO
#define AON_GPIO    (AON_GPIO_ADDR) // Non-Secure address
#undef PON_GPIO
#define PON_GPIO    (PON_GPIO_ADDR) // Non-Secure address
#undef SYSON_GPIO
#define SYSON_GPIO  (SYSON_GPIO_ADDR) // Non-Secure address

#endif

// Weide adapted from Crypto Example

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

/// @cond DOXYGEN_GPIO_REG_TYPE


/* ================================================================================================================ */
/* ================                          Device Specific Peripheral Address Map                           ===== */
/* ================================================================================================================ */


/** @addtogroup device_gpio_addr AON/PON/SYSON GPIO Register Base Addresses
 *  @ingroup hal_gpio
 *  @{
 */

#define AON_GPIO_S_BASE               0x5000A800UL
#define AON_GPIO_NS_BASE              0x4000A800UL

#define PON_GPIO_S_BASE               0x5000AC00UL
#define PON_GPIO_NS_BASE              0x4000AC00UL

#define SYSON_GPIO_S_BASE             0x50001000UL
#define SYSON_GPIO_NS_BASE            0x40001000UL

/** @} */ /* End of group device_gpio_addr */


/* ================================================================================================================ */
/* ================                                  Peripheral declaration                                   ===== */
/* ================================================================================================================ */


/** @addtogroup device_gpio_decl AON/PON/SYSON GPIO Device Type
 *  @ingroup hal_gpio
 *  @{
 */

#define AON_GPIO_S_ADDR                             ((GPIO_TypeDef *)           AON_GPIO_S_BASE)
#define AON_GPIO_ADDR                               ((GPIO_TypeDef *)           AON_GPIO_NS_BASE)

#define PON_GPIO_S_ADDR                             ((GPIO_TypeDef *)           PON_GPIO_S_BASE)
#define PON_GPIO_ADDR                               ((GPIO_TypeDef *)           PON_GPIO_NS_BASE)

#define SYSON_GPIO_S_ADDR                           ((GPIO_TypeDef *)           SYSON_GPIO_S_BASE)
#define SYSON_GPIO_ADDR                             ((GPIO_TypeDef *)           SYSON_GPIO_NS_BASE)

/** @} */ /* End of group device_gpio_decl */

/// @endcond /* End of condition DOXYGEN_GPIO_REG_TYPE */


/**
  \brief  Defines the data type for GPIO pin name, a GPIO pin name is
          from combination of GPIO port and GPIO pin index.
 */
typedef struct gpio_pin_s {
	union {
		uint8_t pin_name;
		struct {
			uint8_t pin: 5;             ///< bit:  4.. 0  the pin index in a port
			uint8_t port: 3;            ///< bit:  7.. 5 the port index
		} pin_name_b;
	};
} gpio_pin_t, *pgpio_pin_t;

/**
  \brief  Defines the data type of GPIO port. The GPIO port data type is from the
          combination of port index, pin mask and the offset of the 1st pin.
 */
typedef struct gpio_port_s {
	union {
		uint32_t port_name;
		struct {
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test chip
			uint32_t mask: 18;            ///< bit: 17.. 0  the pin mask of the port
			uint32_t offset: 5;           ///< bit: 22.. 18 the 1st pin offset
			uint32_t : 1;                 ///< bit: 23.. 23 reserved
			uint32_t port: 3;             ///< bit: 26.. 24 the GPIO IP port index
#else // MP chip
			uint32_t mask: 21;            ///< bit: 20.. 0  the pin mask of the port
			uint32_t offset: 5;           ///< bit: 25.. 21 the 1st pin offset
			uint32_t : 2;                 ///< bit: 27.. 26 reserved
			uint32_t port: 3;             ///< bit: 30.. 28 the GPIO IP port index
#endif

		} port_name_b;
	};
} gpio_port_t, *pgpio_port_t;

/// Defines the maximum GPIO pin in a port
#define GPIO_MAX_PIN_IDX            32     // the maximum pin number in a GPIO IP port

/// Defines the maximum GPIO interrupt pins. It is the number of the PON or SYSON GPIO IRQ pins this platform can support.
#define GPIO_MAX_INT_PIN            16     // 0 ~ 15, one SYSON or PON GPIO IP only support 16 configurable interrupt pins
/// Defines the maximum GPIO interrupt pins. It is the number of the AON GPIO IRQ pins this platform can support.
#define AON_GPIO_MAX_INT_PIN        6     // 0 ~ 5, one AON GPIO IP only support 6 configurable interrupt pins

/// Defines the maximum GPIO debounce pins. It is the number of GPIO pin can enable the debounce function simultaneously.
#define GPIO_MAX_DEBOUNCE_PIN       16     // 0 ~ 15, one GPIO IP only support 16 configurable de-bounce pins
/// Defines the maximum GPIO debounce pins. It is the number of GPIO pin can enable the debounce function simultaneously.
#define AON_GPIO_MAX_DEBOUNCE_PIN   6     // 0 ~ 5, one GPIO IP only support 16 configurable de-bounce pins

/// define the GPIO port number. It's the number of the GPIO port this platform have.
#define GPIO_MAX_PORT_NUM           4      // 0 ~ 3, the port number of the GPIO IP // should be be 1 right?

/**
  \brief  Defines the GPIO port name
 */
enum {
	GPIO_IP_PORT0         = 0,
	GPIO_IP_PORT1         = 1,
	GPIO_IP_PORT2         = 2,
	GPIO_IP_PORT3         = 3,

	GPIO_IP_MAX_PORT_ID   = 4
};

/**
  \brief  Defines type of GPIO - AON/PON/SYSON GPIO.
 */
enum gpio_type_e {
	AonGPIO  = 0,
	SysonGPIO = 1,
	PonGPIO  = 2
};
typedef uint8_t gpio_type_t;

/**
  \brief  Defines GPIO interrupt polarity status
 */
enum {
	GPIO_LevelHigh      = 0,
	GPIO_LevelLow       = 1,
	GPIO_EdgeRising     = 0,
	GPIO_EdgeFalling    = 1,
	GPIO_EdgeDual       = 2
};

/**
  \brief  Defines GPIO interrupt trigger event type.
 */
enum  gpio_int_trigger_type_e {
	GPIO_IntType_None           = 0,
	GPIO_IntType_EdgeRising     = 1,
	GPIO_IntType_EdgeFalling    = 2,
	GPIO_IntType_LevelLow       = 3,
	GPIO_IntType_LevelHigh      = 4,
	GPIO_IntType_EdgeDual       = 5,

	GPIO_IntType_Invalid        = 0x0F
};
typedef uint8_t gpio_int_trig_type_t;

/**
  \brief  Defines GPIO pin direction.
 */
enum  gpio_dir_e {
	GPIO_IN                  = 0,
	GPIO_OUT                 = 1
};
typedef uint8_t gpio_dir_t;

#if 0 // debounce clk always 32K for all GPIOs in ProII.
/*! define GPIO Debounce clock source */
enum  gpio_deb_clk_e {
	GPIO_DebClk_LS32K      = 0,
	GPIO_DebClk_HS32K      = 0
};
typedef uint8_t gpio_deb_clk_t;
#endif

/**
  \brief  Defines GPIO Interrupt clock source.
 */
enum  gpio_int_clk_e {
	GPIO_IntClk_100K    = 0, // 100k clk
	GPIO_IntClk_4M      = 1 // 4M clk
};
typedef uint8_t gpio_int_clk_t;

/**
  \brief  Defines IO pad pull control type.
 */
enum pin_pull_ctrl_e {
	GPIO_REG_PullCtrl_Set_HighZ = 0,
	GPIO_REG_PullCtrl_SetLow = 1,
	GPIO_REG_PullCtrl_SetHigh = 2
};

/**
  \brief  Defines IO pad pull type hardware supported.
 */
enum pin_pull_type_e {
	Pin_PullNone  = 0,
	Pin_PullUp    = 1,
	Pin_PullDown  = 2,
	Pin_PullDefault = Pin_PullNone
};
typedef uint8_t pin_pull_type_t;

#if 0 // Weide commented out because in ProII only SDIO has 2 voltages. GPIOs only have single voltage.
/**
  \brief  Defines IO pad voltage.
 */
enum io_pad_vol_e {
	IO_1p8V  = 0,        // IO pad voltage = 1.8V
	IO_3p3V  = 1         // IO pad voltage = 3.3V
};
typedef uint8_t io_pad_vol_t;
#endif

/**
  \brief  Defines GPIO interrupt call back function type.
 */
typedef void (*gpio_irq_callback_t)(uint32_t int_id, gpio_int_trig_type_t int_type);

/**
  \brief  The data structure for a GPIO pin HAL operation.
*/
typedef struct hal_gpio_pin_adapter_s {
	uint8_t pin_name;               ///< chip pin name to locate the GPIO pin by port & pin index
	uint8_t port_idx;               ///< the GPIO IP port index of the GPIO pin
	uint8_t pin_idx;                ///< the GPIO IP pin index of the GPIO port
	uint8_t debounce_idx;           ///< the index of GPIO debounce function allocated to this GPIO pin, 0 ~ 15
	uint32_t bit_mask;              ///< the bit mask to read/write register

	volatile uint32_t *in_port;     ///< the IN port address
	volatile uint32_t *out0_port;   ///< the OUT port address for write 0
	volatile uint32_t *out1_port;   ///< the OUT port address for write 1
	volatile uint32_t *outt_port;   ///< the OUT port address for toggling
	uint32_t s_ram_aon_gpio_on;     ///< Secure GPIO RAM has turned on power and clock for AON GPIO
	uint32_t s_ram_pon_gpio_on;     ///< Secure GPIO RAM has turned on power and clock for PON GPIO
	uint32_t s_ram_gpio_on;         ///< Secure GPIO RAM has turned on power and clock for SYSON GPIO
	uint32_t reserved[7];           ///< Reserved, make 32-byte aligned
} hal_gpio_adapter_t, *phal_gpio_adapter_t;

/**
  \brief  The data structure for a GPIO IRQ pin HAL operation.
*/
typedef struct hal_gpio_irq_pin_adapter_s {
	uint8_t     pin_name;           ///< chip pin name to locate the GPIO pin by port & pin index
	uint8_t     ip_pin_name;        ///< IP pin name to locate the GPIO pin by port & pin index
	uint8_t     int_idx;            ///< the GPIO interrupt function index, 0 ~ 15
	uint8_t     debounce_idx;       ///< the GPIO debounce function index, 0 ~ 15
	uint8_t     int_type;           ///< the GPIO interrupt trigger type
	uint8_t     resv[3];
	uint32_t    bit_mask;           ///< the bit mask to read register
	volatile uint32_t    *in_port;  ///< the IN port address
	gpio_irq_callback_t irq_callback;   ///< the call-back function of the GPIO IRQ
	uint32_t irq_callback_arg;      ///< the argument of the IRQ call-back function, it's a priviate data will be pass to the application with the call back function.
	void *pnext;                    ///< point to the next gpio_irq_pin_adapter
	uint32_t reserved[7];           ///< Reserved, make 32-byte aligned
} hal_gpio_irq_adapter_t, *phal_gpio_irq_adapter_t;

/**
  \brief  The data structure for a GPIO port HAL operation.
*/

typedef struct hal_gpio_port_adapter_s {
	uint8_t port_idx;               		///< the IP port index
	//uint8_t chip_port_idx;        		  ///< the chip port index (for pinmux reg & unreg purposes)
	uint8_t pin_offset;             		///< the pin0 of this port which is located at the offset of the IP port
	uint8_t reserv0;
	uint8_t reserv1;
	uint32_t pin_mask;              		///< the mask of pin to indicates what pin is included
//    uint32_t bit_mask;            		///< the bit mask to read/write register
	volatile uint32_t *in_port;     		///< the IN port address
	volatile uint32_t *out0_port;   		///< the OUT port address for write 0
	volatile uint32_t *out1_port;   		///< the OUT port address for write 1
	volatile uint32_t *outt_port;   		///< the OUT port address for toggling

	// To handle GPIO E overflow. Overflow means the bits from GPIO E fills to the end of GPIO Group A registers, and flows to use GPIO Group B registers.
	uint8_t pin_offset_PORTE; 				///< the pin0 of this port which is located at the offset of the IP port
	volatile uint32_t *in_port_PORTE;     	///< the IN port address - for GPIO Port E overflow
	volatile uint32_t *out0_port_PORTE;   	///< the OUT port address for write 0 - for GPIO Port E overflow
	volatile uint32_t *out1_port_PORTE;   	///< the OUT port address for write 1 - for GPIO Port E overflow
	volatile uint32_t *outt_port_PORTE;  	///< the OUT port address for toggling - for GPIO Port E overflow
	uint32_t reserved[5];                	///< Reserved, make 32-byte aligned
} hal_gpio_port_adapter_t, *phal_gpio_port_adapter_t;

/**
  \brief  The data structure for SYSON GPIO Common resource menagement.
*/
typedef struct hal_gpio_comm_adapter_s {
	volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
	volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
	volatile uint32_t gpio_irq_using;        			///< the bit map to indicate using status of IRQ functions // may be need to add more
	volatile uint32_t gpio_deb_using;        			///< the bit map to indicate using status of debounce functions
	volatile uint32_t critical_lv;  					///< to record AON GPIO HAL enter critical section level
	union {
		volatile uint32_t errs;
		struct {
			volatile uint32_t irq_err: 1;    			///< IRQ handler error
			volatile uint32_t init_err: 1;   			///< initial error
		} err_flag;
	};
	uint32_t reserved[2];                				///< Reserved, make 32-byte aligned
} hal_gpio_comm_adapter_t, *phal_gpio_comm_adapter_t;

/**
  \brief  The data structure for AON GPIO Common resource menagement.
*/
typedef struct hal_aon_gpio_comm_adapter_s {
	volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
	volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
	volatile uint32_t gpio_irq_using;        			///< the bit map to indicate using status of IRQ functions // may be need to add more
	volatile uint32_t gpio_deb_using;        			///< the bit map to indicate using status of debounce functions
	volatile uint32_t critical_lv; 						///< to record AON GPIO HAL enter critical section level
	union {
		volatile uint32_t errs;
		struct {
			volatile uint32_t irq_err: 1;   			///< IRQ handler error
			volatile uint32_t init_err: 1;  			///< initial error
		} err_flag;
	};
	uint32_t reserved[2];                				///< Reserved, make 32-byte aligned
} hal_aon_gpio_comm_adapter_t, *phal_aon_gpio_comm_adapter_t;

/**
  \brief  The data structure for PON GPIO Common resource menagement.
*/
typedef struct hal_pon_gpio_comm_adapter_s {
	volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
	volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
	volatile uint32_t gpio_irq_using;        			///< the bit map to indicate using status of IRQ functions // may be need to add more
	volatile uint32_t gpio_deb_using;        			///< the bit map to indicate using status of debounce functions
	volatile uint32_t critical_lv;  					///< to record AON GPIO HAL enter critical section level
	union {
		volatile uint32_t errs;
		struct {
			volatile uint32_t irq_err: 1;    			///< IRQ handler error
			volatile uint32_t init_err: 1;  			///< initial error
		} err_flag;
	};
	uint32_t reserved[2];                				///< Reserved, make 32-byte aligned
} hal_pon_gpio_comm_adapter_t, *phal_pon_gpio_comm_adapter_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_gpio_rom_func GPIO HAL ROM APIs.
 * @ingroup hs_hal_gpio
 * @{
 */

void hal_rtl_gpio_reg_irq(gpio_type_t gpio_type, irq_handler_t irq_handler);
void hal_rtl_gpio_set_irq_priority(uint32_t priority);
hal_status_t hal_rtl_gpio_interrupt_clk_sel(gpio_type_t gpio_type, uint8_t clk_sel);
void hal_rtl_gpio_comm_init(phal_gpio_comm_adapter_t pgpio_comm_adp);
void hal_rtl_aon_gpio_comm_init(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);
void hal_rtl_pon_gpio_comm_init(phal_pon_gpio_comm_adapter_t ppon_gpio_comm_adp);
void hal_rtl_gpio_comm_deinit(void);
void hal_rtl_aon_gpio_comm_deinit(void);  // new
void hal_rtl_pon_gpio_comm_deinit(void);  // new
void hal_rtl_gpio_enter_critical(void);
void hal_rtl_aon_gpio_enter_critical(void);  // new
void hal_rtl_pon_gpio_enter_critical(void);  // new
void hal_rtl_gpio_exit_critical(void);
void hal_rtl_aon_gpio_exit_critical(void);
void hal_rtl_pon_gpio_exit_critical(void);
hal_status_t hal_rtl_gpio_init(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
void hal_rtl_gpio_deinit(phal_gpio_adapter_t pgpio_adapter);
void hal_rtl_gpio_set_dir(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
gpio_dir_t hal_rtl_gpio_get_dir(phal_gpio_adapter_t pgpio_adapter);
void hal_rtl_gpio_write(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
void hal_rtl_gpio_toggle(phal_gpio_adapter_t pgpio_adapter);
uint32_t hal_rtl_gpio_read(phal_gpio_adapter_t pgpio_adapter);
hal_status_t hal_rtl_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
uint32_t hal_rtl_gpio_read_debounce(phal_gpio_adapter_t pgpio_adapter);
void hal_rtl_gpio_debounce_disable(phal_gpio_adapter_t pgpio_adapter);
hal_status_t hal_rtl_gpio_irq_init(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
								   gpio_irq_callback_t callback, uint32_t arg);
void hal_rtl_gpio_irq_deinit(phal_gpio_irq_adapter_t pgpio_irq_adapter);
void hal_rtl_gpio_irq_set_trig_type(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
gpio_int_trig_type_t hal_rtl_gpio_irq_get_trig_type(phal_gpio_irq_adapter_t pgpio_adapter);
void hal_rtl_gpio_irq_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter);
void hal_rtl_gpio_irq_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t hal_rtl_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t debounce_us);
void hal_rtl_gpio_irq_debounce_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter);
uint32_t hal_rtl_gpio_irq_read(phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t hal_rtl_gpio_port_init(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
									uint32_t mask, gpio_dir_t dir);
void hal_rtl_gpio_port_deinit(phal_gpio_port_adapter_t pgpio_port_adapter);
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip
void hal_rtl_gpio_port_write(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data);
#else // Test chip
void hal_rtl_gpio_port_write(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, uint32_t io_data);
#endif

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip
uint32_t hal_rtl_gpio_port_read(phal_gpio_port_adapter_t pgpio_port_adapter);
#else // Test chip
uint32_t hal_rtl_gpio_port_read(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask);
#endif

hal_status_t hal_rtl_gpio_pull_ctrl(uint32_t pin_name, pin_pull_type_t pull_type);
hal_status_t hal_rtl_gpio_schmitt_ctrl(uint32_t pin_name, BOOLEAN ctrl);

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip
void hal_rtl_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir);
#else // Test chip
void hal_rtl_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, gpio_dir_t dir);
#endif

hal_status_t hal_rtl_gpio_drive_ctrl(uint32_t pin_name, uint8_t drv);
hal_status_t hal_rtl_gpio_slew_rate_ctrl(uint32_t pin_name, uint8_t slew_rate_func);

/** @} */ /* End of group hs_hal_gpio_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/**
  \brief  The data structure of the stubs functions of the GPIO HAL functions in ROM
*/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
typedef struct hal_gpio_func_stubs_s {
	phal_gpio_comm_adapter_t *ppgpio_comm_adp;
	phal_aon_gpio_comm_adapter_t *ppaon_gpio_comm_adp;
	phal_pon_gpio_comm_adapter_t *pppon_gpio_comm_adp;
	//void (*hal_gpio_en_ctrl) (BOOL en); // should be defunct
	//void (*hal_gpio_pclk_ctrl) (BOOL en); // should be defunct
	//void (*hal_gpio_sclk_ctrl) (BOOL en); // should be defunct
	//void (*hal_gpio_int_clk) (gpio_int_clk_t clk_sel); // should be defunct
	void (*hal_gpio_reg_irq)(gpio_type_t gpio_type, irq_handler_t irq_handler);
	void (*hal_gpio_comm_init)(phal_gpio_comm_adapter_t pgpio_comm_adp);
	void (*hal_aon_gpio_comm_init)(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);  // new
	void (*hal_pon_gpio_comm_init)(phal_pon_gpio_comm_adapter_t ppon_gpio_comm_adp);  // new
	void (*hal_gpio_comm_deinit)(void);
	void (*hal_aon_gpio_comm_deinit)(void);  // new
	void (*hal_pon_gpio_comm_deinit)(void);  // new
	void (*hal_gpio_enter_critical)(void);
	void (*hal_aon_gpio_enter_critical)(void);  // new
	void (*hal_pon_gpio_enter_critical)(void);  // new
	void (*hal_gpio_exit_critical)(void);
	void (*hal_aon_gpio_exit_critical)(void);  // new
	void (*hal_pon_gpio_exit_critical)(void);  // new
	hal_status_t (*hal_gpio_init)(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
	void (*hal_gpio_deinit)(phal_gpio_adapter_t pgpio_adapter);
	void (*hal_gpio_set_dir)(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
	gpio_dir_t (*hal_gpio_get_dir)(phal_gpio_adapter_t pgpio_adapter);
	void (*hal_gpio_write)(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
	void (*hal_gpio_toggle)(phal_gpio_adapter_t pgpio_adapter);
	uint32_t (*hal_gpio_read)(phal_gpio_adapter_t pgpio_adapter);
	hal_status_t (*hal_gpio_debounce_enable)(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
	uint32_t (*hal_gpio_read_debounce)(phal_gpio_adapter_t pgpio_adapter);
	void (*hal_gpio_debounce_disable)(phal_gpio_adapter_t pgpio_adapter);
	hal_status_t (*hal_gpio_irq_init)(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
									  gpio_irq_callback_t callback, uint32_t arg);
	void (*hal_gpio_irq_deinit)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	void (*hal_gpio_irq_set_trig_type)(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
	gpio_int_trig_type_t (*hal_gpio_irq_get_trig_type)(phal_gpio_irq_adapter_t pgpio_adapter);
	void (*hal_gpio_irq_enable)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	void (*hal_gpio_irq_disable)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	hal_status_t (*hal_gpio_irq_debounce_enable)(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t debounce_us);
	void (*hal_gpio_irq_debounce_disable)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	uint32_t (*hal_gpio_irq_read)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	hal_status_t (*hal_gpio_port_init)(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
									   uint32_t mask, gpio_dir_t dir);
	void (*hal_gpio_port_deinit)(phal_gpio_port_adapter_t pgpio_port_adapter);
	void (*hal_gpio_port_write)(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, uint32_t io_data);
	uint32_t (*hal_gpio_port_read)(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask);
	hal_status_t (*hal_gpio_pull_ctrl)(uint32_t pin_name, pin_pull_type_t pull_type);
	hal_status_t (*hal_gpio_schmitt_ctrl)(uint32_t pin_name, BOOLEAN ctrl);
	void (*hal_gpio_port_dir)(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, gpio_dir_t dir);
	hal_status_t (*hal_gpio_drive_ctrl)(uint32_t pin_name, uint8_t drv);
	hal_status_t (*hal_gpio_slew_rate_ctrl)(uint32_t pin_name, uint8_t slew_rate_func);
	uint32_t reserved[4];  // reserved space for next ROM code version function table extending.
} hal_gpio_func_stubs_t;
#else

typedef struct hal_gpio_func_stubs_s {
	phal_gpio_comm_adapter_t *ppgpio_comm_adp;
	phal_aon_gpio_comm_adapter_t *ppaon_gpio_comm_adp;
	phal_pon_gpio_comm_adapter_t *pppon_gpio_comm_adp;
	void (*hal_gpio_reg_irq)(gpio_type_t gpio_type, irq_handler_t irq_handler);
	hal_status_t (*hal_gpio_interrupt_clk_sel)(gpio_type_t gpio_type, uint8_t clk_sel);
	void (*hal_gpio_comm_init)(phal_gpio_comm_adapter_t pgpio_comm_adp);
	void (*hal_aon_gpio_comm_init)(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);
	void (*hal_pon_gpio_comm_init)(phal_pon_gpio_comm_adapter_t ppon_gpio_comm_adp);
	void (*hal_gpio_comm_deinit)(void);
	void (*hal_aon_gpio_comm_deinit)(void);
	void (*hal_pon_gpio_comm_deinit)(void);
	void (*hal_gpio_enter_critical)(void);
	void (*hal_aon_gpio_enter_critical)(void);
	void (*hal_pon_gpio_enter_critical)(void);
	void (*hal_gpio_exit_critical)(void);
	void (*hal_aon_gpio_exit_critical)(void);
	void (*hal_pon_gpio_exit_critical)(void);
	hal_status_t (*hal_gpio_init)(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
	void (*hal_gpio_deinit)(phal_gpio_adapter_t pgpio_adapter);
	void (*hal_gpio_set_dir)(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
	gpio_dir_t (*hal_gpio_get_dir)(phal_gpio_adapter_t pgpio_adapter);
	void (*hal_gpio_write)(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
	void (*hal_gpio_toggle)(phal_gpio_adapter_t pgpio_adapter);
	uint32_t (*hal_gpio_read)(phal_gpio_adapter_t pgpio_adapter);
	hal_status_t (*hal_gpio_debounce_enable)(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
	uint32_t (*hal_gpio_read_debounce)(phal_gpio_adapter_t pgpio_adapter);
	void (*hal_gpio_debounce_disable)(phal_gpio_adapter_t pgpio_adapter);
	hal_status_t (*hal_gpio_irq_init)(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
									  gpio_irq_callback_t callback, uint32_t arg);
	void (*hal_gpio_irq_deinit)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	void (*hal_gpio_irq_set_trig_type)(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
	gpio_int_trig_type_t (*hal_gpio_irq_get_trig_type)(phal_gpio_irq_adapter_t pgpio_adapter);
	void (*hal_gpio_irq_enable)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	void (*hal_gpio_irq_disable)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	hal_status_t (*hal_gpio_irq_debounce_enable)(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t debounce_us);
	void (*hal_gpio_irq_debounce_disable)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	uint32_t (*hal_gpio_irq_read)(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	hal_status_t (*hal_gpio_port_init)(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
									   uint32_t mask, gpio_dir_t dir);
	void (*hal_gpio_port_deinit)(phal_gpio_port_adapter_t pgpio_port_adapter);
	void (*hal_gpio_port_write)(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data);
	uint32_t (*hal_gpio_port_read)(phal_gpio_port_adapter_t pgpio_port_adapter);
	hal_status_t (*hal_gpio_pull_ctrl)(uint32_t pin_name, pin_pull_type_t pull_type);
	hal_status_t (*hal_gpio_schmitt_ctrl)(uint32_t pin_name, BOOLEAN ctrl);
	void (*hal_gpio_port_dir)(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir);
	hal_status_t (*hal_gpio_drive_ctrl)(uint32_t pin_name, uint8_t drv);
	hal_status_t (*hal_gpio_slew_rate_ctrl)(uint32_t pin_name, uint8_t slew_rate_func);
	uint32_t reserved[3];  // reserved space for next ROM code version function table extending.
} hal_gpio_func_stubs_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_GPIO_H */


/** @} */ /* End of group hs_hal_gpio */

