#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__
#include <motor.h>

#define DC_MOTOR_NR	(2)
#define LMOTOR_ID	(1 << 0)
#define RMOTOR_ID	(1 << 1)

#define CONFIG_MOTOR_DEBUG

int dc_motor_register(void);
struct motor_dev *dc_motor_get(int id);

#endif
