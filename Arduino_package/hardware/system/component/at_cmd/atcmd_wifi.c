#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "osdep_service.h"
#include "log_service.h"
#include "atcmd_wifi.h"
#if CONFIG_LWIP_LAYER
#include <lwip_netconf.h>
#include <dhcp/dhcps.h>
#endif
#if CONFIG_WLAN
#include <wifi_conf.h>
#include <wifi_conf_inter.h>
#ifdef CONFIG_RTK_MESH
#include <drv_types.h>
#include <rtw_security.h>
#endif

#endif

#if ATCMD_VER == ATVER_2
#include "flash_api.h"
#include "device_lock.h"
#include <wifi_fast_connect.h>
#endif

#ifdef WIFI_PERFORMANCE_MONITOR
#include "wifi_performance_monitor.h"
#endif

#include "platform_opts.h"

#if defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_8735B) || defined(CONFIG_PLATFORM_AMEBALITE)
#include "platform_opts_bt.h"
#endif
extern int rltk_set_pmf(unsigned char mode);
/******************************************************************************/
#define	_AT_WLAN_SET_SSID_          "ATW0"
#define	_AT_WLAN_SET_PASSPHRASE_    "ATW1"
#define	_AT_WLAN_SET_KEY_ID_        "ATW2"
#define	_AT_WLAN_AP_SET_SSID_       "ATW3"
#define	_AT_WLAN_AP_SET_SEC_KEY_    "ATW4"
#define	_AT_WLAN_AP_SET_CHANNEL_    "ATW5"
#define _AT_WLAN_SET_BSSID_         "ATW6"
#define _AT_WLAN_SET_WPA_MODE_      "ATW8"
#define	_AT_WLAN_AP_ACTIVATE_       "ATWA"
#define _AT_WLAN_AP_STA_ACTIVATE_   "ATWB"
#define	_AT_WLAN_JOIN_NET_          "ATWC"
#define	_AT_WLAN_DISC_NET_          "ATWD"
#define	_AT_WLAN_DATE_RATE_         "ATWd"
#define	_AT_WLAN_WEB_SERVER_        "ATWE"
#define _AT_WLAN_P2P_FIND_          "ATWF"
#define _AT_WLAN_P2P_START_         "ATWG"
#define _AT_WLAN_P2P_STOP_          "ATWH"
#define _AT_WLAN_PING_TEST_         "ATWI"
#define _AT_WLAN_P2P_CONNECT_       "ATWJ"
#define _AT_WLAN_P2P_DISCONNECT_    "ATWK"
#define _AT_WLAN_SSL_CLIENT_        "ATWL"
#define _AT_WLAN_PROMISC_           "ATWM"
#define _AT_WLAN_P2P_INFO_          "ATWN"
#define _AT_WLAN_OTA_UPDATE_        "ATWO"
#define	_AT_WLAN_POWER_             "ATWP"
#define	_AT_WLAN_SIMPLE_CONFIG_     "ATWQ"
#define	_AT_WLAN_GET_RSSI_          "ATWR"
#define	_AT_WLAN_GET_BEACON_RSSI_   "ATWr"
#define	_AT_WLAN_SCAN_              "ATWS"
#define _AT_WLAN_SCAN_WITH_SSID_    "ATWs"
#define _AT_WLAN_TCP_TEST_          "ATWT"
#define _AT_WLAN_UDP_TEST_          "ATWU"
#define _AT_WLAN_WPS_               "ATWW"
#define _AT_WLAN_AP_WPS_            "ATWw"
#define _AT_WLAN_AIRKISS_           "ATWX"
#define _AT_WLAN_SET_MESH_GROUP_    "ATGP"
#define _AT_WLAN_IWPRIV_            "ATWZ"
#define	_AT_WLAN_INFO_              "ATW?"
#define	_AT_WLAN_FLUSH_CONNCTION_INFO_     "ATWf"

#define	_AT_WLAN_EXTEND_POWER_MODE_        "ATXP"

#ifndef CONFIG_SSL_CLIENT
#define CONFIG_SSL_CLIENT       0
#endif
#ifndef CONFIG_OTA_UPDATE
#define CONFIG_OTA_UPDATE       0
#endif
#ifndef CONFIG_BSD_TCP
#define CONFIG_BSD_TCP	        1
#endif
#ifndef CONFIG_ENABLE_P2P
#define CONFIG_ENABLE_P2P		0
#endif
#define SCAN_WITH_SSID		0

#if ATCMD_VER == ATVER_2
extern int SwithToUtf_8(const unsigned char *pszBufIn, int nBufInLen, unsigned char *pszBufOut, int *pnBufOutLen);
extern int SwitchToGbk(const unsigned char *pszBufIn, int nBufInLen, unsigned char *pszBufOut, int *pnBufOutLen);
extern int is_str_utf8(const char *str);
#endif


#if WIFI_LOGO_CERTIFICATION_CONFIG == 0
#define IPERF_OLD_EN 1
#else
#define IPERF_OLD_EN 0
#endif

#if CONFIG_LWIP_LAYER
#if IPERF_OLD_EN
extern void cmd_tcp(int argc, char **argv);
extern void cmd_udp(int argc, char **argv);
#else
extern void cmd_iperf(int argc, char **argv);
#endif

extern void cmd_ping(int argc, char **argv);
extern void cmd_ssl_client(int argc, char **argv);
#endif

#if CONFIG_WLAN
extern void cmd_promisc(int argc, char **argv);
extern void cmd_update(int argc, char **argv);
extern void cmd_simple_config(int argc, char **argv);
#if defined(CONFIG_INCLUDE_DPP_CONFIG) && CONFIG_INCLUDE_DPP_CONFIG
extern void cmd_dpp(int argc, char **argv);
#endif
#if CONFIG_ENABLE_WPS
extern void cmd_wps(int argc, char **argv);
#endif

#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
extern void cmd_ap_wps(int argc, char **argv);
extern int wpas_wps_dev_config(u8 *dev_addr, u8 bregistrar);
#endif
#if CONFIG_ENABLE_P2P
extern void cmd_wifi_p2p_start(int argc, char **argv);
extern void cmd_wifi_p2p_stop(int argc, char **argv);
extern void cmd_p2p_listen(int argc, char **argv);
extern void cmd_p2p_find(int argc, char **argv);
extern void cmd_p2p_peers(int argc, char **argv);
extern void cmd_p2p_info(int argc, char **argv);
extern void cmd_p2p_disconnect(int argc, char **argv);
extern void cmd_p2p_connect(int argc, char **argv);
extern int cmd_wifi_p2p_auto_go_start(int argc, char **argv);
#endif //CONFIG_ENABLE_P2P
#if CONFIG_AIRKISS
extern int airkiss_start(rtw_network_info_t *);
extern int airkiss_stop(void);
#endif
#ifdef CONFIG_AS_INIC_AP
extern int inic_ipc_iwpriv_command(char *cmd, unsigned int cmd_len, int show_msg);
#endif
#if CONFIG_LWIP_LAYER
extern struct netif xnetif[NET_IF_NUM];
#endif

#define JOIN_CONNECTING             (uint32_t)(1 << 10)

/* fastconnect use wifi AT command. Not init_wifi_struct when log service disabled
 * static initialize all values for using fastconnect when log service disabled
 */
static rtw_network_info_t wifi = {0};

static rtw_softap_info_t ap = {0};
static unsigned char password[RTW_MAX_PSK_LEN + 1] = {0};
#ifdef CONFIG_FPGA
int security = -1;
#endif

struct static_ip_config user_static_ip;
#if ATCMD_VER == ATVER_2
unsigned char sta_ip[4] = {192, 168, 1, 80}, sta_netmask[4] = {255, 255, 255, 0}, sta_gw[4] = {192, 168, 1, 1};
#endif

#if ATCMD_VER == ATVER_2
unsigned char dhcp_mode_sta = 1, dhcp_mode_ap = 1;
unsigned char  ap_ip[4] = {192, 168, 43, 1},  ap_netmask[4] = {255, 255, 255, 0},  ap_gw[4] = {192, 168, 43, 1};
static void atcmd_wifi_disconn_hdl(char *buf, int buf_len, int flags, void *userdata);
#endif

rtw_mode_t wifi_mode = RTW_MODE_STA;

#if ATCMD_VER == ATVER_2
rtw_mode_t wifi_mode_new = RTW_MODE_STA;
#endif

static void init_wifi_struct(void)
{
	memset(wifi.ssid.val, 0, sizeof(wifi.ssid.val));
	memset(wifi.bssid.octet, 0, ETH_ALEN);
	memset(password, 0, sizeof(password));
	wifi.ssid.len = 0;
	wifi.password = NULL;
	wifi.password_len = 0;
	wifi.key_id = -1;
	wifi.channel = 0;
	wifi.pscan_option = 0;
	wifi.joinstatus_user_callback = NULL;
	memset(ap.ssid.val, 0, sizeof(ap.ssid.val));
	ap.ssid.len = 0;
	ap.password = NULL;
	ap.password_len = 0;
	ap.channel = 1;
	ap.hidden_ssid = 0;
#ifdef CONFIG_FPGA
	security = -1;
#endif
}

static void print_scan_result(rtw_scan_result_t *record)
{
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
	at_printf("%s,%d,%s,%d,"MAC_FMT"", record->SSID.val, record->channel,
			  (record->security == RTW_SECURITY_OPEN) ? "Open" :
			  (record->security == RTW_SECURITY_WEP_PSK) ? "WEP" :
			  (record->security == RTW_SECURITY_WPA_TKIP_PSK) ? "WPA TKIP" :
			  (record->security == RTW_SECURITY_WPA_AES_PSK) ? "WPA AES" :
			  (record->security == RTW_SECURITY_WPA_MIXED_PSK) ? "WPA Mixed" :
			  (record->security == RTW_SECURITY_WPA2_AES_PSK) ? "WPA2 AES" :
			  (record->security == RTW_SECURITY_WPA2_TKIP_PSK) ? "WPA2 TKIP" :
			  (record->security == RTW_SECURITY_WPA2_MIXED_PSK) ? "WPA2 Mixed" :
			  (record->security == RTW_SECURITY_WPA_WPA2_TKIP_PSK) ? "WPA/WPA2 TKIP" :
			  (record->security == RTW_SECURITY_WPA_WPA2_AES_PSK) ? "WPA/WPA2 AES" :
			  (record->security == RTW_SECURITY_WPA_WPA2_MIXED_PSK) ? "WPA/WPA2 Mixed" :
			  (record->security == RTW_SECURITY_WPA2_ENTERPRISE) ? "WPA2 Enterprise" :
			  (record->security == RTW_SECURITY_WPA_WPA2_ENTERPRISE) ? "WPA/WPA2 Enterprise" :
#ifdef CONFIG_SAE_SUPPORT
			  (record->security == RTW_SECURITY_WPA3_AES_PSK) ? "WPA3-SAE AES" :
			  (record->security == RTW_SECURITY_WPA3_GCMP_PSK) ? "WPA3-SAE GCMP AES" :
			  (record->security == RTW_SECURITY_WPA2_WPA3_MIXED) ? "WPA2/WPA3-SAE AES" :
#endif
			  "Unknown",
			  record->signal_strength, MAC_ARG(record->BSSID.octet));
#else
	RTW_API_INFO("%s\t ", (record->bss_type == RTW_BSS_TYPE_ADHOC) ? "Adhoc" : "Infra");
	RTW_API_INFO(MAC_FMT, MAC_ARG(record->BSSID.octet));
	RTW_API_INFO(" %d\t ", record->signal_strength);
	RTW_API_INFO(" %d\t  ", record->channel);
	RTW_API_INFO(" %d\t  ", (unsigned int)record->wps_type);
	RTW_API_INFO("%s\t\t ", (record->security == RTW_SECURITY_OPEN) ? "Open" :
				 (record->security == RTW_SECURITY_WEP_PSK) ? "WEP" :
				 (record->security == RTW_SECURITY_WPA_TKIP_PSK) ? "WPA TKIP" :
				 (record->security == RTW_SECURITY_WPA_AES_PSK) ? "WPA AES" :
				 (record->security == RTW_SECURITY_WPA_MIXED_PSK) ? "WPA Mixed" :
				 (record->security == RTW_SECURITY_WPA2_AES_PSK) ? "WPA2 AES" :
				 (record->security == RTW_SECURITY_WPA2_TKIP_PSK) ? "WPA2 TKIP" :
				 (record->security == RTW_SECURITY_WPA2_MIXED_PSK) ? "WPA2 Mixed" :
				 (record->security == RTW_SECURITY_WPA_WPA2_TKIP_PSK) ? "WPA/WPA2 TKIP" :
				 (record->security == RTW_SECURITY_WPA_WPA2_AES_PSK) ? "WPA/WPA2 AES" :
				 (record->security == RTW_SECURITY_WPA_WPA2_MIXED_PSK) ? "WPA/WPA2 Mixed" :
				 (record->security == RTW_SECURITY_WPA2_ENTERPRISE) ? "WPA2 Enterprise" :
				 (record->security == RTW_SECURITY_WPA_WPA2_ENTERPRISE) ? "WPA/WPA2 Enterprise" :
#ifdef CONFIG_SAE_SUPPORT
				 (record->security == RTW_SECURITY_WPA3_AES_PSK) ? "WPA3-SAE AES" :
				 (record->security == RTW_SECURITY_WPA3_GCMP_PSK) ? "WPA3-SAE GCMP" :
				 (record->security == RTW_SECURITY_WPA2_WPA3_MIXED) ? "WPA2/WPA3-SAE AES" :
#endif
				 "Unknown");

	RTW_API_INFO(" %s ", record->SSID.val);
	RTW_API_INFO("\r\n");
#endif
}

static rtw_result_t app_scan_result_handler(unsigned int scanned_AP_num, void *user_data)
{
	/* To avoid gcc warnings */
	(void) user_data;

	rtw_scan_result_t *scanned_AP_info;
	char *scan_buf = NULL;
	unsigned int i = 0;

	if (scanned_AP_num == 0) {/* scanned no AP*/
		return RTW_ERROR;
	}

	scan_buf = (char *)rtw_zmalloc(scanned_AP_num * sizeof(rtw_scan_result_t));
	if (scan_buf == NULL) {
		return RTW_ERROR;
	}

	if (wifi_get_scan_records(&scanned_AP_num, scan_buf) < 0) {
		rtw_mfree((u8 *)scan_buf, 0);
		return RTW_ERROR;
	}

	for (i = 0; i < scanned_AP_num; i++) {
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("\r\nAP : %d,", (i + 1));
#else
		RTW_API_INFO("%d\t ", (i + 1));
#endif
		scanned_AP_info = (rtw_scan_result_t *)(scan_buf + i * sizeof(rtw_scan_result_t));
		scanned_AP_info->SSID.val[scanned_AP_info->SSID.len] = 0; /* Ensure the SSID is null terminated */

#if ATCMD_VER == ATVER_2
		if (is_str_utf8(scanned_AP_info->SSID.val)) {
			unsigned char GBKbuf[33];
			int GBKbuflen = 0;
			memset(&GBKbuf[0], 0x00, 33);
			SwitchToGbk(scanned_AP_info->SSID.val, scanned_AP_info->SSID.len, (unsigned char *)&GBKbuf, &GBKbuflen);
			strcpy((char *)scanned_AP_info->SSID.val, (char *)GBKbuf);
			scanned_AP_info->SSID.len = strlen((char *)GBKbuf);
		}
#endif
		print_scan_result(scanned_AP_info);
	}
	rtw_mfree((u8 *)scan_buf, 0);

#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
	at_printf("\r\n[ATWS] OK");
	at_printf(STR_END_OF_ATCMD_RET);
#endif
	return RTW_SUCCESS;
}

static void print_wifi_setting(const char *ifname, rtw_wifi_setting_t *pSetting)
{
#ifndef CONFIG_INIC_NO_FLASH

	RTW_API_INFO("\n\r\nWIFI  %s Setting:", ifname);
	RTW_API_INFO("\n\r==============================");

	switch (pSetting->mode) {
	case RTW_MODE_AP:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("\r\nAP,");
#endif
		RTW_API_INFO("\n\r      MODE => AP");
		break;
	case RTW_MODE_STA:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("\r\nSTA,");
#endif
		RTW_API_INFO("\n\r      MODE => STATION");
		break;
	default:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("\r\nUNKNOWN,");
#endif
		RTW_API_INFO("\n\r      MODE => UNKNOWN");
	}
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
	at_printf("%s,%d,", pSetting->ssid, pSetting->channel);
#endif
	RTW_API_INFO("\n\r      SSID => %s", pSetting->ssid);
	RTW_API_INFO("\n\r   CHANNEL => %d", pSetting->channel);

	switch (pSetting->security_type) {
	case RTW_SECURITY_OPEN:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("OPEN,");
#endif
		RTW_API_INFO("\n\r  SECURITY => OPEN");
		break;
	case RTW_SECURITY_WEP_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WEP,%d,", pSetting->key_idx);
#endif
		RTW_API_INFO("\n\r  SECURITY => WEP");
		RTW_API_INFO("\n\r KEY INDEX => %d", pSetting->key_idx);
		break;
	case RTW_SECURITY_WPA_TKIP_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA TKIP,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA TKIP");
		break;
	case RTW_SECURITY_WPA2_TKIP_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA2 TKIP,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA2 TKIP");
		break;
	case RTW_SECURITY_WPA_AES_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA AES,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA AES");
		break;
	case RTW_SECURITY_WPA_MIXED_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA MIX,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA Mixed");
		break;
	case RTW_SECURITY_WPA2_AES_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA2 AES,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA2 AES");
		break;
	case RTW_SECURITY_WPA2_MIXED_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA2 Mixd,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA2 Mixed");
		break;
	case RTW_SECURITY_WPA_WPA2_TKIP_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA/WPA2 TKIP,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA/WPA2 TKIP");
		break;
	case RTW_SECURITY_WPA_WPA2_AES_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA/WPA2 AES,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA/WPA2 AES");
		break;
	case RTW_SECURITY_WPA_WPA2_MIXED_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA/WPA2 Mixd,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA/WPA2 Mixed");
		break;
	case RTW_SECURITY_WPA3_AES_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA3 SAE AES,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA3 SAE AES");
		break;
	case RTW_SECURITY_WPA3_GCMP_PSK:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA3 GCMP,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA3 GCMP");
		break;
	case RTW_SECURITY_WPA2_WPA3_MIXED:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("WPA2/WPA3 AES,");
#endif
		RTW_API_INFO("\n\r  SECURITY => WPA2/WPA3 AES");
		break;
	default:
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
		at_printf("UNKNOWN,");
#endif
		RTW_API_INFO("\n\r  SECURITY => UNKNOWN");
	}

#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
	at_printf("%s,", pSetting->password);
#endif
	RTW_API_INFO("\n\r  PASSWORD => %s", pSetting->password);
	RTW_API_INFO("\n\r");
#endif
}

void fATWD(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	int timeout = 20;
	volatile int ret = RTW_SUCCESS;
	rtw_wifi_setting_t wifi_setting = {0};
#if ATCMD_VER == ATVER_2
	int error_no = 0;
#endif

	printf("[ATWD]: _AT_WLAN_DISC_NET_\n\r");
	printf("\n\rDeassociating AP ...");

	if (wifi_get_setting(WLAN0_IDX, &wifi_setting) >= 0) {
		if (wifi_setting.mode == RTW_MODE_AP) {
			printf("\n\rcurrently in softap mode, no need disconnect");
			goto exit_success;
		}
	} else {
		printf("\n\rnetif is down, no need disconnect");
		goto exit_success;
	}

	if (wifi_is_connected_to_ap() != RTW_SUCCESS) {
		printf("\n\rnot connected yet");
		goto exit_success;
	}
#if ATCMD_VER == ATVER_2
	wifi_unreg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl);
#endif
	if ((ret = wifi_disconnect()) < 0) {
		printf("\n\rERROR: Operation failed!");
#if ATCMD_VER == ATVER_2
		error_no = 3;
#endif
		goto exit;
	}

	while (1) {
		if (wifi_is_connected_to_ap() != RTW_SUCCESS) {
			printf("\n\rWIFI disconnect succeed");
			break;
		}

		if (timeout == 0) {
			printf("\n\rERROR: Deassoc timeout!");
			ret = RTW_TIMEOUT;
#if ATCMD_VER == ATVER_2
			error_no = 4;
#endif
			break;
		}

		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}
	printf("\n\r");

#if CONFIG_LWIP_LAYER
	user_static_ip.use_static_ip = 0;
	LwIP_ReleaseIP(WLAN0_IDX);
#endif
exit:
	init_wifi_struct();
#if ATCMD_VER == ATVER_2
	if (error_no == 0) {
		at_printf("\r\n[ATWD] OK");
	} else {
		at_printf("\r\n[ATWD] ERROR:%d", error_no);
	}
#endif
	return;
exit_success:
	init_wifi_struct();
#if ATCMD_VER == ATVER_2
	at_printf("\r\n[ATWD] OK");
#endif
	return;
}

#if defined(CONFIG_INCLUDE_SIMPLE_CONFIG) && CONFIG_INCLUDE_SIMPLE_CONFIG
void fATWQ(void *arg)
{
	int argc = 0;
	char *argv[2] = {0};
	printf("[ATWQ]: _AT_WLAN_SIMPLE_CONFIG_\n\r");
	argv[argc++] = "wifi_simple_config";
	if (arg) {
		argv[argc++] = arg;
	}
#if ATCMD_VER == ATVER_2
	wifi_unreg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl);
#endif
	cmd_simple_config(argc, argv);
}
#endif

#if defined(CONFIG_INCLUDE_DPP_CONFIG) && CONFIG_INCLUDE_DPP_CONFIG
void fATWq(void *arg)
{
	int argc;
	char *argv[MAX_ARGC] = {0};

	char buf[256] = {0};
	printf("[ATWq]:\n\r");
	if (arg) {
		strncpy(buf, arg, sizeof(buf));
		argc = parse_param(buf, argv);
	}
	cmd_dpp(argc, argv);
}
#endif

void fATWS(void *arg)
{
	char buf[33] = {0};
	u8 *channel_list = NULL;
	int num_channel = 0;
	int i, argc = 0;
	char *argv[MAX_ARGC] = {0};
	volatile int ret = RTW_SUCCESS;
	rtw_scan_param_t scan_param = {0};
	rtw_join_status_t join_status = 0;
#if ATCMD_VER == ATVER_2
	int error_no = 0;
#endif
	printf("[ATWS]: _AT_WLAN_SCAN_\n\r");

	join_status = wifi_get_join_status();
	if ((join_status > RTW_JOINSTATUS_UNKNOWN) && (join_status < RTW_JOINSTATUS_SUCCESS)) {
#if ATCMD_VER == ATVER_2
		error_no = 6;
#endif
		goto exit;
	}
	if (arg) {
		strncpy(buf, arg, sizeof(buf) - 1);
		argc = parse_param(buf, argv);
		if (argc < 2) {
			ret = RTW_BADARG;
#if ATCMD_VER == ATVER_2
			error_no = 1;
#endif
			goto exit;
		}
		num_channel = atoi(argv[1]);
		channel_list = (u8 *)malloc(num_channel);
		if (!channel_list) {
			printf("[ATWS]ERROR: Can't malloc memory for channel list\n\r");
			ret = RTW_BUFFER_UNAVAILABLE_TEMPORARY;
#if ATCMD_VER == ATVER_2
			error_no = 2;
#endif
			goto exit;
		}
		//parse command channel list
		for (i = 2; i <= argc - 1 ; i++) {
			*(channel_list + i - 2) = (u8)atoi(argv[i]);
		}
		scan_param.channel_list = channel_list;
		scan_param.channel_list_num = num_channel;
	}

	scan_param.scan_user_callback = app_scan_result_handler;
	if ((ret = wifi_scan_networks(&scan_param, 0)) != RTW_SUCCESS) {
		printf("[ATWS]ERROR: wifi scan failed\n\r");
#if ATCMD_VER == ATVER_2
		error_no = 5;
#endif
		goto exit;
	}
exit:
#if ATCMD_VER == ATVER_2
	if (error_no) {
		at_printf("\r\n[ATWS] ERROR:%d", error_no);
	}
#endif
	if (arg && channel_list) {
		free(channel_list);
	}
}

#ifdef WIFI_PERFORMANCE_MONITOR
/**
  * @brief print the time of WIFI TRx path.
  * @param  arg: the command "ATWm"
  * @retval None
  */
void fATWm(void *arg)
{
	wifi_performance_print();
}
#endif

void fATWx(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	int i = 0;
#if CONFIG_LWIP_LAYER
	u8 *mac = LwIP_GetMAC(0);
	u8 connection_ap_mac[6];
	u8 *ip = LwIP_GetIP(0);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6
	u8 *ipv6_0 = LwIP_GetIPv6_linklocal(&xnetif[0]);
#if LWIP_IPV6_DHCP6
	u8 *ipv6_1 = LwIP_GetIPv6_global(&xnetif[0]);
#endif
#endif
#endif
	u8 *gw = LwIP_GetGW(0);
	u8 *msk = LwIP_GetMASK(0);
#endif
	u8 *ifname[2] = {(u8 *)WLAN0_NAME, (u8 *)WLAN1_NAME};
	rtw_wifi_setting_t setting;
	rtw_sw_statistics_t stats;
#ifdef CONFIG_RTK_MESH
	int path_tbl_no;
	struct path_sel_entry Entry;
#endif

	printf("[ATW?]: _AT_WLAN_INFO_\n\r");
	for (i = 0; i < NET_IF_NUM; i++) {
		if (wifi_is_running(i)) {
#if CONFIG_LWIP_LAYER
			mac = LwIP_GetMAC(i);
			ip = LwIP_GetIP(i);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6
			ipv6_0 = LwIP_GetIPv6_linklocal(&xnetif[i]);
#if LWIP_IPV6_DHCP6
			ipv6_1 = LwIP_GetIPv6_global(&xnetif[i]);
#endif
#endif
#endif
			gw = LwIP_GetGW(i);
			msk = LwIP_GetMASK(i);
#endif
			printf("\n\r\nWIFI %s Status: Running",  ifname[i]);
			printf("\n\r==============================");

			wifi_get_sw_statistic(i, &stats);
			printf("\ntx stat: tx_packets=%d, tx_dropped=%d, tx_bytes=%d\n", (unsigned int)stats.tx_packets, (unsigned int)stats.tx_dropped, (unsigned int)stats.tx_bytes);
			printf("rx stat: rx_packets=%d, rx_dropped=%d, rx_bytes=%d, rx_overflow=%d\n", (unsigned int)stats.rx_packets, (unsigned int)stats.rx_dropped,
				   (unsigned int)stats.rx_bytes, (unsigned int)stats.rx_overflow);
			if (i == 0) {
				printf("max_skbbuf_used_num=%d, skbbuf_used_num=%d\n", stats.max_skbbuf_used_number, stats.skbbuf_used_number);
				printf("max_skbdata_used_num=%d, skbdata_used_num=%d\n", stats.max_skbdata_used_number, stats.skbdata_used_number);
			}
			wifi_get_setting(i, &setting);
			print_wifi_setting((const char *)ifname[i], &setting);

#if CONFIG_LWIP_LAYER
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
			at_printf("%02x:%02x:%02x:%02x:%02x:%02x,", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]) ;
			at_printf("%d.%d.%d.%d,", ip[0], ip[1], ip[2], ip[3]);
			at_printf("%d.%d.%d.%d", gw[0], gw[1], gw[2], gw[3]);
#endif
			printf("\n\rInterface (%s)", ifname[i]);
			printf("\n\r==============================");
			printf("\n\r\tMAC => %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]) ;
			printf("\n\r\tIP  => %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6
			printf("\n\r\tLink-local IPV6 => %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
				   ipv6_0[0], ipv6_0[1],  ipv6_0[2],  ipv6_0[3],  ipv6_0[4],  ipv6_0[5],  ipv6_0[6], ipv6_0[7],
				   ipv6_0[8], ipv6_0[9], ipv6_0[10], ipv6_0[11], ipv6_0[12], ipv6_0[13], ipv6_0[14], ipv6_0[15]);
#if LWIP_IPV6_DHCP6
			printf("\n\r\tIPV6            => %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
				   ipv6_1[0], ipv6_1[1],  ipv6_1[2],  ipv6_1[3],  ipv6_1[4],  ipv6_1[5],  ipv6_1[6], ipv6_1[7],
				   ipv6_1[8], ipv6_1[9], ipv6_1[10], ipv6_1[11], ipv6_1[12], ipv6_1[13], ipv6_1[14], ipv6_1[15]);
#endif
#endif
#endif
			printf("\n\r\tGW  => %d.%d.%d.%d", gw[0], gw[1], gw[2], gw[3]);
			printf("\n\r\tmsk  => %d.%d.%d.%d", msk[0], msk[1], msk[2], msk[3]);
			u8 connection_ap_mac[6];
			if (rtw_wx_get_wap(0, connection_ap_mac) == 0) {
				if (setting.mode == RTW_MODE_STA) {
					printf("\n\r\tBSSID => %02x:%02x:%02x:%02x:%02x:%02x\n\r", connection_ap_mac[0], connection_ap_mac[1], connection_ap_mac[2], connection_ap_mac[3],
						   connection_ap_mac[4], connection_ap_mac[5]);
				}
			}
#endif
			if (setting.mode == RTW_MODE_AP || i == 1) {
				int client_number;
				struct {
					int    count;
					rtw_mac_t mac_list[AP_STA_NUM];
				} client_info;

				client_info.count = AP_STA_NUM;
				wifi_get_associated_client_list(&client_info, sizeof(client_info));

				printf("\n\rAssociated Client List:");
				printf("\n\r==============================");

				if (client_info.count == 0) {
					printf("\n\rClient Num: %d\n\r", client_info.count);
				} else {
					printf("\n\rClient Num: %d", client_info.count);
					for (client_number = 0; client_number < client_info.count; client_number++) {
						printf("\n\rClient %d:", client_number + 1);
						printf("\n\r\tMAC => "MAC_FMT"",
							   MAC_ARG(client_info.mac_list[client_number].octet));
#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
						at_printf("\r\nCLIENT : %d,"MAC_FMT"", client_number + 1, MAC_ARG(client_info.mac_list[client_number].octet));
#endif
#ifdef CONFIG_RTK_MESH
						if (query_table(client_info.mac_list[client_number].octet, &Entry) == 1) {
							printf("\n\r\tPATH table => NEXT HOP:"MAC_FMT"\tSN:%d\tMETRIC:%d\t", MAC_ARG(Entry.nexthopMAC), Entry.sn, Entry.metric);
						}

#endif

					}
					printf("\n\r");
				}
#ifdef CONFIG_RTK_MESH
				printf("\n\rPATH table");
				if (query_whole_table(&path_tbl_no) == 1) {
					printf("\n\rThere are total %d PATH table", path_tbl_no);
				}
#endif
			}
		}
// show the ethernet interface info
		else {
#if CONFIG_ETHERNET
			if (i == NET_IF_NUM - 1) {
#if CONFIG_LWIP_LAYER
				mac = LwIP_GetMAC(i);
				ip = LwIP_GetIP(i);
				gw = LwIP_GetGW(i);
				printf("\n\rInterface ethernet\n");
				printf("\n\r==============================");
				printf("\n\r\tMAC => %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]) ;
				printf("\n\r\tIP  => %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
				printf("\n\r\tGW  => %d.%d.%d.%d\n\r", gw[0], gw[1], gw[2], gw[3]);
#endif // end CONFIG_LWIP_LAYER
			}
#endif // end CONFIG_ETHERNET
		}
	}

#if defined(configUSE_TRACE_FACILITY) && (configUSE_TRACE_FACILITY == 1) && (configUSE_STATS_FORMATTING_FUNCTIONS == 1)
	{
		int buf_len = uxTaskGetNumberOfTasks() * 32;
		char *pcWriteBuffer = NULL;
		if (buf_len < 1024) {
			buf_len = 1024;
		}
		pcWriteBuffer = (char *)rtw_zmalloc(buf_len);
		if (pcWriteBuffer == NULL) {
			printf("malloc pcWriteBuffer for ATW? fail\n");
			return;
		}
		vTaskList((char *)pcWriteBuffer);
		printf("\n\rTask List: \n\r%s", pcWriteBuffer);

		if (pcWriteBuffer) {
			rtw_mfree((u8 *)pcWriteBuffer, 0);
		}
	}
#endif

#if (defined(SUPPORT_UART_LOG_SERVICE) && SUPPORT_UART_LOG_SERVICE) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
	at_printf("\r\n[ATW?] OK");
#endif

}

#if ATCMD_VER == ATVER_1
void fATW0(void *arg)
{
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW0]Usage: ATW0=SSID(Maximum length is 32)\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	if (strlen((char *)arg) > 32) {
		printf("[ATW0]Error: SSID length can't exceed 32\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	printf("[ATW0]: _AT_WLAN_SET_SSID_ [%s]\n\r", (char *)arg);
	strncpy((char *)wifi.ssid.val, (char *)arg, sizeof(wifi.ssid.val) - 1);
	wifi.ssid.len = strlen((char *)arg);
exit:
	return;
}

void fATW1(void *arg)
{
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW1]Usage: ATW1=PASSPHRASE\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	printf("[ATW1]: _AT_WLAN_SET_PASSPHRASE_ [%s]\n\r", (char *)arg);

	strncpy((char *)password, (char *)arg, sizeof(password) - 1);
	wifi.password = password;
	wifi.password_len = strlen((char *)arg);
exit:
	return;
}

void fATW2(void *arg)
{
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW2]Usage: ATW2=KEYID\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	printf("[ATW2]: _AT_WLAN_SET_KEY_ID_ [%s]\n\r", (char *)arg);
	if ((strlen((const char *)arg) != 1) || (*(char *)arg < '0' || *(char *)arg > '3')) {
		printf("\n\rWrong WEP key id. Must be one of 0,1,2, or 3.");
		ret = RTW_BADARG;
		goto exit;
	}
	wifi.key_id = atoi((const char *)(arg));
exit:
	return;
}

void fATW3(void *arg)
{
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW3]Usage: ATW3=SSID\n\r");
		ret = RTW_BADARG;
		goto exit;
	}

	ap.ssid.len = strlen((char *)arg);

	if (ap.ssid.len > 32) {
		printf("[ATW3]Error: SSID length can't exceed 32\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	strncpy((char *)ap.ssid.val, (char *)arg, sizeof(ap.ssid.val) - 1);

	printf("[ATW3]: _AT_WLAN_AP_SET_SSID_ [%s]\n\r", ap.ssid.val);
exit:
	return;
}

void fATW4(void *arg)
{
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW4]Usage: ATW4=PASSWORD\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	if (strlen((char *)arg) > 64) {
		printf("[ATW4]Error: PASSWORD length can't exceed 64\n\r");
		ret = RTW_BADARG;
		goto exit;
	}

	strncpy((char *)password, (char *)arg, sizeof(password) - 1);
	password[sizeof(password) - 1] = 0;
	ap.password = password;
	ap.password_len = strlen((char *)arg);
	printf("[ATW4]: _AT_WLAN_AP_SET_SEC_KEY_ [%s]\n\r", ap.password);
exit:
	return;
}

void fATW5(void *arg)
{
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW5]Usage: ATW5=CHANNEL\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	ap.channel = (unsigned char) atoi((const char *)arg);
	printf("[ATW5]: _AT_WLAN_AP_SET_CHANNEL_ [channel %d]\n\r", ap.channel);
exit:
	return;
}

void fATW6(void *arg)
{
	unsigned int	mac[ETH_ALEN];
	u32		i;
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	if (!arg) {
		printf("[ATW6]Usage: ATW6=BSSID\n\r");
		ret =  RTW_BADARG;
		goto exit;
	}
	printf("[ATW6]: _AT_WLAN_SET_BSSID_ [%s]\n\r", (char *)arg);
	sscanf(arg, MAC_FMT, mac, mac + 1, mac + 2, mac + 3, mac + 4, mac + 5);
	for (i = 0; i < ETH_ALEN; i ++) {
		wifi.bssid.octet[i] = (u8)mac[i] & 0xFF;
	}
exit:
	return;
}

#ifdef CONFIG_FPGA
void fATW7(void *arg)
{
	if (!arg) {
		printf("[ATW7]Usage: ATW7=0,1,2 or 3(open, WEP, TKIP or AES)\n\r");
		return;
	}
	volatile int ret = RTW_SUCCESS;
	(void) ret;
	printf("[ATW7]: _AT_WLAN_SET_SECURITY [%s]\n\r", (char *)arg);
	if ((strlen((const char *)arg) != 1) || (*(char *)arg < '0' || *(char *)arg > '3')) {
		printf("\n\rWrong num. Must be one of 0,1,2 or 3.");
		ret = RTW_BADARG;
		goto exit;
	}
	security = atoi((const char *)(arg));
exit:
	return;
}
#endif
void fATWf(void *arg)
{
	if (!arg) {
		printf("[ATWf]Usage: ATW8=[FLUSH_MODE]\n\r");
		printf("        0 : DISABLE AUTORECONNECT\n\r");
		printf("        1 : Enable AUTORECONNECT\n\r");
		printf("        2 : FLUSH SYSTEM DATA\n\r");
		return;
	}
	int mode =  atoi((const char *)arg);

	if (mode == 0) {
		printf("[ATWf] Disable autoreconnect...\n\r");
		wifi_config_autoreconnect(RTW_AUTORECONNECT_DISABLE, 0, 0);
	}
	if (mode == 1) {
		printf("[ATWf] Enable autoreconnect...\n\r");
		wifi_config_autoreconnect(1, AUTO_RECONNECT_COUNT, AUTO_RECONNECT_INTERVAL);
	} else if (mode == 2) {
		extern int sys_erase_system_data(void);
		printf("[ATWf] Flush system data");
		sys_erase_system_data();
	}

	return;
}

void fATWr(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;
	extern int rltk_wlan_get_beacon_rssi(int *bcn_rssi);
	int bcn_rssi = 0;
	rltk_wlan_get_beacon_rssi(&bcn_rssi);
	printf("\n\rbcn_rssi = %d", bcn_rssi);
	printf("\n\r");

}
char DATA_RATE[20][10] = { "CCK_1M", "CCK_2M", "CCK_5.5M", "CCK_11M", "OFDM_6M"
						   , "OFDM_9M", "OFDM_12M", "OFDM_18M", "OFDM_24M", "OFDM_36M"
						   , "OFDM_48M", "OFDM_54M", "HT_MCS0", "HT_MCS1", "HT_MCS2"
						   , "HT_MCS3", "HT_MCS4", "HT_MCS5", "HT_MCS6", "HT_MCS7"
						 };
void fATWd(void *arg)
{
	if (!arg) {
		printf("[ATDR]Usage: %s=[MODE]\n\r", __FUNCTION__);
		printf("        0 : Show Tx MCS Rate\n\r");
		printf("        1 : Show Rx MCS Rate\n\r");
		return;
	}

	int mode =  atoi((const char *)arg);
	if (mode == 0) {
		extern int rltk_wlan_get_tx_rate(unsigned char *tx_rate);
		u8 rate = 0;
		rltk_wlan_get_tx_rate(&rate);
		printf("[%s] Show Tx MCS Rate, tx_rate: %d[%s]\n\r", __FUNCTION__, rate, DATA_RATE[rate]);

	} else if (mode == 1) {
		extern int rltk_wlan_get_rx_rate(unsigned char *rx_rate);
		u8 rate = 0;
		rltk_wlan_get_rx_rate(&rate);
		printf("[%s] Show Rx MCS Rate, rx_rate: %d[%s]\n\r", __FUNCTION__, rate, DATA_RATE[rate]);
	}

	return;
}

void fATW8(void *arg)
{
	if (!arg) {
		printf("[ATW8]Usage: ATW8=[WPA_MODE]\n\r");
		printf("        0 : WPA_AUTO_MODE\n\r");
		printf("        1 : WPA_ONLY_MODE\n\r");
		printf("        2 : WPA2_ONLY_MODE\n\r");
		printf("        3 : WPA3_ONLY_MODE\n\r");
		printf("        4 : WPA_WPA2_MIXED_MODE\n\r");
		printf("        5 : WPA2_WPA3_MIXED_MODE\n\r");
		return;
	}
	u32 wpa_mode = (u32) atoi((const char *)arg);

	if (wpa_mode <= WPA2_WPA3_MIXED_MODE) {
		wifi_set_wpa_mode(wpa_mode);
		switch (wpa_mode) {
		case 0:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WPA_AUTO_MODE]\n\r");
			break;
		case 1:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WPA_ONLY_MODE]\n\r");
			break;
		case 2:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WPA2_ONLY_MODE]\n\r");
			break;
		case 3:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WPA3_ONLY_MODE]\n\r");
			break;
		case 4:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WPA_WPA2_MIXED_MODE]\n\r");
			break;
		case 5:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WPA2_WPA3_MIXED_MODE]\n\r");
			break;
		default:
			printf("[ATW8]: _AT_WLAN_AP_SET_WPA_MODE_ [WRONG WPA MODE]\n\r");
			break;
		}
	} else {
		printf("[ATW8] Wrong parameter\n\r");
	}

	return;
}

void fATWA(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;
#if CONFIG_LWIP_LAYER
	struct netif *pnetif = &xnetif[0];
	u32 ip_addr;
	u32 netmask;
	u32 gw;
#endif
	int timeout = 20;
	volatile int ret = RTW_SUCCESS;
	printf("[ATWA]: _AT_WLAN_AP_ACTIVATE_\n\r");
	if (ap.ssid.val[0] == 0) {
		printf("[ATWA]Error: SSID can't be empty\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	if (ap.password == NULL) {
		ap.security_type = RTW_SECURITY_OPEN;
	} else {
		if (ap.password_len <= RTW_WPA2_MAX_PSK_LEN &&
			ap.password_len >= RTW_MIN_PSK_LEN) {
			ap.security_type = RTW_SECURITY_WPA2_AES_PSK;
			if (ap.password_len == RTW_WPA2_MAX_PSK_LEN) { //password_len=64 means pre-shared key, pre-shared key should be 64 hex characters
				unsigned char i, j;
				for (i = 0; i < RTW_WPA2_MAX_PSK_LEN; i++) {
					j = ap.password[i];
					if (!((j >= '0' && j <= '9') || (j >= 'A' && j <= 'F') || (j >= 'a' && j <= 'f'))) {
						printf("[ATWA]Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
						ret = RTW_INVALID_KEY;
						goto exit;
					}
				}
			}
		}
#ifdef CONFIG_FPGA
		else if (ap.password_len == 5) {
			ap.security_type = RTW_SECURITY_WEP_PSK;
		}
#endif
		else {
			printf("[ATWA]Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
			ret = RTW_INVALID_KEY;
			goto exit;
		}
	}
#ifdef CONFIG_FPGA
	if (security == 0) {
		ap.security_type = RTW_SECURITY_OPEN;
	} else if (security == 1) {
		ap.security_type = RTW_SECURITY_WEP_PSK;
	} else if (security == 2) {
		ap.security_type = RTW_SECURITY_WPA2_TKIP_PSK;
	} else if (security == 3) {
		ap.security_type = RTW_SECURITY_WPA2_AES_PSK;
	}
#endif

#if CONFIG_LWIP_LAYER
	dhcps_deinit();
	ip_addr = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
	netmask = WIFI_MAKEU32(NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
	gw = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
	LwIP_SetIP(0, ip_addr, netmask, gw);
#endif

#if (defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8735B)) && (defined(CONFIG_BT) && CONFIG_BT)
	if (wifi_set_mode(RTW_MODE_AP) < 0) {
		printf("\n\rERROR: Wifi on failed!");
		ret = RTW_ERROR;
		goto exit;
	}
#else
	wifi_off();
	vTaskDelay(20);
	if (wifi_on(RTW_MODE_AP) < 0) {
		printf("\n\rERROR: Wifi on failed!");
		ret = RTW_ERROR;
		goto exit;
	}
#endif
	printf("\n\rStarting AP ...");

#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
	wpas_wps_dev_config(pnetif->hwaddr, 1);
#endif
	if ((ret = wifi_start_ap(&ap)) < 0) {
		printf("\n\rERROR: Operation failed!");
		goto exit;
	}

	while (1) {
		rtw_wifi_setting_t setting;
		wifi_get_setting(WLAN0_IDX, &setting);
		if (strlen((const char *)setting.ssid) > 0) {
			if (strcmp((const char *) setting.ssid, (const char *)ap.ssid.val) == 0) {
				printf("\n\r%s started\n", ap.ssid.val);
				ret = RTW_SUCCESS;
				break;
			}
		}

		if (timeout == 0) {
			printf("\n\rERROR: Start AP timeout!");
			ret = RTW_TIMEOUT;
			break;
		}

		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}

#if CONFIG_LWIP_LAYER
	ip_addr = WIFI_MAKEU32(AP_IP_ADDR0, AP_IP_ADDR1, AP_IP_ADDR2, AP_IP_ADDR3);
	netmask = WIFI_MAKEU32(AP_NETMASK_ADDR0, AP_NETMASK_ADDR1, AP_NETMASK_ADDR2, AP_NETMASK_ADDR3);
	gw = WIFI_MAKEU32(AP_GW_ADDR0, AP_GW_ADDR1, AP_GW_ADDR2, AP_GW_ADDR3);
	LwIP_SetIP(0, ip_addr, netmask, gw);
	dhcps_init(pnetif);
#endif

exit:
	init_wifi_struct();
}

void fATWC(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	int ret;
	rtw_wifi_setting_t setting = {0};
	unsigned long tick1 = xTaskGetTickCount();
	unsigned long tick2, tick3;
	char empty_bssid[6] = {0}, assoc_by_bssid = 0;
	/* To make coverity quite*/
	unsigned char empty_password[4] = {0};

	printf("[ATWC]: _AT_WLAN_JOIN_NET_\n\r");
	if (memcmp(wifi.bssid.octet, empty_bssid, 6)) {
		assoc_by_bssid = 1;
	} else if (wifi.ssid.val[0] == 0) {
		printf("[ATWC]Error: SSID can't be empty\n\r");
		ret = RTW_BADARG;
		goto EXIT;
	}
	if (wifi.password != NULL) {
		if ((wifi.key_id >= 0) && (wifi.key_id <= 3)) {
			wifi.security_type = RTW_SECURITY_WEP_PSK;
		} else {
			wifi.security_type = RTW_SECURITY_WPA2_AES_PSK;
		}
	} else {
		wifi.security_type = RTW_SECURITY_OPEN;
		wifi.password = empty_password;
	}
	//Check if in AP mode
	wifi_get_setting(WLAN0_IDX, &setting);
	if (setting.mode == RTW_MODE_AP) {
#if CONFIG_LWIP_LAYER
		dhcps_deinit();
#endif
#if (defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8735B)) && (defined(CONFIG_BT) && CONFIG_BT)
		if (wifi_set_mode(RTW_MODE_STA) < 0) {
			printf("\n\rERROR: Wifi on failed!");
			ret = RTW_ERROR;
			goto EXIT;
		}
#else
		wifi_off();
		vTaskDelay(20);
		if (wifi_on(RTW_MODE_STA) < 0) {
			printf("\n\rERROR: Wifi on failed!");
			ret = RTW_ERROR;
			goto EXIT;
		}
#endif
	}

	if (assoc_by_bssid) {
		printf("\n\rJoining BSS by BSSID "MAC_FMT" ...\n\r", MAC_ARG(wifi.bssid.octet));
	} else {
		printf("\n\rJoining BSS by SSID %s...\n\r", (char *)wifi.ssid.val);
	}
	ret = wifi_connect(&wifi, 1);


	if (ret != RTW_SUCCESS) {
		if (ret == RTW_INVALID_KEY) {
			printf("\n\rERROR:Invalid Key ");
		}

		printf("\n\rERROR: Can't connect to AP");
		goto EXIT;
	}
	tick2 = xTaskGetTickCount();
	printf("\r\nConnected after %d ms.\n", (unsigned int)(tick2 - tick1));
#if CONFIG_LWIP_LAYER
	/* Start DHCPClient */
	LwIP_DHCP(0, DHCP_START);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6_DHCP6
	LwIP_DHCP6(0, DHCP6_START);
#endif
#endif
	tick3 = xTaskGetTickCount();
	printf("\r\n\nGot IP after %d ms.\n", (unsigned int)(tick3 - tick1));
#endif


	printf("\n\r");
EXIT:

	init_wifi_struct();
}

#if SCAN_WITH_SSID
static int print_ssid_scan_result(unsigned int scanned_AP_num, void *user_data)
{
	/* To avoid gcc warnings */
	(void) user_data;

	char *scan_buf;
	rtw_scan_result_t *scanned_ap_info;
	int i = 0;

	if (scanned_AP_num == 0) {
		return RTW_ERROR;
	}

	scan_buf = (char *)rtw_zmalloc(scanned_AP_num * sizeof(rtw_scan_result_t));
	if (scan_buf == NULL) {
		printf("malloc scan buf fail for ATWs\n");
		return RTW_ERROR;
	}

	if (wifi_get_scan_records(&scanned_AP_num, scan_buf) < 0) {
		rtw_mfree(scan_buf, 0);
		return RTW_ERROR;
	}
	for (i = 0; i < scanned_AP_num; i++) {
		scanned_ap_info = (rtw_scan_result_t *)(scan_buf + i * sizeof(rtw_scan_result_t));
		scanned_ap_info->SSID.val[scanned_ap_info->SSID.len] = 0; /* Ensure the SSID is null terminated */
		print_scan_result(scanned_ap_info);
	}
	rtw_mfree(scan_buf, 0);

	return RTW_SUCCESS;
}

void fATWs(void *arg)
{
	char buf[32] = {0};
	u8 *channel_list = NULL;
	int num_channel = 0;
	rtw_scan_param_t scan_param;
	int i, argc = 0;
	char *argv[MAX_ARGC] = {0};
	printf("[ATWs]: _AT_WLAN_SCAN_WITH_SSID_ [%s]\n\r", (char *)wifi.ssid.val);
	if (arg) {
		strncpy(buf, arg, sizeof(buf));
		argc = parse_param(buf, argv);
		if (argc > 2) {
			num_channel = atoi(argv[1]);
			channel_list = (u8 *)malloc(num_channel);
			if (!channel_list) {
				printf("[ATWs]ERROR: Can't malloc memory for channel list\n\r");
				goto exit;
			}
			//parse command channel list
			for (i = 2; i <= argc - 1 ; i++) {
				*(channel_list + i - 2) = (u8)atoi(argv[i]);
			}
		} else {
			printf("[ATWs]For Scan all channel Usage: ATWs\n\r");
			printf("[ATWs]For Scan partial channel Usage: ATWs=num_channels[channel_num1, ...]\n\r");
			goto exit;
		}
	}
	if (!wifi.ssid.len) { //not set ssid yet
		printf("[ATWs]ssid not set yet, use ATW0 to set ssid\n\r");
		goto exit;
	}
	rtw_memset(&scan_param, 0, sizeof(rtw_scan_param_t));
	scan_param.ssid = (char *)wifi.ssid.val;
	scan_param.scan_user_callback = print_ssid_scan_result;
	scan_param.channel_list = channel_list;
	scan_param.channel_list_num = num_channel;
	if (wifi_scan_networks(&scan_param, 0) != RTW_SUCCESS) {
		printf("[ATWs]ERROR: wifi scan failed\n\r");
	}
exit:
	init_wifi_struct();
	if (arg && channel_list) {
		free(channel_list);
	}
}
#endif

void fATWR(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	rtw_phy_statistics_t phy_statistics;
	printf("[ATWR]: _AT_WLAN_GET_RSSI_\n\r");
	wifi_fetch_phy_statistic(&phy_statistics);
	printf("\n\rrssi = %d", phy_statistics.rssi);
	printf("\n\r");
}

void fATWY(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;
	rtw_phy_statistics_t phy_statistics;
	printf("[ATWY]: _AT_WLAN_GET_SNR_\n\r");
	wifi_fetch_phy_statistic(&phy_statistics);
	printf("\n\rsnr = %d", phy_statistics.snr);
	printf("\n\r");
}

void fATWP(void *arg)
{
	if (!arg) {
		printf("[ATWP]Usage: ATWP=0/1\n\r");
		return;
	}
	char parm = ((const char *)arg)[0];
	printf("[ATWP]: _AT_WLAN_POWER_[%s]\n\r", parm ? "ON" : "OFF");
	if (parm == '1') {
		if (wifi_on(RTW_MODE_STA) < 0) {
			printf("\n\rERROR: Wifi on failed!\n");
		}
	} else if (parm == '0') {
		wifi_off();
	} else {
		printf("[ATWP]Usage: ATWP=0/1\n\r");
	}
}

#ifdef  CONFIG_CONCURRENT_MODE
void fATWB(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	int timeout = 20;//, mode;
	volatile int ret = RTW_SUCCESS;
#if CONFIG_LWIP_LAYER
	struct netif *pnetiff = (struct netif *)&xnetif[1];
#endif
	printf("[ATWB](_AT_WLAN_AP_STA_ACTIVATE_)\n\r");
	if (ap.ssid.val[0] == 0) {
		printf("[ATWB]Error: SSID can't be empty\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	if (ap.password == NULL) {
		ap.security_type = RTW_SECURITY_OPEN;
	} else {
		if (ap.password_len <= RTW_WPA2_MAX_PSK_LEN &&
			ap.password_len >= RTW_MIN_PSK_LEN) {
			ap.security_type = RTW_SECURITY_WPA2_AES_PSK;
			if (ap.password_len == RTW_WPA2_MAX_PSK_LEN) { //password_len=64 means pre-shared key, pre-shared key should be 64 hex characters
				unsigned char i, j;
				for (i = 0; i < RTW_WPA2_MAX_PSK_LEN; i++) {
					j = ap.password[i];
					if (!((j >= '0' && j <= '9') || (j >= 'A' && j <= 'F') || (j >= 'a' && j <= 'f'))) {
						printf("[ATWA]Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
						ret = RTW_INVALID_KEY;
						goto exit;
					}
				}
			}
		} else {
			printf("[ATWA]Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
			ret = RTW_INVALID_KEY;
			goto exit;
		}
	}
#if CONFIG_LWIP_LAYER
	dhcps_deinit();
#endif

#if (defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8735B)) && (defined(CONFIG_BT) && CONFIG_BT)
	if (wifi_set_mode(RTW_MODE_STA_AP) < 0) {
		printf("\n\rERROR: Wifi on failed!");
		ret = RTW_ERROR;
		goto exit;
	}
#else
	wifi_off();
	vTaskDelay(20);
	if ((ret = wifi_on(RTW_MODE_STA_AP)) < 0) {
		printf("\n\rERROR: Wifi on failed!");
		ret = RTW_ERROR;
		goto exit;
	}
#endif

	printf("\n\rStarting AP ...");
	if ((ret = wifi_start_ap(&ap)) < 0) {
		printf("\n\rERROR: Operation failed!");
		goto exit;
	}
	while (1) {
		rtw_wifi_setting_t setting;
		wifi_get_setting(WLAN1_IDX, &setting);
		if (strlen((const char *)setting.ssid) > 0) {
			if (strcmp((const char *) setting.ssid, (const char *)ap.ssid.val) == 0) {
				printf("\n\r%s started\n", ap.ssid.val);
				ret = RTW_SUCCESS;
				break;
			}
		}

		if (timeout == 0) {
			printf("\n\rERROR: Start AP timeout!");
			ret = RTW_TIMEOUT;
			break;
		}

		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}
#if CONFIG_LWIP_LAYER
	u32 addr = WIFI_MAKEU32(AP_IP_ADDR0, AP_IP_ADDR1, AP_IP_ADDR2, AP_IP_ADDR3);
	u32 netmask = WIFI_MAKEU32(AP_NETMASK_ADDR0, AP_NETMASK_ADDR1, AP_NETMASK_ADDR2, AP_NETMASK_ADDR3);
	u32 gw = WIFI_MAKEU32(AP_GW_ADDR0, AP_GW_ADDR1, AP_GW_ADDR2, AP_GW_ADDR3);
	LwIP_SetIP(1, addr, netmask, gw);
	dhcps_init(pnetiff);
#endif

exit:
	init_wifi_struct();
}

//This AT cmd is used in concurrent mode after resume interface2, there's no wifi on/off in this command
void fATWa(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	int timeout = 20;//, mode;
	volatile int ret = RTW_SUCCESS;
#if CONFIG_LWIP_LAYER
	struct netif *pnetiff = (struct netif *)&xnetif[1];
#endif
	printf("[ATWa](_AT_WLAN_START_AP_ON_IF2_)\n\r");
	if (ap.ssid.val[0] == 0) {
		printf("[ATWa]Error: SSID can't be empty\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	if (ap.password == NULL) {
		ap.security_type = RTW_SECURITY_OPEN;
	} else {
		if (ap.password_len <= RTW_WPA2_MAX_PSK_LEN &&
			ap.password_len >= RTW_MIN_PSK_LEN) {
			ap.security_type = RTW_SECURITY_WPA2_AES_PSK;
			if (ap.password_len == RTW_WPA2_MAX_PSK_LEN) { //password_len=64 means pre-shared key, pre-shared key should be 64 hex characters
				unsigned char i, j;
				for (i = 0; i < RTW_WPA2_MAX_PSK_LEN; i++) {
					j = ap.password[i];
					if (!((j >= '0' && j <= '9') || (j >= 'A' && j <= 'F') || (j >= 'a' && j <= 'f'))) {
						printf("[ATWa]Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
						ret = RTW_INVALID_KEY;
						goto exit;
					}
				}
			}
		} else {
			printf("[ATWa]Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
			ret = RTW_INVALID_KEY;
			goto exit;
		}
	}

#if CONFIG_LWIP_LAYER
	dhcps_deinit();
#endif

	printf("\n\rStarting AP ...");
	if ((ret = wifi_start_ap(&ap)) < 0) {
		printf("\n\rERROR: Operation failed!");
		goto exit;
	}
	while (1) {
		rtw_wifi_setting_t setting;
		wifi_get_setting(WLAN1_IDX, &setting);
		if (strlen((const char *)setting.ssid) > 0) {
			if (strcmp((const char *) setting.ssid, (const char *)ap.ssid.val) == 0) {
				printf("\n\r%s started\n", ap.ssid.val);
				ret = RTW_SUCCESS;
				break;
			}
		}

		if (timeout == 0) {
			printf("\n\rERROR: Start AP timeout!");
			ret = RTW_TIMEOUT;
			break;
		}

		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}
#if CONFIG_LWIP_LAYER
	u32 addr = WIFI_MAKEU32(AP_IP_ADDR0, AP_IP_ADDR1, AP_IP_ADDR2, AP_IP_ADDR3);
	u32 netmask = WIFI_MAKEU32(AP_NETMASK_ADDR0, AP_NETMASK_ADDR1, AP_NETMASK_ADDR2, AP_NETMASK_ADDR3);
	u32 gw = WIFI_MAKEU32(AP_GW_ADDR0, AP_GW_ADDR1, AP_GW_ADDR2, AP_GW_ADDR3);
	LwIP_SetIP(1, addr, netmask, gw);
	dhcps_init(pnetiff);
#endif

exit:
	init_wifi_struct();
}
#endif

#ifdef CONFIG_PROMISC
void fATWM(void *arg)
{
	int argc;
	char *argv[MAX_ARGC] = {0};
	argv[0] = (char *)"wifi_promisc";
	printf("[ATWM]: _AT_WLAN_PROMISC_\n\r");
	if (!arg) {
		printf("[ATWM]Usage: ATWM=DURATION_SECONDS[with_len]");
		return;
	}
	if ((argc = parse_param(arg, argv)) > 1) {
		cmd_promisc(argc, argv);
	}
}
#endif

void fATWW(void *arg)
{
#if CONFIG_ENABLE_WPS
	int argc = 0;
	char *argv[4];
	printf("[ATWW]: _AT_WLAN_WPS_\n\r");
	if (!arg) {
		printf("[ATWW]Usage: ATWW=pbc/pin\n\r");
		return;
	}
	argv[argc++] = (char *)"wifi_wps";
	argv[argc++] = arg;
	cmd_wps(argc, argv);
#else
	(void) arg;
	printf("Please set CONFIG_ENABLE_WPS 1 in platform_opts.h to enable ATWW command\n");
#endif
}
void fATWw(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;
#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
	int argc = 0;
	char *argv[4];
	printf("[ATWw]: _AT_WLAN_AP_WPS_\n\r");
	if (!arg) {
		printf("[ATWw]Usage: ATWw=pbc/pin\n\r");
		return;
	}
	argv[argc++] = (char *)"wifi_ap_wps";
	argv[argc++] = arg;
	cmd_ap_wps(argc, argv);
#endif
}

#if CONFIG_ENABLE_P2P
void fATWG(void *arg)
{
	int argc = 0;
	char *argv[4];
	printf("[ATWG]: _AT_WLAN_P2P_START_\n\r");
	argv[argc++] = (char *)"p2p_start";
	cmd_wifi_p2p_start(argc, argv);
}

void fATWg(void *arg)
{
	int argc = 0;
	char *argv[4];
	int ret = 0;
	printf("[ATWg]: _AT_WLAN_P2P_AUTO_GO_START_\n\r");
	argv[argc++] = (char *)"p2p_auto_go_start";
	ret = cmd_wifi_p2p_auto_go_start(argc, argv);
	if (ret < 0) {
		printf("\r\n[ATWG]: Nothing to do. Please enter ATWG to initialize P2P.\n\r");
	}
}

void fATWH(void *arg)
{
	int argc = 0;
	char *argv[4];
	printf("[ATWH]: _AT_WLAN_P2P_STOP_\n\r");
	argv[argc++] = (char *)"p2p_stop";
	cmd_wifi_p2p_stop(argc, argv);
}
void fATWJ(void *arg)
{
	int argc = 0;
	char *argv[4];
	printf("[ATWJ]: _AT_WLAN_P2P_CONNECT_\n\r");
	argv[0] = (char *)"p2p_connect";
	if (!arg) {
		printf("ATWc=[DEST_MAC,pbc/pin]\n\r");
		return;
	}
	if ((argc = parse_param(arg, argv)) > 1) {
		cmd_p2p_connect(argc, argv);
	}
}
void fATWK(void *arg)
{
	int argc = 0;
	char *argv[4];
	printf("[ATWK]: _AT_WLAN_P2P_DISCONNECT_\n\r");
	argv[argc++] = (char *)"p2p_disconnect";
	cmd_p2p_disconnect(argc, argv);
}
void fATWN(void *arg)
{
	int argc = 0;
	char *argv[4];
	printf("[ATWN]: _AT_WLAN_P2P_INFO_\n\r");
	argv[argc++] = (char *)"p2p_info";
	cmd_p2p_info(argc, argv);
}
void fATWF(void *arg)
{
	int argc = 0;
	char *argv[4];
	printf("[ATWF]: _AT_WLAN_P2P_FIND_\n\r");
	argv[argc++] = (char *)"p2p_find";
	cmd_p2p_find(argc, argv);
}
#endif
#if CONFIG_OTA_UPDATE
void fATWO(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	printf("[ATWO]: _AT_WLAN_OTA_UPDATE_\n\r");
	if (!arg) {
		printf("[ATWO]Usage: ATWO=IP[PORT] or ATWO= REPOSITORY[FILE_PATH]\n\r");
		return;
	}
	argv[0] = (char *)"update";
	if ((argc = parse_param(arg, argv)) != 3) {
		printf("[ATWO]Usage: ATWO=IP[PORT] or ATWO= REPOSITORY[FILE_PATH]\n\r");
		return;
	}
	cmd_update(argc, argv);
}
#endif

#if CONFIG_AIRKISS
void fATWX(void *arg)
{
	int argc;
	int ret = RTW_SUCCESS;
	unsigned char *argv[MAX_ARGC] = {0};

	argv[0] = (char *)"airkiss";
	argc = parse_param(arg, argv);
	if (argc == 2) {
		if (strcmp(argv[1], "start") == 0) {
			ret = airkiss_start(NULL);
		} else if (strcmp(argv[1], "stop") == 0) {
			ret = airkiss_stop();
		} else {
			printf("\r\n[ATWX] Usage: ATWX=[start/stop]");
		}
	} else {
		printf("\r\n[ATWX] start/stop airkiss config\r\n");
		printf("\r\n[ATWX] Usage: ATWX=[start/stop]");
		ret = RTW_ERROR;
	}
}
#endif

void fATWZ(void *arg)
{
	char buf[64] = {0};
	char *copy = buf;
	int i = 0;
	int len = 0;
	volatile int ret = RTW_SUCCESS;
	(void) ret;

	printf("[ATWZ]: _AT_WLAN_IWPRIV_\n\r");
	if (!arg) {
		printf("[ATWZ]Usage: ATWZ=COMMAND[PARAMETERS]\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	strncpy(copy, arg, sizeof(buf) - 1);
	len = strlen(copy);
	do {
		if ((*(copy + i) == '[')) {
			*(copy + i) = ' ';
		}
		if ((*(copy + i) == ']') || (*(copy + i) == '\0')) {
			*(copy + i) = '\0';
			break;
		}
	} while ((i++) < len);

	i = 0;
	do {
		if ((*(copy + i) == ',')) {
			*(copy + i) = ' ';
			break;
		}
	} while ((i++) < len);

#ifdef CONFIG_AS_INIC_AP
	inic_ipc_iwpriv_command(copy, strlen(copy) + 1, 1);
#else
	rtw_iwpriv_command(WLAN0_NAME, copy, 1);
#endif

exit:
	return;	// exit label cannot be last statement
}

void fATXP(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	volatile int ret = 0;
	(void) ret;
	int mode;

	printf("[ATXP]: _AT_WLAN_POWER_MODE_\r\n");

	if (!arg) {
		printf("[ATXP] Usage: ATXP=lps/ips/dtim[mode]\r\n");
		ret = RTW_BADARG;
		goto exit;
	} else {
		argc = parse_param(arg, argv);
		if (argc < 3) {
			printf("[ATXP] Usage: ATXP=lps/ips/dtim[mode]\r\n");
			ret = RTW_BADARG;
			goto exit;
		}
	}

	if (strcmp(argv[1], "lps") == 0) {
		mode = atoi(argv[2]);
		if (mode >= 0 && mode < 0xFF) {
			printf("lps mode:%d\r\n", mode);
			wifi_set_powersave_mode(0xff, mode);
		}
	}

	if (strcmp(argv[1], "ips") == 0) {
		mode = atoi(argv[2]);
		if (mode >= 0 && mode < 0xFF) {
			printf("ips mode:%d\r\n", mode);
			wifi_set_powersave_mode(mode, 0xFF);
		}
	}

exit:
	return;
}

void print_wlan_help(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;

	printf("\n\rWLAN AT COMMAND SET:");
	printf("\n\r==============================");
	printf("\n\r1. Wlan Scan for Network Access Point");
	printf("\n\r   # ATWS");
	printf("\n\r2. Connect to an AES AP");
	printf("\n\r   # ATW0=SSID");
	printf("\n\r   # ATW1=PASSPHRASE");
	printf("\n\r   # ATWC");
	printf("\n\r3. Create an AES AP");
	printf("\n\r   # ATW3=SSID");
	printf("\n\r   # ATW4=PASSPHRASE");
	printf("\n\r   # ATW5=CHANNEL");
	printf("\n\r   # ATWA");
	printf("\n\r4. Ping");
	printf("\n\r   # ATWI=xxx.xxx.xxx.xxx");
}

void fATPE(void *arg)
{
	int argc;
	char *argv[MAX_ARGC] = {0};

	if (!arg) {
		printf("[ATPE] Usage : ATPE=<ip>(,<gateway>,<mask>)\n\r");
		return;
	}

	argc = parse_param(arg, argv);
	if ((argc != 2) && (argc != 4)) {
		printf("[ATPE] command error\n\r");
		return;
	}

	//static IP will be set in LwIP_DHCP()
	user_static_ip.use_static_ip = 1;
	user_static_ip.addr = PP_HTONL(inet_addr(argv[1]));
	user_static_ip.gw = PP_HTONL(inet_addr(argv[2]));
	user_static_ip.netmask = PP_HTONL(inet_addr(argv[3]));

	return;
}

#if WIFI_LOGO_CERTIFICATION_CONFIG
#ifdef CONFIG_SAE_SUPPORT
void fATWGRP(void *arg)
{

	unsigned char grp_id = 0, i = 0, error = 0;
	int target_grp_id[10] = {19, 20};

	if (!arg) {
		error = 1;
	} else {
		grp_id = atoi((const char *)(arg));

		for (i = 0; i < 2; i++)
			if (grp_id == target_grp_id[i]) {
				break;
			}

		if (i == 2) {
			error = 1;
		}
	}

	if (error) {
		printf("[ATGP]error cmd  !!\n\r");
		printf("[ATGP]Usage: ATGP = group_id \n\r");
		printf("      *************************************************\n\r");
		printf("      ECC group: 19, 20 \n\r");
		printf("      *************************************************\n\r");
	} else {
		printf("[ATGP]: _AT_WLAN_SET_GRPID [%s]\n\r", (char *)arg);
		wifi_set_group_id(grp_id);
	}

	return;
}
#endif

void fATWPMK(void *arg)
{

	unsigned char pmk_enable = 0, error = 0;

	if (!arg) {
		error = 1;
	} else {
		if (1 != atoi((const char *)(arg))) {
			pmk_enable = 0;
		} else {
			pmk_enable = 1;
		}

		printf("pmk_enable = %d\r\n", pmk_enable);
		printf("[ATPM]: _AT_WLAN_SET_PMK [%s]\n\r", (char *)arg);
		wifi_set_pmk_cache_enable(pmk_enable);

	}

	if (error) {
		printf("[ATPM]error cmd  !!\n\r");
		printf("[ATPM]Usage: ATPM = enable \n\r");
		printf("      *************************************************\n\r");
		printf("      1: enable; 0: disable \r\n");
		printf("      *************************************************\n\r");
	}

}

#ifdef CONFIG_IEEE80211W
void fATWPMF(void *arg)
{

	int ret;
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	unsigned char pmf_mode;

	printf("[ATMF]: _AT_WLAN_PROTECTED_MANAGEMENT_FRAME_\r\n");

	if (!arg) {
		printf("[ATMF] Usage: ATMF=none/optional/required\r\n");
		ret = RTW_BADARG;
		goto exit;
	} else {
		argc = parse_param(arg, argv);
		if (argc < 2) {
			printf("[ATMF] Usage: ATMF=none/optional/required\r\n");
			ret = RTW_BADARG;
			goto exit;
		}
	}

	if (strcmp(argv[1], "none") == 0) {
		pmf_mode = 0;
		ret = rltk_set_pmf(pmf_mode);
		if (ret == 0) {
			printf("[ATMF]: set station no management protection\r\n");
		}
	}

	if (strcmp(argv[1], "optional") == 0) {
		pmf_mode = 1;
		ret = rltk_set_pmf(pmf_mode);
		if (ret == 0) {
			printf("[ATMF]: set station pmf optional\r\n");
		}
	}

	if (strcmp(argv[1], "required") == 0) {
		pmf_mode = 2;
		ret = rltk_set_pmf(pmf_mode);
		if (ret == 0) {
			printf("[ATMF]: set station pmf required\r\n");
		}
	}

exit:
	return;
}
#endif
#endif //WIFI_LOGO_CERTIFICATION_CONFIG

#ifdef CONFIG_RTK_MESH
void fATW_mesh(void *arg)
{
#if CONFIG_LWIP_LAYER
	int use_default_ip = 1;
	int addr3 = 0;
#endif
	int timeout = 20;
	int ret = RTW_SUCCESS;

	if (!arg) {
		printf("[ATW+]: _AT_WLAN_MESH_ACTIVATE_\n\r");
	} else {
		addr3 = rtw_atoi(arg);
		if ((addr3 > 254) || (addr3 < 1)) {
			printf("[ATW+]Error: the last address x %d of ip 192.168.1.x should be between 1 and 255\n\r", addr3);
			ret = RTW_BADARG;
			goto exit;
		} else {
			printf("[ATW+]: Set mesh IP to 192.168.1.%d\n\r", addr3);
			printf("[ATW+]: _AT_WLAN_MESH_ACTIVATE_\n\r");
			use_default_ip = 0;
		}
	}

	if (ap.ssid.val[0] == 0) {
		printf("[ATWA]Error: SSID can't be empty\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	if (ap.password == NULL) {
		ap.security_type = RTW_SECURITY_OPEN;
	} else {
		if (ap.password_len <= RTW_MAX_PSK_LEN &&
			ap.password_len >= RTW_MIN_PSK_LEN) {
			ap.security_type = RTW_SECURITY_WPA3_AES_PSK;
		} else {
			printf("[ATW+]Error: password length is between 8 to 64 \n\r");
			ret = RTW_INVALID_KEY;
			goto exit;
		}
	}

	wifi_off();
	vTaskDelay(20);
	if (wifi_on(RTW_MODE_AP) < 0) {
		printf("\n\rERROR: Wifi on failed!");
		ret = RTW_ERROR;
		goto exit;
	}
	printf("\n\rStarting Mesh Point ...");

	if ((ret = wifi_start_mesh_point((char *)ap.ssid.val, ap.security_type, (char *)ap.password, ap.ssid.len, ap.password_len, ap.channel)) < 0) {
		printf("\n\rERROR: Operation failed!");
		goto exit;
	}

	while (1) {
		char mesh_id[33] = {0};

		if (wifi_get_mesh_id((unsigned char *) mesh_id) == 0) {
			if (strcmp((const char *) mesh_id, (const char *)ap.ssid.val) == 0) {
				printf("\n\r%s started\n", ap.ssid.val);
				ret = RTW_SUCCESS;
				break;
			}
		}

		if (timeout == 0) {
			printf("\n\rERROR: Start Mesh point timeout!");
			ret = RTW_TIMEOUT;
			break;
		}

		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}

#if CONFIG_LWIP_LAYER
	u32 addr = 0;
	u32 netmask = WIFI_MAKEU32(AP_NETMASK_ADDR0, AP_NETMASK_ADDR1, AP_NETMASK_ADDR2, AP_NETMASK_ADDR3);
	u32 gw = WIFI_MAKEU32(AP_GW_ADDR0, AP_GW_ADDR1, AP_GW_ADDR2, AP_GW_ADDR3);

	if (use_default_ip == 1) {
		addr = WIFI_MAKEU32(AP_IP_ADDR0, AP_IP_ADDR1, AP_IP_ADDR2, AP_IP_ADDR3);
	} else {
		addr = WIFI_MAKEU32(AP_IP_ADDR0, AP_IP_ADDR1, AP_IP_ADDR2, addr3);
	}
	LwIP_SetIP(0, addr, netmask, gw);
	//dhcps_init(pnetif);
#endif
exit:
	init_wifi_struct();
}

void fATW7(void *arg)
{
	int ret = RTW_SUCCESS;
	s32 rssi = 0;
	if (!arg) {
		printf("[ATW7]Usage: ATW7=threshold\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	rssi = (unsigned char) atoi((const char *)arg);
	printf("[ATW7]: _AT_WLAN_MESH_SET_RSSI_ [threshold %d]\n\r", rssi);
	wifi_set_mesh_rssi_threshold(WLAN0_NAME, rssi);

exit:
	return;
}

void fATW8(void *arg)
{
	int ret = RTW_SUCCESS;
	int i, j;
	u8 hwaddr[ETH_ALEN];
	u8 *mac;
	if (!arg) {
		printf("[ATW8]Usage: ATW8=MAC\n\r");
		ret = RTW_BADARG;
		goto exit;
	}
	printf("[ATW8]: _AT_WLAN_MESH_SET_MAC_FILTER_ [%s]\n\r", arg);
	mac = (u8 *)arg;
	for (i = 0, j = 0; i < ETH_ALEN; i++, j += 3) {
		hwaddr[i] = key_2char2num(mac[j], mac[j + 1]);
	}
	wifi_init_mac_filter();
	wifi_add_mac_filter(hwaddr);
	wifi_list_mac_filter();

exit:
	return;
}

void fATW9(void *arg)
{
	int ret = RTW_SUCCESS;
	int i, j;
	u8 hwaddr[ETH_ALEN];
	u8 *mac;
	if (arg) {
		printf("[ATW9]: _AT_WLAN_MESH_DEL_MAC_FILTER_ [%s]\n\r", arg);
		mac = (u8 *)arg;
		for (i = 0, j = 0; i < ETH_ALEN; i++, j += 3) {
			hwaddr[i] = key_2char2num(mac[j], mac[j + 1]);
		}
		wifi_del_mac_filter(hwaddr);
	}
	wifi_list_mac_filter();

exit:
	return;
}
#endif
#elif ATCMD_VER == ATVER_2 // UART module at command

//ATPA=<ssid>,<pwd>,<chl>,<hidden>[,<max_conn>]
void fATPA(void *arg)
{
	int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	rtw_wifi_setting_t setting = {0};
#if CONFIG_LWIP_LAYER
	struct ip_addr ipaddr;
	struct ip_addr netmask;
	struct ip_addr gw;
	uint8_t idx;
	struct netif *pnetif;
#endif
	int timeout = 20;

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPA] Usage: ATPA=<ssid>,<pwd>,<chl>,<hidden>[,<max_conn>]");
		error_no = 1;
		goto exit;
	}

	argc = parse_param(arg, argv);
	if (argc < 5) {
		//at_printf("\r\n[ATPA] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	if ((wifi_mode_new != RTW_MODE_AP) && (wifi_mode_new != RTW_MODE_STA_AP)) {
		//at_printf("\r\n[ATPA] ERROR : wifi mode error");
		error_no = 5;
		goto exit;
	}

	//SSID
	if (argv[1] != NULL) {
		ap.ssid.len = strlen((char *)argv[1]);
		if (ap.ssid.len > 32) {
			//at_printf("\r\n[ATPA] ERROR : SSID length can't exceed 32");
			error_no = 2;
			goto exit;
		}
		strncpy((char *)ap.ssid.val, (char *)argv[1], sizeof(ap.ssid.val));
	} else {
		//at_printf("\r\n[ATPA] ERROR : SSID can't be empty");
		error_no = 2;
		goto exit;
	}

	//PASSWORD
	if (argv[2] != NULL) {
		if ((strlen(argv[2]) < 8) || (strlen(argv[2]) > 64)) {
			//at_printf("\r\n[ATPA] ERROR : PASSWORD length error");
			error_no = 2;
			goto exit;
		}
		strncpy((char *)password, (char *)argv[2], sizeof(password));
		ap.password = password;
		ap.password_len = strlen((char *)argv[2]);
		ap.security_type = RTW_SECURITY_WPA2_AES_PSK;
	} else {
		ap.security_type = RTW_SECURITY_OPEN;
	}

	//CHANNEL
	if (argv[3] != NULL) {
		ap.channel = (unsigned char) atoi((const char *)argv[3]);
		if ((ap.channel < 0) || (ap.channel > 11)) {
			//at_printf("\r\n[ATPA] ERROR : channel number error");
			error_no = 2;
			goto exit;
		}
	}

	//HIDDEN SSID
	if (argv[4] != NULL) {
		if ((atoi(argv[4]) != 0) && (atoi(argv[4]) != 1)) {
			//at_printf("\r\n[ATPA] ERROR : HIDDEN SSID must be 0 or 1");
			error_no = 2;
			goto exit;
		}
		ap.hidden_ssid = (unsigned char) atoi((const char *)argv[4]);
	}

#if CONFIG_LWIP_LAYER
	dhcps_deinit();
#endif

	wifi_unreg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl);

#if (defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8735B)) && (defined(CONFIG_BT) && CONFIG_BT)
	if (wifi_set_mode(wifi_mode_new) < 0) {
		//at_printf("\r\n[ATPA] ERROR : Wifi on failed");
		error_no = 3;
		goto exit;
	}
#else
	wifi_off();
	vTaskDelay(20);

	if (wifi_on(wifi_mode_new) < 0) {
		//at_printf("\r\n[ATPA] ERROR : Wifi on failed");
		error_no = 3;
		goto exit;
	}
#endif

	if (wifi_start_ap(&ap) < 0) {
		//at_printf("\r\n[ATPA] ERROR : Start AP failed");
		error_no = 4;
		goto exit;
	}

	while (1) {
		char essid[33];
		if (wifi_mode_new == RTW_MODE_AP) {
			wifi_get_setting(WLAN0_IDX, &setting);
			if (strlen(setting.ssid) > 0) {
				if (strcmp((const char *) setting.ssid, (const char *)ap.ssid.val) == 0) {
					break;
				}
			}
		} else if (wifi_mode_new == RTW_MODE_STA_AP) {
			wifi_get_setting(WLAN1_IDX, &setting);
			if (strlen(setting.ssid) > 0) {
				if (strcmp((const char *) setting.ssid, (const char *)ap.ssid.val) == 0) {
					break;
				}
			}
		}

		if (timeout == 0) {
			//at_printf("\r\n[ATPA] ERROR : Start AP timeout");
			error_no = 4;
			break;
		}

		vTaskDelay(1 * configTICK_RATE_HZ);
		timeout --;
	}
#if CONFIG_LWIP_LAYER
	if (wifi_mode_new == RTW_MODE_STA_AP) {
		idx = 1;
	} else {
		idx = 0;
	}

	u32 addr = WIFI_MAKEU32(AP_IP_ADDR0, AP_IP_ADDR1, AP_IP_ADDR2, AP_IP_ADDR3);
	u32 netmask = WIFI_MAKEU32(AP_NETMASK_ADDR0, AP_NETMASK_ADDR1, AP_NETMASK_ADDR2, AP_NETMASK_ADDR3);
	u32 gw = WIFI_MAKEU32(AP_GW_ADDR0, AP_GW_ADDR1, AP_GW_ADDR2, AP_GW_ADDR3);
	LwIP_SetIP(idx, addr, netmask, gw);

	if (dhcp_mode_ap == 1) {
		pnetif = &xnetif[idx];
		dhcps_init(pnetif);
	}
#endif

exit:
	init_wifi_struct();

	if (error_no == 0) {
		at_printf("\r\n[ATPA] OK");
	} else {
		at_printf("\r\n[ATPA] ERROR:%d", error_no);
	}

	return;
}

/*find ap with "ssid" from scan list*/
static int _find_ap_from_scan_buf(char *target_ssid, void *user_data, int ap_num)
{
	rtw_wifi_setting_t *pwifi = (rtw_wifi_setting_t *)user_data;
	rtw_scan_result_t *scanned_ap_info;
	int i = 0;
	char *scan_buf = NULL;

	scan_buf = (char *)rtw_zmalloc(ap_num * sizeof(rtw_scan_result_t));
	if (scan_buf == NULL) {
		return -1;
	}

	if (wifi_get_scan_records(&ap_num, scan_buf) < 0) {
		rtw_mfree(scan_buf, 0);
		return -1;
	}

	for (i = 0; i < ap_num; i++) {
		scanned_ap_info = (rtw_scan_result_t *)(scan_buf + i * sizeof(rtw_scan_result_t));
		if ((scanned_ap_info->SSID.len == strlen(target_ssid)) && (!memcmp(scanned_ap_info->SSID.val, target_ssid, scanned_ap_info->SSID.len))) {
			strncpy((char *)pwifi->ssid, target_ssid, sizeof(pwifi->ssid));
			pwifi->channel = scanned_ap_info->channel;
			pwifi->security_type = scanned_ap_info->security;
		}
	}
	rtw_mfree(scan_buf, 0);
	return 0;

}

/*get ap security mode from scan list*/
static int _get_ap_security_mode(IN char *ssid, OUT rtw_security_t *security_mode, OUT u8 *channel)
{
	rtw_wifi_setting_t wifi;
	rtw_scan_param_t scan_param;
	int scanned_ap_num = 0;
	int ret = 0;

	memset(&wifi, 0, sizeof(wifi));

	rtw_memset(&scan_param, 0, sizeof(rtw_scan_param_t));
	scan_param.ssid = ssid;
	scanned_ap_num = wifi_scan_networks(&scan_param, 1);

	if (scanned_ap_num <= 0) {
		ret = 0;
	} else {
		_find_ap_from_scan_buf(ssid, (void *)&wifi, scanned_ap_num);

		if (strcmp(wifi.ssid, ssid) == 0) {
			*security_mode = wifi.security_type;
			*channel = wifi.channel;
			ret = 1;
		}
	}

	return ret;
}

//ATPN=<ssid>,<pwd>[,<key_id>,<bssid>]
static char g_assoc_by_bssid = 0;
static int connect_async = 0;

static void atcmd_wifi_disconn_hdl(char *buf, int buf_len, int flags, void *userdata)
{
	wifi_unreg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl);
#if CONFIG_LOG_SERVICE_LOCK
	log_service_lock();
#endif
	at_printf("\r\n[ATWD] OK");
	at_printf(STR_END_OF_ATCMD_RET);
#if CONFIG_LOG_SERVICE_LOCK
	log_service_unlock();
#endif
}

u32 connect_by_rssi(char *target_ssid, int ap_num)
{
	rtw_scan_result_t *scanned_ap_info;
	signed short last_rssi;
	int same_ssid_cnt = 0;
	int i;
	char *scan_buf = NULL;

	scan_buf = (char *)rtw_zmalloc(ap_num * sizeof(rtw_scan_result_t));
	if (scan_buf == NULL) {
		return RTW_ERROR;
	}

	if (wifi_get_scan_records(&ap_num, scan_buf) < 0) {
		rtw_mfree(scan_buf, 0);
		return RTW_ERROR;
	}

	for (i = 0; i < ap_num; i++) {
		scanned_ap_info = (rtw_scan_result_t *)(scan_buf + i * sizeof(rtw_scan_result_t));
		if ((scanned_ap_info->SSID.len == strlen(target_ssid)) && (!memcmp(scanned_ap_info->SSID.val, target_ssid, strlen(target_ssid)))) {
			AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_INFO,
					   "\r\n[ATPN] The target ssid is found %s, same_ssid_cnt %d, last_rssi %d, rssi %d \n",
					   scanned_ap_info->SSID.val, same_ssid_cnt, last_rssi, scanned_ap_info->signal_strength);
			if (same_ssid_cnt != 0 && last_rssi < scanned_ap_info->signal_strength) {
				rtw_memcpy(wifi.bssid.octet, scanned_ap_info->BSSID.octet, ETH_ALEN);
				g_assoc_by_bssid = 1;
			}
			same_ssid_cnt++;
			last_rssi = scanned_ap_info->signal_strength;
		}
	}
	rtw_mfree(scan_buf, 0);
	return 0;
}

void scan_and_sort()
{
	rtw_scan_param_t scan_param;
	int scanned_ap_num = 0;

	rtw_memset(&scan_param, 0, sizeof(rtw_scan_param_t));
	scan_param.ssid = (char *)wifi.ssid.val;

	scanned_ap_num = wifi_scan_networks(&scan_param, 1);
	if (scanned_ap_num <= 0) {
		at_printf("wifi scan failed\n\r");
	} else {
		connect_by_rssi((char *)wifi.ssid.val, scanned_ap_num);
	}

	return;
}

void connect_thread(void *param)
{
	int ret, error_no = 0;

	ret = wifi_connect(&wifi, 1);

	if (ret != RTW_SUCCESS) {
		//at_printf("\r\n[ATPN] ERROR: Can't connect to AP");
		error_no = 4;
		goto exit;
	}

#if CONFIG_LWIP_LAYER
	if (dhcp_mode_sta == 2) {
		struct netif *pnetif = &xnetif[0];
		u32 addr = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
		u32 netmask = WIFI_MAKEU32(NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
		u32 gw = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
		LwIP_SetIP(0, addr, netmask, gw);
		dhcps_init(pnetif);
	} else {
		ret = LwIP_DHCP(0, DHCP_START);
		if (ret != DHCP_ADDRESS_ASSIGNED) {
			error_no = 7;
		}
	}
#endif

exit:
	init_wifi_struct();
	if (error_no == 0) {
		wifi_reg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl, NULL);
		at_printf("\r\n[ATPN] OK");
	} else {
		at_printf("\r\n[ATPN] ERROR:%d", error_no);
	}
	connect_async = 0;
	vTaskDelete(NULL);


}
void fATPN(void *arg)
{
	int argc, error_no = 0;
	int i, j;
	int async = 0;
	char *argv[MAX_ARGC] = {0};

	int mode, ret;
	rtw_wifi_setting_t setting = {0};
	unsigned long tick1 = xTaskGetTickCount();
	unsigned long tick2, tick3;
	char empty_bssid[6] = {0};
	u8 connect_channel;

	g_assoc_by_bssid = 0;
#if ATCMD_VER == ATVER_2
	int rc = -1;
	int switch_buflen = 33;
	unsigned char switch_buf[33];
#endif
	int security_retry_count = 0;

	printf("[ATPN]: _AT_WLAN_CONNECT_\n\r");

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPN] Usage : ATPN=<ssid>,<pwd>[,<key_id>,<bssid>,<async>]");
		error_no = 1;
		goto exit;
	}

	if (connect_async) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPN] Async wifi connect haven't finished");
		error_no = 8;
		goto exit;
	}

	argc = parse_param(arg, argv);
	if ((argc < 2) || (argc > 6)) {
		//at_printf("\r\n[ATPN] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	if ((wifi_mode_new != RTW_MODE_STA) && (wifi_mode_new != RTW_MODE_STA_AP)) {
		//at_printf("\r\n[ATPN] ERROR : wifi mode error");
		error_no = 5;
		goto exit;
	}

	//SSID
	if (argv[1] != NULL) {
		strncpy((char *)wifi.ssid.val, (char *)argv[1], sizeof(wifi.ssid.val));
		wifi.ssid.len = strlen((char *)argv[1]);
	} else {
		//at_printf("\r\n[ATPN] ERROR : SSID can't be Empty");
		error_no = 2;
		goto exit;
	}
	wifi.security_type = RTW_SECURITY_OPEN;

	//PASSWORD
	if (argv[2] != NULL) {
		int pwd_len = strlen(argv[2]);
		if (pwd_len > 64 || (pwd_len < 8 && pwd_len != 5)) {
			//at_printf("\r\n[ATPN] ERROR : PASSWORD format error");
			error_no = 2;
			goto exit;
		}
		strncpy((char *)password, (char *)argv[2], sizeof(password));
		wifi.password = password;
		wifi.password_len = strlen((char *)argv[2]);
		wifi.security_type = RTW_SECURITY_WPA2_AES_PSK;
	}

	//KEYID
	if (argv[3] != NULL) {
		if ((strlen((const char *)argv[3]) != 1) || (*(char *)argv[3] < '0' || *(char *)argv[3] > '3')) {
			//at_printf("\r\n[ATPN] ERROR : Wrong WEP key id. Must be one of 0,1,2, or 3");
			error_no = 2;
			goto exit;
		}
		wifi.key_id = atoi((const char *)(argv[3]));
		wifi.security_type = RTW_SECURITY_WEP_PSK;
	}

	//BSSID
	if (argv[4] != NULL) {
		if (strlen(argv[4]) != 12) {
			//at_printf("\r\n[ATPN] ERROR : BSSID format error");
			error_no = 2;
			goto exit;
		}
		for (i = 0, j = 0; i < ETH_ALEN; i++, j += 2) {
			wifi.bssid.octet[i] = key_2char2num(argv[4][j], argv[4][j + 1]);
			g_assoc_by_bssid = 1;
		}
	}

	if (argv[5] != NULL) {
		async = atoi((const char *)(argv[5]));
		if (async != 0 && async != 1) {
			//at_printf("\r\n[ATPB] ERROR : parameter must be 0 or 1");
			error_no = 2;
			goto exit;
		}
	}
	//Check if in AP mode
	wifi_get_setting(WLAN0_IDX, &setting);
	if (setting.mode == RTW_MODE_AP) {
#if CONFIG_LWIP_LAYER
		dhcps_deinit();
#endif
#if (defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8735B)) && (defined(CONFIG_BT) && CONFIG_BT)
		if (wifi_set_mode(RTW_MODE_STA) < 0) {
			//at_printf("\r\n[ATPN] ERROR: Wifi on failed");
			error_no = 3;
			goto exit;
		}
#else
		wifi_off();
		vTaskDelay(20);
		if (wifi_on(RTW_MODE_STA) < 0) {
			//at_printf("\r\n[ATPN] ERROR: Wifi on failed");
			error_no = 3;
			goto exit;
		}
#endif
	}

	/************************************************************
	*    Get security mode from scan list, if it's WEP and key_id isn't set by user,
	*    system will use default key_id = 0
	************************************************************/
	while (1) {
		if (_get_ap_security_mode((char *)wifi.ssid.val, &wifi.security_type, &connect_channel)) {
			break;
		}
		security_retry_count++;

		memset(&switch_buf, 0x00, switch_buflen);
		//fail 3 times then try UTF-8
		if (security_retry_count == 3)
#if ATCMD_VER == ATVER_2
		{
			if (is_str_utf8(wifi.ssid.val)) {
				AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_INFO,
						   "\r\n[ATPN] Switch to GBK to scan again");
				rc = SwitchToGbk(wifi.ssid.val, wifi.ssid.len, (unsigned char *)&switch_buf, &switch_buflen);
			} else {
				AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_INFO,
						   "\r\n[ATPN] Switch to UTF-8 to scan again");
				rc = SwithToUtf_8(wifi.ssid.val, wifi.ssid.len, (unsigned char *)&switch_buf, &switch_buflen);
			}

			if (rc == 0) {
				strncpy((char *)wifi.ssid.val, (char *)switch_buf, switch_buflen);
				wifi.ssid.len = (switch_buflen > 32) ? 32 : switch_buflen;
			} else {
				error_no = 2;
				goto exit;
			}
		}
		if (security_retry_count >= 6)
#endif
		{
			printf("Can't get AP security mode and channel.\n");
			error_no = 6;
			goto exit;
		}
	}

	//the keyID may be not set for WEP which may be confued with WPA2
	if (wifi.security_type == RTW_SECURITY_WEP_PSK || wifi.security_type == RTW_SECURITY_WEP_SHARED) {
		wifi.key_id = (wifi.key_id < 0 || wifi.key_id > 3) ? 0 : wifi.key_id;
	}

	if (wifi.security_type == RTW_SECURITY_OPEN && wifi.password_len != 0) {
		//at_printf("\r\n[ATPN] ERROR : AP security mode is open, no password is required");
		error_no = 2;
		goto exit;
	}

	if (connect_channel > 0 && connect_channel < 14) {
		wifi.channel = connect_channel;
	}

	if (g_assoc_by_bssid == 0) {
		scan_and_sort();
	}

	wifi_unreg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl);

	if (async) {
		connect_async = 1;
		if (xTaskCreate(connect_thread, ((const char *)"connect"), 512, NULL, tskIDLE_PRIORITY + 3 + PRIORITIE_OFFSET, NULL) != pdPASS) {
			printf("\n\r%s xTaskCreate(init_thread) failed", __FUNCTION__);
		}
	} else {
		ret = wifi_connect(&wifi, 1);

		if (ret != RTW_SUCCESS) {
			//at_printf("\r\n[ATPN] ERROR: Can't connect to AP");
			error_no = 4;
			goto exit;
		}

#if CONFIG_LWIP_LAYER
		if (dhcp_mode_sta == 2) {
			struct netif *pnetif = &xnetif[0];
			u32 addr = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
			u32 netmask = WIFI_MAKEU32(NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
			u32 gw = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
			LwIP_SetIP(0, addr, netmask, gw);
			dhcps_init(pnetif);
		} else {
			ret = LwIP_DHCP(0, DHCP_START);
			if (ret != DHCP_ADDRESS_ASSIGNED) {
				error_no = 7;
			}
		}
#endif
	}

exit:
	init_wifi_struct();
	if (error_no == 0) {
		wifi_reg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl, NULL);
		at_printf("\r\n[ATPN] OK");
	} else {
		at_printf("\r\n[ATPN] ERROR:%d", error_no);
	}

	return;
}

//ATPH=<mode>,<enable>
void fATPH(void *arg)
{
	int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int mode, enable;

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPH] Usage : ATPH=<mode>,<enable>");
		error_no = 1;
		goto exit;
	}

	argc = parse_param(arg, argv);
	if (argc != 3) {
		//at_printf("\r\n[ATPH] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	if (argv[1] != NULL) {
		mode = atoi((const char *)(argv[1]));
		if (mode != 1 && mode != 2) {
			//at_printf("\r\n[ATPH] ERROR : parameter must be 1 or 2");
			error_no = 2;
			goto exit;
		}
	}

	if (argv[2] != NULL) {
		enable = atoi((const char *)(argv[2]));
		if (enable != 1 && enable != 2) {
			//at_printf("\r\n[ATPH] ERROR : parameter must be 1 or 2");
			error_no = 2;
			goto exit;
		}
		if (mode == 1) {
			dhcp_mode_ap = enable;
		} else if (mode == 2) {
			dhcp_mode_sta = enable;
		}
	}

exit:
	if (error_no == 0) {
		at_printf("\r\n[ATPH] OK");
	} else {
		at_printf("\r\n[ATPH] ERROR:%d", error_no);
	}

	return;

}

//ATPE=<ip>(,<gateway>,<mask>)
void fATPE(void *arg)
{
	int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	unsigned int ip_addr = 0;
	//unsigned char sta_ip[4] = {192,168,3,80}, sta_netmask[4] = {255,255,255,0}, sta_gw[4] = {192,168,3,1};

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPE] Usage : ATPE=<ip>(,<gateway>,<mask>)");
		error_no = 1;
		goto exit;
	}

	argc = parse_param(arg, argv);
	if ((argc > 4) || (argc < 2)) {
		//at_printf("\r\n[ATPE] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	if (argv[1] != NULL) {
		ip_addr = inet_addr(argv[1]);
		sta_ip[0] = (unsigned char) ip_addr & 0xff;
		sta_ip[1] = (unsigned char)(ip_addr >> 8) & 0xff;
		sta_ip[2] = (unsigned char)(ip_addr >> 16) & 0xff;
		sta_ip[3] = (unsigned char)(ip_addr >> 24) & 0xff;
	} else {
		//at_printf("\r\n[ATPE] ERROR : parameter format error");
		error_no = 2;
		goto exit;
	}

	if (argv[2] != NULL) {
		ip_addr = inet_addr(argv[2]);
		sta_gw[0] = (unsigned char) ip_addr & 0xff;
		sta_gw[1] = (unsigned char)(ip_addr >> 8) & 0xff;
		sta_gw[2] = (unsigned char)(ip_addr >> 16) & 0xff;
		sta_gw[3] = (unsigned char)(ip_addr >> 24) & 0xff;
	} else {
		sta_gw[0] = sta_ip[0];
		sta_gw[1] = sta_ip[1];
		sta_gw[2] = sta_ip[2];
		sta_gw[3] = 1;
	}

	if (argv[3] != NULL) {
		ip_addr = inet_addr(argv[3]);
		sta_netmask[0] = (unsigned char) ip_addr & 0xff;
		sta_netmask[1] = (unsigned char)(ip_addr >> 8) & 0xff;
		sta_netmask[2] = (unsigned char)(ip_addr >> 16) & 0xff;
		sta_netmask[3] = (unsigned char)(ip_addr >> 24) & 0xff;
	} else {
		sta_netmask[0] = 255;
		sta_netmask[1] = 255;
		sta_netmask[2] = 255;
		sta_netmask[3] = 0;
	}

exit:
	if (error_no == 0) {
		at_printf("\r\n[ATPE] OK");
	} else {
		at_printf("\r\n[ATPE] ERROR:%d", error_no);
	}

	return;

}

//ATPF=<start_ip>,<end_ip>,<gateway>
void fATPF(void *arg)
{
	int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	unsigned int ip_addr = 0;
	struct ip_addr start_ip, end_ip;

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPF] Usage : ATPF=<start_ip>,<end_ip>,<ip>(,<gateway>,<mask>)");
		error_no = 1;
		goto exit;
	}

	argc = parse_param(arg, argv);
	if ((argc != 4)) {
		//at_printf("\r\n[ATPF] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	if (argv[1] != NULL) {
#if LWIP_VERSION_MAJOR >= 2
		ip_addr_set_ip4_u32(&start_ip, inet_addr(argv[1]));
#else
		start_ip.addr = inet_addr(argv[1]);
#endif
	} else {
		//at_printf("\r\n[ATPF] ERROR : parameter format error");
		error_no = 2;
		goto exit;
	}

	if (argv[2] != NULL) {
#if LWIP_VERSION_MAJOR >= 2
		ip_addr_set_ip4_u32(&end_ip, inet_addr(argv[2]));
#else
		end_ip.addr = inet_addr(argv[2]);
#endif
	} else {
		//at_printf("\r\n[ATPF] ERROR : parameter format error");
		error_no = 2;
		goto exit;
	}

	dhcps_set_addr_pool(1, &start_ip, &end_ip);

	if (argv[3] != NULL) {
		ip_addr = inet_addr(argv[3]);
		ap_ip[0] = (unsigned char) ip_addr & 0xff;
		ap_ip[1] = (unsigned char)(ip_addr >> 8) & 0xff;
		ap_ip[2] = (unsigned char)(ip_addr >> 16) & 0xff;
		ap_ip[3] = (unsigned char)(ip_addr >> 24) & 0xff;
	} else {
		//at_printf("\r\n[ATPF] ERROR : parameter format error");
		error_no = 2;
		goto exit;
	}

	ap_gw[0] = ap_ip[0];
	ap_gw[1] = ap_ip[1];
	ap_gw[2] = ap_ip[2];
	ap_gw[3] = ap_ip[3];

	ap_netmask[0] = 255;
	ap_netmask[1] = 255;
	ap_netmask[2] = 255;
	ap_netmask[3] = 0;

exit:
	if (error_no == 0) {
		at_printf("\r\n[ATPF] OK");
	} else {
		at_printf("\r\n[ATPF] ERROR:%d", error_no);
	}

	return;
}

int atcmd_wifi_read_info_from_flash(u8 *read_data, u32 read_len)
{
	atcmd_update_partition_info(AT_PARTITION_WIFI, AT_PARTITION_READ, read_data, read_len);
	return 0;
}

void atcmd_wifi_write_info_to_flash(rtw_wifi_setting_t *setting, int enable)
{
	struct atcmd_wifi_conf *data_to_flash;
	rtw_wifi_setting_t *old_setting;
	struct psk_info PSK_info;

	flash_t flash;
	u32 channel = 0, i, write_needed = 0;
	u8 index = 0;
	u32 data;

	data_to_flash = (struct atcmd_wifi_conf *)malloc(sizeof(struct atcmd_wifi_conf));

	if (data_to_flash) {
		if (enable) {
			memset((u8 *)data_to_flash, 0, sizeof(struct atcmd_wifi_conf));
			atcmd_update_partition_info(AT_PARTITION_WIFI, AT_PARTITION_READ, (u8 *)data_to_flash, sizeof(struct atcmd_wifi_conf));
			old_setting = &(data_to_flash->setting);
			if (memcmp((u8 *)old_setting, setting, sizeof(rtw_wifi_setting_t))) {
				memcpy(old_setting, setting, sizeof(rtw_wifi_setting_t));
				write_needed = 1;
			}
			if (setting->mode == RTW_MODE_STA || setting->mode == RTW_MODE_STA_AP) {
				struct wlan_fast_reconnect reconn;
				int found = 0;
				/*clean wifi ssid,key and bssid*/
				memset((u8 *)&reconn, 0, sizeof(struct wlan_fast_reconnect));

				channel = setting->channel;

				switch (setting->security_type) {
				case RTW_SECURITY_OPEN:
					rtw_memcpy(reconn.psk_essid, setting->ssid, strlen(setting->ssid));
					reconn.security_type = RTW_SECURITY_OPEN;
					break;
				case RTW_SECURITY_WEP_PSK:
					rtw_memcpy(reconn.psk_essid, setting->ssid, strlen(setting->ssid));
					rtw_memcpy(reconn.psk_passphrase, setting->password, strlen(setting->password));
					reconn.security_type = RTW_SECURITY_WEP_PSK;
					channel |= (setting->key_idx) << 28;
					break;
				case RTW_SECURITY_WPA_TKIP_PSK:
				case RTW_SECURITY_WPA2_AES_PSK:
#ifdef CONFIG_SAE_SUPPORT
				case RTW_SECURITY_WPA3_AES_PSK:
				case RTW_SECURITY_WPA3_GCMP_PSK:
				case RTW_SECURITY_WPA2_WPA3_MIXED:
#endif
					rtw_memset(&PSK_info, 0, sizeof(struct psk_info));
					PSK_info.index = 0;
					wifi_psk_info_get(&PSK_info);
					rtw_memcpy(reconn.psk_essid, PSK_info.psk_essid, sizeof(reconn.psk_essid));
					rtw_memcpy(reconn.psk_passphrase, PSK_info.psk_passphrase, sizeof(reconn.psk_passphrase));
					rtw_memcpy(reconn.wpa_global_PSK, PSK_info.wpa_global_PSK, sizeof(reconn.wpa_global_PSK));

					reconn.security_type = setting->security_type;
					break;
				default:
					break;
				}

				memcpy(&(reconn.channel), &channel, 4);

				if (data_to_flash->reconn_num < 0 || data_to_flash->reconn_num > ATCMD_WIFI_CONN_STORE_MAX_NUM ||
					data_to_flash->reconn_last_index < 0 || data_to_flash->reconn_last_index > ATCMD_WIFI_CONN_STORE_MAX_NUM
				   ) {
					data_to_flash->reconn_num = 0;
					data_to_flash->reconn_last_index = -1;
				}

				reconn.enable = enable;
				for (i = 0; i < data_to_flash->reconn_num; i++) {
					if (memcmp((u8 *)&reconn, (u8 *) & (data_to_flash->reconn[i]), sizeof(struct wlan_fast_reconnect)) == 0) {
						AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ALWAYS,
								   "the same profile found in flash");
						found = 1;
						break;
					}
				}
				if (!found) {
					data_to_flash->reconn_last_index++;
					if (data_to_flash->reconn_last_index >= ATCMD_WIFI_CONN_STORE_MAX_NUM) {
						data_to_flash->reconn_last_index -= ATCMD_WIFI_CONN_STORE_MAX_NUM;
					}
					memcpy((u8 *)&data_to_flash->reconn[data_to_flash->reconn_last_index], (u8 *)&reconn, sizeof(struct wlan_fast_reconnect));
					data_to_flash->reconn_num++;
					if (data_to_flash->reconn_num > ATCMD_WIFI_CONN_STORE_MAX_NUM) {
						data_to_flash->reconn_num = ATCMD_WIFI_CONN_STORE_MAX_NUM;
					}
					write_needed = 1;
				}
			}
			if (write_needed || data_to_flash->auto_enable != enable) {
				data_to_flash->auto_enable = enable;
				atcmd_update_partition_info(AT_PARTITION_WIFI, AT_PARTITION_WRITE, (u8 *)data_to_flash, sizeof(struct atcmd_wifi_conf));
			}
		} else {
			atcmd_update_partition_info(AT_PARTITION_WIFI, AT_PARTITION_ERASE, (u8 *)data_to_flash, sizeof(struct atcmd_wifi_conf));
		}
	}
	if (data_to_flash) {
		free(data_to_flash);
	}
}

int atcmd_wifi_restore_from_flash(void)
{
	flash_t		flash;
	struct atcmd_wifi_conf *data;
	rtw_wifi_setting_t *setting;
	rtw_wifi_setting_t cur_setting = {0};
	struct wlan_fast_reconnect *reconn;
	struct psk_info PSK_info;
	uint32_t	channel;
	char key_id[2] = {0};
	int ret = -1, i;
	int mode;

	rtw_network_info_t wifi = {
		{0},    // ssid
		{0},    // bssid
		0,      // security
		NULL,   // password
		0,      // password len
		-1,      // key id
		0,      // channel
		0      // pscan option
	};

	data = (struct atcmd_wifi_conf *)rtw_zmalloc(sizeof(struct atcmd_wifi_conf));
	if (data) {
		atcmd_update_partition_info(AT_PARTITION_WIFI, AT_PARTITION_READ, (u8 *)data, sizeof(struct atcmd_wifi_conf));
		if (data->auto_enable != 1) {
			goto exit;
		}
		setting = &data->setting;
		if (setting->mode == RTW_MODE_AP || setting->mode == RTW_MODE_STA_AP) {
			//start AP here
			goto exit;
		}

		//Check if in AP mode
		wifi_get_setting(WLAN0_IDX, &cur_setting);
		if (cur_setting.mode == RTW_MODE_AP) {
#if CONFIG_LWIP_LAYER
			dhcps_deinit();
#endif
			wifi_off();
			vTaskDelay(20);
			if (wifi_on(RTW_MODE_STA) < 0) {
				printf("\n\rERROR: Wifi on failed!");
				ret = -1;
				goto exit;
			}
		}

#if CONFIG_AUTO_RECONNECT
		//setup reconnection flag
		wifi_config_autoreconnect(0, 0, 0);
#endif
		int last_index = data->reconn_last_index;
		for (i = 0; i < data->reconn_num; i++) {
			reconn = &data->reconn[last_index];
			last_index ++;
			if (last_index >= ATCMD_WIFI_CONN_STORE_MAX_NUM) {
				last_index -= ATCMD_WIFI_CONN_STORE_MAX_NUM;
			}
			if (reconn->enable != 1) {
				continue;
			}

			channel = reconn->channel;
			snprintf(key_id, sizeof(key_id), "%d", (char)(channel >> 28));
			channel &= 0xff;
			//set fast survey on last channel
			wifi.channel = channel;
			wifi.pscan_option = PSCAN_FAST_SURVEY;
			wifi.security_type = reconn->security_type;

			//SSID
			rtw_memcpy(wifi.ssid.val, reconn->psk_essid, strlen((char const *)reconn->psk_essid));
			wifi.ssid.len = strlen((char const *)reconn->psk_essid);

			switch (reconn->security_type) {
			case RTW_SECURITY_WEP_PSK:
				wifi.password = reconn->psk_passphrase;
				wifi.password_len = strlen((char const *)reconn->psk_passphrase);
				wifi.key_id = atoi((const char *)key_id);
			case RTW_SECURITY_WPA_TKIP_PSK:
			case RTW_SECURITY_WPA2_AES_PSK:
#ifdef CONFIG_SAE_SUPPORT
			case RTW_SECURITY_WPA3_AES_PSK:
			case RTW_SECURITY_WPA3_GCMP_PSK:
			case RTW_SECURITY_WPA2_WPA3_MIXED:
#endif
				wifi.password = reconn->psk_passphrase;
				wifi.password_len = strlen((char const *)reconn->psk_passphrase);
				rtw_memset(&PSK_info, 0, sizeof(struct psk_info));
				PSK_info.index = 0;
				rtw_memcpy(PSK_info.psk_essid, reconn.psk_essid, sizeof(reconn.psk_essid));
				rtw_memcpy(PSK_info.psk_passphrase, reconn.psk_passphrase, sizeof(reconn.psk_passphrase));
				rtw_memcpy(PSK_info.wpa_global_PSK, reconn.wpa_global_PSK, sizeof(reconn.wpa_global_PSK));
				wifi_psk_info_set(&PSK_info);
				break;
			default:
				break;
			}

			ret = wifi_connect(&wifi, 1);
			if (ret == RTW_SUCCESS) {
				LwIP_DHCP(0, DHCP_START);
				ret = 0;
				break;
			}
		}
	}

exit:
	if (ret == 0) {
		wifi_reg_event_handler(WIFI_EVENT_DISCONNECT, atcmd_wifi_disconn_hdl, NULL);
	}
	if (data) {
		rtw_mfree((u8 *)data, sizeof(struct wlan_fast_reconnect));
	}
	return ret;
}

//ATPG=<enable>
void fATPG(void *arg)
{
	int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
//	flash_t flash;
//	struct wlan_fast_reconnect read_data = {0};

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPG] Usage : ATPG=<enable>");
		error_no = 1;
		goto exit;
	}
	argc = parse_param(arg, argv);
	if (argc != 2) {
		//at_printf("\r\n[ATPG] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	//ENABLE FAST CONNECT
	if (argv[1] != NULL) {
#if 0
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_stream_read(&flash, FAST_RECONNECT_DATA, sizeof(struct wlan_fast_reconnect), (u8 *) &read_data);
		read_data.enable = atoi((const char *)(argv[1]));
		if (read_data.enable != 0 && read_data.enable != 1) {
			//at_printf("\r\n[ATPG] ERROR : parameter must be 0 or 1");
			error_no = 2;
			device_mutex_unlock(RT_DEV_LOCK_FLASH);
			goto exit;
		}
		flash_erase_sector(&flash, FAST_RECONNECT_DATA);
		flash_stream_write(&flash, FAST_RECONNECT_DATA, sizeof(struct wlan_fast_reconnect), (u8 *) &read_data);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
#else
		rtw_wifi_setting_t setting;
		int enable = atoi((const char *)(argv[1]));
		if (enable != 0 && enable != 1) {
			error_no = 2;
			goto exit;
		}
		if (enable == 1) {
			if (wifi_get_setting(WLAN0_IDX, &setting)) {
				AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
						   "wifi_get_setting fail");
				error_no = 3;
				goto exit;
			}
		}
		atcmd_wifi_write_info_to_flash(&setting, enable);
#endif
	}

exit:
	if (error_no == 0) {
		at_printf("\r\n[ATPG] OK");
	} else {
		at_printf("\r\n[ATPG] ERROR:%d", error_no);
	}

	return;
}

void fATPM(void *arg)
{
	return;

}

//ATPW=<mode>
void fATPW(void *arg)
{
	int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};

	if (!arg) {
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
				   "\r\n[ATPW] Usage : ATPW=<mode>");
		error_no = 1;
		goto exit;
	}

	argc = parse_param(arg, argv);
	if (argc != 2) {
		//at_printf("\r\n[ATPW] ERROR : command format error");
		error_no = 1;
		goto exit;
	}

	if (argv[1] != NULL) {
		wifi_mode_new = atoi((const char *)(argv[1]));
		if ((wifi_mode_new != RTW_MODE_STA) && (wifi_mode_new != RTW_MODE_AP) && (wifi_mode_new != RTW_MODE_STA_AP)) {
			//at_printf("\r\n[ATPW] ERROR : parameter must be 1 , 2 or 3");
			error_no = 2;
		}
	}

exit:
	if (error_no == 0) {
		at_printf("\r\n[ATPW] OK");
	} else {
		at_printf("\r\n[ATPW] ERROR:%d", error_no);
	}

	return;
}

void print_wlan_help(void *arg)
{
	at_printf("\r\nWLAN AT COMMAND SET:");
	at_printf("\r\n==============================");
	at_printf("\r\n1. Wlan Scan for Network Access Point");
	at_printf("\r\n   # ATWS");
	at_printf("\r\n2. Connect to an AES AP");
	at_printf("\r\n   # ATPN=<ssid>,<pwd>,<key_id>(,<bssid>)");
	at_printf("\r\n3. Create an AES AP");
	at_printf("\r\n   # ATPA=<ssid>,<pwd>,<chl>,<hidden>");
}

#endif // end of #if ATCMD_VER == ATVER_1

#endif // end of #if CONFIG_WLAN

#if CONFIG_LWIP_LAYER
#if ATCMD_VER == ATVER_1
void fATWL(void *arg)
{
	/* To avoid gcc warnings */
	(void) arg;
#if CONFIG_SSL_CLIENT
	int argc;
	char *argv[MAX_ARGC] = {0};
	printf("[ATWL]: _AT_WLAN_SSL_CLIENT_\n\r");
	argv[0] = (char *)"ssl_client";
	if (!arg) {
		printf("ATWL=SSL_SERVER_HOST\n\r");
		return;
	}
	if ((argc = parse_param(arg, argv)) > 1) {
		if (argc != 2 && argc != 3) {
			printf("ATWL=SSL_SERVER_HOST\n\r");
			return;
		}

		cmd_ssl_client(argc, argv);
	}
#else
	printf("Please set CONFIG_SSL_CLIENT 1 in platform_opts.h to enable ATWL command\n");
#endif
}

void fATWI(void *arg)
{
	int argc;
	char *argv[MAX_ARGC] = {0};

	printf("[ATWI]: _AT_WLAN_PING_TEST_\n\r");

	if (!arg) {
		printf("\n\r[ATWI] Usage: ATWI=[host],[options]\n");
		printf("\n\r       stop      Terminate ping \n");
		printf("  \r     -t    #   Ping the specified host until stopped\n");
		printf("  \r     -n    #   Number of echo requests to send (default 4 times)\n");
		printf("  \r     -l    #   Send buffer size (default 32 bytes)\n");
		printf("\n\r   Example:\n");
		printf("  \r     ATWI=192.168.1.2,-n,100,-l,5000\n");
		return;
	}

	argv[0] = (char *)"ping";

	if ((argc = parse_param(arg, argv)) > 1) {
		cmd_ping(argc, argv);
	}
}

/*
 * To aviod compile error when cmd_iperf3 is not implemented
 */
_WEAK void cmd_iperf3(int argc, char **argv)

{
	/* To avoid gcc warnings */
	(void) argc;
	(void) argv;
	printf(" iperf3 is not compiled \n");
}

void fATWT(void *arg)
{
#if CONFIG_BSD_TCP
	int argc;
	char *argv[MAX_ARGC] = {0};

	if (!arg) {
		printf("\n\r[ATWT] iperf3 Usage: More Usage: ATWT=-help\n\n");

		printf("\n\r[ATWT] iperf1 Usage: ATWT=[-s|-c,host|stop],[options]\n");
		printf("\n\r[ATWT] Usage: ATWT=[-s|-c,host|stop],[options]\n");
		printf("\n\r   Client/Server:\n");
		printf("  \r     stop           terminate client & server\n");
		printf("  \r     -i    #        seconds between periodic bandwidth reports\n");
		printf("  \r     -l    #        length of buffer to read or write (default 1460 Bytes)\n");
		printf("  \r     -p    #        server port to listen on/connect to (default 5001)\n");
		printf("\n\r   Server specific:\n");
		printf("  \r     -s             run in server mode\n");
		printf("\n\r   Client specific:\n");
		printf("  \r     -c    <host>   run in client mode, connecting to <host>\n");
		printf("  \r     -d             do a bidirectional test simultaneously\n");
		printf("  \r     -t    #        time in seconds to transmit for (default 10 secs)\n");
		printf("  \r     -n    #[KM]    number of bytes to transmit (instead of -t)\n");
		printf("\n\r   Example:\n");
		printf("  \r     ATWT=-s,-p,5002\n");
		printf("  \r     ATWT=-c,192.168.1.2,-t,100,-p,5002\n");
		return;
	}

	char *body = (char *) malloc(strlen(arg) + 1);
	memset(body, 0, strlen(arg) + 1);
	memcpy(body, arg, strlen(arg));

	char delims[] = ",";
	char *version = NULL;
	version = strtok(body, delims);
	argv[0] = (char *)"iperf3";

	if ((strlen(version) == strlen("iperf3")) && (memcmp(version, argv[0], strlen(argv[0])) == 0)) {
		printf("[ATWT]: _AT_WLAN_IPERF3_TEST_\n\r");

		if ((argc = parse_param((char *)arg + strlen(argv[0]) + 1, argv)) > 1) {
			cmd_iperf3(argc, argv);
		} else {
			printf("\n\r[ATWT] More Usage: ATWT=-help\n");
		}
	} else {
		printf("[ATWT]: _AT_WLAN_IPERF1_TCP_TEST_\n\r");
		argv[0] = (char *)"tcp";
		if ((argc = parse_param(arg, argv)) > 1) {
#if IPERF_OLD_EN
			cmd_tcp(argc, argv);
#else
			cmd_iperf(argc, argv);
#endif
		}
	}
	free(body);
#else
	printf("Please set CONFIG_BSD_TCP 1 in platform_opts.h to enable ATWT command\n");
#endif
}

void fATWU(void *arg)
{
#if CONFIG_BSD_TCP
	int argc;
	char *argv[MAX_ARGC] = {0};

	printf("[ATWU]: _AT_WLAN_UDP_TEST_\n\r");

	if (!arg) {
		printf("\n\r[ATWU] Usage: ATWU=[-s|-c,host|stop][options]\n");
		printf("\n\r   Client/Server:\n");
		printf("  \r     stop           terminate client & server\n");
		printf("  \r     -i    #        seconds between periodic bandwidth reports\n");
		printf("  \r     -l    #        length of buffer to read or write (default 1460 Bytes)\n");
		printf("  \r     -p    #        server port to listen on/connect to (default 5001)\n");
		printf("\n\r   Server specific:\n");
		printf("  \r     -s             run in server mode\n");
		printf("\n\r   Client specific:\n");
		printf("  \r     -b    #[KM]    for UDP, bandwidth to send at in bits/sec (default 1 Mbit/sec)\n");
		printf("  \r     -c    <host>   run in client mode, connecting to <host>\n");
		printf("  \r     -d             do a bidirectional test simultaneously\n");
		printf("  \r     -t    #        time in seconds to transmit for (default 10 secs)\n");
		printf("  \r     -n    #[KM]    number of bytes to transmit (instead of -t)\n");
		printf("  \r     -S    #        set the IP 'type of service'\n");
		printf("\n\r   Example:\n");
		printf("  \r     ATWU=-s,-p,5002\n");
		printf("  \r     ATWU=-c,192.168.1.2,-t,100,-p,5002\n");
		return;
	}

	argv[0] = (char *)"udp";

	if ((argc = parse_param(arg, argv)) > 1) {
#if IPERF_OLD_EN
		cmd_udp(argc, argv);
#else
		cmd_iperf(argc, argv);
#endif
	}
#else
	printf("Please set CONFIG_BSD_TCP 1 in platform_opts.h to enable ATWU command\n");
#endif
}
#elif ATCMD_VER == ATVER_2 // uart at command
//move to atcmd_lwip.c
#endif
#endif
log_item_t at_wifi_items[ ] = {
#if ATCMD_VER == ATVER_1
#if CONFIG_LWIP_LAYER
	{"ATWL", fATWL, {NULL, NULL}},
	{"ATWI", fATWI, {NULL, NULL}},
	{"ATWT", fATWT, {NULL, NULL}},
	{"ATWU", fATWU, {NULL, NULL}},
#endif
	{"ATPE", fATPE, {NULL, NULL}}, // set static IP for STA
#if WIFI_LOGO_CERTIFICATION_CONFIG
#ifdef CONFIG_SAE_SUPPORT
	{"ATGP", fATWGRP,}, // set SAE group
#endif
	{"ATPM", fATWPMK,},// enable pmk
#ifdef CONFIG_IEEE80211W
	{"ATMF", fATWPMF, {NULL, NULL}},
#endif
#endif // WIFI_LOGO_CERTIFICATION_CONFIG
#if CONFIG_WLAN
	{"ATW0", fATW0, {NULL, NULL}},
	{"ATW1", fATW1, {NULL, NULL}},
	{"ATW2", fATW2, {NULL, NULL}},
	{"ATW3", fATW3, {NULL, NULL}},
	{"ATW4", fATW4, {NULL, NULL}},
	{"ATW5", fATW5, {NULL, NULL}},
	{"ATW6", fATW6, {NULL, NULL}},
	{"ATW8", fATW8, {NULL, NULL}},
	{"ATWf", fATWf, {NULL, NULL}},
	{"ATWd", fATWd, {NULL, NULL}},
	{"ATWr", fATWr, {NULL, NULL}},
#ifdef CONFIG_FPGA
	{"ATW7", fATW7, {NULL, NULL}},
#endif
	{"ATWA", fATWA, {NULL, NULL}},
#ifdef  CONFIG_CONCURRENT_MODE
	{"ATWB", fATWB, {NULL, NULL}},
	{"ATWa", fATWa, {NULL, NULL}},
#endif
	{"ATWC", fATWC, {NULL, NULL}},
	{"ATWD", fATWD, {NULL, NULL}},
	{"ATWP", fATWP, {NULL, NULL}},
	{"ATWR", fATWR, {NULL, NULL}},
	{"ATWS", fATWS, {NULL, NULL}},
#ifdef WIFI_PERFORMANCE_MONITOR
	{"ATWm", fATWm,},
#endif
#if SCAN_WITH_SSID
	{"ATWs", fATWs,},
#endif
#ifdef CONFIG_PROMISC
	{"ATWM", fATWM, {NULL, NULL}},
#endif
	{"ATWZ", fATWZ, {NULL, NULL}},

#if CONFIG_OTA_UPDATE
	{"ATWO", fATWO,},
#endif

#if defined(CONFIG_INCLUDE_SIMPLE_CONFIG) && (CONFIG_INCLUDE_SIMPLE_CONFIG)
	{"ATWQ", fATWQ, {NULL, NULL}},
#endif
#if defined(CONFIG_INCLUDE_DPP_CONFIG) && (CONFIG_INCLUDE_DPP_CONFIG)
	{"ATWq", fATWq,},
#endif
#ifdef CONFIG_WPS
	{"ATWW", fATWW, {NULL, NULL}},
	{"ATWw", fATWw, {NULL, NULL}}, //wps registrar for softap
#if CONFIG_ENABLE_P2P
	{"ATWG", fATWG,},  //p2p start
	{"ATWH", fATWH,},  //p2p stop
	{"ATWJ", fATWJ,},  //p2p connect
	{"ATWK", fATWK,},  //p2p disconnect
	{"ATWN", fATWN,},  //p2p info
	{"ATWF", fATWF,},  //p2p find
	{"ATWg", fATWg,},  //p2p auto go start
#endif
#endif

#if CONFIG_AIRKISS
	{"ATWX", fATWX},
#endif
	{"ATWY", fATWY, {NULL, NULL}},
	{"ATW?", fATWx, {NULL, NULL}},
	{"ATW+ABC", fATWx, {NULL, NULL}},
	{"ATXP", fATXP, {NULL, NULL}},
#ifdef CONFIG_RTK_MESH
	{"ATW+", fATW_mesh},
	{"ATW7", fATW7},
	{"ATW8", fATW8},
	{"ATW9", fATW9},
#endif
#endif
#elif ATCMD_VER == ATVER_2 // uart at command
#if CONFIG_WLAN
	{"ATPA", fATPA,}, // set AP
	{"ATPN", fATPN,}, // connect to Network
	{"ATPH", fATPH,}, // set DHCP mode
	{"ATPE", fATPE,}, // set static IP for STA
	{"ATPF", fATPF,}, // set DHCP rule for AP
	{"ATPG", fATPG,}, // set auto connect
	{"ATPW", fATPW,}, // set Wifi mode
	{"ATWD", fATWD,},
	{"ATWS", fATWS,},
	{"ATW?", fATWx,},
#if defined(CONFIG_INCLUDE_SIMPLE_CONFIG) && CONFIG_INCLUDE_SIMPLE_CONFIG
	{"ATWQ", fATWQ,},
#endif // #if (CONFIG_INCLUDE_SIMPLE_CONFIG)
#endif // #if CONFIG_WLAN
#endif // end of #if ATCMD_VER == ATVER_1
};

#if ATCMD_VER == ATVER_2
void print_wifi_at(void *arg)
{
	int index;
	int cmd_len = 0;

	cmd_len = sizeof(at_wifi_items) / sizeof(at_wifi_items[0]);
	for (index = 0; index < cmd_len; index++) {
		at_printf("\r\n%s", at_wifi_items[index].log_cmd);
	}
}
#endif

void at_wifi_init(void)
{
#if CONFIG_WLAN
	init_wifi_struct();
#endif
	log_service_add_table(at_wifi_items, sizeof(at_wifi_items) / sizeof(at_wifi_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_wifi_init);
#endif
