/******************************************************************************
 *
 * Copyright(c) 2007 - 2015 Realtek Corporation. All rights reserved.
 *
 *
 ******************************************************************************/

/** @file

This example demonstrate how to implement wifi fast reconnection
**/
#include <platform_opts.h>
#include <wifi_fast_connect.h>
#include <wifi_conf.h>

#include "FreeRTOS.h"
#include <task.h>
#include <platform_stdlib.h>
#include "osdep_service.h"
#include "flash_api.h"
#include "device_lock.h"
#if CONFIG_LWIP_LAYER
#include <lwip_netconf.h>
#include "system_data_api.h"
extern struct netif xnetif[NET_IF_NUM];
#endif

#if defined(CONFIG_FAST_DHCP) && CONFIG_FAST_DHCP
uint32_t offer_ip = 0;
uint32_t server_ip = 0;
#endif

#define WIFI_CANDIDATE_CONNECTION 0

#if (WIFI_CANDIDATE_CONNECTION == 1)
#define WIFI_RETRYCOUNT 12
#define WIFI_FAST_SCAN_RETRYCOUNT 9
#define WIFI_RETRYCOUNT_CANDIACATE 8
#else
#define WIFI_RETRYCOUNT 5
#endif

#define WIFI_FAST_CON_PARTION_SIZE 0x400
#define TOTAL_PARTION_SIZE 0x1000

#define TABLE_SIZE 256

static const uint32_t crc_table[TABLE_SIZE] = {0x0, 0x4c11db7, 0x9823b6e, 0xd4326d9, 0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f,
											   0x2f8ad6d6, 0x2b4bcb61, 0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
											   0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75, 0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
											   0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039, 0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
											   0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d, 0xd4326d90, 0xd0f37027,
											   0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
											   0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c,
											   0x2e003dc5, 0x2ac12072, 0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x18aeb13, 0x54bf6a4, 0x808d07d, 0xcc9cdca,
											   0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde, 0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
											   0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba, 0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
											   0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6, 0x99a95df3, 0x9d684044,
											   0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
											   0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59,
											   0x608edb80, 0x644fc637, 0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
											   0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53, 0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
											   0x3f9b762c, 0x3b5a6b9b, 0x315d626, 0x7d4cb91, 0xa97ed48, 0xe56f0ff, 0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
											   0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b, 0xd727bbb6, 0xd3e6a601,
											   0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
											   0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad,
											   0x81b02d74, 0x857130c3, 0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
											   0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8, 0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
											   0x18197087, 0x1cd86d30, 0x29f3d35, 0x65e2082, 0xb1d065b, 0xfdc1bec, 0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
											   0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0, 0xd6ad50a5, 0xd26c4d12,
											   0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
											   0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06,
											   0xa6322bdf, 0xa2f33668, 0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
											  };

uint32_t crc32(void *data, uint32_t data_size, uint32_t crc)
{
	unsigned int i, j;
	uint8_t *u8_data = data;

	for (j = 0; j < data_size; j++) {
		i = ((uint32_t)(crc >> 24) ^ (*u8_data)) & 0xFF;
		crc = (crc << 8) ^ crc_table[i];
		u8_data++;
	}
	crc = ~crc;
	return crc;
}

/*
* Usage:
*       wifi connection indication trigger this function to save current
*       wifi profile in flash
*/

int wifi_check_fast_connect_data(struct wlan_fast_reconnect *data)
{
	//Check SSID
	int ret = 0;
	if ((strlen((const char *)data->psk_essid) < 0) || (strlen((const char *)data->psk_essid) > 32)) {
		ret = -1;
		goto exit;
	}

	//Check Password
	if ((strlen((const char *)data->psk_passphrase) < 0) || (strlen((const char *)data->psk_passphrase) > IW_PASSPHRASE_MAX_SIZE)) {
		ret = -1;
		goto exit;
	}

exit:

	return ret;
}

int write_fast_connect_data_to_flash(unsigned int offer_ip, unsigned int server_ip)
{
	/* To avoid gcc warnings */
#if(!defined(CONFIG_FAST_DHCP) || (!CONFIG_FAST_DHCP))
	(void) offer_ip;
	(void) server_ip;
#endif
	struct wlan_fast_reconnect read_data = {0};
	struct wlan_fast_reconnect wifi_data_to_flash = {0};
	rtw_wifi_setting_t setting;
	struct psk_info PSK_info;
	u32 channel = 0;
	int ret = 0;
	int crc = 0;
	/* STEP1: get current connect info from wifi driver*/
	if (wifi_get_setting(WLAN0_IDX, &setting) || setting.mode == RTW_MODE_AP) {
		RTW_API_INFO("\r\n %s():wifi_get_setting fail or ap mode", __func__);
		return RTW_ERROR;
	}

	rtw_memset(&wifi_data_to_flash, 0, sizeof(struct wlan_fast_reconnect));
	channel = (u32)setting.channel;

	u8 bssid[6];
	if (rtw_wx_get_wap(0, bssid) == 0) {
		rtw_memcpy(wifi_data_to_flash.bssid, bssid, 6);
	}

	switch (setting.security_type) {
	case RTW_SECURITY_OPEN:
		rtw_memcpy(wifi_data_to_flash.psk_essid, setting.ssid, strlen((const char *)setting.ssid));
		wifi_data_to_flash.security_type = RTW_SECURITY_OPEN;
		break;
	case RTW_SECURITY_WEP_PSK:
		rtw_memcpy(wifi_data_to_flash.psk_essid, setting.ssid, strlen((const char *)setting.ssid));
		rtw_memcpy(wifi_data_to_flash.psk_passphrase, setting.password, strlen((const char *)setting.password));
		channel |= (setting.key_idx) << 28;
		wifi_data_to_flash.security_type = RTW_SECURITY_WEP_PSK;
		break;
	case RTW_SECURITY_WPA_TKIP_PSK:
	case RTW_SECURITY_WPA_AES_PSK:
	case RTW_SECURITY_WPA_MIXED_PSK:
	case RTW_SECURITY_WPA2_AES_PSK:
	case RTW_SECURITY_WPA2_TKIP_PSK:
	case RTW_SECURITY_WPA2_MIXED_PSK:
	case RTW_SECURITY_WPA_WPA2_TKIP_PSK:
	case RTW_SECURITY_WPA_WPA2_AES_PSK:
	case RTW_SECURITY_WPA_WPA2_MIXED_PSK:
#ifdef CONFIG_SAE_SUPPORT
	case RTW_SECURITY_WPA3_AES_PSK:
	case RTW_SECURITY_WPA2_WPA3_MIXED:
	case RTW_SECURITY_WPA3_GCMP_PSK:
#endif
		rtw_memset(&PSK_info, 0, sizeof(struct psk_info));
		wifi_psk_info_get(&PSK_info);
		rtw_memcpy(wifi_data_to_flash.psk_essid, PSK_info.psk_essid, sizeof(wifi_data_to_flash.psk_essid));
		rtw_memcpy(wifi_data_to_flash.psk_passphrase, PSK_info.psk_passphrase, sizeof(wifi_data_to_flash.psk_passphrase));
		rtw_memcpy(wifi_data_to_flash.wpa_global_PSK, PSK_info.wpa_global_PSK, sizeof(wifi_data_to_flash.wpa_global_PSK));
		wifi_data_to_flash.security_type = setting.security_type;
		break;

	default:
		break;
	}
	rtw_memcpy(&(wifi_data_to_flash.channel), &channel, 4);
#if defined(CONFIG_FAST_DHCP) && CONFIG_FAST_DHCP
	wifi_data_to_flash.offer_ip = offer_ip;
	wifi_data_to_flash.server_ip = server_ip;
#endif

	/* STEP2: get last time fast connect info from flash*/
	memset(&read_data, 0xff, sizeof(struct wlan_fast_reconnect));
	sys_read_wlan_data_from_flash((uint8_t *) &read_data,  sizeof(struct wlan_fast_reconnect));

#if ATCMD_VER == ATVER_2
	struct wlan_fast_reconnect *copy_data = (struct wlan_fast_reconnect *) &wifi_data_to_flash;
	copy_data->enable = read_data.enable;
#endif

	crc = crc32(&wifi_data_to_flash, sizeof(struct wlan_fast_reconnect) - 4, 0);
	wifi_data_to_flash.crc = crc;

	/* STEP3: wirte new connect info to flash if different content: SSID, Passphrase, Channel, Security type*/
	if (memcmp((u8 *) &wifi_data_to_flash, (u8 *) &read_data, sizeof(struct wlan_fast_reconnect)) != 0) {
#if defined(CONFIG_FAST_DHCP) && CONFIG_FAST_DHCP
		printf("\r\n %s():not the same ssid/passphrase/channel/offer_ip, write new profile to flash \n", __func__);
#else
		printf("\r\n %s():not the same ssid/passphrase/channel, write new profile to flash \n", __func__);
#endif
		sys_write_wlan_data_to_flash((uint8_t *)&wifi_data_to_flash, sizeof(struct wlan_fast_reconnect));
	}

	return RTW_SUCCESS;
}

static uint8_t wr_11v_enable = 0;
static uint8_t wr_11v_channel = 0;
static uint8_t wr_11v_bssid[6] = {0};
void wifi_set_11v_ch_bssid(uint8_t channel, uint8_t *bssid)
{
	char empty_bssid[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	if (memcmp(wr_11v_bssid, empty_bssid, 6)) {
		wr_11v_enable = 1;
		memcpy(wr_11v_bssid, bssid, 6);
		wr_11v_channel = channel;
		RTW_API_INFO("[%s] wr_11v_bssid: "MAC_FMT", channel: %d\n\r", __FUNCTION__, MAC_ARG(wr_11v_bssid), channel);
	} else {
		RTW_API_INFO("[%s] bssid: "MAC_FMT", channel: %d\n\r", __FUNCTION__, MAC_ARG(bssid), channel);
	}
}

static uint8_t pno_wr_enable = 0;
static uint8_t pno_wr_channel = 0;
void wifi_set_pno_reconnect_channel(uint8_t channel)
{
	if (channel > 0) {
		pno_wr_enable = 1;
	}
	pno_wr_channel = channel;
}

void wifi_get_pno_disconnect_params(char *ssid, uint8_t *ssid_len, uint8_t *channel)
{
	struct wlan_fast_reconnect *data = (struct wlan_fast_reconnect *)malloc(sizeof(struct wlan_fast_reconnect));
	if (data) {
		memset(data, 0xff, sizeof(struct wlan_fast_reconnect));
		sys_read_wlan_data_from_flash((uint8_t *)data, sizeof(struct wlan_fast_reconnect));

		/* Check whether stored flash profile is empty */
		struct wlan_fast_reconnect *empty_data;
		empty_data = (struct wlan_fast_reconnect *)malloc(sizeof(struct wlan_fast_reconnect));
		if (empty_data) {
			memset(empty_data, 0xff, sizeof(struct wlan_fast_reconnect));
			if (memcmp(empty_data, data, sizeof(struct wlan_fast_reconnect)) == 0) {
				printf("[FAST_CONNECT] Fast connect profile is empty\n");
				free(data);
				free(empty_data);
				return;
			}
			free(empty_data);
		}

		strcpy(ssid, (char *)(data->psk_essid));
		*ssid_len = strlen((char *)(data->psk_essid));
		*channel = data->channel & 0xFF;
		free(data);
	} else {
		printf("[FAST_CONNECT] malloc buf fail\n");
	}
}

/*
* Usage:
*       This function read previous saved wlan profile in flash and execute connection.
*
*/
int wifi_do_fast_connect(void)
{
	struct wlan_fast_reconnect *data;
	uint32_t	channel;
	uint32_t    security_type;
	u8 key_id;
	int ret = 0;
	uint32_t wifi_retry_connect = WIFI_RETRYCOUNT;//For fast wifi connect retry
	rtw_network_info_t wifi = {0};
	struct psk_info PSK_INFO;

#if (WIFI_CANDIDATE_CONNECTION == 1)
	int candidate_en = 0;
	int candidate_channel = 0;
	u8 candidate_bssid[6] = {0x0};
	int second_candidate_bssid_exist = 0;
	u8 second_candidate_bssid[6] = {0x0};
	int second_candidate_channel = 0;
	int third_candidate_bssid_exist = 0;
	u8 third_candidate_bssid[6] = {0x0};
	int third_candidate_channel = 0;
#endif

#if CONFIG_LWIP_LAYER
	netif_set_up(&xnetif[0]);
#endif

#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6
	netif_create_ip6_linklocal_address(&xnetif[0], 1);
#endif
#endif

#if CONFIG_AUTO_RECONNECT
#if (WIFI_CANDIDATE_CONNECTION == 1)
	//setup reconnection flag to avoid candidate connection to influence the current connection
	if (wifi_config_autoreconnect(1, AUTO_RECONNECT_COUNT, 30) < 0) {
		ret = -1;
		goto exit;
	}
#else
	//setup reconnection flag
	if (wifi_config_autoreconnect(1, AUTO_RECONNECT_COUNT, AUTO_RECONNECT_INTERVAL) < 0) {
		ret = -1;
		goto exit;
	}
#endif
#endif
	data = (struct wlan_fast_reconnect *)malloc(sizeof(struct wlan_fast_reconnect));
	if (data) {
		memset(data, 0xff, sizeof(struct wlan_fast_reconnect));
		sys_read_wlan_data_from_flash((uint8_t *)data, sizeof(struct wlan_fast_reconnect));

		/* Check whether stored flash profile is empty */
		struct wlan_fast_reconnect *empty_data;
		empty_data = (struct wlan_fast_reconnect *)malloc(sizeof(struct wlan_fast_reconnect));
		if (empty_data) {
			memset(empty_data, 0xff, sizeof(struct wlan_fast_reconnect));
			if (memcmp(empty_data, data, sizeof(struct wlan_fast_reconnect)) == 0) {
				printf("[FAST_CONNECT] Fast connect profile is empty, abort fast connection\n");
				free(data);
				free(empty_data);
				ret = -1;
				goto exit;
			}
			free(empty_data);
		}

#if (FCS_CRC_CHECK == 1)
		//check fast connection crc
		int crc1;
		crc1 = crc32(data, sizeof(struct wlan_fast_reconnect) - 4, 0);

		if ((crc1 == data->crc) || (data->crc == 0xffffffff) || (data->crc == 0)) {
			//printf("[wifi_do_fast_connect] Check crc ok, and then start fcs\n\r");
		} else {
			printf("[FAST_CONNECT] Check default crc not same, abort fast connection\n");
			free(data);
			ret = -1;
			goto exit;
		}
#endif

		memset(&PSK_INFO, 0, sizeof(struct psk_info));
		rtw_memcpy(PSK_INFO.psk_essid, data->psk_essid, sizeof(data->psk_essid));
		rtw_memcpy(PSK_INFO.psk_passphrase, data->psk_passphrase, sizeof(data->psk_passphrase));
		rtw_memcpy(PSK_INFO.wpa_global_PSK, data->wpa_global_PSK, sizeof(data->wpa_global_PSK));

		if (wifi_check_fast_connect_data(data) < 0) {
			printf("[FAST_CONNECT] Fast connect profile is wrong, abort fast connection\n");
			free(data);
			ret = -1;
			goto exit;
		}

		wifi_psk_info_set(&PSK_INFO);

		if (pno_wr_enable) {
			channel = pno_wr_channel;
			pno_wr_enable = 0;
		} else {
			channel = data->channel;
		}

		if (wr_11v_enable) {
			channel = wr_11v_channel;
			rtw_memcpy(wifi.bssid.octet, wr_11v_bssid, 6);
			RTW_API_INFO("[%s] wr_11v_bssid: "MAC_FMT", wr_11v_channel: %d\n\r", __FUNCTION__, MAC_ARG(wr_11v_bssid), wr_11v_channel);
		}

		key_id = channel >> 28;
		channel &= 0xff;
		security_type = data->security_type;
		//set partial scan for entering to listen beacon quickly

		//Avoid the wrong flash data for fast connnection
		if (channel > 165) {
			channel = 0;
			int password_len = strlen((const char *)PSK_INFO.psk_passphrase);
			if (password_len == 0) {
				security_type = RTW_SECURITY_OPEN;
			} else {
				security_type = RTW_SECURITY_WPA2_AES_PSK;
			}
		}
WIFI_RETRY_LOOP:

#if (WIFI_CANDIDATE_CONNECTION == 1)
		//12 11 10
		if ((wifi_retry_connect <= WIFI_RETRYCOUNT) && (wifi_retry_connect > WIFI_FAST_SCAN_RETRYCOUNT)) {
			printf("[%s] fast_pscan(%d)\n\r", __FUNCTION__, wifi_retry_connect);
			wifi.channel = channel;
			wifi_set_channel(channel);
			wifi.pscan_option = PSCAN_FAST_SURVEY;
		} else {
			if (candidate_en) {
				printf("[%s] candidate_en, retry (%d)\n\r", __FUNCTION__, wifi_retry_connect);
				wifi.channel = candidate_channel;
				wifi_set_channel(candidate_channel);
				wifi.pscan_option = PSCAN_FAST_SURVEY;
				printf("[%s] Using bssid("MAC_FMT") connection\n\r", __FUNCTION__, MAC_ARG(candidate_bssid));
				memcpy(wifi.bssid.octet, candidate_bssid, 6);
			} else {
				printf("[%s] full scan(%d)\n\r", __FUNCTION__, wifi_retry_connect);
				wifi.channel = 0;
				wifi_set_channel(1);
				wifi.pscan_option = 0;
				memset(wifi.bssid.octet, 0, 6);
			}
		}
#else
		wifi.channel = channel;
		wifi_set_channel(channel);
		wifi.pscan_option = PSCAN_FAST_SURVEY;
#endif

		wifi.security_type = security_type;
		//SSID
		strcpy((char *)wifi.ssid.val, (char *)(data->psk_essid));
		wifi.ssid.len = strlen((char *)(data->psk_essid));

		switch (security_type) {
		case RTW_SECURITY_WEP_PSK:
			wifi.password = (unsigned char *)(data->psk_passphrase);
			wifi.password_len = strlen((char *)(data->psk_passphrase));
			wifi.key_id = key_id;
			break;
		case RTW_SECURITY_WPA_TKIP_PSK:
		case RTW_SECURITY_WPA_AES_PSK:
		case RTW_SECURITY_WPA_MIXED_PSK:
		case RTW_SECURITY_WPA2_AES_PSK:
		case RTW_SECURITY_WPA2_TKIP_PSK:
		case RTW_SECURITY_WPA2_MIXED_PSK:
		case RTW_SECURITY_WPA_WPA2_TKIP_PSK:
		case RTW_SECURITY_WPA_WPA2_AES_PSK:
		case RTW_SECURITY_WPA_WPA2_MIXED_PSK:
#ifdef CONFIG_SAE_SUPPORT
		case RTW_SECURITY_WPA3_AES_PSK:
		case RTW_SECURITY_WPA2_WPA3_MIXED:
		case RTW_SECURITY_WPA3_GCMP_PSK:
#endif
			wifi.password = (unsigned char *)(data->psk_passphrase);
			wifi.password_len = strlen((char *)(data->psk_passphrase));
			break;
		default:
			break;
		}

#if defined(CONFIG_FAST_DHCP) && CONFIG_FAST_DHCP
		offer_ip = data->offer_ip;
		server_ip = data->server_ip;
		if (wifi.pscan_option != PSCAN_FAST_SURVEY) {
			offer_ip = 0;
			server_ip = 0;
		}
#endif

		ret = wifi_connect(&wifi, 1);
		if (ret != RTW_SUCCESS) {
			wifi_retry_connect--;
			if ((wifi_retry_connect > 0) && (p_wifi_do_fast_connect != NULL)) {
				/* Add the delay to wait for the _rtw_join_timeout_handler
				 * If there is no this delay, there are some error when rhe AP
				 * send the disassociation frame. It will cause the connection
				 * to be failed at first time after resetting. So keep 300ms delay
				 * here. For the detail about this error, please refer to
				 * [RSWLANDIOT-1954].
				 */
#if (WIFI_CANDIDATE_CONNECTION == 1)
				//  3 full scan connection and each full scan connection will consider two alternative routers
				// 12 11 10 fast scan
				//  9 full scan
				//  8 (connect to second candidate router)
				if (wifi_retry_connect == WIFI_RETRYCOUNT_CANDIACATE) {
					extern int rltk_get_connection_scan_list(wifi_connect_scan_list * connection_scan_list, u8 * bssid);
					u8 connection_bssid[6] = {0x0};
					wifi_connect_scan_list connection_scan_list;
					rltk_get_connection_scan_list(&connection_scan_list, connection_bssid);
					int scan_list_ap_num = connection_scan_list.num;

					for (int i = 0; i < scan_list_ap_num; i++) {
						if (memcmp(connection_bssid, connection_scan_list.bssid[i], 6) && (second_candidate_bssid_exist == 0)) {
							//Find out the second candidate router
							second_candidate_bssid_exist = 1;
							memcpy(second_candidate_bssid, connection_scan_list.bssid[i], 6);
							second_candidate_channel = connection_scan_list.channel[i];
							continue; //try next run
						}
						if (memcmp(connection_bssid, connection_scan_list.bssid[i], 6)
							&& (second_candidate_bssid_exist == 1) && (third_candidate_bssid_exist == 0)) {
							//Find out the third candidate router
							third_candidate_bssid_exist = 1;
							memcpy(third_candidate_bssid, connection_scan_list.bssid[i], 6);
							third_candidate_channel = connection_scan_list.channel[i];
							break;
						}
					}

					printf("[%s] (first run) find out second bssid(%d): "MAC_FMT"; third bssid(%d): "MAC_FMT"\n\r\n\r"
						   , __FUNCTION__, second_candidate_bssid_exist, MAC_ARG(second_candidate_bssid),
						   third_candidate_bssid_exist, MAC_ARG(third_candidate_bssid));

					if (second_candidate_bssid_exist == 1) {
						candidate_en = 1;
						memcpy(candidate_bssid, second_candidate_bssid, 6);
						candidate_channel = second_candidate_channel;
					} else {
						// don't exist second candidate ap, go to full scan again
						wifi_retry_connect = 6;
					}
				}

				// 7 (connect to third candidate router)
				if (wifi_retry_connect == 7) {
					if (third_candidate_bssid_exist == 1) {
						candidate_en = 1;
						memcpy(candidate_bssid, third_candidate_bssid, 6);
						candidate_channel = third_candidate_channel;
					} else {
						// don't exist third candidate ap, go to full scan again
						wifi_retry_connect = 6;
					}
				}

				// 6 full scan
				if (wifi_retry_connect == 6) {
					candidate_en = 0;
					memset(candidate_bssid, 0, 6);
					second_candidate_bssid_exist = 0;
					memset(second_candidate_bssid, 0, 6);
					third_candidate_bssid_exist = 0;
					memset(third_candidate_bssid, 0, 6);
				}

				// 5 (connect to second candidate router)
				if (wifi_retry_connect == 5) {
					extern int rltk_get_connection_scan_list(wifi_connect_scan_list * connection_scan_list, u8 * bssid);
					u8 connection_bssid[6] = {0x0};
					wifi_connect_scan_list connection_scan_list;
					rltk_get_connection_scan_list(&connection_scan_list, connection_bssid);
					int scan_list_ap_num = connection_scan_list.num;
					for (int i = 0; i < scan_list_ap_num; i++) {
						if (memcmp(connection_bssid, connection_scan_list.bssid[i], 6) && (second_candidate_bssid_exist == 0)) {
							//Find out the second candidate router
							second_candidate_bssid_exist = 1;
							memcpy(second_candidate_bssid, connection_scan_list.bssid[i], 6);
							second_candidate_channel = connection_scan_list.channel[i];
							continue; //try next run
						}
						if (memcmp(connection_bssid, connection_scan_list.bssid[i], 6)
							&& (second_candidate_bssid_exist == 1) && (third_candidate_bssid_exist == 0)) {
							//Find out the third candidate router
							third_candidate_bssid_exist = 1;
							memcpy(third_candidate_bssid, connection_scan_list.bssid[i], 6);
							third_candidate_channel = connection_scan_list.channel[i];
							break;
						}
					}

					printf("[%s] (second run) find out second bssid(%d): "MAC_FMT"; third bssid(%d): "MAC_FMT"\n\r\n\r"
						   , __FUNCTION__, second_candidate_bssid_exist, MAC_ARG(second_candidate_bssid),
						   third_candidate_bssid_exist, MAC_ARG(third_candidate_bssid));

					if (second_candidate_bssid_exist == 1) {
						candidate_en = 1;
						memcpy(candidate_bssid, second_candidate_bssid, 6);
						candidate_channel = second_candidate_channel;
					} else {
						// don't exist third candidate ap, go to full scan again
						wifi_retry_connect = 3;
					}
				}

				// 4 (connect to third candidate router)
				if (wifi_retry_connect == 4) {
					if (third_candidate_bssid_exist == 1) {
						candidate_en = 1;
						memcpy(candidate_bssid, third_candidate_bssid, 6);
						candidate_channel = third_candidate_channel;
					} else {
						// don't exist third candidate ap, go to full scan again
						wifi_retry_connect = 3;
					}
				}

				// 3 full scan
				if (wifi_retry_connect == 3) {
					candidate_en = 0;
					memset(candidate_bssid, 0, 6);
					second_candidate_bssid_exist = 0;
					memset(second_candidate_bssid, 0, 6);
					third_candidate_bssid_exist = 0;
					memset(third_candidate_bssid, 0, 6);
				}

				// 2 (connect to second candidate router)
				if (wifi_retry_connect == 2) {
					extern int rltk_get_connection_scan_list(wifi_connect_scan_list * connection_scan_list, u8 * bssid);
					u8 connection_bssid[6] = {0x0};
					wifi_connect_scan_list connection_scan_list;
					rltk_get_connection_scan_list(&connection_scan_list, connection_bssid);
					int scan_list_ap_num = connection_scan_list.num;
					for (int i = 0; i < scan_list_ap_num; i++) {
						if (memcmp(connection_bssid, connection_scan_list.bssid[i], 6) && (second_candidate_bssid_exist == 0)) {
							second_candidate_bssid_exist = 1;
							memcpy(second_candidate_bssid, connection_scan_list.bssid[i], 6);
							second_candidate_channel = connection_scan_list.channel[i];
							continue; //try next run
						}
						if (memcmp(connection_bssid, connection_scan_list.bssid[i], 6)
							&& (second_candidate_bssid_exist == 1) && (third_candidate_bssid_exist == 0)) {
							third_candidate_bssid_exist = 1;
							memcpy(third_candidate_bssid, connection_scan_list.bssid[i], 6);
							third_candidate_channel = connection_scan_list.channel[i];
							break;
						}
					}

					printf("[%s] (third run) find out second bssid(%d): "MAC_FMT"; third bssid(%d): "MAC_FMT"\n\r\n\r"
						   , __FUNCTION__, second_candidate_bssid_exist, MAC_ARG(second_candidate_bssid),
						   third_candidate_bssid_exist, MAC_ARG(third_candidate_bssid));

					if (second_candidate_bssid_exist == 1) {
						candidate_en = 1;
						memcpy(candidate_bssid, second_candidate_bssid, 6);
						candidate_channel = second_candidate_channel;
					} else {
						// don't exist second candidate router, goto exit
						printf("[%s] don't exist second_candidate router, goto exit\n\r", __FUNCTION__);
						candidate_en = 0;
						ret = -1;
						goto exit;
					}
				}

				// 1 (connect to third candidate router)
				if (wifi_retry_connect == 1) {
					if (third_candidate_bssid_exist == 1) {
						candidate_en = 1;
						memcpy(candidate_bssid, third_candidate_bssid, 6);
						candidate_channel = third_candidate_channel;
					} else {
						// don't exist third candidate router, goto exit
						printf("[%s] don't exist third_candidate router, goto exit\n\r", __FUNCTION__);
						candidate_en = 0;
						ret = -1;
						goto exit;
					}
				}
#endif
				vTaskDelay(300);
				printf("wifi retry\r\n");
				goto WIFI_RETRY_LOOP;
			}
		}
#if CONFIG_LWIP_LAYER
		if (ret == RTW_SUCCESS) {
			LwIP_DHCP(0, DHCP_START);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6_DHCP6
			LwIP_DHCP6(0, DHCP6_START);
#endif
#endif
		}
#endif
		free(data);
	}

exit:

#if (WIFI_CANDIDATE_CONNECTION == 1)
	//setup reconnection flag to avoid candidate connection to influence the current connection
	if (wifi_config_autoreconnect(1, AUTO_RECONNECT_COUNT, AUTO_RECONNECT_INTERVAL) < 0) {
		ret = -1;
	}
#endif

	return ret;
}

/*
* Usage:
*       After wifi connected, check if it is the same AP which previously stored in flash.
*       Return 0 means not the same AP or FASH DHCP not enabled, return 1 means the same AP.
*/
int check_is_the_same_ap()
{
	int ret = 0;
#if defined(CONFIG_FAST_DHCP) && CONFIG_FAST_DHCP
	if (p_store_fast_connect_info != NULL) {
		struct wlan_fast_reconnect data;
		rtw_wifi_setting_t setting;

		if (wifi_get_setting(WLAN0_IDX, &setting) || setting.mode == RTW_MODE_AP) {
			RTW_API_INFO("\r\n %s():wifi_get_setting fail or ap mode", __func__);
			return 0;
		}

		memset(&data, 0xff, sizeof(struct wlan_fast_reconnect));
		sys_read_wlan_data_from_flash((uint8_t *)&data, sizeof(struct wlan_fast_reconnect));

		if (strncmp((const char *)data.psk_essid, (const char *)setting.ssid, strlen((char const *)setting.ssid)) == 0) {
			ret = 1;
		} else {
			ret = 0;
		}
	}
#endif
	return ret;
}

int Erase_Fastconnect_data(void)
{
	flash_t flash;

	if (p_wifi_do_fast_connect != NULL) {
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_erase_sector(&flash, FAST_RECONNECT_DATA);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
	}
	return 0;
}

/*
* Usage:
*       config fast connect related function.
*       input param: enable, set to 1 means enable fast connect, set to 0 means disable fast connect
*/
void wifi_fast_connect_enable(u8 enable)
{
	if (enable == 0) {
		p_wifi_do_fast_connect = NULL;
		p_store_fast_connect_info = NULL;
	} else if (enable == 0xff) {
		p_wifi_do_fast_connect = NULL;
	} else {
#if ATCMD_VER == ATVER_2
		struct wlan_fast_reconnect read_data = {0};
		memset(&read_data, 0xff, sizeof(struct wlan_fast_reconnect));
		sys_read_wlan_data_from_flash((uint8_t *)&read_data, sizeof(struct wlan_fast_reconnect));

		if (read_data.enable == 1)
#endif
		{
			// this function will be called after wlan init done to read info from flash and do fast connect
			p_wifi_do_fast_connect = wifi_do_fast_connect;

			// this function will be called after wifi_connection success to store connect info to flash
			p_store_fast_connect_info = write_fast_connect_data_to_flash;
		}
	}
}

/*
* Usage:
*       This function load previous saved ip in flash for fast dhcp.
*
*/
void wifi_fast_connect_load_fast_dhcp(void)
{
#if defined(CONFIG_FAST_DHCP) && CONFIG_FAST_DHCP
	struct wlan_fast_reconnect *data;
	data = (struct wlan_fast_reconnect *)malloc(sizeof(struct wlan_fast_reconnect));
	if (data) {
		memset(data, 0xff, sizeof(struct wlan_fast_reconnect));
		sys_read_wlan_data_from_flash((uint8_t *)data, sizeof(struct wlan_fast_reconnect));

		/* Check whether stored flash profile is empty */
		struct wlan_fast_reconnect *empty_data;
		empty_data = (struct wlan_fast_reconnect *)malloc(sizeof(struct wlan_fast_reconnect));
		if (empty_data) {
			memset(empty_data, 0xff, sizeof(struct wlan_fast_reconnect));
			if (memcmp(empty_data, data, sizeof(struct wlan_fast_reconnect)) == 0) {
				free(data);
				free(empty_data);
				return;
			}
			free(empty_data);
		}

		offer_ip = data->offer_ip;
		server_ip = data->server_ip;
		free(data);
	}
#endif
}
