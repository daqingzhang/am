#include <led_task.h>

struct fsm_state led_fsm_map[] =
{
	{.current = STATE_DISP, .route = DISP_TO_DISP, .next = STATE_DISP},
	{.current = STATE_DISP, .route = DISP_TO_DLY,  .next = STATE_DLY},
	{.current = STATE_DLY,  .route = DLY_TO_DLY,   .next = STATE_DLY},
	{.current = STATE_DLY,  .route = DLY_TO_RSP,   .next = STATE_RSP},
	{.current = STATE_RSP,  .route = RSP_TO_RSP,   .next = STATE_RSP},
	{.current = STATE_RSP,  .route = RSP_TO_DISP,  .next = STATE_DISP},
	{.current = STATE_RSP,  .route = RSP_TO_IDLE,  .next = STATE_IDLE},
	{.current = STATE_IDLE, .route = IDLE_TO_IDLE, .next = STATE_IDLE},
	{.current = STATE_IDLE, .route = IDLE_TO_DISP, .next = STATE_DISP},
	{.current = FSM_S_END,	.route = FSM_R_END,    .next = FSM_S_END},
};

static int led_fsm_init(struct fsm_state *p, void *priv)
{
	if(p == NULL)
		return -1;

	p->current = STATE_DISP;
	p->route   = DISP_TO_DISP;
	p->next	   = STATE_DISP;

	return 0;
}

static int led_fsm_debug(struct fsm_state *s,void *priv)
{
	rprintf("\r\nstate: current: %d, r: %d, next: %d\r\n",
			s->current,s->route,s->next);
	return 0;
}
#if 0
static void led_fsm_run(struct fsm_state *s, void *priv)
{
	return 0;
}
#endif

static struct fsm_operations led_fsm_ops =
{
	.init	= led_fsm_init,
	//.run	= led_fsm_run,
	.run	= NULL,
	.debug	= led_fsm_debug,
};

static struct fsm_device led_fsm_dev;

int led_fsm_register(void)
{
	return fsm_register(&led_fsm_dev, "led_fsm",
				&led_fsm_ops,led_fsm_map,0);
}

struct fsm_device *led_fsm_get(void)
{
	return &led_fsm_dev;
}
