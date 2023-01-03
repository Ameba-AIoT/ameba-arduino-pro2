/*
 * loguart.h
 *
 *  Created on: 2021年12月29日
 *      Author: ran_wei
 */

#ifndef __LOGUART_H__
#define __LOGUART_H__
#include "stdint.h"
#define __IO volatile
#define __I volatile const
#define __O volatile

#define u8 uint8_t
#define u32 uint32_t
#define s32 int32_t
#define u16 uint16_t
#define BOOL int
#define TRUE 1
#define FALSE 0

#define LOGUART_MASK_RX_FIFO_PTR            ((u32)0x000000FF << 24)          /*!<R   Data bytes count in the receive FIFO: the value of rx_fifo_ptr[7:0] indicates the data bytes number received in the FIFO. */
#define LOGUART_RX_FIFO_PTR(x)              ((u32)(((x) & 0x000000FF) << 24))
#define LOGUART_GET_RX_FIFO_PTR(x)          ((u32)(((x >> 24) & 0x000000FF)))
#define LOGUART_BIT_TP4F_NOT_FULL           ((u32)0x00000001 << 23)          /*!<R   Tx Path4 FIFO not full indicator */
#define LOGUART_TP4F_NOT_FULL(x)            ((u32)(((x) & 0x00000001) << 23))
#define LOGUART_BIT_TP3F_NOT_FULL           ((u32)0x00000001 << 22)          /*!<R   Tx Path3 FIFO not full indicator */
#define LOGUART_TP3F_NOT_FULL(x)            ((u32)(((x) & 0x00000001) << 22))
#define LOGUART_BIT_TP2F_NOT_FULL           ((u32)0x00000001 << 21)          /*!<R   Tx Path2 FIFO not full indicator */
#define LOGUART_TP2F_NOT_FULL(x)            ((u32)(((x) & 0x00000001) << 21))
#define LOGUART_BIT_TP1F_NOT_FULL           ((u32)0x00000001 << 20)          /*!<R   Tx Path1 FIFO not full indicator */
#define LOGUART_TP1F_NOT_FULL(x)            ((u32)(((x) & 0x00000001) << 20))
#define LOGUART_BIT_TP4F_EMPTY              ((u32)0x00000001 << 19)          /*!<R   Tx Path4 FIFO empty indicator */
#define LOGUART_TP4F_EMPTY(x)               ((u32)(((x) & 0x00000001) << 19))
#define LOGUART_BIT_TP3F_EMPTY              ((u32)0x00000001 << 18)          /*!<R   Tx Path3 FIFO empty indicator */
#define LOGUART_TP3F_EMPTY(x)               ((u32)(((x) & 0x00000001) << 18))
#define LOGUART_BIT_TP2F_EMPTY              ((u32)0x00000001 << 17)          /*!<R   Tx Path2 FIFO empty indicator */
#define LOGUART_TP2F_EMPTY(x)               ((u32)(((x) & 0x00000001) << 17))
#define LOGUART_BIT_TP1F_EMPTY              ((u32)0x00000001 << 16)          /*!<R   Tx Path1 FIFO empty indicator */
#define LOGUART_TP1F_EMPTY(x)               ((u32)(((x) & 0x00000001) << 16))
#define LOGUART_BIT_RP_RXFIFO_ERR           ((u32)0x00000001 << 15)          /*!<R   Relay Path rx_error,only valid when the FCR[12] set to 1 * 0: Clear when the CPU reads the LSR, if there are no subsequent errors in the relay path FIFO * 1: Parity error, framing error or break indication in the relay path FIFO */
#define LOGUART_RP_RXFIFO_ERR(x)            ((u32)(((x) & 0x00000001) << 15))
#define LOGUART_BIT_TIMEOUT_INT             ((u32)0x00000001 << 14)          /*!<R   This bit is only set when Rx Timeout interrupt is enabled(ETOI is set) 1: at least one character in the FIFO but no character has been input to the FIFO or reading from it for the time duration, which depends on the value in register REG_RX_PATH_CTRL[31:16] */
#define LOGUART_TIMEOUT_INT(x)              ((u32)(((x) & 0x00000001) << 14))
#define LOGUART_BIT_RXFIFO_INT              ((u32)0x00000001 << 13)          /*!<R   This bit is only set when Received Data Available Interrupt interrupt is enabled(ERBI is set) 1: FIFO Trigger level reached or Rx FIFO full */
#define LOGUART_RXFIFO_INT(x)               ((u32)(((x) & 0x00000001) << 13))
#define LOGUART_BIT_RP_FRM_ERR              ((u32)0x00000001 << 12)          /*!<R   Relay Path Framing Error (FE) indicator * 0: No framing error in the current character * 1: The received character does not have a valid stop bit */
#define LOGUART_RP_FRM_ERR(x)               ((u32)(((x) & 0x00000001) << 12))
#define LOGUART_BIT_RP_PAR_ERR              ((u32)0x00000001 << 11)          /*!<R   Relay Path Parity Error (PE) indicator * 0: No parity error in current character * 1: The received character does not have the correct parity bit */
#define LOGUART_RP_PAR_ERR(x)               ((u32)(((x) & 0x00000001) << 11))
#define LOGUART_BIT_RPF_OVR_ERR             ((u32)0x00000001 << 10)          /*!<R   Relay Path FIFO Overrun Error (OE) indicator * 0: No Overrun state * 1: The transmission is continue although the Relay FIFO is full */
#define LOGUART_RPF_OVR_ERR(x)              ((u32)(((x) & 0x00000001) << 10))
#define LOGUART_BIT_RPF_NOT_FULL            ((u32)0x00000001 << 9)          /*!<R 0x1  Relay Path FIFO Not FULL (NF) indicator * 0: Relay path FIFO is full * 1: Relay path FIFO is not full */
#define LOGUART_RPF_NOT_FULL(x)             ((u32)(((x) & 0x00000001) << 9))
#define LOGUART_BIT_RPF_DRDY                ((u32)0x00000001 << 8)          /*!<R   Relay Path FIFO Data Ready (DR) indicator * 0: No characters in the Relay Receiver FIFO * 1: At least one character has been received and transferred into the Relay path FIFO */
#define LOGUART_RPF_DRDY(x)                 ((u32)(((x) & 0x00000001) << 8))
#define LOGUART_BIT_RXFIFO_ERR              ((u32)0x00000001 << 7)          /*!<R   Uart_rx_error, only valid when the FCR bit [0] set to 1 * 0: Clear when the CPU reads the LSR, if there are no subsequent errors in the FIFO * 1: Parity error, overrun error,framing error or break indication in the FIFO */
#define LOGUART_RXFIFO_ERR(x)               ((u32)(((x) & 0x00000001) << 7))
#define LOGUART_BIT_TX_EMPTY                ((u32)0x00000001 << 6)          /*!<R   TX fifo empty indicator */
#define LOGUART_TX_EMPTY(x)                 ((u32)(((x) & 0x00000001) << 6))
#define LOGUART_BIT_MONITOR_DONE_INT        ((u32)0x00000001 << 5)          /*!<R 0  This bit is only set when Rx Path Monitor Done interrupt is enabled(EMDI is set) 1: Rx path monitor done */
#define LOGUART_MONITOR_DONE_INT(x)         ((u32)(((x) & 0x00000001) << 5))
#define LOGUART_BIT_BREAK_INT               ((u32)0x00000001 << 4)          /*!<R   Break Interrupt (BI) indicator * 0: No break condition in the current character * 1: The received data input held in the Spacing ( logic 0) state is longer than a full word transmission time */
#define LOGUART_BREAK_INT(x)                ((u32)(((x) & 0x00000001) << 4))
#define LOGUART_BIT_FRM_ERR                 ((u32)0x00000001 << 3)          /*!<R   Framing Error (FE) indicator * 0: No framing error in the current character * 1: The received character does not have a valid stop bit */
#define LOGUART_FRM_ERR(x)                  ((u32)(((x) & 0x00000001) << 3))
#define LOGUART_BIT_PAR_ERR                 ((u32)0x00000001 << 2)          /*!<R   Parity Error (PE) indicator * 0: No parity error in current character * 1: The received character does not have the correct parity bit */
#define LOGUART_PAR_ERR(x)                  ((u32)(((x) & 0x00000001) << 2))
#define LOGUART_BIT_OVR_ERR                 ((u32)0x00000001 << 1)          /*!<R   Overrun Error (OE) indicator * 0: No Overrun state * 1: The transmission is continue although the Rx FIFO is full */
#define LOGUART_OVR_ERR(x)                  ((u32)(((x) & 0x00000001) << 1))
#define LOGUART_BIT_DRDY                    ((u32)0x00000001 << 0)          /*!<R   Data Ready (DR) indicator * 0: No characters in the Receiver FIFO * 1: At least one character has been received and transferred into the FIFO */
#define LOGUART_DRDY(x)                     ((u32)(((x) & 0x00000001) << 0))

#define KB_ASCII_NUL    0x00
#define KB_ASCII_BS     0x08
#define KB_ASCII_TAB    0x09
#define KB_ASCII_LF     0x0A
#define KB_ASCII_CR     0x0D
#define KB_ASCII_ESC    0x1B
#define KB_ASCII_SP     0x20
#define KB_ASCII_BS_7F  0x7F
#define KB_ASCII_LBRKT  0x5B         //[

#define UARTLOG_REG_BASE 0x41014000

#define LOGUART_DEV ((LOGUART_TypeDef *) UARTLOG_REG_BASE)


typedef s32 IRQn_Type;

typedef struct {
	u32 idx;
	u32 not_full;
	u32 empty;
	u32 tx_timeout; /* caculate under 4800bps, test ok under 9600bps */
	IRQn_Type irq_num;
} LOG_UART_PORT;

typedef struct {
	__IO uint32_t LOGUART_UART_DLL;                       /*!< UART DIVISOR LENGTH REGISTER,  Address offset: 0x000 */
	__IO uint32_t LOGUART_UART_IER;                       /*!< UART INTERRUPT ENABLE REGISTER,  Address offset: 0x004 */
	__I  uint32_t LOGUART_UART_IIR;                       /*!< UART INTERRUPT IDENTIFICATION REGISTER,  Address offset: 0x008 */
	__IO uint32_t LOGUART_UART_LCR;                       /*!< UART LINE CONTROL REGISTER,  Address offset: 0x00C */
	__IO uint32_t LOGUART_UART_MCR;                       /*!< UART MODEM CONTROL REGISTER,  Address offset: 0x010 */
	__I  uint32_t LOGUART_UART_LSR;                       /*!< UART LINE STATUS REGISTER,  Address offset: 0x014 */
	__I  uint32_t LOGUART_UART_MSR;                       /*!< UART MODEM STATUS REGISTER,  Address offset: 0x018 */
	__IO uint32_t LOGUART_UART_SCR;                       /*!< UART SCRATCH PAD REGISTER,  Address offset: 0x01C */
	__IO uint32_t LOGUART_UART_STSR;                      /*!< UART STS REGISTER,  Address offset: 0x020 */
	__I  uint32_t LOGUART_UART_RBR;                       /*!< UART RECEIVER BUFFER REGISTER,  Address offset: 0x024 */
	__IO uint32_t LOGUART_UART_MISCR;                     /*!< UART MISC CONTROL REGISTER,  Address offset: 0x028 */
	__IO uint32_t LOGUART_UART_REG_SIR_TX_PWC0;           /*!< UART IRDA SIR TX PULSE WIDTH CONTROL 0 REGISTER,  Address offset: 0x02C */
	__IO uint32_t LOGUART_UART_REG_SIR_RX_PFC;            /*!< UART IRDA SIR RX PULSE FILTER CONTROL REGISTER,  Address offset: 0x030 */
	__IO uint32_t LOGUART_UART_REG_BAUD_MON;              /*!< UART BAUD MONITOR REGISTER,  Address offset: 0x034 */
	__IO uint32_t RSVD0;                                  /*!<  Reserved,  Address offset:0x38 */
	__I  uint32_t LOGUART_UART_REG_DBG;                   /*!< UART DEBUG REGISTER,  Address offset: 0x03C */
	__IO uint32_t LOGUART_UART_REG_RX_PATH_CTRL;          /*!< UART RX PATH CONTROL REGISTER,  Address offset: 0x040 */
	__IO uint32_t LOGUART_UART_REG_MON_BAUD_CTRL;         /*!< UART MONITOR BAUD RATE CONTROL REGISTER,  Address offset: 0x044 */
	__IO uint32_t LOGUART_UART_REG_MON_BAUD_STS;          /*!< UART MONITOR BAUD RATE STATUS REGISTER,  Address offset: 0x048 */
	__I  uint32_t LOGUART_UART_REG_MON_CYC_NUM;           /*!< UART MONITORED CYCLE NUMBER REGISTER,  Address offset: 0x04C */
	__IO uint32_t LOGUART_UART_REG_RX_BYTE_CNT;           /*!< UART RX DATA BYTE COUNT REGISTER,  Address offset: 0x050 */
	__IO uint32_t LOGUART_UART_FCR;                       /*!< UART FIFO CONTROL REGISTER,  Address offset: 0x054 */
	__IO uint32_t LOGUART_UART_AGGC;                      /*!< UART AGG CONTROL REGISTER,  Address offset: 0x058 */
	__O  uint32_t LOGUART_UART_THRx[4];                   /*!< UART TRANSMITTER HOLDING REGISTER x Register,  Address offset: 0x05C-0x068 */
	__IO uint32_t LOGUART_UART_RP_LCR;                    /*!< UART RELAY RX PATH LINE CONTROL REGISTER,  Address offset: 0x06C */
	__IO uint32_t LOGUART_UART_RP_RX_PATH_CTRL;           /*!< UART RELAY RX PATH CONTROL REGISTER,  Address offset: 0x070 */
	__O  uint32_t LOGUART_UART_ICR;                       /*!< UART INTERRUPT CLEAR REGISTER,  Address offset: 0x074 */
} LOGUART_TypeDef;

void LOGUART_PutChar(u8 c);
int32_t DiagPrintf(const char *fmt, ...);
#endif /*  */
