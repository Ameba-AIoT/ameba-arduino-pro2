#ifndef ETHERNET_USB_H
#define ETHERNET_USB_H

#include "lwip_netconf.h"

#define ETHERNET_IDX (NET_IF_NUM - 1)
#define WLAN_IDX 0

void ethernet_usb_init(void);

#endif // __MII_ETHERNETIF_H__