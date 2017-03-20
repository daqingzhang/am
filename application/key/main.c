#include <common.h>
#include <key.h>
#include <key_task.h>

int main(int argc, const char *argv[])
{
	int r;

	// config KEY
	key_init(KEY2_ID | KEY3_ID | KEY4_ID);

	// KEY task construction
	r =xKeyTaskConstructor();
	if(r) {
		rprintf("%s, create tasks failed\n",__func__);
		return -1;
	}

	rprintf("Press any KEY\n");
	// call scheduler
	vTaskStartScheduler();

	for(;;);
	return 0;
}
