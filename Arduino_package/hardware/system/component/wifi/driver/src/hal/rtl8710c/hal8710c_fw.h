#ifdef CONFIG_RTL8710C

#ifndef _FW_HEADER_8710C_H
#define _FW_HEADER_8710C_H

#if (DM_ODM_SUPPORT_TYPE & ODM_IOT)
extern const u8 array_mp_8710c_fw_iot[];
extern u32 array_length_mp_8710c_fw_iot;
extern const u8 array_mp_8710c_fw_iot_acut[];
extern u32 array_length_mp_8710c_fw_iot_acut;
#ifdef CONFIG_WOWLAN
extern u8 array_mp_8710c_fw_wowlan[];
extern u32 array_length_mp_8710c_fw_wowlan;
#endif
#endif
#if !defined(RTW_HALMAC)
#define FW_8710C_SIZE		0x6000
#define FW_8710C_START_ADDR	0x1000
#define FW_8710C_END_ADDR	0x1FFF
#define MAX_FW_PAGE_SIZE 	4096
#define MAX_FW_BLK_SIZE 	64
#define POLLING_READY_TIMEOUT_COUNT 1000
#define GET_FIRMWARE_HDR_SIGNATURE(__FwHdr) LE_BITS_TO_4BYTE(__FwHdr, 0, 16)
#define IS_FW_HEADER_EXIST_8710C(_pFwHdr) ((GET_FIRMWARE_HDR_SIGNATURE(_pFwHdr) & 0xFFF0) == 0x10C0)
#endif
#endif
#endif /* end of HWIMG_SUPPORT*/

