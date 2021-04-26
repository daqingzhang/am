#include <common.h>
#include "app_led.h"

typedef struct {
	bool opened[APP_LED_ID_QTY];
	app_led_cfg_t cfg[APP_LED_ID_QTY];
} app_led_ctrl_t;

app_led_ctrl_t app_led_ctrl;

static bool led_inited = false;

void app_led_init(bool init)
{
	if (led_inited == init) {
		return;
	}
	if (init) {
	} else {
	}
	led_inited = init;
}

void app_led_open(enum APP_LED_ID_T id, app_led_cfg_t cfg)
{
}

void app_led_on(enum APP_LED_ID_T id)
{
}

void app_led_off(enum APP_LED_ID_T id)
{
}

void app_led_close(enum APP_LED_ID_T id)
{
}


