#include <string.h>
#include <common.h>
#include <app_init.h>
#include "app_thread.h"
#include "app_led.h"

int app_init(int argc, char *argv[])
{
	printf("%s\n", __func__);

	app_thread_init(true);
	app_led_init(true);

	return 0;
}
