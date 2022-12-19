#ifndef __TENSOR_H__
#define __TENSOR_H__

#include "mmf2_module.h"
#include "module_vipnn.h"

float get_tensor_value(void *data, int idx, nn_tensor_format_t *fmt);
void *get_tensor_addr(void *data, int idx, nn_tensor_format_t *fmt);

#endif /* __TENSOR_H__ */