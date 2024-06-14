#ifndef _QRCODE_SCANNER_H_
#define _QRCODE_SCANNER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "qrcode_drv.h"

#ifdef __cplusplus
}
#endif

class QRCodeScanner {
public:
    QRCodeScanner();
    ~QRCodeScanner();
    void StartScanning();
    void GetResultString();
    void GetResultLength();
    char* ResultString;
    unsigned int ResultLength;

private:
};



#endif
