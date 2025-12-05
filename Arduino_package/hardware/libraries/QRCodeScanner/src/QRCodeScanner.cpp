#include <Arduino.h>
#include "QRCodeScanner.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "qrcode_drv.h"

#ifdef __cplusplus
}
#endif


QRCodeScanner::QRCodeScanner()
{
}

QRCodeScanner::~QRCodeScanner()
{
}

void QRCodeScanner::StartScanning()
{
    qr_code_scanning();
}

void QRCodeScanner::GetResultString()
{
    if (result_string1 == NULL) {
        QRCodeScanner::ResultString = NULL;
        return;
    }

    if (QRCodeScanner::ResultString != NULL) {
        free(QRCodeScanner::ResultString);
        QRCodeScanner::ResultString = NULL;
    }

    int len = strlen(result_string1);
    QRCodeScanner::ResultString = (char *)malloc(len + 1);

    memcpy(QRCodeScanner::ResultString, result_string1, len + 1);
    result_string1 = NULL;
}

void QRCodeScanner::GetResultLength()
{
    QRCodeScanner::ResultLength = result_length1;
    result_length1 = 0;
}
