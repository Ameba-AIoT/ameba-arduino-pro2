/**************************************************************************//**
 * @file     app_start.c
 * @brief    The application entry function implementation. It initial the
 *           application functions.
 * @version  V1.00
 * @date     2016-05-27
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#undef ROM_REGION

#include "cmsis.h"
#include "partition_rtl8735b.h"
#include "hal_trng_sec.h"

extern void shell_cmd_init(void);
extern void shell_task(void);

//void app_start (void) __attribute__ ((noreturn));

#if !defined ( __CC_ARM ) && !(defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* ARM Compiler 4/5 */
// for __CC_ARM compiler, it will add a __ARM_use_no_argv symbol for every main() function, that cause linker report error
/// default main
__weak int main(void)
{
	while (1) {
		shell_task();
	}
	return 0;
}
#endif

#if defined ( __ICCARM__ )
extern void *__iar_cstart_call_ctors(void *ptr);
extern void __iar_data_init3(void);

#endif

#if defined(__GNUC__)
__weak void _init(void)
{

}
void __libc_init_array(void);
#endif
//#define TM_TTFF_MEASURE
#if defined(TM_TTFF_MEASURE)
#define dbg_printf(...)                     do {  } while(0)
#endif

#if defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)

// This data type should be same with ns_region_t defined in ram_start.c
/// The data structure to record a NS region configuration
typedef struct ns_region_s {
	uint32_t start_addr;   /*!< the start address of NS region */
	uint32_t end_addr;   /*!< the end address of NS region */
	uint32_t is_valid;   /*!< indicates the valid state of this record */
} ns_region_t, *pns_region_t;

/**
 *  @brief To setup SAUs to partition the system memory as Secure memory and Non-secure memory.
 *
 *  @returns void
 */
void sau_setup(ns_region_t *ns_region)
{
#if SAU_INIT_REGION0
	dbg_printf("SAU 0: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START0, SAU_INIT_END0, SAU_INIT_NSC0 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC0 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU0
		bus_idau_setup(0, SAU_INIT_START0, SAU_INIT_END0);
		ns_region[0].start_addr = SAU_INIT_START0;
		ns_region[0].end_addr = SAU_INIT_END0;
		ns_region[0].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION1
	dbg_printf("SAU 1: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START1, SAU_INIT_END1, SAU_INIT_NSC1 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC1 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU1
		bus_idau_setup(1, SAU_INIT_START1, SAU_INIT_END1);
		ns_region[1].start_addr = SAU_INIT_START1;
		ns_region[1].end_addr = SAU_INIT_END1;
		ns_region[1].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION2
	dbg_printf("SAU 2: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START2, SAU_INIT_END2, SAU_INIT_NSC2 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC2 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU2
		bus_idau_setup(2, SAU_INIT_START2, SAU_INIT_END2);
		ns_region[2].start_addr = SAU_INIT_START2;
		ns_region[2].end_addr = SAU_INIT_END2;
		ns_region[2].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION3
	dbg_printf("SAU 3: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START3, SAU_INIT_END3, SAU_INIT_NSC3 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC3 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU3
		bus_idau_setup(3, SAU_INIT_START3, SAU_INIT_END3);
		ns_region[3].start_addr = SAU_INIT_START3;
		ns_region[3].end_addr = SAU_INIT_END3;
		ns_region[3].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION4
	dbg_printf("SAU 4: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START4, SAU_INIT_END4, SAU_INIT_NSC4 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC4 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU4
		bus_idau_setup(4, SAU_INIT_START4, SAU_INIT_END4);
		ns_region[4].start_addr = SAU_INIT_START4;
		ns_region[4].end_addr = SAU_INIT_END4;
		ns_region[4].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION5
	dbg_printf("SAU 5: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START5, SAU_INIT_END5, SAU_INIT_NSC5 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC5 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU5
		bus_idau_setup(5, SAU_INIT_START5, SAU_INIT_END5);
		ns_region[5].start_addr = SAU_INIT_START5;
		ns_region[5].end_addr = SAU_INIT_END5;
		ns_region[5].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION6
	dbg_printf("SAU 6: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START6, SAU_INIT_END6, SAU_INIT_NSC6 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC6 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU6
		bus_idau_setup(6, SAU_INIT_START6, SAU_INIT_END6);
		ns_region[6].start_addr = SAU_INIT_START6;
		ns_region[6].end_addr = SAU_INIT_END6;
		ns_region[6].is_valid = 1;
	}
#endif
#if SAU_INIT_REGION7
	dbg_printf("SAU 7: 0x%08x ~ 0x%08x as %s\r\n", SAU_INIT_START7, SAU_INIT_END7, SAU_INIT_NSC7 ? "Secure(NSC)" : "Non-Secure");
	if (SAU_INIT_NSC7 == 0) {
		// Set Bus IDAU to match the SAU setting, use IDAU7
		bus_idau_setup(7, SAU_INIT_START7, SAU_INIT_END7);
		ns_region[7].start_addr = SAU_INIT_START7;
		ns_region[7].end_addr = SAU_INIT_END7;
		ns_region[7].is_valid = 1;
	}
#endif
	TZ_SAU_Setup();

#if CTRL_DUMP_IP_SEC_CFG_EN
	// Show the Non-secure interrupt vectors info
	dump_nvic_int_sec_info();
	//dbg_printf("ITNS[0] = 0x%08x\r\n",  NVIC->ITNS[0]);
	//dbg_printf("ITNS[1] = 0x%08x\r\n",  NVIC->ITNS[1]);
#endif
}

static void app_gen_random_seed(void)
{
	uint32_t seed = 0;

	hal_trng_sec_init();
	seed = hal_trng_sec_get_rand();
	hal_trng_sec_deinit();
	srand(seed);
}

void NS_ENTRY app_gen_random_seed_nsc(void)
{
	app_gen_random_seed();
}

#endif

void app_start(void)
{
	dbg_printf("Build @ %s, %s\r\n", __TIME__, __DATE__);

#if defined (__ICCARM__)
	// __iar_data_init3 replaced by __iar_cstart_call_ctors, just do c++ constructor
	__iar_cstart_call_ctors(NULL);
#elif defined(__GNUC__)
	__libc_init_array();

#endif
	shell_cmd_init();
	main();

#if defined ( __ICCARM__ )
	// for compile issue, If user never call this function, Liking fail
	__iar_data_init3();
#endif
}


