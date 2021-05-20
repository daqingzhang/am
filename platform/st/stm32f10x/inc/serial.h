#ifndef __SERIAL_H__
#define __SERIAL_H__
#include <plat_types.h>

#ifndef CONFIG_SERIAL_0_BAUDRATE
#define CONFIG_SERIAL_0_BAUDRATE	115200
#endif

#ifndef CONFIG_SERIAL_1_BAUDRATE
#define CONFIG_SERIAL_1_BAUDRATE	115200
#endif

#define NVIC_CHANNEL_PRIO_USART1 13
#define NVIC_CHANNEL_PRIO_USART2 12

typedef struct {
	uint8_t data_bits;//8 or 9
	uint8_t parity; //0:None, 1:Odd, 2:Even
	uint8_t stop_bits; //1:1bit,2:2bit
	uint8_t flow_ctrl; //0: No, 1:RTS, 2: CTS, 3:RTS+CTS
	uint32_t baudrate; //4800,9600,19200,115200,38400,921600
} serial_config_t;

enum SERIAL_ID_T {
	SERIAL_ID_0,
	SERIAL_ID_1,

	SERIAL_ID_QTY,
};

void serial_init(enum SERIAL_ID_T id);
int serial_tstc(enum SERIAL_ID_T id);
char serial_getc(enum SERIAL_ID_T id);
void serial_putc(enum SERIAL_ID_T id,char c);
void serial_puts(enum SERIAL_ID_T id,const char *s);
int serial_gets(enum SERIAL_ID_T id,char *s);
int serial_set_config(enum SERIAL_ID_T id, serial_config_t *cfg);
int serial_get_config(enum SERIAL_ID_T id, serial_config_t *cfg);
int serial_set_speed(enum SERIAL_ID_T id, int speed);
int serial_get_speed(enum SERIAL_ID_T id);

#endif
