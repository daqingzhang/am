#ifndef __COMMON_H__
#define __COMMON_H__
#include <core_reg.h>
#include <serial.h>
#include <timer.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr)	(sizeof(arr)/sizeof((arr)[0]))
#endif

#ifdef CONFIG_USE_FREERTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

void vMsgPrint(void  *pvParameters,char c);
u16 CalCRC16(u8 *pdata,int size);
#endif

void rprintf(const char *fmt, ...);
void mdelay(unsigned long ms);
void udelay(unsigned long us);

int interrupts_enable();
void interrupts_disable();
#endif
