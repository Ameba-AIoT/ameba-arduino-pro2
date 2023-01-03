/*
 * crc16.h
 *
 *  Created on: 2021年11月30日
 *      Author: ran_wei
 */

#ifndef __CRC16_H__
#define __CRC16_H__

#include "stdint.h"

uint16_t crc16_encode(uint8_t *octet_in, int32_t octet_len);
uint16_t crc16_decode(const uint8_t *octet_in, uint32_t octet_len);
void gen_crc16_table(void);
void crc16_encode_test(void);
void crc16_decode_test(void);

#endif /*  */
