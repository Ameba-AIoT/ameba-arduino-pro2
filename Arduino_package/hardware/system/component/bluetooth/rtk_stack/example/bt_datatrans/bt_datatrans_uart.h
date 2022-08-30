/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     dataTrans_uart.h
* @brief    Data uart operations for testing profiles.
* @details  Data uart init and print data through data uart.
* @author
* @date     2015-03-19
* @version  v0.1
*********************************************************************************************************
*/

#ifndef _DATA_TRANSMIT_UART_H_
#define _DATA_TRANSMIT_UART_H_

#include <basic_types.h>


typedef enum
{
    BAUD_2400           = 0,
    BAUD_4800           = 1,
    BAUD_9600           = 2,
    BAUD_19200          = 3,
    BAUD_38400          = 4,
    BAUD_57600          = 5,
    BAUD_115200         = 6,
    BAUD_921600         = 7,
    BAUD_2000000        = 8,
} BUAD_SET;

#define IO_MSG_RECEIVED            0x0A
#define IO_MSG_RECEIVE_ERR         0x0B
#define IO_MSG_RECEIVE_END         0x0C
typedef struct
{
    uint8_t cause;
    uint32_t mass_data_remainder;
} T_MASS_DATA_RESULT;

//#define DMA_BLOCK_SIZE      0x800//(244*10)

void bt_datatrans_uart_tx_char(int ch);
void bt_datatrans_uart_task_init(void);
void bt_datatrans_uart_task_deinit(void);
void bt_datatrans_uart_init(void);
void bt_datatrans_set_baud(void);

#endif

