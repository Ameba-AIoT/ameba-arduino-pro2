#ifndef EXAMPLE_RMESH_H
#define EXAMPLE_RMESH_H
#include "rmesh.h"

#define GPIO_BUTTON_PIN	_PA_12

#if PING_TP_TEST
struct test_data {
	u16 buf_size;
	u32 time;
	u32 report_interval;
	u32   interval;
};
#endif

extern void rmesh_free_node_test();

#endif /* EXAMPLE_RMESH_H */

