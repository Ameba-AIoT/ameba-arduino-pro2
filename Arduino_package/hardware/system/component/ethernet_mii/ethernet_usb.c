#include <platform_opts.h>
#include <platform_stdlib.h>
#include "usbh.h"
#include "osdep_service.h"
#include "usbh_cdc_ecm.h"
#include "usbh_cdc_ecm_hal.h"
#include "log_service.h"
#include "ethernet_usb.h"

#ifdef PLATFORM_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#endif
#include "osdep_service.h"
#include "lwip_netconf.h"
#include "lwip_intf.h"
#include "platform_opts.h"

#if(CONFIG_ETHERNET == 1 && ETHERNET_INTERFACE == USB_INTERFACE)

#define ETHERNET_IDX (NET_IF_NUM - 1)

extern struct netif  xnetif[NET_IF_NUM];

//static u8 TX_BUFFER[1536];
//static u8 RX_BUFFER[1536];

static u8 *TX_BUFFER;
static u8 *RX_BUFFER;
static _mutex mii_tx_mutex;
static _mutex mii_link_mutex;

static struct task_struct task_ecm_attach;
static struct task_struct task_ecm_detach;

extern int lwip_init_done;

#define USBH_ECM_THREAD_STACK_SIZE 2048
//#define ECM_STATIC_IP_TEST

void usb_ethernet_ecm_cb(u8 *buf, u32 len);

static _sema ecm_detach_sema = NULL;
static _sema ecm_attach_sema = NULL;

static u32 rx_buffer_saved_data = 0;
static u32 ip_total_len = 0;
static int ecm_status = ECM_STATUS_NONE;
static int lwip_status = 0;
static int lwip_connect_mode = ECM_LWIP_DHCP_MODE;
static ecm_static_ip_attr_t static_ip_attr;
static int detach_mode = 0; //0 USB Detach 1 Ethenet Detach
static int lwip_dhcp_retry_count = ECM_DCHP_RETRY_COUNT;
static int lwip_dhcp_status = -1;
u8 multi_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static bool ecm_flg = false;
static int lwip_static_ip_status = -1;

//#define ECM_MONITOR_MODE //If the usb is detach that it will initial the ecm to get the attach

static void usb_cdc_ecm_attach_cb(void)
{
	//rtw_up_sema(&ecm_attach_sema);
}

static void usb_cdc_ecm_detach_cb(void)
{
	detach_mode = ECM_USB_CABLE_DETACH;
	rtw_up_sema(&ecm_detach_sema);
}

void ecm_lwip_setup_connect_mode(int mode)
{
	if (mode <= 1) {
		lwip_connect_mode = mode;
	} else {
		printf("The mode is not supported\r\n");
	}
}

int ecm_lwip_dhcp_status(void)
{
	return lwip_dhcp_status;
}

int ecm_lwip_static_ip_status(void)
{
	return lwip_static_ip_status;
}

int ecm_lwip_check_ip(char *ip)
{
	int ret = 0;
	struct eth_addr *dhcp_dst_eth_ret = NULL;
	ip4_addr_t *dhcp_dst_ip_ret = NULL;
	ip4_addr_t target_ip;
	ip4addr_aton(ip, &target_ip);
	LwIP_etharp_request(2, &target_ip);
	vTaskDelay(10);
	ret = LwIP_etharp_find_addr(2, &target_ip, &dhcp_dst_eth_ret, (const ip4_addr_t **)&dhcp_dst_ip_ret);
	printf("ecm_lwip_check_ip ret %d\r\n", ret);
	return ret;
}

void ecm_setup_static_ip_param(ecm_static_ip_info *attr)
{
	int ret = 0;
	ip_addr_t dnsserver;
	static_ip_attr.ip_addr = PP_HTONL(inet_addr(attr->ip));
	static_ip_attr.netmask = PP_HTONL(inet_addr(attr->netmask));
	static_ip_attr.gw = PP_HTONL(inet_addr(attr->gw));
	if (attr->dns_num > ECM_MAX_DNS_NUM) {
		static_ip_attr.dns_num = ECM_MAX_DNS_NUM;
	} else {
		static_ip_attr.dns_num = attr->dns_num;
	}
	for (int i = 0; i < static_ip_attr.dns_num; i++) {
		if (i == 0) {
			ip4_addr_set_u32(&static_ip_attr.dnsserver1, ipaddr_addr(attr->dns1));
		} else if (i == 1) {
			ip4_addr_set_u32(&static_ip_attr.dnsserver2, ipaddr_addr(attr->dns2));
		}
	}
}

int ecm_lwip_static_ip(int idx)
{
	int ret = 0;
	struct in_addr ip_addr;
	ip_addr.s_addr = PP_HTONL(static_ip_attr.ip_addr);
	char *ip = inet_ntoa(ip_addr);
	printf("ip_addr %s\r\n", ip);
	ret = ecm_lwip_check_ip(ip);
	if (ret < 0) {
		LwIP_SetIP(idx, static_ip_attr.ip_addr, static_ip_attr.netmask, static_ip_attr.gw);
		for (int i = 0; i < static_ip_attr.dns_num; i++) {
			if (i == 0) {
				dns_setserver(i, &static_ip_attr.dnsserver1);
			} else if (i == 1) {
				dns_setserver(i, &static_ip_attr.dnsserver2);
			}
		}
		printf("Static ip setup finish\r\n");
		lwip_static_ip_status = 1;
		ret = 0;
	} else {
		printf("Duplicate ip conflict\r\n");
		lwip_static_ip_status = -1;
		ret = -1;
	}
	return ret;
}

void ecm_lwip_dhcp_retry_setup(int count)
{
	if (count > 0) {
		lwip_dhcp_retry_count = count;
	} else {
		printf("The retry count need to bigger than zero %d\r\n", count);
	}
}

int ecm_lwip_dhcp(int idx)
{
	int dhcp_status = 0;
	int ret = 0;
	for (int i = 0; i < lwip_dhcp_retry_count; i++) {
		lwip_dhcp_status = DHCP_START;
		dhcp_status = LwIP_DHCP(idx, DHCP_START);
		if (DHCP_ADDRESS_ASSIGNED == dhcp_status) {
			printf("DHCP Successful\r\n");
			ret = 0;
			break;
		} else {
			printf("It can't get the DHCP\r\n");
			ret = -1;
			if (lwip_status == 0) {
				break;
			}
		}
	}
	lwip_dhcp_status = dhcp_status;
	return ret;
}

int ecm_lwip_switch_connect_mode(void)
{
	int ret = 0;
	if (usbh_cdc_ecm_get_connect_status()) {
		lwip_status = 0;
		//dhcp_stop(&xnetif[ETHERNET_IDX]);
		LwIP_DHCP_stop(ETHERNET_IDX);
		ecm_lwip_deinit();
		lwip_status = 1;
		ecm_lwip_init();
		if (lwip_connect_mode == ECM_LWIP_DHCP_MODE) {
			if (DHCP_ADDRESS_ASSIGNED != lwip_dhcp_status) {
				printf("It can't switch the mode\r\n");
				ret = -1;
			}
		}
	} else {
		printf("The ethernet is not connect\r\n");
		ret = -1;
	}
	return ret;
}

int ecm_lwip_connect_mode(int idx, int mode) //0
{
	int ret = 0;
	if (mode == ECM_LWIP_DHCP_MODE) {
		ret = ecm_lwip_dhcp(idx);
	} else if (mode == ECM_LWIP_STATIC_IP_MODE) {
		ret = ecm_lwip_static_ip(idx);
	} else {
		printf("The mode is not support %d\r\n", mode);
		ret = -1;
	}
	return ret;
}
void ecm_lwip_init(void)//Connect to lwip
{
	int link_is_up = 0;
	int dhcp_status = 0;
	printf("ecm lwip init\r\n");
	//Wait the ethernet ready
	while (1) {
		link_is_up = usbh_cdc_ecm_get_connect_status();
		if (link_is_up) {
			break;
		} else {
			vTaskDelay(100);
		}
	}

	u8 *mac = (unsigned char *)usbh_cdc_ecm_process_mac_str();
	//If no mac address that we will set the fake mac address
	if (mac[0] == 0 && mac[1] == 0 && mac[2] == 0 && mac[3] == 0 && mac[4] == 0 && mac[5] == 0) {
		mac[0] = 0x00;
		mac[1] = 0xe0;
		mac[2] = 0x4c;
		mac[3] = 0x36;
		mac[4] = 0x00;
		mac[5] = 0x02;
	}
	printf("mac[%02x %02x %02x %02x %02x %02x]\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	for (int i = 0; i < 6; i++) {
		multi_mac[i] = mac[i];
	}

	memcpy(xnetif[NET_IF_NUM - 1].hwaddr, mac, 6);

	if (!netif_is_link_up(&xnetif[ETHERNET_IDX])) {
		printf("Lwip link up\r\n");
		netif_set_link_up(&xnetif[ETHERNET_IDX]);
		netif_set_up(&xnetif[ETHERNET_IDX]);
	}

	if (!ecm_lwip_connect_mode(NET_IF_NUM - 1, lwip_connect_mode)) {
		netif_set_default(&xnetif[NET_IF_NUM - 1]);
	}
}

void ecm_lwip_deinit(void)//disconnect to lwip
{
	netif_set_default(&xnetif[0]);
	LwIP_ReleaseIP(ETHERNET_IDX);
	lwip_dhcp_status = DHCP_STOP;
	if (netif_is_link_up(&xnetif[ETHERNET_IDX])) {
		printf("Lwip link down\r\n");
		netif_set_link_down(&xnetif[ETHERNET_IDX]);
		netif_set_down(&xnetif[ETHERNET_IDX]);
	}
}

void usb_cdc_ecm_connect_cb(void)
{
	printf("connect\r\n");
	rtw_up_sema(&ecm_attach_sema);
}

void usb_cdc_ecm_disconnect_cb(void)
{
	printf("disconnect\r\n");
	detach_mode = ECM_ETH_CABLE_DETACH;
	rtw_up_sema(&ecm_detach_sema);
}
bool ecm_on(void)
{
	bool status = false;
	if (ecm_flg == false) {
		usbh_cdc_ecm_user_cb_t usb_cb;
		memset(&usb_cb, 0x00, sizeof(usb_cb));
		rx_buffer_saved_data = 0;
		ip_total_len = 0;
		usb_cb.report_data = usb_ethernet_ecm_cb;//Recevie the packet
		usb_cb.usb_attach = usb_cdc_ecm_attach_cb;//Attach the ECM
		usb_cb.usb_detach = usb_cdc_ecm_detach_cb;//Detach the ECM
		usb_cb.usb_connect = usb_cdc_ecm_connect_cb;
		usb_cb.usb_disconnect = usb_cdc_ecm_disconnect_cb;
		status = usbh_cdc_ecm_on(&usb_cb);
		if (status == true) {
			printf("ecm init ok\r\n");
		} else {
			printf("ecm init fail\r\n");
		}
		ecm_flg = true;
	}

	return status;
}

bool ecm_off(void)
{
	bool status = false;
	if (ecm_flg == true) {
		status = usbh_cdc_ecm_off();
		if (status == true) {
			printf("ecm deinit ok\r\n");
			ecm_flg = false;
		} else {
			printf("ecm deinit fail\r\n");
		}
	}

	return status;
}

void ecm_deinit_resoure(void)
{

	rtw_free_sema(&ecm_attach_sema);
	rtw_free_sema(&ecm_detach_sema);
	rtw_delete_task(&task_ecm_attach);
	ecm_status = ECM_STATUS_DEINIT;
	printf("ecm deinit\r\n");
}

static void ecm_detach_thread(void *parm)
{
	while (1) {
		rtw_down_sema(&ecm_detach_sema);
		if (lwip_status) {
			lwip_status = 0;
			//dhcp_stop(&xnetif[ETHERNET_IDX]);
			LwIP_DHCP_stop(ETHERNET_IDX);
			ecm_lwip_deinit();
			printf("link to unlink !!\n");
		} else {
			printf("lwip_status %d !!\n", lwip_status);
		}
		ecm_off();
		vTaskDelay(50);
		if (detach_mode == ECM_ETH_CABLE_DETACH) {
			ecm_on();//Keep monitor the ethernet calbe connect
		} else {
			ecm_deinit_resoure();
			break;
		}
	}
	rtw_delete_task(&task_ecm_detach);


}

static void ecm_attach_thread(void *parm)
{
	while (1) {
		rtw_down_sema(&ecm_attach_sema);
		if (lwip_status == 0) {
			lwip_status = 1;
			ecm_lwip_init();
			printf("unlink to link !!\n");
		} else {
			printf("lwip_status %d !!\n", lwip_status);
		}
	}

	rtw_delete_task(&task_ecm_attach);
}

//should parse the data to get the ip header
u8 rltk_mii_recv_data(u8 *buf, u32 total_len, u32 *frame_length)
{
	u8 *pbuf ;

	if (0 == ip_total_len) { //first packet
		pbuf = RX_BUFFER;
		rtw_memcpy((void *)pbuf, buf, total_len);
		if (total_len != 512) { //should finish
			*frame_length = total_len;
			return 1;
		} else { //get the total length
			rx_buffer_saved_data = total_len;
			//should check the vlan header
			//should check it is IP packet 0x0800
			ip_total_len = buf[14 + 2] * 256 + buf[14 + 2 + 1];
			//printf("ip packet len = %d\n", ip_total_len);
			if (512 - 14 == ip_total_len) { //the total length is 512
				*frame_length = total_len;
				ip_total_len = 0;
				return 1;
			}
		}
	} else {
		pbuf = RX_BUFFER + rx_buffer_saved_data;
		rtw_memcpy((void *)pbuf, buf, total_len);
		rx_buffer_saved_data += total_len;
		if (total_len != 512) {
			//should finish
			*frame_length = rx_buffer_saved_data;
			ip_total_len = 0;
			return 1;
		} else {
			//should check the vlan header
			//should check it is IP packet 0x0800
			if (rx_buffer_saved_data - 14 == ip_total_len) {
				//should finish
				*frame_length = rx_buffer_saved_data;
				ip_total_len = 0;
				return 1;
			}
		}
	}

	return 0;
}
u8 rltk_mii_recv_data_check(u8 *mac, u32 frame_length)
{
	u8 *pbuf = RX_BUFFER;
	u8 checklen = 0;
	u8 multi[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	//printf("[usb]get framelen=%d\n",frame_length);

	if (memcmp(mac, pbuf, 6) == 0 || memcmp(multi, pbuf, 6) == 0) {
		checklen = 7 ;
		//printf("\n[rx data header]");
	} else {
		checklen = 6;
		//printf("\n[rx data header][exit]");
	}

	if (1) {
		u32 index = 0 ;
		u32 max = frame_length;

		if (frame_length >= checklen) {
			max = checklen;
		}
	}

	return (checklen == 6) ? (0) : (1);
}

void usb_ethernet_ecm_cb(u8 *buf, u32 len)
{
#if 0
	u8 *pbuf = RX_BUFFER;
	u32 frame_len = 0;

	if (0 == rltk_mii_recv_data(buf, len, &frame_len)) {
		return;
	}

	if (0 == rltk_mii_recv_data_check(multi_mac, frame_len)) {
		return;
	}
	ethernetif_mii_recv(&xnetif[ETHERNET_IDX], frame_len);
#else
	RX_BUFFER = buf;
	if (0 == rltk_mii_recv_data_check(multi_mac, len)) {
		return;
	}
	ethernetif_mii_recv(&xnetif[ETHERNET_IDX], len);
#endif
}

void rltk_mii_recv(struct eth_drv_sg *sg_list, int sg_len)
{
	struct eth_drv_sg *last_sg;
	u8 *pbuf = RX_BUFFER;

	for (last_sg = &sg_list[sg_len]; sg_list < last_sg; ++sg_list) {
		if (sg_list->buf != 0) {
			rtw_memcpy((void *)(sg_list->buf), pbuf, sg_list->len);
			pbuf += sg_list->len;
		}
	}
}

s8 rltk_mii_send(struct eth_drv_sg *sg_list, int sg_len, int total_len)
{

	int ret = 0;
	struct eth_drv_sg *last_sg;
	usb_send_packet *tx_packet = usbh_ecm_send_get_buf();
	if (tx_packet) {
		u8 *pdata = tx_packet->packet;
		u32 size = 0;
		for (last_sg = &sg_list[sg_len]; sg_list < last_sg; ++sg_list) {
			rtw_memcpy(pdata, (void *)(sg_list->buf), sg_list->len);
			pdata += sg_list->len;
			size += sg_list->len;
		}
		tx_packet->packet_length = size;
		usbh_ecm_tx_push_message(tx_packet);
	} else {
		ret = -1;
	}

	return ret;
}

void atcmd_usb_ecm_init(void);
void usbh_ecm_thread(void *param)
{
	int ret = 0;
	bool status = false;
	lwip_status = 0;
	lwip_dhcp_status = -1;
	lwip_static_ip_status = -1;
	rtw_init_sema(&ecm_attach_sema, 0);
	rtw_init_sema(&ecm_detach_sema, 0);
#ifdef ECM_STATIC_IP_TEST
	ecm_static_ip_info attr;
	memset(&attr, 0x00, sizeof(ecm_static_ip_info));
	attr.ip = "192.168.33.150";
	attr.netmask = "255.255.255.0";
	attr.gw = "192.168.33.1";
	attr.dns1 = "192.168.33.1";
	attr.dns_num = 1;
	ecm_setup_static_ip_param(&attr);
	ecm_lwip_setup_connect_mode(ECM_LWIP_STATIC_IP_MODE);
#endif
	if (!lwip_init_done) {
		LwIP_Init();
	}

	ret = rtw_create_task(&task_ecm_attach, "ecm_attach_thread", USBH_ECM_THREAD_STACK_SIZE, tskIDLE_PRIORITY + 2, ecm_attach_thread, NULL);

	if (ret != pdPASS) {
		printf("\n[ECM] Fail to create USB host ECM thread\n");
		goto EXIT_FAIL_ATTACH;
	}

	ret = rtw_create_task(&task_ecm_detach, "ecm_detach_thread", USBH_ECM_THREAD_STACK_SIZE, tskIDLE_PRIORITY + 2, ecm_detach_thread, NULL);

	if (ret != pdPASS) {
		printf("\n[ECM] Fail to create USB host ECM thread\n");
		goto EXIT_FAIL_DETACH;
	}

	vTaskDelay(100);

	status = ecm_on();//It don't have the usb signal
	atcmd_usb_ecm_init();
	if (status == false) {
		rtw_delete_task(&task_ecm_detach);
		ecm_off();
		ecm_status = ECM_STATUS_DEINIT;
		printf("ecm_status %d\r\n", ecm_status);
		goto EXIT_FAIL_DETACH;
	} else {
		ecm_status = ECM_STATUS_START;
		printf("ecm_status %d\r\n", ecm_status);
	}
	goto EXIT;
EXIT_FAIL_DETACH:
	rtw_delete_task(&task_ecm_attach);
EXIT_FAIL_ATTACH:
	rtw_free_sema(&ecm_attach_sema);
	rtw_free_sema(&ecm_detach_sema);
EXIT:
	vTaskDelete(NULL);
}

int ethernet_ecm_status(void)
{
	return ecm_status;
}
int ethernet_is_linked(void)
{
	return (int)usbh_cdc_ecm_ethernt_status();
}

int ethernet_is_unplug(void)
{
	return (int)usbh_cdc_ecm_ethernt_status();
}

void ethernet_usb_init(void)
{
	int ret;
	struct task_struct task;

	printf("\n[ECM] USB host ECM demo started...\n");

	ret = rtw_create_task(&task, "usbh_ecm_thread", USBH_ECM_THREAD_STACK_SIZE, tskIDLE_PRIORITY + 2, usbh_ecm_thread, NULL);
	if (ret != pdPASS) {
		printf("\n[MSC] Fail to create USB host ECM thread\n");
	}
}

void ethernet_usb_deinit(void)
{
	detach_mode = ECM_USB_CABLE_DETACH;
	rtw_up_sema(&ecm_detach_sema);//Trigger to close the ecm driver
	int count = 0;
	ecm_status = ECM_STATUS_DEINIT;
	while (1) {
		count++;
		vTaskDelay(100);
		if (ecm_status == ECM_STATUS_DEINIT) {
			printf("ecm deinit finish\r\n");
			break;
		} else if (count >= 50) {
			printf("timeout 5s\r\n");
			break;
		}
	}
}

void AECMD(void *arg)
{
	if (ecm_status == ECM_STATUS_START) {
		ethernet_usb_deinit();
	} else {
		printf("It has already deinit\r\n");
	}
}

void AECME(void *arg)
{
	if (ecm_status == ECM_STATUS_DEINIT) {
		ethernet_usb_init();
	} else {
		printf("The usb ecm is running\r\n");
	}
}

log_item_t usb_ecm_items[] = {
	{"ECMD", AECMD,},
	{"ECME", AECME,},
};

void atcmd_usb_ecm_init(void)
{
	log_service_add_table(usb_ecm_items, sizeof(usb_ecm_items) / sizeof(usb_ecm_items[0]));
}
#endif