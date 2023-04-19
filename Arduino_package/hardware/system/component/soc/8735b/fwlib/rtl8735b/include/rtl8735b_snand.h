/**************************************************************************//**
 * @file     rtl8735b_snand.h
 * @brief    The header file of rtl8735b_snand.c.
 * @version  1.00
 * @date     2020-11-05
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020Realtek Corporation. All rights reserved.
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

#ifndef RTL8735B_SNAND_H
#define RTL8735B_SNAND_H

#include "rtl8735b_snafc_type.h"
#include "rtl8735b_irq.h"

/**

        \addtogroup hal_snand Serial NAND Flash Controller (SNAFC)
        \ingroup 8735b_hal
        \brief Serial NAND Flash Controller (Snand) module
        @{
*/

/**
  \brief  Enumeration to define SNAFC clkSrcSel
*/
typedef enum snafcSrcClkSel_e {
	SNAFC_SRCCLKSEL_0 = 0,  //!< 200 MHz Clock for RTL8735B
	SNAFC_SRCCLKSEL_1 = 1,  //!< 250 MHz Clock for RTL8735B
	SNAFC_SRCCLKSEL_MAX = 2,
} snafcSrcClkSel_t;

/**
  \brief  Enumeration to define SNAFC clock div
*/
typedef enum snafcClkDivSel_e {
	SNAFC_CLKDIV2 = 0,
	SNAFC_CLKDIV4 = 1,
	SNAFC_CLKDIV6 = 2,
	SNAFC_CLKDIV8 = 3,
	SNAFC_CLKDIV10 = 4,
	SNAFC_CLKDIV12 = 5,
	SNAFC_CLKDIV14 = 6,
	SNAFC_CLKDIV16 = 7,
	SNAFC_CLKDIV_MAX = 8,
} snafcClkDivSel_t;

/**
  \brief  Enumeration to define SNAFC speed level
*/
// zzw arduino cpp
enum {
	SNAFC_SPEED_SEL_0 = 0,  //!< slowest pre-defined value
	SNAFC_SPEED_SEL_1 = 1,  //!< slower pre-defined value
	SNAFC_SPEED_SEL_2 = 2,  //!< faster pre-defined value
	SNAFC_SPEED_SEL_3 = 3,  //!< fastest pre-defined value
};
typedef uint8_t snafc_clk_sel_t;

#define SNAFC_INITVAL_SETS (4) //!< 0->3, slowest default value to fastest default value

/**
  \brief  Enumeration to define flash IO mode
*/
typedef enum snafcBusWidth_e {
	SNAFC_SIO_WIDTH = 0,
	SNAFC_DIO_WIDTH = 1,
	SNAFC_QIO_WIDTH = 2
} snafcBusWidth_t;

/**
  \brief  Enumeration to define flash IO mode
*/
typedef enum snafcBusTypeMode_e {
	SnafcOneIOMode = 0,                  //!< Define One IO mode, 1-1-1
	SnafcDualOutputMode = 1,             //!< Define Dual Output mode, 1-1-2
	SnafcDualIOMode = 2,                 //!< Define Dual IO mode, 1-2-2
	SnafcQuadOutputMode = 3,             //!< Define Quad Output mode, 1-1-4
	SnafcQuadIOMode = 4,                 //!< Define Quad IO mode, 1-4-4
} snafcBusTypeMode_t;

/**
  \brief  Enumeration to define pinmux selection
*/
typedef enum snafcPinmuxSel_e {
	SnafcPinmuxCfg_0 = 0,               //!< only 1 pinmux cfg for SNAFC in RTL8735B
	SnafcPinmuxCfg_MAX = 1
} snafcPinmuxSel_t;


/**
  \brief  Enumeration to SNAFC DMA direction
*/
typedef enum snafcDmaDir_e {
	SNAFC_DMA_READ_DIR = 0,
	SNAFC_DMA_WRITE_DIR = 1
} snafcDmaDir_t;


/**
  \brief  Enumeration to SPI-NAND OP CMD
Typical qspi BUS configuration:
   * 1-0-0: ONLY 1-bit mode CMD.
   * 1-1-0: 1-bit mode CMD + 1-bit mode (ADDR+DUMMY / DUMMY+ADDR)
   * 1-1-1: 1-bit mode CMD + 1-bit mode (ADDR+DUMMY / DUMMY+ADDR) + 1-bit mode DATA.
   * 1-1-2: 1-bit mode CMD + 1-bit mode (ADDR+DUMMY / DUMMY+ADDR) + 2-bit mode DATA.
   * 1-1-4: 1-bit mode CMD + 1-bit mode (ADDR+DUMMY / DUMMY+ADDR) + 4-bit mode DATA.
   * 1-2-2: 1-bit mode CMD + 2-bit mode (ADDR+DUMMY / DUMMY+ADDR) + 2-bit mode DATA.
   * 1-4-4: 1-bit mode CMD + 4-bit mode (ADDR+DUMMY / DUMMY+ADDR) + 4-bit mode DATA.
*/
enum snandBusOpCmd_e {
	/*Init cmd*/
	SNAND_RDID_OP = 0x9F, /* (1-1-1) */ /* Get NAND flash's device ID */
	/* WARNING: MOST OF CASE, NO NEED TO ASK NAND DEVICE RESET */
	SNAND_RESET_OP = 0xFF, /* (1-0-0) */ /* Ask NAND flash device RESET */
	/* Set configuration (block protect, OTP feature) and get status (op_in_progress, write_enable_latch, erase_fail, program_fail, ecc_sts. */
	SNAND_GET_FEATURE_OP = 0x0F, /* (1-1-1), ADDR: regAddr */
	SNAND_SET_FEATURE_OP = 0x1F, /* (1-1-1), ADDR: regAddr */
	/* WRITE DATA to S-NAND */
	SNAND_WRITE_ENABLE_OP = 0x06, /* (1-1-1), ADDR: regAddr */
	SNAND_WRITE_DISABLE_OP = 0x04, /* (1-1-1), ADDR: regAddr */
	SNAND_BLOCK_ERASE_OP = 0xD8, /* (1-1-1), ADDR: regAddr */
	SNAND_PROGRAM_LOAD_OP = 0x02, /* (1-1-1), ADDR: columnAddr */
	SNAND_PROGRAM_LOAD_X4_OP = 0x32, /* (1-1-4), ADDR: columnAddr */
	SNAND_PROGRAM_EXECUTE_OP = 0x10, /* (1-1-0), ADDR: pageAddr */
	/* READ DATA from S-NAND */
	SNAND_PAGE_DATA_READ_OP = 0x13, /* (1-1-0), ADDR: pageAddr */
	SNAND_NORMAL_READ_OP = 0x03, /* (1-1-1), ADDR: columnAddr */
	SNAND_FAST_READ_OP = 0x0B, /* (1-1-1), ADDR: columnAddr */
	SNAND_FAST_READ_X2_OP = 0x3B, /* (1-1-2), ADDR: columnAddr */
	SNAND_FAST_READ_X4_OP = 0x6B, /* (1-1-4), ADDR: columnAddr */
	SNAND_FAST_READ_DIO_OP = 0xBB, /* (1-2-2), ADDR: columnAddr */
	SNAND_FAST_READ_QIO_OP = 0xEB, /* (1-4-4), ADDR: columnAddr */
};

enum snandGenericWaitOipSts_e {
	SNAND_STS_WAIT_OP_COMPLETE = 0,
	SNAND_STS_WAIT_OP_IN_PROPGRESS = 1,
};

enum snandGenericWelSts_e {
	SNAND_STS_WEL_NONE = 0,
	SNAND_STS_WRITE_ENABLE_LATCHED = 1,
};

enum snandGenericEraseSts_e {
	SNAND_STS_ERASE_NO_ERR = 0,
	SNAND_STS_ERASE_FAIL = 1,
};

enum snandGenericProgramSts_e {
	SNAND_STS_PROGRAM_NO_ERR = 0,
	SNAND_STS_PROGRAM_FAIL = 1,
};

enum snandGenericEccSts_e {
	SNAND_STS_ECC_NO_ERR = 0,
	SNAND_STS_ECC_ERR_AND_FIXED = 1,
	SNAND_STS_ECC_ERR_CANNOT_FIX = 2,
};

/**
  \brief  The data struct of CFG register
*/
typedef union _snafcInitParam_s {
	uint32_t l; /* long */
	struct {
		uint8_t lbc_bsz     : 2; //!< [1:0] LX bus burst size. 0: 16B; 1: 32B; 2: 64B; 3: 128B; (Default: 3)
		uint8_t rsvd0       : 2;
		uint8_t spi_clk_div : 3; //!< [6:4] clkDiv for SNFAC (after clkSecSel). 0: div2; 1: div4; 2: div6; 3: div8; 4: div10; 5: div12; 6: div14; 7: div16; (Default: 7)
		uint8_t rsvd1       : 1;
		uint8_t pipe_lat    : 2; //!< [9:8] pipe latency. data latch pipe latency. 0; 1; 2; 3; (Default: 0)
		uint8_t rsvd2       : 2;
		uint8_t precise     : 1; //!< [12] Precise, 1: LX bus DMA precise; (Default: 1)
		uint8_t dmaEndian   : 1; //!< [13] DMA_Endian, 1: DMA data is re-ordered to LX master bus; (Default: 0)
		uint8_t slvEndian   : 1; //!< [14] SLV_Endian, 1: Slave data is re-ordered to LX slave bus; (Default: 0)
		uint8_t rsvd3       : 1;
		uint8_t rsvd4       : 4;
		uint8_t dmaIe       : 1; //!< [20] DMA_IE, NAND flash controller DMA interrupt enable. 1: enable interrupt (Default: 0)
		uint8_t wb0         : 1; //!< [21] WBO, Write Read Byte Ordering. 1: high to low {3, 2, 1, 0}; (Default: 0)
		uint8_t rb0         : 1; //!< [22] RBO, Read Byte Ordering. 1: high to low {3, 2, 1, 0}; (Default: 0)
		uint8_t rsvd5       : 1;
		uint8_t rsvd6       : 8; //!< [31:24] RESERVED
	} reg;
} snafcInitParam_t, *psnafcInitParam_t;

/**
  \brief  The data struct that lists all flash commands
*/
#if 0
/*
 Philip: reference to Winbond's W25N512GVEIR.pdf (512Mb S-NAND flash (2K pages)) data sheet
 ToDo: not yet complete @ 2021/04/14, (so no yet commit to GIT)
*/
typedef struct _snand_cmd_s {
	volatile uint8_t wren;                      //!< Write Enable Command
	volatile uint8_t wrdi;                      //!< Write Enable Command
	volatile uint8_t rdsr;                      //!< Read Status Register Command
	volatile uint8_t wrsr;                      //!< Write Status Register Command
	volatile uint8_t rdsr2;                     //!< Read Status Register 2 Command
	volatile uint8_t wrsr2;                     //!< Write Status Register 2 Command
	volatile uint8_t rdsr3;                     //!< Read Status Register 3 Command
	volatile uint8_t wrsr3;                     //!< Write Status Register 3 Command
	volatile uint8_t rear;                      //!< Read Extended Address Register Command
	volatile uint8_t wear;                      //!< Write Extended Address Register Command
	volatile uint8_t se;                        //!< Sector Erase Command
	volatile uint8_t be;                        //!< Block Erase Command (128K-Byte)(64 pages x 2K bytes/page)
	volatile uint8_t ce;                        //!< Chip Erase Command
	volatile uint8_t rdid;                      //!< Read Flash ID Command
	volatile uint8_t read;                      //!< Read Command
	volatile uint8_t fread;                     //!< Fast Read Command
	volatile uint8_t dread;                     //!< Dual Output Read Command (1-1-2)
	volatile uint8_t str_2read;                 //!< Dual IO Read Command (1-2-2)
	//volatile uint8_t dtr_2read;                 //!< DTR Daul IO Read Command (2-2D-2D)
	volatile uint8_t qread;                     //!< Quad Output Read Command (1-1-4)
	volatile uint8_t str_4read;                 //!< Quad IO Read Command (1-4-4), also for QPI(4-4-4)
	//volatile uint8_t dtr_4read;                 //!< DTR Quad IO Read Command (1-4D-4D), also for QPI DTR(4-4D-4D/4D-4D-4D)
	volatile uint8_t pp;                        //!< Page Program Command
	volatile uint8_t dp;                        //!< Enter Deep Power Down Command
	volatile uint8_t udp;                       //!< Enter Ultra Deep Power Down Command
	volatile uint8_t rdp;                       //!< Release From Deep Power Down Command
	volatile uint8_t en_spi;                    //!< Enter SPI Mode Command
	volatile uint8_t en_qpi;                    //!< Enter QPI Mode Command
	volatile uint8_t block_lock;                //!< Individual Block Lock Command
	volatile uint8_t block_unlock;              //!< Individual Block Unlock Command
	volatile uint8_t global_lock;               //!< Global Block Lock Command
	volatile uint8_t global_unlock;             //!< Global Block Unlock Command
	volatile uint8_t rd_block_lock;             //!< Read Block Lock State Command
	volatile uint8_t en_reset;                  //!< Enable Reset Command
	volatile uint8_t reset;                     //!< Reset Command
	volatile uint8_t read_sfdp;                 //!< Read SFDP Command
} snand_cmd_t, *psnand_cmd_t;
#endif

typedef struct snand_bus_cfg_s {
	volatile uint8_t w_cmd_cycle; // w_cmd_cycle (usually 1 byte cycle for CMD)
	volatile uint8_t w_cmd; // w_cmd (PROGRAM_LOAD_OP, PROGRAM_LOAD_X4_OP)
	volatile uint8_t
	w_addr_cycle; // w_addr_cycle (0 means NO addr cycle; 1 for 1 address cycle; ..; 3 for 3 address cycle; 4 for 4 address cycle)(For pageAddr==3, usually colAddr=2)
	volatile uint8_t w_addr_io; // w_addr_io (0 for SIO, 1 for DIO, 2 for QIO)
	volatile uint8_t w_data_io; // w_addr_io (0 for SIO, 1 for DIO, 2 for QIO)
	volatile uint8_t r_cmd_cycle; // r_cmd_cycle (usually 1 byte cycle for CMD)
	volatile uint8_t r_cmd; // r_cmd (NORMAL_READ_OP, FAST_READ_OP, FAST_READ_X2_OP, FAST_READ_X4_OP, FAST_READ_DIO_OP, FAST_READ_QIO_OP)
	volatile uint8_t
	r_addr_cycle; // r_addr_cycle (0 means NO addr cycle; 1 for 1 address cycle; ..; 3 for 3 address cycle; 4 for 4 address cycle)(For pageAddr==3, usually colAddr=2)
	volatile uint8_t r_addr_io; // r_addr_io (0 for SIO, 1 for DIO, 2 for QIO)
	volatile uint8_t r_addr_dummy_cycle; // r_addr_dummy_cycle (0 means NO dummy cycle (rear); 1 for 1 dummy cycle (typical); 2 for 2 dummy cycle)
	volatile uint8_t r_data_io; // r_data_io (0 for SIO, 1 for DIO, 2 for QIO)
	volatile uint8_t rsvd; // padding
} snand_bus_cfg_t;

#define DEFAULT_W_CMD_CYCLE (3)
#define DEFAULT_W_CMD_OP (SNAND_PROGRAM_LOAD_OP)
#define DEFAULT_W_CMD_IOWIDTH (SNAFC_SIO_WIDTH)
#define DEFAULT_W_ADDR_CYCLE (3)
#define DEFAULT_W_DAT_IOWIDTH (SNAFC_SIO_WIDTH)
#define DEFAULT_R_CMD_CYCLE (3)
#define DEFAULT_R_CMD_OP (SNAND_NORMAL_READ_OP)
#define DEFAULT_R_CMD_IOWIDTH (SNAFC_SIO_WIDTH)
#define DEFAULT_R_ADDR_CYCLE (3)
#define DEFAULT_R_DAT_IOWIDTH (SNAFC_SIO_WIDTH)

/* callback function, can use default, or use customer specific wait function */
typedef uint32_t snand_wait_snand_rdy_t(uint32_t timeout);
typedef uint32_t snand_check_wel_sts_t(void);
typedef uint32_t snand_check_erase_sts_t(void);
typedef uint32_t snand_check_pgm_sts_t(void);
typedef uint32_t snand_check_ecc_sts_t(void);
typedef uint32_t snand_block_protect_none_t(void);
typedef uint32_t snand_block_protect_all_t(void);
typedef uint32_t snand_enable_quad_mode_t(void);
typedef uint32_t snand_disable_quad_mode_t(void);
typedef uint32_t snand_enable_ecc_mode_t(void);
typedef uint32_t snand_disable_ecc_mode_t(void);

/**
  \brief  The data struct of Snand adaptor
*/
typedef struct _hal_snafc_adaptor_s {
	/* platform-depend info */
	irq_config_t irq_handle;            //!< Interrupt handler, reserved
	snafcInitParam_t initVal[SNAFC_INITVAL_SETS];  //!< Init register setting for difference clkSrcSel
	snafc_clk_sel_t clkSel;             //!< clk configuration selection (0~3, slowest to fastest within pre-defined initVal)
	uint8_t bakClkSrcSel;               //!< Backup original clkSrcSel at init, and restore bakClkSrcSel at deinit
	snafcPinmuxSel_t pinmuxSel;         //!< Pinmux selection (dummy usage in RTL8735b)
	uint8_t rsvd0;                      //!< RESERVED
	uint32_t maxCtrlRdyCnt;             //!< max value of software counter for polling SNAFC cltr ready
	uint32_t maxDmaRdyCnt;              //!< max value of software counter for polling SNAFC dma ready
	uint32_t maxWaitOipCnt;             //!< max value of software counter for polling S-NAND OIP sts
	/* device-depend info */
	uint8_t devId[3];                   //!< Flash Device ID for S-NAND
	uint8_t flashType;                  //!< Flash Device type for S-NAND, 0: no onChip ECC, 1: with onChip ECC
	uint32_t pageSize;                  //!< pageSize (unit: byte) (Usually 2048)
	uint32_t spareSize;                 //!< spareSize (unit: byte) (Usually 64)
	uint8_t pagePerBlk;                 //!< page per block (Usually 64). blockSize = (pageSize+spareSize)xpagePerBlk
	uint8_t blkPerDev;                  //!< block per device. For pageSize 2KB, capacity 512Mb's device, blkPerDev is 512; 1Gb device is 1024; 2Gb device is 2048.
	uint8_t dma_en;                     //!< Indicate whether Transfer mode is DMA (1) or PIO (0)
	uint8_t rsvd1;                      //!< RESERVED
	uint32_t col_addr;                      //!< Column Address for specific CA[11:0] in S-NAND bus protocol. (default 0)
	snand_bus_cfg_t snand_cmd_info;     //!< Indicate snand_cmd_info (w_cmd_cycle, w_cmd, w_addr_io, w_data_io)(r_cmd_cycle, r_cmd, r_addr_io, r_data_io)
	snand_wait_snand_rdy_t *funcWaitSnandReady; //!< S-NAND device dependent wait ready rule
	snand_check_wel_sts_t *funcChkWelSts;   //!< S-NAND device dependent checking WEL status (checking WRITE_ENABLE or not)
	snand_check_erase_sts_t *funcChkEraseSts;   //!< S-NAND device dependent checking ERASE FAIL sts for the last ERASE
	snand_check_pgm_sts_t *funcChkPgmSts;   //!< S-NAND device dependent checking PROGRAM FAIL sts for the last PROGRAM_EXECUTE
	snand_check_ecc_sts_t *funcChkEccSts;   //!< S-NAND device dependent checking ECC sts for the last READ operation
	snand_block_protect_none_t *funcBlockProtectNone;   //!< S-NAND device dependent block protect none rule
	snand_block_protect_all_t *funcBlockProtectAll; //!< S-NAND device dependent block protect all rule
	snand_enable_quad_mode_t *funcEnQuadSpiMode;    //!< S-NAND device dependent enable QUAD SPI bus mode rule
	snand_disable_quad_mode_t *funcDisQuadSpiMode;  //!< S-NAND device dependent disable QUAD SPI bus mode rule
	snand_enable_ecc_mode_t *funcEnOnChipEccMode;    //!< S-NAND device dependent enable onChip ECC mode rule
	snand_disable_ecc_mode_t *funcDisOnChipEccMode;  //!< S-NAND device dependent disable onChip ECC mode rule
} hal_snafc_adaptor_t, *phal_snafc_adaptor_t;

/**
  \brief  The data struct of flash controller stub functions. ROM code functions are accessed in RAM code through stub functions.
*/
typedef struct hal_snand_func_stubs_s {
	void (*hal_snand_init)(void *adaptor);
	void (*hal_snand_deinit)(void *adaptor);
	uint32_t (*hal_snand_reset_to_spi)(void *adaptor);
	uint32_t (*hal_snand_read_id)(void *adaptor);
	void (*hal_snand_set_quad_enable)(void *adaptor);
	void (*hal_snand_unset_quad_enable)(void *adaptor);
	void (*hal_snand_set_feature)(void *adaptor, uint32_t cmd, uint32_t data);
	void (*hal_snand_set_feature_no_check)(void *adaptor, uint32_t cmd, uint32_t data);
	uint32_t (*hal_snand_get_feature)(void *adaptor, uint32_t cmd);
	uint32_t (*hal_snand_wait_ready)(void *adaptor);
	void (*hal_snand_set_write_enable)(void *adaptor);
	void (*hal_snand_set_write_disable)(void *adaptor);
	uint32_t (*hal_snand_block_erase)(void *adaptor, uint32_t blkPageAddr);
	uint32_t (*hal_snand_page_program)(void *adaptor, uint32_t blkPageAddr);
	uint32_t (*hal_snand_pageWrite)(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
	uint32_t (*hal_snand_pageRead)(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
	uint32_t reserved[8];  // reserved space for next ROM code version function table extending.
} hal_snand_func_stubs_t;

/**

        \addtogroup hal_rtl_snand_func S-NAND Flash Controller HAL ROM APIs
        @{
*/
extern void hal_rtl_snand_init(void *adaptor);
extern void hal_rtl_snand_deinit(void *adaptor);
extern uint32_t hal_rtl_snand_issusResetOpCmd(void *adaptor);
extern uint32_t hal_rtl_snand_issueReadIdOpCmd(void *adaptor);
extern void hal_rtl_snand_quadModeEnable(void *adaptor);
extern void hal_rtl_snand_quadModeDisable(void *adaptor);
extern void hal_rtl_snand_issueSetFeatureRegisterOpCmd(void *adaptor, uint32_t feature_addr, uint32_t data);
extern void hal_rtl_snand_issueSetFeatureRegisterOpCmd_NoCheck(void *adaptor, uint32_t feature_addr, uint32_t data);
extern uint32_t hal_rtl_snand_issueGetFeatureRegisterOpCmd(void *adaptor, uint32_t feature_addr);
extern uint32_t hal_rtl_snand_waitSnandOipComplete(void *adaptor);
extern void hal_rtl_snand_issueWriteEnableOpCmd(void *adaptor);
extern void hal_rtl_snand_issueWriteDisableOpCmd(void *adaptor);
extern uint32_t hal_rtl_snand_issueBlockEraseOpCmd(void *adaptor, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_issueProgramExecuteOpCmd(void *adaptor, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_pioPageWrite(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_pioPageRead(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_dmaPageWrite(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_dmaPageRead(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_pageWrite(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);
extern uint32_t hal_rtl_snand_pageRead(void *adaptor, void *memAddr, uint32_t byteLens, uint32_t blkPageAddr);

/** *@} */ /* End of group hal_rtl_snand_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/** *@} */ /* End of group hal_snand */

#endif /* RTL8195BHP_snand_H */
