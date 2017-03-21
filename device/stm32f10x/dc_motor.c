#include <common.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <dc_motor.h>

#define LMOTOR_ID	1
#define LMOTOR_GPIO	GPIOA
#define LMOTOR_PINA	GPIO_Pin_4
#define LMOTOR_PINB	GPIO_Pin_5

#define RMOTOR_ID	2
#define RMOTOR_GPIO	GPIOA
#define RMOTOR_PINA	GPIO_Pin_6
#define RMOTOR_PINB	GPIO_Pin_7

int dc_motor_init(struct dc_motor *m, void *priv)
{
	unsigned short pin;
	int id = *priv;
	GPIO_InitTypeDef Init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	if(id == LMOTOR_ID) {
		pin = (LMOTOR_PINA | LMOTOR_PINB);


		Init.GPIO_Pin   = pin;
		Init.GPIO_Mode  = GPIO_Mode_Out_PP;
		Init.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LMOTOR_GPIO,&Init);//GPIOA
		if(m->wire_a)
			GPIO_WriteBit(LMOTOR_GPIO,LMOTOR_PINA,Bit_SET);
		else
			GPIO_WriteBit(LMOTOR_GPIO,LMOTOR_PINA,Bit_RESET);

		if(m->wire_b)
			GPIO_WriteBit(LMOTOR_GPIO,LMOTOR_PINB,Bit_SET);
		else
			GPIO_WriteBit(LMOTOR_GPIO,LMOTOR_PINB,Bit_RESET);
	}
	if(id == RMOTOR_ID) {
		pin = (RMOTOR_PINA | RMOTOR_PINB);

		Init.GPIO_Pin   = (unsigned short)pin;
		Init.GPIO_Mode  = GPIO_Mode_Out_PP;
		Init.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RMOTOR_GPIO,&Init);//GPIOA
		if(m->wire_a)
			GPIO_WriteBit(RMOTOR_GPIO,RMOTOR_PINA,Bit_SET);
		else
			GPIO_WriteBit(RMOTOR_GPIO,RMOTOR_PINA,Bit_RESET);

		if(m->wire_b)
			GPIO_WriteBit(RMOTOR_GPIO,RMOTOR_PINB,Bit_SET);
		else
			GPIO_WriteBit(RMOTOR_GPIO,RMOTOR_PINB,Bit_RESET);
	}
	return 0;
}

int dc_motor_run(struct dc_motor *m, void *priv, unsigned int pulse)
{

}
