#include "wifi_drv.h"

// arduino includes
#include "wl_definitions.h"
#include "wl_types.h"
#include "wiring.h"
#include "wifi_conf.h"

#undef CONFIG_LWIP_DHCP_COARSE_TIMER //Remove redfinition warning
#ifdef __cplusplus
extern "C" {
#endif

// RTK includes
#include "main.h"
#include "wifi_constants.h"
#include "wifi_structures.h"
#include "lwip_netconf.h"
#include "wifi_fast_connect.h"
#include "lwip/err.h"
#include "osdep_service.h"
// modifed here
#include "lwip/netif.h"
#include "lwip/api.h"
#include <dhcp/dhcps.h>
#include "ard_socket.h"

extern struct netif xnetif[NET_IF_NUM];
#ifdef __cplusplus
}
#endif

// Array of data to cache the information related to the networks discovered
uint8_t     WiFiDrv::_networkCount = 0;
char        WiFiDrv::_networkSsid[][WL_SSID_MAX_LENGTH] = {{"1"}, {"2"}, {"3"}, {"4"}, {"5"}};
int32_t     WiFiDrv::_networkRssi[WL_NETWORKS_LIST_MAXNUM] = {0};
uint32_t    WiFiDrv::_networkEncr[WL_NETWORKS_LIST_MAXNUM] = {0};

static bool init_wlan = false;
//static int wifi_mode = NULL;
rtw_mode_t wifi_mode = RTW_MODE_STA;
struct static_ip_config user_static_ip;

static rtw_network_info_t wifi;
static rtw_softap_info_t ap = {0};
static unsigned char password[65] = {0};

rtw_wifi_setting_t WiFiDrv::wifi_setting;

IPAddress WiFiDrv::_arduinoIpAddr = IPAddress(192, 168, 1, 80);
IPAddress WiFiDrv::_arduinoGwAddr = IPAddress(192, 168, 1, 1);
IPAddress WiFiDrv::_arduinoNetmaskAddr = IPAddress(255, 255, 255, 0);
IPAddress WiFiDrv::_arduinoApIpAddr = IPAddress(192, 168, 1, 1);
IPAddress WiFiDrv::_arduinoApGwAddr = IPAddress(192, 168, 1, 1);
IPAddress WiFiDrv::_arduinoApNetmaskAddr = IPAddress(255, 255, 255, 0);
IPAddress WiFiDrv::_arduinoDns1;
IPAddress WiFiDrv::_arduinoDns2;
bool WiFiDrv::_useStaticIp = false;
char WiFiDrv::_hostname[HOSTNAME_LEN+1] = {0};

static void init_wifi_struct(void) {
    memset(wifi.ssid.val, 0, sizeof(wifi.ssid.val));
    memset(wifi.bssid.octet, 0, ETH_ALEN);
    memset(password, 0, sizeof(password));
    wifi.ssid.len = 0;
    wifi.password = NULL;
    wifi.password_len = 0;
    wifi.key_id = -1;
    memset(ap.ssid.val, 0, sizeof(ap.ssid.val));
    ap.ssid.len = 0;
    ap.password = NULL;
    ap.password_len = 0;
    ap.channel = 1;
}

void WiFiDrv::wifiDriverInit() {
    struct netif * pnetif = &xnetif[0];
    if (init_wlan == false) {
        init_wlan = true;
        LwIP_Init();
        wifi_on(RTW_MODE_STA);
        wifi_mode = RTW_MODE_STA;
    } else if (init_wlan == true) {
        if (wifi_mode != RTW_MODE_STA) {
            dhcps_deinit();
            wifi_off();
            vTaskDelay(20);
            wifi_on(RTW_MODE_STA);
            dhcps_init(pnetif);
            wifi_mode = RTW_MODE_STA;
        }
    }
}

int8_t WiFiDrv::wifiSetNetwork(char* ssid, uint8_t ssid_len) {
    int ret;
    uint8_t dhcp_result;

    memset(wifi.bssid.octet, 0, ETH_ALEN);
    memcpy(wifi.ssid.val, ssid, ssid_len);
    wifi.ssid.len = ssid_len;

    wifi.security_type = RTW_SECURITY_OPEN;
    wifi.password = NULL;
    wifi.password_len = 0;
    wifi.key_id = 0;

    ret = wifi_connect(&wifi, 1);

    if (ret == RTW_SUCCESS) {
        init_wifi_struct();

        if (_useStaticIp) {
            struct ip_addr ipaddr;
            struct ip_addr netmask;
            struct ip_addr gw;
            struct netif* pnetif = &xnetif[0];
            // modified here
//            if (getIPv6Status() == 0) {
                printf("IPv6 is disabled\n\r");
                IP4_ADDR(ip_2_ip4(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
                IP4_ADDR(ip_2_ip4(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
                IP4_ADDR(ip_2_ip4(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
                netif_set_addr(pnetif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));
//            } else {
//                printf("IPv6 is enabled\n\r");
//                IP6_ADDR(ip_2_ip6(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
//                IP6_ADDR(ip_2_ip6(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
//                IP6_ADDR(ip_2_ip6(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
//                // requires to modify this line
//                // netif.h
//                netif_ip6_addr_set(pnetif, 3, ip_2_ip6(&ipaddr));
//            }
            return WL_SUCCESS;
        } else {
            netif_set_hostname(&xnetif[0], getHostname());
            dhcp_result = LwIP_DHCP(0, DHCP_START);
            if (dhcp_result == DHCP_ADDRESS_ASSIGNED) {
                return WL_SUCCESS;
            } else {
                wifi_disconnect();
                return WL_FAILURE;
            }
        }
    } else {
        init_wifi_struct();
        return WL_FAILURE;
    }
}

int8_t WiFiDrv::wifiSetPassphrase(char* ssid, uint8_t ssid_len, const char* passphrase, const uint8_t len) {
    int ret;
    uint8_t dhcp_result;

    memset(wifi.bssid.octet, 0, ETH_ALEN);
    memcpy(wifi.ssid.val, ssid, ssid_len);
    wifi.ssid.len = ssid_len;

    wifi.security_type = RTW_SECURITY_WPA2_AES_PSK;

    memset(password, 0, sizeof(password));

    memcpy(password, passphrase, len);
    wifi.password = password;
    wifi.password_len = len;
    wifi.key_id = 0;

    ret = wifi_connect(&wifi, 1);

    if (ret == RTW_SUCCESS) {
        init_wifi_struct();

        if (_useStaticIp) {
            struct ip_addr ipaddr;
            struct ip_addr netmask;
            struct ip_addr gw;
            struct netif* pnetif = &xnetif[0];
//            if (getIPv6Status() == 0) {
                printf("IPv6 is disabled\n\r");
                IP4_ADDR(ip_2_ip4(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
                IP4_ADDR(ip_2_ip4(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
                IP4_ADDR(ip_2_ip4(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
                netif_set_addr(pnetif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));
//            } else {
//                printf("IPv6 is enabled\n\r");
//                IP6_ADDR(ip_2_ip6(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
//                IP6_ADDR(ip_2_ip6(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
//                IP6_ADDR(ip_2_ip6(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
//                // requires to modify this line in netif.h
//                netif_ip6_addr_set(pnetif, 3, ip_2_ip6(&ipaddr));
//            }
            return WL_SUCCESS;
        } else {
            netif_set_hostname(&xnetif[0], getHostname());
            dhcp_result = LwIP_DHCP(0, DHCP_START);
            if (dhcp_result == DHCP_ADDRESS_ASSIGNED) {
                return WL_SUCCESS;
            } else {
                wifi_disconnect();
                return WL_FAILURE;
            }
        }
    } else {
        init_wifi_struct();
        return WL_FAILURE;
    }
}

int8_t WiFiDrv::wifiSetKey(char* ssid, uint8_t ssid_len, uint8_t key_idx, const void* key, const uint8_t len) {
    int ret;
    uint8_t dhcp_result;

    memset(wifi.bssid.octet, 0, ETH_ALEN);
    memcpy(wifi.ssid.val, ssid, ssid_len);
    wifi.ssid.len = ssid_len;

    wifi.security_type = RTW_SECURITY_WEP_PSK;
    memset(password, 0, sizeof(password));

#if 0
    const unsigned char* k = (const unsigned char *)key;
    // convert hex sring to hex value
    for (int i = 0,int idx = 0; i < len; i++) {
        if ((k[i] >= '0') && (k[i] <= '9')) {
            password[idx] += (k[i] - '0');
        } else if ((k[i] >= 'a') && (k[i] <= 'f')) {
            password[idx] += (k[i] - 'a' + 10);
        } else if ((k[i] >= 'A') && (k[i] <= 'F')) {
            password[idx] += (k[i] - 'A' + 10);
        }

        if (i % 2 == 0) {
            password[idx] *= 16;
        } else {
            idx++;
        }
    }

    wifi.password = password;
    wifi.password_len = len/2;
    wifi.key_id = key_idx;
#else
    memcpy(password, key, len);

    wifi.password = password;
    wifi.password_len = len;
    wifi.key_id = key_idx;
#endif

    ret = wifi_connect(&wifi, 1);

    if (ret == RTW_SUCCESS) {
        init_wifi_struct();

        if (_useStaticIp) {
            struct ip_addr ipaddr;
            struct ip_addr netmask;
            struct ip_addr gw;
            struct netif* pnetif = &xnetif[0];

//            if (getIPv6Status() == 0) {
                printf("IPv4 enabled\n\r");
                IP4_ADDR(ip_2_ip4(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
                IP4_ADDR(ip_2_ip4(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
                IP4_ADDR(ip_2_ip4(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
                netif_set_addr(pnetif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));
//            }

//            else {
//                printf("IPv6 enabled\n\r");
//                IP6_ADDR(ip_2_ip6(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
//                IP6_ADDR(ip_2_ip6(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
//                IP6_ADDR(ip_2_ip6(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
//                // requires to modify this line
//                // netif.h
//                netif_ip6_addr_set(pnetif, 3, ip_2_ip6(&ipaddr));
//            }
            return WL_SUCCESS;
        } else {
            netif_set_hostname(&xnetif[0], getHostname());
            dhcp_result = LwIP_DHCP(0, DHCP_START);
            if (dhcp_result == DHCP_ADDRESS_ASSIGNED) {
                return WL_SUCCESS;
            } else {
                wifi_disconnect();
                return WL_FAILURE;
            }
        }
    } else {
        init_wifi_struct();
        return WL_FAILURE;
    }
}

int8_t WiFiDrv::apSetNetwork(char* ssid, uint8_t ssid_len) {
    int ret = WL_SUCCESS;

    ap.ssid.len = ssid_len;

    if (ap.ssid.len > 32) {
        printf("Error: SSID length can't exceed 32\n\r");
        ret = WL_FAILURE;
    }
    strcpy((char *)ap.ssid.val, (char*)ssid);
    return ret;
}

int8_t WiFiDrv::apSetPassphrase(const char *passphrase, uint8_t len) {
    int ret = WL_SUCCESS;
    strcpy((char *)password, (char*)passphrase);
    ap.password = password;
    ap.password_len = len;
    if (ap.password_len < 8) {
        printf("Error: Password length can't less than 8\n\r");
        ret = WL_FAILURE;
    }
    return ret;
}

int8_t WiFiDrv::apSetChannel(const char *channel) {
    int ret = WL_SUCCESS;
    ap.channel = (unsigned char) atoi((const char *)channel);
    return ret;
}

int8_t WiFiDrv::apActivate(uint8_t hidden_ssid) {
#if CONFIG_LWIP_LAYER
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;
    struct netif * pnetif = &xnetif[0];
#endif
    int timeout = 20;
    int ret = WL_SUCCESS;
    if (ap.ssid.val[0] == 0) {
        printf("Error: SSID can't be empty\n\r");
        ret = WL_FAILURE;
        goto exit;
    }
    if (ap.password == NULL) {
        ap.security_type = RTW_SECURITY_OPEN;
    } else {
        ap.security_type = RTW_SECURITY_WPA2_AES_PSK;
    }

#if CONFIG_LWIP_LAYER
    dhcps_deinit();

//    if (getIPv6Status() == 0) {
        printf("IPv4 enabled\n\r");
        IP4_ADDR(ip_2_ip4(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
        IP4_ADDR(ip_2_ip4(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
        IP4_ADDR(ip_2_ip4(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
        netif_set_addr(pnetif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));
//    } else {
//        printf("IPv6 enabled\n\r");
//        IP6_ADDR(ip_2_ip6(&ipaddr), _arduinoIpAddr[0], _arduinoIpAddr[1], _arduinoIpAddr[2], _arduinoIpAddr[3]);
//        IP6_ADDR(ip_2_ip6(&netmask), _arduinoNetmaskAddr[0], _arduinoNetmaskAddr[1], _arduinoNetmaskAddr[2], _arduinoNetmaskAddr[3]);
//        IP6_ADDR(ip_2_ip6(&gw), _arduinoGwAddr[0], _arduinoGwAddr[1], _arduinoGwAddr[2], _arduinoGwAddr[3]);
//        // requires to modify this line
//        // netif.h
//        netif_ip6_addr_set(pnetif, 3, ip_2_ip6(&ipaddr));
//    }
#endif
    wifi_off();
    vTaskDelay(20);
    if (wifi_on(RTW_MODE_AP) < 0) {
        printf("\n\rERROR: Wifi on failed!");
        ret = WL_FAILURE;
        goto exit;
    }
    printf("\n\rStarting AP ...");

    if (hidden_ssid == 1) {
        ap.hidden_ssid = 1;
    }

    if ((ret = wifi_start_ap(&ap)) < 0) {
        printf("\n\rERROR: Operation failed!");
        ret = WL_FAILURE;
        goto exit;
    }

    while (1) {
        wifi_get_setting(WLAN0_IDX, &wifi_setting);
        if (strlen((const char *)wifi_setting.ssid) > 0) {
            if (strcmp((const char *)wifi_setting.ssid, ((const char *)ap.ssid.val)) == 0) {
                printf("\n\r%s started\n", ap.ssid.val);
                ret = WL_SUCCESS;
                break;
            }
        }

        if (timeout == 0) {
            printf("\n\rERROR: Start AP timeout!");
            ret = WL_FAILURE;
            break;
        }

        vTaskDelay(1 * configTICK_RATE_HZ);
        timeout--;
    }
#if CONFIG_LWIP_LAYER
    //LwIP_UseStaticIP(pnetif);
    IP4_ADDR(ip_2_ip4(&ipaddr), _arduinoApIpAddr[0], _arduinoApIpAddr[1], _arduinoApIpAddr[2], _arduinoApIpAddr[3]);
    IP4_ADDR(ip_2_ip4(&netmask), _arduinoApNetmaskAddr[0], _arduinoApNetmaskAddr[1], _arduinoApNetmaskAddr[2], _arduinoApNetmaskAddr[3]);
    IP4_ADDR(ip_2_ip4(&gw), _arduinoApGwAddr[0], _arduinoApGwAddr[1], _arduinoApGwAddr[2], _arduinoApGwAddr[3]);
    netif_set_addr(pnetif, ip_2_ip4(&ipaddr), ip_2_ip4(&netmask), ip_2_ip4(&gw));
    dhcps_init(pnetif);
#endif

exit:
    init_wifi_struct();
    if (ret == WL_SUCCESS) {
        wifi_mode = RTW_MODE_AP;
    }
    return ret;
}


int8_t WiFiDrv::disconnect() {
    wifi_disconnect();
    return WL_DISCONNECTED;
}

uint8_t WiFiDrv::getConnectionStatus() {
    wifiDriverInit();

    if (wifi_is_connected_to_ap() == 0) {
        return WL_CONNECTED;
    } else {
        return WL_DISCONNECTED;
    }
}

uint8_t* WiFiDrv::getMacAddress() {
    return LwIP_GetMAC(0);
}

void WiFiDrv::getIpAddress(IPAddress& ip) {
    ip = LwIP_GetIP(0);
}

#if 0
void WiFiDrv::getIpv6Address() {
    LwIP_AUTOIP_IPv6(&xnetif[0]);
    while (!ip6_addr_isvalid(netif_ip6_addr_state(&xnetif[0],0))) {
        vTaskDelay(10);
    }
}
#endif

void WiFiDrv::getSubnetMask(IPAddress& mask) {
    mask = LwIP_GetMASK(0);
}

void WiFiDrv::getGatewayIP(IPAddress& ip) {
    ip = LwIP_GetGW(0);
}

char* WiFiDrv::getCurrentSSID() {
    wifi_get_setting(WLAN0_IDX, &wifi_setting);
    return (char *)(wifi_setting.ssid);
}

uint8_t* WiFiDrv::getCurrentBSSID() {
    wifi_get_setting(WLAN0_IDX, &wifi_setting);
    return (uint8_t *)(wifi_setting.bssid);
}

int32_t WiFiDrv::getCurrentRSSI() {
    rtw_phy_statistics_t phy_statistics;
    wifi_fetch_phy_statistic(&phy_statistics);
    return phy_statistics.rssi;
}

uint8_t WiFiDrv::getCurrentEncryptionType() {
    wifi_get_setting(WLAN0_IDX, &wifi_setting);
    return (wifi_setting.security_type);
}

rtw_result_t WiFiDrv::wifidrv_scan_result_handler(unsigned int scanned_AP_num, void *user_data) {
    (void) user_data;
    char *scan_buf = NULL;
    rtw_scan_result_t *scanned_AP_info;
    if (scanned_AP_num == 0) {
        return RTW_ERROR;
    }

// Check if no of AP will be more than the max number
    if (scanned_AP_num > WL_NETWORKS_LIST_MAXNUM) {
        scanned_AP_num = WL_NETWORKS_LIST_MAXNUM;
    }

    scan_buf = (char *)malloc(scanned_AP_num * sizeof(rtw_scan_result_t));
    if (scan_buf == NULL) {
        return RTW_ERROR;
    }
    memset(scan_buf, 0, scanned_AP_num * sizeof(rtw_scan_result_t));

    if (wifi_get_scan_records(&scanned_AP_num, scan_buf) < 0) {
        free(scan_buf);
        return RTW_ERROR;
    }

    for (uint8_t i = 0; i < scanned_AP_num; i++) {
        scanned_AP_info = (rtw_scan_result_t *)(scan_buf + i * sizeof(rtw_scan_result_t));
        scanned_AP_info->SSID.val[scanned_AP_info->SSID.len] = 0; /* Ensure the SSID is null terminated */

        strcpy(_networkSsid[_networkCount], (char *)scanned_AP_info->SSID.val);
        _networkRssi[_networkCount] = scanned_AP_info->signal_strength;
        _networkEncr[_networkCount] = scanned_AP_info->security;
        _networkCount++;
    }

    if (_networkCount != scanned_AP_num) {
        printf("count != num\r\n");
    }

    free(scan_buf);
    return RTW_SUCCESS;
}

int8_t WiFiDrv::startScanNetworks() {
    _networkCount = 0;
    //rtw_scan_param_t  scan_param = {0};
    rtw_scan_param_t  scan_param;
    rtw_memset(&scan_param, 0, sizeof(rtw_scan_param_t));
    scan_param.scan_user_callback = wifidrv_scan_result_handler;
    if (wifi_scan_networks(&scan_param, 0 ) != RTW_SUCCESS) {
        return WL_FAILURE;
    }

    return WL_SUCCESS;
}

uint8_t WiFiDrv::getScanNetworks() {
    return _networkCount;
}

char* WiFiDrv::getSSIDNetworks(uint8_t networkItem) {
    if (networkItem >= WL_NETWORKS_LIST_MAXNUM) {
        return NULL;
    }

    return _networkSsid[networkItem];
}

uint8_t WiFiDrv::getEncTypeNetworks(uint8_t networkItem) {
    if (networkItem >= WL_NETWORKS_LIST_MAXNUM) {
        //return NULL;
        return 0;
    }

    uint8_t encType = 0;

    if (_networkEncr[networkItem] == RTW_SECURITY_OPEN) {
        encType = ENC_TYPE_NONE;
    } else if (_networkEncr[networkItem] & WPA3_SECURITY) {
        encType = ENC_TYPE_WPA3;
    } else if (_networkEncr[networkItem] & WPA2_SECURITY) {
        encType = ENC_TYPE_WPA2;
    } else if (_networkEncr[networkItem] & WPA_SECURITY) {
        encType = ENC_TYPE_WPA;
    } else if (_networkEncr[networkItem] & WEP_ENABLED) {
        encType = ENC_TYPE_WEP;
    }

    return encType;
}

uint32_t WiFiDrv::getEncTypeNetworksEx(uint8_t networkItem) {
    //return ((networkItem >= WL_NETWORKS_LIST_MAXNUM) ? NULL : _networkEncr[networkItem]);
    return ((networkItem >= WL_NETWORKS_LIST_MAXNUM) ? 0 : _networkEncr[networkItem]);
}

int32_t WiFiDrv::getRSSINetworks(uint8_t networkItem) {
    if (networkItem >= WL_NETWORKS_LIST_MAXNUM) {
        //return NULL;
        return 0;
    }

    return _networkRssi[networkItem];
}

char* WiFiDrv::getFwVersion() {
    // The version is for compatible to arduino example code
    return "1.0.0";
}

int WiFiDrv::getHostByName(const char* aHostname, IPAddress& aResult) {
    ip_addr_t ip_addr;
    err_t err;
    err = netconn_gethostbyname_addrtype(aHostname, &ip_addr, NETCONN_DNS_IPV4);
    if (err != ERR_OK) {
        return WL_FAILURE;
    } else {
        aResult = ip_addr.u_addr.ip4.addr;
        return WL_SUCCESS;
    }
}

#if 0
int WiFiDrv::getHostByNamev6(const char* aHostname, IPv6Address& aResult) {

    printf("[INFO]wifi_drv.cpp: getHostByNamev6()\n\r");
    ip_addr_t ip_addr;
    err_t err;   
#if 0
    printf("[INFO]wifi_drv.cpp:  0 ip address: %x\n\r", ip_addr.u_addr.ip6.addr[0]);
    printf("[INFO]wifi_drv.cpp:  1 ip address: %x\n\r", ip_addr.u_addr.ip6.addr[1]);
    printf("[INFO]wifi_drv.cpp:  2 ip address: %x\n\r", ip_addr.u_addr.ip6.addr[2]);
    printf("[INFO]wifi_drv.cpp:  3 ip address: %x\n\r", ip_addr.u_addr.ip6.addr[3]);
#endif
    err = netconn_gethostbyname_addrtype(aHostname, &ip_addr, NETCONN_DNS_IPV6);
    if (err != ERR_OK) {
        return WL_FAILURE;
    } else {
        printf("[INFO]wifi_drv.cpp: netconn_gethostbyname done\n\r");
        for (int xx = 0; xx < 4; xx++) {
            aResult._address.dword[xx] = ip_addr.u_addr.ip6.addr[xx];
        }
#if 0
        printf("[INFO]wifi_drv.cpp:  0 dword: %x\n\r", aResult._address.dword[0]);
        printf("[INFO]wifi_drv.cpp:  1 dword: %x\n\r", aResult._address.dword[1]);
        printf("[INFO]wifi_drv.cpp:  2 dword: %x\n\r", aResult._address.dword[2]);
        printf("[INFO]wifi_drv.cpp:  3 dword: %x\n\r", aResult._address.dword[3]);
#endif
        return WL_SUCCESS;
    }
}
#endif 

int WiFiDrv::disablePowerSave() {
    return wifi_set_powersave_mode(1, 1);
}

void WiFiDrv::config(uint8_t validParams, IPAddress local_ip, IPAddress gateway, IPAddress subnet) {

    if (validParams == 1) {
        _arduinoIpAddr = local_ip;
        _arduinoApIpAddr = local_ip;
    } else if (validParams == 2) {
        _arduinoIpAddr = local_ip;
        _arduinoGwAddr = gateway;
        _arduinoApIpAddr = local_ip;
        _arduinoApGwAddr = gateway;
    } else if (validParams == 3) {
        _arduinoIpAddr = local_ip;
        _arduinoGwAddr = gateway;
        _arduinoNetmaskAddr = subnet;
        _arduinoApIpAddr = local_ip;
        _arduinoApGwAddr = gateway;
        _arduinoApNetmaskAddr = subnet;
    } else {
        return;
    }

    _useStaticIp = true;
}

void WiFiDrv::setDNS(uint8_t validParams, IPAddress dns_server1, IPAddress dns_server2) {
    struct ip_addr dns;

    if (validParams == 1) {
        _arduinoDns1 = dns_server1;
    } else if (validParams == 2) {
        _arduinoDns1 = dns_server1;
        _arduinoDns2 = dns_server2;
    } else {
        return;
    }

//    if (getIPv6Status() == 0) {
        IP4_ADDR(ip_2_ip4(&dns), _arduinoDns1[0], _arduinoDns1[1], _arduinoDns1[2], _arduinoDns1[3]);
//    } else {
//          IP6_ADDR(ip_2_ip6(&dns), _arduinoDns1[0], _arduinoDns1[1], _arduinoDns1[2], _arduinoDns1[3]);
//    }
    LwIP_SetDNS(&dns);
}

#if 0
int WiFiDrv::getIPv6Status() {
    return get_ipv6_status();
}
#endif

void WiFiDrv::setHostname(const char* hostname) {
    if (hostname) {
        snprintf(_hostname, HOSTNAME_LEN, "%s", hostname);
    }
}

const char* WiFiDrv::getHostname() {
    if (_hostname[0] == 0) {
        uint8_t* eth_mac = NULL;
        eth_mac = getMacAddress();
        snprintf(_hostname, HOSTNAME_LEN, "%s%02X%02X%02X", "Ameba_", eth_mac[3], eth_mac[4], eth_mac[5]);
    }
    return (const char *)_hostname;
}

WiFiDrv wiFiDrv;
