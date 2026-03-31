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
#include "atcmd_wifi.h"
#endif
#if defined(CONFIG_PLATFORM_8721D) || defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_AMEBAD2) || defined(CONFIG_PLATFORM_8735B) || defined(CONFIG_PLATFORM_AMEBALITE)
#include "platform_opts_bt.h"
#endif
#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
#include <wifi_wps_config.h>
#endif

#if defined(CONFIG_AS_INIC_NP)
#include "inic_ipc_api.h"
#endif

//#include <drv_types.h>

/******************************************************
 *                    Constants
 ******************************************************/
#define RTW_JOIN_TIMEOUT 20000
/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *               Variables Declarations
 ******************************************************/

#if !defined(CONFIG_MBED_ENABLED)
#if CONFIG_LWIP_LAYER
extern struct netif xnetif[NET_IF_NUM];
#endif
#endif

/******************************************************
 *               Variables Definitions
 ******************************************************/
static internal_join_block_param_t *join_block_param = NULL;

#if defined(CONFIG_MBED_ENABLED) || defined (CONFIG_AS_INIC_NP)
rtw_mode_t wifi_mode = RTW_MODE_STA;
#else
extern rtw_mode_t wifi_mode;
#endif

#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6
extern void dhcp6_stop(struct netif *netif);
#endif
#endif

rtw_join_status_t rtw_join_status;
rtw_joinstatus_callback_t p_wifi_joinstatus_user_callback = NULL;
rtw_joinstatus_callback_t p_wifi_joinstatus_internal_callback = NULL;

rtw_detail_join_status_t rtw_detail_join_status;
rtw_detail_joinstatus_callback_t p_wifi_detail_joinstatus_internal_callback = NULL;

wifi_do_fast_connect_ptr p_wifi_do_fast_connect = NULL;
write_fast_connect_info_ptr p_store_fast_connect_info = NULL;

/* The flag to check if wifi init is completed */
int _wifi_is_on = 0;
extern void *param_indicator;

/******************************************************
 *               Variables Definitions
 ******************************************************/
/* Give default value if not defined */
/******************************************************
 *               Function Definitions
 ******************************************************/

extern int rtw_check_wifi_user_config_size(void);

#if CONFIG_WLAN
//----------------------------------------------------------------------------//
int g_conn_time = -1;
int g_conn_record[20][6] = {{0}};
static rtw_join_status_t g_wifi_last_status = RTW_JOINSTATUS_UNKNOWN;
static rtw_detail_join_status_t g_wifi_last_detail_status = RTW_DETAIL_JOINSTATUS_UNKNOWN;
unsigned long conn_tick;
unsigned long conn_starting_tick;
unsigned long conn_auth_tick;
unsigned long conn_assoiciation_tick;
unsigned long conn_handshake_tick;
unsigned long conn_connection_tick;
int is_filter_security = 0;
int is_unsupport_security = 0;
void wifi_join_status_debug(rtw_join_status_t join_status)
{
	if (wifi_user_config.wifi_debug_enabled & BIT(3)) {
		printf("[wifi_connect_status_callback] join_status: %d, wifi_last_status: %d,g_conn_time: %d\n\r"
			   , join_status, g_wifi_last_status, g_conn_time);
	}
	if (join_status == RTW_JOINSTATUS_STARTING) {
		g_conn_time = g_conn_time + 1;
		if ((g_conn_time < 0) || (g_conn_time >= 20)) {
			g_conn_time = 0;
		}
		conn_tick = xTaskGetTickCount();
	} else if (join_status == RTW_JOINSTATUS_SCANN_DONE) {
		if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
			conn_starting_tick = xTaskGetTickCount();
			g_conn_record[g_conn_time][0] = conn_starting_tick - conn_tick;
		} else {
			g_conn_record[g_conn_time][0] = 1;
		}
	} else if (join_status == RTW_JOINSTATUS_AUTHENTICATED) {
		if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
			conn_auth_tick = xTaskGetTickCount();
			g_conn_record[g_conn_time][1] = conn_auth_tick - conn_starting_tick;
		} else {
			g_conn_record[g_conn_time][1] = 1;
		}
	} else if (join_status == RTW_JOINSTATUS_ASSOCIATED) {
		if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
			conn_assoiciation_tick = xTaskGetTickCount();
			g_conn_record[g_conn_time][2] = conn_assoiciation_tick - conn_auth_tick;
		} else {
			g_conn_record[g_conn_time][2] = 1;
		}
	} else if (join_status == RTW_JOINSTATUS_4WAY_HANDSHAKE_DONE) {
		if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
			conn_handshake_tick = xTaskGetTickCount();
			g_conn_record[g_conn_time][3] = conn_handshake_tick - conn_assoiciation_tick;
		} else {
			g_conn_record[g_conn_time][3] = 1;
		}
	} else if (join_status == RTW_JOINSTATUS_REJECT_CONNECTION_SECURITY) {
		is_filter_security = 1;
	} else if (join_status == RTW_JOINSTATUS_REJECT_UNSUPPORT_SECURITY) {
		is_unsupport_security = 1;
	} else if (join_status == RTW_JOINSTATUS_SUCCESS) {
		if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
			conn_connection_tick = xTaskGetTickCount();
			g_conn_record[g_conn_time][4] = conn_connection_tick - conn_handshake_tick;
		} else {
			g_conn_record[g_conn_time][4] = 1;
		}

		for (int i = 0 ; i <= g_conn_time ; i++) {
			printf("(%d) Scan: %d, Auth: %d, Assoc: %d, 4way: %d, connect: %d, reason: %d\n\r",
				   i, g_conn_record[i][0], g_conn_record[i][1], g_conn_record[i][2],
				   g_conn_record[i][3], g_conn_record[i][4], g_conn_record[i][5]);
		}
		g_conn_time = -1;
		memset(g_conn_record, 0, sizeof(g_conn_record));
		conn_tick = 0;
		conn_starting_tick = 0;
		conn_auth_tick = 0;
		conn_assoiciation_tick = 0;
		conn_handshake_tick = 0;

		is_filter_security = 0;
		is_unsupport_security = 0;
	} else if (join_status == RTW_JOINSTATUS_DISCONNECT) {
		int reason_code = 0;
		wifi_get_disconn_reason_code((unsigned short *)&reason_code);
		if (65535 == reason_code) {
			//printf("[wifi_join_status_debug] no beacon for a long time\n\r");
		} else if (65534 == reason_code) {
			//printf("[wifi_join_status_debug] ap has changed, disconnect now\n\r");
		} else if (65533 == reason_code) {
			//printf("[wifi_join_status_debug] Disconnection from driver\n\r");
		} else {
			// deauth reason code from the router
		}
	}

	if (join_status == RTW_JOINSTATUS_FAIL) {
		if (g_wifi_last_status == RTW_JOINSTATUS_SCANN_DONE) {
			if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
				conn_starting_tick = xTaskGetTickCount();
				g_conn_record[g_conn_time][0] = conn_starting_tick - conn_tick;
			} else {
				g_conn_record[g_conn_time][0] = 1;
			}
			//scan
			if (is_filter_security) {
				printf("\n\r[%s] last state RTW_JOINSTATUS_REJECT_CONNECTION_SECURITY\n\r", __FUNCTION__);
			} else if (is_unsupport_security) {
				printf("\n\r[%s] last state RTW_JOINSTATUS_REJECT_UNSUPPORT_SECURITY\n\r", __FUNCTION__);
			} else {
				//printf("\n\r[%s] last state RTW_JOINSTATUS_SCANN_DONE\n\r",__FUNCTION__);
			}
		} else if (g_wifi_last_status == RTW_JOINSTATUS_AUTHENTICATING) {
			if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
				conn_auth_tick = xTaskGetTickCount();
				g_conn_record[g_conn_time][1] = conn_auth_tick - conn_starting_tick;
			} else {
				g_conn_record[g_conn_time][1] = 1;
			}
		} else if (g_wifi_last_status == RTW_JOINSTATUS_ASSOCIATING) {
			if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
				conn_assoiciation_tick = xTaskGetTickCount();
				g_conn_record[g_conn_time][2] = conn_assoiciation_tick - conn_auth_tick;
			} else {
				g_conn_record[g_conn_time][2] = 1;
			}
		} else if (g_wifi_last_status == RTW_JOINSTATUS_4WAY_HANDSHAKING) {
			if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
				conn_handshake_tick = xTaskGetTickCount();
				g_conn_record[g_conn_time][3] = conn_handshake_tick - conn_assoiciation_tick;
			} else {
				g_conn_record[g_conn_time][3] = 1;
			}
		} else if (g_wifi_last_status == RTW_JOINSTATUS_4WAY_HANDSHAKE_DONE) {
			if (wifi_user_config.wifi_debug_enabled & BIT(2)) {
				conn_connection_tick = xTaskGetTickCount();
				g_conn_record[g_conn_time][4] = conn_connection_tick - conn_handshake_tick;
			} else {
				g_conn_record[g_conn_time][4] = 1;
			}
		} else if (g_wifi_last_status == RTW_JOINSTATUS_TIMEOUT) {
			printf("\n\r[%s] last state RTW_JOINSTATUS_TIMEOUT\n\r", __FUNCTION__);
		} else if (g_wifi_last_status == RTW_JOINSTATUS_STATUS_CODE_FAIL) {
			int reason_code = 0;
			wifi_get_status_code((unsigned short *)&reason_code);
			printf("\n\r[%s] last state RTW_JOINSTATUS_STATUS_CODE_FAIL, reason_code: %d\n\r", __FUNCTION__, reason_code);
		}

		if (g_wifi_last_status > RTW_JOINSTATUS_STARTING && g_wifi_last_status < RTW_JOINSTATUS_4WAY_HANDSHAKE_DONE) {
			int reason_code = 0;
			wifi_get_status_code((unsigned short *)&reason_code);
			if (reason_code == 0) {
				wifi_get_disconn_reason_code((unsigned short *)&reason_code);
			}

			g_conn_record[g_conn_time][5] = reason_code;
			printf("(%d) Scan: %d, Auth: %d, Assoc: %d, 4way: %d, connect: %d, reason: %d\n\r",
				   g_conn_time, g_conn_record[g_conn_time][0], g_conn_record[g_conn_time][1], g_conn_record[g_conn_time][2],
				   g_conn_record[g_conn_time][3], g_conn_record[g_conn_time][4], g_conn_record[g_conn_time][5]);
		}

		conn_tick = 0;
		conn_starting_tick = 0;
		conn_auth_tick = 0;
		conn_assoiciation_tick = 0;
		conn_handshake_tick = 0;
		is_filter_security = 0;
		is_unsupport_security = 0;
	}
#if 0
	//Check the wrong password method
	if ((join_status == RTW_JOINSTATUS_FAIL)) {
		extern int rltk_get_connecting_security_type(unsigned int *connecting_security_type);
		unsigned int connecting_security_type = 0;
		rltk_get_connecting_security_type(&connecting_security_type);
		if (connecting_security_type == WPA3_SECURITY) {
			if ((g_wifi_last_status > RTW_JOINSTATUS_SCANN_DONE && g_wifi_last_status < RTW_JOINSTATUS_ASSOCIATING)
				|| (g_wifi_last_status > RTW_JOINSTATUS_ASSOCIATED && g_wifi_last_status < RTW_JOINSTATUS_4WAY_HANDSHAKE_DONE)) {
				int reason_code = 0;
				wifi_get_disconn_reason_code((unsigned short *)&reason_code);
				if (reason_code == 0) {
					wifi_get_status_code((unsigned short *)&reason_code);
				}
				printf("\n\r[%s] reason: %d, password wrong(WPA3)!!!!!!!!!!!\n\r\n\r", __FUNCTION__, reason_code);
			}
		} else {
			if (g_wifi_last_status > RTW_JOINSTATUS_ASSOCIATED && g_wifi_last_status < RTW_JOINSTATUS_4WAY_HANDSHAKE_DONE) {
				int reason_code = 0;
				wifi_get_disconn_reason_code((unsigned short *)&reason_code);
				if (reason_code == 0) {
					wifi_get_status_code((unsigned short *)&reason_code);
				}
				printf("\n\r[%s] reason: %d, password wrong(WPA2)!!!!!!!!!!!\n\r\n\r", __FUNCTION__, reason_code);
			}
		}
	}
#endif

	g_wifi_last_status = join_status;

}

int is_detail_filter_security = 0;
int is_detail_unsupport_security = 0;
void _wifi_detail_join_status_indicate(rtw_detail_join_status_t detail_join_status)
{
	rtw_detail_join_status = detail_join_status;

	printf("[%s] detail_join_status: %d, g_wifi_last_detail_status: %d\n\r", __FUNCTION__, detail_join_status, g_wifi_last_detail_status);

	if (detail_join_status == RTW_DETAIL_JOINSTATUS_REJECT_CONNECTION_SECURITY) {
		is_detail_filter_security = 1;
	} else if (detail_join_status == RTW_DETAIL_JOINSTATUS_REJECT_UNSUPPORT_SECURITY) {
		is_detail_unsupport_security = 1;
	} else if (detail_join_status == RTW_DETAIL_JOINSTATUS_SUCCESS) {
		is_detail_filter_security = 0;
		is_detail_unsupport_security = 0;
	} else if (detail_join_status == RTW_DETAIL_JOINSTATUS_DISCONNECT) {
		int reason_code = 0;
		wifi_get_disconn_reason_code((unsigned short *)&reason_code);
		if (65535 == reason_code) {
			//printf("[wifi_join_status_debug] no beacon for a long time\n\r");
		} else if (65534 == reason_code) {
			//printf("[wifi_join_status_debug] ap has changed, disconnect now\n\r");
		} else if (65533 == reason_code) {
			//printf("[wifi_join_status_debug] Disconnection from driver\n\r");
		} else {
			// deauth reason code from the router
		}
	}

	if (detail_join_status == RTW_DETAIL_JOINSTATUS_FAIL) {
		if (g_wifi_last_detail_status == RTW_DETAIL_JOINSTATUS_SCANN_DONE) {
			//scan
			if (is_detail_filter_security) {
				printf("\n\r[%s] last state RTW_DETAIL_JOINSTATUS_REJECT_CONNECTION_SECURITY\n\r", __FUNCTION__);
			} else if (is_detail_unsupport_security) {
				printf("\n\r[%s] last state RTW_DETAIL_JOINSTATUS_REJECT_UNSUPPORT_SECURITY\n\r", __FUNCTION__);
			} else {
				//printf("\n\r[%s] last state RTW_JOINSTATUS_SCANN_DONE\n\r",__FUNCTION__);
			}
		} if (g_wifi_last_detail_status == RTW_DETAIL_JOINSTATUS_TIMEOUT) {
			printf("\n\r[%s] last state RTW_DETAIL_JOINSTATUS_TIMEOUT\n\r", __FUNCTION__);
		} else if (g_wifi_last_detail_status == RTW_DETAIL_JOINSTATUS_STATUS_CODE_FAIL) {
			int reason_code = 0;
			wifi_get_status_code((unsigned short *)&reason_code);
			printf("\n\r[%s] last state RTW_DETAIL_JOINSTATUS_STATUS_CODE_FAIL, reason_code: %d\n\r", __FUNCTION__, reason_code);
		}

		if (g_wifi_last_detail_status > RTW_DETAIL_JOINSTATUS_STARTING && g_wifi_last_detail_status < RTW_DETAIL_JOINSTATUS_4WAY_HANDSHAKE_DONE) {
			int reason_code = 0;
			wifi_get_status_code((unsigned short *)&reason_code);
			if (reason_code == 0) {
				wifi_get_disconn_reason_code((unsigned short *)&reason_code);
			}
		}


		is_detail_filter_security = 0;
		is_detail_unsupport_security = 0;
	}
#if 1
	//Check the wrong password method
	if ((detail_join_status == RTW_DETAIL_JOINSTATUS_FAIL)) {
		extern int rltk_get_connecting_security_type(unsigned int *connecting_security_type);
		unsigned int connecting_security_type = 0;
		rltk_get_connecting_security_type(&connecting_security_type);
		if (connecting_security_type == WPA3_SECURITY) {
			if ((g_wifi_last_detail_status > RTW_DETAIL_JOINSTATUS_SCANN_DONE && g_wifi_last_detail_status < RTW_DETAIL_JOINSTATUS_ASSOCIATING)
				|| (g_wifi_last_detail_status > RTW_DETAIL_JOINSTATUS_ASSOCIATED && g_wifi_last_detail_status < RTW_DETAIL_JOINSTATUS_4WAY_HANDSHAKE_DONE)) {
				int reason_code = 0;
				wifi_get_disconn_reason_code((unsigned short *)&reason_code);
				if (reason_code == 0) {
					wifi_get_status_code((unsigned short *)&reason_code);
				}
				printf("\n\r[%s] reason: %d, password wrong(WPA3)(Status: %d)!!!!!!!!!!!\n\r\n\r", __FUNCTION__, reason_code, g_wifi_last_detail_status);
			}
		} else {
			if (g_wifi_last_detail_status > RTW_DETAIL_JOINSTATUS_ASSOCIATED && g_wifi_last_detail_status < RTW_DETAIL_JOINSTATUS_4WAY_HANDSHAKE_DONE) {
				int reason_code = 0;
				wifi_get_disconn_reason_code((unsigned short *)&reason_code);
				if (reason_code == 0) {
					wifi_get_status_code((unsigned short *)&reason_code);
				}
				printf("\n\r[%s] reason: %d, password wrong(WPA2)(Status: %d)!!!!!!!!!!!\n\r\n\r", __FUNCTION__, reason_code, g_wifi_last_detail_status);
			}
		}
	}
#endif

	g_wifi_last_detail_status = detail_join_status;
}

void _wifi_join_status_indicate(rtw_join_status_t join_status)
{
	/* step 1: internal process for different status*/
	if (join_status == RTW_JOINSTATUS_SUCCESS) {
#if CONFIG_LWIP_LAYER
		LwIP_netif_set_link_up(0);
#endif

		/* if not use fast dhcp, store fast connect info to flash when connect successfully*/
#if (!CONFIG_FAST_DHCP)
		if (p_store_fast_connect_info) {
			p_store_fast_connect_info(0, 0);
		}
#endif

		/* if Synchronous connection, up sema when connect success*/
		if (join_block_param && join_block_param->block) {
			rtw_up_sema(&join_block_param->join_sema);
		}
	}

	if (join_status == RTW_JOINSTATUS_FAIL) {
		/* if synchronous connection, up sema when connect fail*/
		if (join_block_param && join_block_param->block) {
			rtw_up_sema(&join_block_param->join_sema);
		}
	}

	if (join_status == RTW_JOINSTATUS_DISCONNECT) {
#if CONFIG_LWIP_LAYER
		LwIP_DHCP_stop(0);
#if LWIP_AUTOIP
		/*delete auto ip process for conflict with dhcp*/
		//LwIP_AUTOIP_STOP(0);
#endif
		LwIP_netif_set_link_down(0);
#endif
	}

	rtw_join_status = join_status;

	wifi_join_status_debug(join_status);

	/* step 2: execute user callback to process join_status*/
	if (p_wifi_joinstatus_user_callback) {
		p_wifi_joinstatus_user_callback(join_status);
	}
}

int wifi_connect(rtw_network_info_t *connect_param, unsigned char block)
{
	rtw_result_t result = RTW_SUCCESS;
	internal_join_block_param_t *block_param = NULL;

	if (connect_param == NULL) {
		RTW_API_INFO("\nwifi connect param not set!");
		return RTW_ERROR;
	}

	/* step1: check if there's ongoing connect*/
	if ((rtw_join_status > RTW_JOINSTATUS_UNKNOWN) && (rtw_join_status < RTW_JOINSTATUS_SUCCESS)) {
		RTW_API_INFO("\nthere is ongoing wifi connect!");
		return RTW_BUSY;
	}

	if (is_promisc_enabled()) {
		RTW_API_INFO("\npromisc is ongoing, can not do wifi connect now!");
		return RTW_BUSY;
	}

	if ((strlen((const char *)connect_param->ssid.val) < 0) || (strlen((const char *)connect_param->ssid.val) > 32)) {
		RTW_API_INFO("\nwifi connect param ssid is wrong!");
		rtw_join_status = RTW_JOINSTATUS_FAIL;
		rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
		return RTW_ERROR;
	}

	if ((((connect_param->password_len >  RTW_MAX_PSK_LEN) ||
		  (connect_param->password_len <  RTW_MIN_PSK_LEN)) &&
		 ((connect_param->security_type == RTW_SECURITY_WPA_TKIP_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA_AES_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA_MIXED_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA2_AES_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA2_TKIP_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA2_MIXED_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA_WPA2_TKIP_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA_WPA2_AES_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA_WPA2_MIXED_PSK) ||
#ifdef CONFIG_SAE_SUPPORT
		  (connect_param->security_type == RTW_SECURITY_WPA3_AES_PSK) ||
		  (connect_param->security_type == RTW_SECURITY_WPA2_WPA3_MIXED) ||
		  (connect_param->security_type == RTW_SECURITY_WPA3_GCMP_PSK)
#endif
		 ))) {
		RTW_API_INFO("\nwifi connect param password is wrong!");
		rtw_join_status = RTW_JOINSTATUS_FAIL;
		rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
		return RTW_INVALID_KEY;
	}

	p_wifi_joinstatus_user_callback = connect_param->joinstatus_user_callback;
	p_wifi_joinstatus_internal_callback = _wifi_join_status_indicate;
	p_wifi_detail_joinstatus_internal_callback = connect_param->detail_joinstatus_user_callback;

	/*clear for last connect status */
	rtw_join_status = RTW_JOINSTATUS_STARTING;
	_wifi_join_status_indicate(RTW_JOINSTATUS_STARTING);

	/* step2: malloc and set synchronous connection related variables*/
	if (block) {
		block_param = (internal_join_block_param_t *)rtw_zmalloc(sizeof(internal_join_block_param_t));
		if (!block_param) {
			result = (rtw_result_t) RTW_NOMEM;
			rtw_join_status = RTW_JOINSTATUS_FAIL;
			rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
			goto error;
		}
		block_param->block = block;
		rtw_init_sema(&block_param->join_sema, 0);
		if (!block_param->join_sema) {
			result = (rtw_result_t) RTW_NOMEM;
			rtw_join_status = RTW_JOINSTATUS_FAIL;
			rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
			goto error;
		}
	}

	/* step3: set connect cmd to driver*/
	result = rtw_wx_connect_local(connect_param);
	if (result != RTW_SUCCESS) {
		rtw_join_status = RTW_JOINSTATUS_FAIL;
		rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
		goto error;
	}

	/* step4: wait connect finished for synchronous connection*/
	if (block) {
		join_block_param = block_param;

#ifdef CONFIG_ENABLE_EAP
		// for eap connection, timeout should be longer (default value in wpa_supplicant: 60s)
		if (wifi_get_eap_phase()) {
			block_param->join_timeout = 60000;
		} else
#endif
			block_param->join_timeout = RTW_JOIN_TIMEOUT;

		if (rtw_down_timeout_sema(&block_param->join_sema, block_param->join_timeout) == RTW_FALSE) {
			RTW_API_INFO("RTW API: Join bss timeout\r\n");
			rtw_join_status = RTW_JOINSTATUS_FAIL;
			rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
			result = RTW_TIMEOUT;
			goto error;
		} else {
			if (wifi_is_connected_to_ap() != RTW_SUCCESS) {
				result = RTW_ERROR;
				rtw_join_status = RTW_JOINSTATUS_FAIL;
				rtw_detail_join_status = RTW_DETAIL_JOINSTATUS_FAIL;
				goto error;
			}
		}
	}

error:
	if (block_param) {
		if (block_param->join_sema) {
			rtw_free_sema(&block_param->join_sema);
		}
		rtw_free((u8 *)block_param);
		join_block_param = NULL;
	}

	if (result == RTW_TIMEOUT) {
		int ret;
		ret = wifi_disconnect();

		int timeout = 10;
		while (1) {
			if (wifi_is_connected_to_ap() != RTW_SUCCESS) {
				printf("WIFI disconnect succeed\n\r");
				break;
			}

			if (timeout == 0) {
				printf("Deassoc timeout!\n\r");
				ret = RTW_TIMEOUT;
				break;
			}

			vTaskDelay(1 * configTICK_RATE_HZ);
			timeout --;
		}
		printf("\n\r");
	}

	if (rtw_join_status == RTW_JOINSTATUS_FAIL) {
		_wifi_join_status_indicate(RTW_JOINSTATUS_FAIL);
	}

	if ((rtw_detail_join_status == RTW_DETAIL_JOINSTATUS_FAIL) && p_wifi_detail_joinstatus_internal_callback) {
		p_wifi_detail_joinstatus_internal_callback(RTW_DETAIL_JOINSTATUS_FAIL);
	}

	return result;
}
//----------------------------------------------------------------------------//
int wifi_disconnect(void)
{
	int ret = 0;

	//set MAC address last byte to 1 since driver will filter the mac with all 0x00 or 0xff
	//add extra 2 zero byte for check of #@ in wext_set_bssid()
	const __u8 null_bssid[ETH_ALEN + 2] = {0, 0, 0, 0, 0, 1, 0, 0};

	if (rtw_wx_set_wap(WLAN0_IDX, (__u8 *)null_bssid) < 0) {
		RTW_API_INFO("\n\rWEXT: Failed to set bogus BSSID to disconnect");
		ret = -1;
	}
	return ret;
}

//----------------------------------------------------------------------------//
int wifi_is_connected_to_ap(void)
{
	return rltk_wlan_is_connected_to_ap();
}

//----------------------------------------------------------------------------//
int wifi_is_running(unsigned char wlan_idx)
{
	return rltk_wlan_running(wlan_idx) && _wifi_is_on;
}

//----------------------------------------------------------------------------//
int wifi_set_channel(int channel)
{
	return rtw_wx_set_freq(WLAN0_IDX, channel);
}

int wifi_get_channel(u8 *channel)
{
	return rtw_wx_get_freq(WLAN0_IDX, (u8 *)channel);
}

unsigned char wifi_country_code_to_channel_plan(unsigned char band_type, unsigned char country_code)
{
	unsigned char channel_plan = 0;

	switch (country_code) {
	case RTW_COUNTRY_US:
		if (band_type == 1) {// 2.4g only
			channel_plan = 0x2A; // ch1 ~ 13
		} else {
			channel_plan = 0x7F; // default
		}
		break;
	case RTW_COUNTRY_EU:
		if (band_type == 1) {// 2.4g only
			channel_plan = 0x21;
		} else {
			channel_plan = 0x7F; // default
		}
		break;
	case RTW_COUNTRY_AU:
		if (band_type == 1) {// 2.4g only
			channel_plan = 0x21;
		} else {
			channel_plan = 0x7F; // default
		}
		break;
	case RTW_COUNTRY_JP:
		if (band_type == 1) {// 2.4g only
			channel_plan = 0x23;
		} else {
			channel_plan = 0x7F; // default
		}
		break;
	}
	return channel_plan;
}

//----------------------------------------------------------------------------//
static uint8_t bForece_ap_compatibilty_enabled = 0;
void wifi_set_ap_compatibilty_enabled(unsigned int  ap_compatibilty_enabled)
{
	bForece_ap_compatibilty_enabled = 1;
	wifi_user_config.ap_compatibilty_enabled = ap_compatibilty_enabled;
}

void wifi_set_user_config(void)
{
	// adaptivity
	wifi_user_config.rtw_adaptivity_en = DISABLE;
	/*
	 * 0 : RTW_ADAPTIVITY_MODE_NORMAL
	 * 1: RTW_ADAPTIVITY_MODE_CARRIER_SENSE
	 */
	wifi_user_config.rtw_adaptivity_mode = 0;
	wifi_user_config.rtw_adaptivity_th_l2h_ini = 0;
	//trp
	wifi_user_config.rtw_tx_pwr_lmt_enable = 2;	// 0: disable, 1: enable, 2: Depend on efuse(flash)
	wifi_user_config.rtw_tx_pwr_by_rate	= 2;	// 0: disable, 1: enable, 2: Depend on efuse(flash)
	wifi_user_config.rtw_trp_tis_cert_en = RTW_TRP_TIS_DISABLE;

	wifi_user_config.rtw_powersave_en = 1;

#ifdef CONFIG_SAE_SUPPORT
	// set to 'ENABLE' when using WPA3
	wifi_user_config.rtw_cmd_tsk_spt_wap3 = ENABLE;
#endif

	wifi_user_config.g_user_ap_sta_num = NUM_STA;//NUM_STA (2 + AP_STA_NUM)

	/* power save */
	wifi_user_config.lps_dtim = 0;
	wifi_user_config.lps_enter_threshold = 0; // LPS_THRESH_PKT_COUNT

	wifi_user_config.rtw_power_mgnt = PS_MODE_MIN;
#if defined(CONFIG_LPS_PG)
	wifi_user_config.rtw_lps_level = LPS_PG;
#else
	wifi_user_config.rtw_lps_level = LPS_NORMAL;
#endif
#ifdef CONFIG_PLATFORM_8195BHP
	wifi_user_config.rtw_lps_level = LPS_NORMAL;
	wifi_user_config.rtw_power_mgnt = PS_MODE_MAX;//PS_MODE_MIN
#endif
	wifi_user_config.rtw_ps_timeout = 80;// default: 20
	wifi_user_config.smart_ps = 2;

	/* AP */
	wifi_user_config.bForwardingDisabled = 0;

	wifi_user_config.bAcceptAddbaReq = (u8)_TRUE; // 0:Reject AP's Add BA req, 1:Accept AP's Add BA req.
	wifi_user_config.bIssueAddbaReq = (u8)_TRUE;
	wifi_user_config.addba_tx_num_th = 100;

	wifi_user_config.bCheckDestAddress = (u8)_TRUE;

	if (!bForece_ap_compatibilty_enabled) {
		wifi_user_config.ap_compatibilty_enabled = 0x0F;
	} else {
		printf("force wifi_user_config.ap_compatibilty_enabled: %x\n\r", wifi_user_config.ap_compatibilty_enabled);
	}

#ifdef CONFIG_LAYER2_ROAMING
	wifi_user_config.max_roaming_times = 2;
#endif

#ifdef CONFIG_ENABLE_AP_POLLING_CLIENT_ALIVE
	wifi_user_config.ap_polling_sta = 1;
#else
	wifi_user_config.ap_polling_sta = 0;
#endif

	wifi_user_config.channel_plan = 0;
	if (wifi_user_config.country_code) {
		wifi_user_config.channel_plan = wifi_country_code_to_channel_plan(wifi_user_config.band_type, wifi_user_config.country_code);
	}

	wifi_user_config.active_keepalive_enabled = 1;

	wifi_user_config.active_keepalive_interval = 20;

	wifi_user_config.fast_pscan_retry_times_max = 14;

	wifi_default_config.listen_interval = 0;

	u32 cfg_size_lib, cfg_size_user;
	cfg_size_lib = rtw_check_wifi_user_config_size();
	cfg_size_user = sizeof(struct wifi_user_conf);
	printf("cfg_size_lib = %d, cfg_size_user = %d\n\r", cfg_size_lib, cfg_size_user);
}

int wifi_get_disconn_reason_code(unsigned short *reason_code)
{
	return rltk_wlan_get_disconn_reason_code(reason_code);
}

int wifi_get_status_code(unsigned short *status_code)
{
	return rltk_wlan_get_status_code(status_code);
}

rtw_join_status_t wifi_get_join_status(void)
{
	return rtw_join_status;
}

void wifi_set_join_status(rtw_join_status_t status)
{
	rtw_join_status = status;
}

int wifi_on(rtw_mode_t mode)
{
	int ret = 1;
	int timeout = 20;
	int idx;
	int devnum = 1;
	static int event_init = 0;

	device_mutex_lock(RT_DEV_LOCK_WLAN);
	if (rltk_wlan_running(WLAN0_IDX)) {
		RTW_API_INFO("\n\rWIFI is already running");
		device_mutex_unlock(RT_DEV_LOCK_WLAN);
		return 1;
	}

	if (event_init == 0) {
		init_event_callback_list();
		event_init = 1;
	}

	wifi_mode = mode;

	if (mode == RTW_MODE_STA_AP) {
		devnum = 2;
	}

	// set wifi mib
	wifi_set_user_config();
	RTW_API_INFO("\n\rInitializing WIFI ...");
	for (idx = 0; idx < devnum; idx++) {
		ret = rltk_wlan_init(idx, mode);
		if (ret < 0) {
			wifi_mode = RTW_MODE_NONE;
			device_mutex_unlock(RT_DEV_LOCK_WLAN);
			return ret;
		}
	}
	for (idx = 0; idx < devnum; idx++) {
		ret = rltk_wlan_start(idx);
		if (ret == 0) {
			_wifi_is_on = 1;
		}
		if (ret < 0) {
			RTW_API_INFO("\n\rERROR: Start WIFI Failed!");
			rltk_wlan_deinit();
			wifi_mode = RTW_MODE_NONE;
			device_mutex_unlock(RT_DEV_LOCK_WLAN);
			return ret;
		}
	}
	device_mutex_unlock(RT_DEV_LOCK_WLAN);

	while (1) {
		if (rltk_wlan_running(devnum - 1)) {
			RTW_API_INFO("\n\rWIFI initialized\n");
			if (wifi_user_config.channel_plan) {
				rltk_wlan_change_channel_plan(wifi_user_config.channel_plan);
			}
			if (wifi_user_config.chn2_4G_num || wifi_user_config.chn5G_num) {
				wifi_set_customized_channel_plan(wifi_user_config.chn2_4G, wifi_user_config.chn2_4G_num,
												 wifi_user_config.chn5G, wifi_user_config.chn5G_num,
												 wifi_user_config.regulation2_4G, wifi_user_config.regulation5G);
			}
#if CONFIG_AUTO_RECONNECT
#if WIFI_LOGO_CERTIFICATION
			//setup reconnection flag
			wifi_config_autoreconnect_ms(1, 100, 10);
#else
			//setup reconnection flag
			wifi_config_autoreconnect(1, AUTO_RECONNECT_COUNT, AUTO_RECONNECT_INTERVAL);
#endif
#endif
			//Used by FAST RECONNECTION
			if (p_wifi_do_fast_connect && wifi_mode == RTW_MODE_STA) {
				p_wifi_do_fast_connect();
			}
			break;
		}

		if (timeout == 0) {
			RTW_API_INFO("\n\rERROR: Init WIFI timeout!");
			break;
		}

		rtw_msleep_os(1000);
		timeout --;
	}

#if CONFIG_LWIP_LAYER
#if defined(CONFIG_MBED_ENABLED) || defined(CONFIG_PLATFOMR_CUSTOMER_RTOS)
	//TODO
#else
	LwIP_netif_set_up(0);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6
	netif_create_ip6_linklocal_address(&xnetif[0], 1);
#endif
#endif
	if (mode == RTW_MODE_AP) {
		LwIP_netif_set_link_up(0);
	} else	 if (mode == RTW_MODE_STA_AP) {
		LwIP_netif_set_up(1);
		LwIP_netif_set_link_up(1);
	}
#endif
#endif

	return ret;
}

int wifi_off(void)
{
	int ret = 0;
	int timeout = 20;

	if ((rltk_wlan_running(WLAN0_IDX) == 0) &&
		(rltk_wlan_running(WLAN1_IDX) == 0)) {
		RTW_API_INFO("\n\rWIFI is not running");
		return 0;
	}
#if CONFIG_LWIP_LAYER
#if defined(CONFIG_MBED_ENABLED) || defined(CONFIG_PLATFOMR_CUSTOMER_RTOS)
	//TODO
#else
	dhcps_deinit();
	LwIP_DHCP_stop(0);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 1
#if LWIP_IPV6_DHCP6
	LwIP_DHCP6(0, DHCP6_STOP);
#endif
#endif
	LwIP_netif_set_down(0);
	LwIP_netif_set_down(1);
	if (wifi_mode == RTW_MODE_AP) {
		LwIP_netif_set_link_down(0);
	}
#endif
#endif
#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
	if ((wifi_mode ==  RTW_MODE_AP) || (wifi_mode == RTW_MODE_STA_AP)) {
		wpas_wps_deinit();
	}
#endif
	RTW_API_INFO("\n\rDeinitializing WIFI ...");
	device_mutex_lock(RT_DEV_LOCK_WLAN);
	rltk_wlan_deinit();
	_wifi_is_on = 0;
	device_mutex_unlock(RT_DEV_LOCK_WLAN);

	while (1) {
		if ((rltk_wlan_running(WLAN0_IDX) == 0) &&
			(rltk_wlan_running(WLAN1_IDX) == 0)) {
			RTW_API_INFO("\n\rWIFI deinitialized");
			break;
		}

		if (timeout == 0) {
			RTW_API_INFO("\n\rERROR: Deinit WIFI timeout!");
			break;
		}

		rtw_msleep_os(1000);
		timeout --;
	}

	wifi_mode = RTW_MODE_NONE;

	return ret;
}

int wifi_set_mode(rtw_mode_t mode)
{
	int ret = 0;
#ifdef CONFIG_WLAN_SWITCH_MODE
	rtw_mode_t curr_mode, next_mode;
#if defined(CONFIG_AUTO_RECONNECT) && CONFIG_AUTO_RECONNECT
	u8 autoreconnect_mode;
#endif
#endif
	device_mutex_lock(RT_DEV_LOCK_WLAN);

	if ((rltk_wlan_running(WLAN0_IDX) == 0) &&
		(rltk_wlan_running(WLAN1_IDX) == 0)) {
		RTW_API_INFO("\n\r[%s] WIFI is not running", __FUNCTION__);
		device_mutex_unlock(RT_DEV_LOCK_WLAN);
		return -1;
	}

#ifdef CONFIG_WLAN_SWITCH_MODE
#ifndef CONFIG_AS_INIC_NP
#if defined(CONFIG_AUTO_RECONNECT) && CONFIG_AUTO_RECONNECT
	wifi_get_autoreconnect(&autoreconnect_mode);
	if (autoreconnect_mode != RTW_AUTORECONNECT_DISABLE) {
		wifi_config_autoreconnect(RTW_AUTORECONNECT_DISABLE, 0, 0);

		// if set to AP mode, delay until the autoconnect task is finished
		if ((mode == RTW_MODE_AP) || (mode == RTW_MODE_STA_AP)) {
			while (param_indicator != NULL) {
				rtw_msleep_os(2);
			}
		}
	}
#endif
#endif
	curr_mode = wifi_mode;
	next_mode = mode;
	ret = rltk_set_mode_prehandle(curr_mode, next_mode, WLAN0_NAME);
	if (ret < 0) {
		goto Exit;
	}
#endif

	if ((wifi_mode == RTW_MODE_STA) && (mode == RTW_MODE_AP)) {
		RTW_API_INFO("\n\r[%s] WIFI Mode Change: STA-->AP", __FUNCTION__);

		wifi_disconnect();
		//must add this delay, because this API may have higher priority, wifi_disconnect will rely RTW_CMD task, may not be excuted immediately.
		rtw_msleep_os(50);

#if CONFIG_LWIP_LAYER
		LwIP_netif_set_link_up(0);
#endif

		wifi_mode = mode;
		rtw_wx_set_pmk_cache_enable(WLAN0_IDX, 0);
	} else if ((wifi_mode == RTW_MODE_AP) && (mode == RTW_MODE_STA)) {
		RTW_API_INFO("\n\r[%s] WIFI Mode Change: AP-->STA", __FUNCTION__);

		ret = rtw_wx_set_mode(WLAN0_IDX, RTW_MODE_INFRA);
		if (ret < 0) {
			goto Exit;
		}

		rtw_msleep_os(50);

#if CONFIG_LWIP_LAYER
		LwIP_netif_set_link_down(0);
#endif

		wifi_mode = mode;
		rtw_wx_set_pmk_cache_enable(WLAN0_IDX, 1);
	} else if ((wifi_mode == RTW_MODE_AP) && (mode == RTW_MODE_AP)) {
		RTW_API_INFO("\n\rWIFI Mode Change: AP-->AP");
		ret = rtw_wx_set_mode(WLAN0_IDX, RTW_MODE_INFRA);
		if (ret < 0) {
			goto Exit;
		}

		vTaskDelay(50);

	} else if ((wifi_mode == RTW_MODE_STA) && (mode == RTW_MODE_STA)) {
		RTW_API_INFO("\n\rWIFI Mode No Need To Change: STA -->STA");
	} else if ((wifi_mode == RTW_MODE_STA) && (mode == RTW_MODE_PROMISC)) {
		RTW_API_INFO("\n\rWIFI Mode Change: STA-->PROMISC");
		unsigned char ssid[33];
		if (rtw_wx_get_essid(WLAN0_IDX, ssid) > 0) {
			wifi_disconnect();
		}
	} else if ((wifi_mode == RTW_MODE_AP) && (mode == RTW_MODE_PROMISC)) {
		RTW_API_INFO("\n\rWIFI Mode Change: AP-->PROMISC");//Same as AP--> STA
		ret = rtw_wx_set_mode(WLAN0_IDX, RTW_MODE_INFRA);
		if (ret < 0) {
			goto Exit;
		}
		rtw_msleep_os(50);
#if CONFIG_LWIP_LAYER
		LwIP_netif_set_link_down(0);
#endif
		wifi_mode = mode;
	}
#ifdef CONFIG_CONCURRENT_MODE
#ifdef CONFIG_WLAN_SWITCH_MODE
	else if ((wifi_mode == RTW_MODE_STA_AP) && (mode == RTW_MODE_STA)) {
		RTW_API_INFO("\n\rWIFI Mode Change: CONCURRENT-->STA");
#if CONFIG_LWIP_LAYER
		dhcps_deinit();
		LwIP_netif_set_down(1);
		LwIP_netif_set_link_down(1);
#endif
	} else if ((wifi_mode == RTW_MODE_STA) && (mode == RTW_MODE_STA_AP)) {
		RTW_API_INFO("\n\rWIFI Mode Change: STA-->CONCURRENT");
#if CONFIG_LWIP_LAYER
		dhcps_init(&xnetif[1]);
		LwIP_netif_set_up(1);
		LwIP_netif_set_link_up(1);
#endif
		wifi_mode = mode;
	}
#endif
#endif
	else {
		RTW_API_INFO("\n\rWIFI Mode Change: not support");
		goto Exit;
	}

#ifdef CONFIG_WLAN_SWITCH_MODE
	ret = rltk_set_mode_posthandle(curr_mode, next_mode, WLAN0_NAME);
	if (ret < 0) {
		goto Exit;
	}
#ifdef CONFIG_CONCURRENT_MODE
	if ((wifi_mode == RTW_MODE_STA_AP) && (mode == RTW_MODE_STA)) {
		wifi_mode = RTW_MODE_STA;
	}
#endif
#ifndef CONFIG_AS_INIC_NP
#if defined(CONFIG_AUTO_RECONNECT) && CONFIG_AUTO_RECONNECT
	/* enable auto reconnect */
	if (autoreconnect_mode != RTW_AUTORECONNECT_DISABLE) {
		wifi_config_autoreconnect(autoreconnect_mode, AUTO_RECONNECT_COUNT, AUTO_RECONNECT_INTERVAL);
	}
#endif
#endif
#endif

	device_mutex_unlock(RT_DEV_LOCK_WLAN);
	return 0;

Exit:
#ifdef CONFIG_WLAN_SWITCH_MODE
#ifndef CONFIG_AS_INIC_NP
#if defined(CONFIG_AUTO_RECONNECT) && CONFIG_AUTO_RECONNECT
	/* enable auto reconnect */
	if (autoreconnect_mode != RTW_AUTORECONNECT_DISABLE) {
		wifi_config_autoreconnect(autoreconnect_mode, AUTO_RECONNECT_COUNT, AUTO_RECONNECT_INTERVAL);
	}
#endif
#endif
#endif
	device_mutex_unlock(RT_DEV_LOCK_WLAN);
	return -1;
}

int wifi_start_ap(rtw_softap_info_t *softAP_config)
{
	const char *ifname = WLAN0_NAME;
	unsigned char wlan_idx = WLAN0_IDX;
	int ret = 0;

	if (softAP_config->ssid.len > 32) {
		RTW_API_INFO("Error: SSID should be 0-32 characters\r\n");
		ret = RTW_BADARG;
		goto exit;
	}

	if (softAP_config->password == NULL) {
		if (softAP_config->security_type != RTW_SECURITY_OPEN) {
			ret = RTW_INVALID_KEY;
			goto exit;
		}
	}
	if (softAP_config->security_type != RTW_SECURITY_OPEN) {
		if (softAP_config->password_len <= RTW_WPA2_MAX_PSK_LEN &&
			softAP_config->password_len >= RTW_MIN_PSK_LEN) {
			if (softAP_config->password_len == RTW_WPA2_MAX_PSK_LEN) { //password_len=64 means pre-shared key, pre-shared key should be 64 hex characters
				unsigned char i, j;
				for (i = 0; i < RTW_WPA2_MAX_PSK_LEN; i++) {
					j = softAP_config->password[i];
					if (!((j >= '0' && j <= '9') || (j >= 'A' && j <= 'F') || (j >= 'a' && j <= 'f'))) {
						RTW_API_INFO("Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
						ret = RTW_INVALID_KEY;
						goto exit;
					}
				}
			}
		}
#ifdef CONFIG_FPGA
		else if ((softAP_config->password_len == 5) && (softAP_config->security_type == RTW_SECURITY_WEP_PSK)) {
		}
#endif
		else {
			printf("Error: password should be 64 hex characters or 8-63 ASCII characters\n\r");
			ret = RTW_INVALID_KEY;
			goto exit;
		}
	}

	if (wifi_mode == RTW_MODE_STA_AP) {
		ifname = WLAN1_NAME;
		wlan_idx = WLAN1_IDX;
	}

	if (is_promisc_enabled()) {
		wifi_set_promisc(0, NULL, 0);
	}

	ret = rtw_wx_set_mode(wlan_idx, RTW_MODE_MASTER);
	if (ret < 0) {
		goto exit;
	}
	ret = rtw_wx_set_freq(wlan_idx, softAP_config->channel);	//Set channel before starting ap
	if (ret < 0) {
		goto exit;
	}

	switch (softAP_config->security_type) {
	case RTW_SECURITY_OPEN:
		break;
#if defined(CONFIG_FPGA) && CONFIG_FPGA
	case RTW_SECURITY_WEP_PSK:
		ret = rtw_wx_set_auth(ifname, RTW_AUTH_80211_AUTH_ALG, RTW_AUTH_ALG_OPEN_SYSTEM);
		if (ret == 0) {
			ret = rtw_wx_set_enc_ext(ifname, RTW_ENCODE_ALG_WEP, NULL, 0, 1, 0, 0, (u8 *)softAP_config->password, softAP_config->password_len);
		}
		break;
	case RTW_SECURITY_WPA2_TKIP_PSK:
		ret = rtw_wx_set_auth(ifname, RTW_AUTH_80211_AUTH_ALG, RTW_AUTH_ALG_OPEN_SYSTEM);
		if (ret == 0) {
			ret = rtw_wx_set_enc_ext(ifname, RTW_ENCODE_ALG_TKIP, NULL, 0, 0, 0, 0, NULL, 0);
		}
		if (ret == 0) {
			ret = rtw_wx_set_passphrase(wlan_idx, (u8 *)softAP_config->password, softAP_config->password_len);
		}
		break;
#endif
	case RTW_SECURITY_WPA2_AES_PSK:
		ret = rtw_wx_set_auth(ifname, RTW_AUTH_80211_AUTH_ALG, RTW_AUTH_ALG_OPEN_SYSTEM);
		if (ret == 0) {
			ret = rtw_wx_set_enc_ext(ifname, RTW_ENCODE_ALG_CCMP, NULL, 0, 0, 0, 0, NULL, 0);
		}
		if (ret == 0) {
			ret = rtw_wx_set_passphrase(wlan_idx, (u8 *)softAP_config->password, softAP_config->password_len);
		}
		break;
#ifdef CONFIG_IEEE80211W
	case RTW_SECURITY_WPA2_AES_CMAC:
		ret = rtw_wx_set_auth(ifname, RTW_AUTH_80211_AUTH_ALG, RTW_AUTH_ALG_OPEN_SYSTEM);
		if (ret == 0) {
			ret = rtw_wx_set_enc_ext(ifname, RTW_ENCODE_ALG_AES_CMAC, NULL, 0, 0, 0, 0, NULL, 0);
		}
		if (ret == 0) {
			ret = rtw_wx_set_passphrase(wlan_idx, (u8 *)softAP_config->password, softAP_config->password_len);
		}
		break;
#endif
	default:
		ret = -1;
		RTW_API_INFO("\n\rWIFICONF: security type is not supported");
		break;
	}
	if (ret < 0) {
		goto exit;
	}

	if (softAP_config->hidden_ssid == 1) {
		ret = rltk_set_hidden_ssid(ifname, 1);
		if (ret < 0) {
			goto exit;
		}
	}
	ret = rtw_wx_set_ap_essid(wlan_idx, softAP_config->ssid.val, softAP_config->ssid.len);
#if defined(CONFIG_ENABLE_WPS_AP) && CONFIG_ENABLE_WPS_AP
	wpas_wps_init(ifname);
#endif
#if CONFIG_LWIP_LAYER
#if defined(CONFIG_MBED_ENABLED) || defined(CONFIG_PLATFOMR_CUSTOMER_RTOS)
	//TODO
#else
	if (wifi_mode == RTW_MODE_STA_AP) {
		LwIP_netif_set_link_up(1);
	} else {
		LwIP_netif_set_link_up(0);
	}
#endif
#endif

exit:

	return ret;
}

int wifi_scan_networks(rtw_scan_param_t *scan_param, unsigned char block)
{
	int ret = RTW_SUCCESS;
	//default 2G & 5G support channel list
	u8 channel_list_2G[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	u8 channel_list_5G[25] = {36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 149, 153, 157, 161, 165};

	if (scan_param == NULL) {
		RTW_API_INFO("SCAN param not set!\n");
		return RTW_ERROR;
	}

	if (block && scan_param->scan_user_callback) {
		RTW_API_INFO("not support user callback for block scan!\n");
		return RTW_ERROR;
	}

	if (scan_param->options & RTW_SCAN_REPORT_EACH) {
		if (scan_param->scan_report_each_mode_user_callback == NULL) {
			RTW_API_INFO("please register scan_report_each_mode_user_callback for RTW_SCAN_REPORT_EACH mode!\n");
			return RTW_ERROR;
		}
	}
	/* lock 2s to forbid suspend under scan */
	rtw_wakelock_timeout(2 * 1000);

	if (scan_param->band == 1) {
		if (scan_param->channel_list_num == 0) {
			scan_param->channel_list_num = 13;
			scan_param->channel_list = channel_list_2G;
		}
	} else if (scan_param->band == 2) {
		if (scan_param->channel_list_num == 0) {
			scan_param->channel_list_num = 25;
			scan_param->channel_list = channel_list_5G;
		}
	}

	ret = rtw_wx_set_scan(scan_param, block);

	return ret;
}

int wifi_set_customized_channel_plan(customized_chl_cfg_t *chnlplan2_4, u8 chnlnum2_4, customized_chl_cfg_t *chnlplan5, u8 chnlnum5, u8 regulation2_4,
									 u8 regulation5)
{
	return rltk_wlan_set_customized_channel_plan(chnlplan2_4, chnlnum2_4, chnlplan5, chnlnum5, regulation2_4, regulation5, 0);
}

int wifi_get_scan_records(unsigned int *AP_num, char *scan_buf)
{
	return rtw_wx_get_scan_results(AP_num, scan_buf);
}

int wifi_scan_abort(void)
{
	return rtw_wx_scan_abort();
}

int wifi_set_country_code(const char *country_code)
{
	return rltk_wlan_set_country_code(country_code);
}

int wifi_set_channel_plan(u8 channel_plan)
{
	return rltk_wlan_set_channel_plan(channel_plan);
}

void wifi_set_active_keepalive_enabled(u8 active_keepalive_enabled)
{
	wifi_user_config.active_keepalive_enabled = active_keepalive_enabled;
}

extern void get_wpa_global_PMK(unsigned char *key);
void wifi_get_wpa_global_PMK(unsigned char *key)
{
	get_wpa_global_PMK(key);
}

int wifi_connection_abort(void)
{
	extern int rtw_wx_connection_abort(void);
	return rtw_wx_connection_abort();
}

int wifi_cancel_connection(int mode)
{
	extern int rtw_wx_cancel_connection(int mode);
	return rtw_wx_cancel_connection(mode);
}
//----------------------------------------------------------------------------//

#endif	//#if CONFIG_WLAN
