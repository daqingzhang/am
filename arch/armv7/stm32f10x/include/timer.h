#ifndef __TIMER_H__
#define __TIMER_H__

enum {
	TIMER1_ID = (1 << 0),
	TIMER2_ID = (1 << 1),
	TIMER3_ID = (1 << 2),
	TIMER4_ID = (1 << 3),
};

#define CONFIG_TIMER_DEBUG
#define ms_to_us(ms) ((ms) * 1000)

void timer_init(int id);
int  timer_capture_pulse(int id, unsigned int *period,
			unsigned int *pos_width, int enable);
int  timer_output_pulse(int id, unsigned int period,
			unsigned int pos_width,int enable);

void timer_delay_us(void *priv, unsigned int us);
void udelay(unsigned long us);
void mdelay(unsigned long ms);

#endif
