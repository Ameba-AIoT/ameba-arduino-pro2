/**************************************************************************//**
 * @file     shell_stub.c
 * @brief    This shell stub functions. Re-direct to ROM code functions.
 *
 * @version  V1.00
 * @date     2016-07-15
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

#include "shell.h"


/**
 * @addtogroup util_shell Shell Command Interface
 * @{
 */

extern const cmd_shell_func_stubs_t cmd_shell_stubs;

#define SHELL_CMD_BUF_SIZE       80
#define SHELL_CMD_HIST_SIZE      256

shell_command_t shell_cmd_hdl;
char shell_cmd_buffer[SHELL_CMD_BUF_SIZE];
char shell_cmd_hist[SHELL_CMD_HIST_SIZE];
shell_command_entry_t shell_cmd_list[SHELL_CMD_LIST_SIZE];
char shell_case_conv_buf[32];

const char prompt_str[] = "$8735b>";

/**
 * @brief Initialize the shell command line interface.
 *
 * @details Initializes the resources used by the command line interface. This function
 *          also tries to start the command line task if the option is enabled. The main
 *          program for the command line interface where all the data is handled is
 *          shell_task().
 *
 * @param[in]   pshell_cmd  The The shell command entity to be initialized.
 *
 * @param[in]   reader      The callback function used to get a character from the stream.
 *
 * @param[in]   writer      The callback function used to write a character to the stream.
 *
 * @param[in]   adapter     The user pointer for the character read/write callback function calling.
 *                          This pointer usually point to a handler of an UART/terminal device.
 *
 * @return  Returns TRUE if the shell was succesfully initialized, returns FALSE
 *          otherwise.
 */
BOOL shell_init(shell_reader_t reader, shell_writer_t writer, void *adapter)
{
	return cmd_shell_stubs.shell_init(&shell_cmd_hdl, reader, writer, adapter);
}

/**
 * @brief Initialize the command line interface and setup the callback function
 *        for the shell command to read/write a character from/to the terminal.
 *        The function to read/write characters is implemented by the StdIO Port.
 *        So the StdIO Port should be initialed before callinf this function.
 *        The StdIO Port initialization is out of the function of shell
 *        command module.
 *
 * @return  Returns TRUE if the shell was succesfully initialized, returns FALSE
 *          otherwise.
 */
BOOL shell_init_with_stdio_port(void)
{
	return cmd_shell_stubs.shell_init_with_stdio_port(&shell_cmd_hdl);
}

/**
 * @brief Assign a buffer for the command characters receiving.
 *
 * Before we start the shell command task, the command receive buffer MUST be assigned.
 *
 * @param buf The given buffer.
 *
 * @param buf_size The size of the given buffer, in bytes.
 *
 * @return Returns TRUE if the shell was succesfully initialized, returns FALSE
 * otherwise.
 */
BOOL shell_set_cmd_buf(char *buf, unsigned int buf_size)
{
	return cmd_shell_stubs.shell_set_cmd_buf(&shell_cmd_hdl, buf, buf_size);
}

/**
 * @brief To assign a buffer for the command history.
 *
 * @details This buffer is used to store commands ever entered. So we can re-call a command
 *          from the history buffer. This is a ring buffer. Once the buffer is full, the new
 *          added command will overwrite the oldest command.
 *
 * @param[in]   buf         The given buffer.
 *
 * @param[in]   buf_size    The size of the given buffer, in bytes.
 *
 * @return  Returns TRUE if the shell was succesfully initialized, returns FALSE
 *          otherwise.
 */
BOOL shell_set_hist_buf(char *buf, unsigned int buf_size)
{
	return cmd_shell_stubs.shell_set_hist_buf(&shell_cmd_hdl, buf, buf_size);
}

/**
 * @brief Set the prompt string of the shell command.
 *
 * @param[in]   prompt      The pointer of the prompt string.
 *
 * @return  void.
 */
void shell_set_prompt(const char *prompt)
{
	cmd_shell_stubs.shell_set_prompt(&shell_cmd_hdl, prompt);
}

/**
 * @brief Assign a prefixed command table to the shell command.
 *
 * @details When a command string is entered, we will search the match command from this table
 *          and execute the callback function if a matched command is found.
 *
 * @param[in]   cmd_table   The start pointer of the prefixed command table.
 *
 */
void shell_set_cmd_table(const shell_command_entry_t *cmd_table)
{
	cmd_shell_stubs.shell_set_cmd_table(&shell_cmd_hdl, cmd_table);
}

/**
 * @brief Hooks a registrable command entry buffer to the shell command. A new command entry can be
 *        add to this command list at run time.
 *
 * @param[in]   cmd_list    The buffer for the registerable of command entry list.
 *
 * @param[in]   list_size   The command list size, which means the maximum number of commands we can add to this list.
 *
 */
void shell_set_cmd_list(shell_command_entry_t *cmd_list, unsigned int list_size)
{
	cmd_shell_stubs.shell_set_cmd_list(&shell_cmd_hdl, cmd_list, list_size);
}

/**
 * @brief Register a command entry on the registerable command list.
 *
 * @details Registers a command on the registerable command list. The command string and the
 *          corresponding callback function should be provided.
 *
 * @param[in]   program     The callback function for the new register command.
 *
 * @param[in]   cmd_string  The new command to be registered.
 *
 * @param[in]   help_string A describtion about the command to be registered.
 *
 * @return  Returns TRUE if command was successfully added to the command list,
 *          or returns FALSE if something fails (no more commands can be registered).
 */
#if defined(COLLECT_SHELL) && (COLLECT_SHELL == 1) //Raymond
BOOL shell_register(shell_program_t program, const char *cmd_string, const char *help_string)
{
	return cmd_shell_stubs.shell_register(&shell_cmd_hdl, program, cmd_string, help_string);
}
#else
BOOL shell_register(shell_command_entry_t *entry_cmd)
{
	return cmd_shell_stubs.shell_register(&shell_cmd_hdl, entry_cmd);
}
#endif
/**
 * @brief Removes all commands entrys in the registrable command list.
 *
 * @return  void.
 */
void shell_unregister_all(void)
{
	cmd_shell_stubs.shell_unregister_all(&shell_cmd_hdl);
}

/**
 * @brief Main shell command processing loop.
 *
 * @details This function implements the main functionality of the shell command line interface.
 *          This function should be called frequently so it can handle the input from the terminal
 *          data stream.
 *
 * @param[in]   pshell_cmd  The command shell entity.
 *
 * @return  -1: if the shell command entity is not initialed.
 * @return   0: wait for a command input or no match command was found for the input string.
 * @return   other: the return value from the command handler function.
 */
s32 shell_task(void)
{
	return cmd_shell_stubs.shell_task(&shell_cmd_hdl);
}

/**
 * @brief Initialize the application level of shell command interface entity.
 *
 * @details This function provides a "one step" initialization of the shell command interface.
 *          It will setup all needed resource for the shell command function. The shell command
 *          function is ready to run after this function call.
 *
 * @return  void
 */
void shell_cmd_init(void)
{
	// assign the buffer for input command
	shell_set_cmd_buf(shell_cmd_buffer, SHELL_CMD_BUF_SIZE);

	// assign the buffer for command history
	shell_set_hist_buf(shell_cmd_hist, SHELL_CMD_HIST_SIZE);

	// hook the putc & getc functions
	shell_init_with_stdio_port();
	shell_cmd_hdl.case_conv_buf = shell_case_conv_buf;
	shell_set_cmd_table(cmd_shell_stubs.rom_cmd_table);
	shell_set_prompt(prompt_str);

	// Add a buffer for dynamical shell command register
	shell_set_cmd_list(shell_cmd_list, SHELL_CMD_LIST_SIZE);
	shell_unregister_all();
}

#if 0
// Entry function for Non-Secure

BOOL __attribute__((cmse_nonsecure_entry)) shell_init(shell_reader_t reader, shell_writer_t writer, void *adapter)
{
	return shell_init(reader, writer, adapter);
}

BOOL __attribute__((cmse_nonsecure_entry)) shell_init_with_stdio_port(void)
{
	return shell_init_with_stdio_port();
}

BOOL __attribute__((cmse_nonsecure_entry)) shell_set_cmd_buf(char *buf, unsigned int buf_size)
{
	return shell_set_cmd_buf(buf, buf_size);
}

BOOL __attribute__((cmse_nonsecure_entry)) shell_set_hist_buf(char *buf, unsigned int buf_size)
{
	return shell_set_hist_buf(buf, buf_size);
}

void __attribute__((cmse_nonsecure_entry)) shell_set_prompt_ns(const char *prompt)
{
	shell_set_prompt(prompt);
}

void __attribute__((cmse_nonsecure_entry)) shell_set_cmd_table(const shell_command_entry_t *cmd_table)
{
	shell_set_cmd_table(cmd_table);
}

void __attribute__((cmse_nonsecure_entry)) shell_set_cmd_list_ns(shell_command_entry_t *cmd_list, unsigned int list_size)
{
	shell_set_cmd_list(cmd_list, list_size);
}

BOOL __attribute__((cmse_nonsecure_entry)) shell_register_ns(shell_program_t program, const char *cmd_string, const char *help_string)
{
	return shell_register(program, cmd_string, help_string);
}

void __attribute__((cmse_nonsecure_entry)) shell_unregister_all_ns(void)
{
	shell_unregister_all();
}

s32 __attribute__((cmse_nonsecure_entry)) shell_task_ns(void)
{
	return shell_task();
}

void __attribute__((cmse_nonsecure_entry)) shell_cmd_init_ns(void)
{
	shell_cmd_init();
}
#endif

/** @} */ /* End of group util_shell */

