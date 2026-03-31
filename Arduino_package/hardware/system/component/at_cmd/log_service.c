#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
#include "freertos_pmu.h"
#endif
#include "log_service.h"
#include "task.h"
#include "semphr.h"
#include "main.h"
#include "atcmd_wifi.h"
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
#include "atcmd_lwip.h"
#endif
#include "osdep_service.h"
//osdep_service.h include platform_autoconfig.h, it will undefine BT macro default
#if defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_8735B) || defined(CONFIG_PLATFORM_AMEBALITE)
#include <platform_opts_bt.h>
#endif

#if SUPPORT_LOG_SERVICE
//======================================================
struct list_head log_hash[ATC_INDEX_NUM];

extern void at_wifi_init(void);
extern void at_fs_init(void);
extern void at_sys_init(void);
extern void at_ethernet_init(void);
extern void at_google_init(void);
extern void at_transport_init(void);
//extern void at_app_init(void);
extern void at_mp_init(void);
#if	!defined(CONFIG_BT_MP_MODE)
extern void at_bt_init(void);
#endif
extern void at_qr_code_init(void);
extern void at_isp_init(void);
extern void at_ftl_init(void);
#ifdef CONFIG_ACURA
extern void at_acura_init(void);
#endif
#ifdef CONFIG_MP_INCLUDED
#ifdef CONFIG_AS_INIC_AP
extern void inic_ipc_mp_command(char *token, unsigned int cmd_len, int show_msg);
#else
extern int wext_private_command(const char *ifname, char *cmd, int show_msg);
#endif
#endif

void at_log_init(void);

char log_buf[LOG_SERVICE_BUFLEN];
xSemaphoreHandle log_rx_interrupt_sema = NULL;
#if CONFIG_LOG_SERVICE_LOCK
xSemaphoreHandle log_service_sema = NULL;
#endif

//#if defined (__ICCARM__)
//#pragma section=".data.log_init"
//
//unsigned int __log_init_begin__;
//unsigned int __log_init_end__;
//#elif defined ( __CC_ARM   ) || defined(__GNUC__)
#if defined (__ICCARM__) || defined ( __CC_ARM   ) || defined(__GNUC__)
//#pragma section=".data.log_init"
log_init_t *__log_init_begin__;
log_init_t *__log_init_end__;
log_init_t log_init_table[] = {

#if CONFIG_WLAN
	at_wifi_init,
#endif

#if	!defined(CONFIG_BT_MP_MODE)
#if defined(CONFIG_BT) && CONFIG_BT
	at_bt_init,
#endif
#endif

#if defined(CONFIG_ATCMD_MP) && CONFIG_ATCMD_MP
	at_mp_init,
#endif

#ifndef CONFIG_INIC_IPC_TODO

	//	at_fs_init,

#if (CONFIG_PLATFORM_AMEBA_X == 1)
	at_sys_init,
#endif
	at_log_init,
	//	at_app_init,
#if (CONFIG_ETHERNET == 1 && ETHERNET_INTERFACE == MII_INTERFACE)
	at_ethernet_init,
#endif

#if (defined(CONFIG_GOOGLE_NEST) && CONFIG_GOOGLE_NEST)
	at_google_init,
#endif

#if CONFIG_TRANSPORT
	at_transport_init,
#endif

#if defined(CONFIG_FTL) && CONFIG_FTL
	at_ftl_init,
#endif
#if defined(CONFIG_ISP) && CONFIG_ISP
	at_isp_init,
#endif
#if defined(CONFIG_ACURA) && CONFIG_ACURA
	at_acura_init,
#endif
#endif
};
#else
#error "not implement, add to linker script"
extern unsigned int __log_init_begin__;
extern unsigned int __log_init_end__;
#endif

#if defined(__GNUC__) || defined(CONFIG_PLATFORM_8710C)
#define USE_STRSEP
#ifdef CONFIG_STDLIB_TODO//AMEBAD2_TODO
#define _strsep strsep
#endif
#if defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)
#if defined(CONFIG_BUILD_NONSECURE)
#if !defined(__GNUC__)
#include "strproc.h"
#endif
#define _strsep strsep
#else
#undef USE_STRSEP
#endif
#endif
#endif

//======================================================
int hash_index(const char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str) {
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

void log_add_new_command(log_item_t *new)
{
	int index = hash_index(new->log_cmd) % ATC_INDEX_NUM;

	if (log_hash[index].prev == NULL && log_hash[index].next == NULL) {
		return;
	}

	list_add(&new->node, &log_hash[index]);
}
void start_log_service(void);
void log_service_init(void)
{
	unsigned int i;

//#if defined (__ICCARM__)
//	log_init_t *log_init_table;
//	__log_init_begin__ = (unsigned int)__section_begin(".data.log_init");
//	__log_init_end__ = (unsigned int)__section_end(".data.log_init");
//	log_init_table = (log_init_t *)__log_init_begin__;
//#elif defined(__CC_ARM) || defined(__GNUC__)
#if defined (__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
	__log_init_begin__ = log_init_table;
	__log_init_end__ = __log_init_begin__ + sizeof(log_init_table) / sizeof(log_init_t);
#else
#error "not implement"
#endif


	for (i = 0; i < ATC_INDEX_NUM; i++) {
		INIT_LIST_HEAD(&log_hash[i]);
	}

	for (i = 0; i < (unsigned int)(__log_init_end__ - __log_init_begin__); i++) {
		log_init_table[i]();
	}

	/* Initial uart rx swmaphore*/
	vSemaphoreCreateBinary(log_rx_interrupt_sema);
	xSemaphoreTake(log_rx_interrupt_sema, 1 / portTICK_RATE_MS);
#if CONFIG_LOG_SERVICE_LOCK
	log_service_lock_init();
#endif
	start_log_service();
}

//sizeof(log_items)/sizeof(log_items[0])
void log_service_add_table(log_item_t *tbl, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		log_add_new_command(&tbl[i]);
	}
}

void *log_action(char *cmd)
{
	int search_cnt = 0;
	int index = hash_index(cmd) % ATC_INDEX_NUM;
	struct list_head *head = &log_hash[index];
	struct list_head *iterator;
	log_item_t *item;
	void *act = NULL;

	list_for_each(iterator, head) {
		item = list_entry(iterator, log_item_t, node);
		search_cnt++;
		if (strcmp(item->log_cmd, cmd) == 0) {
			//printf("%s match %s, search cnt %d\n\r", cmd, item->log_cmd, search_cnt);
			act = (void *)item->at_act;
			break;
		}
	}

	return act;
}

void *log_handler(char *cmd)
{
	log_act_t action = NULL;
	char buf[LOG_SERVICE_BUFLEN];
	memset(buf, 0, LOG_SERVICE_BUFLEN);
	char *copy = buf;
	char *token = NULL;
	char *param = NULL;
	char tok[33] = {0};//'\0'
	strncpy(copy, cmd, LOG_SERVICE_BUFLEN - 1);

#if defined(USE_STRSEP)
	token = _strsep(&copy, "=");
	param = copy;
#else
	token = strtok(copy, "=");
	param = strtok(NULL, "\0");
#endif
	//if (token && (strlen(token) <= 4)) {
	if (token && (strlen(token) > 0)) {
		strncpy(tok, token, sizeof(tok) - 1);
	} else {
		//printf("\n\rAT Cmd format error!\n");
		return NULL;
	};
	//printf(" Command %s \n\r ", tok);
	//printf(" Param %s \n\r", param);
	action = (log_act_t)log_action(tok);

	if (action) {
		action(param);
	}
	return (void *)action;

}

int parse_param(char *buf, char **argv)
{

	int argc = 1;
	char str_buf[LOG_SERVICE_BUFLEN];
	memset(str_buf, 0, LOG_SERVICE_BUFLEN);
	int str_count = 0;
	int buf_cnt = 0;
	static char temp_buf[LOG_SERVICE_BUFLEN];
	char *buf_pos = temp_buf;
	memset(temp_buf, 0, sizeof(temp_buf));

	if (buf == NULL) {
		goto exit;
	}
	strncpy(temp_buf, buf, LOG_SERVICE_BUFLEN - 1);

	while ((argc < MAX_ARGC) && (*buf_pos != '\0')) {
		while ((*buf_pos == ',') || (*buf_pos == '[') || (*buf_pos == ']')) {
			if ((*buf_pos == ',') && (*(buf_pos + 1) == ',')) {
				argv[argc] = NULL;
				argc++;
			}
			*buf_pos = '\0';
			buf_pos++;
		}

		if (*buf_pos == '\0') {
			break;
		} else if (*buf_pos == '"') {
			memset(str_buf, '\0', LOG_SERVICE_BUFLEN);
			str_count = 0;
			buf_cnt = 0;
			*buf_pos = '\0';
			buf_pos ++;
			if (*buf_pos == '\0') {
				break;
			}
			argv[argc] = buf_pos;
			while ((*buf_pos != '"') && (*buf_pos != '\0')) {
				if (*buf_pos == '\\') {
					buf_pos ++;
					buf_cnt++;
				}
				str_buf[str_count] = *buf_pos;
				str_count++;
				buf_cnt++;
				buf_pos ++;
			}
			*buf_pos = '\0';
			memcpy(buf_pos - buf_cnt, str_buf, buf_cnt);
		} else {
			argv[argc] = buf_pos;
		}
		argc++;
		buf_pos++;

		while ((*buf_pos != ',') && (*buf_pos != '\0') && (*buf_pos != '[') && (*buf_pos != ']')) {
			buf_pos++;
		}
	}
exit:
	return argc;
}

unsigned char  gDbgLevel = AT_DBG_ERROR;
unsigned int   gDbgFlag  = 0xFFFFFFFF;
void at_set_debug_level(unsigned char newDbgLevel)
{
	gDbgLevel = newDbgLevel;
}

void at_set_debug_mask(unsigned int newDbgFlag)
{
	gDbgFlag = newDbgFlag;
}

#if CONFIG_WLAN
#ifndef WLAN0_NAME
#define WLAN0_NAME		"wlan0"
#endif
#ifndef WLAN1_NAME
#define WLAN1_NAME		"wlan1"
#endif

int mp_commnad_handler(char *cmd)
{
	char buf[64];
	char *token = NULL;
	memset(buf, 0, 64);

	//strncpy(buf, cmd, sizeof(buf));
	strncpy(buf, cmd, (64 - 1));
	token = strtok(buf, " ");
	if (token && (strcmp(buf, "iwpriv") == 0)) {
		token = strtok(NULL, "");
#ifdef CONFIG_MP_INCLUDED
#ifdef CONFIG_AS_INIC_AP
		inic_ipc_mp_command(token, sizeof(buf), 1);
#else
		wext_private_command(WLAN0_NAME, token, 1);
#endif
#endif
		return 0;
	}
	return -1;
}
#endif
void print_help_msg(void)
{
#if CONFIG_WLAN
	extern void print_wlan_help(void);
	print_wlan_help();
#endif
//add other help message print here
}

int print_help_handler(char *cmd)
{
	if (strcmp(cmd, "help") == 0) {
		print_help_msg();
		return 0;
	}
	return -1;
}

#if CONFIG_LOG_SERVICE_LOCK
void log_service_lock(void)
{
	rtw_down_sema((_sema *)(&log_service_sema));
}

u32 log_service_lock_timeout(u32 ms)
{
	return rtw_down_timeout_sema((_sema *)(&log_service_sema), ms);
}

void log_service_unlock(void)
{
	rtw_up_sema((_sema *)(&log_service_sema));
}

void log_service_lock_init(void)
{
	rtw_init_sema((_sema *)(&log_service_sema), 1);
}
#endif

#ifdef CONFIG_BT
#define LOG_SERVICE_SECURE_STACK_SIZE	( configMINIMAL_SECURE_STACK_SIZE + 320 )
#else
#define LOG_SERVICE_SECURE_STACK_SIZE	configMINIMAL_SECURE_STACK_SIZE
#endif

__weak char *log_get_buffer(void)
{
	while (xSemaphoreTake(log_rx_interrupt_sema, portMAX_DELAY) != pdTRUE);
	return log_buf;
}

void log_service(void *param)
{
	/* To avoid gcc warnings */
	(void) param;

	char *line_buf = NULL;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(LOG_SERVICE_SECURE_STACK_SIZE);
#endif
	_AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_INFO, "\n\rStart LOG SERVICE MODE\n\r");
	_AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_INFO, "\n\r# ");
	while (1) {
		//while (xSemaphoreTake(log_rx_interrupt_sema, portMAX_DELAY) != pdTRUE);
		line_buf = log_get_buffer();
#if CONFIG_LOG_SERVICE_LOCK
		log_service_lock();
#endif
		if (log_handler((char *)line_buf) == NULL) {
#if CONFIG_WLAN
			if (mp_commnad_handler((char *)line_buf) < 0)
#endif
			{
				if (print_help_handler((char *)line_buf) < 0) {
					at_printf("\r\nunknown command '%s'", line_buf);
				}
			}
		}
		line_buf[0] = '\0';

		_AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ALWAYS, "\n\r[MEM] After do cmd, available heap %d\n\r", xPortGetFreeHeapSize());
		_AT_DBG_MSG(AT_FLAG_COMMON, AT_DBG_ALWAYS, "\r\n\n#\r\n"); //"#" is needed for mp tool
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE)
		if (atcmd_lwip_is_tt_mode()) {
			at_printf(STR_END_OF_ATDATA_RET);
		} else {
			at_printf(STR_END_OF_ATCMD_RET);
		}
#endif
#if CONFIG_LOG_SERVICE_LOCK
		log_service_unlock();
#endif
#if defined(configUSE_WAKELOCK_PMU) && (configUSE_WAKELOCK_PMU == 1)
		pmu_release_wakelock(PMU_LOGUART_DEVICE);
#endif
	}
}

#define STACKSIZE               1280
void start_log_service(void)
{
	xTaskHandle CreatedTask;
	int result;

#if defined(CONFIG_USE_TCM_HEAP) && CONFIG_USE_TCM_HEAP
	/*********************************************************************
	 *
	 * ATCMD V2 supports commands for SSL
	 * It will cause problems while doing SSL operations if the stack is placed in TCM region
	 *
	 *********************************************************************/
	void *stack_addr = NULL;
#if (ATCMD_VER == ATVER_1) || ((ATCMD_VER == ATVER_2)&&(ATCMD_SUPPORT_SSL == 0))
	extern void *tcm_heap_malloc(int size);
	stack_addr = tcm_heap_malloc(STACKSIZE * sizeof(int));

	if (stack_addr == NULL) {
	}
#endif

	result = xTaskGenericCreate(
				 log_service,
				 (signed portCHAR *) "log_service",
				 STACKSIZE,
				 NULL,
				 tskIDLE_PRIORITY + 5,
				 &CreatedTask,
				 stack_addr,
				 NULL);
#else
	result = xTaskCreate(log_service, (const portCHAR *) "log_service", STACKSIZE, NULL, tskIDLE_PRIORITY + 5, &CreatedTask);
#endif

	if (result != pdPASS) {
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
	}

}

void fAT_exit(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	printf("\n\rLeave LOG SERVICE");
	vTaskDelete(NULL);
}
log_item_t at_log_items[ ] = {
	{"AT--", fAT_exit, {NULL, NULL}},
	{"ATxx", fAT_exit, {NULL, NULL}}
};
void at_log_init(void)
{
	log_service_add_table(at_log_items, sizeof(at_log_items) / sizeof(at_log_items[0]));
}
log_module_init(at_log_init);
#endif
