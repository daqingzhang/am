#include <common.h>
#include <string.h>
#include <dc_motor.h>
#include <task_motor.h>

TaskHandle_t  MotorDriverHandler;
QueueHandle_t MotorDriverQueue;

void vMotorDriver(void *pvParameters)
{
	struct motor_dev *lmotor, *rmotor;
	TickType_t cycle = 50,cur;
	int mm = 100;

	dc_motor_register();
	lmotor = dc_motor_get(LMOTOR_ID);
	rmotor = dc_motor_get(RMOTOR_ID);

	for(;;) {
		motor_run_forward(lmotor,mm);
		motor_run_forward(rmotor,mm);

		cur = xTaskGetTickCount();
		vTaskDelayUntil(&cur,cycle);

		motor_run_backward(lmotor,mm);
		motor_run_backward(rmotor,mm);

		cur = xTaskGetTickCount();
		vTaskDelayUntil(&cur,cycle);
	}
}
