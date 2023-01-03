/*
 * pxp_tests.h
 *
 *  Created on: 2021骞�12鏈�31鏃�
 *      Author: ran_wei
 */

#ifndef _PXP_TESTS_
#define _PXP_TESTS_

#include "ameba_common.h"

#ifndef BIT
#define BIT(__n)       (1U<<(__n))
#endif

#define BIT_KM4_SIMULATION_END          BIT(17) /* simulation end */


extern char g_test_buf[];
void debug_print_tests(void);
void zgb_mem_latency(void);
void debug_cache_info(void);
void debug_cache_tests(void);
void xt_cache_example(void);

#endif /*  */
