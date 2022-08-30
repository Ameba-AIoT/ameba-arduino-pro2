/**
 * Copyright (c) 2017, Realsil Semiconductor Corporation. All rights reserved.
 *
 */

#include <stdio.h>
#include <string.h>

/*  READ_ME
 * <b>Example usage</b>
 * \code{ble_app_main.c}
 void app_le_gap_init(void)
 {
    ....
    bt_coex_init();
 }
 */
#define BT_SW_MAILBOX_SCAN_OFF  0x00
#define BT_SW_MAILBOX_SCAN_ON   0x01

void bt_coex_handle_cmd_complete_evt(uint16_t opcode, uint16_t cause, uint8_t total_len, uint8_t *p);

void bt_coex_handle_specific_evt(uint8_t *p, uint8_t len);

unsigned int bt_coex_sw_mailbox_set(unsigned int mailbox_control);

void bt_coex_init(void);

