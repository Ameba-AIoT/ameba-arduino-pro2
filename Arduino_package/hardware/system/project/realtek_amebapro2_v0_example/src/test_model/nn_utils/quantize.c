//------------------------------------------------------------------------------
// QUANTIZE
//------------------------------------------------------------------------------
#include <stdint.h>
#include "quantize.h"

float u8_to_f(uint8_t val, uint8_t zero_p, float scale)
{
	return  scale * ((float)val - (float)zero_p);
}

float s8_to_f(int8_t val, int q)
{
	if(q>0){
		return (float)val / (float)(1 << q);
	}
	else{
		return (float)val * (float)(1 << -q);
	}
}

float s16_to_f(int16_t val, int q)
{
	if(q>0){
		return (float)val / (float)(1 << q);
	}
	else{
		return (float)val * (float)(1 << -q);
	}
}

float bf16_to_f(__fp16 val)
{
	return (float)val;
}

float q2f(void *val, nn_tensor_format_t *fmt)
{
	switch (fmt->type) {
	case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
		if (fmt->buf_type == VIP_BUFFER_FORMAT_INT16) {
			// s16
			return s16_to_f(*(int16_t *)val, fmt->fix_point_pos);
		} else if (fmt->buf_type == VIP_BUFFER_FORMAT_INT8) {
			// s8
			return s8_to_f(*(int8_t *)val, fmt->fix_point_pos);
		}
	case VIP_BUFFER_QUANTIZE_TF_ASYMM:
		if (fmt->buf_type == VIP_BUFFER_FORMAT_UINT8) {
			// u8
			return u8_to_f(*(uint8_t *)val, fmt->zero_point, fmt->scale);
		}
	case VIP_BUFFER_QUANTIZE_NONE:
		if (fmt->buf_type == VIP_BUFFER_FORMAT_FP16) {
			// bf16
			return bf16_to_f(*(__fp16 *)val);
		} else if (fmt->buf_type == VIP_BUFFER_FORMAT_FP32) {
			// fp32
			return *(float *)val;
		}
	default:
		break;
	}

	return bf16_to_f(*(__fp16 *)val);
}

uint8_t f_to_u8(float val, uint8_t zero_p, float scale)
{
	return (uint8_t)(val / scale) + zero_p;
}

int8_t f_to_s8(float val, int q)
{
	if(q>0){
		return (int8_t)(val * (1 << q));
	}
	else{
		return (int8_t)(val / (1 << -q));
	}
}

int16_t f_to_s16(float val, int q)
{
	if(q>0){
		return (int16_t)(val * (1 << q));
	}
	else{
		return (int16_t)(val / (1 << -q));
	}
}

__fp16 f_to_bf16(float val)
{
	return (__fp16)val;
}

