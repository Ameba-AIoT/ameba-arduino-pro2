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
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
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

