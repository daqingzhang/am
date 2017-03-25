#include <common.h>
#include <key.h>
#include <key_task.h>

int main(int argc, const char *argv[])
{
	int r;

	// config KEY
	r = key_register();
	if(r) {
		rprintf("register key device failed, %d\n",r);
		goto loop;
	}
	// KEY task construction
	r =xKeyTaskConstructor();
	if(r) {
		rprintf("%s, create tasks failed\n",__func__);
		return -1;
	}

	rprintf("Press any KEY\n");
	// call scheduler
	vTaskStartScheduler();
loop:
	for(;;);
	return 0;
}
