#include "trace.h"
#include "serial.h"

#ifdef TRACE_CRLF
#define NEW_LINE_STR "\r\n"
#else
#define NEW_LINE_STR "\n"
#endif

#ifndef TRACE_BUF_SIZE
#define TRACE_BUF_SIZE (1024*1)
#endif

struct trace_assert_info_t {
	uint32_t id;
	uint32_t cpu_id;
	const char *file;
	const char *func;
	uint32_t line;
	uint32_t regs[15];
	uint32_t reg_msp;
	uint32_t reg_psp;
	uint32_t reg_control;
};

struct trace_exception_info_t {
	uint32_t regs[15];
	uint32_t reg_msp;
	uint32_t reg_psp;
	uint32_t reg_control;
};

struct trace_buff_t {
	uint8_t buf[TRACE_BUF_SIZE];
	uint32_t wpos;
	uint32_t rpos;
	uint16_t discards;
	bool sending;
	bool in_trace;
	bool wrapped;
	uint8_t pause_cnt;
};

static enum TRACE_TRANSPORT_T trace_tport = TRACE_TRANSPORT_QTY;
static enum SERIAL_ID_T trace_serid = SERIAL_ID_QTY;
static struct trace_buff_t trace;
static bool trace_opened = false;

static serial_config_t trace_uart_cfg = {
	.data_bits = 8,
	.parity = 0,
	.stop_bits = 1,
	.flow_ctrl = 0,
	.baudrate = 9600,
};

static const unsigned char discards_prefix[] = NEW_LINE_STR "LOST";
static unsigned char discards_buf[sizeof(discards_prefix)-1+7];

static bool trace_is_uart_transport(enum TRACE_TRANSPORT_T tport)
{
	if (tport == TRACE_TRANSPORT_UART1
		|| tport == TRACE_TRANSPORT_UART2) {
		return true;
	} else {
		return false;
	}
}

static void trace_uart_idle_send_data(void)
{
	uint32_t i;
	uint32_t wpos, rpos;
	uint8_t *buf;

	wpos = trace.wpos;
	rpos = trace.rpos;
	buf  = trace.buf;

	if (rpos == wpos) {
		return;
	}
	if (rpos > wpos) {
		for (i = rpos; i < TRACE_BUF_SIZE; i++) {
			serial_putc(trace_serid, buf[i]);
			rpos = 0;
		}
		for (i = rpos; i < wpos; i++) {
			serial_putc(trace_serid, buf[i]);
		}
	}
	trace.rpos = trace.wpos;
	if (trace.rpos >= TRACE_BUF_SIZE) {
		trace.rpos -= TRACE_BUF_SIZE;
	}
}

static void trace_uart_send_data(void)
{
	trace_uart_idle_send_data();
}

static void trace_send_data(void)
{
	if (trace.pause_cnt) {
		return;
	}
	if (trace_is_uart_transport(trace_tport)) {
		trace_uart_send_data();
	}
}

void trace_idle_send_data(void)
{
	if (trace.pause_cnt) {
		return;
	}
	if (trace_is_uart_transport(trace_tport)) {
		trace_uart_idle_send_data();
	}
}

static void trace_print_discards(uint32_t trace_discards)
{
}

static int trace_output_data(const unsigned char *buf, unsigned int buf_len)
{
	int ret = 0;

	//lock irq

	if (!trace.in_trace) {
		uint32_t avail, out_len, size;

		if (trace.wpos >= trace.rpos) {
			avail = TRACE_BUF_SIZE - (trace.wpos - trace.rpos) - 1;
		} else {
			avail = trace.rpos - trace.wpos - 1;
		}

		out_len = buf_len;
		if (trace.discards) {
			out_len += sizeof(discards_buf);
		}
		if (avail < out_len) {
			if (trace.discards < (1<<(sizeof(trace.discards)*8))-1) {
				trace.discards++;
			}
			trace_send_data();
		} else {
			if (trace.discards) {
				trace_print_discards(trace.discards);
				trace.discards = 0;
			}
			size = TRACE_BUF_SIZE - trace.wpos;
			if (buf_len <= size) {
				size = buf_len;
			}
			memcpy(&trace.buf[trace.wpos], buf, size);
			if (buf_len > size) {
				memcpy(&trace.buf[0], &buf[size], buf_len - size);
			}
			trace.wpos += buf_len;
			if (trace.wpos >= TRACE_BUF_SIZE) {
				trace.wpos -= TRACE_BUF_SIZE;
				trace.wrapped = true;
			}
			trace_send_data();
		}
		trace.in_trace = false;
	}

	//unlock irq
	return ret;
}

static void trace_info_print(enum TRACE_TRANSPORT_T tport)
{
	char buf[50] = {0};
	int len = 0;

	len = snprintf(buf, sizeof(buf),
		NEW_LINE_STR  "---- TRACE %d ----" NEW_LINE_STR, tport);
	trace_output_data((unsigned char *)buf, len);
}

int trace_open(enum TRACE_TRANSPORT_T tport)
{
	int ret = 0;

	if (trace_opened) {
		return 0;
	}
	if (tport >= TRACE_TRANSPORT_QTY) {
		return -1;
	}

	trace.wpos = 0;
	trace.rpos = 0;
	trace.sending = false;
	trace.in_trace = false;
	trace.wrapped = false;
	trace.pause_cnt = 0;

	if (tport == TRACE_TRANSPORT_UART1) {
		trace_serid = SERIAL_ID_0;
		ret = serial_open(trace_serid, &trace_uart_cfg);
	} else if (tport == TRACE_TRANSPORT_UART2) {
		trace_serid = SERIAL_ID_1;
		ret = serial_open(trace_serid, &trace_uart_cfg);
	} else {
		return -2;
	}
	trace_tport = tport;
	trace_opened = true;
	trace_info_print(tport);
	return ret;
}

void trace_close(enum TRACE_TRANSPORT_T tport)
{
	if (!trace_opened) {
		return;
	}
	if (tport == TRACE_TRANSPORT_UART1) {
		serial_close(SERIAL_ID_0);
	} else if (tport == TRACE_TRANSPORT_UART2) {
		serial_close(SERIAL_ID_1);
	}
	trace_opened = false;
}

int trace_format_va(unsigned int attr, char *buf, unsigned int buf_len, const char *fmt, va_list ap)
{
	int len = 0;

	len = vsnprintf(&buf[0], buf_len, fmt, ap);
	return len;
}

int trace_printf_ts(unsigned int attr, char *buf, unsigned int size)
{
	return 0;
}

int trace_printf_internal(unsigned int attr, const char *fmt, va_list ap)
{
	char buf[128];
	int len = 0;

	if ((attr & TR_ATTR_NO_TS) == 0) {
		len = trace_printf_ts(attr, buf, len);
	}
	len += trace_format_va(attr, &buf[len],sizeof(buf)-len, fmt, ap);
	return trace_output_data((unsigned char *)buf, len);
}

int trace_printf(unsigned int attr, const char *fmt, ...)
{
	int ret = 0;
	va_list ap;

	va_start(ap, fmt);
	ret = trace_printf_internal(attr, fmt, ap);
	va_end(ap);

	return ret;
}

void trace_assert(const char *file, const char *func,
	unsigned int line, const char *fmt, ...)
{
}

