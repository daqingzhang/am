#ifndef __MOTOR_TASK_H__
#define __MOTOR_TASK_H__
#include <common.h>

#define DC_MTR_PRIO	 2
#define DC_MTR_STK_SIZE	 256
#define DC_MTR_QUE_DEPTH 10
#define DC_MTR_QUE_WIDTH 1

extern TaskHandle_t MotorDriverHandler;
extern QueueHandle_t MotorDriverQueue;

void vMotorDriver(void *pvParameters);

#endif
