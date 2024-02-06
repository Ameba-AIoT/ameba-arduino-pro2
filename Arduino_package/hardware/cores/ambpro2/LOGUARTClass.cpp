/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LOGUARTClass.h"

// #define LOG_UART_MODIFIABLE_BAUD_RATE 1

#ifdef __cplusplus
extern "C" {
#endif

#include "serial_api.h"

serial_t log_uart_obj;

extern hal_uart_adapter_t log_uart;

#ifdef __cplusplus
}
#endif

RingBuffer rx_buffer0;

// volatile char rc = 0;

// void uart_send_str(serial_t *sobj, char *pstr)
//{
//     unsigned int i = 0;

//    while (*(pstr + i) != 0) {
//        serial_putc(sobj, *(pstr + i));
//        i++;
//    }
//}

void arduino_loguart_irq_handler(uint32_t id, SerialIrq event)
{
    char c;
    RingBuffer *pRxBuffer = (RingBuffer *)id;

    if (event == RxIrq) {
        c = char(serial_getc(&log_uart_obj));
        pRxBuffer->store_char(c);
    }

    // if (event == TxIrq && rc != 0) {
    //     uart_send_str(sobj, "\r\n8735b$");
    // rc = 0;
    // }
}

LOGUARTClass::LOGUARTClass(int dwIrq, RingBuffer *pRx_buffer)
{
    _rx_buffer = pRx_buffer;
    _dwIrq = dwIrq;
    log_uart_obj.uart_adp = log_uart;
}

// Protected Methods //////////////////////////////////////////////////////////////

// Public Methods //////////////////////////////////////////////////////////////
// zzw
#if 0
void LOGUARTClass::IrqHandler(void) {
    uint8_t     data = 0;
    BOOL        PullMode = _FALSE;

    uint32_t    IrqEn;
    //IrqEn = UART_IntStatus((UART_TypeDef*)UART2_DEV);
    IrqEn =  log_uart_obj.irq_en &= 0x02;

    serial_irq_set(&log_uart_obj, RxIrq, 0);
    //serial_irq_set(&log_uart_obj, TxIrq, 0);

    data = DiagGetChar(PullMode);
    if (data > 0) {
        _rx_buffer->store_char(data);
    }

    serial_irq_set(&log_uart_obj, RxIrq, IrqEn);
}
#endif

void LOGUARTClass::begin(const uint32_t dwBaudRate, uint8_t serial_config_value)
{
    // amb_ard_pin_check_fun(LOG_TX, PIO_UART);
    // amb_ard_pin_check_fun(LOG_RX, PIO_UART);

    if (log_uart_obj.uart_adp.is_inited != 0) {
        serial_free(&log_uart_obj);
    }
    // Log, UART1
    // serial_init(&log_uart_obj, PF_4, PF_3);
    ////serial_init(&log_uart_obj, PF_13, PF_12);
    serial_init(&log_uart_obj, PinName(g_APinDescription[LOG_TX].pinname), PinName(g_APinDescription[LOG_RX].pinname));

    // serial1, UART0
    // serial_init(&uart_obj, PA_2, PA_3);
    // serial_init(&uart_obj, PinName(g_APinDescription[SERIAL1_TX].pinname), PinName(g_APinDescription[SERIAL1_RX].pinname));

    // serial2, UART2
    // serial_init(&uart_obj, PD_15, PD_16);
    // serial_init(&uart_obj, PinName(g_APinDescription[SERIAL2_TX].pinname), PinName(g_APinDescription[SERIAL2_RX].pinname));

    // serial3, UART3
    // serial_init(&uart_obj, PE_1, PE_2);
    // serial_init(&uart_obj, PinName(g_APinDescription[SERIAL3_TX].pinname), PinName(g_APinDescription[SERIAL3_RX].pinname));

    uint32_t LOGUART_BaudRate = dwBaudRate;

#if LOG_UART_MODIFIABLE_BAUD_RATE
    /* log uart initialize in 115200 baud rate.
     * If we change baud rate here, Serail Monitor would not detect this change and show nothing on screen.
     */
#else
    LOGUART_BaudRate = 115200;
#endif
    serial_baud(&log_uart_obj, LOGUART_BaudRate);

    switch (serial_config_value) {
        // case SERIAL_5N1:
        //     break;
        // case SERIAL_6N1:
        //     break;
        case SERIAL_7N1:
            serial_format(&log_uart_obj, 7, ParityNone, 1);
            break;
        case SERIAL_8N1:
            serial_format(&log_uart_obj, 8, ParityNone, 1);
            break;
        // case SERIAL_5N2:
        //     break;
        // case SERIAL_6N2:
        //     break;
        case SERIAL_7N2:
            serial_format(&log_uart_obj, 7, ParityNone, 2);
            break;
        case SERIAL_8N2:
            serial_format(&log_uart_obj, 8, ParityNone, 2);
            break;
        // case SERIAL_5E1:
        //     break;
        // case SERIAL_6E1:
        //     break;
        case SERIAL_7E1:
            serial_format(&log_uart_obj, 7, ParityEven, 1);
            break;
        case SERIAL_8E1:
            serial_format(&log_uart_obj, 8, ParityEven, 1);
            break;
        // case SERIAL_5E2:
        //     break;
        // case SERIAL_6E2:
        //     break;
        case SERIAL_7E2:
            serial_format(&log_uart_obj, 7, ParityEven, 2);
            break;
        case SERIAL_8E2:
            serial_format(&log_uart_obj, 8, ParityEven, 2);
            break;
        // case SERIAL_5O1:
        //     break;
        // case SERIAL_6O1:
        //     break;
        case SERIAL_7O1:
            serial_format(&log_uart_obj, 7, ParityOdd, 1);
            break;
        case SERIAL_8O1:
            serial_format(&log_uart_obj, 8, ParityOdd, 1);
            break;
        // case SERIAL_5O2:
        //     break;
        // case SERIAL_6O2:
        //     break;
        case SERIAL_7O2:
            serial_format(&log_uart_obj, 7, ParityOdd, 2);
            break;
        case SERIAL_8O2:
            serial_format(&log_uart_obj, 8, ParityOdd, 2);
            break;
        // case SERIAL_511:
        //     break;
        // case SERIAL_611:
        //     break;
        case SERIAL_711:
            serial_format(&log_uart_obj, 7, ParityForced1, 1);
            break;
        case SERIAL_811:
            serial_format(&log_uart_obj, 8, ParityForced1, 1);
            break;
        // case SERIAL_512:
        //     break;
        // case SERIAL_612:
        //     break;
        case SERIAL_712:
            serial_format(&log_uart_obj, 7, ParityForced1, 2);
            break;
        case SERIAL_812:
            serial_format(&log_uart_obj, 8, ParityForced1, 2);
            break;
        // case SERIAL_501:
        //     break;
        // case SERIAL_601:
        //     break;
        case SERIAL_701:
            serial_format(&log_uart_obj, 7, ParityForced0, 1);
            break;
        case SERIAL_801:
            serial_format(&log_uart_obj, 8, ParityForced0, 1);
            break;
        // case SERIAL_502:
        //     break;
        // case SERIAL_602:
        //     break;
        case SERIAL_702:
            serial_format(&log_uart_obj, 7, ParityForced0, 2);
            break;
        case SERIAL_802:
            serial_format(&log_uart_obj, 8, ParityForced0, 2);
            break;
        default:
            serial_format(&log_uart_obj, 8, ParityNone, 1);
    }

    serial_irq_handler(&log_uart_obj, arduino_loguart_irq_handler, (uint32_t)_rx_buffer);
    serial_irq_set(&log_uart_obj, RxIrq, 1);
    // serial_irq_set(&log_uart_obj, TxIrq, 1);
}

void LOGUARTClass::end(void)
{
    // clear any received data
    _rx_buffer->_iHead = _rx_buffer->_iTail;
    serial_free(&log_uart_obj);
}

int LOGUARTClass::available(void)
{
    return (uint32_t)(SERIAL_BUFFER_SIZE + _rx_buffer->_iHead - _rx_buffer->_iTail) % SERIAL_BUFFER_SIZE;
}

int LOGUARTClass::peek(void)
{
    if (_rx_buffer->_iHead == _rx_buffer->_iTail) {
        return -1;
    }

    return _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
}

int LOGUARTClass::read(void)
{
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer->_iHead == _rx_buffer->_iTail) {
        return -1;
    }

    uint8_t uc = _rx_buffer->_aucBuffer[_rx_buffer->_iTail];
    _rx_buffer->_iTail = (unsigned int)(_rx_buffer->_iTail + 1) % SERIAL_BUFFER_SIZE;
    return uc;
}

void LOGUARTClass::flush(void)
{
    // TODO:
    // while ( serial_writable(&(this->sobj)) != 1 );
    /*
      // Wait for transmission to complete
      while ((_pUart->UART_SR & UART_SR_TXRDY) != UART_SR_TXRDY)
        ;
    */
}

size_t LOGUARTClass::write(const uint8_t uc_data)
{
    serial_putc(&log_uart_obj, ((int)uc_data));
    return 1;
}

bool Serial_available()
{
    return Serial.available() > 0;
}

//    UART0_IRQn                =   9,              /*!< 9  UART0*/
//    UART1_IRQn                =  10,              /*!< 10 UART1*/
//    UART2_IRQn                =  11,              /*!< 11 UART2*/
//    UART3_IRQn                =  12,              /*!< 12 UART3*/

LOGUARTClass Serial(UART1_IRQn, &rx_buffer0);
