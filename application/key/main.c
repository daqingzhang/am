#include <string.h>
#include <common.h>
#include <stm32f10x_system.h>
#include <led.h>
#include <key.h>
#include <motor.h>
#include <infra.h>
#include <speaker.h>
#include <lcd.h>

#ifndef CONFIG_USE_FREERTOS
extern void serial_loopback(void);
extern void leds_on(void);

int main(int argc, const char *argv[])
{
	u32 cpuid = system_get_cpuid();

	rprintf("CPUID: %x\r\n",cpuid);
	rprintf("SYSCLK: %d, APB1CLK: %d, APB2CLK: %d\r\n",
		clktree.sysclk,clktree.apb1clk,clktree.apb2clk);

	system_systick_run(1);

	//serial_loopback();

	leds_on();
	return 0;
}
#else //defined (CONFIG_USE_FREERTOS)
#include <led_task.h>
#include <key_task.h>

extern void vTaskInfoInit(void);

int main(int argc, const char *argv[])
{
	int r;

	rprintf("SYSCLK: %d, APB1CLK: %d, APB2CLk: %d\r\n",
		clktree.sysclk,clktree.apb1clk,clktree.apb2clk);
#if 0
	// config LED
	led_init(LED1|LED2|LED3);

	// config KEY
	key_init(KEY2_ID | KEY3_ID | KEY4_ID);

	//config motor
	motor_init();

	//config infra
	infra_init();

	//config speaker
	speaker_init();
#endif

#ifdef CONFIG_TEST_MOTOR
	motor_test();
#endif
#ifdef CONFIG_TEST_INFRA
	infra_test();
#endif
#ifdef CONFIG_TEST_SPEAKER
	speaker_test();
#endif
	lcd_test();
	// LED task construction
	r = xLedTaskConstructor();
	if(r) {
		rprintf("%s, xLedTaskConstructor failed\n",__func__);
		return -1;
	}

	// KEY task construction
	r =xKeyTaskConstructor();
	if(r) {
		rprintf("%s, xKeyTaskConstructor failed\n",__func__);
		return -1;
	}

	// init task information
#ifdef CONFIG_TASK_INFO
	vTaskInfoInit();
#endif
	// call scheduler
	vTaskStartScheduler();

	for(;;);
	return 0;
}
#endif
