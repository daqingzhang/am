#include <common.h>
#include <motor.h>

static void init_motor(struct motor *m, int a, int b,
			int c, int d)
{
	m->wire_a = a;
	m->wire_b = b;
	m->wire_c = c;
	m->wire_d = d;
}

int motor_register(struct motor_dev *d, struct motor_operations *ops,
			const char *name, int id,void *priv)
{
	int retval = -2;

	if((!d) || (!ops) || (d->inited))
		return -1;

	d->name = name;
	d->ops  = ops;
	d->id   = id;
	d->priv = priv;
	d->inited = 1;

	init_motor(&d->motor,0,0,0,0);

	if(d->ops->init)
		retval = d->ops->init(&d->motor, d->priv);
	return retval;
}

int motor_unregister(struct motor_dev *d)
{
	d->inited = 0;
	return -1;
}

int motor_stop(struct motor_dev *d)
{
	int retval = -2;

	if(!d->inited)
		return -1;
	if(d->ops->stop)
		retval = d->ops->stop(&d->motor, d->priv);
	return retval;
}

int motor_run_backward(struct motor_dev *d, unsigned int mm)
{
	int retval = -2;
	unsigned int pulse = 0;

	if(!d->inited)
		return -1;
	/*
	 * TODO: convert mm to pulse value
	 */
	 pulse = mm + 10;

	 if(d->ops->run)
		 retval = d->ops->run(&d->motor, d->priv, pulse, 0);
	return retval;
}

int motor_run_forward(struct motor_dev *d, unsigned int mm)
{
	int retval = -2;
	unsigned int pulse = 0;

	if(!d->inited)
		return -1;
	/*
	 * TODO: convert mm to pulse value
	 */
	 pulse = mm + 10;

	 if(d->ops->run)
		 retval = d->ops->run(&d->motor, d->priv, pulse, 1);
	return retval;
}
