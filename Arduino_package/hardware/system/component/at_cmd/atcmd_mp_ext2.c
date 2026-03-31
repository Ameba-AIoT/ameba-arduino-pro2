#include <platform_stdlib.h>
#include <platform_opts.h>
#include <platform_opts_bt.h>
#include <gpio_api.h>
#include "log_service.h"
#include "osdep_service.h"
#include "atcmd_mp.h"
#include "bt_intf.h"

#define MP_EXT2_PREFIX		"[ATM2]: "
#define MP_EXT2_PRINTF(...) \
		do{ \
			_AT_PRINTK(MP_EXT2_PREFIX); \
			_AT_PRINTK(__VA_ARGS__); \
		}while(0)

#define UART_BRIDGE_USAGE		"ATM2=bridge\n"
#define BT_POWER_USAGE			"ATM2=bt_power,ACT <ACT: on/off>\n"
#define GNT_BT_USAGE			"ATM2=gnt_bt,TARGET <TARGET: wifi/bt>\n"
#define SELECTION_BT_ANTENNA	"ATM2=ant,TARGET <TARGET: s0/s1>\n"

#if defined(CONFIG_BT) && CONFIG_BT
#if defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)
extern void console_reinit_uart(void);
#endif
#if defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_AMEBALITE)
extern void rtk_bt_mp_power_on(void);
extern void rtk_bt_mp_power_off(void);
extern void rtk_bt_set_ant(uint8_t ant_switch);
#else
extern bool bte_init(void);
extern void bte_deinit(void);
extern bool bt_trace_init(void);
extern bool bt_trace_deinit(void);
#endif
extern void wifi_btcoex_set_pta(pta_type_t  type);
extern void bt_uart_bridge_close(void);
extern void bt_uart_bridge_open(void);
static bool open_flag = 0;
#endif

static int mp_ext2_uart_bridge(void **argv, int argc)
{
#if defined(CONFIG_BT) && CONFIG_BT
	MP_EXT2_PRINTF("_AT_MP_BRIDGE_\n");
	if (argc == 1) {
		if (strncmp(argv[0], "close", 5) == 0) {
			MP_EXT2_PRINTF("close UART bridge.\n");
			if (open_flag == 0) {
				return 0;
			}

			bt_uart_bridge_close();
#if defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8735B)
			console_reinit_uart();
#endif
			open_flag = 0;
			return 0;
		}
	}
	MP_EXT2_PRINTF("open UART bridge.\n");
	bt_uart_bridge_open();
	open_flag = 1;
#else
	(void)argv;
	(void)argc;
#endif
	return 0;
}

static int mp_ext2_bt_power(void **argv, int argc)
{
	(void)argv;
	(void)argc;
#if defined(CONFIG_BT) && CONFIG_BT
	if (strcmp(argv[0], "on") == 0) {
		MP_EXT2_PRINTF("BT power on.\n\r");
		wifi_btcoex_set_pta(PTA_BT);
#if defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_AMEBALITE)
		rtk_bt_mp_power_on();
#else
		bt_trace_init();
		bte_init();
#endif
	} else if (strcmp(argv[0], "off") == 0) {
		MP_EXT2_PRINTF("BT power off.\n\r");
#if defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_AMEBALITE)
		rtk_bt_mp_power_off();
#else
		bte_deinit();
		bt_trace_deinit();
#endif
		wifi_btcoex_set_pta(PTA_WIFI);
	}
#endif
	return 0;
}

static int mp_ext2_gnt_bt(void **argv, int argc)
{
	(void)argc;
#if defined(CONFIG_BT) && CONFIG_BT
	if (strcmp(argv[0], "wifi") == 0) {
		MP_EXT2_PRINTF("Switch GNT_BT to WIFI.\n\r");
		wifi_btcoex_set_pta(PTA_WIFI);

	} else if (strcmp(argv[0], "bt") == 0) {
		MP_EXT2_PRINTF("Switch GNT_BT to BT.\n\r");
		wifi_btcoex_set_pta(PTA_BT);
	}
#else
	(void)argv;
#endif
	return 0;
}

static int mp_ext2_ant(void **argv, int argc)
{
	(void)argc;
#if defined(CONFIG_BT) && CONFIG_BT
	if (strcmp(argv[0], "s0") == 0) {
		MP_EXT2_PRINTF("BT use dedicated RF s0.\n\r");
#if defined(CONFIG_PLATFORM_AMEBAD2)
		rtk_bt_set_ant(0);
#endif
	} else if (strcmp(argv[0], "s1") == 0) {
		MP_EXT2_PRINTF("BT use share RF s1.\n\r");
#if defined(CONFIG_PLATFORM_AMEBAD2)
		rtk_bt_set_ant(1);
#endif
	}
#else
	(void)argv;
#endif
	return 0;
}

at_mp_ext_item_t at_mp_ext2_items[] = {
	{"bridge",		mp_ext2_uart_bridge,		UART_BRIDGE_USAGE},
	{"bt_power",	mp_ext2_bt_power,			BT_POWER_USAGE},
	{"gnt_bt",		mp_ext2_gnt_bt,				GNT_BT_USAGE},
	{"ant",			mp_ext2_ant,				SELECTION_BT_ANTENNA},
};

void fATM2(void *arg)
{
	int argc = 0, idx, cmd_cnt;
	char *argv[MAX_ARGC] = {0};

	cmd_cnt = sizeof(at_mp_ext2_items) / sizeof(at_mp_ext2_items[0]);
	argc = parse_param(arg, argv);
	if (argc == 1) {
		_AT_PRINTK("\n");
		MP_EXT2_PRINTF("Command usage :\n");
		for (idx = 0; idx < cmd_cnt; idx++) {
			_AT_PRINTK("%s", at_mp_ext2_items[idx].mp_ext_usage);
		}
	} else {
		for (idx = 0; idx < cmd_cnt; idx++) {
			if (strcmp(argv[1], at_mp_ext2_items[idx].mp_ext_cmd) == 0) {
				int (*fun)(void **argv, int argc) = at_mp_ext2_items[idx].mp_ext_fun;
				fun((void **)&argv[2], argc - 2);
				return;
			}
		}
		MP_EXT2_PRINTF("unknown command %s.\n", argv[1]);
	}
}

