/**
 * The IR cut only use one GPIO
 *     1: enable IR cut
 *     0: disable IR cut
 *
 * In normal case, the IR cut is always enabled.
 * In low light situation, IR led is turned on and IR cut should be disabled.
 */

#include "platform_opts.h"

#include "sensor_service.h"
#include "ir_cut.h"

#include "gpio_api.h"

static gpio_t gpio_ir_cut;

int ir_cut_init(void *param)
{
	gpio_init(&gpio_ir_cut, GPIO_IR_CUT_PIN);
	gpio_dir(&gpio_ir_cut, PIN_OUTPUT);
	gpio_mode(&gpio_ir_cut, PullNone);
	gpio_write(&gpio_ir_cut, 1);

	return 0;
}

int ir_cut_enable(int enable)
{
	gpio_write(&gpio_ir_cut, enable);
	return 0;
}