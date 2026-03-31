#include <stdint.h>
#include <string.h>
#include <lwip_netconf.h>
#include "console_auth.h"
#include "hal_cache.h"

extern void _put_char_generic(char c, FILE *stream);
extern void _send_string_generic(const char *str, FILE *stream);
extern void _send_buf_generic(uint8_t *buf, uint32_t len, FILE *stream);

static int console_auth_errcnt = 0;

#if defined(CONSOLE_AUTH) && (CONSOLE_AUTH==1)
static int console_auth_state = CONSOLE_AUTH_FAIL;
#else
static int console_auth_state = CONSOLE_AUTH_PASS;
#endif

#if defined(CONSOLE_AUTH) && (CONSOLE_AUTH==1) && (CONSOLE_AUTH_WARM_BOOT_RECORD==1)
static __attribute__((section(".retention.data"))) uint32_t auth_mark __attribute__((aligned(32))) = 0;
static __attribute__((section(".retention.data"))) uint32_t auth_status __attribute__((aligned(32))) = 0;
#endif


static char password[16];
char *console_auth_get_password(void)
{
	/* Just an example, please use reliable algorithm to generating password */
	uint8_t mac[6];
	uint8_t macd[6];

	memcpy(mac, LwIP_GetMAC(0), 6);
	macd[0] = mac[5] - mac[0];
	macd[1] = mac[0] - mac[1];
	macd[2] = mac[1] - mac[2];
	macd[3] = mac[2] - mac[3];
	macd[4] = mac[3] - mac[4];
	macd[5] = mac[4] - mac[5];

	for (int i = 0; i < 6; i++) {
		if (mac[i] < 0x30) {
			mac[i] += 0x30;
		}
		if (macd[i] < 0x30) {
			macd[i] += 0x30;
		}
		if (mac[i] > 0x7F) {
			mac[i] = ((mac[i] - 0x30) % 0x4E) + 0x30;
		}
		if (macd[i] > 0x7F) {
			macd[i] = ((macd[i] - 0x30) % 0x4E) + 0x30;
		}
	}

	memcpy(password, mac, 6);
	memcpy(&password[6], macd, 6);
	password[12] = 0;
	return password;
}

static char auth_buffer[AUTH_BUF_SIZE + 4];
static int auth_idx = 0;
void auth_key_handling(char c)
{
#if CONSOLE_AUTH_FAIL_BLOCK == 1
	if (console_auth_state == CONSOLE_AUTH_BLOCK) {
		return;
	}
#endif

	if (c == '\n' || c == '\r') {
		// show auth fail, please enter password
		if (auth_idx == 0) {
			_send_string_generic("\n\rpassword:", stderr);
		} else {
			//_send_buf_generic((uint8_t*)auth_buffer, auth_idx, stderr);
			//_send_buf_generic((uint8_t*)console_auth_get_password(), 12, stderr);
			int cmp_res = strncmp(auth_buffer, console_auth_get_password(), 12);
			if (cmp_res != 0) {
				_send_string_generic("\n\rwrong password\n\rpassword:", stderr);
				console_auth_errcnt++;
			} else {
				console_auth_state = CONSOLE_AUTH_PASS;
				console_auth_errcnt = 0;
#if defined(CONSOLE_AUTH) && (CONSOLE_AUTH==1) && (CONSOLE_AUTH_WARM_BOOT_RECORD==1)
				auth_status = CONSOLE_AUTH_PASS;
				dcache_clean_invalidate_by_addr((uint32_t *) &auth_status, sizeof(auth_status));
#endif
				_send_string_generic("\n\rauth success\n\r", stderr);
			}
		}
		auth_idx = 0;
	} else {
		if (c >= 0x20 && c <= 0x7F) {
			_put_char_generic('*', stderr);

			auth_buffer[auth_idx++] = c;
			if (auth_idx >= AUTH_BUF_SIZE) {
				_send_string_generic("\n\rwrong password\n\rpassword:", stderr);
				console_auth_errcnt++;
				auth_idx = 0;
			}
		} else {
			_send_string_generic("\n\rwrong password\n\rpassword:", stderr);
			console_auth_errcnt++;
			auth_idx = 0;
		}
	}
#if CONSOLE_AUTH_FAIL_BLOCK == 1
	if (console_auth_errcnt >= 3) {
		console_auth_state = CONSOLE_AUTH_BLOCK;
		_send_string_generic("\n\rblock login\n\r", stderr);
	}
#endif
}

int auth_check(void)
{
#if defined(CONSOLE_AUTH) && (CONSOLE_AUTH==1) && (CONSOLE_AUTH_WARM_BOOT_RECORD==1)
	if (auth_mark != CONSOLE_AUTH_MAGIC) {
		auth_mark = CONSOLE_AUTH_MAGIC;
		auth_status = CONSOLE_AUTH_FAIL;
		dcache_clean_invalidate_by_addr((uint32_t *) &auth_mark, sizeof(auth_mark));
		dcache_clean_invalidate_by_addr((uint32_t *) &auth_status, sizeof(auth_status));
	}

	if (auth_mark == CONSOLE_AUTH_MAGIC) {
		console_auth_state = auth_status;
	}
#endif
	return console_auth_state == CONSOLE_AUTH_PASS;
}