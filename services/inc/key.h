#ifndef __KEY_H__
#define __KEY_H__
#include <sensor.h>

#define CONFIG_KEY_DEBUG

#define KEY_DEV_NR 3

enum key_id
{
	KEY2_ID = 1,
	KEY3_ID = 2,
	KEY4_ID = 3,
};

int key_register(void);
struct sensor_dev *key_get(int id);

#endif
