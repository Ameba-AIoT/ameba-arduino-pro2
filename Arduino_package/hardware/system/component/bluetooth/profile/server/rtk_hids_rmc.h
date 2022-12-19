/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __HID_SERVICE_RMC_H__
#define __HID_SERVICE_RMC_H__

#ifdef __cplusplus
extern "C"  {
#endif

#include <rtk_bt_def.h>

#define HIDS_KB_REPORT_ID                      1
#if FEATURE_SUPPORT_MULTIMEDIA_KEYBOARD
#define HIDS_MM_KB_REPORT_ID                   2
#endif
#if (VOICE_ENC_TYPE == SW_MSBC_ENC)
#define HIDS_VOICE_REPORT_ID                0x5A // input and output
#elif (VOICE_ENC_TYPE == SW_SBC_ENC)
#define HIDS_VOICE_REPORT_ID                0x5B // input and output
#elif (VOICE_ENC_TYPE == SW_OPT_ADPCM_ENC)
#define HIDS_VOICE_REPORT_ID                0x5C // input and output
#else
#define HIDS_VOICE_REPORT_ID                0x5A // input and output
#endif

typedef enum {
	HID_INPUT_TYPE   = 1, /**< @enum Input report */
	HID_OUTPUT_TYPE  = 2, /**< @enum Output report */
	HID_FEATURE_TYPE = 3 /**< @enum Feature report */
} TProfile_HIDReportType;

typedef enum {
	HIDS_PARAM_PROTOCOL_MODE = 1,
	HIDS_PARAM_SUSPEND_MODE = 2,
	HIDS_PARAM_HID_INFO = 3,
	HIDS_PARAM_REPORT = 4
} T_HIDS_PARAM_TYPE;

typedef enum {
    BOOT_PROTOCOL_MODE = 0,
    REPORT_PROCOCOL_MODE = 1
} T_HID_PROTOCOL_MODE;

typedef struct _HID_INFO_ATTRB {
	uint8_t  CountryCode;
	uint8_t  bFlags;
	uint16_t BcdHID;
} HID_INFO_ATTRB;

uint16_t hids_set_parameter(T_HIDS_PARAM_TYPE param_type, uint8_t length, void *value_ptr);

void hid_srv_callback(uint8_t event, void *data);

uint16_t hid_srv_add(void);

void hids_disconnect(uint16_t conn_handle);

void hids_status_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __HID_SERVICE_RMC_H__ */