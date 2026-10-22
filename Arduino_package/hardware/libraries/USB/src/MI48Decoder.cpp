#include "MI48Decoder.h"

#include <stdlib.h>
#include <string.h>

/* --------------------------------------------------------------------------
 * Construction / destruction
 * -------------------------------------------------------------------------- */

MI48Decoder::MI48Decoder() : _pixels(nullptr), _info{0, 0, 0, 0, 0, 0, 0}, _valid(false)
{
}

MI48Decoder::~MI48Decoder()
{
    end();
}

/* --------------------------------------------------------------------------
 * GFRA decoding
 * -------------------------------------------------------------------------- */

bool MI48Decoder::decode(const uint8_t *gfra, uint32_t length)
{
    if ((gfra == nullptr) || (length < GFRA_PAYLOAD_SIZE)) {

        _valid = false;
        return false;
    }

    if (_pixels == nullptr) {
        _pixels = (uint16_t *)malloc(PIXEL_COUNT * sizeof(uint16_t));

        if (_pixels == nullptr) {
            _valid = false;
            return false;
        }
    }

    /*
     * The original FrameHeader_CTX is packed and begins at byte 960.
     * Decode explicitly as little-endian rather than casting the buffer, so
     * this code does not depend on alignment.
     */
    const uint8_t *header = gfra + GFRA_HEADER_OFFSET;

    _info.frameCounter = readLE16(header + 0);
    _info.sensorVdd = readLE16(header + 2);
    _info.sensorDieTemp = readLE16(header + 4);
    _info.timestamp = readLE32(header + 6);
    _info.maxRaw = readLE16(header + 10);
    _info.minRaw = readLE16(header + 12);
    _info.headerCRC = readLE16(header + 14);

    const uint8_t *src = gfra + GFRA_PIXEL_OFFSET;

    for (uint32_t i = 0; i < PIXEL_COUNT; i++) {
        _pixels[i] = readLE16(src + (i * 2));
    }

    _valid = true;

    return true;
}

void MI48Decoder::end()
{
    if (_pixels != nullptr) {
        free(_pixels);
        _pixels = nullptr;
    }

    memset(&_info, 0, sizeof(_info));

    _valid = false;
}

bool MI48Decoder::valid()
{
    return _valid;
}

const MI48Decoder::FrameInfo &MI48Decoder::frameInfo()
{
    return _info;
}

const uint16_t *MI48Decoder::pixels()
{
    if (!_valid) {
        return nullptr;
    }

    return _pixels;
}

/* --------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------- */

uint16_t MI48Decoder::readLE16(const uint8_t *p)
{
    return (uint16_t)((uint16_t)p[0] | ((uint16_t)p[1] << 8));
}

uint32_t MI48Decoder::readLE32(const uint8_t *p)
{
    return ((uint32_t)p[0]) | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}
