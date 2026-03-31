/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#include <string.h>
#include "osif.h"
#include "hci_uart.h"
#include "hci_dbg.h"
#include "serial_api.h"
#include "serial_ex_api.h"

#define HCI_UART_TX_DMA          1

#define HCI_UART_TX_FIFO_SIZE    (16)
#define HCI_UART_RX_FIFO_SIZE    (32)
#define HCI_UART_RX_BUF_SIZE     (0x2000)   /* RX buffer size 8K */
#define HCI_UART_RX_ENABLE_SIZE  (512)      /* Only 512 left to read */
#define HCI_UART_RX_DISABLE_SIZE (128)      /* Only 128 left to write */

#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
#define HCI_UART_TX_BUF_SIZE     (512)      /* TX buffer size 512 */
#endif

static struct amebapro2_uart_t
{
    /* Serial UART */
    serial_t     serial_obj;

    /* UART RX RingBuf */
    uint8_t*     ring_buffer;
    uint32_t     ring_buffer_size;
    uint32_t     write_ptr;
    uint32_t     read_ptr;
    uint8_t      rx_disabled;

    /* UART RX Indication */
    HCI_RECV_IND rx_ind;

    /* UART TX */
#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
    uint8_t*     tx_buffer;
    void*        tx_done_sem;
#endif

    /* UART Bridge */
    uint8_t      bridge_flag;
} *amebapro2_uart = NULL;

_WEAK void bt_uart_bridge_putc(uint8_t tx_data)
{
    (void)tx_data;
}

void amebapro2_uart_bridge_open(uint8_t flag)
{
    if (amebapro2_uart)
        amebapro2_uart->bridge_flag = flag;
    else
        HCI_ERR("amebapro2_uart is NULL!");
}

void amebapro2_uart_bridge_to_hci(uint8_t rc)
{
    serial_putc(&amebapro2_uart->serial_obj, rc);
}

void amebapro2_uart_hci_to_bridge(uint8_t rc)
{
    bt_uart_bridge_putc(rc);
}

static uint8_t amebapro2_uart_set_bdrate(uint32_t baudrate)
{
    serial_baud(&amebapro2_uart->serial_obj, baudrate);
    HCI_INFO("Set baudrate to %d success!", baudrate);
    return HCI_SUCCESS;
}

static uint8_t amebapro2_uart_set_rx_ind(HCI_RECV_IND rx_ind)
{
    amebapro2_uart->rx_ind = rx_ind;
    return HCI_SUCCESS;
}

static inline uint16_t amebapro2_uart_rx_to_read_space(void)
{
    return (amebapro2_uart->write_ptr + amebapro2_uart->ring_buffer_size - amebapro2_uart->read_ptr) % amebapro2_uart->ring_buffer_size;
}

static inline uint16_t amebapro2_uart_rx_to_write_space(void)
{
    return (amebapro2_uart->read_ptr + amebapro2_uart->ring_buffer_size - amebapro2_uart->write_ptr - 1) % amebapro2_uart->ring_buffer_size;
}

static void amebapro2_uart_irq(uint32_t id, SerialIrq event)
{
    uint8_t ch;
    uint16_t write_len = amebapro2_uart_rx_to_write_space();
    uint16_t max_count = (write_len > HCI_UART_RX_FIFO_SIZE) ? HCI_UART_RX_FIFO_SIZE : write_len;

    if (event == RxIrq) {
        if (amebapro2_uart->bridge_flag) {
            while (serial_readable(&amebapro2_uart->serial_obj) && max_count-- > 0)
            {
                ch = serial_getc(&amebapro2_uart->serial_obj);
                amebapro2_uart_hci_to_bridge(ch);
            }
        } else {
            while (serial_readable(&amebapro2_uart->serial_obj) && max_count-- > 0)
            {
                ch = serial_getc(&amebapro2_uart->serial_obj);
                amebapro2_uart->ring_buffer[amebapro2_uart->write_ptr++] = ch;
                amebapro2_uart->write_ptr %= amebapro2_uart->ring_buffer_size;
            }

            if (!amebapro2_uart->rx_disabled && amebapro2_uart_rx_to_write_space() < HCI_UART_RX_DISABLE_SIZE)
            {
                serial_irq_set(&amebapro2_uart->serial_obj, RxIrq, 0);
                amebapro2_uart->rx_disabled = 1;
                HCI_INFO("amebapro2_uart rx disable!");
            }

            if (amebapro2_uart->rx_ind)
                amebapro2_uart->rx_ind();
        }
    }
}

static uint16_t amebapro2_uart_send(uint8_t *buf, uint16_t len)
{
#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
    int ret;
    if ((uint32_t)buf % 32 != 0) { //if p_buf address is not 32B aligned
        if (len > HCI_UART_TX_BUF_SIZE)
            return 0;

        memcpy(amebapro2_uart->tx_buffer, buf, len);
        ret = serial_send_stream_dma(&amebapro2_uart->serial_obj, (char *)amebapro2_uart->tx_buffer, len);
    } else {
        ret = serial_send_stream_dma(&amebapro2_uart->serial_obj, (char *)buf, len);
    }

    if (ret != 0) {
        HCI_ERR("serial_send_stream_dma fail!");
        return 0;
    }

    if (amebapro2_uart->tx_done_sem) {
        if (osif_sem_take(amebapro2_uart->tx_done_sem, 0xFFFFFFFF) == false) {
            HCI_ERR("amebapro2_uart->tx_done_sem take fail!");
            return 0;
        }
    }
#else
    serial_send_blocked(&amebapro2_uart->serial_obj, (char *)buf, len, UART_WAIT_FOREVER);
#endif

    return len;
}

#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
static void amebapro2_uart_send_done(uint32_t id)
{
    if (amebapro2_uart->tx_done_sem)
        osif_sem_give(amebapro2_uart->tx_done_sem);
}
#endif

static uint16_t amebapro2_uart_read(uint8_t *buf, uint16_t len)
{
    uint16_t read_len = amebapro2_uart_rx_to_read_space();
    read_len = (read_len > len) ? len : read_len;

    if (0 == read_len)
        return 0;

    if (read_len > amebapro2_uart->ring_buffer_size - amebapro2_uart->read_ptr)
        read_len = amebapro2_uart->ring_buffer_size - amebapro2_uart->read_ptr;

    memcpy(buf, &amebapro2_uart->ring_buffer[amebapro2_uart->read_ptr], read_len);
    amebapro2_uart->read_ptr += read_len;
    amebapro2_uart->read_ptr %= amebapro2_uart->ring_buffer_size;

    if (amebapro2_uart->rx_disabled && amebapro2_uart_rx_to_read_space() < HCI_UART_RX_ENABLE_SIZE)
    {
        serial_irq_set(&amebapro2_uart->serial_obj, RxIrq, 1);
        amebapro2_uart->rx_disabled = 0;
        HCI_INFO("amebapro2_uart rx enable!");
    }

    return read_len;
}

static uint8_t amebapro2_uart_open(void)
{
    /* Init amebapro2_uart */
    if (!amebapro2_uart)
    {
        amebapro2_uart = osif_mem_alloc(RAM_TYPE_DATA_ON, sizeof(struct amebapro2_uart_t));
        if (!amebapro2_uart) {
            HCI_ERR("amebapro2_uart is NULL!");
            return HCI_FAIL;
        }
        memset(amebapro2_uart, 0, sizeof(struct amebapro2_uart_t));
    }
    if (!amebapro2_uart->ring_buffer)
    {
        amebapro2_uart->ring_buffer = osif_mem_aligned_alloc(0, HCI_UART_RX_BUF_SIZE, 4);
        if (!amebapro2_uart->ring_buffer) {
            HCI_ERR("amebapro2_uart->ring_buffer is NULL!");
            return HCI_FAIL;
        }
        memset(amebapro2_uart->ring_buffer, 0, sizeof(HCI_UART_RX_BUF_SIZE));
    }
    amebapro2_uart->ring_buffer_size = HCI_UART_RX_BUF_SIZE;
    amebapro2_uart->read_ptr = 0;
    amebapro2_uart->write_ptr = 0;
    amebapro2_uart->rx_disabled = 0;
    amebapro2_uart->rx_ind = 0;

#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
    if (!amebapro2_uart->tx_buffer)
    {
        amebapro2_uart->tx_buffer = osif_mem_aligned_alloc(0, HCI_UART_TX_BUF_SIZE, 32);
        if (!amebapro2_uart->tx_buffer) {
            HCI_ERR("amebapro2_uart->tx_buffer is NULL!");
            return HCI_FAIL;
        }
        memset(amebapro2_uart->tx_buffer, 0, sizeof(HCI_UART_TX_BUF_SIZE));
    }

    if (osif_sem_create(&amebapro2_uart->tx_done_sem, 0, 1) == false) {
        HCI_ERR("amebapro2_uart->tx_done_sem create fail!");
        return HCI_FAIL;
    }
#endif

    hal_uart_init(&amebapro2_uart->serial_obj.uart_adp, PIN_UART4_TX, PIN_UART4_RX, NULL);
    serial_baud(&amebapro2_uart->serial_obj, 115200);
    serial_format(&amebapro2_uart->serial_obj, 8, ParityNone, 1);
    amebapro2_uart->serial_obj.uart_adp.base_addr->fcr_b.rxfifo_trigger_level = FifoLvHalf;
    //serial_rx_fifo_level(&amebapro2_uart->serial_obj, FifoLvHalf);
    serial_set_flow_control(&amebapro2_uart->serial_obj, FlowControlRTSCTS, NC, NC);
#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
    serial_send_comp_handler(&amebapro2_uart->serial_obj, (void *)amebapro2_uart_send_done, (uint32_t)&amebapro2_uart->serial_obj);
#endif
    serial_clear_rx(&amebapro2_uart->serial_obj);
    serial_irq_handler(&amebapro2_uart->serial_obj, amebapro2_uart_irq, (uint32_t)&amebapro2_uart->serial_obj);
    serial_irq_set(&amebapro2_uart->serial_obj, RxIrq, 1);

    return HCI_SUCCESS;
}

static uint8_t amebapro2_uart_close(void)
{
    if (!amebapro2_uart)
    {
        HCI_ERR("amebapro2_uart is NULL!");
        return HCI_FAIL;
    }

    /* Disable Serial UART */
    serial_irq_set(&amebapro2_uart->serial_obj, RxIrq, 0);
    serial_free(&amebapro2_uart->serial_obj);
    memset(&amebapro2_uart->serial_obj, 0, sizeof(serial_t));

    return HCI_SUCCESS;
}

static uint8_t amebapro2_uart_free(void)
{
    if (!amebapro2_uart)
    {
        HCI_ERR("amebapro2_uart is NULL!");
        return HCI_FAIL;
    }

#if defined(HCI_UART_TX_DMA) && HCI_UART_TX_DMA
    if (amebapro2_uart->tx_done_sem) {
        osif_sem_delete(amebapro2_uart->tx_done_sem);
        amebapro2_uart->tx_done_sem = NULL;
    }

    if (amebapro2_uart->tx_buffer)
        osif_mem_aligned_free(amebapro2_uart->tx_buffer);
#endif
    /* Deinit UART Ringbuf */
    if (amebapro2_uart->ring_buffer)
        osif_mem_aligned_free(amebapro2_uart->ring_buffer);

    osif_mem_free(amebapro2_uart);
    amebapro2_uart = NULL;

    return HCI_SUCCESS;
}

HCI_UART_OPS hci_uart_ops = {
    .open          = amebapro2_uart_open,
    .close         = amebapro2_uart_close,
    .free_ops      = amebapro2_uart_free,
    .send          = amebapro2_uart_send,
    .read          = amebapro2_uart_read,
    .set_rx_ind    = amebapro2_uart_set_rx_ind,
    .set_bdrate    = amebapro2_uart_set_bdrate,
    .bridge_open   = amebapro2_uart_bridge_open,
    .bridge_to_hci = amebapro2_uart_bridge_to_hci,
};
