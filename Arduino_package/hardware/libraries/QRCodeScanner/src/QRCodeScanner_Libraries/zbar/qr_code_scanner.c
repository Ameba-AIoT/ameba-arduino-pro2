/*************************************************************************************************/
// qr_code_scanner.c
/************************************************************************************************/

#include "qr_code_stdlib.h"
#include "qr_code_scanner.h"
#include "zbar.h"

qr_code_scanner_result qr_code_parsing(unsigned char *raw_data, unsigned int width, unsigned int height, int x_density, int y_density, char *string, unsigned int *len)
{
    qr_code_scanner_result ret = QR_CODE_FAIL_UNSPECIFIC_ERROR;
    zbar_image_scanner_t *scanner = NULL;
    zbar_image_t *image = NULL;
    const zbar_symbol_t *symbol = NULL;
    int n = 0;
    int scan_ret = 0;

    /*check output buffer is valid*/
    if (string == NULL) {
        qr_code_printf(QR_CODE_ERROR, "qr_code_parsing: output buffer is not valid \r\n");
        goto exit;
    }

    /* create a reader */
    scanner = zbar_image_scanner_create(x_density, y_density);

    if (scanner == NULL) {
        qr_code_printf(QR_CODE_ERROR, "qr_code_parsing: scanner is null \r\n");
        goto exit;
    }

    image = zbar_image_create();
    if (image == NULL) {
        qr_code_printf(QR_CODE_ERROR, "qr_code_parsing: image is null \r\n");
        goto exit;
    }

    qr_code_printf(QR_CODE_INFO, "qr_code_parsing \r\n");

    /* configure the reader */
    zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);

    /* wrap image data */
    zbar_image_set_format(image, *(int *)"Y800");
    zbar_image_set_size(image, width, height);
    zbar_image_set_data(image, raw_data, width * height, zbar_image_free_data);

    /* scan the image for barcodes */
    n = zbar_scan_image(scanner, image, &scan_ret);
    if (scan_ret == -1) {
        ret = QR_CODE_FAIL_NO_FINDER_CENTER;
    } else if (scan_ret == -2) {
        ret = QR_CODE_FAIL_DECODE_ERROR;
    }

    /* extract results */
    symbol = zbar_image_first_symbol(image);
    for (; symbol; symbol = zbar_symbol_next(symbol)) {
        /* do something useful with results */
        zbar_symbol_type_t typ = zbar_symbol_get_type(symbol);
        const char *data = zbar_symbol_get_data(symbol);
        unsigned int length = zbar_symbol_get_data_length(symbol);
        qr_code_printf(QR_CODE_INFO, "\r\ndecoded %s symbol \"%s\" length %d\r\n", zbar_get_symbol_name(typ), data, length);

        /*copy result*/
        if (length > QR_CODE_MAX_RESULT_LENGTH) {
            qr_code_printf(QR_CODE_ERROR, "qr_code_parsing: output buffer is not enough: length = %d \r\n", length);
            goto exit;
        } else {
            memcpy(string, data, length);
            *len = length;
            ret = QR_CODE_SUCCESS;
            break;
        }
    }

exit:
    /* clean up */
    if (image != NULL) {
        zbar_image_destroy(image);
    }
    if (scanner != NULL) {
        zbar_image_scanner_destroy(scanner);
    }
    return ret;
}
