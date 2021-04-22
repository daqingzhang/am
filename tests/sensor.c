#include <sensor.h>

static void init_sensor(struct sensor *sen, int val)
{
	sen->value = val;
}

int sensor_register(struct sensor_dev *d, struct sensor_operations *ops,
			const char *name, int id, void *priv)
{
	if((!d) || (!ops))
		return -1;

	d->inited = 1;
	d->ops = ops;
	d->name = name;
	d->id = id;
	d->priv = priv;

	init_sensor(&d->sen,0);

	if(d->ops->init)
		return d->ops->init(&d->sen, d->priv);
	return 0;
}

int sensor_unregister(struct sensor_dev *d)
{
	d->inited = 0;
	return 0;
}

int sensor_read(struct sensor_dev *d, int *pdata)
{
	int retval;

	if((!d->inited) || (!d->ops->read))
		return -1;

	retval = d->ops->read(&d->sen, d->priv);
	if(retval)
		return retval;
	*pdata = d->sen.value;
	return 0;
}

int sensor_write(struct sensor_dev *d, int val)
{
	int retval;

	if((!d->inited) || (!d->ops->write))
		return -1;

	d->sen.value = val;
	retval = d->ops->write(&d->sen, d->priv);
	if(retval)
		return retval;
	return 0;
}

int sensor_config(struct sensor_dev *d, int cmd)
{
	if((!d->inited) || (!d->ops->config))
		return -1;
	return d->ops->config(&d->sen, d->priv, cmd);
}
