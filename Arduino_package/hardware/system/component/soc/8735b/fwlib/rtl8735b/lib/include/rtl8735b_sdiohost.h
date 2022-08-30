/**************************************************************************//**
 * @file    rtl8735b_sdiohost.h
 * @brief    The HAL related definition and macros for SD Host controller.
 *           Includes Registers and data type definition.
 * @version V1.00
 * @date    2020-10-12
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
#ifndef _RTL8735B_SDIOHOST_H_
#define _RTL8735B_SDIOHOST_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hal_sdiohost SDIOHOST
 * @ingroup 8195bh_hal
 * @{
 * @brief The SD Host HAL module of the HS platform.
 */

#include "rtl8735b_sdiohost_type.h"
#include "basic_types.h"

/**
  \brief  Defines SDIO GPIO pin levels.
*/
typedef enum sdioh_gpio_pin_level_e {
	SdiohGpioLevelLow   = 1,
	SdiohGpioLevelHigh  = 2,
} sdioh_gpio_pin_level_t;

/**
  \brief  Defines SDIO GPIO pin drive.
*/
typedef enum sdioh_gpio_pin_drive_e {
	SdiohGpioDrive4mA   = 0,
	SdiohGpioDrive8mA   = 1,
} sdioh_gpio_pin_drive_t;

/**
  \brief  Defines SDIO Host DMA transfer type.
*/

typedef enum sdioh_dma_mode_e {
	SdiohDMAModeSDMA    = 0,
	SdiohDMAModeADMA    = 1,
} sdioh_dma_mode_t;

/**
  \brief  Defines SDIO Host ADMA table end.
*/

typedef enum sdioh_adma_line_end_e {
	SdiohADMALineCont   = 0,
	SdiohADMALineEnd    = 1,
} sdioh_adma_line_end_t;

/**
  \brief  Defines SDIO Host RW operation.
*/
typedef enum sdioh_rw_flag_e {
	SdiohRWFlagRead     = 0,
	SdiohRWFlagWrite    = 1,
} sdioh_rw_flag_t;

/**
  \brief  Defines SDIO Host Data direction.
*/
typedef enum sdioh_data_direction_e {
	SdiohDataDirectionRead  = 1,
	SdiohDataDirectionWrite = 0,
} sdioh_data_direction_t;

/**
  \brief  Defines SDIO Host function number.
*/
typedef enum sdioh_function_number_e {
	SdiohFunc0  = 0,
	SdiohFunc1  = 1,
	SdiohFunc2  = 2,
	SdiohFunc3  = 3,
	SdiohFunc4  = 4,
	SdiohFunc5  = 5,
	SdiohFunc6  = 6,
	SdiohFunc7  = 7,
	SdiohFuncNA = 8,
} sdioh_function_number_t;

/**
  \brief  Defines SDIO Host RAW.
*/
typedef enum sdioh_raw_flag_e {
	SdiohRAWFlagNo  = 0,
	SdiohRAWFlagYes = 1,
} sdioh_raw_flag_t;

/**
  \brief  Defines SDIO Host CMD53 mode.
*/
typedef enum sdioh_cmd53_block_mode_flag_e {
	SdiohCMD53ByteMode  = 0,
	SdiohCMD53BlockMode = 1,
} sdioh_cmd53_block_mode_flag_t;

/**
  \brief  Defines SDIO Host CMD53 op code.
*/
typedef enum sdioh_cmd53_op_code_flag_e {
	SdiohCMD53AddrFixed = 0,
	SdiohCMD53AddrIncr  = 1,
} sdioh_cmd53_op_code_flag_t;

/**
  \brief  Defines SDIO Host speed modes.
*/
typedef enum sdioh_speed_e {
	SdiohDefaultSpeed   = 0,
	SdiohHighSpeed      = 1,
} sdioh_speed_t;

/**
  \brief  Defines SDIO bus state.
*/
typedef enum sdioh_bus_state_e {
	SdiohBusInit    = 0,
	SdiohBusStandby = 1,
	SdiohBusCmd     = 2,
	SdiohBusXferPIO = 3,
	SdiohBusXferDMA = 4,
	SdiohBusOff     = 5,
} sdioh_bus_state_t;

/**
  \brief  Defines SDIO DMA operation state.
*/
typedef enum sdioh_dma_op_state_e {
	SdiohOpNA           = 0,
	SdiohOpPending      = 1,
	SdiohOpInProgress   = 2,
	SdiohOpComplete     = 3,
	SdiohOpError        = 4,
} sdioh_dma_op_state_t;

/**
  \brief  Defines SDIO client CCCR.
*/
typedef enum sdioh_client_cccr_e {
	SdiohClientCccrRev          = 0x00,
	SdiohClientSdSpecRev        = 0x01,
	SdiohClientIoEn             = 0x02,
	SdiohClientIoRdy            = 0x03,
	SdiohClientIntEn            = 0x04,
	SdiohClientIntPend          = 0x05,
	SdiohClientIoAbort          = 0x06,
	SdiohClientBusInterfaceCtl  = 0x07,
	SdiohClientCardCapability   = 0x08,
	SdiohClientCisPtr           = 0x09,
	SdiohClientBusSuspend       = 0x0C,
	SdiohClientFnSel            = 0x0D,
	SdiohClientExecFlag         = 0x0E,
	SdiohClientRdyFlag          = 0x0F,
	SdiohClientFn0BlkSz         = 0x10,
	SdiohClientPwrCtl           = 0x12,
	SdiohClientBusSpeedSel      = 0x13,
	SdiohClientUhsSupport       = 0x14,
	SdiohClientDvrStrength      = 0x15,
	SdiohClientIntExt           = 0x16,
} sdioh_client_cccr_t;

/**
  \brief  Defines SDIO client function status.
*/
typedef enum sdioh_client_fn_state_e {
	SdiohClientFnOff    = 0,
	SdiohClientFnOn     = 1,
} sdioh_client_fn_state_t;

/**
  \brief  Defines SDIO client memory support.
*/
typedef enum sdioh_client_memory_supp_e {
	SdiohClientMemNo    = 0,
	SdiohClientMemYes   = 1,
} sdioh_client_memory_supp_t;

/**
  \brief  Defines SDIO client CCCR revision.
*/
typedef enum sdioh_client_cccr_rev_e {
	SdiohClientCccrRev1_0   = 0x0,
	SdiohClientCccrRev1_1   = 0x1,
	SdiohClientCccrRev2_0   = 0x2,
	SdiohClientCccrRev3_0   = 0x3,
} sdioh_client_cccr_rev_t;

/**
  \brief  Defines SDIO client SDIO revision.
*/
typedef enum sdioh_client_sdio_rev_e {
	SdiohClientSdioRev1_0   = 0x0,
	SdiohClientSdioRev1_1   = 0x1,
	SdiohClientSdioRev1_2   = 0x2,
	SdiohClientSdioRev2_0   = 0x3,
	SdiohClientSdioRev3_0   = 0x4,
} sdioh_client_sdio_rev_t;

/**
  \brief  Defines SDIO client SD revision.
*/
typedef enum sdioh_client_sd_rev_e {
	SdiohClientSdRev1_01    = 0x0,
	SdiohClientSdRev1_10    = 0x1,
	SdiohClientSdRev2_00    = 0x2,
	SdiohClientSdRev3_00    = 0x3,
} sdioh_client_sd_rev_t;

/**
  \brief  Defines SDIO client bus width.
*/
typedef enum sdioh_client_bus_width_e {
	SdiohClientBus1Bit    = 0x0,
	SdiohClientBus4Bit    = 0x2,
	SdiohClientBus8Bit    = 0x3,
} sdioh_client_bus_width_t;

/**
  \brief  Defines SDIO client 8-bit support.
*/
typedef enum sdioh_client_8bit_support_e {
	SdiohClient8BitNo   = 0x0,
	SdiohClient8BitYes  = 0x1,
} sdioh_client_8bit_support_t;

/**
  \brief  Defines SDIO client multi-block support.
*/
typedef enum sdioh_client_multiblk_support_e {
	SdiohClientMultiblkNo   = 0x0,
	SdiohClientMultiblkYes  = 0x1,
} sdioh_client_multiblk_support_t;

/**
  \brief  Defines SDIO client block interrupt support.
*/
typedef enum sdioh_client_blk_int_support_e {
	SdiohClientBlkIntNo     = 0x0,
	SdiohClientBlkIntYes    = 0x1,
} sdioh_client_blk_int_support_t;

/**
  \brief  Defines SDIO client function interface code.
*/
typedef enum sdioh_client_fn_interface_e {
	SdiohClientFnIntNA      = 0x0,
	SdiohClientFnIntUart    = 0x1,
	SdiohClientFnIntBtA     = 0x2,
	SdiohClientFnIntBtB     = 0x3,
	SdiohClientFnIntGps     = 0x4,
	SdiohClientFnIntCam     = 0x5,
	SdiohClientFnIntPhs     = 0x6,
	SdiohClientFnIntWlan    = 0x7,
	SdiohClientFnIntAta     = 0x8,
	SdiohClientFnIntBtAAmp  = 0x9,
} sdioh_client_fn_interface_t;

/**
  \brief  Defines SDIO client function CSA support.
*/
typedef enum sdioh_client_fn_csa_support_e {
	SdiohClientFnCsaNo  = 0x0,
	SdiohClientFnCsaYes = 0x1,
} sdioh_client_fn_csa_support_t;


/**
  \brief  Defines SDIO command index.
*/
typedef enum sdioh_cmd_idx_e {
	SdiohCmdSendRelAddr     = 3,
	SdiohCmdSendOpCond      = 5,
	SdiohCmdSelDeselCard    = 7,
	SdiohCmdRdWrSingleByte  = 52,
	SdiohCmdRdWrMultiBlk    = 53,
} sdioh_cmd_idx_t;

/**
  \brief  Callback function type without parameter.
*/
typedef void (*sdiohost_cb_t)(void);

/**
  \brief  Callback function type with parameter.
*/
typedef void (*sdiohost_para_cb_t)(void *para);


// /**
//   \brief  The structure of the settings for DMA control.
// */
// typedef struct hal_sdiohost_dma_ctrl_s {
//  u32 start_addr;
//  u16 blk_cnt;
//  u8 op;
//  u8 type;
// } hal_sdiohost_dma_ctrl_t, *phal_sdiohost_dma_ctrl_t;


typedef union sdioh_reg_arg1_s {
	u32 arg1;

	struct {
		u32 write_data : 8;
		u32 stuff_0 : 1;
		u32 reg_addr : 17;
		u32 stuff_1 : 1;
		u32 raw_flag : 1;
		u32 function_number : 3;
		u32 rw_flag : 1;
	} cmd52_t;

	struct {
		u32 byte_block_count : 9;
		u32 reg_addr : 17;
		u32 op_code : 1;
		u32 block_mode : 1;
		u32 function_number : 3;
		u32 rw_flag : 1;
	} cmd53_t;
} sdioh_reg_arg1_t;

typedef struct sdioh_xfer_mode_reg_s {
	u16 dma_enable : 1;
	u16 block_count : 1;
	u16 auto_cmd : 2;
	u16 data_direction : 1;
	u16 block_select : 1;
	u16 stuff_0 : 10;
} sdioh_xfer_mode_reg_t;

typedef struct sdioh_cmd_reg_s {
	u16 response_type : 2;
	u16 stuff_0 : 1;
	u16 cmd_crc_check : 1;
	u16 cmd_index_check : 1;
	u16 data_present : 1;
	u16 cmd_type : 2;
	u16 cmd_index : 6;
	u16 stuff_1 : 2;
} sdioh_cmd_reg_t;

/**
  \brief  The structure of command attributes.
*/
typedef struct hal_sdioh_cmd_attr_s {
	sdioh_cmd_idx_t idx;
	sdioh_reg_arg1_t arg;
	sdioh_xfer_mode_reg_t xfer;
	sdioh_cmd_reg_t cmd;
} hal_sdioh_cmd_attr_t, *phal_sdioh_cmd_attr_t;

/**
  \brief  Current state.
*/
typedef struct hal_sdioh_state_s {
	volatile sdioh_bus_state_t curr_state;
	volatile sdioh_function_number_t curr_function;
	volatile sdioh_dma_op_state_t op_state;
} hal_sdioh_state_t, *phal_sdioh_state_t;

/**
  \brief  Card function info.
*/
typedef struct hal_sdioh_client_fn_info_s {
	sdioh_client_fn_interface_t fn_interface;
	sdioh_client_fn_csa_support_t csa_support;
	u32 cis_ptr;
} hal_sdioh_client_fn_info_t, *phal_sdioh_client_fn_info_t;

/**
  \brief  Card info.
*/
typedef struct hal_sdioh_client_info_s {
	uint8_t num_io_fn;
	sdioh_client_memory_supp_t memory_support;
	sdioh_client_cccr_rev_t cccr_rev;
	sdioh_client_sdio_rev_t sdio_rev;
	sdioh_client_sd_rev_t sd_rev;
	u32 cis_ptr;
	hal_sdioh_client_fn_info_t fn_info[7];
} hal_sdioh_client_info_t, *phal_sdioh_client_info_t;

typedef struct adma_descriptor_line_s {
	u32 valid : 1;
	u32 end : 1;
	u32 interrupt : 1;
	u32 stuff_0 : 1;
	u32 act : 2;
	u32 stuff_1 : 10;
	u32 length : 16;
} adma_descriptor_line_t;

/**
  \brief  The data structure for SDIO host HAL operations.
*/
typedef struct hal_sdiohost_adapter_s {
	SDIOHOST_TypeDef *base_addr;
	volatile u16 error_int;
	volatile u16 normal_int;
	volatile hal_sdioh_state_t curr_state;
	hal_sdioh_client_info_t client_info;
	sdiohost_para_cb_t transfer_done_cb;
	sdiohost_para_cb_t task_yield_cb;
	sdiohost_para_cb_t sdma_update_cb;
	sdiohost_para_cb_t card_int_cb;
	void *transfer_done_cb_para;
	void *task_yield_cb_para;
	void *sdma_update_cb_para;
	void *card_int_cb_para;
} hal_sdiohost_adapter_t, *phal_sdiohost_adapter_t;


/**
  \brief  The data structure of the stubs function for the SDIO Host HAL functions in ROM
*/
typedef struct hal_sdiohost_func_stubs_s {
	// io_pin_t *sdiohost_pin_table;
	// void (*hal_sdiohost_irq_handler)(void);
	// void (*hal_sdiohost_irq_reg)(irq_handler_t irq_handler);
	// void (*hal_sdiohost_irq_unreg)(void);
	hal_status_t (*hal_sdiohost_init_host)(hal_sdiohost_adapter_t *psdiohost_adapter, u32 base_addr);
	hal_status_t (*hal_sdiohost_deinit_host)(hal_sdiohost_adapter_t *psdiohost_adapter);
	hal_status_t (*hal_sdiohost_reset_host)(hal_sdiohost_adapter_t *psdiohost_adapter);
	hal_status_t (*hal_sdiohost_init_client)(hal_sdiohost_adapter_t *psdiohost_adapter);
	hal_status_t (*hal_sdiohost_reset_client)(hal_sdiohost_adapter_t *psdiohost_adapter);
	hal_status_t (*hal_sdiohost_send_cmd_52)(hal_sdiohost_adapter_t *psdiohost_adapter,
			sdioh_rw_flag_t rw_flag,
			sdioh_function_number_t func_num,
			sdioh_raw_flag_t raw_flag,
			u32 reg_addr,
			u8 write_data);
	hal_status_t (*hal_sdiohost_send_cmd_53_pio)(hal_sdiohost_adapter_t *psdiohost_adapter,
			sdioh_rw_flag_t rw_flag,
			sdioh_function_number_t func_num,
			sdioh_cmd53_block_mode_flag_t block_mode,
			sdioh_cmd53_op_code_flag_t op_code,
			u32 reg_addr,
			u16 byte_count,
			u32 *pio_buffer_ptr);
	hal_status_t (*hal_sdiohost_send_cmd_53_sdma)(hal_sdiohost_adapter_t *psdiohost_adapter,
			sdioh_rw_flag_t rw_flag,
			sdioh_function_number_t func_num,
			sdioh_cmd53_block_mode_flag_t block_mode,
			sdioh_cmd53_op_code_flag_t op_code,
			u32 reg_addr,
			u16 byte_count,
			u32 *sdma_buffer_ptr);
	hal_status_t (*hal_sdiohost_send_cmd_53_adma)(hal_sdiohost_adapter_t *psdiohost_adapter,
			sdioh_rw_flag_t rw_flag,
			sdioh_function_number_t func_num,
			sdioh_cmd53_block_mode_flag_t block_mode,
			sdioh_cmd53_op_code_flag_t op_code,
			u32 reg_addr,
			u16 byte_count,
			u32 *adma_system_address_ptr);
	hal_status_t (*hal_sdiohost_abort_xfer)(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num);
	hal_status_t (*hal_sdiohost_chk_xfer_error)(hal_sdiohost_adapter_t *psdiohost_adapter);
	hal_status_t (*hal_sdiohost_switch_xfer_speed)(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_speed_t sdioh_speed);
	hal_status_t (*hal_sdiohost_error_recovery)(hal_sdiohost_adapter_t *psdiohost_adapter);
	hal_status_t (*hal_sdiohost_set_block_size)(hal_sdiohost_adapter_t *psdiohost_adapter, u16 block_size);
	hal_status_t (*hal_sdiohost_client_bus_setting)(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_client_bus_width_t bus_width);
	hal_status_t (*hal_sdiohost_client_enable_fn)(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num, sdioh_client_fn_state_t fn_state);
	hal_status_t (*hal_sdiohost_client_set_block_size)(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num, u16 block_size);
	hal_status_t (*hal_sdiohost_create_adma_entry)(u32 *buffer_ptr, u16 length, sdioh_adma_line_end_t end, u32 *adma_system_address_ptr);
	void (*hal_sdiohost_task_yield_hook)(hal_sdiohost_adapter_t *psdiohost_adapter, sdiohost_para_cb_t task_yield, void *pdata);
	void (*hal_sdiohost_transfer_done_int_hook)(hal_sdiohost_adapter_t *psdiohost_adapter, sdiohost_para_cb_t transfer_done_cb, void *pdata);
	uint32_t reserved[12];  // 32 bytes align for next ROM code version function table extending.
} hal_sdiohost_func_stubs_t;


/// @cond DOXYGEN_ROM_HAL_API

// /**
//  * @addtogroup hs_hal_sdiohost__rom_func SDIO Host HAL ROM APIs.
//  * @ingroup hs_hal_sdiohost_
//  * @{
//  */

hal_status_t hal_rtl_sdiohost_init_host(hal_sdiohost_adapter_t *psdiohost_adapter, u32 base_addr);
hal_status_t hal_rtl_sdiohost_deinit_host(hal_sdiohost_adapter_t *psdiohost_adapter);
hal_status_t hal_rtl_sdiohost_reset_host(hal_sdiohost_adapter_t *psdiohost_adapter);
hal_status_t hal_rtl_sdiohost_init_client(hal_sdiohost_adapter_t *psdiohost_adapter);
hal_status_t hal_rtl_sdiohost_reset_client(hal_sdiohost_adapter_t *psdiohost_adapter);
hal_status_t hal_rtl_sdiohost_send_cmd_52(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_raw_flag_t raw_flag,
		u32 reg_addr,
		u8 write_data);
hal_status_t hal_rtl_sdiohost_send_cmd_53_pio(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_cmd53_block_mode_flag_t block_mode,
		sdioh_cmd53_op_code_flag_t op_code,
		u32 reg_addr,
		u16 byte_count,
		u32 *pio_buffer_ptr);
hal_status_t hal_rtl_sdiohost_send_cmd_53_sdma(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_cmd53_block_mode_flag_t block_mode,
		sdioh_cmd53_op_code_flag_t op_code,
		u32 reg_addr,
		u16 byte_count,
		u32 *sdma_buffer_ptr);
hal_status_t hal_rtl_sdiohost_send_cmd_53_adma(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_cmd53_block_mode_flag_t block_mode,
		sdioh_cmd53_op_code_flag_t op_code,
		u32 reg_addr,
		u16 byte_count,
		u32 *adma_system_address_ptr);
hal_status_t hal_rtl_sdiohost_abort_xfer(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num);
hal_status_t hal_rtl_sdiohost_chk_xfer_error(hal_sdiohost_adapter_t *psdiohost_adapter);
hal_status_t hal_rtl_sdiohost_switch_xfer_speed(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_speed_t sdioh_speed);
hal_status_t hal_rtl_sdiohost_error_recovery(hal_sdiohost_adapter_t *psdiohost_adapter);
hal_status_t hal_rtl_sdiohost_set_block_size(hal_sdiohost_adapter_t *psdiohost_adapter, u16 block_size);
hal_status_t hal_rtl_sdiohost_client_bus_setting(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_client_bus_width_t bus_width);
hal_status_t hal_rtl_sdiohost_client_enable_fn(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num, sdioh_client_fn_state_t fn_state);
hal_status_t hal_rtl_sdiohost_client_set_block_size(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num, u16 block_size);
hal_status_t hal_rtl_sdiohost_create_adma_entry(u32 *buffer_ptr, u16 length, sdioh_adma_line_end_t end, u32 *adma_system_address_ptr);
void hal_rtl_sdiohost_task_yield_hook(hal_sdiohost_adapter_t *psdiohost_adapter, sdiohost_para_cb_t task_yield, void *pdata);
void hal_rtl_sdiohost_transfer_done_int_hook(hal_sdiohost_adapter_t *psdiohost_adapter, sdiohost_para_cb_t transfer_done_cb, void *pdata);

/** @} */ /* End of group hs_hal_sdiohost__rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */
/** @} */ /* End of group hs_hal_sdiohost_ */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_SDHOST_H_"


