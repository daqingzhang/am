#ifndef __CTRACE_H__
#define __CTRACE_H__

enum CTRACE_ID {
	CTRACE_ID_0,
	CTRACE_ID_1,
	CTRACE_ID_2,
	CTRACE_ID_QTY,
};

void ctrace_open(enum CTRACE_ID id);
void ctrace_close(enum CTRACE_ID id);
void ctrace_printf(unsigned int attr, const char *str, ...);
void ctrace_assert(const char *file, const char *func, unsigned int line, const char *fmt, ...);

#ifndef ASSERT
#define ASSERT(cond, str, ...) {if (!(cond)) {ctrace_assert(__FILE__, __func__, __LINE__, str, ##__VA_ARGS__); }}
#endif

#ifndef TRACE
#define TRACE(attr, str, ...) ctrace_printf(attr, str, ##__VA_ARGS__)
#endif

#ifndef INFO
#define INFO(attr, str, ...) ctrace_printf(attr, str, ##__VA_ARGS__)
#endif

#ifndef WARN
#define WARN(attr, str, ...) ctrace_printf(attr, str, ##__VA_ARGS__)
#endif

#endif
