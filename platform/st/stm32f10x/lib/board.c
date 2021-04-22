#include <common.h>
#include <stm32f10x_system.h>

void board_init(void)
{
	int retval = 0;
	unsigned int cpuid,prigrp;

	interrupts_disable();

	// init system clock
	retval = system_init_clock();

	// config serial
	serial_init(USART1_ID | USART2_ID);

	printf("\nserial inited\n");

	if(retval) {
		printf("init system clock failed, %d\n",retval);
		return;
	}
	printf("SYS: %d Hz, APB1: %d Hz, APB2: %d Hz\n",
		clktree.sysclk, clktree.apb1clk, clktree.apb2clk);

	cpuid = system_get_cpuid();
	printf("CPU ID: %x\n",cpuid);

	// set priority group
	prigrp = NVIC_PRIORITY_GRP4;
	system_set_priority_group(NVIC_PRIORITY_GRP4);
	printf("prigrp: %x\n",prigrp);

	// set vector address
	system_set_vectaddr(NVIC_VECTOR_BASE_ADDR,0);
	printf("vect addr: %x\n",NVIC_VECTOR_BASE_ADDR);

	// config system tick
	retval = system_systick_config(CONFIG_SYSTICK_MS(100));
	if(retval) {
		printf("config system tick failed %d\n",retval);
		return;
	}
	//system_systick_run(1);

	// config pinmux & GPIO

	// config TIMER1,TIMER2,TIMER3,TIMER4
	timer_init(TIMER1_ID | TIMER2_ID | TIMER3_ID | TIMER4_ID);
	printf("timer inited\n");

	interrupts_enable();

	printf("%s done! \r\n",__func__);
}
