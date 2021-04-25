#ifndef __COMMON_H__
#define __COMMON_H__
#include <serial.h>
#include <timer.h>
#include <string.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr)	(sizeof(arr)/sizeof((arr)[0]))
#endif

#define IRQ_PRIORITY_REALTIME 0

#ifdef CONFIG_USE_FREERTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#endif

void board_init(void);

void rprintf(const char *fmt, ...);
void mdelay(unsigned long ms);
void udelay(unsigned long us);

void interrupts_disable(void);
void interrupts_enable(void);

#ifndef printf
#define printf rprintf
#endif

#endif
