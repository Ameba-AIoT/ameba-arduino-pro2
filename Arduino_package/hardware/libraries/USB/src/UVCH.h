#ifndef __UVCH_H__
#define __UVCH_H__

#include <Arduino.h>
#include "ff.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <platform_stdlib.h>
#include "osdep_service.h"

// FreeRTOS USB Stack v1.0.0.
// usb_os.h MUST come first: it pulls in ameba_soc.h, which defines __PACKED,
// used by usb_ch9.h when it declares usb_setup_req_t.
//
// These use explicit paths on purpose. A bare "usb_ch9.h" resolves to
// system/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/inc/usb_ch9.h
// (include position 33, guard _USB_CH9_H_), which does NOT define
// usb_setup_req_t. That ROM copy shadows the v1.0.0 header at position 168.
#include "usb_stack/v1.0.0/common/usb_os.h"
#include "usb_stack/v1.0.0/common/usb_ch9.h"
#include "usb_stack/v1.0.0/common/usb_hal.h"
#include "usb_stack/v1.0.0/host/core/usbh.h"
#include "usb_stack/v1.0.0/host/uvc/usbh_uvc.h"

#include "fatfs_sdcard_api.h"

#ifdef __cplusplus
}
#endif

#define USBH_UVC_JFIF_TAG 0xFF
#define USBH_UVC_JFIF_SOI 0xD8
#define USBH_UVC_JFIF_EOI 0xD9

#define WARMUP_FRAMES     30
#define USBH_UVC_BUF_SIZE 500000U

#define DEBUG_UVC 1

extern SDRAM_BSS_SECTION u8 uvc_buf[USBH_UVC_BUF_SIZE];
extern int uvc_buf_size;

class UVCH {
public:
    UVCH(int width, int height, int frame_rate, int format);
    ~UVCH(void);

    static int uvcIsInit(void);
    static int uvcIsDeinit(void);
    static int uvcIsAttach(void);
    static int uvcIsDetach(void);

    static int usbStatus(usb_host_t *host, uint8_t id);
    bool initUSB(void);
    bool initUVC(void);
    void initSD(void);
    void deinitUVC(void);
    void deinitUSB(void);
    void deinitSD(void);
    void setParameters(void);
    bool readyToCapture(void);
    bool uvcFrameToBuf(usbh_uvc_frame_t *frame);
    void saveImageToSD(void);
    void startStream(void);
    void stopStream(void);
    void captureFrameStart(void);
    bool isUsbConnected(void);
    bool attachedReady(uint32_t timeout_ms);

private:
    static volatile bool _attached;
    static volatile bool _usbConnected;

    int _warmupCount = 0;
    int _saveCount = 0;

    // Format parameters
    int _width;
    int _height;
    int _frame_rate;
    int _fmt_type;

    // SD card
    static int _sdInitDone;
    static int _imgFileNoSD;
    static fatfs_sd_params_t _fatfsSd;
    static FIL _mFile;
};
#endif
