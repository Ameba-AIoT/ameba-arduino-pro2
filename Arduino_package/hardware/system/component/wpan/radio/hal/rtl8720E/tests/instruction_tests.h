/*
 * instruction_tests.h
 *
 *  Created on: 2021年11月3日
 *      Author: ran_wei
 */

#ifndef __INSTRUCTION_TESTS_H__
#define __INSTRUCTION_TESTS_H__
#include "common.h"
#include <stdio.h>

#define TESTCASE(S) void tc_##S(void);
void tc_AE_MULA16_00(void);
void tc_AE_MUL16X4(void);
void testcases_run(void);

#endif /*  */
