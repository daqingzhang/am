#ifndef __APP_LED_H__
#define __APP_LED_H__

#ifdef __cplusplus
extern "C" {
#endif

enum APP_LED_ID_T {
	APP_LED_ID_0 = (1<<0),
	APP_LED_ID_1 = (1<<1),
	APP_LED_ID_2 = (1<<2),
};

#define APP_LED_ID_QTY 3

enum APP_LED_WORK_MODE_T {
	APP_LED_MODE_BASIC, //basic mode
	APP_LED_MODE_BLINK, //blink mode
	APP_LED_MODE_ONE_SHOT, //one shot mode
};

enum APP_LED_EVT_T {
	APP_LED_EVT_ON,
	APP_LED_EVT_OFF,
};

typedef void (*app_led_event_handler_t)(enum APP_LED_ID_T id, enum APP_LED_EVT_T evt);

typedef struct {
	enum APP_LED_WORK_MODE_T mode;
	uint32_t time_blk_on;    //blink on period
	uint32_t time_blk_off;   //blink off period
	uint32_t time_one_short; //period time for one shot mode
	app_led_event_handler_t handler;
} app_led_cfg_t;

void app_led_init(bool init);
void app_led_open(enum APP_LED_ID_T id, app_led_cfg_t cfg);
void app_led_close(enum APP_LED_ID_T id);
void app_led_on(enum APP_LED_ID_T id);
void app_led_off(enum APP_LED_ID_T id);

#ifdef __cplusplus
}
#endif

#endif
