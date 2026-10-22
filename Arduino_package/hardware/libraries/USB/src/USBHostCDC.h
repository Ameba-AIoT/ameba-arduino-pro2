#ifndef _USBHOSTCDC_H_
#define _USBHOSTCDC_H_

#include <Arduino.h>
// #include <USBV1Stack.h>

class USBHostCDC: public Stream {
public:
    USBHostCDC();

    bool begin();
    void end();

    bool connected();

    int available() override;
    int read() override;
    size_t read(uint8_t *buffer, size_t size);
    int peek() override;
    void flush() override;

    size_t write(uint8_t data) override;
    size_t write(const uint8_t *buffer, size_t size) override;
    using Print::write;

    bool setControlLineState(bool dtr, bool rts);

    /*
     * Send SET_LINE_CODING (baud/parity/data-bits) to the device.
     * Many CDC-ACM virtual-COM (e.g. Nuvoton) devices will not open their
     * BULK data endpoint until this request completes.
     */
    bool setLineCoding(uint32_t baud = 115200);

    uint32_t rxBytes();
    uint32_t txBytes();
    uint32_t droppedBytes();

private:
    bool ensureReceiveStarted();
};

#endif /* _USBHOSTCDC_H_ */
