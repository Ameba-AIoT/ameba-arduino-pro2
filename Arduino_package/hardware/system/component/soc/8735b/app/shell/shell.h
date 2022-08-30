/**************************************************************************//**
 * @file     shell.h
 * @brief    The macro and data structure type definition for command shell.
 *
 * @version  V1.00
 * @date     2021-08-07
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

#ifndef _SHELL_H_
#define _SHELL_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "platform_conf.h"

#include "basic_types.h"
#include <stddef.h> /* for size_t */
#include <stdarg.h>


#include "rt_printf.h"

// Section define
#define SECTION_SHELL_TEXT         SECTION(".shell.text")
//#define SECTION_SHELL_DATA         SECTION(".shell.data")
#define SECTION_SHELL_RODATA       SECTION(".shell.rodata")
#define SECTION_SHELL_BSS          SECTION(".shell.bss")

/**
 * @addtogroup util_shell Shell Command Interface
 * @ingroup 8710c_util
 * @{
 * @brief The shell command line interface API.
 */

/**
  \brief  The flag to control the enable of the command history log.
          The history log function will use 1K code size.
*/
#define CONFIG_SHELL_HISTORY_EN             1

/**
  \brief  The flag to control the enable of the command auto-complete (by tab key).
          The auto-complete function will use 0.8K code size.
*/
#define CONFIG_SHELL_AUTO_COMP_EN           1

/// The maximum number of commands that can be registered.
#define CONFIG_SHELL_MAX_COMMANDS           10

/// The maximum characters that the command input buffer can accept.
#define CONFIG_SHELL_MAX_INPUT              70

/// Configures the maximum number of arguments per command tha can be accepted.
#define CONFIG_SHELL_MAX_COMMAND_ARGS       10

/// The maximum number of commands that can be registered.
#define CONFIG_SHELL_FMT_BUFFER             70

/// The maximum characters that can be storred in the history buffer.
#define CONFIG_SHELL_MAX_HIST_SIZE          512

/// The maximum characters for the escape sequence processing.
#define CONFIG_SHELL_MAX_ESCAPE_LEN         8

/// The ROM CMD LIST SIZE FOR_BOOT ROM
#define SHELL_BOOT_ROM_CMD_LIST_SIZE        16

/// The ROM CMD LIST SIZE FOR ROM
#define SHELL_ROM_CMD_LIST_SIZE             32

/// The size of CMD list for verify code
#define SHELL_VRF_CMD_LIST_SIZE             200

/// The RAM CMD LIST SIZE
#define SHELL_CMD_LIST_SIZE                 (SHELL_ROM_CMD_LIST_SIZE + SHELL_VRF_CMD_LIST_SIZE)

/**
  \brief  Defines the ASCII code for the shell command input control keys.
*/
enum shell_ctrl_key_ascii_e {
	SHELL_ASCII_NUL             = 0x00,     ///< Null character.
	SHELL_ASCII_BEL             = 0x07,     ///< Bell.
	SHELL_ASCII_BS              = 0x08,     ///< Backspace.
	SHELL_ASCII_HT              = 0x09,     ///< Horizontal Tab.
	SHELL_ASCII_LF              = 0x0A,     ///< Line Feed.
	SHELL_ASCII_CR              = 0x0D,     ///< Carriage Return.
	SHELL_ASCII_ESC             = 0x1B,     ///< Escape.
	SHELL_ASCII_US              = 0x1F,     ///< Unit Separator.
	SHELL_ASCII_SP              = 0x20,     ///< Space.
	SHELL_ASCII_DEL             = 0x7F      ///< Delete.
};

#define SHELL_RET_SUCCESS                   0
#define SHELL_RET_FAILURE                   1

#if defined(ROM_REGION)
extern int _strcmp(const char *cs, const char *ct);
extern int _strncmp(const char *cs, const char *ct, unsigned int count);
extern size_t _strlen(const char *s);
extern void *_memcpy(void *s1, const void *s2, size_t n);
extern void *_memmove(void *destaddr, const void *sourceaddr, unsigned length);
extern void *_memset(void *s, int c, size_t n);

#define shell_strcmp(cs, ct)                _strcmp(cs, ct)
#define shell_strncmp(cs, ct, count)        _strncmp(cs, ct, count)
#define shell_strlen(s)                     _strlen(s)
#define shell_memcpy(dest, src, len)        _memcpy(dest, src, len)
#define shell_memmove(dest, src, len)       _memmove(dest, src, len)
#define shell_memset(dest, value, len)      _memset(dest, value, len)

#else

#include "string.h"

#define shell_strcmp(cs, ct)                strcmp(cs, ct)
#define shell_strncmp(cs, ct, count)        strncmp(cs, ct, count)
#define shell_strlen(s)                     strlen(s)
#define shell_memcpy(dest, src, len)        memcpy(dest, src, len)
#define shell_memmove(dest, src, len)       memmove(dest, src, len)

#endif

/**
  \brief  The function for the shell command to read a character from the terminal.
*/
typedef int (*shell_reader_t)(char *);

/**
  \brief  The function for the shell command to send a character to the terminal.
*/
typedef int (*shell_writer_t)(char);

/**
  \brief  The function for the shell command to print a string of message text.
*/
typedef void (*shell_printer_t)(const char *fmt, ...);

/**
  \brief  The callback function type of a shell command.
*/
typedef s32(*shell_program_t)(u32, char **);

#if 0
/**
  \brief  The enumeration of errors of shell command.
 */
enum shell_errors {
	E_SHELL_ERR_ARGCOUNT = 0,   ///< There are missing arguments for the command
	E_SHELL_ERR_OUTOFRANGE,     ///< The program received an argument that is out of range
	E_SHELL_ERR_VALUE,          ///< The program received an argument with a value different than expected
	E_SHELL_ERR_ACTION,         ///< Invalid action requested for the current state
	E_SHELL_ERR_PARSE,          ///< Cannot parse the user input
	E_SHELL_ERR_STORAGE,        ///< Cannot access storage device or memory device
	E_SHELL_ERR_IO,             ///< IO device error caused program interruption
};
#endif


/**
  \brief  The data type of a shell command entry.
 */
typedef struct shell_command_entry_s {
	const char *shell_command_type;   /*!< the command type string */
	const char *shell_command_string;   /*!< the command string */
	shell_program_t shell_program;      /*!< the callback function association with the command string */
	const char *help_string;            /*!< the hel message for the command */
} shell_command_entry_t;

/**
  \brief  The data structure for the shell command handling.
 */
typedef struct shell_command {
	const shell_command_entry_t *cmd_table; /*!< the pre-defined(compile time defined) table of command entrys */

	shell_command_entry_t *cmd_list; /*!< the registerable table of command entrys.
                                          A new command entry is able to be added to this table at run time */
	char current_type[32];          /*!< current type for class command */
	char *shellbuf; /*!< the buffer to store the received command characters */

	shell_reader_t shell_reader;    /*!< The function for the shell command to read a character from the terminal */
	shell_writer_t shell_writer;    /*!< The function for the shell command to write a character to the terminal */
	void *adapter;  /*!< The adapter (UART adapter) for terminal to read/write characters */

	const char *prompt;   /*!< point to a string as the command prompt */

	char *hist_buf; /*!< the buffer to store the command history, this is a ring buffer */

	char *argv_list[CONFIG_SHELL_MAX_COMMAND_ARGS];    /*!< the array to holds the parameters(string pointers) of a command */
	unsigned int  argc;            /*!< the parameters counter */

	unsigned int cmd_list_size;    /*!< the size (number of command entrys) of the registerable command table */
	unsigned int shellbuf_sz;      /*!< the size (in bytes) of the command characters receive buffer */
	unsigned int buf_count;        /*!< the counter of the characters are received in the receive buffer */
	unsigned int buf_pos;          /*!< the position of the receive buffer, to indicate the cursor location
                                        in the receive buffer */
	int hist_step;  /*!< the position of the history buffer, it indicates the start of the selected history command string */
	int hist_begin; /*!< the begin position of the history buffer */
	int hist_end;   /*!< the end position of the history buffer */
	unsigned int hist_buf_sz;   /*!< the size (in byte) of the history buffer */

	int escape_len;     /*!< number of received characters of a escape sequence */
	char escape[CONFIG_SHELL_MAX_ESCAPE_LEN];     /*!< the buffer to store all characters of a escape sequence */
	BOOL initialized;   /*!< indicates if the shell command adapter is totally initialed or not */
	uint8_t reserved1[3];
	char *case_conv_buf;   /*!< the buffer for command case conversion, if this pointer is NULL means the command is case sense */
} shell_command_t;

/// @cond DOXYGEN_SHELL_ROM_CODE
/**
 * @addtogroup util_shell_rom_func
 * @ingroup util_shell
 * @{
 */

BOOL _shell_init(shell_command_t *pshell_cmd, shell_reader_t reader, shell_writer_t writer, void *adapter);
BOOL _shell_set_cmd_buf(shell_command_t *pshell_cmd, char *buf, unsigned int buf_size);
BOOL _shell_set_hist_buf(shell_command_t *pshell_cmd, char *buf, unsigned int buf_size);
void _shell_set_prompt(shell_command_t *pshell_cmd, const char *prompt);
void _shell_set_cmd_table(shell_command_t *pshell_cmd, const shell_command_entry_t *cmd_table);
void _shell_set_cmd_list(shell_command_t *pshell_cmd, shell_command_entry_t *cmd_list, unsigned int list_size);
BOOL _shell_register(shell_command_t *pshell_cmd, shell_command_entry_t *entry_cmd);
void _shell_unregister_all(shell_command_t *pshell_cmd);
s32 _shell_task(shell_command_t *pshell_cmd);
s32 _shell_parse_one_cmd(shell_command_t *pshell_cmd);

/** @} */ /* End of group util_shell_rom_func */

/// @endcond /* End of condition DOXYGEN_SHELL_ROM_CODE */

/**
  \brief  The data structure of the stubs function for the shell functions in ROM
*/
typedef struct cmd_shell_func_stubs_s {
	shell_command_t *shell_cmd_hdl;
	BOOL (*shell_init)(shell_command_t *pshell_cmd, shell_reader_t reader, shell_writer_t writer, void *adapter);
	BOOL (*shell_init_with_stdio_port)(shell_command_t *pshell_cmd);
	BOOL (*shell_set_cmd_buf)(shell_command_t *pshell_cmd, char *buf, unsigned int buf_size);
	BOOL (*shell_set_hist_buf)(shell_command_t *pshell_cmd, char *buf, unsigned int buf_size);
	void (*shell_set_prompt)(shell_command_t *pshell_cmd, const char *prompt);
	void (*shell_set_cmd_table)(shell_command_t *pshell_cmd, const shell_command_entry_t *cmd_table);
	void (*shell_set_cmd_list)(shell_command_t *pshell_cmd, shell_command_entry_t *cmd_list, unsigned int list_size);
	BOOL (*shell_register)(shell_command_t *pshell_cmd, shell_command_entry_t *entry_cmd);
	void (*shell_unregister_all)(shell_command_t *pshell_cmd);
	void (*shell_cmd_task_init)(void);
	s32(*shell_task)(shell_command_t *pshell_cmd);
	s32(*shell_parse_one_cmd)(shell_command_t *pshell_cmd);
	void (*shell_rom_cmd_set_prompt)(void);

	const shell_command_entry_t *rom_cmd_table;
	void (*shell_cmd_without_rom_tbl_task_init)(void);
	uint32_t reserved[5];  // reserved space for next ROM code version function table extending.
} cmd_shell_func_stubs_t;

BOOL shell_init(shell_reader_t reader, shell_writer_t writer, void *adapter);
BOOL shell_set_cmd_buf(char *buf, unsigned int buf_size);
BOOL shell_set_hist_buf(char *buf, unsigned int buf_size);
void shell_set_prompt(const char *prompt);
void shell_set_cmd_table(const shell_command_entry_t *cmd_table);
void shell_set_cmd_list(shell_command_entry_t *cmd_list, unsigned int list_size);
BOOL shell_register(shell_command_entry_t *entry_cmd);
void shell_unregister_all(void);
s32 shell_task(void);

/** @} */ /* End of group util_shell */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#ifndef _SHELL_H_"
// End of Header file
