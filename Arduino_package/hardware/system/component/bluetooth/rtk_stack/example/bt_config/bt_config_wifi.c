#include <platform_opts_bt.h>
#if (defined(CONFIG_BT_CONFIG) && CONFIG_BT_CONFIG) || (defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG)
#include "platform_stdlib.h"
#if defined(CONFIG_PLATFORM_8721D)
#include "ameba_soc.h"
#endif
#include "bt_config_wifi.h"
#include <osdep_service.h>
#include <gap_conn_le.h>
#include <gap_adv.h>
#include <lwip_netconf.h>
#include "wifi_conf.h"
#include "dhcp/dhcps.h"
#include "bt_config_app_task.h"
#include "os_mem.h"
#include "os_sync.h"
#include "os_task.h"
#include "os_sched.h"

extern void bt_config_app_deinit(void);
extern T_GAP_CONN_STATE bt_config_gap_conn_state;
extern T_GAP_DEV_STATE bt_config_gap_dev_state;

#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
#include "bt_airsync_config_app_task.h"
extern void bt_airsync_config_app_deinit(void);
extern T_GAP_CONN_STATE bt_airsync_config_gap_conn_state;
extern T_GAP_DEV_STATE bt_airsync_config_gap_dev_state;
#endif

#if defined(CONFIG_BT_CES_DEMO) && CONFIG_BT_CES_DEMO
#include "bt_ipc_dev_api.h"
#include "bt_mesh_provisioner_ces_demo_config.h"
#endif

// a temp variable for wifi scan
static void *wifi_scan_sema = NULL;
static void *BC_status_monitor_task_hdl = NULL;

static uint8_t pscan_channel_2G[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static uint8_t pscan_channel_5G[] = {36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 165};

static uint8_t last_conn_error = 0;
static rtw_join_status_t last_join_status = RTW_JOINSTATUS_UNKNOWN;

extern uint8_t *lwip_getip_intf(uint8_t idx);

extern uint8_t airsync_specific;

static rtw_result_t scan_result_handler(unsigned int scanned_AP_num, void *user_data)
{
	struct BC_wifi_scan_result *BC_scan_result = (struct BC_wifi_scan_result *) user_data;
	rtw_scan_result_t *scanned_ap_info;
	char *scan_buf = NULL;
	int ret = RTW_SUCCESS;
	int i = 0;

	if (scanned_AP_num == 0) {
		ret = RTW_ERROR;
		goto EXIT;
	}

	scanned_AP_num = (scanned_AP_num <= BC_MAX_WIFI_SCAN_AP_NUM) ? scanned_AP_num : BC_MAX_WIFI_SCAN_AP_NUM;

	scan_buf = (char *)rtw_zmalloc(scanned_AP_num * sizeof(rtw_scan_result_t));
	if (scan_buf == NULL) {
		BC_printf("malloc scan buf fail for BC_req_scan\n");
		ret = RTW_ERROR;
		goto EXIT;
	}

	if (wifi_get_scan_records(&scanned_AP_num, scan_buf) < 0) {
		ret = RTW_ERROR;
		goto EXIT;
	}

	for (i = 0; i < scanned_AP_num; i++) {
		scanned_ap_info = (rtw_scan_result_t *)(scan_buf + i * sizeof(rtw_scan_result_t));
		memcpy(&(BC_scan_result->ap_info[BC_scan_result->ap_num]), scanned_ap_info, sizeof(rtw_scan_result_t));
		BC_scan_result->ap_num++;
	}
EXIT:
	if (scan_buf) {
		rtw_mfree(scan_buf, 0);
	}
	os_sem_give(wifi_scan_sema);
	return ret;
}

BC_band_t BC_req_band_hdl(void)
{
	BC_printf("Band Request");

	u8 Band;
	Band = wifi_get_band_type();

	if (Band == WL_BAND_2_4G) {
		return BC_BAND_2G;
	} else if (Band == WL_BAND_5G) {
		return BC_BAND_5G;
	} else {
		return BC_BAND_2G_5G;
	}
}

int BC_req_scan_hdl(BC_band_t band, struct BC_wifi_scan_result *BC_scan_result)
{
	int ret = -1;
	uint8_t *pscan_channel;
	int pscan_config_size;
	rtw_scan_param_t scan_param;
	BC_band_t supported_band = BC_BAND_UNKNOWN;

	BC_printf("Scan Request");
	memset(BC_scan_result, 0, sizeof(struct BC_wifi_scan_result));

	if (band == BC_BAND_2G) {		// 2.4G
		pscan_channel = pscan_channel_2G;
		pscan_config_size = sizeof(pscan_channel_2G);
	} else if (band == BC_BAND_5G) {	// 5G
		pscan_channel = pscan_channel_5G;
		pscan_config_size = sizeof(pscan_channel_5G);
	}

	BC_printf("Scan %s AP\r\n", (band == BC_BAND_2G) ? "2.4G" : "5G");

	supported_band = BC_req_band_hdl();
	if((supported_band & band) == 0 ) {
		BC_printf("Can not Scan %s AP\r\n", (band == BC_BAND_2G) ? "2.4G" : "5G");
		return 0;
	}

	os_sem_create(&wifi_scan_sema, 0, 1);
#if defined(CONFIG_BT_CES_DEMO) && CONFIG_BT_CES_DEMO
    /* message CA7 to start wifi scan */
    {
        int *pret = NULL;
        uint32_t param_buf[24 + 3] = {0};
        bt_ipc_dev_request_message bt_dev_ipc_info;

        param_buf[0] = pscan_config_size;
        param_buf[1] = (uint32_t)BC_scan_result;
        param_buf[2] = (uint32_t)scan_result_handler;
        for (uint8_t i = 0; i < pscan_config_size; i++) {
            param_buf[i + 3] = pscan_channel[i];
        }
        pret = bt_ipc_api_dev_message_send(RTK_BT_MESH_CES_DEMO, MESH_DEMO_BC_WIFI_SCAN, param_buf, pscan_config_size + 3);
        if (pret[0] != RTW_SUCCESS) {
            BC_printf("Failed to invoke wifi scan on ca7 \n\r");
            rtw_mfree((void *)pret, sizeof(bt_dev_ipc_info.ret));
            ret = -1;
            os_sem_delete(wifi_scan_sema); 
            goto exit;
        } else {
            ret = pret[0];
            rtw_mfree((void *)pret, sizeof(bt_dev_ipc_info.ret));
        }

        os_sem_take(wifi_scan_sema, 0xFFFFFFFF);
	    os_sem_delete(wifi_scan_sema);   
    }
#else
    BC_scan_result->ap_num = 0;
	rtw_memset(&scan_param, 0, sizeof(rtw_scan_param_t));
	scan_param.scan_user_data = (void *)BC_scan_result;
	scan_param.scan_user_callback = scan_result_handler;
	scan_param.channel_list = pscan_channel;
	scan_param.channel_list_num = pscan_config_size;
	ret = wifi_scan_networks(&scan_param, 0);
	if (ret != RTW_SUCCESS) {
		BC_printf("wifi scan failed (%d)\n", ret);
		ret = -1;
	}
	os_sem_take(wifi_scan_sema, 0xFFFFFFFF);
	os_sem_delete(wifi_scan_sema);
#endif

exit:
	return ret;
}

static void wifi_join_status_callback(rtw_join_status_t join_status)
{
	unsigned short reason;
	if (join_status == RTW_JOINSTATUS_FAIL) {
		/* process error flag*/
		if (last_join_status == RTW_JOINSTATUS_ASSOCIATED || last_join_status == RTW_JOINSTATUS_4WAY_HANDSHAKING) {
			wifi_get_disconn_reason_code(&reason);
			if (reason != RTW_4WAY_HANDSHAKE_TIMEOUT) {
				last_conn_error = 1; //indicate wrong password
			}
		}
	}
	last_join_status = join_status;
}

#if defined(CONFIG_PLATFORM_AMEBAD2) && CONFIG_PLATFORM_AMEBAD2
#include "bt_ipc_dev_api.h"
#include "bt_mesh_provisioner_ces_demo_config.h"
#endif

int BC_req_connect_hdl(uint8_t *ssid, uint8_t *password, uint8_t *bssid, rtw_security_t security, BC_band_t band)
{
	rtw_network_info_t wifi = {0};
	rtw_wifi_setting_t setting = {0};
	int ret;
	uint32_t tick1, tick2, tick3;
	uint8_t assoc_by_bssid = 0;
	uint8_t DCHP_state;
	uint32_t wifi_retry_connect = 5;//For wifi connect retry        
	(void) band;

	BC_printf("Connect Request");

	BC_DBG("[Connect] band: [%s], BSSID: ["MAC_FMT"]",
		   (band == BC_BAND_2G) ? "2.4G" : (band == BC_BAND_5G) ? "5G" : "UNKNOWN", MAC_ARG(bssid));
	BC_DBG("[Connect] SSID: [%s], password: [%s]\r\n",
		   ssid, password);

#if CONFIG_AUTO_RECONNECT
	/* disable auto reconnect */
	wifi_config_autoreconnect(0, 0, 0);
#endif

	wifi.ssid.len = strlen((char const *)ssid);
	memcpy(wifi.ssid.val, ssid, wifi.ssid.len);
	wifi.password_len = strlen((char const *)password);
	wifi.password = password;
	memcpy(wifi.bssid.octet, bssid, 6);
	wifi.security_type = security;
	wifi.key_id = 0; // WEP key ID missed in BT Config, default WEP key ID 0
	wifi.joinstatus_user_callback = wifi_join_status_callback;

	tick1 = rtw_get_current_time();

	if (wifi.bssid.octet[0] != 0) {
		assoc_by_bssid = 1;
	} else if (wifi.ssid.len == 0) {
		BC_printf("Error: SSID can't be empty\r\n");
		return -1;
	}

WIFI_RETRY_LOOP:        
	//Check if in AP mode
	wifi_get_setting(WLAN0_IDX, &setting);
	if (setting.mode != RTW_MODE_STA) {
		wifi_set_mode(RTW_MODE_STA);
	}

	last_conn_error = 0; //clear before connect
	ret = wifi_connect(&wifi, 1);
	if (ret == RTW_INVALID_KEY) {
		last_conn_error = 1; //indicate wrong password
	}

	if (ret != RTW_SUCCESS) {
                wifi_retry_connect--;
                if (wifi_retry_connect > 0) {      
                  vTaskDelay(300);
                  BC_printf("wifi retry(ssid: %s(%d); password: %s(%d); security: %x)\r\n",ssid,wifi.ssid.len,password,wifi.password_len,security);
                  goto WIFI_RETRY_LOOP;
                }
		return ret;
	}
	tick2 = rtw_get_current_time();
	BC_printf("Connected after %dms.\r\n", (tick2 - tick1));

#if defined(CONFIG_PLATFORM_AMEBAD2) && CONFIG_PLATFORM_AMEBAD2
	{
        int *ret = NULL;
        bt_ipc_dev_request_message bt_dev_ipc_info;

        ret = bt_ipc_api_dev_message_send(RTK_BT_MESH_CES_DEMO, MESH_DEMO_START_DHCP, NULL, 0);
        if (ret[0]) {
            tick3 = rtw_get_current_time();
            BC_printf("Got IP after %dms.\r\n", (tick3 - tick1));
            rtw_mfree((void *)ret, sizeof(bt_dev_ipc_info.ret));
        } else {
            BC_printf("Got IP Fail.\r\n");
            rtw_mfree((void *)ret, sizeof(bt_dev_ipc_info.ret));
            return -1;
        }
    }
#elif defined(CONFIG_LWIP_LAYER) && CONFIG_LWIP_LAYER
    /* Start DHCPClient */
	DCHP_state = LwIP_DHCP(0, DHCP_START);

	if (DCHP_state != DHCP_ADDRESS_ASSIGNED) {
		return -1;
	}
	tick3 = rtw_get_current_time();
	BC_printf("Got IP after %dms.\r\n", (tick3 - tick1));
#endif

	return 0;
}

void BC_req_status_hdl(BC_status_t *status, uint8_t *SSID, uint8_t *BSSID, rtw_security_t *security, uint8_t *channel, int *rssi)
{
	rtw_wifi_setting_t setting;
	rtw_phy_statistics_t phy_statistics;

	//BC_printf("Status Request");
	if (!wifi_is_running(WLAN0_IDX)) {
		*status = BC_STATE_DISABLED;
		BC_printf("%s is disabled\r\n", WLAN0_NAME);
	} else if (last_conn_error == 1) {
		*status = BC_STATE_WRONG_PASSWORD;
		BC_printf("Wrong Password\r\n");
	} else if ((wifi_get_join_status() == RTW_JOINSTATUS_SUCCESS) && (*(u32 *)lwip_getip_intf(0) != IP_ADDR_INVALID)) {
		if (wifi_get_setting(WLAN0_IDX, &setting) != -1) {
			*status = BC_STATE_CONNECTED;
			memcpy(SSID, setting.ssid, BC_MAX_SSID_LEN);
			memcpy(BSSID, setting.bssid, BC_BSSID_LEN);
			*security = setting.security_type;
			*channel = setting.channel;
			wifi_fetch_phy_statistic(&phy_statistics);
			*rssi = phy_statistics.rssi;

			BC_DBG("Connected, SSID: [%s], BSSID: ["MAC_FMT"], channel: [%d], rssi: [%d]",
				   SSID, MAC_ARG(BSSID), *channel, *rssi);
		} else {
			*status = BC_STATE_IDLE;
			BC_DBG("Wifi not Connected\r\n");
		}
	} else {
		*status = BC_STATE_IDLE;
		BC_DBG("Wifi not Connected\r\n");
	}
}

void BC_status_monitor(void *p_param)
{
	(void)p_param;
	T_GAP_CONN_STATE gap_conn_state;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	osif_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif

	while (1) {
		os_delay(500);
		if ((wifi_get_join_status() == RTW_JOINSTATUS_SUCCESS) && (*(u32 *)lwip_getip_intf(0) != IP_ADDR_INVALID)) {// wifi connected
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
			if (airsync_specific) {
				gap_conn_state = bt_airsync_config_gap_conn_state;
			} else
#endif
			{
				gap_conn_state = bt_config_gap_conn_state;
			}

			if (gap_conn_state != GAP_CONN_STATE_CONNECTED) {					// BT not connected
				if (airsync_specific) {
					BC_printf("[%s] wifi connected, deinit BT Airsync Config\r\n", __FUNCTION__);
				} else {
					BC_printf("[%s] wifi connected, deinit BT Config\r\n", __FUNCTION__);
				}
				break;
			}
		}
	}

	BC_status_monitor_task_hdl = NULL;
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
	if (airsync_specific) {
		bt_airsync_config_app_deinit();
	} else
#endif
	{
		bt_config_app_deinit();
	}
	os_task_delete(NULL);
}

void bt_config_create_secure_context(void)
{
	#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
		rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE + 256);
	#endif
}

void bt_config_wifi_init(void)
{
	BC_cmd_task_init();

	if (BC_status_monitor_task_hdl == NULL) {
		if (os_task_create(&BC_status_monitor_task_hdl, (char const *)"BC_status_monitor", BC_status_monitor, NULL, 1024, 1) != true) {
			BC_printf("[%s] Create BC_status_monitor failed", __FUNCTION__);
		}
	} else {
		BC_printf("BC_status_monitor already on\r\n");
	}
}

void bt_config_wifi_deinit(void)
{
	T_GAP_DEV_STATE gap_dev_state;

	// Stop ADV
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
	if (airsync_specific) {
		bt_airsync_config_send_msg(0);
	} else
#endif
	{
		bt_config_send_msg(0);
	}

	do {
		os_delay(1);
#if defined(CONFIG_BT_AIRSYNC_CONFIG) && CONFIG_BT_AIRSYNC_CONFIG
		if (airsync_specific) {
			gap_dev_state = bt_airsync_config_gap_dev_state;
		} else
#endif
		{
			gap_dev_state = bt_config_gap_dev_state;
		}
	} while (gap_dev_state.gap_adv_state != GAP_ADV_STATE_IDLE);

	BC_cmd_task_deinit();
	if (BC_status_monitor_task_hdl != NULL) {
		os_task_delete(BC_status_monitor_task_hdl);
		BC_status_monitor_task_hdl = NULL;
	}
	airsync_specific = 0;
}
#endif
