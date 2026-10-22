#ifndef _MI48_DECODER_H_
#define _MI48_DECODER_H_

#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>

/*
 * MI48Decoder
 *
 * Transport-independent decoder for the Meridian MI16xx GFRA payload.
 *
 * This class does NOT know anything about USB, CDC, RTSP, JPEG, MMF or VOE.
 * It ONLY turns the raw GFRA bytes into the 160x120 thermal pixels and the
 * frame header. Temperature conversion and NV12 rendering live in
 * MI48Renderer.
 */
class MI48Decoder {
public:
    static constexpr uint16_t WIDTH = 160;
    static constexpr uint16_t HEIGHT = 120;
    static constexpr uint32_t PIXEL_COUNT = (uint32_t)WIDTH * (uint32_t)HEIGHT;

    /*
     * MI16xx GFRA payload layout:
     *
     *   [reserved 960 bytes]
     *   [frame/header area 320 bytes]
     *   [160x120 pixels, uint16 little-endian]
     *
     * Total payload = 39680 bytes.
     */
    static constexpr uint32_t GFRA_PAYLOAD_SIZE = 39680;
    static constexpr uint32_t GFRA_RESERVED_BYTES = (3 * WIDTH * 2);                          // 960
    static constexpr uint32_t GFRA_HEADER_OFFSET = GFRA_RESERVED_BYTES;                       // 960
    static constexpr uint32_t GFRA_HEADER_BYTES = (WIDTH * 2);                                // 320
    static constexpr uint32_t GFRA_PIXEL_OFFSET = GFRA_RESERVED_BYTES + GFRA_HEADER_BYTES;    // 1280

    struct FrameInfo {
        uint16_t frameCounter;
        uint16_t sensorVdd;
        uint16_t sensorDieTemp;
        uint32_t timestamp;
        uint16_t maxRaw;
        uint16_t minRaw;
        uint16_t headerCRC;
    };

    MI48Decoder();
    ~MI48Decoder();

    /*
     * Decode one complete GFRA payload.
     *
     * The pixel data is copied into this object, so the caller may reuse or
     * overwrite the original GFRA buffer after decode() returns.
     */
    bool decode(const uint8_t *gfra, uint32_t length);

    /*
     * Release the internal 160x120 pixel buffer.
     */
    void end();

    bool valid();

    const FrameInfo &frameInfo();

    const uint16_t *pixels();

private:
    uint16_t *_pixels;
    FrameInfo _info;
    bool _valid;

    static uint16_t readLE16(const uint8_t *p);
    static uint32_t readLE32(const uint8_t *p);
};

#endif /* _MI48_DECODER_H_ */
