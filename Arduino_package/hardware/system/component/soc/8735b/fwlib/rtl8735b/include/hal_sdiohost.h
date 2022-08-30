/**************************************************************************//**
 * @file    hal_sdiohost.h
 * @brief   The HAL API implementation for SDIO Host controller
 * @version V1.00
 * @date    2017-07-12
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
#ifndef _HAL_SDIOHOST_H_
#define _HAL_SDIOHOST_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_sdiohost_ SDIOHOST
 * @{
 * brief The SDIO Host HAL RAM APIs. These APIs is provided for user application to control the SDIO Host hardware.
 */

extern const hal_sdiohost_func_stubs_t hal_sdiohost_stubs;

// /**
//  *  @brief To reg irq of the SDIO host controller.
//  *
//  *  @param[in]  irq_handler The SDIO host irq handler
//  *
//  *  @returns    void.
//  */
// __STATIC_INLINE void hal_sdiohost_irq_reg(irq_handler_t irq_handler)
// {
//  hal_sdiohost_stubs.hal_sdiohost_irq_reg(irq_handler);
// }


// /**
//  *  @brief To unreg irq of the SDIO host controller.
//  *
//  *  @param[in]  void.
//  *
//  *  @returns    void.
//  */
// __STATIC_INLINE void hal_sdiohost_irq_unreg(void)
// {
//  hal_sdiohost_stubs.hal_sdiohost_irq_unreg();
// }


/**
 *  @brief To initialize the SDIO host controller.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  base_addr The address of SDIO IP reg.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_init_host(hal_sdiohost_adapter_t *psdiohost_adapter, u32 base_addr)
{
	return hal_sdiohost_stubs.hal_sdiohost_init_host(psdiohost_adapter, base_addr);
}

/**
 *  @brief To de-initialize the SDIO host controller.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_deinit_host(hal_sdiohost_adapter_t *psdiohost_adapter)
{
	return hal_sdiohost_stubs.hal_sdiohost_deinit_host(psdiohost_adapter);
}

/**
 *  @brief To reset the SDIO host controller.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_reset_host(hal_sdiohost_adapter_t *psdiohost_adapter)
{
	return hal_sdiohost_stubs.hal_sdiohost_reset_host(psdiohost_adapter);
}

/**
 *  @brief To initialize the SDIO client.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_init_client(hal_sdiohost_adapter_t *psdiohost_adapter)
{
	return hal_sdiohost_stubs.hal_sdiohost_init_client(psdiohost_adapter);
}

/**
 *  @brief To reset the SDIO client.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_reset_client(hal_sdiohost_adapter_t *psdiohost_adapter)
{
	return hal_sdiohost_stubs.hal_sdiohost_reset_client(psdiohost_adapter);
}

/**
 *  @brief To write/read byte data from the SDIO client using CMD52.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  rw_flag The read or write operation flag.
 *  @param[in]  func_num The function number to perform operation on.
 *  @param[in]  raw_flag The read after write flag.
 *  @param[in]  reg_addr The SDIO client register address to perform operation on.
 *  @param[in]  write_data The data to be written (0x0 for read operation).
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_send_cmd_52(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_raw_flag_t raw_flag,
		u32 reg_addr,
		u8 write_data)
{
	return hal_sdiohost_stubs.hal_sdiohost_send_cmd_52(psdiohost_adapter, rw_flag, func_num, raw_flag, reg_addr, write_data);
}

/**
 *  @brief To write/read byte or block data from the SDIO client using CMD53 (PIO).
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  rw_flag The read or write operation flag.
 *  @param[in]  func_num The function number to perform operation on.
 *  @param[in]  block_mode The byte/block transfer select flag.
 *  @param[in]  op_code The fixed/incrementing address flag.
 *  @param[in]  reg_addr The SDIO client register address to perform operation on.
 *  @param[in]  byte_count The total number of bytes to be read/written.
 *  @param[in]  pio_buffer_ptr The pointer to data buffer to read/write to.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_send_cmd_53_pio(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_cmd53_block_mode_flag_t block_mode,
		sdioh_cmd53_op_code_flag_t op_code,
		u32 reg_addr,
		u16 byte_count,
		u32 *pio_buffer_ptr)
{
	return hal_sdiohost_stubs.hal_sdiohost_send_cmd_53_pio(psdiohost_adapter, rw_flag, func_num, block_mode, op_code, reg_addr, byte_count, pio_buffer_ptr);
}

/**
 *  @brief To write/read byte or block data from the SDIO client using CMD53 (SDMA).
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  rw_flag The read or write operation flag.
 *  @param[in]  func_num The function number to perform operation on.
 *  @param[in]  block_mode The byte/block transfer select flag.
 *  @param[in]  op_code The fixed/incrementing address flag.
 *  @param[in]  reg_addr The SDIO client register address to perform operation on.
 *  @param[in]  byte_count The total number of bytes to be read/written.
 *  @param[in]  sdma_buffer_ptr The pointer to data buffer to read/write to.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_send_cmd_53_sdma(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_cmd53_block_mode_flag_t block_mode,
		sdioh_cmd53_op_code_flag_t op_code,
		u32 reg_addr,
		u16 byte_count,
		u32 *sdma_buffer_ptr)
{
	return hal_sdiohost_stubs.hal_sdiohost_send_cmd_53_sdma(psdiohost_adapter, rw_flag, func_num, block_mode, op_code, reg_addr, byte_count, sdma_buffer_ptr);
}

/**
 *  @brief To write/read byte or block data from the SDIO client using CMD53 (ADMA).
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  rw_flag The read or write operation flag.
 *  @param[in]  func_num The function number to perform operation on.
 *  @param[in]  block_mode The byte/block transfer select flag.
 *  @param[in]  op_code The fixed/incrementing address flag.
 *  @param[in]  reg_addr The SDIO client register address to perform operation on.
 *  @param[in]  byte_count The total number of bytes to be read/written.
 *  @param[in]  adma_system_address_ptr The pointer to the ADMA descriptor table.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_send_cmd_53_adma(hal_sdiohost_adapter_t *psdiohost_adapter,
		sdioh_rw_flag_t rw_flag,
		sdioh_function_number_t func_num,
		sdioh_cmd53_block_mode_flag_t block_mode,
		sdioh_cmd53_op_code_flag_t op_code,
		u32 reg_addr,
		u16 byte_count,
		u32 *adma_system_address_ptr)
{
	return hal_sdiohost_stubs.hal_sdiohost_send_cmd_53_adma(psdiohost_adapter, rw_flag, func_num, block_mode, op_code, reg_addr, byte_count,
			adma_system_address_ptr);
}

/**
 *  @brief To abort CMD53 SDMA/ADMA data transfer.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  func_num The function number of current data operation to abort.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_abort_xfer(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num)
{
	return hal_sdiohost_stubs.hal_sdiohost_abort_xfer(psdiohost_adapter, func_num);
}

/**
 *  @brief To check CMD53 SDMA/ADMA data transfer status for completion.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_chk_xfer_error(hal_sdiohost_adapter_t *psdiohost_adapter)
{
	return hal_sdiohost_stubs.hal_sdiohost_chk_xfer_error(psdiohost_adapter);
}

/**
 *  @brief To set data bus speed mode (DS/HS).
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  sdioh_speed The speed setting to switch to.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_switch_xfer_speed(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_speed_t sdioh_speed)
{
	return hal_sdiohost_stubs.hal_sdiohost_switch_xfer_speed(psdiohost_adapter, sdioh_speed);
}

/**
 *  @brief To attempt data bus recovery after data transfer error incident.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_error_recovery(hal_sdiohost_adapter_t *psdiohost_adapter)
{
	return hal_sdiohost_stubs.hal_sdiohost_error_recovery(psdiohost_adapter);
}

/**
 *  @brief To set data transfer block size.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  block_size The size of one data block in bytes.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_set_block_size(hal_sdiohost_adapter_t *psdiohost_adapter, u16 block_size)
{
	return hal_sdiohost_stubs.hal_sdiohost_set_block_size(psdiohost_adapter, block_size);
}

/**
 *  @brief To set data transfer bus width in SDIO client.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  bus_width The setting for data bus width.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_client_bus_setting(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_client_bus_width_t bus_width)
{
	return hal_sdiohost_stubs.hal_sdiohost_client_bus_setting(psdiohost_adapter, bus_width);
}

/**
 *  @brief To enable/disable specific function number in SDIO client.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  func_num The function number in SDIO client to enable/disable.
 *  @param[in]  fn_state The state setting for selected function number.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_client_enable_fn(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num,
		sdioh_client_fn_state_t fn_state)
{
	return hal_sdiohost_stubs.hal_sdiohost_client_enable_fn(psdiohost_adapter, func_num, fn_state);
}

/**
 *  @brief To set data transfer block size of specific function number in SDIO client.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  func_num The function number in SDIO client to apply setting to.
 *  @param[in]  block_size The size of one data block in bytes.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_client_set_block_size(hal_sdiohost_adapter_t *psdiohost_adapter, sdioh_function_number_t func_num, u16 block_size)
{
	return hal_sdiohost_stubs.hal_sdiohost_client_set_block_size(psdiohost_adapter, func_num, block_size);
}

/**
 *  @brief To create table entry for ADMA descriptor table
 *
 *  @param[in]  buffer_ptr The pointer to buffer for data read/write.
 *  @param[in]  length The length of data in bytes to read/write.
 *  @param[in]  end The end flag for ADMA data transfer.
 *  @param[in]  adma_system_address_ptr The pointer to the ADMA descriptor table.
 *
 *  @returns    The result.
 */
__STATIC_INLINE hal_status_t hal_sdiohost_create_adma_entry(u32 *buffer_ptr, u16 length, sdioh_adma_line_end_t end, u32 *adma_system_address_ptr)
{
	return hal_sdiohost_stubs.hal_sdiohost_create_adma_entry(buffer_ptr, length, end, adma_system_address_ptr);
}

/**
 *  @brief To hook a callback function to make OS do a context-switch while waiting.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  task_yield The callback function.
 *  @param[in]  pdata The pointer to data required for callback function.
 *
 *  @returns    void.
 */
__STATIC_INLINE void hal_sdiohost_task_yield_hook(hal_sdiohost_adapter_t *psdiohost_adapter, sdiohost_para_cb_t task_yield, void *pdata)
{
	hal_sdiohost_stubs.hal_sdiohost_task_yield_hook(psdiohost_adapter, task_yield, pdata);
}

/**
 *  @brief To hook a callback function on SDMA/ADMA transfer completion.
 *
 *  @param[in]  psdiohost_adapter The SDIO host HAL adapter.
 *  @param[in]  transfer_done_cb The callback function.
 *  @param[in]  pdata The pointer to data required for callback function.
 *
 *  @returns    void.
 */
__STATIC_INLINE void hal_sdiohost_transfer_done_int_hook(hal_sdiohost_adapter_t *psdiohost_adapter, sdiohost_para_cb_t transfer_done_cb, void *pdata)
{
	hal_sdiohost_stubs.hal_sdiohost_transfer_done_int_hook(psdiohost_adapter, transfer_done_cb, pdata);
}

/** @} */ /* End of group hs_hal_sdiohost_ */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SDIOHOST_H_"

