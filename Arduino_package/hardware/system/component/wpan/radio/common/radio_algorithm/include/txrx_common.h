#ifndef TXRX_COMMON_H
#define TXRX_COMMON_H

#include <stdint.h>

#define FS_4M 4
#define SFD_LEN 8
#define PREAMBLE_LEN 32
#define FRM_LEN_SIZE 7
#define SYMBOL_GRP 4
#define CHIP_MAP_LEN 32
#define CHIP_MAP_GOUP 16
#define CHIP_EXPAN 8
#define CHIP_BUF_SIZE 64

extern int32_t g_sym_shape_real[16 * 64];
extern int32_t g_sym_shape_imag[16 * 64];
extern uint8_t g_chip_map[CHIP_MAP_GOUP][CHIP_MAP_LEN];
extern int32_t g_chip_ideal_im_odd[16][16];
extern int32_t g_chip_ideal_re_even[16][16];
void get_symbol_shape(void);

#endif