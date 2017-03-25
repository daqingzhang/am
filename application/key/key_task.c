#include <common.h>
#include <key.h>
#include <key_task.h>

TaskHandle_t KeyGetHandle = NULL;
TaskHandle_t KeyPrcHandle = NULL;
TaskHandle_t KeyWthHandle = NULL;
QueueHandle_t KeyPrcQueue = NULL;
SemaphoreHandle_t KeyPresSema = NULL;

void vKeyWatcherTask(void *pvParameters)
{
	BaseType_t r;

	for(;;) {
		r = xSemaphoreTake(KeyPresSema,portMAX_DELAY);

		vTaskSuspendAll();
		if(r == pdTRUE) {
			rprintf("%s, key sema taken\n",__func__);
		} else {
			rprintf("%s, key sema taken failed\n",__func__);
		}
		xTaskResumeAll();
	}
}

void vKeyGetTask(void *pvParameters)
{
	TickType_t tick,cnt = 0;
	u32 k;
	int val,i,id[] = {KEY2_ID,KEY3_ID,KEY4_ID};
	struct sensor_dev *key[KEY_DEV_NR];

	for(i = 0;i < KEY_DEV_NR;i++)
		key[i] = key_get(id[i]);

	for(;;) {
		tick = xTaskGetTickCount();
		vTaskDelayUntil(&tick,2);

		k = 0;
		for(i = 0;i < KEY_DEV_NR;i++) {
			sensor_read(key[i], &val);
			if(val)
				k |= (1 << i);
		}
		if(k == 0) {
			cnt = 0;
			continue;
		}
		cnt++;
		if(cnt < 5)
			continue;
		cnt = 0;

		vTaskSuspendAll();
		rprintf("%s, %x\n",__func__,k);
		xTaskResumeAll();

		xQueueSend(KeyPrcQueue,(void *)&k,10);
	}
}

static void vKeyPrcFunction(u32 key)
{
	BaseType_t r;

	vTaskSuspendAll();
	rprintf("%s, process key %x\n",__func__,key);
	xTaskResumeAll();
	//speaker_beep(100,100);
	r = xSemaphoreGive(KeyPresSema);
	if(r != pdTRUE) {
		vMsgPrint("vKeyPrcFunction, give a sema failed\n",'s');
	}
}

void vKeyPrcTask(void *pvParameters)
{
	u32 k;
	BaseType_t r;

	for(;;) {
		r = xQueueReceive(KeyPrcQueue,(void *)&k,portMAX_DELAY);
		if(r != pdPASS)
			continue;
		switch(k) {
		case 0x01:
			// TODO: add process code here
			vKeyPrcFunction(k);
			break;
		case 0x02:
			// TODO: add process code here
			vKeyPrcFunction(k);
			break;
		case 0x04:
			// TODO: add process code here
			vKeyPrcFunction(k);
			break;
		default:
			break;
		}
	}
}

int xKeyTaskConstructor(void)
{
	BaseType_t r;
	int depth = 10,width = 4,stk = 256;

	rprintf("%s, depth = %d, width = %d, stk = %d\n",__func__,depth,width,stk);
	// create queue
	// queue width is the number of bytes, key value is a 32 bits number,
	// so the width is 4.
	KeyPrcQueue = xQueueCreate(depth,width);
	if(KeyPrcQueue == 0) {
		rprintf("%s, create KeyPrcQueue failed\n",__func__);
		return -1;
	}
	KeyPresSema = xSemaphoreCreateBinary();
	if(KeyPresSema == NULL) {
		rprintf("%s, create KeyPresSema failed\n",__func__);
		return -1;
	}
	// create task
	r = xTaskCreate(vKeyGetTask,"vKeyGetTask",stk,NULL,2,&KeyGetHandle);
	if(r != pdPASS) {
		rprintf("%s, create vKeyGetTask failed\n",__func__);
		return -1;
	}
	r = xTaskCreate(vKeyPrcTask,"vKeyPrcTask",stk,NULL,2,&KeyPrcHandle);
	if(r != pdPASS) {
		rprintf("%s, create vKeyPrcTask failed\n",__func__);
		return -1;
	}
	r = xTaskCreate(vKeyWatcherTask,"vKeyWatcher",stk,NULL,2,&KeyWthHandle);
	if(r != pdPASS) {
		rprintf("%s, create vKeyWatcherTask failed\n",__func__);
		return -1;
	}
	return 0;
}
