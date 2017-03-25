#include <common.h>
#include <infra.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define INFRA1_GPIO	GPIOB
#define INFRA1_PIN	GPIO_Pin_0

#define INFRA2_GPIO	GPIOB
#define INFRA2_PIN	GPIO_Pin_1

#ifdef CONFIG_INFRA_DEBUG
#define dprintf rprintf
#else
#define dprintf(...) do{}while(0)
#endif

struct infra_gpio
{
	const char *name;
	int id;
	void *gpio;
	unsigned int pin;
};

static struct infra_gpio infra_gp[] = {
	{
		.name = "INFRA1",
		.id   = INFRA1_ID,
		.gpio = INFRA1_GPIO,
		.pin  = INFRA1_PIN,
	},
	{
		.name = "INFRA2",
		.id   = INFRA2_ID,
		.gpio = INFRA2_GPIO,
		.pin  = INFRA2_PIN,
	},
};

static int infra_init(struct sensor *sen, void *priv)
{
	struct infra_gpio *gp = priv;
	GPIO_InitTypeDef Init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIOB
	Init.GPIO_Pin   = gp->pin;
	Init.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gp->gpio,&Init);
	dprintf("%s, %s pin = 0x%x\n",__func__,gp->name,gp->pin);
	return 0;
}

static int infra_read(struct sensor *sen, void *priv)
{
	struct infra_gpio *gp = priv;
	unsigned int t;

	t =  GPIO_ReadInputData(gp->gpio);
	sen->value = gp->pin & t;
	dprintf("%s, %s val = 0x%x\n",__func__,gp->name,sen->value);
	return 0;
}

static struct sensor_operations infra_ops = {
	.init = infra_init,
	.read = infra_read,
	.write = NULL,
	.config = NULL,
};

static struct sensor_dev infra_dev[INFRA_DEV_NR];

int infra_register(void)
{
	int i;

	for(i = 0;i < INFRA_DEV_NR;i++) {
		sensor_register(&infra_dev[i], &infra_ops, infra_gp[i].name,
				infra_gp[i].id, &infra_gp[i]);
		dprintf("%s, %s registered, id = %d\n",__func__,
			infra_gp[i].name,infra_gp[i].id);
	}
	return 0;
}

struct sensor_dev *infra_get(int id)
{
	int i;

	for(i = 0;i < INFRA_DEV_NR;i++) {
		if(infra_dev[i].id == id)
			return &infra_dev[i];
	}
	return NULL;
}
