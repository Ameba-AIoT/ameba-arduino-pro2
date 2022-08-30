/**
  ******************************************************************************
  * @file    rmesh.h
  * @author
  * @version V1.0.0
  * @date    2016-05-17
  * @brief   This file contains all the functions prototypes for the realmesh.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */

#ifndef _RTL_MESH_H_
#define _RTL_MESH_H_

#include <wifi_mesh.h>
#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include "rmesh_config.h"
#include "rmesh_debug.h"
#include "rmesh_connect.h"
#include "rmesh_power_save.h"
#include "rmesh_ps_free_device.h"
#include "rmesh_security.h"

#define PING_TP_TEST	1

#define PARENT_AUTO_SWITCH_MECHANISM

#define STORE_NET_CONFIG_INFO			1
#define ROOT_ELECTION_MECHANISM			1
#define KEEP_ALIVE_ACK					0

//#define RMESH_ROOT_CONTROL		1
//#define RMESH_ENCRYPT			1
//#define RMESH_POWER_SAVE	1
#ifdef RMESH_POWER_SAVE
#define RMESH_FREE_NODE		1
#endif


#define RMESH_MAC_HEADER_LEN 24
#define RMESH_HEADER_LEN	40
#define RMESH_BCN_LEN		300

#define MAX_LAYER			6
#define MAX_CHILD_NUM		4
#define MAX_NODE_NUM		20

#define CONNECT_RETRY		8

#define KEEP_ALIVE_TIMER		400

#define RMESH_MAC_TRX_SIZE	3
#define RMESH_MAX_DEVICE_NUM	100
#define RMESH_DATA_QUEUE_SIZE		10
#define RMESH_MGNT_QUEUE_SIZE	10
#define RMESH_SOCKET_DATA_QUEUE_SIZE		10

#define MAX_MSG_LEN	1460
#define RMESH_BEACON_INTERVAL_NORMAL	500

extern struct rmesh_adapter adapter;

/*******************************************************
 *                Enumerations
 *******************************************************/

/**
 * @brief Device type
 */

enum RMESH_NODE_TYPE {
	RMESH_IDLE = 0,     /* hasn't joined the mesh network yet */
	RMESH_ROOT,          /* Has the ability to access external IP network */
	RMESH_NODE,          /* intermediate device. Has the ability to forward packets over the mesh network */
	RMESH_LEAF,           /* has no forwarding ability */
#ifdef RMESH_POWER_SAVE
	RMESH_FREE,			/* free state device */
#endif
	RMESH_AP,             /* node can be root node (without care threshold), or intermediate node */
};

/**
 * @brief mesh data type
 */

enum MESH_FRAME_MAC_TYPE {
	WIFI_MESH_BEACON = BIT(7),
	WIFI_MESH_DATA = (BIT(6) | BIT(5) | BIT(4)),
};

enum MESH_FRAME_TYPE {
	MESH_MGT_TYPE  = (0),
	MESH_DATA_TYPE = (BIT(0)),
	MESH_CTL_TYPE = 0x2,
};

/**
 *IF the tyep is changed, rmesh_mgnt_handler mesh_mgnt_tbl[] also should be changed
 */

enum MESH_FRAME_SUBTYPE {
	// below is for mesh mgnt frame
	MESH_ASSOCREQ			= (0 | MESH_MGT_TYPE),
	MESH_ASSOCRSP			= (BIT(0) << 8 | MESH_MGT_TYPE),
	MESH_ROUTEUPDATE		= (BIT(1) << 8 | MESH_MGT_TYPE),
	MESH_DEAUTH 			= ((0x3 << 8) | MESH_MGT_TYPE),
	MESH_PROBEREQ			= ((0x4 << 8) | MESH_MGT_TYPE),
	MESH_PROBERSP			= ((0x5 << 8) | MESH_MGT_TYPE),
	MESH_KEEP_ALIVE 		= ((0x6 << 8) | MESH_MGT_TYPE),
	MESH_KEEP_ALIVE_ACK 	= ((0x7 << 8) | MESH_MGT_TYPE),

	MESH_HELP_CONFIG_REQUEST	= ((0x8 << 8) | MESH_MGT_TYPE),

	MESH_LEAVE				= ((0x9 << 8) | MESH_MGT_TYPE),
	MESH_POLL_REQ			= ((0xa << 8) | MESH_MGT_TYPE),

	// below is for mesh data frame
	MESH_DATA				= (0 | MESH_DATA_TYPE),
	MESH_BC_CONFIG			= ((0x1 << 8) | MESH_DATA_TYPE),	//broadcast
	MESH_FREE_NODE_DATA		= ((0x2 << 8) | MESH_DATA_TYPE),	//free node: broadcast; mesh node: unicast

	// below is for mesh ctl frame
	MESH_DATA_ACK			= (0 << 8 | MESH_CTL_TYPE),			// used in mesh free node
	MESH_TRIGGERING			= ((0x1 << 8) | MESH_CTL_TYPE),	//broadcast
};

/**
 * @brief state of port0
 */
enum PORT0_STATE {
	RMESH_INIT	= 0,
	RMESH_CONFIGURING,
	RMESH_CONFIGED,
	RMESH_CONNECTING,
	RMESH_CONNECTED,
};

/**
  * @brief  The enumeration lists the results of the function.
  */
enum {
	RMESH_SUCCESS                      = 0,    /**< Success */
	RMESH_CLOSED                      = 1,    /**< socket is closed */
	RMESH_TIMEOUT                      = 2,    /**< Timeout */
	RMESH_RESTART                      = 3,

	RMESH_FAIL                       = -1,
	RMESH_DROP			= -2,
};

/**
 * @brief The enumeration is event type indicated from rmesh stack.
 */
enum {
	RMESH_EVENT_STARTED = 0,                 	/**< mesh is started */
	RMESH_EVENT_STOPPED,                 		/**< mesh is stopped */
	RMESH_EVENT_CONFIGURE,           		/**< node enter configure stage */
	RMESH_EVENT_SCAN_RESULT_REPORT,       /**< scan one valid beacon */
	RMESH_EVENT_SCAN_DONE,                         /**< scan finished */
	RMESH_EVENT_CONNECT,                          	/**< inter node connect to parent */
	RMESH_EVENT_CONNECTED,        			/**< node connected on port0 interface */
	RMESH_EVENT_ROOT_CONNECTED,			/**< root connected to cloud */
	RMESH_EVENT_DISCONNECTED,    			/**< node disconnected on port0 interface */

	RMESH_EVENT_CHILD_CONNECTED,         	/**< a child is connected on port1 interface */
	RMESH_EVENT_CHILD_DISCONNECTED,     	/**< a child is disconnected on port1 interface */

	RMESH_EVENT_ROUTING_TABLE_ADD,       	/**< routing table is changed by adding newly joined children */
	RMESH_EVENT_ROUTING_TABLE_REMOVE,   /**< routing table is changed by removing leave children */

	RMESH_EVENT_NO_PARENT_SCANNED,        /**< no parent node or router scanned */
	RMESH_EVENT_LAYER_CHANGE,           		/**< layer changes over the mesh network */

	RMESH_EVENT_ROOT_GOT_IP,             		/**< the root obtains the IP address. */
	RMESH_EVENT_ROOT_LOST_IP,            		/**< the root loses the IP address. */

	RMESH_EVENT_ROOT_FIXED,              		/**< when devices join a network, if the setting of Fixed Root for one device is different
                                             		from that of its parent, the device will update the setting the same as its parent's.
                                             		Fixed Root Setting of each device is variable as that setting changes of the root. */
	RMESH_EVENT_DISCONNECT,
	RMESH_EVENT_MAX,
};


enum {
	down_link = 0,
	up_link,
	no_link,
};


/*******************************************************
 *                Structures
 *******************************************************/

/**
 * @brief mesh header
 */
struct rmesh_hdr {
	u16	version;
	u8	type;
	u8	sub_type;

	u32	seq_ctl;
	u32	control;
	u32	reserved;

	u8	addr0[ETH_ALEN]; /* current source */
	u8	addr1[ETH_ALEN]; /* current destination */
	u8	addr2[ETH_ALEN]; /* mesh source */
	u8	addr3[ETH_ALEN]; /* mesh destination */
};

#define RMESH_MORE_DATA		BIT0		//current used in free node
#define RMESH_PROTECTED		BIT1		//used in mesh mgnt frame encrypt, if protected = 1, the mesh mgnt frame is encrypted

/**
 * @brief mesh beacon header
 */
struct rmesh_beacon_hdr {
	/* 802.11 MAC header */
	u8	frame_ctl[2];
	u8	duration_id[2];
	u8	addr1[ETH_ALEN];
	u8	addr2[ETH_ALEN];
	u8	addr3[ETH_ALEN];
	u8	seq_ctl[2];

	/* 802.11 beacon IE */
	u8	timestamp[8];
};

/**
 * @brief mesh beacon vendor ie
 */
struct rmesh_beacon_vendor_ie {
	u8	mesh_ID[ETH_ALEN];
	u8	rmesh_type;   /* mesh node type */
	u8	max_layer;     /* maximum numbers of layer permitted in the network */
	u8	current_layer;  /* current layer of node */
	u8	current_child_num;  /* current number of child nodes */
	u8	max_child_num;  /* Maximum number of downstream connections to accept */
	u8	connect_flag;    /* 1: cannot be connected; 0: can be connected */
};

#if ROOT_ELECTION_MECHANISM
struct rmesh_beacon_vendor_ie_root_election {
	u8	mesh_ID[ETH_ALEN];
	signed char rssi0;
	u8 mac_self[ETH_ALEN];         /* port1 */
	signed char rssi1;
	u8 mac1[ETH_ALEN];     /* mac address of device with max RSSI to AP */
	signed char rssi2;
	u8 mac2[ETH_ALEN];     /* mac address of device with second RSSI to AP */
	signed char rssi3;
	u8 mac3[ETH_ALEN];     /* mac address of device with third RSSI to AP */
};
#endif

#ifdef RMESH_POWER_SAVE
struct rmesh_beacon_vendor_ie_power_save {
	u8 cur_node_num;		// same as root
	u8 max_node_num;
	u8 dw;
	u8 ps_flag;		// 1 represents device has entered power save mode, child can enter
	u32 ap_offset;			// unit: us
	u8 sync_flag;			// true: synced
};
#endif

/**
 * @brief information of node port0
 */
struct rmesh_port0_info {
	u8	mac[ETH_ALEN];
	u8	channel;
	u64	rx_bcn_pkts;      /* 200ms */
	u64	last_rx_bcn_pkts;    /* 200ms */
	u64	rx_bcn_pkts_t;       /* 2s */
	u64	last_rx_bcn_pkts_t;  /* 2s */
	u8	retry;
};

/**
 * @brief router configuration
 */
struct rmesh_smart_config {
	u8	ssid[33];
	u8	ssid_len;
	u8	bssid[ETH_ALEN];
	u8	password[65];
	u8	pswd_len;
	u8	channel;
	unsigned long	security;
	signed char	rssi;
};

/**
 * @brief mesh softap configuration (port1)
 */
struct rmesh_ap_info {
	char	ssid[33];
	u8	ssid_len;
	u8	bssid[ETH_ALEN];
	u8	password[65];    /* mesh softAP password */
	u8	channel;
	u8	node_type;
	u8	child_num;
	u8	layer;     /* the layer of node in the network */
	u8	max_child_num;  /**< max number of stations allowed to connect in, max 20 */
	u8	max_layer;
	u8	connect_flag;
	u8	mesh_ID[ETH_ALEN];

	struct mesh_rxcache prxcache;
};

struct rmesh_rssi {
	s8	rssi;
	signed short root_thres;
	signed short node_thres;
};


struct rmesh_sta_priv {
	u8 mac[ETH_ALEN];
	struct mesh_rxcache prxcache;
	u64 rx_keep_alive_pkts;
	u64 last_rx_keep_alive_pkts;
	u8 retry;
	bool probe_flag;		// 0: recv no probe req; 1: recved probe req from child
	u8 waiting_probe_flag;		//1: need check probe_flag
	struct rmesh_sta_priv *next;
};

#if ROOT_ELECTION_MECHANISM
struct rmesh_rssi_mac_mapping {
	signed char rssi;
	u8 mac[ETH_ALEN];
	struct rmesh_rssi_mac_mapping *next;
};
#endif

struct rmesh_key {
	u8 aes_key[16];
	u8 group_key[16];
	u8 got_key;		// 1: has got key; 0: hasn't got key
};

/**
 * @brief mesh adapter
 */
struct rmesh_adapter {
	struct rmesh_key				key;
	struct rmesh_port0_info 		node_info;    /* node port0 information */
	struct rmesh_ap_info 			parent_node;     /* parent node information */
	struct rmesh_ap_info 			self_node;      /* self node port1 configuration */
	struct _RMESH_Config_info 		router;     /* router configuration */
	struct rmesh_rssi 	rssi_thres;   /* rssi threshlod: three level */
	struct rmesh_sta_priv 			*child_info;		/* a list that stores info of child connected with port1 */
	struct rmesh_route_node 		*route_table;  /* route table, root and common node except leaf node, need maintain */
	struct rmesh_topo_node 		*topo_table;    /* topology table, only root node need maintain */
	int sta_state; /*station state*/
	int scan_state; /*scan statue*/
	u8 root_status; /*0: donot connect to server; 1: connect to server success */
	u8 fixed_node_type;

	_sema						rmesh_connecting_sema; /* node enter connect state */

	_timer						rmesh_dynamic_chk_timer;  /* mesh STA dynamic check beacon */
	_timer						rmesh_ap_dynamic_chk_timer;  /* mesh AP dynamic check keep alive from child */
	_timer						rmesh_probe_timer;  /* */
	bool							probe_flag;   /* 0: child recv no probe rsp; 1: child recved probe rsp */

	struct rmesh_connect_priv			network_connect_priv;   /* node connect structure */

	mesh_config_status				status;

	struct rmesh_tcp_nl_msg			*tcp_nl_msg;

	QueueHandle_t					mesh_data_queue;
	QueueHandle_t					mesh_mgnt_queue;
	QueueHandle_t					mesh_socket_data_queue;

#if ROOT_ELECTION_MECHANISM
	struct rmesh_rssi_mac_mapping		*rssi_mac_table;		/* rssi and mac address of device in the mesh network */
	_timer							root_election_timer;		/* device listen beacon and update self's beacon to elect the device with the maximum rssi */
	bool								root_election_start;		/* true: start root election mechanism; false: otherwise */
#endif

#if KEEP_ALIVE_ACK
	bool								route_changed;		/* true: route table has changed; false: payload of keep alive frame is NULL */
#endif

#if RMESH_POWER_SAVE
	struct rmesh_power_save				ps_mode;
#endif

#if RMESH_FREE_NODE
	struct rmesh_free_node_buffer_table		*buffered_table;
#endif

#if RMESH_ROOT_CONTROL
	bool root_scan;
#endif
};

/**
 * @brief route table
 */
struct rmesh_route_node {
	u8 mac[ETH_ALEN];
	u8 mac_next_hop[ETH_ALEN];
	u8 mac_parent[ETH_ALEN];
	struct rmesh_route_node *next;
};

/**
 * @brief topology table
 */
struct rmesh_topo_node {
	u8 mac[ETH_ALEN];
	u8 mac_parent[ETH_ALEN];
	struct rmesh_topo_node *next;
};

struct thread_buffer {
	u8 *data;           /* payload, include MAC hdr, mesh hdr and app hdr */
	u32 data_len;
	u8 socket_offset;
	unsigned char rssi;

	u8 mac_da[ETH_ALEN];    /* destination address */
	u8 mac_sa[ETH_ALEN];

	u8 link;               /* 0: down-link; 1: up-link, send to parent node */

	/* down-link */
	u8 da_type;						/* 1: unicast to self; 2: unicast to child; 3: broadcast*/

	u8 pkt_type;					/* 1: keep alive; 2: probe request */
};

enum DA_TYPE {
	UNICAST_TO_SELF = 1,
	UNICAST_TO_CHILD = 2,
	BROADCAST = 3,
	MESH_BROADCAST = 4,
};

typedef void (*real_mesh_event_handler_t)(char *buf, void *handler_user_data);

typedef struct {
	real_mesh_event_handler_t	handler;
	void	*handler_user_data;
} rmesh_event_list_t;

struct rmesh_mgnt_handler {
	unsigned int   num;
	unsigned int (*func)(u8 *pframe, int len);
};



#define GetMeshHeaderType(pbuf)	(cpu_to_le16(*(unsigned short *)(pbuf + 2)))
#define GetMeshHeaderSubType(pbuf)	(cpu_to_le16(*(unsigned short *)(pbuf + 3)))

#define ARG_MAC(x) ((u8*)(x))[0],((u8*)(x))[1],((u8*)(x))[2],((u8*)(x))[3],((u8*)(x))[4],((u8*)(x))[5]
#define EQ_MAC( a, b )  (((a[0])==(b[0]))&& \
                          ((a[1])==(b[1]))&& \
                          ((a[2])==(b[2]))&& \
                          ((a[3])==(b[3]))&& \
                          ((a[4])==(b[4]))&& \
                          ((a[5])==(b[5])))

/* mesh indication API */
void rmesh_indication(u8 event, u8 *buf);
void rmesh_reg_event_handler(unsigned int event_cmds, real_mesh_event_handler_t handler_func, void *handler_user_data);
void rmesh_unreg_event_handler(unsigned int event_cmds, real_mesh_event_handler_t handler_func);


/*******************************************************
 *                APIs
 *******************************************************/

/* *
* @brief: real mesh init

* @attention: 	this func can only called by root node

* @param	none

* @retval		none
*/
int real_mesh_init();

/* *
* @brief: real mesh deinit

* @param	none

* @retval		none
*/
int real_mesh_deinit();

/* *
* @brief: fix node type: root / inter-node / leaf

* @param	type

* @retval	none
*/
void real_mesh_fix_node_type(u8 type);


/* *
* @brief: get node type: root / inter-node / leaf

* @param	none

* @retval	node type
*/
u8 real_mesh_get_node_type();


/* *
* @brief: get mac address of device port0 or port1

* @param	port

* @retval	mac address
*/
u8 *real_mesh_get_mac(u8 port);

/* *
* @brief: set rmesh reconnect times, default value is 8

* @param	none

* @retval	none
*/
void real_mesh_set_reconnect_times();

/* *
* @brief: set router rssi threshold
		if rssi between node and route > threshold, this node can be root

* @param	rssi

* @retval	void
*/
void real_mesh_set_rssi_threshold(int rssi);

/* *
* @brief: get router rssi threshold

* @param	none

* @retval	rssi
*/
int real_mesh_get_rssi_threshold();

/* *
* @brief: set mesh network maxmimum layer, default value is 10

* @param	layer

* @retval	void
*/
void real_mesh_set_mesh_network_layer(u8 layer);

/* *
* @brief: set mesh network maximum child number of each parent, default value is 2

* @param	child_num

* @retval	void
*/
void real_mesh_set_mesh_network_child_num(u8 child_num);

#endif //_RTL_MESH_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
