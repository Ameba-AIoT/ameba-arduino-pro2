#include "MI48Renderer.h"

#include <math.h>
#include <string.h>

/* --------------------------------------------------------------------------
 * Temperature helpers
 * -------------------------------------------------------------------------- */

float MI48Renderer::rawToCelsius(uint16_t raw)
{
    return ((float)raw / 10.0f) - 273.15f;
}

uint16_t MI48Renderer::pixelRawValue(MI48Decoder &frame, uint16_t x, uint16_t y)
{
    const uint16_t *pixels = frame.pixels();

    if ((pixels == nullptr) || (x >= MI48Decoder::WIDTH) || (y >= MI48Decoder::HEIGHT)) {
        return 0;
    }

    return pixels[((uint32_t)y * MI48Decoder::WIDTH) + x];
}

float MI48Renderer::pixelTemperatureC(MI48Decoder &frame, uint16_t x, uint16_t y)
{
    const uint16_t *pixels = frame.pixels();

    if ((pixels == nullptr) || (x >= MI48Decoder::WIDTH) || (y >= MI48Decoder::HEIGHT)) {
        return NAN;
    }

    return rawToCelsius(pixels[((uint32_t)y * MI48Decoder::WIDTH) + x]);
}

uint16_t MI48Renderer::minRaw(MI48Decoder &frame)
{
    if (!frame.valid()) {
        return 0;
    }
    return frame.frameInfo().minRaw;
}

uint16_t MI48Renderer::maxRaw(MI48Decoder &frame)
{
    if (!frame.valid()) {
        return 0;
    }
    return frame.frameInfo().maxRaw;
}

float MI48Renderer::minCelsius(MI48Decoder &frame)
{
    if (!frame.valid()) {
        return NAN;
    }
    return rawToCelsius(frame.frameInfo().minRaw);
}

float MI48Renderer::maxCelsius(MI48Decoder &frame)
{
    if (!frame.valid()) {
        return NAN;
    }
    return rawToCelsius(frame.frameInfo().maxRaw);
}

bool MI48Renderer::temperatureGrid12x12(MI48Decoder &frame, float *out, size_t count)
{
    const uint16_t *pixels = frame.pixels();

    if ((pixels == nullptr) || (out == nullptr) || (count < GRID_COUNT)) {
        return false;
    }

    for (uint8_t y = 0; y < GRID_ROWS; y++) {
        for (uint8_t x = 0; x < GRID_COLS; x++) {
            uint16_t srcX = ((uint32_t)x * MI48Decoder::WIDTH) / GRID_COLS;
            uint16_t srcY = ((uint32_t)y * MI48Decoder::HEIGHT) / GRID_ROWS;
            uint32_t srcIndex = ((uint32_t)srcY * MI48Decoder::WIDTH) + srcX;
            out[((uint16_t)y * GRID_COLS) + x] = rawToCelsius(pixels[srcIndex]);
        }
    }

    return true;
}

/* --------------------------------------------------------------------------
 * NV12 conversion
 * -------------------------------------------------------------------------- */

size_t MI48Renderer::nv12BufferSize(uint16_t dstWidth, uint16_t dstHeight)
{
    if ((dstWidth == 0) || (dstHeight == 0) || ((dstWidth & 1) != 0) || ((dstHeight & 1) != 0)) {
        return 0;
    }

    size_t yPlane = (size_t)dstWidth * dstHeight;
    size_t uvPlane = yPlane / 2;

    return yPlane + uvPlane;
}

bool MI48Renderer::toNV12(MI48Decoder &frame, uint8_t *dst, size_t dstSize, uint16_t dstWidth,
                                 uint16_t dstHeight, bool mirrorX)
{
    const uint16_t *pixels = frame.pixels();

    if ((pixels == nullptr) || (dst == nullptr)) {
        return false;
    }

    size_t required = nv12BufferSize(dstWidth, dstHeight);

    if ((required == 0) || (dstSize < required)) {
        return false;
    }

    const uint16_t minValue = frame.frameInfo().minRaw;
    const uint16_t maxValue = frame.frameInfo().maxRaw;

    const size_t yPlaneSize = (size_t)dstWidth * dstHeight;

    uint8_t *yPlane = dst;
    uint8_t *uvPlane = dst + yPlaneSize;

    /*
     * Y plane: nearest-neighbour resize.
     */
    for (uint16_t y = 0; y < dstHeight; y++) {

        uint16_t srcY = ((uint32_t)y * MI48Decoder::HEIGHT) / dstHeight;
        uint32_t rowOffset = (uint32_t)srcY * MI48Decoder::WIDTH;

        for (uint16_t x = 0; x < dstWidth; x++) {
            uint16_t mappedX = x;
            if (mirrorX) {
                mappedX = (uint16_t)(dstWidth - 1 - x);
            }
            uint16_t srcX = ((uint32_t)mappedX * MI48Decoder::WIDTH) / dstWidth;
            uint16_t raw = pixels[rowOffset + srcX];
            yPlane[((size_t)y * dstWidth) + x] = normalizeTo8(raw, minValue, maxValue);
        }
    }

    /*
     * Grayscale NV12:
     * neutral chroma for every 2x2 luma block.
     */
    memset(uvPlane, 128, yPlaneSize / 2);

    return true;
}

bool MI48Renderer::toNV12Colormap(MI48Decoder &frame, uint8_t *dst, size_t dstSize,
                                         uint16_t dstWidth, uint16_t dstHeight, const uint8_t *cmapY,
                                         const uint8_t *cmapU, const uint8_t *cmapV, bool mirrorX)
{
    const uint16_t *pixels = frame.pixels();

    if ((pixels == nullptr) || (dst == nullptr) || (cmapY == nullptr) || (cmapU == nullptr) || (cmapV == nullptr)) {
        return false;
    }

    size_t required = nv12BufferSize(dstWidth, dstHeight);

    if ((required == 0) || (dstSize < required)) {
        return false;
    }

    const uint16_t minValue = frame.frameInfo().minRaw;
    const uint16_t maxValue = frame.frameInfo().maxRaw;

    const size_t yPlaneSize = (size_t)dstWidth * dstHeight;

    uint8_t *yPlane = dst;
    uint8_t *uvPlane = dst + yPlaneSize;

    for (uint16_t y = 0; y < dstHeight; y++) {
        uint16_t srcY = ((uint32_t)y * MI48Decoder::HEIGHT) / dstHeight;
        uint32_t rowOffset = (uint32_t)srcY * MI48Decoder::WIDTH;

        for (uint16_t x = 0; x < dstWidth; x++) {
            uint16_t mappedX = x;
            if (mirrorX) {
                mappedX = (uint16_t)(dstWidth - 1 - x);
            }
            uint16_t srcX = ((uint32_t)mappedX * MI48Decoder::WIDTH) / dstWidth;
            uint16_t raw = pixels[rowOffset + srcX];
            uint8_t index = normalizeTo8(raw, minValue, maxValue);
            yPlane[((size_t)y * dstWidth) + x] = cmapY[index];

            /*
             * NV12 stores one interleaved U,V pair per 2x2 luma block.
             * Match the original implementation by taking the colour of
             * the top-left output pixel in that 2x2 block.
             */
            if (((y & 1) == 0) && ((x & 1) == 0)) {
                size_t uvIndex = ((size_t)(y / 2) * dstWidth) + x;
                uvPlane[uvIndex] = cmapU[index];
                uvPlane[uvIndex + 1] = cmapV[index];
            }
        }
    }

    return true;
}

/* --------------------------------------------------------------------------
 * Diagnostics
 * -------------------------------------------------------------------------- */

uint16_t MI48Renderer::pixelCRC16(MI48Decoder &frame)
{
    const uint16_t *pixels = frame.pixels();

    if (pixels == nullptr) {
        return 0;
    }

    /*
     * pixels contains native uint16_t values. AmebaPro2 is little-endian,
     * which matches the original incoming GFRA byte order.
     *
     * To make this independent of CPU byte order, rebuild the byte stream
     * logically rather than CRC'ing the uint16_t array directly.
     */
    uint16_t crc = 0xFFFF;

    for (uint32_t i = 0; i < MI48Decoder::PIXEL_COUNT; i++) {
        uint8_t low = (uint8_t)(pixels[i] & 0xFF);
        uint8_t high = (uint8_t)(pixels[i] >> 8);
        const uint8_t bytes[2] = {low, high};

        for (uint8_t b = 0; b < 2; b++) {
            crc ^= (uint16_t)bytes[b] << 8;
            for (uint8_t bit = 0; bit < 8; bit++) {
                if ((crc & 0x8000) != 0) {
                    crc = (uint16_t)((crc << 1) ^ 0x1021);
                } else {
                    crc = (uint16_t)(crc << 1);
                }
            }
        }
    }

    return crc;
}

/* --------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------- */
uint8_t MI48Renderer::normalizeTo8(uint16_t raw, uint16_t minValue, uint16_t maxValue)
{
    if (maxValue <= minValue) {
        return 0;
    }

    if (raw <= minValue) {
        return 0;
    }

    if (raw >= maxValue) {
        return 255;
    }

    uint32_t range = (uint32_t)maxValue - minValue;
    uint32_t value = (uint32_t)raw - minValue;

    return (uint8_t)((value * 255) / range);
}

uint16_t MI48Renderer::crc16CcittFalse(const uint8_t *data, size_t length)
{
    if (data == nullptr) {
        return 0;
    }

    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i] << 8;
        for (uint8_t bit = 0; bit < 8; bit++) {
            if ((crc & 0x8000) != 0) {
                crc = (uint16_t)((crc << 1) ^ 0x1021);
            } else {
                crc = (uint16_t)(crc << 1);
            }
        }
    }

    return crc;
}
