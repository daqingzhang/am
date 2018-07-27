#include <common.h>
#include <task_motor.h>

int main(int argc, const char *argv[])
{
	int retval;

	MotorDriverQueue = xQueueCreate(DC_MTR_QUE_DEPTH,DC_MTR_QUE_WIDTH);

	retval = xTaskCreate(vMotorDriver, "xMotorDriver",
			DC_MTR_STK_SIZE, NULL,DC_MTR_PRIO,&MotorDriverHandler);
	if(retval != pdPASS) {
		rprintf("create task failed, %d\n",retval);
		goto loop;
	}
	vTaskStartScheduler();
loop:
	for(;;);
	return 0;
}
