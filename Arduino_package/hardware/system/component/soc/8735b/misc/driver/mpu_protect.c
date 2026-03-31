#include <stdint.h>
#include <stdio.h>
#include "mpu.h"


#if defined ( __GNUC__ )
extern uint8_t __ram_readonly_start__[];
extern uint8_t __ram_readonly_end__[];

extern uint8_t __eram_readonly_start__[];
extern uint8_t __eram_readonly_end__[];
#else
#error "NOT SUPPORT this compiler"
#endif


static mpu_region_config_t eram_rodata = {
	.xn = MPU_EXEC_ALLOW,
	.ap = MPU_PRIV_R,
	.sh = MPU_OUT_SHAREABLE,
	.attr_idx = 2,
};

static mpu_region_config_t ram_rodata = {
	.xn = MPU_EXEC_ALLOW,
	.ap = MPU_PRIV_R,
	.sh = MPU_OUT_SHAREABLE,
	.attr_idx = 2,
};

void mpu_rodata_protect_init(void)
{

	eram_rodata.region_base = (uint32_t)__eram_readonly_start__ & (~31);
	eram_rodata.region_limit = ((uint32_t)__eram_readonly_end__ - 1) & (~31);

	ram_rodata.region_base = (uint32_t)__ram_readonly_start__ & (~31);
	ram_rodata.region_limit = ((uint32_t)__ram_readonly_end__ - 1) & (~31);

	printf("RODATA protect %x %x, %x %x\n\r", eram_rodata.region_base, eram_rodata.region_limit, ram_rodata.region_base, ram_rodata.region_limit);

	mpu_region_cfg(6, &ram_rodata);
	mpu_region_cfg(7, &eram_rodata);
}


//-------------------------------------------------------------------------
// Test code
//-------------------------------------------------------------------------
#if 0
#include "FreeRTOS.h"
#include "task.h"

void mpu_broken_test(void *arg)
{
	(void)arg;

	vTaskDelay(5000);
	printf("Broken tester start\n\r");
	vTaskDelay(10);

	__eram_readonly_start__[100] = 1;
	__ram_readonly_start__[100] = 1;
}

__attribute__((constructor))
static void mpu_protect_tester(void)
{
	xTaskCreate(mpu_broken_test, "mpu_broken", 1024, NULL, 1, NULL);
}
#endif