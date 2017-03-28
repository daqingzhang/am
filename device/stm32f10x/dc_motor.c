#include <common.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <dc_motor.h>

#define LMOTOR_GPIO	GPIOA
#define LMOTOR_PINA	GPIO_Pin_4
#define LMOTOR_PINB	GPIO_Pin_5

#define RMOTOR_GPIO	GPIOA
#define RMOTOR_PINA	GPIO_Pin_6
#define RMOTOR_PINB	GPIO_Pin_7

#if defined(CONFIG_MOTOR_DEBUG)
#define dprintf rprintf
#else
#define dprintf(...) do{}while(0)
#endif

enum dc_motor_cmd
{
	DC_MTR_CMD_INIT = 0x10,
	DC_MTR_CMD_RESET,
	DC_MTR_CMD_FORWARD,
	DC_MTR_CMD_BACKWARD,
	DC_MTR_CMD_STOP,
};

struct dc_motor_gpio
{
	void *gpio;
	unsigned int pina;
	unsigned int pinb;
};

static int dc_motor_write(struct dc_motor_gpio *gp,int cmd)
{
	int wa = 0, wb = 0;

	switch(cmd) {
	case DC_MTR_CMD_INIT:
	{
		GPIO_InitTypeDef Init;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

		Init.GPIO_Pin   = gp->pina | gp->pinb;
		Init.GPIO_Mode  = GPIO_Mode_Out_PP;
		Init.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(gp->gpio,&Init);

	}
	case DC_MTR_CMD_STOP:
	case DC_MTR_CMD_RESET:
		wa = 0;
		wb = 0;
		break;
	case DC_MTR_CMD_FORWARD:
		wa = 0;
		wb = 1;
		break;
	case DC_MTR_CMD_BACKWARD:
		wa = 1;
		wb = 0;
		break;
	default:
		return -1;
	}
	GPIO_WriteBit(gp->gpio,gp->pina,wa);
	GPIO_WriteBit(gp->gpio,gp->pinb,wb);

	dprintf("%s, cmd: 0x%2x, pina 0x%4x = %d, pinb 0x%4x = %d\n",__func__,
			cmd, gp->pina, wa, gp->pinb, wb);
	return 0;
}

static int dc_motor_init(struct motor *m, void *priv)
{
	return dc_motor_write(priv,DC_MTR_CMD_INIT);
}

static int dc_motor_run(struct motor *m, void *priv, unsigned int pulse, int forward)
{
	int cmd;

	cmd = forward ? DC_MTR_CMD_FORWARD : DC_MTR_CMD_BACKWARD;

	dc_motor_write(priv,cmd);
	udelay(pulse);
	return dc_motor_write(priv,DC_MTR_CMD_STOP);
}

static int dc_motor_stop(struct motor *m, void *priv)
{
	return dc_motor_write(priv,DC_MTR_CMD_STOP);
}

static struct dc_motor_gpio lmotor_gp = {
	.gpio = LMOTOR_GPIO,
	.pina = LMOTOR_PINA,
	.pinb = LMOTOR_PINB,
};

static struct dc_motor_gpio rmotor_gp = {
	.gpio = RMOTOR_GPIO,
	.pina = RMOTOR_PINA,
	.pinb = RMOTOR_PINB,
};

static struct motor_operations dc_motor_ops = {
	.init = dc_motor_init,
	.run  = dc_motor_run,
	.stop = dc_motor_stop,
};

static int dc_motor_inited = 0;
static struct motor_dev dc_motors[DC_MOTOR_NR];

int dc_motor_register(void)
{
	int retval;

	dc_motor_inited = 1;

	retval  = motor_register(&dc_motors[0],&dc_motor_ops,"L_DC_MOTOR",LMOTOR_ID,&lmotor_gp);
	retval += motor_register(&dc_motors[1],&dc_motor_ops,"R_DC_MOTOR",RMOTOR_ID,&rmotor_gp);

	if(retval)
		dprintf("%s, failed, %d\n",__func__, retval);
	return retval;
}

struct motor_dev *dc_motor_get(int id)
{
	int i;
	struct motor_dev *m = dc_motors;

	if(!dc_motor_inited)
		return NULL;

	for(i = 0;i < ARRAY_SIZE(dc_motors);i++) {
		if(m->id == id)
			return m;
		m++;
	}
	return NULL;
}
