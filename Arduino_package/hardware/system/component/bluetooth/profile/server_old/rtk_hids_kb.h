/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __HID_SERVICE_KB_H__
#define __HID_SERVICE_KB_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_gatts.h>

#ifdef __cplusplus
extern "C"  {
#endif

#define MULTIMEDIA_KEYBOARD         1

typedef enum {
    HID_PROTOCOL_MODE = 0x01,
    HID_REPORT_INPUT,
    HID_REPORT_OUTPUT,
    HID_REPORT_FEATURE,
    HID_REPORT_MAP,
    HID_EXTERNAL_REPORT_REFER,
    HID_BOOT_KB_IN_REPORT,
    HID_BOOT_KB_OUT_REPORT,
    HID_BOOT_MS_IN_REPORT,
    HID_INFO,
    HID_CONTROL_POINT,
} T_HIDS_PARAM_TYPE;

typedef struct {
    uint8_t  b_country_code;
    uint8_t  flags;
    uint16_t bcd_hid;
} T_HID_INFO;

typedef enum {
    HID_INPUT_TYPE   = 1,
    HID_OUTPUT_TYPE  = 2,
    HID_FEATURE_TYPE = 3
} T_PROFILE_HID_REPORT_TYPE;

typedef enum {
    HID_SUSPEND         = 0,
    HID_EXIT_SUSPEND    = 1,
} T_HID_CTL_POINT;

typedef enum {
    BOOT_PROTOCOL_MODE = 0,
    REPORT_PROCOCOL_MODE = 1
} T_HID_PROTOCOL_MODE;

rtk_bt_err_t hids_set_parameter(T_HIDS_PARAM_TYPE param_type, uint8_t length, void *value_ptr);

void hid_srv_callback(rtk_bt_gatts_evt_code_t event, void *data);

rtk_bt_err_t hid_srv_add(void);

void hids_disconnect(uint8_t conn_id);

void hids_status_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __HID_SERVICE_KB_H__ */