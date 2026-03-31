/******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 *
 ******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "device.h"
#include "serial_api.h"
#include "log_service.h"
#include "osdep_service.h"
#include "serial_ex_api.h"
#include "pinmap.h"

#include "cmsis.h"
#include "mpu.h"
#include "rtl8735b_ramstart.h"
#include "cmsis_os.h"               // CMSIS RTOS header file
#include "hal.h"
#include <string.h>
#include <stdio.h>
//#include "memory.h"
#include "stdio_port_func.h"
#include "hci_uart.h"	// BT HCI

#include "console_auth.h"

extern hal_uart_adapter_t log_uart;

#define KEY_CTRL_D		0x4
#define KEY_NL			0xa // '\n'
#define KEY_ENTER		0xd // '\r'
#define KEY_BS			0x8
#define KEY_ESC			0x1B
#define KEY_LBRKT		0x5B
#define STR_END_OF_MP_FORMAT	"\r\n\r\r#"


#define CMD_HISTORY_LEN	4	// max number of executed command saved
extern char log_buf[LOG_SERVICE_BUFLEN];
extern xSemaphoreHandle log_rx_interrupt_sema;
char cmd_history[CMD_HISTORY_LEN][LOG_SERVICE_BUFLEN];
static unsigned int cmd_history_count = 0;
static char g_bt_uart_bridge = 0;

void _put_char_generic(char c, FILE *stream)
{
	//serial_putc(&loguart_sobj, c);
	//stdio_port_putc(c);
	putc(c, stream);

	// TODO : use fflush. for archive goal, should implement correct newlib implement and remove link wrapper
	_fflush_r(_REENT, stream);
}

void _put_char(char c)
{
	_put_char_generic(c, stdout);
}

void _send_string_generic(const char *str, FILE *stream)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
		//serial_putc(&loguart_sobj, str[i]);
		//stdio_port_putc(str[i]);
		putc(str[i], stream);
		i++;
	}
	_fflush_r(_REENT, stream);
}

void _send_string(const char *str)
{
	_send_string_generic(str, stdout);
}

void _send_buf_generic(uint8_t *buf, uint32_t len, FILE *stream)
{
	char *st_p = (char *)buf;
	if (!len || (!buf)) {
		return;
	}
	while (len) {
		//serial_putc(&loguart_sobj, *st_p);
		//stdio_port_putc(*st_p);
		putc(*st_p, stream);
		st_p++;
		len--;
	}
	_fflush_r(_REENT, stream);
}

void _send_buf(uint8_t *buf, uint32_t len)
{
	_send_buf_generic(buf, len, stdout);
}


__weak void uart_set_dbgmon_pending(void) {}

static unsigned char temp_buf[LOG_SERVICE_BUFLEN] = "\0";
static unsigned char combo_key = 0;
static short buf_count = 0;
static unsigned char key_enter = 0;
static char cmd_history_index = 0;
//rc = serial_getc(sobj);
void default_key_handling(char rc)
{

	if (key_enter && rc == KEY_NL) {
		//serial_putc(sobj, rc);
		return;
	}

	// ignore NULL terminate
	if (rc == 0) {
		return;
	}

	if (rc == KEY_ESC) {
		combo_key = 1;
	} else if (rc == KEY_CTRL_D) {
		uart_set_dbgmon_pending();
	} else if (combo_key == 1) {
		if (rc == KEY_LBRKT) {
			combo_key = 2;
		} else {
			combo_key = 0;
		}
	} else if (combo_key == 2) {
		if (rc == 'A' || rc == 'B') { // UP or Down
			if (rc == 'A') {
				cmd_history_index--;
				if (cmd_history_index < 0) {
					cmd_history_index = (cmd_history_count > CMD_HISTORY_LEN) ? CMD_HISTORY_LEN - 1 : (cmd_history_count - 1) % CMD_HISTORY_LEN;
				}
			} else {
				cmd_history_index++;
				if (cmd_history_index > (cmd_history_count > CMD_HISTORY_LEN ? CMD_HISTORY_LEN - 1 : (cmd_history_count - 1) % CMD_HISTORY_LEN)) {
					cmd_history_index = 0;
				}
			}

			if (cmd_history_count > 0) {
				buf_count = strlen((char const *)temp_buf);
				memset(temp_buf, '\0', buf_count);
				while (--buf_count >= 0) {
					//serial_putc(sobj, KEY_BS);
					//serial_putc(sobj, ' ');
					//serial_putc(sobj, KEY_BS);
					_put_char(KEY_BS);
					_put_char(' ');
					_put_char(KEY_BS);
				}
				_send_string(cmd_history[cmd_history_index % CMD_HISTORY_LEN]);
				strcpy((char *)temp_buf, cmd_history[cmd_history_index % CMD_HISTORY_LEN]);
				buf_count = strlen((char const *)temp_buf);
			}
		}

		// exit combo
		combo_key = 0;
	} else if (rc == KEY_ENTER) {
		key_enter = 1;
		if (buf_count > 0) {
			//serial_putc(sobj, KEY_NL);
			//serial_putc(sobj, KEY_ENTER);
			_put_char(KEY_NL);
			_put_char(KEY_ENTER);
			memset(log_buf, '\0', LOG_SERVICE_BUFLEN);
			strncpy(log_buf, (char *)&temp_buf[0], buf_count);
			if (log_rx_interrupt_sema != NULL) {
				rtw_up_sema((_sema *)&log_rx_interrupt_sema);
			}

			/* save command */
			memset(cmd_history[((cmd_history_count) % CMD_HISTORY_LEN)], '\0', buf_count + 1);
			strncpy(cmd_history[((cmd_history_count++) % CMD_HISTORY_LEN)], (char *)&temp_buf[0], buf_count);

			memset(temp_buf, '\0', buf_count);
			cmd_history_index = cmd_history_count % CMD_HISTORY_LEN;
			//cmd_history_count++;
			buf_count = 0;
		} else {
			_send_string(STR_END_OF_MP_FORMAT);
		}
	} else if (rc == KEY_BS) {
		if (buf_count > 0) {
			buf_count--;
			temp_buf[buf_count] = '\0';

			//serial_putc(sobj, rc);
			//serial_putc(sobj, ' ');
			//serial_putc(sobj, rc);
			_put_char(rc);
			_put_char(' ');
			_put_char(rc);
		}
	} else {
		/* cache input characters */
		if (buf_count < (LOG_SERVICE_BUFLEN - 1)) {
			temp_buf[buf_count] = rc;
			buf_count++;
			//serial_putc(sobj, rc);
			_put_char(rc);
			key_enter = 0;
		} else if (buf_count == (LOG_SERVICE_BUFLEN - 1)) {
			temp_buf[buf_count] = '\0';

			_send_string(("\r\nWARN: exceed size limit"STR_END_OF_ATCMD_RET));
		}
	}
}

typedef struct user_key_event_s {
	char seq[8];
	int  seq_len;
	void (*action)(void);
} user_key_event_t;

static user_key_event_t user_key_mapping[8];
static int user_key_mapping_cnt;

static char key_shift_buf[8];	// 0 is latest
void uesrdef_key_handling(char rc)
{
	memmove(&key_shift_buf[0], &key_shift_buf[1], 7);
	key_shift_buf[7] = rc;

	for (int i = 0; i < user_key_mapping_cnt; i++) {
		if (memcmp(&key_shift_buf[8 - user_key_mapping[i].seq_len], user_key_mapping[i].seq, user_key_mapping[i].seq_len) == 0) {
			user_key_mapping[i].action();
		}
	}

}

void key_event_register(char *key_seq, int seq_len, void (*action)(void))
{
	if (user_key_mapping_cnt >= 8)	{
		return;
	}

	memcpy(user_key_mapping[user_key_mapping_cnt].seq, key_seq, 8);
	user_key_mapping[user_key_mapping_cnt].seq_len = seq_len;
	user_key_mapping[user_key_mapping_cnt].action = action;

	user_key_mapping_cnt++;
}


#define MODE_IRQ 0
#define MODE_TASK 1

#if !defined(CONSOLE_MODE)
#define CONSOLE_MODE MODE_TASK
#endif


#if defined(CONSOLE_MODE) && (CONSOLE_MODE==MODE_IRQ)
__weak void uart_irq(u32 id, u32 event)
{
	char rc = 0;
	if (event == RxIrq) {
		//rc = serial_getc(sobj);
		stdio_port_getc(&rc);
		//rc = getc(stdin);
		default_key_handling((char)rc);
		uesrdef_key_handling((char)rc);
	}
}
#endif


#if defined(CONSOLE_MODE) && (CONSOLE_MODE!=MODE_IRQ)

#define UART_BUF_SIZE	576*2 // 115200/10/1000*50, baud rate/8bit+1bit start + 1bit stop/1000ms*50ms
static char uart_buffer[2][UART_BUF_SIZE];
static int uart_buffer_idx[2] = {0};
static int uart_buffer_slot = 0;
#include <hal_uart.h>
int loguart_readable(void)
{
	extern hal_uart_adapter_t log_uart;
	return log_uart.base_addr->rflvr_b.rx_fifo_lv;
}

void uart_irq(u32 id, u32 event)
{
	char rc = 0;
	if (event == RxIrq) {
		int idx = uart_buffer_idx[uart_buffer_slot];
		while (loguart_readable()) {
			stdio_port_getc(&rc);
			if (idx < UART_BUF_SIZE - 1) {
				uart_buffer[uart_buffer_slot][idx] = rc;
				idx++;
			}
		}
		uart_buffer_idx[uart_buffer_slot] = idx;
	}
}

unsigned uart_write_buffer(unsigned fd, const void *buf, unsigned len)
{
	char *buf_c = (char *)buf;
	for (int i = 0; i < len; i++) {
		stdio_port_putc(buf_c[i]);
	}
	return len;
}

unsigned uart_read_buffer(unsigned fd, void *buf, unsigned len)
{
	int curr_slot;
	unsigned cnt;

	__disable_irq();
	curr_slot = uart_buffer_slot;
	uart_buffer_slot ^= 1;
	__enable_irq();

	cnt = (unsigned)uart_buffer_idx[curr_slot];
	if (cnt > 0) {
		memcpy(buf, uart_buffer[curr_slot], cnt);
	}
	uart_buffer_idx[curr_slot] = 0;

	return cnt;
}

unsigned(*console_stdio_read_buffer)(unsigned fd, void *buf, unsigned len) = uart_read_buffer;
unsigned(*console_stdio_write_buffer)(unsigned fd, const void *buf, unsigned len) = uart_write_buffer;

unsigned(*remote_stdio_read_buffer)(unsigned fd, void *buf, unsigned len) = NULL;
unsigned(*remote_stdio_write_buffer)(unsigned fd, const void *buf, unsigned len) = NULL;

void console_stdio_init(void *read_cb, void *write_cb)
{
	unsigned(*stdio_read_buffer)(unsigned, void *, unsigned) = (unsigned(*)(unsigned, void *, unsigned))read_cb;
	unsigned(*stdio_write_buffer)(unsigned, const void *, unsigned) = (unsigned(*)(unsigned, const void *, unsigned))write_cb;;
	console_stdio_read_buffer = stdio_read_buffer;
	console_stdio_write_buffer = stdio_write_buffer;
}

void remote_stdio_init(void *read_cb, void *write_cb)
{
	unsigned(*stdio_read_buffer)(unsigned, void *, unsigned) = (unsigned(*)(unsigned, void *, unsigned))read_cb;
	unsigned(*stdio_write_buffer)(unsigned, const void *, unsigned) = (unsigned(*)(unsigned, const void *, unsigned))write_cb;;
	remote_stdio_read_buffer = stdio_read_buffer;
	remote_stdio_write_buffer = stdio_write_buffer;
}

void console_stdio_get(void **read_cb, void **write_cb)
{
	*read_cb = (void *)console_stdio_read_buffer;
	*write_cb = (void *)console_stdio_write_buffer;
}

void remote_stdio_get(void **read_cb, void **write_cb)
{
	*read_cb = (void *)remote_stdio_read_buffer;
	*write_cb = (void *)remote_stdio_write_buffer;
}

static char recv_buf[UART_BUF_SIZE];
void console_stdin_handler(void *dummy)
{
	(void)dummy;
	//char buf[UART_BUF_SIZE];
	int rd_len;
	while (1) {
		if (console_stdio_read_buffer && (rd_len = console_stdio_read_buffer(0, recv_buf, UART_BUF_SIZE)) != 0) {

			for (int i = 0; i < rd_len; i++) {
				if (auth_check() == 0) {
					auth_key_handling((char)recv_buf[i]);
				} else {
					if (g_bt_uart_bridge) {
						uesrdef_key_handling((char)recv_buf[i]);
						hci_uart_bridge_to_hci((char)recv_buf[i]);
					} else {
						default_key_handling((char)recv_buf[i]);
						uesrdef_key_handling((char)recv_buf[i]);
					}
				}
			}
		} else if (remote_stdio_read_buffer && (rd_len = remote_stdio_read_buffer(0, recv_buf, UART_BUF_SIZE)) != 0) {
			for (int i = 0; i < rd_len; i++) {
				if (auth_check() == 0) {
					auth_key_handling((char)recv_buf[i]);
				} else {
					default_key_handling((char)recv_buf[i]);
					uesrdef_key_handling((char)recv_buf[i]);
				}
			}
		} else {
			if (g_bt_uart_bridge) {
				vTaskDelay(1);
			} else {
				vTaskDelay(50);
			}
		}
	}
}

#endif

#define system_init(fn) \
static void* init_##fn __attribute__((used, section(".init_array")))  = (void*)fn;

// put to init array
__weak void console_io_init(void)
{
	//uart_send_string((char*)"hook uart interrupt\n\r");
#if defined(SEGGER_RTT) && (SEGGER_RTT==1)
	extern unsigned SEGGER_RTT_Read(unsigned BufferIndex, void *pBuffer, unsigned BufferSize);
	extern unsigned SEGGER_RTT_Write(unsigned BufferIndex, const void *pBuffer, unsigned NumBytes);
	console_stdio_init(SEGGER_RTT_Read, SEGGER_RTT_Write);
#else
	hal_uart_rxind_hook(&log_uart, uart_irq, 0, 0);
	console_stdio_init(uart_read_buffer, uart_write_buffer);
#endif

}

system_init(console_io_init);

extern void log_service_init(void);
void console_init(void)
{
	int i = 0;

#if defined(CONSOLE_MODE) && (CONSOLE_MODE!=MODE_IRQ)
	xTaskCreate(console_stdin_handler, "cons_stdin", 512, NULL, 1, NULL);
#endif

	for (i = 0; i < CMD_HISTORY_LEN; i++) {
		memset(cmd_history[i], '\0', LOG_SERVICE_BUFLEN);
	}
	log_service_init();
}

void console_reinit_uart(void)
{
	hal_uart_reset_rx_fifo(&log_uart);
	hal_uart_rxind_hook(&log_uart, uart_irq, 0, 0);
}



#if 0

//  put to  void console_init(void)
//
//	key_event_register(key_seq_ctrl_c, 1, key_ctrl_c);
//	key_event_register(key_seq_L_arrow, 3, key_L_arrow);
//	key_event_register(key_seq_R_arrow, 3, key_R_arrow);

static char key_seq_ctrl_c[] = {0x3};
void key_ctrl_c(void)
{
	uart_send_string(("key: ctrl c\n\r"));
}

//Down Arrow  0x1B 0x5B 0x42
//Left Arrow  0x1B 0x5B 0x44
//Right Arrow 0x1B 0x5B 0x43
//Up Arrow    0x1B 0x5B 0x41

static char key_seq_L_arrow[] = {0x1B, 0x5B, 0x44};
static char key_seq_R_arrow[] = {0x1B, 0x5B, 0x43};
void key_L_arrow(void)
{
	uart_send_string(("key: <-\n\r"));
}

void key_R_arrow(void)
{
	uart_send_string(("key: ->\n\r"));
}

#endif

static char key_seq_bridge_close_arrow[] = "ge,close"; // ATM2=bridge,close
void key_bridge_close(void)
{
	hci_uart_bridge_open(false);
	user_key_mapping_cnt--;
	g_bt_uart_bridge = 0;
}

void key_bridge_register(void)
{
	key_event_register(key_seq_bridge_close_arrow, 8, key_bridge_close);
	g_bt_uart_bridge = 1;
}





