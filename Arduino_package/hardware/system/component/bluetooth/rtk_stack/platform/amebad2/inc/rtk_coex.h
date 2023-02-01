/**
 * Copyright (c) 2017, Realsil Semiconductor Corporation. All rights reserved.
 *
 */
#ifndef __RTK_COEX_H__
#define __RTK_COEX_H__

#include <stdio.h>
#include <string.h>
#include "platform_opts_bt.h"
#if defined CONFIG_BT && CONFIG_BT
void bt_coex_init(void);
unsigned int send_coex_mailbox_to_wifi_from_BtAPP(unsigned char state);
#else
#define bt_coex_init()
#define send_coex_mailbox_to_wifi_from_BtAPP(state) 1

#endif
#endif