#include <common.h>
#include <timer.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_system.h>
#include <stm32f10x_rcc.h>

#define HWP_DLY_TIMER TIM4

#ifdef CONFIG_TIMER_DEBUG
#define dprintf rprintf
#else
#define dprintf(...) do{}while(0)
#endif

void timer_init(int id)
{
	if(id & TIMER4_ID)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	if(id & TIMER3_ID)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	if(id & TIMER2_ID)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	if(id & TIMER1_ID)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	else
		return;
}

void timer_delay_us(void *priv, unsigned int us)
{
	TIM_TypeDef *tim = priv;
	u32 pscl = (clktree.apb1clk) / 1000000;

	dprintf("%s, delay %d us\n",__func__,us);
	do {
		if(us > 0xffff) {
			us   = us >> 1;
			pscl = pscl << 1;
		}
	} while(us > 0xffff);
	// CK_CNT = Fsrc / (PSCL + 1)
	pscl -= 1;
	dprintf("%s, us = %d, pscl = %d\n",__func__, us, pscl);

	// down counter, center-aligned mode 3
	tim->CR1 = TIM_CR1_DIR | TIM_CR1_CMS;
	tim->PSC = (u16)pscl;
	tim->ARR = (u16)us;
	tim->EGR = TIM_EGR_UG;
	tim->SR = ~(TIM_SR_UIF);
	tim->CR1 |= TIM_CR1_CEN;
	while((tim->SR & TIM_SR_UIF) == 0);
	tim->CR1 = 0;
	tim->SR = ~(TIM_SR_UIF);
}

int timer_capture_pulse(int id, unsigned int *period, unsigned int *pos_width, int enable)
{
	return 0;
}

int timer_output_pulse(int id, unsigned int period, unsigned int pos_width,int enable)
{
	return 0;
}

void udelay(unsigned long us)
{
	timer_delay_us(HWP_DLY_TIMER,us);
}

void mdelay(unsigned long ms)
{
	timer_delay_us(HWP_DLY_TIMER, ms_to_us(ms));
}
