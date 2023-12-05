/**************************************************************************//**
 * @file     cmd_shell_rom.h
 * @brief    The header file of the command shell.
 *
 * @version  V1.00
 * @date     2021-08-07
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
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

#ifndef _CMD_SHELL_H_
#define _CMD_SHELL_H_

#include "shell.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 *  @brief To initial the command shell task.
 *
 *  @param uart_adapter The UART port adapter as the I/O of this command shell task.
 *
 *  @returns void
 */
void shell_cmd_task_init(void);


/**
 *  @brief To initial the command shell task for RMA using.
 *
 *  @param uart_adapter The UART port adapter as the I/O of this command shell task.
 *
 *  @returns void
 */
void shell_cmd_without_rom_tbl_task_init(void);


/**
 *  @brief The command shell main function. This function should be called periodically
 *         or in a loop.
 *
 *  @returns void
 */
void shell_cmd_task(void);

/**
 * @brief Set the ROM default prompt string of the shell command.
 *
 * @return  void.
 */
void rom_cmd_shell_set_prompt(void);

#ifdef  __cplusplus
}
#endif

#endif  // #ifndef _CMD_SHELL_H_

