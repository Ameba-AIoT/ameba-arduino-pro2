#ifndef _MI48_PROTOCOL_H_
#define _MI48_PROTOCOL_H_

#include <Arduino.h>
#include <USBHostCDC.h>

/*
 * Meridian MI48 / MI16xx protocol layer over a generic USB CDC Host transport.
 *
 * USBHostCDC owns the Realtek USB Host / CDC-ACM driver.
 * MI48Protocol owns only the Meridian protocol:
 *   - RREG / WREG / RRSE commands
 *   - GFRA message framing/reassembly
 *   - MI16xx frame delivery
 *
 * No Realtek USB Host APIs are used in this class.
 */
class MI48Protocol {
public:
    /* MI16xx GFRA payload layout:
     *   [reserved 960][frame header 320][160x120 temperature words]
     */
    static constexpr uint32_t GFRA_PAYLOAD_SIZE = 39680;
    static constexpr uint32_t GFRA_RESERVED_BYTES = (3 * 160 * 2);                            // 960
    static constexpr uint32_t GFRA_HEADER_OFFSET = GFRA_RESERVED_BYTES;                       // 960
    static constexpr uint32_t GFRA_HEADER_BYTES = (160 * 2);                                  // 320
    static constexpr uint32_t GFRA_PIXEL_OFFSET = GFRA_RESERVED_BYTES + GFRA_HEADER_BYTES;    // 1280

    MI48Protocol();
    ~MI48Protocol();

    /*
     * Initialise the MI48 protocol layer on an already-started USBHostCDC.
     *
     * The function waits for CDC enumeration/setup, asserts DTR/RTS,
     * sends the Meridian setup sequence, and enables continuous GFRA capture.
     */
    bool begin(USBHostCDC &cdc, uint32_t connectTimeoutMs = 5000);

    /*
     * Release MI48 protocol buffers and reset parser state.
     * Does not stop/deinitialise USBHostCDC.
     */
    void end();

    /*
     * Drain bytes currently available from USBHostCDC and feed the
     * Meridian framing parser.
     *
     * Call frequently from loop().
     */
    void poll();

    bool ready();
    bool frameAvailable();

    /*
     * Return the latest complete GFRA payload.
     *
     * The returned pointer remains valid until the next complete frame
     * is accepted. Calling getFrame() marks the current frame as consumed.
     */
    const uint8_t *getFrame(uint32_t *payloadLen = nullptr);

    /*
     * Convenience accessors into the current GFRA payload.
     */
    const uint8_t *frameHeader();
    const uint8_t *pixelData();

private:
    static constexpr uint16_t MI16_CONTENTS_LENGTH = 0x9B08;
    static constexpr uint32_t MAX_MESSAGE_SIZE = 4 + (uint32_t)MI16_CONTENTS_LENGTH + 4;    // 39696

    static constexpr uint8_t FRAME_MODE_CONTINUOUS = 0x02;
    static constexpr uint8_t FRAME_MODE_WITH_HEADER = 0x00;

    enum ParserState : uint8_t {
        SEEK_DELIMITER = 0,
        READ_HEADER,
        READ_BODY
    };

    USBHostCDC *_cdc;

    uint8_t *_messageBuf;
    uint8_t *_frameBuf;

    uint32_t _messageUsed;
    uint32_t _messageExpected;
    uint8_t _delimiterPos;
    ParserState _parserState;

    bool _ready;
    bool _framePending;

    uint32_t _framesReceived;
    uint32_t _badMessages;

    static uint8_t hexDigit(uint8_t value);
    static bool parseHex4(const uint8_t *buf, uint16_t &value);
    static void putHex4(uint8_t *buf, uint16_t value);

    void resetParser();
    void pushByte(uint8_t byte);
    void handleCompleteMessage();

    bool sendMessage(const char *name, const uint8_t *data, uint16_t dataLen);
    bool sendRREG(uint8_t address);
    bool sendWREG(uint8_t address, uint8_t value);
    bool sendRRSESensorID();
};

#endif /* _MI48_PROTOCOL_H_ */
