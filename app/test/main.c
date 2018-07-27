#include <string.h>
#include <common.h>
#include <stm32f10x_system.h>
#include <led.h>
#include <key.h>
#include <motor.h>
#include <infra.h>
#include <speaker.h>
#include <lcd.h>

void serial_loopback(void);
void leds_on(void);

void trigger_swi(void)
{
	asm volatile("swi #4\n"
			:
			:
			: "memory");
}

int main(int argc, const char *argv[])
{
	//system_systick_run(1);

	printf("hello world\n");

//	trigger_swi();

	__ISB();
	__DSB();
	__WFI();
//	__WFE();
	leds_on();

	return 0;
}
