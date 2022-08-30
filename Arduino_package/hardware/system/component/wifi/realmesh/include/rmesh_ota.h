#ifndef _RMESH_OTA_H_
#define _RMESH_OTA_H_

#include "rtl8721d_ota.h"

/* Flash OTA Area 0x08000000*/
#define MESH_OTA_UPDATE_AREA_1			0x08006000
#define MESH_OTA_UPDATE_AREA_2			0x08106000

#define OTA_SEQ_BYTE					2
#define SIGNATURE_BYTE					8
#define OTA_PACKET_SIZE					(1024)  /* max length for single packet*/
#define OTA_DATA_TRANSPORT_SIZE			(OTA_SEQ_BYTE + OTA_PACKET_SIZE)

typedef enum enum_ota_type {
	CHIP_CATEGORY	= 0X01,
	OTA_AREA		= 0x02,
	OTA_VERSION		= 0x03,
	OTA_HEADER		= 0x04,
	OTA_SIGNATURE	= 0x05,
};

extern void flash_erase_sector_except(u32 address, u32 len);
extern void flash_protect_version_info(u8	order);

#endif
