#ifdef CONFIG_RTL8735B

#ifndef _FW_HEADER_8735B_H
#define _FW_HEADER_8735B_H

#if (DM_ODM_SUPPORT_TYPE & ODM_IOT)
extern const u8 array_mp_8735b_fw_iot_bcut[];
extern u32 array_length_mp_8735b_fw_iot_bcut;
extern const u8 array_mp_8735b_fw_iot_dcut[];
extern u32 array_length_mp_8735b_fw_iot_dcut;
#ifdef CONFIG_WOWLAN
extern const u8 array_mp_8735b_fw_wowlan_bcut[];
extern u32 array_length_mp_8735b_fw_wowlan_bcut;
extern const u8 array_mp_8735b_fw_wowlan_dcut[];
extern u32 array_length_mp_8735b_fw_wowlan_dcut;
extern const u8 array_mp_8735b_fw2_wowlan_bcut[];
extern u32 array_length_mp_8735b_fw2_wowlan_bcut;
extern const u8 array_mp_8735b_fw2_wowlan_dcut[];
extern u32 array_length_mp_8735b_fw2_wowlan_dcut;
#endif
#endif

#endif
#endif /* end of HWIMG_SUPPORT*/

