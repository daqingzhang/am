#include <common.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <dc_motor.h>

#define DCMOTOR_NR	(2)
#define LMOTOR_ID	(1 << 0)
#define RMOTOR_ID	(1 << 1)

#define LMOTOR_GPIO	GPIOA
#define LMOTOR_PINA	GPIO_Pin_4
#define LMOTOR_PINB	GPIO_Pin_5

#define RMOTOR_GPIO	GPIOA
#define RMOTOR_PINA	GPIO_Pin_6
#define RMOTOR_PINB	GPIO_Pin_7

#define dprintf rprintf

struct dc_motor_pins_grp
{
	void *gpio;
	unsigned int pina;
	unsigned int pinb;
};

static dc_motor_pins_grp lmotor_grp = {
	.gpio = LMOTOR_GPIO,
	.pina = LMOTOR_PINA,
	.pinb = LMOTOR_PINB,
};

static dc_motor_pins_grp rmotor_grp = {
	.gpio = RMOTOR_GPIO,
	.pina = RMOTOR_PINA,
	.pinb = RMOTOR_PINB,
};

static int motor_init(void *priv,int wa,int wb)
{
	struct dc_motor_pins_grp *grp = priv;
	GPIO_InitTypeDef Init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	Init.GPIO_Pin   = grp->pina | grp->pinb;
	Init.GPIO_Mode  = GPIO_Mode_Out_PP;
	Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(grp->gpio,&Init);

	GPIO_WriteBit(grp->gpio,grp->pina,wa);
	GPIO_WriteBit(grp->gpio,grp->pinb,wb);
	dprintf("%s, pina %d = %d\n",__func__, grp->pina,wa);
	dprintf("%s, pinb %d = %d\n",__func__, grp->pinb,wb);
	return 0;
}

static int motor_run(void *priv, int wa, int wb, unsigned int pulse)
{
	struct dc_motor_pins_grp *grp = priv;

	dprintf("%s, pina %d = %d\n",__func__, grp->pina,wa);
	dprintf("%s, pinb %d = %d\n",__func__, grp->pinb,wb);

	GPIO_WriteBit(grp->gpio,grp->pina,wa);
	GPIO_WriteBit(grp->gpio,grp->pinb,wb);

	mdelay(pulse);
	return 0;
}

void int motor_stop(void *priv, int wa, int wb)
{
	struct dc_motor_pins_grp *grp = priv;

	dprintf("%s, pina %d = %d\n",__func__, grp->pina,wa);
	dprintf("%s, pinb %d = %d\n",__func__, grp->pinb,wb);

	GPIO_WriteBit(grp->gpio,grp->pina,wa);
	GPIO_WriteBit(grp->gpio,grp->pinb,wb);
	return 0;
}

struct dc_motor_operations motor_ops[] = {
	{
		.init = motor_init,
		.run  = motor_run,
		.stop = motor_stop,
	},
	{
		.init = motor_init,
		.run  = motor_run,
		.stop = motor_stop,
	},
};

struct dc_motor motors[DCMOTOR_NR];

int dc_motor_register(struct dc_motor *motor, struct dc_motor_operations *ops,
			const char *name, int id, void *priv)
{
	if((!motor) || (!ops))
		return -1;

	motor->name = name;
	motor->id = id;
	motor->ops = ops;
	motor->priv = priv;

	if(motor->ops->init)
		motor->ops->init(motor->priv, 0,0);
}

