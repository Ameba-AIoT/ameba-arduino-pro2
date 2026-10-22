#include "UVCH.h"

SDRAM_BSS_SECTION u8 uvc_buf[USBH_UVC_BUF_SIZE];
int uvc_buf_size = 0;

usbh_uvc_cb_t uvc_cb = {
    .init = UVCH::uvcIsInit,
    .deinit = UVCH::uvcIsDeinit,
    .attach = UVCH::uvcIsAttach,
    .detach = UVCH::uvcIsDetach,
    .setup = nullptr,
    .set_param = nullptr
};

usbh_user_cb_t user_cb = {
    .process = UVCH::usbStatus,
};

/* v1.0.0 host config. The legacy host_channels / dma_enable / *_fifo_size
 * members do not exist in this stack; FIFO depths are in dwords. */
static usbh_config_t usbh_cfg = {
    /* USBH_SOF_INTR is required: usbh_hal_host_init() only sets the SOF
     * interrupt enable bit in GAHBCFG when this flag is set (or when
     * tick_source == USBH_SOF_TICK). Without SOF the UVC class driver's
     * usbh_uvc_sof() callback never fires, so no isochronous URBs are
     * queued and usbh_uvc_get_frame() always times out. */
    .ext_intr_enable = USBH_SOF_INTR,
    .rx_fifo_depth = 0x200U,
    .nptx_fifo_depth = 0x100U,
    .ptx_fifo_depth = 0x100U,
    .main_task_stack_size = 2048U,
    .main_task_priority = 3U,
    .isr_priority = 4U,
    .xfer_retry_max_cnt = 3U,
    .class_num = 1U,
    .tick_source = USBH_SW_TICK,
    .speed = USB_SPEED_HIGH,
};

volatile bool UVCH::_attached = false;
volatile bool UVCH::_usbConnected = false;

int UVCH::_imgFileNoSD = 0;
int UVCH::_sdInitDone = 0;
fatfs_sd_params_t UVCH::_fatfsSd;
FIL UVCH::_mFile;

UVCH::UVCH(int width, int height, int frame_rate, int format)
{
    _width = width;
    _height = height;
    _frame_rate = frame_rate;
    _fmt_type = format;

    // No OTG-mode call here. usbh_hcd_init() already performs
    // usb_hal_set_otg_mode(USB_OTG_MODE_HOST) as part of usbh_init().
    // Calling it from this constructor would run during static initialisation -
    // before the scheduler starts and before the USB clock/PHY are enabled -
    // and usb_hal_set_otg_mode() both touches USB registers and calls
    // usb_os_sleep_ms(), which faults at that point.
}

UVCH::~UVCH(void)
{
}

int UVCH::uvcIsInit(void)
{
    printf("UVC Init\n");
    return HAL_OK;
}

int UVCH::uvcIsDeinit(void)
{
    printf("UVC Deinit\n");
    return HAL_OK;
}

int UVCH::uvcIsAttach(void)
{
    _attached = true;
    printf("UVC Attach\n");
    return HAL_OK;
}

int UVCH::uvcIsDetach(void)
{
    _attached = false;
    printf("UVC Detach\n");
    return HAL_OK;
}

int UVCH::usbStatus(usb_host_t *host, uint8_t id)
{
    switch (id) {
        case USBH_MSG_CONNECTED:
            _usbConnected = true;
            break;

        case USBH_MSG_DISCONNECTED:
            _usbConnected = false;
            _attached = false;
            _sdInitDone = 0;
            break;
    }
    return 0;
}

bool UVCH::initUSB(void)
{
    int ret = usbh_init(&usbh_cfg, &user_cb);
    if (ret != HAL_OK) {
        printf("\nFail to init USB\n");
        return false;
    }
    return true;
}

bool UVCH::isUsbConnected(void)
{
    return _usbConnected;
}

bool UVCH::initUVC(void)
{
    usbh_uvc_ctx_t cfg = {};

    cfg.frame_buf_size = 500000;

    int ret = usbh_uvc_init(&cfg, &uvc_cb);

    if (ret != 0) {
        printf("UVC init failed: %d\n", ret);
        return false;
    }

    // usbh_uvc_init() registers the UVC class driver, but the v1.0.0 stack
    // does not begin enumeration until usbh_start() is called. The legacy
    // stack started automatically, so this call has no legacy equivalent.
    ret = usbh_start();
    if (ret != 0) {
        printf("Fail to start USB host: %d\n", ret);
        return false;
    }

    return true;
}

void UVCH::initSD()
{
    int res;

    if (_sdInitDone) {
        return;
    }

    printf("Init FATFS SD...\n");

    res = fatfs_sd_init();
    if (res < 0) {
        printf("fatfs_sd_init fail: %d\n", res);
        return;
    }

    fatfs_sd_get_param(&_fatfsSd);
    printf("SD mounted at: %s\n", _fatfsSd.drv);

    _sdInitDone = 1;
}

bool UVCH::attachedReady(uint32_t timeout_ms)
{
    uint32_t start = millis();
    while (!_attached) {
        if ((millis() - start) > timeout_ms) {
            printf("Attach timeout (%lu ms)\n", timeout_ms);
            return false;
        }
        delay(10);
    }
    return true;
}

bool UVCH::readyToCapture(void)
{
    _warmupCount++;

    if (_warmupCount < WARMUP_FRAMES) {
        return false;
    }

    _saveCount++;

    if ((_saveCount % _frame_rate) != 0) {
        return false;
    }

    return true;
}

bool UVCH::uvcFrameToBuf(usbh_uvc_frame_t *frame)
{
    uint32_t len = 0;
    uint32_t start = 0;

    if (frame != NULL) {
        if (_fmt_type == USBH_UVC_FORMAT_MJPEG) {

            uint8_t *ptr = frame->buf;
            len = frame->byteused;
            uint32_t end = frame->byteused - 2;

            if (len < 4) {
                printf("\nToo short uvc data, len=%lu\n", len);
                return false;
            }

            // Check mjpeg image data
            while (start < len - 1) {
                if ((ptr[start] == USBH_UVC_JFIF_TAG) && (ptr[start + 1] == USBH_UVC_JFIF_SOI)) {    // Check SOI
                    while (end > 0) {
                        if (ptr[end + 1] != 0) {
                            if ((ptr[end] == USBH_UVC_JFIF_TAG) && (ptr[end + 1] == USBH_UVC_JFIF_EOI)) {    // Check EOI
                                break;
                            } else {
                                printf("\nInvalid uvc data, len=%lu, end with %02X %02X\n", frame->byteused, ptr[end], ptr[end + 1]);
                                return false;
                            }
                        }
                        end--;
                    }
                    break;
                }
                start++;
            }

            if (start == len - 1) {
                printf("\nInvalid uvc data, len=%lu, start with %02X %02X\n", frame->byteused, frame->buf[0], frame->buf[1]);
                return false;
            }

            len = end + 2 - start;

            if (!readyToCapture()) {
                return false;
            }
#ifdef DEBUG_UVC
            if (len == frame->byteused) {
                printf("\nCapture uvc data, len=%lu\n", len);
            } else {
                printf("\nCapture uvc data, start=%lu, end=%lu, actul_len=%lu, buf->len=%lu\n", start, end + 2, len, frame->byteused);
            }
#endif
        } else {
            len = frame->byteused;
        }

        if (len > USBH_UVC_BUF_SIZE) {
            printf("\nImage len overflow!\n");
            return false;
        }

        rtw_memcpy(uvc_buf, (void *)(frame->buf + start), len);
        uvc_buf_size = len;
    }

    return true;
}

void UVCH::saveImageToSD()
{
    int res;
    UINT bw;
    char filename[64];
    char path[128];

    if (uvc_buf_size == 0) {
        printf("Invalid image buffer (size=0)\n");
        return;
    }

    if (!_sdInitDone) {
        initSD();
    }

    if (!_sdInitDone) {
        return;
    }

    snprintf(filename, sizeof(filename), "img%d.jpeg", _imgFileNoSD);
    snprintf(path, sizeof(path), "%s%s", _fatfsSd.drv, filename);

    res = f_open(&_mFile, path, FA_CREATE_ALWAYS | FA_WRITE);
    if (res) {
        printf("Fail to open file (%s): %d\n", path, res);
        return;
    }

    printf("Create image file: %s\n", path);

    res = f_write(&_mFile, uvc_buf, uvc_buf_size, &bw);

    if (res || bw != (UINT)uvc_buf_size) {
        printf("Fail to write file: res=%d bw=%lu size=%d\n",
               res, bw, uvc_buf_size);
        f_close(&_mFile);
        return;
    }

    printf("Write %lu bytes\n", bw);

    res = f_close(&_mFile);
    if (res) {
        printf("Fail to close file (%s): %d\n", path, res);
        return;
    }

    _imgFileNoSD++;
}

// void UVCH::setParameters(void)
// {
//     struct uvc_config uvc_ctx;

//     uvc_ctx.fmt_type = _fmt_type;
//     uvc_ctx.width = _width;
//     uvc_ctx.height = _height;
//     uvc_ctx.frame_rate = _frame_rate;

//     if (usbh_uvc_set_param(&uvc_ctx, 0) == 0) {
//         printf("UVC para: %d*%d@%dfps\n", uvc_ctx.width, uvc_ctx.height, uvc_ctx.frame_rate);
//     }
// }

void UVCH::setParameters(void)
{
    usbh_uvc_s_ctx_t uvc_ctx = {};

    uvc_ctx.fmt_type = _fmt_type;
    uvc_ctx.width = _width;
    uvc_ctx.height = _height;
    uvc_ctx.frame_rate = _frame_rate;
    uvc_ctx.frame_buf_size = USBH_UVC_BUF_SIZE;

    int ret = usbh_uvc_set_param(&uvc_ctx, 0);

    if (ret == HAL_OK) {
        printf("UVC para: %d*%d@%dfps\n",
               uvc_ctx.width,
               uvc_ctx.height,
               uvc_ctx.frame_rate);
    } else {
        printf("UVC set param failed: %d\n", ret);
    }
}

void UVCH::startStream(void)
{
    while (!_usbConnected) {
        printf("USB not connected\n");
        delay(1000);
    }

    printf("Preparing to start...\n");

    // Time to stabilize — important for hot-plug
    delay(3000);

    setParameters();

    printf("\nUVC stream on\n");
    usbh_uvc_start(0);

    if (!_attached) {
        if (!attachedReady(3000)) {
            return;
        }

        delay(1000);
        usbh_uvc_stop(0);
        setParameters();
        usbh_uvc_start(0);
    }

    uint32_t frame_wait = millis();
    while ((millis() - frame_wait) < 5000) {
        usbh_uvc_frame_t *first_frame = usbh_uvc_get_frame(0);
        if (first_frame != NULL) {
            usbh_uvc_put_frame(first_frame, 0);
            break;
        }
        delay(100);
    }
}

void UVCH::captureFrameStart(void)
{
    // usbh_get_status() does not exist in the v1.0.0 stack. _usbConnected is
    // driven by usbStatus() from the USBH_MSG_CONNECTED / _DISCONNECTED
    // callbacks, so no polling is needed here.

    // USB physically disconnected — wait for reconnection, then re-init
    if (!_usbConnected) {
        printf("USB disconnected, waiting for reconnection...\n");

        uint32_t t = millis();
        while (!_usbConnected) {
            if ((millis() - t) > 10000) {
                printf("Reconnect timeout\n");
                return;
            }
            delay(100);
        }

        printf("USB reconnected, waiting for UVC device...\n");

        usbh_uvc_stop(0);

        _warmupCount = 0;
        _saveCount = 0;

        if (!attachedReady(3000)) {
            return;
        }

        startStream();
        return;
    }

    // USB connected but no UVC device attached yet — just wait
    if (!_attached) {
        delay(100);
        return;
    }
    usbh_uvc_frame_t *buf = usbh_uvc_get_frame(0);
    if (buf == NULL) {
        delay(10);
        return;
    }

    if (uvcFrameToBuf(buf)) {
        usbh_uvc_put_frame(buf, 0);

        if (uvc_buf_size > 0) {
            saveImageToSD();
            uvc_buf_size = 0;
        }
    } else {
        usbh_uvc_put_frame(buf, 0);
    }

    delay(1);

#ifdef DEBUG_UVC
    static int dbg_cnt = 0;
    if ((++dbg_cnt % 100) == 0) {
        printf("heap=0x%lx\n", rtw_getFreeHeapSize());
    }
#endif
}

void UVCH::deinitUVC(void)
{
    usbh_uvc_deinit();
}

void UVCH::stopStream(void)
{
    usbh_uvc_stop(0);
    deinitUVC();
}

void UVCH::deinitUSB(void)
{
    usbh_deinit();
}

void UVCH::deinitSD(void)
{
    if (_sdInitDone) {
        fatfs_sd_close();
        _sdInitDone = 0;
        printf("SD deinitialized\n");
    }
}
