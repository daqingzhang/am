#include <string.h>
#include <common.h>
#include <app_init.h>
#include "app_thread.h"
#include "app_led.h"
#include <services.h>

int app_init(int argc, char *argv[])
{
	printf("%s\n", __func__);

	services_init();

	app_thread_init(true);
	app_led_init(true);

	return 0;
}
