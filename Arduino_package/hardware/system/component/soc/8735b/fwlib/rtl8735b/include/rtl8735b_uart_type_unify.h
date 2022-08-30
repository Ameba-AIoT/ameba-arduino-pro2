#ifndef _RTL8735B_UART_TYPE_H_
#define _RTL8735B_UART_TYPE_H_

/**************************************************************************//**
 * @defgroup UART_DLLR
 * @brief  Divisor Latch (LS) Register               (@ 0X000)
 * @{
 *****************************************************************************/
#define UART_SHIFT_DLL                               0
#define UART_MASK_DLL                                ((u32)0x000000FF << 0)                              /*!<R/W 0  Divisor [7:0]; accessible when DLAB = 1 */
/** @} */

/**************************************************************************//**
 * @defgroup UART_DLMR
 * @brief  Divisor Latch (MS) Register               (@ 0X004)
 * @{
 *****************************************************************************/
#define UART_SHIFT_DLM                               0
#define UART_MASK_DLM                                ((u32)0x000000FF << 0)                              /*!<R/W 0  Divisor [15:8]; accessible when DLAB = 1  */
/** @} */

/**************************************************************************//**
 * @defgroup UART_IER
 * @brief  Interrupt Enable Register                 (@ 0X004)
 * @{
 *****************************************************************************/
#define UART_SHIFT_EDSSI                             3
#define UART_BIT_EDSSI                               ((u32)0x00000001 << 3)                              /*!<R/W 0  Enable Modem Status Interrupt (EDSSI) (modem status transition) 0: disabled 1: enabled */
#define UART_SHIFT_ELSI                              2
#define UART_BIT_ELSI                                ((u32)0x00000001 << 2)                              /*!<R/W 0  Enable Receiver Line Status Interrupt (ELSI) (receiver line status) 0: disabled 1: enabled */
#define UART_SHIFT_ETBEI                             1
#define UART_BIT_ETBEI                               ((u32)0x00000001 << 1)                              /*!<R/W 0  Enable Transmitter FIFO Empty interrupt (ETBEI) (tx fifo empty) 0: disabled 1: enabled */
#define UART_SHIFT_ERBI                              0
#define UART_BIT_ERBI                                ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable Received Data Available Interrupt (ERBFI) (rx trigger) 0: disabled 1: enabled */
/** @} */

/**************************************************************************//**
 * @defgroup UART_IIR
 * @brief  Interrupt Identification Register         (@ 0X008)
 * @{
 *****************************************************************************/
#define UART_SHIFT_INT_ID                            1
#define UART_MASK_INT_ID                             ((u32)0x00000007 << 1)                              /*!<R 0  Bit1 and Bit2 the two bits of the IIR are used to identify the highest priority interrupt pending as indicated in the following table Bit3: In the FIFO mode this bit is set along with bit 2 when a timeout interrupt is pending. Bit3~Bit1 displays the list of possible interrupts along with the bits they enable, priority, and their source and reset control. ''3'b011'': Interrupt Priority: 1st priority (int_3) Interrupt Type: Receiver Line Status (read lsr) Interrupt Source: Parity, overrun or Framing errors or break interrupt. Interrupt Reset Control: Reading the Line Status Register. ''3'b010'': Interrupt Priority: 2nd priority Interrupt Type: Receiver Data Available or trigger level reached.(int_2) Interrupt source: FIFO Trigger level reached or RX FIFO full. Interrupt Reset Control: FIFO drops below trigger level ( depend on FCR[7:6]: rcvr_trig 000: 1, 001: 8, 110: 16, 111: 30) ''3'b110'': Interrupt Priority: 2nd priority Interrupt Type: Timeout Indication Interrupt source: There's at least 1 character in the FIFO but no character has been input to the FIFO or read from it for the last 4 characters times Interrupt Reset Control: Reading Receiver Buffer Register (RBR) ''3'b001'': Interrupt Priority: 3rd priority Interrupt Type: TXFIFO empty Interrupt source: TXFIFO empty Interrupt Reset Control: Writing to the TXFIFO or reading IIR (if source of interrupt) ''3'b000'': Interrupt Priority: 4th priority Interrupt Type: Modem Status Interrupt source: CTS, DSR, RI, or DCD (input relative signal) Interrupt Reset Control: Reading the Modem status register */
#define UART_SHIFT_INT_PEND                          0
#define UART_BIT_INT_PEND                            ((u32)0x00000001 << 0)                              /*!<R 1  Indicates that an interrupt is pending when it's logic ''0''. When it is ''1'', no interrupt is pending 0: an interrupt is pending and the IIR contents may be used as a pointer to the appropriate interrupt service routine 1: no interrupt is pending */
/** @} */

/**************************************************************************//**
 * @defgroup UART_FCR
 * @brief  FIFO Control Register                     (@ 0X008)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RXFIFO_TRIGGER_LEVEL              6
#define UART_MASK_RXFIFO_TRIGGER_LEVEL               ((u32)0x00000003 << 6)                              /*!<W 0  Define the 32-entries Receiver FIFO Interrupt trigger level 0~31 bytes ''00'': 1 byte ''01'': 8 bytes ''10'': 16 bytes ''11'': 30 bytes (for some device detect RTS de-assertion slower, reserve more RX FIFO space to prevent RX FIFO overflow ) */
#define UART_SHIFT_TXFIFO_LOW_LEVEL                  5
#define UART_BIT_TXFIFO_LOW_LEVEL                    ((u32)0x00000001 << 5)                              /*!<W 0  Define the Transmission FIFO Low Water Level Interrupt trigger. 0: 4 byte 1: 8 bytes */
#define UART_SHIFT_DMA_MODE                          3
#define UART_BIT_DMA_MODE                            ((u32)0x00000001 << 3)                              /*!<W 1  Support DMA mode. (cooperate with DW DDMA in the data path) */
#define UART_SHIFT_CLEAR_TXFIFO                      2
#define UART_BIT_CLEAR_TXFIFO                        ((u32)0x00000001 << 2)                              /*!<W 0  Writing a Logic ''1'' to Bit 2 clears the Transmitter FIFO and resets its logic. The shift register is not cleared, i.e., transmitting of the current character continues. The 1 that is written to this bit position is self-clearing */
#define UART_SHIFT_CLEAR_RXFIFO                      1
#define UART_BIT_CLEAR_RXFIFO                        ((u32)0x00000001 << 1)                              /*!<W 0  Writing a Logic ''1'' to Bit 1 clears the Receiver FIFO and resets its logic. But it doesn't clear the shift register, i.e. receiving of the current character continues. The 1 that is written to this bit position is self-clearing */
#define UART_SHIFT_EN_RXFIFO_ERR                     0
#define UART_BIT_EN_RXFIFO_ERR                       ((u32)0x00000001 << 0)                              /*!<W 1  Set as 1 to enable the report of Error in RCVR FIFO field in LSR bit [7] */
/** @} */

/**************************************************************************//**
 * @defgroup UART_LCR
 * @brief  Line Control Register                     (@ 0X00C)
 * @{
 *****************************************************************************/
#define UART_SHIFT_DLAB                              7
#define UART_BIT_DLAB                                ((u32)0x00000001 << 7)                              /*!<R/W 0  Divisor Latch Access bit 0: The divisor latches cannot be accessed 1: The divisor latches can be accessed Note: DLL/DLM only can be access when dlab bit = 1 IER only can be access when dlab bit = 0 THR/RBR don't care about dlab bit value. */
#define UART_SHIFT_BREAK_CTRL                        6
#define UART_BIT_BREAK_CTRL                          ((u32)0x00000001 << 6)                              /*!<R/W 0  Break Control bit 0: break is disabled 1: the serial out is forced into logic '0' (break state). Break control bit causes a break condition to be transmitted to the receiving UART. When it is set to logic 1, the serial output (Sout) is forced to the Spacing (logic 0) state. The break is disabled by setting bit 6 to logic 0. The Break Control bit acts only on SOUT and has no effect on the transmitter logic. */
#define UART_SHIFT_STICK_PARITY_EN                   5
#define UART_BIT_STICK_PARITY_EN                     ((u32)0x00000001 << 5)                              /*!<R/W 0  Stick Parity enable control. 1: Enable Stick Parity. 0: Disable Stick Parity. If the stick parity is enabled, the parity bit is controlled by the LCR bit[4]. LCR[5:4]: 00: Odd Parity 01: Even Parity 10: Stick Parity as 0 11: Stick Parity as 1 */
#define UART_SHIFT_EVEN_PARITY_SEL                   4
#define UART_BIT_EVEN_PARITY_SEL                     ((u32)0x00000001 << 4)                              /*!<R/W 0  Even Parity select 0: Odd number of Logic ''1'' is transmitted and checked in each word (data and parity combined). In other words, if the data has an even number of ''1'' in it, then the parity bit is ''1'' 1: Even number of ''1'' is transmitted in each word. */
#define UART_SHIFT_PARITY_EN                         3
#define UART_BIT_PARITY_EN                           ((u32)0x00000001 << 3)                              /*!<R/W 0  Parity Enable 0: No parity 1: Parity bit is generated on each outgoing character and is checked on each incoming one. */
#define UART_SHIFT_STB                               2
#define UART_BIT_STB                                 ((u32)0x00000001 << 2)                              /*!<R/W 0  This bit specifies the number of Stop bits transmitted and received in each serial character. 0: 1 stop bit. 1: 2 stop bits. Note that the receiver always checks the first stop bit only. */
#define UART_SHIFT_WLS0                              0
#define UART_BIT_WLS0                                ((u32)0x00000001 << 0)                              /*!<R/W 1  Word length selection, 0: data is 7 bit word length. 1: data is 8 bit word length. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_MCR
 * @brief  Modem Control Register                    (@ 0X010)
 * @{
 *****************************************************************************/
#define UART_SHIFT_SW_CTS                            7
#define UART_BIT_SW_CTS                              ((u32)0x00000001 << 7)                              /*!<R/W 0  Software controlled CTS. The software can use this bit to pause the UART transmission, just like the HW flow control. This is useful for software to implement XOn/XOff SW flow control. This bit setting will effects the CTS flow-control: CTS = cts_en ? (sw_cts | CTS_input) : sw_cts */
#define UART_SHIFT_RTS_EN                            6
#define UART_BIT_RTS_EN                              ((u32)0x00000001 << 6)                              /*!<R/W 0  RTS flow control enable (RTSE) This Bit (RTSE) is the auto RTS flow control enables. When set (1), the auto RTS flow control as described in the detailed description is enabled. Note: Auto-RTS_ data flow control originates in the receiver timing and control block and is linked to the programmed receiver FIFO trigger level. When the receiver FIFO level reaches a trigger level, RTS_ is de-asserted. The sending communication element may send an additional byte after the trigger level is reached (assuming the sending communication element has another byte to send) because it may not recognize the de-assertion of RTS_ until after it has begun sending the additional byte. RTS_ is automatically reasserted once the Receive FIFO is emptied. */
#define UART_SHIFT_CTS_EN                            5
#define UART_BIT_CTS_EN                              ((u32)0x00000001 << 5)                              /*!<R/W 0  CTS flow control enable (CTSE) This Bit (CTSE) is the auto CTS flow control enable. When set (1), the auto CTS flow control as described in the detailed description is enabled. Note: Auto-CTS_:The Transmitter circuitry checks CTS_ before sending the next data byte. When CTS_ is active, it sends the next byte. Top stop the transmitter from sending the following byte, CTS_ must be released before the middle of the last stop bit that is currently being sent. The auto-CTS_ function reduces interrupts to the host system. When flow control is enabled, CTS_ level changes do not trigger host interrupts because the device automatically controls its own transmitter. Without auto-CTS_, the transmitter sends any data present in the transmitter FIFO and a receiver overrun error may result. Note: With auto-CTS_, the CTS_ input must be active before the transmitter FIFO can emit data. With auto-RTS_, RTS_ becomes active when the receiver needs more data and notifies the sending serial device. When RTS_ is connected to CTS_, data transmission does not occur unless the receiver FIFO has space for the data; thus, overrun errors are eliminated with the auto flow control enabled. If not, overrun errors occurs when the transmit data rate exceeds the receiver FIFO read latency. Note: In the diagnostic mode, data that is transmitted is immediately received. This allows the CPU to verify the transmitting and receive data paths. The receiver and transmitter interrupts are fully operational. The modem control interrupts are also operational, but the modem control interrupt's sources are now the lower four bits of the MCR instead of four the four modem control inputs. All interrupts are still controlled by the IER */
#define UART_SHIFT_LOOPBACK_EN                       4
#define UART_BIT_LOOPBACK_EN                         ((u32)0x00000001 << 4)                              /*!<R/W 0  LoopBack mode 0: normal operation 1: loopback mode This bit provides a local loopback feature for diagnostic testing of the UART. When bit 4 is set to logic 1, the following occur: the transmitter Serial Output ( SOUT) is set to the Marking ( logic 1) state; the receiver Serial Input (SIN) is disconnected; the output of the Transmitter Shift Register is ''looped back'' into the Receiver Shift Register input; the four MODEM control inputs (DSR_, CTS_, RI_ and DCD_) are disconnected; and the four MODEM Control output (DTR_, RTS_, OUT1_, and OUT2_) are internally connected to the four MODEM Control inputs, and the MODEM Control output pins are forced to their inactive state (high). In the loop-back mode, data that is transmitted is immediately received. This feature allows the processor to verify the transmit-and-received data paths of the UART. In the loopback mode, the receiver and transmitter interrupts are fully operational. Their sources are external to the part. The MODEM Control interrupts are also operational, but the interrupts' sources are now the lower four bits of the MODEM Control Register instead of the four MODEM Control inputs. The interrupts are still controlled by the Interrupt Enable Register.  */
#define UART_SHIFT_OUT2                              3
#define UART_BIT_OUT2                                ((u32)0x00000001 << 3)                              /*!<R/W 0  This bit controls the output 2 (OUT2_) signal, which is an auxiliary user-designated output. Bit3 affects the OUT2_output in a manner identical to that described below for bit 0. In loopback mode, connected to Data Carrier Detect (DCD) */
#define UART_SHIFT_OUT1                              2
#define UART_BIT_OUT1                                ((u32)0x00000001 << 2)                              /*!<R/W 0  This bit controls the Output 1 (OUT1_) signal, which is an auxiliary user-designated output. Bit 2 affects the OUT1_ in a manner identical to that described below for bit 0. In loopback mode, connected Ring Indicator (RI) signal input */
#define UART_SHIFT_RTS                               1
#define UART_BIT_RTS                                 ((u32)0x00000001 << 1)                              /*!<R/W 0  Request to Send (RTS) signal control ''0'' RTS is logic 1 ''1'' RTS is logic 0 This bit controls the Request to Send (RTS) output. The RTS output is controlled as following equation: RTS_output = rts_en ? (~rts|FIFO_FlowCtrl):~rts */
#define UART_SHIFT_DTR                               0
#define UART_BIT_DTR                                 ((u32)0x00000001 << 0)                              /*!<R/W 0  Data Terminal Ready (DTR) signal control 0:DTR is logic 1 1:DTR is logic 0 This bit controls the Data Terminal Ready (DTR_) output. When bit 0 is set to logic 1, the DTR_ output is forced to logic 0. When bit0 reset to logic 0, the DTR_ output is forced to logic 1. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_LSR
 * @brief  Line Status Register                      (@ 0X014)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RXFIFO_ERR                        7
#define UART_BIT_RXFIFO_ERR                          ((u32)0x00000001 << 7)                              /*!<R 0  Uart_rx_error 1: In the FIFO mode, this bit (LSR bit7) is set when there is at least on parity error, framing error or break indication in the FIFO. LSR7 is clear when the CPU reads the LSR, if there are no subsequent errors in the FIFO. */
#define UART_SHIFT_TXFIFO_EMPTY                      5
#define UART_BIT_TXFIFO_EMPTY                        ((u32)0x00000001 << 5)                              /*!<R 0  TXFIFO empty indicator. 0: Otherwise 1: It indicates that the Transmitter FIFO is empty. This bit is set when the Transmitter FIFO is empty; it is cleared when at least 1 byte is written to the Transmitter FIFO. */
#define UART_SHIFT_BREAK_ERR_INT                     4
#define UART_BIT_BREAK_ERR_INT                       ((u32)0x00000001 << 4)                              /*!<R 0  Break Interrupt (BI) indicator 0: No break condition in the current character 1: set to logic 1 whenever the received data input is held in the Spacing (logic 0) state for a longer than a full word transmission time (that is, the total time of Start bit + data bits + Parity + Stop bits). The BI indicator is reset whenever the CPU reads the contents of the Line Status Register. This error is revealed to the CPU when its associated character is at the top of the FIFO. When break occurs only one zero character is loaded into the FIFO. The next character transfer is enabled after Serial-In goes to the marking state (Logic 1) and receives the next valid start bit. */
#define UART_SHIFT_FRAMING_ERR                       3
#define UART_BIT_FRAMING_ERR                         ((u32)0x00000001 << 3)                              /*!<R 0  Framing Error (FE) indicator 0: No framing error in the current character 1: The received character at the top of the FIFO did not have a valid stop bit. Of course, generally, it might be that all the following data is corrupt. It indicates that the received character did not have a valid stop bit. Bit 3 is set to a logic 1 whenever the Stop bit following the last data bit or parity bit is detected as a logic 0 bit (Spacing level). The FE indicator is reset whenever the CPU reads the contents of the Line Status Register. This error is revealed to the CPU when its associated character is at the top of the FIFO. The UART will try to resynchronize after a framing error. To do this it assumes that the framing error was due to the next start bit, so it samples this ''start'' bit twice and then takes in the ''data''. */
#define UART_SHIFT_PARITY_ERR                        2
#define UART_BIT_PARITY_ERR                          ((u32)0x00000001 << 2)                              /*!<R 0  Parity Error (PE) indicator 0: No parity error in current character 1: Indicates that the received data character does not have the correct even or odd parity, as selected by the even-parity-select bit. The PE bit is set to logic ''1'' upon detection of a parity error and is reset to logic 0 whenever the CPU reads the contents of the Line Status Register. This error is revealed to the CPU when its associated character is at the top of the FIFO (next character to be read). */
#define UART_SHIFT_OVERRUN_ERR                       1
#define UART_BIT_OVERRUN_ERR                         ((u32)0x00000001 << 1)                              /*!<R 0  Overrun Error (OE) indicator 0: No Overrun state 1: Indicates that data in the RX FIFO was not read by the CPU before the next character was transferred into the RX FIFO, thereby destroying the previous character. The OE indicator is set to logic 1 upon detection of an overrun condition and reset whenever the CPU reads the contents of the Line Status Register. If the FIFO mode data continues to fill the FIFO beyond the trigger level, an overrun error will occur only after the FIFO is full and the next character has been completely received in the shift register. OE is indicated to the CPU as soon as it happens. The character in the shift register is overwritten, but it is not transferred to the FIFO. */
#define UART_SHIFT_RXFIFO_DATARDY                    0
#define UART_BIT_RXFIFO_DATARDY                      ((u32)0x00000001 << 0)                              /*!<R 0  Data Ready (DR) indicator 0: No characters in the Receiver FIFO 1: At least one character has been received and transferred into the FIFO. Bit0 is reset to logic ''0'' by reading all of the data in the Receiver Buffer Register or the RX FIFO. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_MSR
 * @brief  Modem Status Register                     (@ 0X018)
 * @{
 *****************************************************************************/
#define UART_SHIFT_R_DCD                             7
#define UART_BIT_R_DCD                               ((u32)0x00000001 << 7)                              /*!<R 0  Complement of the DCD input or equals to Out2 in loopback mode. */
#define UART_SHIFT_R_RI                              6
#define UART_BIT_R_RI                                ((u32)0x00000001 << 6)                              /*!<R 0  Complement of the RI input or equals to Out1 in loopback mode. */
#define UART_SHIFT_R_DSR                             5
#define UART_BIT_R_DSR                               ((u32)0x00000001 << 5)                              /*!<R 0  Complement of the DSR input or equals to DTR in loopback mode. */
#define UART_SHIFT_R_CTS                             4
#define UART_BIT_R_CTS                               ((u32)0x00000001 << 4)                              /*!<R 0  Complement of the CTS input or equals to RTS in loopback mode. */
#define UART_SHIFT_D_DCD                             3
#define UART_BIT_D_DCD                               ((u32)0x00000001 << 3)                              /*!<R 0  Delta Data Carrier Detect (DDCD) indicator 1: The DCD line has changed its state. 0: Otherwise. */
#define UART_SHIFT_TERI                              2
#define UART_BIT_TERI                                ((u32)0x00000001 << 2)                              /*!<R 0  Trailing Edge of Ring Indicator (TERI) detector. The RI line has changed its state from low to high state */
#define UART_SHIFT_D_DSR                             1
#define UART_BIT_D_DSR                               ((u32)0x00000001 << 1)                              /*!<R 0  Delta Data Set Ready (DDSR) indicator 1: The DSR line has changed its state. 0: Otherwise */
#define UART_SHIFT_D_CTS                             0
#define UART_BIT_D_CTS                               ((u32)0x00000001 << 0)                              /*!<R 0  Delta Clear to Send (DCTS) indicator 1: The CTS line has changed its state. 0: Otherwise */
/** @} */

/**************************************************************************//**
 * @defgroup UART_SCR
 * @brief  Scratch Pad Register                      (@ 0X01C)
 * @{
 *****************************************************************************/
#define UART_SHIFT_XFACTOR_ADJ                       16
#define UART_MASK_XFACTOR_ADJ                        ((u32)0x000007FF << 16)                             /*!<R/W 0  One factor of Baud rate calculation, i.e., the ovsr_adj[10:0] of following formula. */
#define UART_SHIFT_DBG_SEL                           8
#define UART_MASK_DBG_SEL                            ((u32)0x0000000F << 8)                              /*!<R/W 0  Debug port selection */
#define UART_SHIFT_RX_BREAK_INT_STS                  7
#define UART_BIT_RX_BREAK_INT_STS                    ((u32)0x00000001 << 7)                              /*!<R/W 0  rx break signal interrupt status. Write one clear. */
#define UART_SHIFT_RX_BREAK_INT_EN                   6
#define UART_BIT_RX_BREAK_INT_EN                     ((u32)0x00000001 << 6)                              /*!<R/W 0  rx break signal interrupt enable */
#define UART_SHIFT_FL_SET_BI_ERR                     5
#define UART_BIT_FL_SET_BI_ERR                       ((u32)0x00000001 << 5)                              /*!<R 1   */
#define UART_SHIFT_FL_FRAME_ERR                      4
#define UART_BIT_FL_FRAME_ERR                        ((u32)0x00000001 << 4)                              /*!<R 1   */
#define UART_SHIFT_PIN_LB_TEST                       3
#define UART_BIT_PIN_LB_TEST                         ((u32)0x00000001 << 3)                              /*!<R/W 0  For uart IP txd/rxd/rts/cts pin loopback test */
/** @} */

/**************************************************************************//**
 * @defgroup UART_STSR
 * @brief  STS Register                              (@ 0X020)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RXFIFO_TRIGGER_LEVEL_STATUS       27
#define UART_MASK_RXFIFO_TRIGGER_LEVEL_STATUS        ((u32)0x00000003 << 27)                             /*!<R b'11  rxfifo_trigger_level in FCR bit[7:6], Define the 32-entries Receiver FIFO Interrupt trigger level 0~31 bytes 00: 1 byte 01: 8 bytes 10: 16 bytes 11: 28 bytes (for some device detect RTS de-assertion slower, reserve more RX FIFO space to prevent RX FIFO overflow ) */
#define UART_SHIFT_TXFIFO_LOW_LEVEL_STATUS           26
#define UART_BIT_TXFIFO_LOW_LEVEL_STATUS             ((u32)0x00000001 << 26)                             /*!<R 0  txfifo_low_level in FCR bit[5], Define the Transmission FIFO Low Water Level Interrupt trigger. 0: 4 byte 1: 8 bytes */
#define UART_SHIFT_FIFO_EN_STATUS                    25
#define UART_BIT_FIFO_EN_STATUS                      ((u32)0x00000001 << 25)                             /*!<R 1  fifo_en field of FCR bit[0] */
#define UART_SHIFT_DMA_MODE_STATUS                   24
#define UART_BIT_DMA_MODE_STATUS                     ((u32)0x00000001 << 24)                             /*!<R 1  dma_mode field of FCR bit[3] */
#define UART_SHIFT_XFACTOR                           4
#define UART_MASK_XFACTOR                            ((u32)0x0000000F << 4)                              /*!<R/W 0xb  Factor of Baud rate calculation, i.e., the ovsr[3:0] of following formula. */
#define UART_SHIFT_RESET_RCV                         3
#define UART_BIT_RESET_RCV                           ((u32)0x00000001 << 3)                              /*!<R/W 0  Reset Uart Receiver */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RBR
 * @brief  Receiver Buffer Register                  (@ 0X024)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RXDATA                            0
#define UART_MASK_RXDATA                             ((u32)0x000000FF << 0)                              /*!<R 0  Rx data. Note: Bit 0 is the least significant bit. It is the first bit serially received. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_THR
 * @brief  Transmitter Holder Register               (@ 0X024)
 * @{
 *****************************************************************************/
#define UART_SHIFT_TXDATA                            0
#define UART_MASK_TXDATA                             ((u32)0x000000FF << 0)                              /*!<W 0  Tx data. Note: Bit 0 is the least significant bit. It is the first bit serially transmitted. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_MISCR
 * @brief  MISC Control Register                     (@ 0X028)
 * @{
 *****************************************************************************/
#define UART_SHIFT_IRDA_RX_INV                       15
#define UART_BIT_IRDA_RX_INV                         ((u32)0x00000001 << 15)                             /*!<R/W 0  Invert irda_rx_i when 1; Default is 0; Note: Default IRDA RX pulse is Low Active */
#define UART_SHIFT_IRDA_TX_INV                       14
#define UART_BIT_IRDA_TX_INV                         ((u32)0x00000001 << 14)                             /*!<R/W 0  Invert irda_tx_o when 1; Default is 0; Note: Default IRDA TX Pulse is High Active */
#define UART_SHIFT_RXDMA_BURSTSIZE                   8
#define UART_MASK_RXDMA_BURSTSIZE                    ((u32)0x0000003F << 8)                              /*!<R/W 0x4  Rxdma burstsize */
#define UART_SHIFT_TXDMA_BURSTSIZE                   3
#define UART_MASK_TXDMA_BURSTSIZE                    ((u32)0x0000001F << 3)                              /*!<R/W 0x4  Txdma burstsize */
#define UART_SHIFT_RXDMA_EN                          2
#define UART_BIT_RXDMA_EN                            ((u32)0x00000001 << 2)                              /*!<R/W 1  1: rxdma is enabled (valid when dma_mode in FCR is 1'b1) 0: rxdma is disabled  */
#define UART_SHIFT_TXDMA_EN                          1
#define UART_BIT_TXDMA_EN                            ((u32)0x00000001 << 1)                              /*!<R/W 1  1: txdma is enabled (valid when dma_mode in FCR is 1'b1) 0: txdma is disabled */
#define UART_SHIFT_IRDA_ENABLE                       0
#define UART_BIT_IRDA_ENABLE                         ((u32)0x00000001 << 0)                              /*!<R/W 0  1: UART is co-work with IRDA SIR mode. i.e., txd/rxd are irda signals 0: UART mode only. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_TXPLSR
 * @brief  IRDA SIR TX Pulse Width Control 0 Register (@ 0X02C)
 * @{
 *****************************************************************************/
#define UART_SHIFT_UPPERBOUND_SHIFTRIGHT             31
#define UART_BIT_UPPERBOUND_SHIFTRIGHT               ((u32)0x00000001 << 31)                             /*!<R/W 0  0: shift left (minus offset value of txplsr[30:16]) 1: shift right (plus offset value txplsr[30:16]) */
#define UART_SHIFT_TXPULSE_UPPERBOUND_SHIFTVAL       16
#define UART_MASK_TXPULSE_UPPERBOUND_SHIFTVAL        ((u32)0x00007FFF << 16)                             /*!<R/W 0  The shift value of SIR tx pulse's right edge position. The nominal IRDA SIR tx pulse width is 3/16 bit time. If want to increase or decrease the right edge position of tx pulse then must change this value. Note: In time unit of uart clock period. Nominally the 10ns.(100Mhz uart clk) */
#define UART_SHIFT_LOWBOUND_SHIFTRIGHT               15
#define UART_BIT_LOWBOUND_SHIFTRIGHT                 ((u32)0x00000001 << 15)                             /*!<R/W 0  0: shift left (minus offset value of txplsr[14:0]) 1: shift right (plus offset value txplsr[14:0]) */
#define UART_SHIFT_TXPULSE_LOWBOUND_SHIFTVAL         0
#define UART_MASK_TXPULSE_LOWBOUND_SHIFTVAL          ((u32)0x00007FFF << 0)                              /*!<R/W 0  The shift value of SIR tx pulse's left edge position The nominal IRDA SIR tx pulse width is 3/16 bit time. If want to increase or decrease the left edge position of tx pulse then must change the value. Note: In time unit of uart clock period. Nominally the 10ns.(100Mhz uart clk) */
/** @} */

/**************************************************************************//**
 * @defgroup UART_DBG_UART
 * @brief  Debug Register                            (@ 0X03C)
 * @{
 *****************************************************************************/
#define UART_SHIFT_DBG_UART                          0
#define UART_MASK_DBG_UART                           ((u32)0xFFFFFFFF << 0)                              /*!<R 0  dbg_urt[31:0]: debug port output value, depend on dbg_sel value in SCR[2:0] */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RFCR
 * @brief  RX Filter Control Register                (@ 0X040)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RF_EN                             7
#define UART_BIT_RF_EN                               ((u32)0x00000001 << 7)                              /*!<R/W 0  RX Filter enable control 0: Disable 1: Enable */
#define UART_SHIFT_RF_CMP_OP                         2
#define UART_MASK_RF_CMP_OP                          ((u32)0x00000003 << 2)                              /*!<R/W 0  Set the RX filter comparing rule. The ''matched'' condition is listed as following table: RF_LEN = 0: RF_CMP_OP = 0 (AND) 1st byte = Magic Pattern1 1 (OR) (1st byte = Magic Pattern1) OR (1st byte = Magic Pattern2) 2 (XOR) (1st byte != Magic Pattern1) AND (1st byte != Magic Pattern2) RF_LEN = 1: RF_CMP_OP = 0 (AND) (1st byte = Magic Pattern1) AND (2nd byte = Magic Pattern2) 1 (OR) (2nd byte = Magic Pattern1) OR (2nd byte = Magic Pattern2) 2 (XOR) (1st byte != Magic Pattern1) AND (2nd byte != Magic Pattern2) */
#define UART_SHIFT_RF_MASK_EN                        1
#define UART_BIT_RF_MASK_EN                          ((u32)0x00000001 << 1)                              /*!<R/W 0  Enable the mask operation for received data. 0: No mask, compare the received bytes with the magic pattern directly. 1: Mask enabled, received data needs to ''AND'' with mask value before it to be compared with magic pattern. */
#define UART_SHIFT_RF_LEN                            0
#define UART_BIT_RF_LEN                              ((u32)0x00000001 << 0)                              /*!<R/W 0  Set the length of received data to be check. 0: Check the first 1 received byte only. 1: Check the first 2 received bytes. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RFMPR
 * @brief  RX Filter Magic Pattern Register          (@ 0X044)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RF_MP2                            8
#define UART_MASK_RF_MP2                             ((u32)0x000000FF << 8)                              /*!<R/W 0  The magic pattern2 for the 2nd received byte checking. */
#define UART_SHIFT_RF_MP1                            0
#define UART_MASK_RF_MP1                             ((u32)0x000000FF << 0)                              /*!<R/W 0  The magic pattern1 for the 1st received byte checking. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RFMVR
 * @brief  RX Filter Mask Value Register             (@ 0X048)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RF_MV2                            8
#define UART_MASK_RF_MV2                             ((u32)0x000000FF << 8)                              /*!<R/W 0xFF  The mask value for the 2nd received byte. */
#define UART_SHIFT_RF_MV1                            0
#define UART_MASK_RF_MV1                             ((u32)0x000000FF << 0)                              /*!<R/W 0xFF  The mask value for the 1st received byte. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RFTOR
 * @brief  RX Filter Timeout Register                (@ 0X04C)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RF_TIMEOUT                        0
#define UART_MASK_RF_TIMEOUT                         ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Set the timeout value of the RX filter idle detection. This value is number of ticks. A tick time is equal to a UART bit time. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RFLVR
 * @brief  RX FIFO Level Register                    (@ 0X050)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RX_FIFO_LV                        0
#define UART_MASK_RX_FIFO_LV                         ((u32)0x0000003F << 0)                              /*!<R 0  The level of the RX FIFO. This value indicates the number of data bytes in the RX FIFO.  */
/** @} */

/**************************************************************************//**
 * @defgroup UART_TFLVR
 * @brief  TX FIFO Level Register                    (@ 0X054)
 * @{
 *****************************************************************************/
#define UART_SHIFT_TX_FIFO_LV                        0
#define UART_MASK_TX_FIFO_LV                         ((u32)0x0000001F << 0)                              /*!<R 0  The level of the TX FIFO. This value indicates the number of data bytes in the TX FIFO.  */
/** @} */

/**************************************************************************//**
 * @defgroup UART_VISR
 * @brief  Vendor Interrupt Status Register          (@ 0X058)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RX_IDLE_TIMEOUT_INT_STS           3
#define UART_BIT_RX_IDLE_TIMEOUT_INT_STS             ((u32)0x00000001 << 3)                              /*!<R/W1C 0  This bit indicate the receiver idle timeout interrupt pending status. Write 1 to this bit will clear the pending status. */
#define UART_SHIFT_TX_FIFO_LV_INT_STS                2
#define UART_BIT_TX_FIFO_LV_INT_STS                  ((u32)0x00000001 << 2)                              /*!<R/W1C 0  This bit indicates the interrupt pending status of the TX FIFO water level equal to the level setting. The software can use this interrupt to know the TX FIFO water level is low and refill the TX FIFO. To enable this interrupt, IER bit[5] should be written as 1. Write 1 to this bit will clear the pending status. */
#define UART_SHIFT_RF_IDLE_TIMEOUT_INT_STS           1
#define UART_BIT_RF_IDLE_TIMEOUT_INT_STS             ((u32)0x00000001 << 1)                              /*!<R/W1C 0  This bit indicates the interrupt pending status of the RX filter timeout occurred. The RX idle detection mechanism is used to check whether the receiving is in idle state for re-aquire pattern matching. This mechanism uses a timer to monitor new data receiving. This timer will reload the initial value whenever a new byte is received. If the timeout occurred (timer value countdown to 0), the RX filter will be reset to the initialed state and restart the first received 1 or 2 bytes checking. */
#define UART_SHIFT_RF_PATT_MATCH_INT_STS             0
#define UART_BIT_RF_PATT_MATCH_INT_STS               ((u32)0x00000001 << 0)                              /*!<R/W1C 0  The interrupt status of RX filter pattern checking matched. Write 1 to clear this interrupt status. 0: Interrupt is not pending. 1: Interrupt is pending. */
/** @} */

/**************************************************************************//**
 * @defgroup UART_VIER
 * @brief  Vendor Interrupt Enabling Control Register (@ 0X05C)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RX_IDLE_TIMEOUT_INT_EN            3
#define UART_BIT_RX_IDLE_TIMEOUT_INT_EN              ((u32)0x00000001 << 3)                              /*!<R/W 0  The RX idle timeout interrupt enabling control: 1: enable 0: disable */
#define UART_SHIFT_TX_FIFO_LV_INT_EN                 2
#define UART_BIT_TX_FIFO_LV_INT_EN                   ((u32)0x00000001 << 2)                              /*!<R/W 0  The TX FIFO water level interrupt enabling control: 1: enable 0: disable */
#define UART_SHIFT_RF_IDLE_TIMEOUT_INT_EN            1
#define UART_BIT_RF_IDLE_TIMEOUT_INT_EN              ((u32)0x00000001 << 1)                              /*!<R/W 0  The Rx filter idle timeout interrupt enabling control: 1: enable 0: disable */
#define UART_SHIFT_RF_PATT_MATCH_INT_EN              0
#define UART_BIT_RF_PATT_MATCH_INT_EN                ((u32)0x00000001 << 0)                              /*!<R/W 0  The Rx filter pattern matched interrupt enabling control: 1: enable 0: disable */
/** @} */

/**************************************************************************//**
 * @defgroup UART_RITOR
 * @brief  RX Idle Timeout Register                  (@ 0X060)
 * @{
 *****************************************************************************/
#define UART_SHIFT_RX_IDLE_TIMEOUT_EN                31
#define UART_BIT_RX_IDLE_TIMEOUT_EN                  ((u32)0x00000001 << 31)                             /*!<R/W 0  RX idle timeout enable, default 0. */
#define UART_SHIFT_RXIDLE_TIMEOUT_VALUE              0
#define UART_MASK_RXIDLE_TIMEOUT_VALUE               ((u32)0x0000000F << 0)                              /*!<R/W 0  Time unit is the duration of a UART bit, depends on the baud-rate setting. Default 0. 0: 8 bit time. (1*8) 1: 16 bit time. (2*8) 2: 32 bit time. (2^2*8) 3: 64 bit time. (2^3*8) 4: 128 bit time. (2^4*8) 5: 256 bit time. (2^5*8) 6: 512 bit time. (2^6*8) 7: 1024 bit time. (2^7*8) 8: 2048 bit time. (2^8*8) 9: 4096 bit time. (2^9*8) 10: 8192 bit time. (2^10*8) 11: 16384 bit time. (2^11*8) 12: 32768 bit time. (2^12*8) 13: 65535 bit time. (2^13*8) 14: 131072 bit time. (2^14*8) 15: 262144 bit time. (2^15*8)  */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_UART
 * @{
 * @brief rtl8735b_UART Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t UART_DLLR ;                              /*!<  Divisor Latch (LS) Register register,  Address offset: 0x000 */
	__IO uint32_t UART_DLMR ;                              /*!<  Divisor Latch (MS) Register register,  Address offset: 0x004 */
	__IO uint32_t UART_IER ;                               /*!<  Interrupt Enable Register register,  Address offset: 0x004 */
	__I  uint32_t UART_IIR ;                               /*!<  Interrupt Identification Register register,  Address offset: 0x008 */
	__O  uint32_t UART_FCR ;                               /*!<  FIFO Control Register register,  Address offset: 0x008 */
	__IO uint32_t UART_LCR ;                               /*!<  Line Control Register register,  Address offset: 0x00C */
	__IO uint32_t UART_MCR ;                               /*!<  Modem Control Register register,  Address offset: 0x010 */
	__I  uint32_t UART_LSR ;                               /*!<  Line Status Register register,  Address offset: 0x014 */
	__I  uint32_t UART_MSR ;                               /*!<  Modem Status Register register,  Address offset: 0x018 */
	__IO uint32_t UART_SCR ;                               /*!<  Scratch Pad Register register,  Address offset: 0x01C */
	__IO uint32_t UART_STSR ;                              /*!<  STS Register register,  Address offset: 0x020 */
	__I  uint32_t UART_RBR ;                               /*!<  Receiver Buffer Register register,  Address offset: 0x024 */
	__O  uint32_t UART_THR ;                               /*!<  Transmitter Holder Register register,  Address offset: 0x024 */
	__IO uint32_t UART_MISCR ;                             /*!<  MISC Control Register register,  Address offset: 0x028 */
	__IO uint32_t UART_TXPLSR ;                            /*!<  IRDA SIR TX Pulse Width Control 0 Register register,  Address offset: 0x02C */
	__IO uint32_t RSVD0[3];                                /*!<  Reserved,  Address offset:0x30-0x38 */
	__I  uint32_t UART_DBG_UART ;                          /*!<  Debug Register register,  Address offset: 0x03C */
	__IO uint32_t UART_RFCR ;                              /*!<  RX Filter Control Register register,  Address offset: 0x040 */
	__IO uint32_t UART_RFMPR ;                             /*!<  RX Filter Magic Pattern Register register,  Address offset: 0x044 */
	__IO uint32_t UART_RFMVR ;                             /*!<  RX Filter Mask Value Register register,  Address offset: 0x048 */
	__IO uint32_t UART_RFTOR ;                             /*!<  RX Filter Timeout Register register,  Address offset: 0x04C */
	__IO uint32_t UART_RFLVR ;                             /*!<  RX FIFO Level Register register,  Address offset: 0x050 */
	__IO uint32_t UART_TFLVR ;                             /*!<  TX FIFO Level Register register,  Address offset: 0x054 */
	__IO uint32_t UART_VISR ;                              /*!<  Vendor Interrupt Status Register register,  Address offset: 0x058 */
	__IO uint32_t UART_VIER ;                              /*!<  Vendor Interrupt Enabling Control Register register,  Address offset: 0x05C */
	__IO uint32_t UART_RITOR ;                             /*!<  RX Idle Timeout Register register,          Address offset: 0x060 */
} UART_TypeDef;
/** @} */

#endif
