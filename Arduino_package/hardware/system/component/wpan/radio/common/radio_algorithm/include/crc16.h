#ifndef CRC16_H
#define CRC16_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <stdint.h>

uint16_t crc16_encode(uint8_t *octet_in, int32_t octet_len);
uint16_t crc16_decode(const uint8_t *octet_in, uint32_t octet_len);
void gen_crc16_table(void);

#ifdef  __cplusplus
}
#endif

#endif

