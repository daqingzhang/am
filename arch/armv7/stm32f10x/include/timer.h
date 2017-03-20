#ifndef __TIMER_H__
#define __TIMER_H__

enum {
	TIMER1_ID = (1 << 0),
	TIMER2_ID = (1 << 1),
	TIMER3_ID = (1 << 2),
	TIMER4_ID = (1 << 3),
};

#define DELAY_TIMER TIMER4_ID

#define CONFIG_TIMEOUT_CAP_PULSE 1000

void timer_init(int id);
int  timer_capture_pulse(int id, unsigned int *period, unsigned int *pos_width, int enable);
int  timer_output_pulse(int id, unsigned int period, unsigned int pos_width,int enable);
void timer_delay_us(int id, int us);

#endif
