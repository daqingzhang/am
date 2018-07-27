#include <common.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <key.h>

#define KEY_GPIO GPIOB
#define K2_PIN GPIO_Pin_9
#define K3_PIN GPIO_Pin_8
#define K4_PIN GPIO_Pin_7

#ifdef CONFIG_KEY_DEBUG
#define dprintf rprintf
#else
#define dprintf(...) do{}while(0)
#endif

struct key_gpio
{
	const char *name;
	int id;
	void *gpio;
	unsigned int pin;
};

static struct key_gpio key_gp[] = {
	{
		.name = "KEY2",
		.id   = KEY2_ID,
		.gpio = KEY_GPIO,
		.pin  = K2_PIN,
	},
	{
		.name = "KEY3",
		.id   = KEY3_ID,
		.gpio = KEY_GPIO,
		.pin  = K3_PIN,
	},
	{
		.name = "KEY4",
		.id   = KEY4_ID,
		.gpio = KEY_GPIO,
		.pin  = K4_PIN,
	},
};

static int key_init(struct sensor *sen, void *priv)
{
	struct key_gpio *gp = priv;
	GPIO_InitTypeDef Init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	Init.GPIO_Pin 	= gp->pin;
	Init.GPIO_Mode 	= GPIO_Mode_IPU;
	Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gp->gpio,&Init);
	dprintf("%s, %s pin = 0x%x\n",__func__, gp->name,gp->pin);
	return 0;
}

static int key_read(struct sensor *sen, void *priv)
{
	struct key_gpio *gp = priv;
	unsigned int t = 0;

	t = GPIO_ReadInputData(gp->gpio);
	// pressed = 0,unpressed = 1
	sen->value = (~t) & gp->pin;
	dprintf("%s, %s value = 0x%x",__func__,gp->name,sen->value);
	return 0;
}

static struct sensor_operations key_ops = {
	.init = key_init,
	.read = key_read,
	.write = NULL,
	.config = NULL,
};

static struct sensor_dev key_dev[KEY_DEV_NR];

int key_register(void)
{
	int i;

	for(i = 0;i < KEY_DEV_NR;i++) {
		sensor_register(&key_dev[i], &key_ops, key_gp[i].name,
				key_gp[i].id, &key_gp[i]);

		dprintf("%s, %s registered, id = %d\n",__func__,
			key_gp[i].name, key_gp[i].id);
	}
	return 0;
}

struct sensor_dev *key_get(int id)
{
	int i;

	for(i = 0;i < KEY_DEV_NR;i++) {
		if(key_dev[i].id == id)
			return &key_dev[i];
	}
	return NULL;
}
