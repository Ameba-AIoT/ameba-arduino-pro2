#include "MI48Protocol.h"

#include <string.h>


/* --------------------------------------------------------------------------
 * Construction / destruction
 * -------------------------------------------------------------------------- */

MI48Protocol::MI48Protocol():
    _cdc(nullptr),
    _messageBuf(nullptr),
    _frameBuf(nullptr),
    _messageUsed(0),
    _messageExpected(0),
    _delimiterPos(0),
    _parserState(SEEK_DELIMITER),
    _ready(false),
    _framePending(false),
    _framesReceived(0),
    _badMessages(0)
{}


MI48Protocol::~MI48Protocol()
{
    end();
}


/* --------------------------------------------------------------------------
 * Public API
 * -------------------------------------------------------------------------- */

bool MI48Protocol::begin(USBHostCDC &cdc, uint32_t connectTimeoutMs)
{
    end();

    _cdc = &cdc;

    _messageBuf = new uint8_t[MAX_MESSAGE_SIZE];
    _frameBuf = new uint8_t[GFRA_PAYLOAD_SIZE];

    if ((_messageBuf == nullptr) || (_frameBuf == nullptr)) {
        end();
        return false;
    }

    resetParser();

    _framePending = false;
    _framesReceived = 0;
    _badMessages = 0;

    /*
     * USBHostCDC::begin() should already have been called by the sketch.
     * Wait until CDC enumeration/setup completes.
     */
    uint32_t start = millis();

    while (!_cdc->connected()) {
        if ((uint32_t)(millis() - start) >= connectTimeoutMs) {
            end();
            return false;
        }

        delay(10);
    }

    /*
     * USBHostCDC starts BULK-IN lazily on the first available()/read().
     * Arm RX before sending Meridian commands, matching the original C driver
     * which started reception before RREG/RRSE/WREG setup.
     */
    (void)_cdc->available();

    /*
     * Same control-line state used by the original Realtek implementation:
     * bit0 = DTR, bit1 = RTS.
     */
    // (void)_cdc->setControlLineState(true, true);
    if (!_cdc->setLineCoding(115200)) {
        printf("MI48: failed to set line coding\r\n");
        end();
        return false;
    }

    if (!_cdc->setControlLineState(true, true)) {
        printf("MI48: failed to set DTR/RTS\r\n");
        end();
        return false;
    }

    delay(100);

    /*
     * Meridian setup sequence from the working C implementation:
     *
     *   RREG B6
     *   RRSE E0..E6,FF
     *   WREG 31 = 00
     *   WREG B1 = continuous + header
     */
    if (!sendRREG(0xB6)) {
        end();
        return false;
    }

    delay(50);

    if (!sendRRSESensorID()) {
        end();
        return false;
    }

    delay(50);

    if (!sendWREG(0x31, 0x00)) {
        end();
        return false;
    }

    delay(50);

    if (!sendWREG(0xB1, FRAME_MODE_CONTINUOUS | FRAME_MODE_WITH_HEADER)) {
        end();
        return false;
    }

    _ready = true;

    return true;
}


void MI48Protocol::end()
{
    _ready = false;
    _framePending = false;

    if (_messageBuf != nullptr) {
        delete[] _messageBuf;
        _messageBuf = nullptr;
    }

    if (_frameBuf != nullptr) {
        delete[] _frameBuf;
        _frameBuf = nullptr;
    }

    _cdc = nullptr;

    resetParser();
}


void MI48Protocol::poll()
{
    if (!_ready || (_cdc == nullptr)) {
        return;
    }

    /*
     * Drain all bytes currently buffered by USBHostCDC.
     *
     * IMPORTANT:
     * MI48 GFRA messages are about 39.7 KB, so call poll() frequently.
     * If USBHostCDC::droppedBytes() becomes non-zero, enlarge the generic
     * CDC RX ring buffer or add a direct RX-consumer callback later.
     */
    while (_cdc->available() > 0) {
        int value = _cdc->read();

        if (value < 0) {
            break;
        }

        pushByte((uint8_t)value);
    }
}


bool MI48Protocol::ready()
{
    return _ready;
}


bool MI48Protocol::frameAvailable()
{
    return _framePending;
}


const uint8_t *MI48Protocol::getFrame(uint32_t *payloadLen)
{
    if (!_framePending || (_frameBuf == nullptr)) {
        return nullptr;
    }

    if (payloadLen != nullptr) {
        *payloadLen = GFRA_PAYLOAD_SIZE;
    }

    /*
     * Mark current frame consumed so the next GFRA message may replace it.
     */
    _framePending = false;

    return _frameBuf;
}


const uint8_t *MI48Protocol::frameHeader()
{
    if (_frameBuf == nullptr) {
        return nullptr;
    }

    return _frameBuf + GFRA_HEADER_OFFSET;
}


const uint8_t *MI48Protocol::pixelData()
{
    if (_frameBuf == nullptr) {
        return nullptr;
    }

    return _frameBuf + GFRA_PIXEL_OFFSET;
}


/* --------------------------------------------------------------------------
 * Meridian framing helpers
 * -------------------------------------------------------------------------- */

uint8_t MI48Protocol::hexDigit(uint8_t value)
{
    value &= 0x0F;

    if (value < 10) {
        return (uint8_t)('0' + value);
    }

    return (uint8_t)('A' + value - 10);
}


bool MI48Protocol::parseHex4(const uint8_t *buf, uint16_t &value)
{
    if (buf == nullptr) {
        return false;
    }

    uint16_t result = 0;

    for (int i = 0; i < 4; i++) {
        uint8_t c = buf[i];
        uint8_t nibble;

        if ((c >= '0') && (c <= '9')) {
            nibble = (uint8_t)(c - '0');
        } else if ((c >= 'A') && (c <= 'F')) {
            nibble = (uint8_t)(c - 'A' + 10);
        } else if ((c >= 'a') && (c <= 'f')) {
            nibble = (uint8_t)(c - 'a' + 10);
        } else {
            return false;
        }

        result = (uint16_t)((result << 4) | nibble);
    }

    value = result;

    return true;
}


void MI48Protocol::putHex4(uint8_t *buf, uint16_t value)
{
    buf[0] = hexDigit((uint8_t)(value >> 12));
    buf[1] = hexDigit((uint8_t)(value >> 8));
    buf[2] = hexDigit((uint8_t)(value >> 4));
    buf[3] = hexDigit((uint8_t)value);
}


/* --------------------------------------------------------------------------
 * Meridian TX commands
 * -------------------------------------------------------------------------- */

bool MI48Protocol::sendMessage(const char *name, const uint8_t *data, uint16_t dataLen)
{
    if ((_cdc == nullptr) || (name == nullptr)) {
        return false;
    }

    /*
     * Original implementation limits command payloads to <= 48 bytes:
     *
     *   "   #" + length + 4-char name + data + checksum
     */
    if (dataLen > 48) {
        return false;
    }

    uint8_t tx[64];

    uint16_t contentsLen = (uint16_t)(8 + dataLen);
    uint32_t totalLen = 4 + (uint32_t)contentsLen + 4;

    if (totalLen > sizeof(tx)) {
        return false;
    }

    tx[0] = ' ';
    tx[1] = ' ';
    tx[2] = ' ';
    tx[3] = '#';

    putHex4(&tx[4], contentsLen);

    tx[8] = (uint8_t)name[0];
    tx[9] = (uint8_t)name[1];
    tx[10] = (uint8_t)name[2];
    tx[11] = (uint8_t)name[3];

    if ((dataLen > 0) && (data != nullptr)) {
        memcpy(&tx[12], data, dataLen);
    }

    uint16_t checksum = 0;

    for (uint32_t i = 4; i < (4 + (uint32_t)contentsLen); i++) {
        checksum = (uint16_t)(checksum + tx[i]);
    }

    putHex4(&tx[4 + contentsLen], checksum);

    return (_cdc->write(tx, totalLen) == totalLen);
}


bool MI48Protocol::sendRREG(uint8_t address)
{
    uint8_t data[2];

    data[0] = hexDigit((uint8_t)(address >> 4));
    data[1] = hexDigit(address);

    return sendMessage("RREG", data, sizeof(data));
}


bool MI48Protocol::sendWREG(uint8_t address, uint8_t value)
{
    uint8_t data[4];

    data[0] = hexDigit((uint8_t)(address >> 4));
    data[1] = hexDigit(address);
    data[2] = hexDigit((uint8_t)(value >> 4));
    data[3] = hexDigit(value);

    return sendMessage("WREG", data, sizeof(data));
}


bool MI48Protocol::sendRRSESensorID()
{
    static const uint8_t data[] = {'E', '0', 'E', '1', 'E', '2', 'E', '3', 'E', '4', 'E', '5', 'E', '6', 'F', 'F'};

    return sendMessage("RRSE", data, sizeof(data));
}


/* --------------------------------------------------------------------------
 * GFRA parser
 * -------------------------------------------------------------------------- */

void MI48Protocol::resetParser()
{
    _messageUsed = 0;
    _messageExpected = 0;
    _delimiterPos = 0;
    _parserState = SEEK_DELIMITER;
}


void MI48Protocol::pushByte(uint8_t byte)
{
    static const uint8_t delimiter[] = {' ', ' ', ' ', '#'};

    if ((_messageBuf == nullptr) || (_frameBuf == nullptr)) {
        return;
    }

    if (_parserState == SEEK_DELIMITER) {
        if (byte == delimiter[_delimiterPos]) {
            _delimiterPos++;

            if (_delimiterPos == sizeof(delimiter)) {
                memcpy(_messageBuf, delimiter, sizeof(delimiter));

                _messageUsed = sizeof(delimiter);
                _parserState = READ_HEADER;
                _delimiterPos = 0;
            }
        } else {
            /*
             * Preserve the first space as a possible start of the next
             * "   #" delimiter.
             */
            _delimiterPos = 0;
            if (byte == (uint8_t)' ') {
                _delimiterPos = 1;
            }
        }

        return;
    }

    if (_messageUsed >= MAX_MESSAGE_SIZE) {
        _badMessages++;
        resetParser();
        return;
    }

    _messageBuf[_messageUsed++] = byte;

    if (_parserState == READ_HEADER) {
        if (_messageUsed < 12) {
            return;
        }

        uint16_t contentsLength = 0;

        if (!parseHex4(&_messageBuf[4], contentsLength)) {
            _badMessages++;
            resetParser();
            return;
        }

        _messageExpected = 4 + (uint32_t)contentsLength + 4;

        if ((contentsLength < 8) || (_messageExpected > MAX_MESSAGE_SIZE)) {

            _badMessages++;
            resetParser();
            return;
        }

        _parserState = READ_BODY;
    }

    if ((_parserState == READ_BODY) && (_messageUsed == _messageExpected)) {

        handleCompleteMessage();
        resetParser();
    }
}


void MI48Protocol::handleCompleteMessage()
{
    /*
     * Header layout after delimiter:
     *
     * 0..3   "   #"
     * 4..7   length
     * 8..11  message name
     * 12..   payload
     */
    if ((_messageBuf[8] != 'G') || (_messageBuf[9] != 'F') || (_messageBuf[10] != 'R') || (_messageBuf[11] != 'A')) {

        return;
    }

    /*
     * Do not overwrite an unconsumed frame.
     *
     * This matches the original C implementation, which sets a
     * frame-pending flag until the application accepts the frame.
     */
    if (_framePending) {
        return;
    }

    /*
     * For the MI16xx GFRA frame used by the original driver,
     * the complete message must contain at least the expected payload.
     */
    if (_messageUsed < (12 + GFRA_PAYLOAD_SIZE)) {
        _badMessages++;
        return;
    }

    memcpy(_frameBuf, &_messageBuf[12], GFRA_PAYLOAD_SIZE);

    _framePending = true;
    _framesReceived++;
}
