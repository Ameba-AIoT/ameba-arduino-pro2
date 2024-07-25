#ifndef ETHERNET_USB_H
#define ETHERNET_USB_H

#include "lwip_netconf.h"

#define ETHERNET_IDX (NET_IF_NUM - 1)
#define WLAN_IDX 0
#define ECM_MAX_DNS_NUM 2
#define ECM_DCHP_RETRY_COUNT 2
enum ecm_status {
	ECM_STATUS_NONE,
	ECM_STATUS_START,
	ECM_STATUS_DEINIT
};

enum ecm_disconnect_status {
	ECM_USB_CABLE_DETACH,
	ECM_ETH_CABLE_DETACH
};
enum ecm_lwip_connect_type {
	ECM_LWIP_DHCP_MODE,
	ECM_LWIP_STATIC_IP_MODE
};

typedef struct {
	const char *ip;
	const char *netmask;
	const char *gw;
	const char *dns1;
	const char *dns2;
	int dns_num;
} ecm_static_ip_info;

typedef struct {
	unsigned int ip_addr;
	unsigned int netmask;
	unsigned int gw;
	ip_addr_t dnsserver1;
	ip_addr_t dnsserver2;
	unsigned int dns_num;
} ecm_static_ip_attr_t;

void ethernet_usb_init(void);
void ethernet_usb_deinit(void);
void ecm_setup_static_ip_param(ecm_static_ip_info *attr);
void ecm_lwip_setup_connect_mode(int mode);
void ecm_lwip_dhcp_retry_setup(int count);
int ecm_lwip_dhcp_status(void);// -1 = idle, other is DHCP_State_TypeDef status
int ecm_lwip_switch_connect_mode(void);//Change the connect mode. First : ecm_lwip_setup_connect_mode. Second : Use the API to change the connect mode.
void ecm_lwip_init(void);
void ecm_lwip_deinit(void);
int ecm_lwip_static_ip_status(void);//-1 = non-connect 1 connect
int ecm_lwip_check_ip(char *ip);// -1: The ip is not be used. Other, the ip is be used.
#endif // __USB_ETHERNETIF_H__