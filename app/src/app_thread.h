#ifndef __APP_THREAD_H__
#define __APP_THREAD_H__

#ifdef __cplusplus
extern "C" {
#endif

enum APP_THREAD_HANDLER_ID_T {
	APP_THREAD_HANDLER_ID_0,
	APP_THREAD_HANDLER_ID_1,
	APP_THREAD_HANDLER_ID_2,
	APP_THREAD_HANDLER_ID_3,
	APP_THREAD_HANDLER_ID_4,
	APP_THREAD_HANDLER_ID_5,

	APP_THREAD_HANDLER_ID_QTY,
};

typedef struct {
	uint32_t cmd;
	uint32_t arg[3];
} app_thread_handler_param_t ;

typedef struct {
	enum APP_THREAD_HANDLER_ID_T hid;
	app_thread_handler_param_t param;
} app_thread_msg_t;

typedef void (*app_thread_handler_t)(app_thread_handler_param_t param);

void app_thread_init(bool init);

int app_thread_register_handler(enum APP_THREAD_HANDLER_ID_T id, app_thread_handler_t *handler);

int app_thread_deregister_handler(enum APP_THREAD_HANDLER_ID_T id, app_thread_handler_t *handler);

#ifdef __cplusplus
}
#endif

#endif
