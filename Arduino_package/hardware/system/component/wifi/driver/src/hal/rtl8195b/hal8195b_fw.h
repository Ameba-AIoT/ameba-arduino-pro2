#ifdef CONFIG_RTL8195B

#ifndef _FW_HEADER_8195B_H
#define _FW_HEADER_8195B_H

#if (DM_ODM_SUPPORT_TYPE & ODM_IOT)
extern const u8 array_mp_8195b_fw_iot[124464];
extern u32 array_length_mp_8195b_fw_iot;
#ifdef CONFIG_WOWLAN
extern u8 array_mp_8195b_fw_wowlan[102272];
extern u32 array_length_mp_8195b_fw_wowlan;
#endif
#endif
#endif
#endif /* end of HWIMG_SUPPORT*/

