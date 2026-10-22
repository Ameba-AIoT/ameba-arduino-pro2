#include "MI48ThermalCamera.h"
#include <USBHostCDC.h>
#include <MI48Protocol.h>
#include <MI48Decoder.h>
#include <MI48Renderer.h>
#include "MI48Encoder.h"
#include "colormap.h"
#include <stdlib.h>
#include <string.h>

static USBHostCDC cdc;
static MI48Protocol mi48;
static MI48Decoder decoder;
static MI48Renderer renderer;
static uint8_t *pendingFrame, *decodeFrame, *nv12;
static void *nv12Allocation;
static uint16_t width, height;
static size_t nv12Bytes;
static bool pending, temperaturesReady, attempted;
static float temperatures[144];
static uint32_t frames;
static uint32_t lastLog = 0;
static bool usbStarted = false;
static bool useRainbow = true;   /* false = grayscale NV12 */

/* One decode + NV12 + JPEG pass. Returns true if a frame was encoded. */
static bool processOneFrame()
{
    if (!pending) {
        return false;
    }

    noInterrupts();
    memcpy(decodeFrame, pendingFrame, MI48Protocol::GFRA_PAYLOAD_SIZE);
    pending = false;
    interrupts();

    if (!decoder.decode(decodeFrame, MI48Protocol::GFRA_PAYLOAD_SIZE)) {
        return false;
    }

    bool rendered;
    if (useRainbow) {
        rendered = renderer.toNV12Colormap(decoder, nv12, nv12Bytes, width, height, cmap_y, cmap_u, cmap_v, false);
    } else {
        rendered = renderer.toNV12(decoder, nv12, nv12Bytes, width, height, false);
    }

    if (!rendered) {
        return false;
    }

    int result = mi48_stream_encode(nv12);
    if (result <= 0) {
        return false;
    }

    float grid[144];
    if (renderer.temperatureGrid12x12(decoder, grid, 144)) {
        noInterrupts();
        memcpy(temperatures, grid, sizeof(grid));
        temperaturesReady = true;
        interrupts();
    }

    noInterrupts();
    ++frames;
    interrupts();

    return true;
}

bool MI48ThermalCamera::begin(uint16_t videoWidth, uint16_t videoHeight, uint8_t videoFps, uint8_t videoChannel, uint32_t videoBps, uint32_t videoType, uint32_t videoResolution, uint32_t videoExtFmt, bool videoUseRainbow)
{
    if (attempted || _p_mmf_context || !videoWidth || !videoHeight || videoWidth > 1920 || videoHeight > 1080
        || (videoWidth & 1) || (videoHeight & 1) || !videoFps || videoFps > 30) {
        return false;
    }
    attempted = true;
    useRainbow = videoUseRainbow;
    width = videoWidth;
    height = videoHeight;
    nv12Bytes = MI48Renderer::nv12BufferSize(width, height);
    pendingFrame = static_cast<uint8_t *>(malloc(MI48Protocol::GFRA_PAYLOAD_SIZE));
    decodeFrame = static_cast<uint8_t *>(malloc(MI48Protocol::GFRA_PAYLOAD_SIZE));
    nv12Allocation = malloc(nv12Bytes + 31);
    if (!pendingFrame || !decodeFrame || !nv12Allocation) {
        return false;
    }
    nv12 = reinterpret_cast<uint8_t *>((reinterpret_cast<uintptr_t>(nv12Allocation) + 31) & ~static_cast<uintptr_t>(31));
    if (!cdc.begin() || !mi48.begin(cdc, 10000)) {
        return false;
    }
    usbStarted = true;
    _p_mmf_context = static_cast<mm_context_t *>(mi48_stream_open(width, height, videoFps, videoChannel, videoBps, videoType, videoResolution, videoExtFmt));
    return _p_mmf_context != NULL;
}

bool MI48ThermalCamera::start()
{
    /* No background task anymore: RX + encoder are driven from loop() via
     * poll()/process(). Keep the call for API compatibility. */
    return _p_mmf_context != NULL;
}

bool MI48ThermalCamera::poll()
{
    if (!usbStarted) {
        return false;
    }

    uint32_t now = millis();
    if ((now - lastLog) >= 2000) {
        lastLog = now;
        printf("MI48 USB: connected=%d ready=%d RX=%lu dropped=%lu\r\n", cdc.connected(), mi48.ready(),
               (unsigned long)cdc.rxBytes(), (unsigned long)cdc.droppedBytes());
        printf("MI48 USB TX=%lu\r\n", (unsigned long)cdc.txBytes());
    }
    mi48.poll();
    if (mi48.frameAvailable()) {
        uint32_t length = 0;
        const uint8_t *frame = mi48.getFrame(&length);
        if (frame && length == MI48Protocol::GFRA_PAYLOAD_SIZE) {
            noInterrupts();
            memcpy(pendingFrame, frame, length);
            pending = true;
            interrupts();
        }
    }
    return true;
}

bool MI48ThermalCamera::process()
{
    if (!usbStarted) {
        return false;
    }
    return processOneFrame();
}

uint32_t MI48ThermalCamera::frameCount()
{
    noInterrupts();
    uint32_t count = frames;
    interrupts();
    return count;
}

bool MI48ThermalCamera::readTemperatures(float values[144])
{
    if (!values) {
        return false;
    }
    noInterrupts();
    bool ready = temperaturesReady;
    if (ready) {
        memcpy(values, temperatures, sizeof(temperatures));
    }
    interrupts();
    return ready;
}
