#ifndef __TENSOR_H__
#define __TENSOR_H__

#if !defined(PC_SIMULATION)
#include "mmf2_module.h"
#else
#include <stdbool.h>
#endif
#include "module_vipnn.h"

int get_element_size(nn_tensor_format_t *fmt);
float get_tensor_value(void *data, int idx, nn_tensor_format_t *fmt);
void *get_tensor_addr(void *data, int idx, nn_tensor_format_t *fmt);

#endif /* __TENSOR_H__ */