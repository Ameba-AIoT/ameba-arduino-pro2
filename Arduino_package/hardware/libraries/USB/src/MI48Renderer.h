#ifndef _MI48_RENDERER_H_
#define _MI48_RENDERER_H_

#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "MI48Decoder.h"

/*
 * MI48Renderer
 *
 * Turns a decoded thermal frame (MI48Decoder) into:
 *   - per-pixel / min / max Celsius temperatures
 *   - a 12x12 temperature grid
 *   - grayscale or false-colour NV12 for a video encoder
 *
 * It is a pure consumer: the caller decodes first, then renders. The pixel
 * data still lives in the decoder.
 */
class MI48Renderer {
public:
    static constexpr uint8_t GRID_COLS = 12;
    static constexpr uint8_t GRID_ROWS = 12;
    static constexpr uint16_t GRID_COUNT = GRID_COLS * GRID_ROWS;

    /*
     * Raw sensor value is unsigned 16-bit deci-Kelvin:
     *
     *     Celsius = raw / 10.0 - 273.15
     */
    static float rawToCelsius(uint16_t raw);

    uint16_t pixelRawValue(MI48Decoder &frame, uint16_t x, uint16_t y);
    float pixelTemperatureC(MI48Decoder &frame, uint16_t x, uint16_t y);

    uint16_t minRaw(MI48Decoder &frame);
    uint16_t maxRaw(MI48Decoder &frame);
    float minCelsius(MI48Decoder &frame);
    float maxCelsius(MI48Decoder &frame);

    /*
     * Fill 144 values using the same 12x12 sampling method used by the
     * original thermal-camera pipeline.
     */
    bool temperatureGrid12x12(MI48Decoder &frame, float *out, size_t count);

    /*
     * Required size for a tightly packed NV12 frame.
     *
     * NV12 requires even width and height.
     * Returns 0 for an invalid size.
     */
    static size_t nv12BufferSize(uint16_t dstWidth, uint16_t dstHeight);

    /*
     * Convert to grayscale NV12 using nearest-neighbour scaling.
     *
     * mirrorX=true matches the horizontally mirrored rainbow path used by
     * the original module_mi48.c.
     */
    bool toNV12(MI48Decoder &frame, uint8_t *dst, size_t dstSize, uint16_t dstWidth, uint16_t dstHeight,
                bool mirrorX = true);

    /*
     * Convert to false-colour NV12.
     *
     * cmapY/cmapU/cmapV must each point to a 256-entry lookup table.
     * This lets the existing Realtek/Meridian colormap.h be reused without
     * making the renderer depend on that header.
     */
    bool toNV12Colormap(MI48Decoder &frame, uint8_t *dst, size_t dstSize, uint16_t dstWidth,
                        uint16_t dstHeight, const uint8_t *cmapY, const uint8_t *cmapU, const uint8_t *cmapV,
                        bool mirrorX = true);

    /*
     * CRC-16/CCITT-FALSE over the decoded 160x120 pixel bytes.
     *
     * Diagnostics only: the original USB implementation notes the GFRA header
     * CRC may cover a different span, so do not reject frames on this alone.
     */
    uint16_t pixelCRC16(MI48Decoder &frame);

private:
    static uint8_t normalizeTo8(uint16_t raw, uint16_t minRaw, uint16_t maxRaw);

    static uint16_t crc16CcittFalse(const uint8_t *data, size_t length);
};

#endif /* _MI48_RENDERER_H_ */
