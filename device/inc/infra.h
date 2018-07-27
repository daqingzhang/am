#ifndef __INFRARED_H__
#define __INFRARED_H__
#include <sensor.h>

#define CONFIG_INFRA_DEBUG

#define INFRA_DEV_NR	2

#define INFRA1_ID	1
#define INFRA2_ID	2

int infra_register(void);
struct sensor_dev *infra_get(int id);

#endif
