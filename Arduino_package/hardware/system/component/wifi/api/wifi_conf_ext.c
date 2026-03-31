//----------------------------------------------------------------------------//
//#include <flash/stm32_flash.h>
#if !defined(CONFIG_MBED_ENABLED) && !defined(CONFIG_PLATFOMR_CUSTOMER_RTOS)
#include "main.h"
#if CONFIG_LWIP_LAYER
#include <lwip_netconf.h>
#include <dhcp/dhcps.h>
#endif
#endif
#include <platform_stdlib.h>
#include <wifi_conf.h>
#include <wifi_ind.h>
#include <osdep_service.h>
#include <device_lock.h>

#if (defined(CONFIG_EXAMPLE_UART_ATCMD) && CONFIG_EXAMPLE_UART_ATCMD) || (defined(CONFIG_EXAMPLE_SPI_ATCMD) && CONFIG_EXAMPLE_SPI_ATCMD)
#include "at_cmd/atcmd_wifi.h"
#endif
#if defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_8735B) || defined(CONFIG_PLATFORM_AMEBALITE)
#include "platform_opts_bt.h"
#endif
#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
#include <wifi_wps_config.h>
#endif
#ifdef CONFIG_BT_COEXIST
#include "bt_intf.h"
#endif

#include "power_mode_api.h"

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/
#if CONFIG_AUTO_RECONNECT
struct wifi_autoreconnect_param {
	rtw_security_t security_type;
	char *ssid;
	int ssid_len;
	char *password;
	int password_len;
	int key_id;
};
#endif
/******************************************************
 *               Variables Declarations
 ******************************************************/

#if !defined(CONFIG_MBED_ENABLED)
#if CONFIG_LWIP_LAYER
extern struct netif xnetif[NET_IF_NUM];
#endif
#endif
#if CONFIG_AUTO_RECONNECT
extern p_wlan_autoreconnect_hdl_t p_wlan_autoreconnect_hdl;
#endif

#if defined(ATCMD_VER) && defined(ATCMD_VER) && ATCMD_VER == ATVER_2
extern unsigned char dhcp_mode_sta;
#endif

/******************************************************
 *               Variables Declarations
 ******************************************************/
#if defined(CONFIG_MBED_ENABLED)
rtw_mode_t wifi_mode = RTW_MODE_STA;
#endif
extern rtw_mode_t wifi_mode;

void *param_indicator;
struct task_struct wifi_autoreconnect_task;

/******************************************************
 *               Variables Definitions
 ******************************************************/

/*NETMASK*/
#ifndef NETMASK_ADDR0
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0
#endif

/*Gateway Address*/
#ifndef GW_ADDR0
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   1
#define GW_ADDR3   1
#endif

/******************************************************
 *               Function Definitions
 ******************************************************/

#if CONFIG_WLAN

//----------------------------------------------------------------------------//
int wifi_get_mac_address(rtw_mac_t *mac)
{
	return rtw_ex_read_mac(WLAN0_IDX, mac);
}

//----------------------------------------------------------------------------//
int wifi_btcoex_set_ble_scan_duty(u8 duty)
{
	return rltk_coex_set_ble_scan_duty(duty);
}

//----------------------------------------------------------------------------//
int wifi_get_associated_client_list(void *client_list_buffer, uint16_t buffer_length)
{
	/* To avoid gcc warnings */
	(void) buffer_length;

	unsigned char wlan_idx = WLAN0_IDX;
	int ret = 0;

	if (wifi_mode == RTW_MODE_STA_AP) {
		wlan_idx = WLAN1_IDX;
	}

	ret = rtw_ex_get_client_list(wlan_idx, (rtw_maclist_t *)client_list_buffer);

	return ret;
}

//----------------------------------------------------------------------------//
int wifi_get_setting(unsigned char wlan_idx, rtw_wifi_setting_t *psetting)
{
	int ret = 0;
	int mode = 0;
	unsigned short security = 0;
	unsigned int auth_type = 0;

	if (wlan_idx > WLAN1_IDX) {
		return RTW_ERROR;
	}

	memset(psetting, 0, sizeof(rtw_wifi_setting_t));
	if (rtw_wx_get_mode(wlan_idx, &mode) < 0) {
		ret = -1;
	}

	switch (mode) {
	case RTW_MODE_MASTER:
		psetting->mode = RTW_MODE_AP;
		break;
	case RTW_MODE_INFRA:
	default:
		psetting->mode = RTW_MODE_STA;
		break;
		//default:
		//RTW_API_INFO("\r\n%s(): Unknown mode %d\n", __func__, mode);
		//break;
	}

	if (rtw_wx_get_wap(wlan_idx, psetting->bssid) < 0) {
		ret = -1;
	}
	if (rtw_wx_get_essid(wlan_idx, psetting->ssid) < 0) {
		ret = -1;
	}
	if (rtw_wx_get_freq(wlan_idx, &psetting->channel) < 0) {
		ret = -1;
	}
	if (rtw_wx_get_enc_ext(wlan_idx, &security, &psetting->key_idx, psetting->password) < 0) {
		ret = -1;
	}

	switch (security) {
	case RTW_ENCODE_ALG_NONE:
		psetting->security_type = RTW_SECURITY_OPEN;
		break;
	case RTW_ENCODE_ALG_WEP:
		psetting->security_type = RTW_SECURITY_WEP_PSK;
		break;
	case RTW_ENCODE_ALG_TKIP:
		if (rtw_wx_get_auth_type(wlan_idx, &auth_type) < 0) {
			ret = -1;
		}
		if (auth_type == WPA_SECURITY) {
			psetting->security_type = RTW_SECURITY_WPA_TKIP_PSK;
		} else if (auth_type == WPA2_SECURITY) {
			psetting->security_type = RTW_SECURITY_WPA2_TKIP_PSK;
		}
		break;
	case RTW_ENCODE_ALG_CCMP:
		if (rtw_wx_get_auth_type(wlan_idx, &auth_type) < 0) {
			ret = -1;
		}
		if (auth_type == WPA_SECURITY) {
			psetting->security_type = RTW_SECURITY_WPA_AES_PSK;
		} else if (auth_type == WPA2_SECURITY) {
			psetting->security_type = RTW_SECURITY_WPA2_AES_PSK;
		} else if (auth_type == WPA3_SECURITY) {
			psetting->security_type = RTW_SECURITY_WPA3_AES_PSK;
		}
		break;
	case RTW_ENCODE_ALG_GCMP:
		psetting->security_type = RTW_SECURITY_WPA3_GCMP_PSK;
		break;
	default:
		break;
	}

	if (security == RTW_ENCODE_ALG_TKIP || security == RTW_ENCODE_ALG_CCMP || security == RTW_ENCODE_ALG_GCMP)
		if (rtw_wx_get_passphrase(wlan_idx, psetting->password) < 0) {
			ret = -1;
		}

	return ret;

}

int wifi_fetch_phy_statistic(rtw_phy_statistics_t *phy_statistic)
{
	return rtw_wx_get_phy_statistic(phy_statistic);
}

int wifi_get_ccmp_key(unsigned char *uncst_key, unsigned char *group_key)
{
	return rltk_wlan_get_ccmp_key(uncst_key, group_key);
}
//----------------------------------------------------------------------------//
int wifi_set_powersave_mode(u8 ips_mode, u8 lps_mode)
{
	int ret = RTW_SUCCESS;

	if ((ips_mode >= IPS_MODE_NUM) && (lps_mode >= LPS_MODE_NUM)) {
		printf("invalid powersave mode\n");
		return RTW_ERROR;
	}

	if (ips_mode < IPS_MODE_NUM) {
		ret = rtw_pm_set(RTW_PM_OPTION_IPS_MODE, &ips_mode);
	}
	if (lps_mode < LPS_MODE_NUM) {
		ret = rtw_pm_set(RTW_PM_OPTION_LPS_MODE, &lps_mode);
	}
	return ret;
}

//----------------------------------------------------------------------------//

int wifi_set_mfp_support(unsigned char value)
{
	return rtw_wx_set_mfp_support(WLAN0_IDX, value);
}

int wifi_set_group_id(unsigned char value)
{
#ifdef CONFIG_SAE_SUPPORT
	return rtw_wx_set_group_id(WLAN0_IDX, value);
#else
	return RTW_SUCCESS;
#endif
}

int wifi_set_network_mode(rtw_network_mode_t mode)
{
	if ((mode == RTW_NETWORK_B) || (mode == RTW_NETWORK_BG) || (mode == RTW_NETWORK_BGN)) {
		return rltk_wlan_wireless_mode((unsigned char) mode);
	}

	return RTW_ERROR;
}

#if WIFI_LOGO_CERTIFICATION
int backup_candidate_bssid_exist = 0;
u8 backup_connection_bssid[6] = {0x0};
u8 backup_second_candidate_bssid[6] = {0x0};
int backup_second_candidate_channel = 0;
#endif
#if CONFIG_ENABLE_WPS
char wps_profile_ssid[33] = {0};
char wps_profile_password[65] = {0};
#endif

static void _wifi_autoreconnect_thread(void *param)
{
#if CONFIG_AUTO_RECONNECT
#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif
	int ret = RTW_ERROR;
	struct wifi_autoreconnect_param *reconnect_info = (struct wifi_autoreconnect_param *) param;
	rtw_network_info_t connect_param = {0};
	unsigned char is_wpa3_disable = 0, is_pmk_disable = 0;
	if (reconnect_info->ssid_len) {
		rtw_memcpy(connect_param.ssid.val, reconnect_info->ssid, reconnect_info->ssid_len);
		connect_param.ssid.len = reconnect_info->ssid_len;
	}
	connect_param.password = (unsigned char *)reconnect_info->password;
	connect_param.password_len = reconnect_info->password_len;
	connect_param.security_type = reconnect_info->security_type;
	connect_param.key_id = reconnect_info->key_id;

#if CONFIG_ENABLE_WPS
	if ((strncmp(wps_profile_ssid, reconnect_info->ssid, reconnect_info->ssid_len) == 0) &&
		(strncmp(wps_profile_password, reconnect_info->password, reconnect_info->password_len) == 0) &&
		(wifi_user_config.rtw_cmd_tsk_spt_wap3 == ENABLE)) {
		wifi_user_config.rtw_cmd_tsk_spt_wap3 = DISABLE;
		is_wpa3_disable = 1;
	}
#endif
	if (reconnect_info->security_type == RTW_SECURITY_WPA3_AES_PSK) {
		wifi_set_pmk_cache_enable(0);
		is_pmk_disable = 1;
	}

	RTW_API_INFO("\n\rauto reconnect ...\n");
#if WIFI_LOGO_CERTIFICATION
	//
	int reconnect_cnt = 0;
	extern int rltk_get_reconnect_cnt(void);
	reconnect_cnt = rltk_get_reconnect_cnt();
	RTW_API_INFO("\n\rauto reconnect(%d) ...\n", reconnect_cnt);
	if (reconnect_cnt < 3) {
		extern int rltk_get_connection_scan_list(wifi_connect_scan_list * connection_scan_list, u8 * bssid);
		wifi_connect_scan_list connection_scan_list;
		rltk_get_connection_scan_list(&connection_scan_list, backup_connection_bssid);
		int scan_list_ap_num = connection_scan_list.num;
		for (int i = 0; i < scan_list_ap_num; i++) {
			if (memcmp(backup_connection_bssid, connection_scan_list.bssid[i], 6) && (backup_candidate_bssid_exist == 0)) {
				//Find out the second candidate router
				backup_candidate_bssid_exist = 1;
				memcpy(backup_second_candidate_bssid, connection_scan_list.bssid[i], 6);
				backup_second_candidate_channel = connection_scan_list.channel[i];
				break;
			}
		}

		if (backup_candidate_bssid_exist) {
			printf("\n\r[%s] PSCAN_FAST_SURVEY channel: %d, MAC: "MAC_FMT"\n\r"
				   , __FUNCTION__, backup_second_candidate_channel, MAC_ARG(backup_second_candidate_bssid));
			connect_param.pscan_option = PSCAN_FAST_SURVEY;
			connect_param.channel = backup_second_candidate_channel;
			wifi_set_channel(backup_second_candidate_channel);
		} else {
			printf("\n\r[%s] Full Scan\n\r", __FUNCTION__);
		}
	} else {
		if (backup_candidate_bssid_exist) {
			printf("\n\r[%s] Clear backup candidate\n\r", __FUNCTION__);
			backup_candidate_bssid_exist = 0;
			memset(backup_connection_bssid, 0, 6);
			memset(backup_second_candidate_bssid, 0, 6);
			backup_second_candidate_channel = 0;
		} else {
			printf("\n\r[%s] No need to clear backup candidate\n\r", __FUNCTION__);
		}
	}
#endif
	ret = wifi_connect(&connect_param, 1);

	if (is_wpa3_disable) {
		wifi_user_config.rtw_cmd_tsk_spt_wap3 = ENABLE;
	}

	if (is_pmk_disable) {
		wifi_set_pmk_cache_enable(1);
	}

	if (ret == RTW_SUCCESS) {
#if CONFIG_LWIP_LAYER
#if ATCMD_VER == ATVER_2
		if (dhcp_mode_sta == 2) {
			struct netif *pnetif = &xnetif[0];
			u32 addr = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
			u32 netmask = WIFI_MAKEU32(NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
			u32 gw = WIFI_MAKEU32(GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
			LwIP_SetIP(0, addr, netmask, gw);
			dhcps_init(pnetif);
		} else
#endif
		{
			LwIP_DHCP(0, DHCP_START);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6_DHCP6
			LwIP_DHCP6(0, DHCP6_START);
#endif
#endif
#if LWIP_AUTOIP
			/*delete auto ip process for conflict with dhcp
						uint8_t *ip = LwIP_GetIP(0);
						if ((ip[0] == 0) && (ip[1] == 0) && (ip[2] == 0) && (ip[3] == 0)) {
							RTW_API_INFO("\n\nIPv4 AUTOIP ...");
							LwIP_AUTOIP(0);
						}
			*/
#endif
		}
#endif //#if CONFIG_LWIP_LAYER

#if WIFI_LOGO_CERTIFICATION
		backup_candidate_bssid_exist = 0;
		memset(backup_connection_bssid, 0, 6);
		memset(backup_second_candidate_bssid, 0, 6);
		backup_second_candidate_channel = 0;
#endif
	}

	param_indicator = NULL;
	rtw_delete_task(&wifi_autoreconnect_task);
#endif
}

void wifi_autoreconnect_hdl(rtw_security_t security_type,
							char *ssid, int ssid_len,
							char *password, int password_len,
							int key_id)
{
#if CONFIG_AUTO_RECONNECT
#if defined(CONFIG_MBED_ENABLED) || defined(CONFIG_PLATFOMR_CUSTOMER_RTOS)
	RTW_API_INFO("\n\r%s Not Implemented Yet!\n", __func__);
#else
	static struct wifi_autoreconnect_param param;
	param_indicator = &param;
	param.security_type = security_type;
	param.ssid = ssid;
	param.ssid_len = ssid_len;
	param.password = password;
	param.password_len = password_len;
	param.key_id = key_id;

	if (wifi_autoreconnect_task.task != NULL) {
#if CONFIG_LWIP_LAYER
		dhcp_stop(&xnetif[0]);
#endif
		u32 start_tick = rtw_get_current_time();
		while (1) {
			rtw_msleep_os(2);
			u32 passing_tick = rtw_get_current_time() - start_tick;
			if (rtw_systime_to_sec(passing_tick) >= 2) {
				RTW_API_INFO("\r\n Create wifi_autoreconnect_task timeout \r\n");
				return;
			}

			if (wifi_autoreconnect_task.task == NULL) {
				break;
			}
		}
	}


	rtw_create_task(&wifi_autoreconnect_task, (const char *)"wifi_autoreconnect", 2048, tskIDLE_PRIORITY + 1, _wifi_autoreconnect_thread, &param);
#endif
#endif
}

int wifi_config_autoreconnect(__u8 mode, __u8 retry_times, __u16 timeout)
{
#if CONFIG_AUTO_RECONNECT
	if (mode == RTW_AUTORECONNECT_DISABLE) {
		p_wlan_autoreconnect_hdl = NULL;
	} else {
		p_wlan_autoreconnect_hdl = wifi_autoreconnect_hdl;
	}
	return rtw_wx_set_autoreconnect(mode, retry_times, timeout);
#else
	return -1;
#endif
}

int wifi_config_autoreconnect_ms(__u8 mode, __u8 retry_times, __u16 timeout)
{
#if CONFIG_AUTO_RECONNECT
	if (mode == RTW_AUTORECONNECT_DISABLE) {
		p_wlan_autoreconnect_hdl = NULL;
	} else {
		p_wlan_autoreconnect_hdl = wifi_autoreconnect_hdl;
	}
	return rtw_wx_set_autoreconnect_ms(mode, retry_times, timeout);
#else
	return -1;
#endif
}

int wifi_get_autoreconnect(__u8 *mode)
{
#if CONFIG_AUTO_RECONNECT
	return rtw_wx_get_autoreconnect(mode);
#else
	return 0;
#endif
}

//----------------------------------------------------------------------------//
/*
 * Example for custom ie
 *
 * u8 test_1[] = {221, 2, 2, 2};
 * u8 test_2[] = {221, 2, 1, 1};
 * rtw_custom_ie_t buf[2] = {{test_1, PROBE_REQ},
 *		 {test_2, PROBE_RSP | BEACON}};
 * u8 buf_test2[] = {221, 2, 1, 3} ;
 * rtw_custom_ie_t buf_update = {buf_test2, PROBE_REQ};
 *
 * add ie list
 * static void cmd_add_ie(int argc, char **argv)
 * {
 *	 wifi_add_custom_ie((void *)buf, 2);
 * }
 *
 * update current ie
 * static void cmd_update_ie(int argc, char **argv)
 * {
 *	 wifi_update_custom_ie(&buf_update, 2);
 * }
 *
 * delete all ie
 * static void cmd_del_ie(int argc, char **argv)
 * {
 *	 wifi_del_custom_ie();
 * }
 */

int wifi_add_custom_ie(void *cus_ie, int ie_num)
{
	return rtw_wx_set_custome_ie(WLAN0_NAME, cus_ie, ie_num);
}


int wifi_update_custom_ie(void *cus_ie, int ie_index)
{
	return rtw_wx_update_custome_ie(WLAN0_NAME, cus_ie, ie_index);
}

int wifi_del_custom_ie()
{
	return rtw_wx_del_custome_ie(WLAN0_NAME);
}
//----------------------------------------------------------------------------//

void wifi_set_indicate_mgnt(int enable)
{
	rltk_wlan_set_indicate_mgnt(enable);
	return;
}

int wifi_send_raw_frame(raw_data_desc_t *raw_data_desc)
{
	return rtw_wx_send_raw_frame(raw_data_desc);
}

int wifi_init_mac_filter(void)
{
	return rltk_wlan_init_mac_filter();
}

int wifi_add_mac_filter(unsigned char *hwaddr)
{
	return rltk_wlan_add_mac_filter(hwaddr);
}

int wifi_del_mac_filter(unsigned char *hwaddr)
{
	return rltk_wlan_del_mac_filter(hwaddr);
}

int wifi_get_antenna_info(unsigned char *antenna)
{
#ifdef CONFIG_ANTENNA_DIVERSITY
	int ret = 0;

	ret = rtw_ex_get_antenna_info(WLAN0_IDX, antenna);
	return ret;
#else
	//UNUSED(antenna);
	return -1;
#endif
}

unsigned int wifi_get_tsf_low(unsigned char port_id)
{
	return rltk_wlan_get_tsf(port_id);
}

int wifi_get_txbuf_pkt_num(void)
{
	return rltk_wlan_get_txbuf_remain_pkt_num();
}

int wifi_set_tx_rate_by_ToS(unsigned char enable, unsigned char ToS_precedence, unsigned char tx_rate)
{
	return rltk_wlan_set_tx_rate_by_ToS(enable, ToS_precedence, tx_rate);
}

int wifi_set_EDCA_param(unsigned int AC_param)
{
	return rltk_wlan_set_EDCA_param(AC_param);
}

int wifi_set_TX_CCA(unsigned char enable)
{
	return rltk_wlan_set_TX_CCA(enable);
}

int wifi_ap_switch_chl_and_inform(unsigned char new_chl, unsigned char chl_switch_cnt, ap_channel_switch_callback_t callback)
{
	return rltk_wlan_ap_switch_chl_and_inform_sta(new_chl, chl_switch_cnt, callback);
}

int wifi_set_cts2self_duration_and_send(unsigned char wlan_idx, unsigned short duration)
{
	return rltk_wlan_set_cts2self_dur_and_send(wlan_idx, duration);
}

/**
 * @brief  there are same function for wifi_get_sta_max_data_rate and wifi_get_sta_current_data_rate to get current wifi data rate index.
 * @param[in]  inidata_rate: can be get the wifi data rate index definition(CCK/OFDM/HT MCS rate)
 * @return  If the function succeeds, the return value is 0.
 * 	Otherwise, return 1.
 */
int wifi_get_sta_max_data_rate(OUT unsigned char *inidata_rate)
{
	return rltk_wlan_get_sta_max_data_rate(inidata_rate);
}

int wifi_get_sta_current_data_rate(OUT unsigned char *inidata_rate)
{
	return rltk_wlan_get_sta_max_data_rate(inidata_rate);
}

/**
 * @brief  there is function for wifi_get_sta_avg_data_rate to get average wifi data MBPS.
 * @param[in]  avg_rate: can be get the wifi data rate value(MBPS)
 * @return  If the function succeeds, the return value is 0.
 * 	Otherwise, return 1.
 */
int wifi_get_sta_avg_data_rate(OUT unsigned char *avg_rate)
{
	return rltk_wlan_get_sta_avg_data_rate(avg_rate);
}

void wifi_set_no_beacon_timeout(unsigned char timeout_sec)
{
	rltk_wlan_set_no_beacon_timeout(timeout_sec);
}

/**
Example:
unsigned char mac[ETH_ALEN] = {0x00, 0xe0, 0x4c, 0x87, 0x12, 0x34};
wifi_change_mac_address_from_ram(idx, mac);
This method is to modify the mac and don't write to efuse.
**/
int wifi_change_mac_address_from_ram(int idx, unsigned char *mac)
{
	return rltk_change_mac_address_from_ram(idx, mac);
}

/**
Example:
unsigned char mac[] = "00e04c871234"
wifi_set_wifi_mac_address(mac);
This method is to modify the mac and write to efuse.
**/
int wifi_set_wifi_mac_address(u8 *mac)
{
	return rltk_wlan_set_wifi_mac_address(mac);
}

/**
Example:
wifi_get_wifi_mac_address(mac);
This method is to get the wifi mac from efuse.
**/
int wifi_get_wifi_mac_address(u8 *mac)
{
	return rltk_wlan_get_wifi_mac_address(mac);
}

/**
Example:
unsigned char mac[] = "00e04c871234"
wifi_set_bt_mac_address(mac);
This method is to modify the bt mac and write to efuse.
**/
int wifi_set_bt_mac_address(u8 *mac)
{
	return rltk_wlan_set_bt_mac_address(mac);
}

/**
Example:
wifi_get_bt_mac_address(mac);
This method is to get the bt mac from efuse.
**/
int wifi_get_bt_mac_address(u8 *mac)
{
	return rltk_wlan_get_bt_mac_address(mac);
}

/**
Example:
wifi_get_ap_dtim(dtim_period);
This method is to get dtim_period from ap beacon info.
**/
int wifi_get_ap_dtim(u8 *dtim_period)
{
	return rltk_wlan_get_ap_dtim(dtim_period);
}

int wifi_csi_config(rtw_csi_action_parm_t *act_param)
{
	int ret = 0;
	ret = rltk_wlan_csi_config(act_param);
	return ret;
}

int wifi_csi_report(u32 buf_len, u8 *csi_buf, u32 *len, rtw_csi_header_t *csi_header)
{
	int ret = 0;
	ret = rltk_wlan_csi_report(buf_len, csi_buf, len, csi_header);
	return ret;
}
/*--------------------------------porting interl api -------------------- */
void wifi_psk_info_set(struct psk_info *psk_data)
{
	rltk_psk_info_set(psk_data);
}

void wifi_psk_info_get(struct psk_info *psk_data)
{
	rltk_psk_info_get(psk_data);
}

u8 wifi_driver_is_mp(void)
{
	return rltk_wlan_is_mp();
}

int wifi_set_pmk_cache_enable(unsigned char value)
{
	return rtw_wx_set_pmk_cache_enable(WLAN0_IDX, value);
}

//----------------------------------------------------------------------------//
int wifi_get_sw_statistic(unsigned char idx, rtw_sw_statistics_t *sw_statistics)
{
	return rltk_wlan_statistic(idx, sw_statistics);
}

int wifi_set_wps_phase(unsigned char is_trigger_wps)
{
	return rltk_wlan_set_wps_phase(is_trigger_wps);
}

int wifi_set_gen_ie(unsigned char wlan_idx, char *buf, __u16 buf_len, __u16 flags)
{
#ifdef CONFIG_WPS
	return rtw_wx_set_gen_ie(wlan_idx, buf, buf_len, flags);
#else
	return -1;
#endif
}

int wifi_set_eap_phase(unsigned char is_trigger_eap)
{
#ifdef CONFIG_EAP
	return rltk_wlan_set_eap_phase(is_trigger_eap);
#else
	return -1;
#endif
}

unsigned char wifi_get_eap_phase(void)
{
#ifdef CONFIG_EAP
	return rltk_wlan_get_eap_phase();
#else
	return 0;
#endif
}

int wifi_set_eap_method(unsigned char eap_method)
{
#ifdef CONFIG_EAP
	return rltk_wlan_set_eap_method(eap_method);
#else
	return -1;
#endif
}

int wifi_send_eapol(const char *ifname, char *buf, __u16 buf_len, __u16 flags)
{
	return rtw_wx_send_eapol(ifname, buf, buf_len, flags);
}

/*
 * @brief get WIFI band type
 *@retval  the support band type.
 * 	WL_BAND_2_4G: only support 2.4G
 *	WL_BAND_5G: only support 5G
 *      WL_BAND_2_4G_5G_BOTH: support both 2.4G and 5G
 */
WL_BAND_TYPE wifi_get_band_type(void)
{
	u8 ret;

	ret = rltk_get_band_type();

	if (ret == 0) {
		return WL_BAND_2_4G;
	} else if (ret == 1) {
		return WL_BAND_5G;
	} else {
		return WL_BAND_2_4G_5G_BOTH;
	}
}

int wifi_get_auto_chl(unsigned char wlan_idx, unsigned char *channel_set, unsigned char channel_num)
{
	return rltk_get_auto_chl(wlan_idx, channel_set, channel_num);
}

int wifi_del_station(unsigned char wlan_idx, unsigned char *hwaddr)
{
	return rltk_del_station(wlan_idx, hwaddr);
}

int wifi_set_ra_start_rate(unsigned char rate)
{
	return rltk_wlan_set_ra_start_rate(rate);
}

int wifi_set_ra_max_rate(unsigned char max_rate)
{
	return rltk_wlan_set_ra_max_rate(max_rate);
}

int wifi_set_ra_1st_fallback_step(unsigned char step)
{
	return rltk_wlan_set_ra_1st_fallback_step(step);
}

int wifi_get_ap_mac_address(rtw_mac_t *mac)
{
	int ret;

	ip4_addr_t *gw_ip, *dst_ip_ret = NULL;
	struct eth_addr *dst_eth_ret;

	gw_ip = (ip4_addr_t *) LwIP_GetGW(0);
	// AP mac address
	if (LwIP_etharp_find_addr(0, gw_ip, &dst_eth_ret, (const ip4_addr_t **)&dst_ip_ret) >= 0) {
		memcpy(mac->octet, dst_eth_ret->addr, ETH_ALEN);
		ret = 0;
	} else {
		memset(mac->octet, 0, ETH_ALEN);
		ret = -1;
	}
	return ret;
}

void wifi_set_scan_time(unsigned short active_to, unsigned short passive_to, unsigned short home_to, unsigned char probe_cnt)
{
	rltk_wlan_scan_time(active_to, passive_to, home_to, probe_cnt);
}

void wifi_set_rts(unsigned char enable, unsigned int rts_threshold)
{
	rltk_wlan_set_rts(enable, rts_threshold);
}

int wifi_set_retry_limit(unsigned char short_retry, unsigned char long_retry)
{
	return rltk_wlan_set_retry_limit(short_retry, long_retry);
}

int wifi_get_router_wps_info(u8 *assoc_AP_manufacturer, u8 *assoc_AP_model_name, u8 *assoc_AP_model_number)
{

	return rltk_wlan_get_router_wps_info(assoc_AP_manufacturer, assoc_AP_model_name, assoc_AP_model_number);
}

int wifi_issue_nulldata(unsigned int power_mode)
{

	return rltk_wlan_issue_nulldata(power_mode);
}

int wifi_get_rx_queue_count(unsigned int *recvframe_cnt)
{

	return rltk_wlan_get_rx_queue_count(recvframe_cnt);

}

//disable the wifi module power
void wifi_power_hci_axi_deinit(void)
{
	printf("[%s] disable power module\n\r", __FUNCTION__);
	AON_TypeDef *aon_wlan = AON;

	// RF1 enable clock source control
	aon_wlan->AON_REG_AON_XTAL_CLK_CTRL1 &= (~AON_BIT_EN_XTAL_DRV_RF1);
	// RF2 enable clock source control
	aon_wlan->AON_REG_AON_XTAL_CLK_CTRL1 &= (~AON_BIT_EN_XTAL_DRV_RF2);
	// AFE enable clock source control
	aon_wlan->AON_REG_AON_XTAL_CLK_CTRL1 &= (~AON_BIT_EN_XTAL_DRV_AFE);
	// DIGI enable clock source control
	aon_wlan->AON_REG_AON_XTAL_CLK_CTRL1 &= (~AON_BIT_EN_XTAL_DRV_DIGI);
	// LPS enable clock source control
	// 20231106 remove: change clk to Xtal for LPS
	//aon_wlan->AON_REG_AON_XTAL_CLK_CTRL1 &= (~AON_BIT_EN_XTAL_DRV_LPS);

	aon_wlan->AON_REG_AON_WL_CTRL &= (~AON_BIT_SYS_WLAFE_POD33);

	aon_wlan->AON_REG_AON_WL_CTRL &= (~AON_BIT_SYS_WLAFE_POD125);

	aon_wlan->AON_REG_AON_WL_CTRL &= (~AON_BIT_SYS_WLON_CLK_EN);

	aon_wlan->AON_REG_AON_WL_CTRL &= (~AON_BIT_SYS_WL_AXI_EN);

	aon_wlan->AON_REG_AON_WL_CTRL &= (~AON_BIT_SYS_WLAXI_CLK_EN);

	aon_wlan->AON_REG_AON_WL_CTRL &= (~AON_BIT_SYS_WLON_EN);

	aon_wlan->AON_REG_AON_ISO_CTRL |= AON_BIT_SYS_ISO_WLON;

	aon_wlan->AON_REG_AON_PWR_CTRL &= (~AON_BIT_WLON_LPC_EN);

	aon_wlan->AON_REG_AON_PWR_CTRL &= (~AON_BIT_WLON_SPC_EN);
}
#endif	//#if CONFIG_WLAN
