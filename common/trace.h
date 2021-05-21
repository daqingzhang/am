#ifndef __TRACE_H__
#define __TRACE_H__

#define TR_ATTR_NO_TS (1<<14)

enum TRACE_TRANSPORT_T {
	TRACE_TRANSPORT_UART1,
	TRACE_TRANSPORT_UART2,
	TRACE_TRANSPORT_QTY,
};

int trace_open(enum TRACE_TRANSPORT_T trans_port);
void trace_close(enum TRACE_TRANSPORT_T tport);

int trace_printf(unsigned int attr, const char *str, ...);
void trace_assert(const char *file, const char *func, unsigned int line, const char *fmt, ...);

#ifndef ASSERT
#define ASSERT(cond, str, ...) {if (!(cond)) {trace_assert(__FILE__, __func__, __LINE__, str, ##__VA_ARGS__); }}
#endif

#ifndef TRACE
#define TRACE(attr, str, ...) trace_printf(attr, str, ##__VA_ARGS__)
#endif

#ifndef INFO
#define INFO(attr, str, ...) trace_printf(attr, str, ##__VA_ARGS__)
#endif

#ifndef WARN
#define WARN(attr, str, ...) trace_printf(attr, str, ##__VA_ARGS__)
#endif

#endif
