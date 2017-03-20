#include <common.h>

void board_init(void)
{
	int retval = 0;
	u32 cpuid,prigrp;

	__disable_irq();

	// init system clock
	retval = system_init_clock();

	// config serial
	serial_init(USART1_ID | USART2_ID);

	rprintf("\nserial inited\n");

	if(retval) {
		rprintf("init system clock failed, %d\n",retval);
		return;
	}
	rprintf("SYS: %d Hz, APB1: %d Hz, APB2: %d Hz\n",
		clktree.sysclk, clktree.apb1clk, clktree.apb2clk);

	cpuid = system_get_cpuid();
	rprintf("CPU ID: %x\n",cpuid);

	// set priority group
	prigrp = NVIC_PRIORITY_GRP4;
	system_set_priority_group(NVIC_PRIORITY_GRP4);
	rprintf("prigrp: %x\n",prigrp);

	// set vector address
	system_set_vectaddr(NVIC_VECTOR_BASE_ADDR,0);
	rprintf("vect addr: %x\n",NVIC_VECTOR_BASE_ADDR);

	// config system tick
	retval = system_systick_config(CONFIG_SYSTICK_MS(100));
	if(retval) {
		rprintf("config system tick failed %d\n",retval);
		return;
	}
	//system_systick_run(1);

	// config pinmux & GPIO

	// config TIMER1,TIMER2,TIMER3,TIMER4
	timer_init(TIMER1_ID | TIMER2_ID | TIMER3_ID | TIMER4_ID);
	rprintf("timer inited\n");

	__enable_irq();

	rprintf("%s done! \r\n",__func__);
}
