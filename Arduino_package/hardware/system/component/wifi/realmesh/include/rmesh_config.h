/**
  ******************************************************************************
  * @file    rmesh_config.h
  * @author
  * @version V1.0.0
  * @date    2019-11-28
  * @brief   This file contains the network config of mesh.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2019, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */
#ifndef _RTL_MESH_CONFIG_H_
#define _RTL_MESH_CONFIG_H_

#define CHIP_CATEGORY_AMEBAD			0

/*user can change the CONFIG FLASH ADDRESS*/
#define FLASH_NET_CONFIG	0x100000

/* Flash Version Area 0x08100100*/
#define MESH_FLASH_VERSION_AREA			0x100100
#define MESH_MAX_VERSION_LEN			16
#define MESH_SINGLE_VERSION_AREA_LEN	18
#define MESH_FLASH_VERSION_AREA_LEN		36

#define CONFIG_CHANNEL_SCAN_INTERVAL	40 //(40ms every channel)
#define RSA_KEY_LEN 128
#define AES_KEY_LEN 16
#define GROUP_KEY_LEN 16

typedef enum {
	MESH_NOT_CONFIGED = 0,
	MESH_HELP_CONFIGED,
	MESH_CONFIGED_BY_SIMPLE_CONFIG,
	MESH_CONFIG_INGO_GET_FROM_FLASH,
	MESH_AES_KEY_GET,
} mesh_config_status;

typedef enum {
	MESH_SSID = 1,
	MESH_WHITE_LIST = 2,
	MESH_AES = 3,
	MESH_NETCONFIG = 4,
	MESH_AP_PSD = 10,
	MESH_GROUP_KEY = 11,
	MESH_IP = 12,

} mesh_config_type;

#pragma pack(1)
struct _RMESH_Config_format {
	u32 random;
	u8 mesh_id[6];
	u8 channel;
	u8 security;
};

/*
	mesh_id: the mesh id, 6 bytes
	channel: the channel of AP
	security: the security of WIFI
	ssid_len: the len of the ssid
	ssid: the ssid of the AP
	password_len: the len of the password
	password: the password of the AP
	bssid: the bssid of the AP
*/
#pragma pack(1)
struct _RMESH_Config_info {
	u8 mesh_id[6];
	u8 channel;
	u8 security;
	u8 ssid_len;
	u8 ssid[33];
	u8 password_len;
	u8 password[65];
	u8 bssid[6];
};


/**
 * @ subtype in real_mesh_construct_NetConfig_rsp
 */
enum rmesh_apInfoRsp_info {
	SECURITY = 0x01,
	SSID = 0x02,
	PASSWORD = 0X03,

};


#define MAX_RMESH_BEACON_ARRAY	10
#define MAX_LIFE_TIMER	5
struct _RMESH_BEACON_ARRAY {
	u8 mesh_id[6];
	u8 mesh_ap_bssid[6];
	s8 rssi;
	u8 used;
	u8 life_timer;
	u8 channel;
};

struct rmesh_config_priv {
	u8 rmesh_aes_key[AES_KEY_LEN];		//AES key
	u8 rmesh_group_key[GROUP_KEY_LEN];
	u8 rmesh_rsa_pk[RSA_KEY_LEN * 2];	//RSA public key send

	mbedtls_rsa_context rmesh_rsa; 		//RSA

	struct _RMESH_BEACON_ARRAY rmesh_beacon_array[MAX_RMESH_BEACON_ARRAY];
};


struct ServerInfo {
	u8  ip[20];
	u16  ip_len;
	u16  port;
};

extern int (*rmesh_net_packet_callback)(u8 *, u32, struct _RMESH_Config_format *);

/*
	local use
	set the config mode
	status: mesh_config_status
*/
extern void real_mesh_set_config_mode(u8 status);

/*
	local use
	convert the config packet to broadcast
*/
extern void rmesh_config_packet_bc(u8 *data, u32 data_len);

/*
	local use
	recv the help config packet
*/
extern void rmesh_help_config_request_recv(u8 *data, u32 data_len);

//Should used by customer
/*
	Erase Flash config information
*/
extern void real_mesh_erase_netconfig_info();

/*
	Read the mesh config info from the FLASH to prmesh_config_info
	ret: _TRUE read correct
	     _FALSE read error
*/
extern bool real_mesh_config_info_get(struct _RMESH_Config_info *prmesh_config_info);

/*
	store the config info to flash
*/
extern void real_mesh_config_info_store(struct _RMESH_Config_info *prmesh_config_info);

/*
	ret: -1 means error packets (do not process)
	      0 means process by the simple config
	      1 means process by the help config
	buf: data point
	userdata: userdata point
	da: destination point point
	sa: source point point
	len: len point
*/
extern int rmesh_help_config_parse(u8 *buf, void *userdata, u8 **da, u8 **sa, unsigned int *len);

/*
	ret: _TRUE means configured by help config
*/
extern bool remsh_configed_by_help();

/*
	ret: the number of mesh AP on this channel
*/
extern int rmesh_get_mesh_offset(int channel);

/*
	change the beacon life timer every 105*channel_num
*/
extern void rmesh_change_mesh_beacon_save_life();

/*
	RMESH help config INIT
*/
extern void rmesh_help_config_init(int (*callback)(u8 *data, u32 data_len, struct _RMESH_Config_info *prmesh_config_info));


/*
	RMESH help config DEINIT
*/
extern void rmesh_help_config_deinit();

/*
	RMESH hel config status
	ret : 1 help config on going
	      0 help config not on going
*/
extern u8 rmesh_help_config_get_status();

/*
	to get ip and port info of server
*/
extern void rmesh_set_server_info(u8 *ip, u16 ip_len, u16 port);

/*
	When the app exits, re-enter to get ap information
*/
void real_mesh_root_issue_apInfo_rsp();

/*
	to construct the packet about ap information
*/
int real_mesh_construct_apInfo_rsp();

#endif //_RTL_MESH_CONFIG_H_

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/

