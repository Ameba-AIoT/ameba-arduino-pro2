#include <platform_stdlib.h>
#include <platform_opts.h>
#include "log_service.h"
#include "atcmd_mp.h"
#include <sys_api.h>


#include <stdio.h>
#include "atcmd_wifi.h"
#include "atcmd_lwip.h"
#include "osdep_service.h"


#if defined(CONFIG_ATCMD_MP) && CONFIG_ATCMD_MP
extern void fATM2(void *arg);	// MP ext2 AT command
//-------- AT MP commands ---------------------------------------------------------------
volatile u8 g_dram_thread_0 = 0;
volatile u8 g_dram_thread_1 = 0;
u8 g_dram_r = 0;
u8 g_dram_w = 0;

void dram_thread_0(void *param)
{
	u32 i, data;
#if 1
	// wo XIP
	u32 buf_size;
	u8	*buf;

	buf_size = 8 * 1024 * 1024;
	buf = rtw_zmalloc(buf_size);
	printf("buf0 = 0x%08x\n\r", buf);
	if (buf) {
		g_dram_thread_0 = 1;
		while (g_dram_thread_0) {
			for (i = 0; i < buf_size; i++) {
				if (g_dram_r) {
					data = buf[i];
				}
				if (g_dram_w) {
					buf[i] = i;
				}
				if (!g_dram_thread_0) {
					break;
				}
				if ((i % 32) == 31) {
					dcache_clean_invalidate_by_addr((uint32_t *)&buf[i - 31], 32);
				}
			}
		}
		rtw_mfree((u8 *)buf, buf_size);
	}
#else
	// XIP
	g_dram_thread_0 = 1;
	while (g_dram_thread_0) {
		for (i = 0; i < 0x1600000; i += 4) { // 22M
			if (g_dram_r) {
//				printf("r 0x%08x\n\r", 0x70000000 + i);
				data = *(u32 *)(0x70000000 + i);
//				printf("r 0x%08x = 0x%04x\n\r", 0x70000000 + i, data);
			}
			if (g_dram_w) {
				*(u32 *)(0x70000000 + i) = i;
//				printf("w 0x%08x = 0x%04x\n\r", 0x70000000 + i, i);
			}
			if (!g_dram_thread_0) {
				break;
			}
		}
	}
#endif
	printf("%s: exit \n\r", __FUNCTION__);
	vTaskDelete(NULL);
}

void dram_thread_1(void *param)
{
	u32 i, data;
#if 1
	// wo XIP
	u32 buf_size;
	u8	*buf;

	buf_size = 8 * 1024 * 1024;
	buf = rtw_zmalloc(buf_size);
	printf("buf1 = 0x%08x\n\r", buf);
	if (buf) {
		g_dram_thread_1 = 1;
		while (g_dram_thread_1) {
			for (i = 0; i < buf_size; i++) {
				if (g_dram_r) {
					data = buf[i];
				}
				if (g_dram_w) {
					buf[i] = i;
				}
				if (!g_dram_thread_1) {
					break;
				}
				if ((i % 32) == 31) {
					dcache_clean_invalidate_by_addr((uint32_t *)&buf[i - 31], 32);
				}
			}
		}
		rtw_mfree((u8 *)buf, buf_size);
	}
#else
	// XIP
	g_dram_thread_1 = 1;
	while (g_dram_thread_1) {
		for (i = 0; i < 0x15FFFC0; i += 4) { // 22M
			if (g_dram_r) {
				data = *(u32 *)(0x71600000 + i);
			}
			if (g_dram_w) {
				*(u32 *)(0x71600000 + i) = i;
			}
			if (!g_dram_thread_1) {
				break;
			}
		}
	}
#endif
	printf("%s: exit \n\r", __FUNCTION__);
	vTaskDelete(NULL);
}

void fATMM(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	(void)argc;

	AT_PRINTK("[ATMM]: _AT_MP_MEM_");
	argc = parse_param(arg, argv);

	if (!strncmp(argv[1], "start", 5)) {
		if (!strncmp(argv[2], "rw", 2)) {
			g_dram_r = 1;
			g_dram_w = 1;
		} else if (!strncmp(argv[2], "r", 1)) {
			g_dram_r = 1;
			g_dram_w = 0;
		} else {
			g_dram_r = 0;
			g_dram_w = 1;
		}
		//dcache_disable();
		if (!g_dram_thread_0) {
			if (xTaskCreate(dram_thread_0, ((const char *)"dram_thread_0"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
				printf("\n\r%s xTaskCreate(dram_thread_0) failed", __FUNCTION__);
			} else {
				if (g_dram_r && g_dram_w) {
					printf("rw dram thread 0 start\n\r");
				} else if (g_dram_r) {
					printf("read dram thread 0 start\n\r");
				} else {
					printf("write dram thread 0 start\n\r");
				}
			}
		}
		if (!g_dram_thread_1) {
			if (xTaskCreate(dram_thread_1, ((const char *)"dram_thread_1"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
				printf("\n\r%s xTaskCreate(dram_thread_1) failed", __FUNCTION__);
			} else {
				if (g_dram_r && g_dram_w) {
					printf("rw dram thread 1 start\n\r");
				} else if (g_dram_r) {
					printf("read dram thread 1 start\n\r");
				} else {
					printf("write dram thread 1 start\n\r");
				}
			}
		}
	}
	if (!strncmp(argv[1], "stop", 4)) {
		//dcache_enable();
		if (g_dram_thread_0) {
			g_dram_thread_0 = 0;
			printf("dram thread 0 stop\n\r");
		}
		if (g_dram_thread_1) {
			g_dram_thread_1 = 0;
			printf("dram thread 1 stop\n\r");
		}
	}
}

void fATMt(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};

	(void)argc;

	AT_PRINTK("[ATM#]: _AT_MP_TEST_");
	argc = parse_param(arg, argv);
}

void fATMx(void *arg)
{
	(void)arg;
	AT_PRINTK("[ATM?]: _AT_MP_HELP_");
}

log_item_t at_mp_items[] = {
	{"ATMM", fATMM, {NULL, NULL}},	// test command
	{"ATM#", fATMt, {NULL, NULL}},	// test command
	{"ATM?", fATMx, {NULL, NULL}},	// Help
	{"ATM2", fATM2, {NULL, NULL}},	// MP ext2 AT command
};

void at_mp_init(void)
{
	log_service_add_table(at_mp_items, sizeof(at_mp_items) / sizeof(at_mp_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_mp_init);
#endif

#endif // #if CONFIG_ATCMD_MP