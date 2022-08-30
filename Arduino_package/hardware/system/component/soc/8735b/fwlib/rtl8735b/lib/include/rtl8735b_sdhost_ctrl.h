/**************************************************************************//**
 * @file    rtl8735b_sdhost_ctrl.h
 * @brief    The macros and types used by SD Host HAL code only.
 * @version V1.00
 * @date    2021-10-25
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
#ifndef _RTL8735B_SDHOST_CTRL_H_
#define _RTL8735B_SDHOST_CTRL_H_
#include "static_assert.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/// Defines the length of CSD register in byte
#define SD_CSD_LEN                   16

/// Defines the max. timeout value when checking the flag of command complete
#define SDHOST_CMD_CPLT_TIMEOUT      5000        // 5 ms
/// Defines the max. timeout value when checking the flag of transfer complete
//#define SDHOST_XFER_TIMEOUT_MAX      0xF0000000
/// Defines the timeout value when checking transfer complete
#define SDHOST_XFER_CPLT_TIMEOUT     3000000     // 3 s
/// Defines the timeout value when checking small transfer complete
#define SDHOST_SMALL_XFER_TIMEOUT    5000        // 5 ms
/// Defines the timeout value for waiting bus status
#define SDHOST_BUS_TIMEOUT           1000        // 1 ms
/// Defines the timeout for waiting for bus idle
#define SDHOST_BUS_IDLE_TIMEOUT      100000      // 100ms
/// Defines the polling time of waiting for bus idel
#define SDHOST_BUS_IDLE_POLL_INTER   10000       // 10ms
/// Defines the max. timeout value when checking the process of card initialization
#define SDHOST_ACMD41_TIMEOUT        1000000     // 1 sec
/// Defines the time interval when checking the process of card initialization
#define SDHOST_ACMD41_POLL_INTERVAL  10000       // 10 ms
/// Defines the erase timeout per block recommanded by SPEC
#define SDHOST_ERASE_1BLK_TIMEOUT    250000      // 250 ms

/// Defines the mask of register "SD Bus Status"
#define SDHOST_BUS_STS_MASK          0x1F        // 0x585 bit[4:0]
/// Defines the mask of register "SD_CMD0"
#define SDHOST_CMD_IDX_MASK          0x3F        // 0x589 bit[5:0]

/// Defines the value of "VHS" field in CMD8
#define SDHOST_CMD8_VHS              0x1         // 2.7-3.6V
/// Defines the value of "Check pattern" field in CMD8
#define SDHOST_CMD8_CHK_PATN         0xAA

/// Defines the value of "OCR" field in ACMD41
#define SDHOST_OCR_VDD_WIN           0xFF8000    // OCR bit[23:0]

/// Defines the byte size of SD response header (start + transmission + cmd_id)
#define SD_RESP_HDR_LEN              1

/// Defines the total number of phases when tuning sample clock
#define SDHOST_CLK_PHASE_CNT    4

#define SDHOST_INT_CARD_END         BIT1
#define SDHOST_INT_DMA_END          BIT4

#define SDHOST_MAGIC_NUM        0x8735b
#define LDO_VOSEL_3V            0xf
#define GPIO_CTRL_IMPED         0
#define GPIO_CTRL_LOW           1
#define GPIO_CTRL_HIGH          2
#define GPIO_DRIVING_4mA        0
#define GPIO_DRIVING_8mA        1
#define SDHOST_BUS_IDLE_STAT    0x1F
#define SDHOST_RST_DELAY        5000        // 5ms
/// For SDSC, the address should only limit in 23 bits
#define SDSC_INVALID_ADDR_MASK  0xFFC00000
/// Weighting of failed phase config for phase-tuning
#define FAILED_PHASE_WEIGHT     0xF000000
/// Retry limit of phase tuning
#define SDHOST_PHASE_RETRY      3

/// Defines the 32 byte align check
#define IS_32BYTE_ALIGN(addr)   (((u32)addr & 0x1f) == 0 ? 1 : 0)

#define SDHOST_CLK_TIMEOUT           10000       // 10ms

/**
  \brief  Defines LDO control voltage.
*/
enum SDHOST_LDO_VOL {
	SDHOST_LDO_0V,
	SDHOST_LDO_3V3,
	SDHOST_LDO_1V8
};

enum SDHOST_LDO_VOL_REG {
	SDIO_LDO_VOADJ_1793V = 8,           // voltage selection 1.793V
	SDIO_LDO_VOADJ_1839V = 9,           // voltage selection 1.839V
	SDIO_LDO_VOADJ_1887V = 10,          // voltage selection 1.887V
};

enum SDHOST_PHASE_RESULT {
	PHASE_PASS = 0,
	PHASE_CMD13_FAIL,
	PHASE_CMD19_FAIL,
	PHASE_READ_FAIL,
	PHASE_WRITE_FAIL,
	PHASE_CMP_FAIL,
	PHASE_NO_VALID,
};

enum SDHOST_VP_SEL {
	SDHOST_VP0 = 0,
	SDHOST_VP1 = 1,
};

/**
  \brief  Defines CMD6 function group 1 (access mode).
*/
typedef enum sd_cmd6_33v {
	SdCmd6SpeedDS           = 0x0,  // 3.3V Function 0
	SdCmd6SpeedHS           = 0x1,  // 3.3V Function 1

	SdCmd6SpeedSDR12        = 0x0,  // 1.8V Function 0
	SdCmd6SpeedSDR25        = 0x1,  // 1.8V Function 1
	SdCmd6SpeedSDR50        = 0x2,  // 1.8V Function 2
	SdCmd6SpeedSDR104       = 0x3,  // 1.8V Function 3
	SdCmd6SpeedDDR50        = 0x4,  // 1.8V Function 4

	SdCmd6KeepCurSpd        = 0xF
} sd_cmd6_arg_t;

/**
  \brief  Defines SDIO Host DMA transfer type.
*/
enum  sdhost_dma_type_e {
	SdHostDmaNormal  = 0,
	SdHostDma64b     = 1,
	SdHostDmaR2      = 2
};

/**
  \brief  Defines SDIO Host DMA operation.
*/
enum  sdhost_dma_op_e {
	SdHostDmaWrite   = 0,
	SdHostDmaRead    = 1
};

/**
  \brief  Defines SDIO Host clock source.
*/
enum  sdhost_clk_src_e {
	SdHostSscClk     = 0,
	SdHostSscClkVp0  = 1,
	SdHostSscClkVp1  = 2
};

/**
  \brief  Defines SDIO Host clock divider.
*/
enum  sdhost_clk_div_e {
	SdHostClkDiv1    = 0,
	SdHostClkDiv2    = 1,
	SdHostClkDiv4    = 2,
	SdHostClkDiv8    = 3
};

/**
  \brief  Defines SDCLK divider.
*/
enum  sdhost_sdclk_divider_e {
	SdHostSdclkDiv128    = 0,
	SdHostSdclkDiv256    = 1
};

/**
  \brief  Defines SDIO Host mode selection.
*/
enum  sdhost_mode_sel_e {
	SdHostModeSd20   = 0,
	SdHostModeDdr    = 1,
	SdHostModeSd30   = 2
};

/**
  \brief  Defines SDIO Host bus width.
*/
enum  sdhost_bus_width_e {
	SdHostBus1bit    = 0,
	SdHostBus4bit    = 1
};

/**
  \brief  Defines SDIO Host response type.
*/
enum  sdhost_rsp_type_e {
	SdHostNoRsp      = 0,
	SdHostRsp6Bytes  = 1,
	SdHostRsp17Bytes = 2
};

/**
  \brief  Defines SDIO bus status.
*/
enum  sdhost_bus_status_e {
	SdHostBusLow     = 0,
	SdHostBusHigh    = 1
};

/**
  \brief  Defines SDIO Host command code.
*/
enum  sdhost_cmd_code_e {
	SdHostCmdNormalWr        = 0,
	SdHostCmdAutoWr3         = 1,
	SdHostCmdAutoWr4         = 2,
	SdHostCmdAutoRd3         = 5,
	SdHostCmdAutoRd4         = 6,
	SdHostCmdSendCmdGetRsp   = 8,
	SdHostCmdAutoWr1         = 9,
	SdHostCmdAutoWr2         = 10,
	SdHostCmdNormalRd        = 12,
	SdHostCmdAutoRd1         = 13,
	SdHostCmdAutoRd2         = 14,
	SdHostCmdTuning          = 15
};

/**
  \brief  Defines the data present select in current transaction.
*/
enum  sdhost_data_present_e {
	SdHostNoDataPresent      = 0,
	SdHostDataPresent        = 1
};

/**
  \brief  Defines CMD6 operation mode.
*/
typedef enum sd_cmd6_mode_e {
	SdCmd6CheckMode      = 0,
	SdCmd6SwitchMode     = 1
} sd_cmd6_mode_t;

/**
  \brief  Defines CMD6 function group 3 (driver strength).
*/
enum  sdhost_driver_strength_e {
	SdHostDriverTypeB        = 0,
	SdHostDriverTypeA        = 1,
	SdHostDriverTypeC        = 2,
	SdHostDriverTypeD        = 3
};

/**
  \brief  Defines CMD6 function group 4 (current limit).
*/
enum  sdhost_current_limit_e {
	SdHostCurLim200mA        = 0,
	SdHostCurLim400mA        = 1,
	SdHostCurLim600mA        = 2,
	SdHostCurLim800mA        = 3,
};

/**
  \brief  Defines CMD7 select/de-select card.
*/
enum  sdhost_card_selection_e {
	SdHostDeselCard          = 0,
	SdHostSelCard            = 1
};

/**
  \brief  Defines host capacity support (ACMD41).
*/
enum  sdhost_host_capacity_e {
	SdHostSupportSdscOnly    = 0,
	SdHostSupportSdhcSdxc    = 1
};

/**
  \brief  Defines SDXC power control (ACMD41).
*/
enum  sdhost_sdxc_pwr_ctl_e {
	SdHostPwrSaving          = 0,
	SdHostMaxPerformance     = 1
};

/**
  \brief  Defines switch to 1.8V request (ACMD41).
*/
enum  sdhost_switch_18v_req_e {
	SdHostUseCurrSigVol      = 0,
	SdHostSwitch18v          = 1
};

/**
  \brief  Defines SD card's current state (Card Status bit[12:9]).
*/
enum  sdhost_card_curr_ste_e {
	SdHostCardSteIdle        = 0,
	SdHostCardSteReady       = 1,
	SdHostCardSteIdent       = 2,
	SdHostCardSteStby        = 3,
	SdHostCardSteTran        = 4,
	SdHostCardSteData        = 5,
	SdHostCardSteRcv         = 6,
	SdHostCardStePrg         = 7,
	SdHostCardSteDis         = 8
};

/**
  \brief  Defines SD physical layer specification version.
*/
enum  sdhost_sd_spec_e {
	SdHostSdSpecV101         = 0,
	SdHostSdSpecV110         = 1,
	SdHostSdSpecV200         = 2,
	SdHostSdSpecV300         = 3,
	SdHostSdSpecUnk          = 0xFF
};

/**
  \brief  Defines SDIO command index.
*/
enum  sdhost_cmd_idx_e {
	SdHostCmdGoIdleSte           = 0,
	SdHostCmdAllSendCid          = 2,
	SdHostCmdSendRelAddr         = 3,
	SdHostCmdSetDsr              = 4,
	SdHostCmdSwitchFunc          = 6,
	SdHostCmdSetBusWidth         = 6,  // ACMD6
	SdHostCmdSelDeselCard        = 7,
	SdHostCmdSendIfCond          = 8,
	SdHostCmdSendCsd             = 9,
	SdHostCmdSendCid             = 10,
	SdHostCmdVolSwitch           = 11,
	SdHostCmdStopXsmission       = 12,
	SdHostCmdSendSts             = 13,
	SdHostCmdSetBlklen           = 16,
	SdHostCmdRdSingleBlk         = 17,
	SdHostCmdRdMulBlk            = 18,
	SdHostCmdSendTuningBlk       = 19,
	SdHostCmdSendNumWrBlks       = 22,  // ACMD22
	SdHostCmdSetBlkCnt           = 23,
	SdHostCmdSetWrBlkEraseCnt    = 23,  // ACMD23
	SdHostCmdWrBlk               = 24,
	SdHostCmdWrMulBlk            = 25,
	SdHostCmdProgCsd             = 27,
	SdHostCmdEraseBlkSt          = 32,
	SdHostCmdEraseBlkEd          = 33,
	SdHostCmdErase               = 38,
	SdHostCmdSdSendOpCond        = 41,  // ACMD41
	SdHostCmdSendScr             = 51,  // ACMD51
	SdHostCmdAppCmd              = 55
};

/**
  \brief  The structure of the settings for DMA control.
*/
typedef struct hal_sdhost_dma_ctrl_s {
	u32 start_addr;
	u16 blk_cnt;
	u8 op;
	u8 type;
} hal_sdhost_dma_ctrl_t, *phal_sdhost_dma_ctrl_t;

/**
  \brief  The structure of command attributes.
*/
typedef struct hal_sdhost_cmd_attr_s {
	u32 arg;
	u8 idx;
	u8 rsp_type;
	u8 rsp_crc_chk;
	u8 data_present;
} hal_sdhost_cmd_attr_t, *phal_sdhost_cmd_attr_t;

// size should be 16 bytes
typedef struct sd_csd_v1 {
	u32 not_used_1      : 1;
	u32 crc             : 7;
	u32 rsvd1           : 2;
	u32 file_format     : 2;
	u32 tmp_write_prot  : 1;
	u32 perm_write_prot : 1;
	u32 copy            : 1;
	u32 file_format_grp : 1;
	u32 rsvd2           : 5;
	u32 write_bl_partial: 1;
	u32 write_bl_len    : 4;
	u32 r2w_factor      : 3;
	u32 rsvd3           : 2;
	u32 wp_grp_enable   : 1;
	u32 wp_grp_size     : 7;
	u32 sector_size     : 7;
	u32 erase_blk_en    : 1;
	u32 c_size_mult     : 3;
	u32 vdd_w_curr_max  : 3;
	u32 vdd_w_curr_min  : 3;
	u32 vdd_r_curr_max  : 3;
	u32 vdd_r_curr_min  : 3;
	u32 c_size_0_1      : 2;
	u32 c_size_2_11     : 10;
	u32 rsvd4           : 2;
	u32 dsr_imp         : 1;
	u32 rd_blk_misalign : 1;
	u32 wr_blk_misalign : 1;
	u32 read_bl_partial : 1;
	u32 read_bl_len     : 4;
	u32 ccc             : 12;
	u32 tran_speed      : 8;
	u32 nsac            : 8;
	u32 taac            : 8;
	u32 rsvd5           : 6;
	u32 csd_structure   : 2;
} __ALIGNED(4) sd_csd_v1_t;

STATIC_ASSERT(sizeof(sd_csd_v1_t) == SD_CSD_LEN, sd_csd_v1_sz);

// size should be 16 bytes
typedef struct sd_csd_v2 {
	u32 not_used_1      : 1;
	u32 crc             : 7;
	u32 rsvd1           : 2;
	u32 file_format     : 2;
	u32 tmp_write_prot  : 1;
	u32 perm_write_prot : 1;
	u32 copy            : 1;
	u32 file_format_grp : 1;
	u32 rsvd2           : 5;
	u32 write_bl_partial: 1;
	u32 write_bl_len    : 4;
	u32 r2w_factor      : 3;
	u32 rsvd3           : 2;
	u32 wp_grp_enable   : 1;
	u32 wp_grp_size     : 7;
	u32 sector_size     : 7;
	u32 erase_blk_en    : 1;
	u32 rsvd4           : 1;
	u32 c_size_0_15     : 16;
	u32 c_size_16_21    : 6;
	u32 rsvd5           : 6;
	u32 dsr_imp         : 1;
	u32 rd_blk_misalign : 1;
	u32 wr_blk_misalign : 1;
	u32 read_bl_partial : 1;
	u32 read_bl_len     : 4;
	u32 ccc             : 12;
	u32 tran_speed      : 8;
	u32 nsac            : 8;
	u32 taac            : 8;
	u32 rsvd6           : 6;
	u32 csd_structure   : 2;
} __ALIGNED(4) sd_csd_v2_t;

STATIC_ASSERT(sizeof(sd_csd_v2_t) == SD_CSD_LEN, sd_csd_v2_sz);

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_SDHOST_CTRL_H_"
