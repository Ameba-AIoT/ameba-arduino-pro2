/******************************************************************************
 * Copyright (c) 2013-2016 Realtek Semiconductor Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
  ******************************************************************************
  * @file    wowlan_driver_api.h
  * @author
  * @version
  * @brief   This file provides the functions related to event handler mechanism.
  ******************************************************************************
  */
#ifndef __WIFI_WOWLAN_API_H__
#define __WIFI_WOWLAN_API_H__

#include "basic_types.h"
#include "wifi_constants.h"
#include "wifi_structures.h"
#include "wlan_intf.h"
#include "wifi_ind.h"
#include <platform_stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

//wowlan wakeup reasson
#define RX_DISASSOC                     0x04
#define RX_DEAUTH                       0x08
#define FW_DECISION_DISCONNECT          0x10
#define RX_UNICAST_PKT                  0x22
#define RX_HW_PATTERN_PKT               0x23
#define TX_TCP_SEND_LIMIT               0x69
#define RX_DHCP_NAK                     0x6A
#define DHCP_RETRY_LIMIT                0x6B
#define RX_MQTT_PATTERN_MATCH           0x6C
#define RX_MQTT_PUBLISH_WAKE            0x6D
#define RX_MQTT_MTU_LIMIT_PACKET        0x6E
#define RX_TCP_FROM_SERVER_TO           0x6F
#define FW_PNO_TIMEOUT                  0x71
#define FW_PNO_RECV_BCN_WAKEUP          0x72
#define FW_PNO_RECV_PROBE_RESP_WAKEUP   0x73
#define FW_BCN_TO_WAKEUP                0x74
#define RX_TCP_RST_FIN_PKT              0x75
#define RX_MQTT_PING_RSP_TO             0x76
#define RX_TCP_WITH_PAYLOAD             0x77
#define GPIO_WDT_TBTT_CHECK_ERROR       0x79
#define CSA_WAKE                        0x7A
#define BCN_DS_MISMATCH_WAKE            0x7B
#define RX_TCP_FIN_PKT                  0x7C
#define RX_TCP_RST_PKT                  0x7D
#define RX_ICMP_REPLY                   0x80
#define ICMP_MAX_SEND                   0x81
#define MQTT_FW_RX_TCP_PKT_WAKEUP       0x84

//wlan lib wowlan api

//Wakeup by receiving all MQTT publish in MQTT fw
void wifi_set_publish_wakeup(void);
//Provide switching between wowlan FW parser general tcp ssl packet and mqtt packet
void wifi_set_tcpssl_keepalive(void);
//Enable dhcp renew at wowlan
//return@
//1 for success, 0 for fail
int wifi_set_dhcp_offload(void);
//Offload ssl information to wowlan fw
//return@
//1 for success, 0 for fail
int wifi_set_ssl_offload(uint8_t *ctr, uint8_t *iv, uint8_t *enc_key, uint8_t *dec_key, uint8_t *hmac_key, uint8_t *content, size_t len, uint8_t is_etm);
//Enable the trx counter recording function of ssl packet during wowlan
void wifi_set_ssl_counter_report(void);
int rtw_get_random_bytes(void *dst, u32 size);
//Read wakeup reason after wifi pattern trigger waking up
//return@
//wowlan wakeup reason code
uint8_t rtl8735b_wowlan_wake_reason(void);
//Read wakeup pattern type after wifi pattern trigger waking up
//return@
//wowlan wakeup pattern
uint8_t rtl8735b_wowlan_wake_pattern(void);
//Read first wakeup pattern from RX buffer
//param@
//uint32_t *size                get packet length
//uint8_t wowlan_reason         input wowlan wakeup reason
//return@
//return the address of wakeup packet
uint8_t *rtl8735b_read_wakeup_packet(uint32_t *size, uint8_t wowlan_reason);
//Read wakeup pattern by index from RX buffer
//param@
//uint32_t *size                get packet length
//uint8_t index                 input the index of packet in rx buffer
//return@
//return the address of wakeup packet
uint8_t *rtl8735b_read_packet_with_index(uint32_t *size, uint8_t index);
//dump the buffer of ssl resume info as bellow
//IV value, decode key value, etm or not, ssl in counter, ssl out counter
uint8_t *rtl8735b_read_ssl_conuter_report(void);
//select wowlan fw version
//param@
//uint8_t ka                    wowlan fw version, and the version is as bellow
//                          	WOWLAN_NORMAL_BCNV1 = 0, /*0: normal fw with bcn tracking v1*/
//	                            WOWLAN_TCPPTL_BCNV2, /*1: tcp protocol keep alive with bcn tracking v2*/
//	                            WOWLAN_MQTT_BCNV2, /*2: mqtt keep alive with bcn tracking v2*/
//	                            WOWLAN_PNO,	/*3: only pno function*/
void rtl8735b_select_keepalive(u8 ka);
//save Wi-Fi connection status before standby
//return@
//1 for success, 0 for fail
int rtw_hal_wlan_resume_backup(void);
//To check if WLAN MCU is awake. When GPIO wakeup, must make sure WLAN MCU is awake before read data from WLAN FW. If WLAN FW is awake, rtw_hal_wowlan_check_wlan_mcu_wakeup API returns 1
//return@
//1 for success, 0 for fail
int rtw_hal_wowlan_check_wlan_mcu_wakeup(void);
//Enter wifi lps pg mode (wowlan)
//return@
//error code
int rtl8735b_suspend(int mode);
//Pre set lps pg information
//return@
//1 for success, 0 for fail
void rtl8735b_set_lps_pg(void);
//Set DTIM value for wowlan
//param@
//uint8_t dtim                  To set the beacon listen interval, the dtim vale setting range is 1 to 15.
void rtl8735b_set_lps_dtim(uint8_t dtim);
//WOWLAN_TCPPTL_BCNV2 and WOWLAN_MQTT_BCNV2
//Set beacon tracking stage1 parameters
//param@
//uint8_t rx_bcn_window         The max window length of the TBTT
//uint8_t bcn_limit             The max beacon loss num in stage1
void wifi_wowlan_bcntrack_stage1(uint8_t rx_bcn_window, uint8_t bcn_limit);
//Set broadcast/multicast packet wait timeout
//param@
//uint8_t set_dtimtimeout       The Max time for timeout, unit ms
void wifi_wowlan_set_dtimtimeout(uint8_t set_dtimtimeout);
//Set rx beacon limit (no weight)
//param@
//uint8_t set_dtimtimeout       The max length of TBTT (no weight), unit ms
void wifi_wowlan_set_rxbcnlimit(uint8_t set_rxbcnlimit);
//Set ps timeout
//param@
//uint8_t set_pstimeout         The max time for RX pkt
void wifi_wowlan_set_pstimeout(uint8_t set_pstimeout);
//Set ps retry
//param@
//uint8_t set_psretry           The max num for ps timeout
void wifi_wowlan_set_psretry(uint8_t set_psretry);
//Set arp request send period
//param@
//u8 period                     arp request send period, unit second, the min value is 20s
void rtw_hal_set_arpreq_period(u8 period);
//dtim level is (DTIM_period * bcn_interval) / 100
//return@
//return the dtim level
uint8_t rtl8735b_get_dynamic_dtim_level(void);
//Read debug infor frome wowlan fw
//param@
//uint8_t log_en                Enable print debug info
//retrun@
//return the address of debug info data buffer
uint8_t *read_rf_conuter_report(uint8_t log_en);
//get the current beacon count when wakeup
//return@
//Count how many of the 20 beacons are received at the moment of wake-up
uint32_t rtl8735b_get_wakeup_bcn_cnt(void);
//Count total sleep time
//return@
//total sleep time, unit second
uint64_t rtl8735b_wowlan_get_sleep_duration(void);
//Get the DTIM value brfore wakeup
//return@
//DTIM value
uint8_t rtl8735b_wowlan_get_pre_dtim(void);
//Get the wowlan wakeup reason when meet suspend fail
//return@
//wowlan wakeup reason
uint8_t rtw_hal_wowlan_get_suspend_wakeup_reason(void);
//Check it is suspend fail before AON Timer wakeup
//return@
//1 is for suspend fail, 0 is not
uint8_t rtw_hal_wowlan_get_suspend_fail(void);
//Read first wakeup pattern from RX buffer after suspend fail wakeup
//param@
//uint32_t *size                get packet length
//return@
//return the address of wakeup packet
u8 *rtw_hal_wowlan_get_suspend_wakeup_pattern(u32 *packet_len);
//Read wakeup pattern by index from RX buffer after suspend fail wakeup
//param@
//uint32_t *size                get packet length
//uint8_t index                 input the index of packet in rx buffer
//return@
//return the address of wakeup packet
u8 *rtw_hal_wowlan_get_suspend_wakeup_pattern_with_index(u32 *packet_len, u8 index);
//Check if Wi-Fi connection status is saved
//return@
//If saved Wi-Fi connection status is existed, rtw_hal_wlan_resume_check API returns 1
int rtw_hal_wlan_resume_check(void);
//Read security key from WLAN FW for WLAN resume
//param@
//u8 *buf                       Buffer used to read the data
//u16 addr                      Offset of WLAN FW FIFO data to be read
//u16 len                       Length of WLAN FW FIFO data to be read
//return@
//1 for success, 0 for fail
int rtw_hal_read_aoac_rpt_from_txfifo(u8 *buf, u16 addr, u16 len);
//read DHCP T1 time when wakeup
//return@
//DHCP T1 time
uint16_t rtw_hal_read_wowlan_t1_time(void);
//Resume Wi-Fi connection status based on saved data
//return@
//1 for success, 0 for fail
int rtw_hal_wlan_resume_restore(void);
//only WOWLAN_NORMAL_BCNV1
//Power saving mechanism could be adjusted through the setting of parameters
//param@
//uint8_t set_pstimeout         The max time for RX pkt
//uint8_t set_pstimeout_retry   The max num for ps timeout
//uint8_t set_rx_bcn_limit      The max length of TBTT (no weight), unit ms
//uint8_t set_dtimtimeout       The Max time for timeout, unit ms
//uint8_t set_bcn_to_limit      The max beacon loss num in stage1
void wifi_wowlan_set_pstune_param(uint8_t set_pstimeout, uint8_t set_pstimeout_retry, uint8_t set_rx_bcn_limit, uint8_t set_dtimtimeout,
								  uint8_t set_bcn_to_limit);
//only WOWLAN_NORMAL_BCNV1
//Wi-Fi disconnection decision policy is controlled by parameter
//param@
//u8  fwdis_period              the number of times that the beacon has not been received
//u8  fwdis_trypktnum           the number of non-acknowledged Null frame to trigger system wakeup
//u8  pno_enable                not use
//u8  pno_timeout               not use
//u8  l2_keepalive_period       arp request send period
//return@
////0 for success
int wifi_wowlan_set_fwdecision_param(u8  fwdis_period, u8  fwdis_trypktnum, u8  pno_enable, u8  pno_timeout, u8  l2_keepalive_period);


#ifdef	__cplusplus
}
#endif

#endif /* _WIFI_WOWLAN_API_H */
