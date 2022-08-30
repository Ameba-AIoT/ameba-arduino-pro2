#ifndef _RMESH_OTA_DEVICE_H_
#define _RMESH_OTA_DEVICE_H_

#include "rtl8721d_ota.h"

#define MESH_DEVICE_OTA_CONFIG		1

/* User Frame SubType */
enum MESH_USER_DATA_SUBTYPE {
	MESH_APP_INFO_SYNC	= 0x16,
	MESH_OTA_SEQ		= 0x17,
	MESH_OTA_SEQ_REQ	= 0x18,
	MESH_OTA_SEQ_REPLY	= 0x19,
};

/* Seq Reply Order */
enum MESH_SEQ_REPLY_ORDER {
	SEND_ALL_ZERO_BIT_MAP	= 0,
	SEND_ALL_ONE_BIT_MAP	= 1,
	SEND_NORMAL_BIT_MAP		= 2,
};

/* Version Area Operation */
enum MESH_VERSION_AREA_ORDER {
	RUNNING_VERSION		= 0,
	UPDATING_VERSION	= 1,
};

typedef struct _RMESH_OTA_DEVICE_CONFIG_ {
	u16 version_len;
	u8 ota_version[16];
	update_ota_target_hdr ota_target_header;
	u8 updating_image_cnt;
	u32 total_seq_num;
	u32 bit_map_len;
	u8 *parry_seq;
} rmesh_ota_device_config;

extern void rmesh_ota_device_config_init();
extern void rmesh_app_info_sync();
extern void rmesh_device_ota_seq_recv(u8 *data, u32 data_len);
extern void rmesh_device_ota_seq_requset_recv(u8 *data, u32 data_len);
extern void rmesh_app_abnormal_data(u8 *data, u32 data_len);

#endif
