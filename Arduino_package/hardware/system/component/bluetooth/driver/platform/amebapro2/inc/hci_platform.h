/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef _HCI_PLATFORM_H_
#define _HCI_PLATFORM_H_

#include "hci/hci_common.h"
#include "./hci_uart.h"
#include "wifi_conf.h"
#include "platform_conf.h"

#define hci_platform_START_IQK
#define hci_platform_WRITE_IQK
#define hci_platform_SET_CUT_VER

#define HCI_START_IQK_TIMES            3

#define HCI_IQK_DATA_LEN               4
#define HCI_WRITE_IQK_DATA_LEN         0X30

#if (CONFIG_CHIP_VER == CHIP_TEST_CUT)
#define HCI_DEFAULT_LMP_SUBVER   0x8735
#else
#define HCI_DEFAULT_LMP_SUBVER   0x8715
#endif

typedef struct {
    uint8_t  offset;
    uint16_t value;
} HCI_IQK_DATA;

extern HCI_IQK_DATA hci_iqk_data[HCI_START_IQK_TIMES];
	
void hci_platform_get_baudrate(uint8_t* baudrate, uint8_t len);
void hci_platform_record_chipid(uint8_t chipid);
void hci_platform_dl_patch_done(void);
uint8_t hci_platform_set_baudrate(void);
uint8_t hci_platform_dl_patch_init(void);
uint8_t hci_platform_get_patch_cmd_len(uint8_t *cmd_len);
uint8_t hci_platform_get_patch_cmd_buf(uint8_t *cmd_buf, uint8_t cmd_len);

uint8_t hci_platform_init(void);
uint8_t hci_platform_deinit(void);

bool rtk_bt_pre_enable(void);
#endif