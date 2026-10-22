#include "USBHostCDC.h"

// #include "usbh.h"
// #include "usbh_cdc_acm.h"

#include "usb_stack/v1.0.0/common/usb_ch9.h"
#include "usb_stack/v1.0.0/common/usb_hal.h"

#include "usb_stack/v1.0.0/host/core/usbh.h"
#include "usb_stack/v1.0.0/host/cdc_acm/usbh_cdc_acm.h"

#include <string.h>

/* --------------------------------------------------------------------------
 * Configuration
 * -------------------------------------------------------------------------- */

#define CDCH_RX_DMA_SIZE 4096
#define CDCH_TX_DMA_SIZE 512

/*
 * Must be power of two for the simple ring-buffer implementation below.
 *
 * Increase this if the connected CDC device sends large bursts.
 * The MI48 GFRA message is ~39.7 KB (> 8192), so the ring MUST be >= 39696.
 */
#define CDCH_RX_RING_SIZE 40960

#define CDCH_TX_RETRY_COUNT 20
#define CDCH_TX_RETRY_MS    10
#define CDCH_TX_TIMEOUT_MS  1000

#define CDCH_CTRL_RETRY_COUNT 30
#define CDCH_CTRL_RETRY_MS    10


/* --------------------------------------------------------------------------
 * Internal state
 *
 * Realtek's CDC Host implementation is effectively a single class instance,
 * so this first Arduino wrapper supports one active USBHostCDC object.
 * -------------------------------------------------------------------------- */

static USBHostCDC *g_cdch_owner = nullptr;

static volatile bool g_cdch_started = false;
static volatile bool g_cdch_connected = false;
static volatile bool g_cdch_rx_armed = false;

static volatile bool g_cdch_tx_done = false;
static volatile uint8_t g_cdch_tx_status = 0;


/* --------------------------------------------------------------------------
 * DMA buffers
 *
 * These buffers are passed directly to the USB Host driver.
 * They MUST satisfy the USB DMA alignment requirements.
 * -------------------------------------------------------------------------- */

static uint8_t g_cdch_rx_dma[CDCH_RX_DMA_SIZE] USB_DMA_ALIGNED;
static uint8_t g_cdch_tx_dma[CDCH_TX_DMA_SIZE] USB_DMA_ALIGNED;


/* --------------------------------------------------------------------------
 * Arduino-side RX ring buffer
 *
 * USB callback:
 *
 *      USB DMA buffer
 *           |
 *           v
 *       RX ring buffer
 *           |
 *           v
 *     available()/read()
 *
 * USB DMA memory is therefore never exposed to the Arduino sketch.
 * -------------------------------------------------------------------------- */

static uint8_t g_cdch_rx_ring[CDCH_RX_RING_SIZE];

static volatile uint32_t g_cdch_rx_head = 0;
static volatile uint32_t g_cdch_rx_tail = 0;


/* --------------------------------------------------------------------------
 * Statistics
 * -------------------------------------------------------------------------- */

static volatile uint32_t g_cdch_rx_bytes = 0;
static volatile uint32_t g_cdch_tx_bytes = 0;
static volatile uint32_t g_cdch_dropped_bytes = 0;


/* --------------------------------------------------------------------------
 * Forward declarations
 * -------------------------------------------------------------------------- */

static int cdch_usb_init(void);
static int cdch_usb_deinit(void);

static int cdch_usb_attach(void);
static int cdch_usb_detach(void);
static int cdch_usb_setup(void);

static int cdch_usb_receive(uint8_t *buf, uint32_t len, uint8_t status);
static int cdch_usb_transmit(uint8_t status);

static int cdch_usb_line_coding_changed(usb_cdc_line_coding_t *line_coding);

static bool cdch_arm_receive(void);

static void cdch_ring_reset(void);
static void cdch_ring_push(const uint8_t *data, uint32_t len);

static usbh_config_t g_cdch_host_config = {};

/* --------------------------------------------------------------------------
 * Realtek CDC ACM callbacks
 * -------------------------------------------------------------------------- */

static usbh_cdc_acm_cb_t g_cdch_callbacks = {
    .init = cdch_usb_init,
    .deinit = cdch_usb_deinit,

    .attach = cdch_usb_attach,
    .detach = cdch_usb_detach,

    .setup = cdch_usb_setup,

    .receive = cdch_usb_receive,
    .transmit = cdch_usb_transmit,

    .line_coding_changed = cdch_usb_line_coding_changed,
};

USBHostCDC::USBHostCDC()
{}

bool USBHostCDC::begin()
{
    /*
     * Current Realtek CDC Host stack supports one active CDC host class.
     */
    if ((g_cdch_owner != nullptr) && (g_cdch_owner != this)) {
        return false;
    }

    if (g_cdch_started) {
        return true;
    }

    g_cdch_owner = this;

    g_cdch_connected = false;
    g_cdch_rx_armed = false;

    g_cdch_tx_done = false;
    g_cdch_tx_status = 0;

    g_cdch_rx_bytes = 0;
    g_cdch_tx_bytes = 0;
    g_cdch_dropped_bytes = 0;

    cdch_ring_reset();

    g_cdch_host_config.speed = USB_SPEED_HIGH;
    g_cdch_host_config.ext_intr_enable = 0;
    g_cdch_host_config.isr_priority = 4;

    g_cdch_host_config.main_task_stack_size = 1024;
    g_cdch_host_config.main_task_priority = 3; /* tskIDLE_PRIORITY is 0 */

    g_cdch_host_config.tick_source = USBH_SOF_TICK;

    g_cdch_host_config.class_num = 1;

    g_cdch_host_config.rx_fifo_depth = 1712;
    g_cdch_host_config.nptx_fifo_depth = 256;
    g_cdch_host_config.ptx_fifo_depth = 256;

    int ret = usbh_init(&g_cdch_host_config, nullptr);

    if (ret != HAL_OK) {
        g_cdch_owner = nullptr;
        return false;
    }

    ret = usbh_cdc_acm_init(&g_cdch_callbacks);

    if (ret != HAL_OK) {
        usbh_deinit();

        g_cdch_owner = nullptr;

        return false;
    }

    usbh_start();

    g_cdch_started = true;

    return true;
}

void USBHostCDC::end()
{
    if (!g_cdch_started) {
        return;
    }

    g_cdch_connected = false;
    g_cdch_rx_armed = false;

    usbh_cdc_acm_deinit();
    usbh_deinit();

    cdch_ring_reset();

    g_cdch_started = false;
    g_cdch_owner = nullptr;
}

bool USBHostCDC::connected()
{
    return g_cdch_connected;
}

int USBHostCDC::available()
{
    /*
     * Start BULK IN the first time the Arduino application attempts
     * to receive data.
     *
     * We deliberately do not start this directly inside the USB setup
     * callback because the Realtek Host state machine may still be
     * transitioning into CLASS_READY.
     */
    ensureReceiveStarted();

    uint32_t head = g_cdch_rx_head;
    uint32_t tail = g_cdch_rx_tail;

    if (head >= tail) {
        return (int)(head - tail);
    }

    return (int)(CDCH_RX_RING_SIZE - tail + head);
}

int USBHostCDC::read()
{
    ensureReceiveStarted();

    uint32_t tail = g_cdch_rx_tail;

    if (tail == g_cdch_rx_head) {
        return -1;
    }

    uint8_t value = g_cdch_rx_ring[tail];

    tail++;

    if (tail >= CDCH_RX_RING_SIZE) {
        tail = 0;
    }

    g_cdch_rx_tail = tail;

    return value;
}

// Non-blocking
size_t USBHostCDC::read(uint8_t *buffer, size_t size)
{
    if ((buffer == nullptr) || (size == 0)) {
        return 0;
    }

    size_t count = 0;

    while (count < size) {

        int c = read();

        if (c < 0) {
            break;
        }

        buffer[count++] = (uint8_t)c;
    }

    return count;
}

int USBHostCDC::peek()
{
    ensureReceiveStarted();

    uint32_t tail = g_cdch_rx_tail;

    if (tail == g_cdch_rx_head) {
        return -1;
    }

    return g_cdch_rx_ring[tail];
}

void USBHostCDC::flush()
{}

size_t USBHostCDC::write(uint8_t data)
{
    return write(&data, 1);
}


/* --------------------------------------------------------------------------
 * write(buffer)
 *
 * The Realtek CDC transmit call is asynchronous.
 *
 * Therefore:
 *
 *   Arduino buffer
 *        |
 *        v
 *   aligned DMA buffer
 *        |
 *        v
 * usbh_cdc_acm_transmit()
 *        |
 *        v
 *   TX callback
 *
 * We wait for completion before reusing g_cdch_tx_dma.
 * -------------------------------------------------------------------------- */

size_t USBHostCDC::write(const uint8_t *buffer, size_t size)
{
    if ((buffer == nullptr) || (size == 0)) {
        return 0;
    }

    if (!g_cdch_connected) {
        return 0;
    }

    size_t total_sent = 0;

    while (total_sent < size) {

        size_t remaining = size - total_sent;

        size_t chunk = remaining;
        if (chunk > CDCH_TX_DMA_SIZE) {
            chunk = CDCH_TX_DMA_SIZE;
        }

        memcpy(g_cdch_tx_dma, buffer + total_sent, chunk);

        g_cdch_tx_done = false;
        g_cdch_tx_status = 0xFF;

        int ret = HAL_ERR_UNKNOWN;

        /*
         * CDC Host may temporarily report BUSY while the previous
         * asynchronous state finishes.
         */
        for (uint32_t retry = 0; retry < CDCH_TX_RETRY_COUNT; retry++) {

            ret = usbh_cdc_acm_transmit(g_cdch_tx_dma, (uint32_t)chunk);

            if (ret == HAL_OK) {
                break;
            }

            delay(CDCH_TX_RETRY_MS);
        }

        if (ret != HAL_OK) {
            break;
        }

        /*
         * Wait until CDC TX callback completes.
         */
        uint32_t start = millis();

        while (!g_cdch_tx_done) {

            if ((uint32_t)(millis() - start) >= CDCH_TX_TIMEOUT_MS) {

                return total_sent;
            }

            delay(1);
        }

        if (g_cdch_tx_status != HAL_OK) {
            break;
        }

        total_sent += chunk;
        g_cdch_tx_bytes += chunk;
    }

    return total_sent;
}

// CDC ACM:
// bit 0 = DTR
// bit 1 = RTS

bool USBHostCDC::setLineCoding(uint32_t baud)
{
    if (!g_cdch_connected) {
        return false;
    }

    usb_cdc_line_coding_t lc;
    memset(&lc, 0, sizeof(lc));

    lc.b.dwDteRate = baud;
    lc.b.bCharFormat = 0; /* 1 stop bit  */
    lc.b.bParityType = 0; /* none        */
    lc.b.bDataBits = 8;   /* 8 data bits */

    for (uint32_t retry = 0; retry < CDCH_CTRL_RETRY_COUNT; retry++) {

        int ret = usbh_cdc_acm_set_line_coding(&lc);

        if (ret == HAL_OK) {
            return true;
        }

        if (ret == HAL_ERR_PARA) {
            return false;
        }

        delay(CDCH_CTRL_RETRY_MS);
    }

    return false;
}

bool USBHostCDC::setControlLineState(bool dtr, bool rts)
{
    if (!g_cdch_connected) {
        return false;
    }

    uint16_t state = 0;

    if (dtr) {
        state |= 0x0001;
    }

    if (rts) {
        state |= 0x0002;
    }

    for (uint32_t retry = 0; retry < CDCH_CTRL_RETRY_COUNT; retry++) {

        int ret = usbh_cdc_acm_set_control_line_state(state);

        if (ret == HAL_OK) {
            return true;
        }

        /*
         * HAL_ERR_PARA usually means the request itself is invalid /
         * unsupported rather than temporarily busy.
         */
        if (ret == HAL_ERR_PARA) {
            return false;
        }

        delay(CDCH_CTRL_RETRY_MS);
    }

    return false;
}

uint32_t USBHostCDC::rxBytes()
{
    return g_cdch_rx_bytes;
}


uint32_t USBHostCDC::txBytes()
{
    return g_cdch_tx_bytes;
}


uint32_t USBHostCDC::droppedBytes()
{
    return g_cdch_dropped_bytes;
}

bool USBHostCDC::ensureReceiveStarted()
{
    if (!g_cdch_connected) {
        return false;
    }

    if (g_cdch_rx_armed) {
        return true;
    }

    return cdch_arm_receive();
}

static bool cdch_arm_receive(void)
{
    if (!g_cdch_connected) {
        return false;
    }

    if (g_cdch_rx_armed) {
        return true;
    }

    int ret = usbh_cdc_acm_receive(g_cdch_rx_dma, sizeof(g_cdch_rx_dma));

    if (ret == HAL_OK) {
        g_cdch_rx_armed = true;

        return true;
    }

    return false;
}

static void cdch_ring_reset(void)
{
    g_cdch_rx_head = 0;
    g_cdch_rx_tail = 0;
}


static void cdch_ring_push(const uint8_t *data, uint32_t len)
{
    if (data == nullptr) {
        return;
    }

    for (uint32_t i = 0; i < len; i++) {

        uint32_t next = g_cdch_rx_head + 1;

        if (next >= CDCH_RX_RING_SIZE) {
            next = 0;
        }

        /*
         * Full:
         *
         * head would catch tail.
         *
         * Drop the newest byte rather than overwrite unread
         * Arduino application data.
         */
        if (next == g_cdch_rx_tail) {
            g_cdch_dropped_bytes++;
            continue;
        }

        g_cdch_rx_ring[g_cdch_rx_head] = data[i];

        g_cdch_rx_head = next;
    }
}

static int cdch_usb_init(void)
{
    return HAL_OK;
}


static int cdch_usb_deinit(void)
{
    g_cdch_connected = false;
    g_cdch_rx_armed = false;

    return HAL_OK;
}

static int cdch_usb_attach(void)
{
    g_cdch_connected = false;
    g_cdch_rx_armed = false;

    cdch_ring_reset();

    return HAL_OK;
}

static int cdch_usb_detach(void)
{
    g_cdch_connected = false;
    g_cdch_rx_armed = false;

    cdch_ring_reset();

    return HAL_OK;
}

static int cdch_usb_setup(void)
{
    g_cdch_connected = true;
    g_cdch_rx_armed = false;

    return HAL_OK;
}

static int cdch_usb_receive(uint8_t *buf, uint32_t len, uint8_t status)
{
    /*
     * The previous transfer has completed.
     */
    g_cdch_rx_armed = false;

    if ((status == HAL_OK) && (buf != nullptr) && (len > 0)) {

        cdch_ring_push(buf, len);

        g_cdch_rx_bytes += len;
    }

    /*
     * status == HAL_OK && len == 0 is allowed.
     *
     * Do not treat a zero-length completion as an Arduino-level error.
     */

    /*
     * Immediately re-arm BULK IN.
     *
     * This is important for continuously streaming CDC devices.
     */
    if (g_cdch_connected) {

        int ret = usbh_cdc_acm_receive(g_cdch_rx_dma, sizeof(g_cdch_rx_dma));

        if (ret == HAL_OK) {
            g_cdch_rx_armed = true;
        }
    }

    return HAL_OK;
}

static int cdch_usb_transmit(uint8_t status)
{
    g_cdch_tx_status = status;
    g_cdch_tx_done = true;

    return HAL_OK;
}

static int cdch_usb_line_coding_changed(usb_cdc_line_coding_t *line_coding)
{
    (void)line_coding;

    return HAL_OK;
}
