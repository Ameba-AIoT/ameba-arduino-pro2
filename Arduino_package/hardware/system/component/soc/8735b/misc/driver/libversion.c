#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern int __libversion_start__[];
extern int __libversion_end__[];

void show_all_libversion(void)
{
	int cnt = ((uint32_t)__libversion_end__ - (uint32_t)__libversion_start__) / sizeof(int);

	for (int i = 0; i < cnt; i++) {
		char *(*get_version)(void) = (char *(*)(void)) __libversion_start__[i];
		printf("%s\n\r", get_version());
	}
}

void show_libversion(char *libname)
{
	int cnt = ((uint32_t)__libversion_end__ - (uint32_t)__libversion_start__) / sizeof(int);

	for (int i = 0; i < cnt; i++) {
		char *(*get_version)(void) = (char *(*)(void)) __libversion_start__[i];
		char *ver = get_version();
		if (strncmp(libname, ver, strlen(libname)) == 0) {
			printf("%s\n\r", ver);
			return;
		}
	}
}

#include "FreeRTOS.h"
#include "task.h"
#include "log_service.h"

void fLIBV(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	argc = parse_param(arg, argv);
	if (argc == 1) {
		show_all_libversion();
	} else if (argc == 2) {
		char *libname = argv[1];
		show_libversion(libname);
	}
}

log_item_t at_libversion_items[] = {
	{"LIBV", fLIBV, {NULL, NULL}},
};


void at_libversion_init(void)
{
	log_service_add_table(at_libversion_items, sizeof(at_libversion_items) / sizeof(at_libversion_items[0]));
}

void at_libversion_delay_init(void *dummy)
{
	(void)dummy;

	at_libversion_init();
	vTaskDelete(NULL);
}

__attribute__((constructor, used))
void libversion_init(void)
{
	xTaskCreate(at_libversion_delay_init, "init_libv", 256, NULL, 1, NULL);
}

