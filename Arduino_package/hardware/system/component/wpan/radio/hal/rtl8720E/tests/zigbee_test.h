/*
 * zigbee_test.h
 *
 *  Created on: 2021骞�11鏈�8鏃�
 *      Author: ran_wei
 */

#ifndef __ZIGBEE_TEST_H__
#define __ZIGBEE_TEST_H__

#include "stdio.h"
#include "ameba_common.h"
#define EXPECT(C) do{ \
						if (C) { \
							printf("%s %d PASS!\n", __FUNCTION__, __LINE__); \
						} else { \
							printf("%s %d FAIL!\n", __FUNCTION__, __LINE__); \
						} \
					} while(0);


#endif /*  */
