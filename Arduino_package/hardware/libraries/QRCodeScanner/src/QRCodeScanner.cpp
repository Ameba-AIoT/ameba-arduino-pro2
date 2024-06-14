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
    QRCodeScanner::ResultString = result_string1;
}

void QRCodeScanner::GetResultLength()
{
    QRCodeScanner::ResultLength = result_length1;
}
