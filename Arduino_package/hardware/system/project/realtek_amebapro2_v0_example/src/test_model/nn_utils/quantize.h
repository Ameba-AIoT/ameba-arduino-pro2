#ifndef __QUANTIZATION_H__
#define __QUANTIZATION_H__

#if !defined(PC_SIMULATION)
#include "mmf2_module.h"
#else
#include <stdbool.h>
#endif
#include "module_vipnn.h"

float u8_to_f(uint8_t val, uint8_t zero_p, float scale);
float s8_to_f(int8_t val, int q);
float s16_to_f(int16_t val, int q);
float bf16_to_f(__fp16 val);
float q2f(void *val, nn_tensor_format_t *fmt);
uint8_t f_to_u8(float val, uint8_t zero_p, float scale);
int8_t f_to_s8(float val, int q);
int16_t f_to_s16(float val, int q);
__fp16 f_to_bf16(float val);

#endif /* __QUANTIZATION_H__ */