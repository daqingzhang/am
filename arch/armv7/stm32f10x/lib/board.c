#include <common.h>

void board_init(void)
{
	int retval = 0;
	u32 cpuid,prigrp;

	__disable_irq();

	// init system clock
	retval = system_init_clock();
	if(retval) {
		rprintf("init system clock failed %d\n",retval);
		return;
	}
	rprintf("SYS: %d MHz, APB1: %d MHz, APB2: %d MHz\n",
		clktree.sysclk, clktree.apb1clk, clktree.apb2clk);

	cpuid = system_get_cpuid();
	rprintf("CPU ID: %x\n",cpuid);

	// set priority group
	prigrp = NVIC_PRIORITY_GRP4;
	system_set_priority_group(NVIC_PRIORITY_GRP4);
	rprintf("prigrp: %x\n",prigrp);

	// set vector address
	system_set_vectaddr(NVIC_VECTOR_BASE_FLASH,0);
	rprintf("vect addr: %x\n",NVIC_VECTOR_BASE_FLASH);

	// config system tick
	retval = system_systick_config(CONFIG_SYSTICK_MS(100));
	if(retval) {
		rprintf("config system tick failed %d\n",retval);
		return;
	}
	//system_systick_run(1);

	// config pinmux & GPIO

	// config serial
	serial_init(USART1_ID);
	serial_init(USART2_ID);

	// config TIMER1,TIMER2,TIMER3,TIMER4
	timer_init(TIMER1_ID);
	timer_init(TIMER2_ID);
	timer_init(TIMER3_ID);
	timer_init(TIMER4_ID);

	__enable_irq();

	rprintf("%s done! \r\n",__func__);
}
