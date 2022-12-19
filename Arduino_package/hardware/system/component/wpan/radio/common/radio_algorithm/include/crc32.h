#ifndef CRC32_H
#define CRC32_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t rx_crc32(const uint32_t *buf, uint32_t size);
void crc32_encode(uint8_t *octet_in, int octet_len);


#ifdef  __cplusplus
}
#endif

#endif

