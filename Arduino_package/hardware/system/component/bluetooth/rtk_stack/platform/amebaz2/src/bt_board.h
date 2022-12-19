/**
  * Copyright (c) 2015, Realsil Semiconductor Corporation. All rights reserved.
  *
  *
*/
#ifndef _BT_BOARD_H_
#define _BT_BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "hal.h"
#include "hal_sys_ctrl.h"

#define hci_board_debug    printf

#define TRACE_TX    PA_3
#define TRACE_RX    PA_2 

#define TRACE_UART_BAUDRATE    1500000

#define HCI_START_IQK
#define HCI_WRITE_IQK
#define BT_DEFAUT_LMP_SUBVER    0x8710

#define CALI_IQK_RF_STEP0    0x4000
#define CALI_IQK_RF_STEP1    0x0f88
#define CALI_IQK_RF_STEP2    0x3400
#define CALI_IQK_RF_STEP3F   0x0700

#define hci_board_32reg_set(addr, val) HAL_WRITE32(addr, 0, val)
#define hci_board_32reg_read(addr) HAL_READ32(addr, 0)

#define FLASH_BT_PARA_ADDR        (SYS_DATA_FLASH_BASE + 0xFF0)

#define LEFUSE(x)  (x-0x190)

#define EFUSE_SW_USE_FLASH_PATCH     BIT0
#define EFUSE_SW_BT_FW_LOG           BIT1
#define EFUSE_SW_RSVD                BIT2
#define EFUSE_SW_IQK_HCI_OUT         BIT3
#define EFUSE_SW_UPPERSTACK_SWITCH   BIT4
#define EFUSE_SW_TRACE_SWITCH        BIT5
#define EFUSE_SW_DRIVER_DEBUG_LOG    BIT6
#define EFUSE_SW_RSVD2               BIT7

#define CFG_SW_BT_TRACE_LOG          EFUSE_SW_TRACE_SWITCH

#define CHECK_SW(x)                  (HAL_READ32(SPI_FLASH_BASE, FLASH_BT_PARA_ADDR) & x)

extern u8 rltk_wlan_is_mp(void);

#ifdef __cplusplus
}
#endif

#endif

