/**************************************************************************//**
 * @file     otp_boot_cfg.h
 * @brief    Define the structure types for boot flow configuration those from OTP.
 * @version  V1.00
 * @date     2022-07-27
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

#ifndef _OTP_BOOT_CFG_H
#define _OTP_BOOT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif
#include "platform_conf.h"

// TODO: modification for 8735b: defines the system configuration in OTP

#define FLASH_PINS_MAX_SEL                  (1)
#define ROTPK_HSH_OTP_BASE_ADDR             (0x250)
#define HUK_OTP_BASE_ADDR                   (0x370)
#define SEC_KEY_OTP_BASE_ADDR               (0x430)
#define SJTAG_S_KEY_OTP_BASE_ADDR           (0x3B0)
#define SJTAG_NS_KEY_OTP_BASE_ADDR          (0x3F0)

#define ROTPK_HSH_RMA_OTP_BASE_ADDR         (0x1D0)
#define HUK_RMA_OTP_BASE_ADDR               (0x470)
#define SEC_KEY_RMA_OTP_BASE_ADDR           (0x1F0)

#define RMA0_PTN_BASE_ADDR                  (0x330)
#define RMA1_MGNPTN_BASE_ADDR               (0x338)
#define RMA1_CHK_SIGN_FLSH_OFFSET           (0x6000)
#define RMA1_SIGN_NAND_PAGE_START           (0x30)
#define RMA1_SIGN_NAND_PAGE_END             (0x37)

#define RMA0_PTN_SIZE                       (8)
#define RMA1_MGN_PTN_SIZE                   (8)
#define RMA1_CHK_SIGN_SIZE                  (64)
#define RMA1_CHK_PBK_SIZE                   (32)
#define RMA1_TOCKEN_SIZE                    (4)
#define RMA2_UUID_PTN_SIZE                  (4)

#define HIGH_VAL_SZ_LOCK_ADDR               (0x350)
#define HIGH_VAL_SSZ_LOCK_ADDR              (0x49F)
#define HIGH_VAL_SSZ_LOCK_CHK_MAX_SIZE      (1)
#define HIGH_VAL_SZ_LOCK_CHK_MAX_SIZE       (32)
#define HIGH_VAL_SZ_WLOCK_ENTRY_VAL         (0x0)

#define OTP_PHY_CTRL_TEST_M_FUNC_ADDR       (0x5B0)
#define OTP_PHY_CTRL_NORM_M_FUNC_ADDR       (0x5B4)
#define OTP_PHY_CTRL_NORM_M_CUST_FUNC_ADDR  (0x5B5)

#define OTP_KC_VANTI_ADDR                   (0x548)
#define OTP_BL_VANTI_ADDR                   (0x550)
#define OTP_FW_VANTI_ADDR                   (0x570)

enum high_val_assets_lock_sel {
	HighVal_SSZ_R_W_LOCK        = 0x1,
	HighVal_SZ_W_LOCK           = 0x2
};

enum high_val_assets_lock_chk {
	HighVal_SSZ_R_W_LOCK_CHK_VAL = 0x0,
	HighVal_SSZ_R_W_LOCK_SET_VAL = 0xFE,
	HighVal_SZ_W_LOCK_CHK_VAL    = 0xFF,
};

/**
  \brief  Define the boot method
*/
enum boot_type_e {
	BootFromNORFlash            = 0,
	BootFromNANDFlash           = 1,
	BootFromUART                = 2,
	BootFromSDCARD              = 3,
	BootFromUSBDEV              = 4,
	BootFromTestModeUART        = 15,
	BootFromJTAG_FPGALOAD       = 16
};

/**
  \brief  Define the debugging port configuration
*/
enum debug_port_cfg_e {
	DbgPorSWD           = 0,
	DbgPorJTag          = 1
};

enum debug_port_pin_sel_e {
	DbgPort_pin_S0      = 0,
	DbgPort_pin_S1      = 1
};


/**
  \brief  Define the pin selection for flash boot
*/
enum flas_boot_pin_sel_e {
	BootFlash_DualIOS0  = 0    /*!< flash pin on C0~C5*/
};

enum flas_boot_io_mod_sel_e {
	BootFlash_SpicOneIOMode   = 0,    /*!< SpicOneIOMode */
	BootFlash_SpicDualIOMode  = 1,    /*!< SpicDualIOMode */
	BootFlash_SpicQuadIOMode  = 2,    /*!< SpicQuadIOMode */
};

/**
  \brief  The data struct of flash pins selected by users
*/
typedef struct _flash_pin_sel_s {
	uint32_t pin_cs;                          //!< flash chip select pin
	uint32_t pin_clk;                         //!< flash clock pin
	uint32_t pin_d0;                          //!< flash data pin 0
	uint32_t pin_d1;                          //!< flash data pin 1
	uint32_t pin_d2;                          //!< flash data pin 2
	uint32_t pin_d3;                          //!< flash data pin 3
} flash_pin_sel_t, *pflash_pin_sel_t;

/**
  \brief  Define the UART port selection for UART boot
*/
enum uart_boot_port_sel_e {
	BootUART1           = 0,
	BootUART2           = 1,
	BootUART3           = 2
};

/**
  \brief  Define the pin selection for UART boot
*/
enum uart_boot_pin_sel_e {
	BootUART_S0         = 0,
	BootUART_S1         = 1
};

/**
  \brief  Define the boot debugging UART port selection
*/
enum boot_dbg_uart_sel_e {
	BootDbgUART1        = 0,
	BootDbgUART2        = 1,
	BootDbgUART3        = 2
};

/**
  \brief  Define the boot debugging message on/off control
*/
enum boot_dbg_msg_ctrl_e {
	BootDbgMsgOn        = 0,
	BootDbgMsgOff       = 1
};

enum boot_nand_flh_clk_sel_e {
	BootNAND_Clk_Sel_62M    = 0x0,
	BootNAND_Clk_Sel_31M    = 0x1,
	BootNAND_Clk_Sel_20M    = 0x2,
	BootNAND_Clk_Sel_12M    = 0x3
};

enum boot_nand_flh_latch_sel_e {
	BootNAND_Latch_Sel_Delay0T    = 0x0,
	BootNAND_Latch_Sel_Delay1T    = 0x1,
	BootNAND_Latch_Sel_Delay2T    = 0x2,
	BootNAND_Latch_Sel_Delay3T    = 0x3
};

typedef struct boot_comm_cfg_s {
	__IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
	__IOM uint8_t boot_pin_sel    : 4;       /*!< [7..4] Boot pins selection */
} boot_comm_cfg_t, *pboot_comm_cfg_t;

typedef struct norflash_boot_cfg_s {
	__IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
	__IOM uint8_t io_mode_sel     : 2;       /*!< [5..4] Flash IO mode selection */
	__IOM uint8_t pin_sel         : 2;       /*!< [7..6] NOR flash pin selection */
} norflash_boot_cfg_t, *pnorflash_boot_cfg_t;

typedef struct nandflash_boot_cfg_s {
	__IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
	__IOM uint8_t io_mode_sel     : 2;       /*!< [5..4] Flash IO mode selection */
	__IOM uint8_t pin_sel         : 2;       /*!< [7..6] NAND flash pin selection */
} nandflash_boot_cfg_t, *pnandflash_boot_cfg_t;

typedef struct uart_boot_cfg_s {
	__IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
	__IOM uint8_t port_sel        : 2;       /*!< [5..4] UART port selection */
	__IOM uint8_t rx_pin_sel      : 1;       /*!< [6] UART RX pin selection */
	__IOM uint8_t tx_pin_sel      : 1;       /*!< [7] UART TX pin selection */
} uart_boot_cfg_t, *puart_boot_cfg_t;

typedef struct sdcard_boot_cfg_s {
	__IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
	__IOM uint8_t boot_pin_sel    : 4;       /*!< [7..4] Boot pins selection */
} sdcard_boot_cfg_t, *psdcard_boot_cfg_t;

typedef struct usbdev_boot_cfg_s {
	__IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
	__IOM uint8_t boot_pin_sel    : 4;       /*!< [7..4] Boot pins selection */
} usbdev_boot_cfg_t, *pusbdev_boot_cfg_t;

typedef union {
	__IOM uint8_t byte;
	union {
		boot_comm_cfg_t boot_comm;
		norflash_boot_cfg_t norflash_boot;
		nandflash_boot_cfg_t nandflash_boot;
		uart_boot_cfg_t uart_boot;
		sdcard_boot_cfg_t sdcard_boot;
		usbdev_boot_cfg_t usbdev_boot;
	} bit;
} otp_boot_cfg1_t, *potp_boot_cfg1_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t uart_boot_baud_sel   : 3;       /*!< [2..0] UART boot baud rate selection */
		__IOM uint8_t boot_rom_dbg_msg_dis : 1;       /*!< [3..3] Boot ROM debugging message disable */
		__IOM uint8_t rom_log_port_sel     : 2;       /*!< [5..4] ROM Log UART port selection */
		__IOM uint8_t rom_log_rx_pin_sel   : 1;       /*!< [6..6] ROM Log UART RX pin selection */
		__IOM uint8_t rom_log_tx_pin_sel   : 1;       /*!< [7..7] ROM Log UART TX pin selection */
	} bit;
} otp_boot_cfg2_t, *potp_boot_cfg2_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t sb_otp_err_chk_en: 1;       /*!< [0..0] Before Secure boot load high value assets check otp error enable: 1'b0: disable otp err check,
                                                                                                                   1'b1: enable otp err check */
		__IM  uint8_t : 3;                        /*!< [3..1] Reserved */
__IOM uint8_t sect_ld_vrf_en   :
		1;       /*!< [4..4] img section load check enable: 1'b0: disable img section load check, without img section load check verify flow;
                                                                                             1'b1: enable img section load check, with img section load verify flow */
		__IOM uint8_t img_hsh_en       : 1;       /*!< [5..5] img hash check enable: 1'b0: disable img hash check, without img hash check verify flow;
                                                                                     1'b1: enable img hash check, with img hash check verify flow */
		__IOM uint8_t tb_en            : 1;       /*!< [6..6] Trust boot enable: 1'b0: disable trust boot, without img manifest signature verify flow;
                                                                                  1'b1: enable trust boot, with img manifest signature verify flow */
		__IOM uint8_t sb_en            : 1;       /*!< [7..7] Secure boot enable: 1'b0: disable secure boot, run plaintext boot flow;
                                                                                  1'b1: enable secure boot, run secue boot flow */
	} bit;
} otp_boot_cfg3_t, *potp_boot_cfg3_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t dbg_port_mod_sel        : 1;       /*!< [0..0] Debug Port mode Select(1'b0: TM SWD/ 1'b1: TM JTAG */
		__IOM uint8_t dbg_port_tms_io_pin_sel : 1;       /*!< [1..1] Debug Port JTAG TMS/SWD IO pin select
                                                                 1'b0: TM SWD_IO S0/ JTAG_TMS S0
                                                                 1'b1: TM SWD_IO S1/ JTAG_TMS S1
                                                      */
		__IOM uint8_t dbg_port_clk_pin_sel    : 1;       /*!< [2..2] Debug Port JTAG/SWD Clock pin select
                                                                 1'b0: TM SWD_CK S0/ JTAG_CLK S0
                                                                 1'b1: TM SWD_CK S1/ JTAG_CLK S1
                                                      */
		__IOM uint8_t dbg_port_voe_en         : 1;       /*!< [3..3] Debug Port VOE enable
                                                                 1'b0: VOE Debug Port disable
                                                                 1'b1: VOE Debug Port enable
                                                      */
		__IOM uint8_t dbg_port_voe_sel        : 1;       /*!< [4..4] Debug Port VOE Select
                                                                 1'b0: VOE Using SWD to Debug
                                                                 1'b1: VOE Using JTAG Chain mode,
                                                                       this will influence TM forced to using JTAG chain mode
                                                                 */
		__IM  uint8_t : 3;
	} bit;
} otp_boot_cfg4_t, *potp_boot_cfg4_t;

typedef union {
	__IOM uint32_t word;

	struct {
		otp_boot_cfg1_t cfg1;                 /*!< [0..7] boot configuration 1, otp logical addr 0x74 */
		otp_boot_cfg2_t cfg2;                 /*!< [8..15] boot configuration 2, otp logical addr 0x75 */
		otp_boot_cfg3_t cfg3;                 /*!< [16..23] boot configuration 3, otp logical addr 0x76 */
		otp_boot_cfg4_t cfg4;                 /*!< [24..31] boot configuration 4, otp logical addr 0x77 */
	} byte;
} otp_boot_cfg_t, *potp_boot_cfg_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IM  uint8_t : 4;
		__IOM uint8_t boot_normal_sic_en      : 1;       /*!< [4..4] Boot Normal mode SIC enable (SW Only)
                                                                 0:SIC Disable
                                                                 1:SIC Enable(CPU operate enable & pinmux)  */
		__IM  uint8_t : 3;
	} bit;
} otp_boot_cfg5_t, *potp_boot_cfg5_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t rom_dcache_dis          : 1;       /*!< [0..0] ROM dcache disable control (1'b0: not disable/ 1'b1: disable */
		__IOM uint8_t ntlv_img_ld_en          : 1;       /*!< [1..1] Non-TLV IMG Format load enable: 1'b0: disable, 1'b1: enable */
		__IOM uint8_t fcs_rom_flow_dis        : 1;       /*!< [2..2] Fast Camera Start rom flow disable control (1'b0: not disable/ 1'b1: disable */
		__IOM uint8_t boot_rom_adv_dbg_en     : 1;       /*!< [3..3] Boot ROM advanced debugging message enable control (1'b0: disable/ 1'b1: enable */
		__IOM uint8_t normal_sw_trap_chk_en   : 1;       /*!< [4..4] Boot ROM Normal sw trap check enable control (1'b0: disable/ 1'b1: enable */
		__IOM uint8_t bl_img_rollback_chk_en  : 1;       /*!< [5..5] Boot loader IMG rollback check enable control (1'b0: disable/ 1'b1: enable */
		__IOM uint8_t kc_img_rollback_chk_en  : 1;       /*!< [6..6] Key certificate IMG rollback check enable control (1'b0: disable/ 1'b1: enable */
		__IM  uint8_t : 1;
	} bit;
} otp_boot_cfg7_t, *potp_boot_cfg7_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t adj_vol_en_ctrl         : 1;       /*!< [0..0] Adjust voltage enable control (1'b0: disable/ 1'b1: enable */
		__IOM uint8_t adj_vol_level           : 4;       /*!< [4..1] Adjust voltage level when enablt set: level reference AON 0x10[7:4] */
		__IM  uint8_t : 3;
	} bit;
} otp_boot_cfg8_t, *potp_boot_cfg8_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t nand_clk_latch_ctrl_en  : 1;       /*!< [0..0] NAND Flash clock & latch enable control (1'b0: disable/ 1'b1: enable */
		__IOM uint8_t nand_clk_sel            : 2;       /*!< [2..1] NAND Flash clock select(2'b0: 62MHz, 2'b01: 31MHz, 2'b10: 20MHz, 3'b11: 12MHz */
		__IOM uint8_t nand_latch_sel          : 2;       /*!< [4..3] NAND Flash latch select(2'b0: no delay, 2'b01: delay 1T, 2'b10: delay 2T, 2'b11: delay 3T) */
		__IM  uint8_t : 3;
	} bit;
} otp_boot_cfg9_t, *potp_boot_cfg9_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t rng_clk_sel             : 2;       /*!< [1..0] RNG Clock select: (2'b0: HI_XTAL40M_LO32K, 2'b01: HI_XTAL40M_LO128K,
                                                                              2'b10: HI_PLL40M_LO32K, 3'b11: HI_PLL40M_LO128K */
		__IOM uint8_t rng_selft_en            : 1;       /*!< [2..2] RNG Selftest module enable: 1'b0: disable selft, 1'b1: enable selft */
		__IOM uint8_t ld_rng_en               : 1;       /*!< [3..3] Load high value assets random enable: 1'b0: disable random load, 1'b1: enable random load */
		__IOM uint8_t rng_delay_unit_sel      : 2;       /*!< [5..4] RNG delay us unit select: (2'b0: 100us, 2'b01: 150us,
                                                                                                2'b10: 200us, 3'b11: 300us */
		__IM uint8_t  : 1;
__IOM uint8_t ld_rng_delay_en         :
		1;       /*!< [7..7] Load high value assets random delay enable: 1'b0: disable random delay, 1'b1: enable random delay */
	} bit;
} otp_boot_cfg10_t, *potp_boot_cfg10_t;

/**
  \brief  Define the device life cycle state in eFuse.
*/
enum dev_lfc_state_e {
	LfC_RMA                     = 0,    // Life Cycle State: RMA state
	LfC_Deployed                = 4,    // Life Cycle State: Deployed state
	LfC_Development             = 6,    // Life Cycle State: Development/Device manufacture state
	LfC_Chip_Manufactur         = 7     // Life Cycle State: Chip manufacture state
};

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t dev_lfc_state     : 3;       /*!< [2..0] device life cycle state  */
		__IM  uint8_t                   : 4;       /*!< [6..3] Reserved */
		__IOM uint8_t secure_lock       : 1;       /*!< [7..7] Secure book lock: is allow to load un-encrypted image */
	} bit;
} efuse_dev_lfc_state_t, *pefuse_dev_lfc_state_t;

typedef union {
	__IOM uint32_t word;

	struct {
		__IOM uint32_t bt_en           : 2;       /*!< [1..0] BT function enable */
		__IOM uint32_t bt_mesh_en      : 2;       /*!< [3..2] BT mesh network function enable */
		__IOM uint32_t trust_zone_en   : 2;       /*!< [5..4] trust zone enable */
		__IOM uint32_t sec_boot_en     : 2;       /*!< [7..6] secure boot enable */
		__IM  uint32_t                 : 2;       /*!< [9..8] Reserved */
		__IOM uint32_t limit_io        : 2;       /*!< [11..10] limit_io enable */
		__IOM uint32_t cpu_clk_sel     : 2;       /*!< [13..12] cpu clock select */
		__IOM uint32_t mcm_flash_type  : 2;       /*!< [15..14] MCM flash type: 11/00: 2M, 01: 1M, 10: 2M downgrad as 1M */
		__IM  uint32_t                 : 18;      /*!< [31..16] Reserved */
	} bit;
} efuse_chip_func_en_t, *pefuse_chip_func_en_t;

#define OTPBootCfg1_LOGL_Offset         (0x74)
#define OTPBootCfg2_LOGL_Offset         (0x75)
#define OTPBootCfg3_LOGL_Offset         (0x76)
#define OTPBootCfg4_LOGL_Offset         (0x77)
#define OTPBootCfg5_LOGL_Offset         (0x78)
#define OTPBootCfg6_LOGL_Offset         (0x79)
#define OTPBootCfg7_LOGL_Offset         (0x7C)
#define OTPBootCfg8_LOGL_Offset         (0x7D)
#define OTPBootCfg9_LOGL_Offset         (0x7E)
#define OTPBootCfg10_LOGL_Offset        (0x7F)


#define OTPBootCfg1Offset               (0x14)
#define OTPBootCfg2Offset               (0x15)
#define OTPBootCfg3Offset               (0x16)
#define OTPBootCfg4Offset               (0x17)
#define OTPBootCfg5Offset               (0x18)
#define OTPBootCfg6Offset               (0x19)
#define OTPBootCfg7Offset               (0x1C)
#define OTPBootCfg8Offset               (0x1D)
#define OTPBootCfg9Offset               (0x1E)
#define OTPBootCfg10Offset              (0x1F)


#define OTPAutoLoadRegBase        (0x400090C0UL)

// Registers for OTP auto-load
#define otpBootCfg                ((otp_boot_cfg_t *)(OTPAutoLoadRegBase + OTPBootCfg1Offset))
#define otpBootCfg5               ((otp_boot_cfg5_t *)(OTPAutoLoadRegBase + OTPBootCfg5Offset))
#define otpBootCfg7               ((otp_boot_cfg7_t *)(OTPAutoLoadRegBase + OTPBootCfg7Offset))
#define otpBootCfg9               ((otp_boot_cfg9_t *)(OTPAutoLoadRegBase + OTPBootCfg9Offset))
#define otpBootCfg10              ((otp_boot_cfg10_t *)(OTPAutoLoadRegBase + OTPBootCfg10Offset))


#ifdef __cplusplus
}
#endif

#endif /* _OTP_BOOT_CFG_H */
