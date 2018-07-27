#include <common.h>
#include <led.h>
#include <led_task.h>

int main(int argc, const char *argv[])
{
	int r;

	led_init(LED1|LED2|LED3);

	// LED task construction
	r = xLedTaskConstructor();
	if(r) {
		rprintf("%s, xLedTaskConstructor failed\n",__func__);
		return -1;
	}

	// call scheduler
	vTaskStartScheduler();

	for(;;);
	return 0;
}
