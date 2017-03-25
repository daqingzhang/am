#ifndef __SENSOR_H__
#define __SENSOR_H__

struct sensor
{
	int value;
};

struct sensor_operations
{
	int (*init)(struct sensor *sen, void *priv);
	int (*read)(struct sensor *sen, void *priv);
	int (*write)(struct sensor *sen, void *priv);
	int (*config)(struct sensor *sen, void *priv, int cmd);
};

struct sensor_dev {
	const char *name;
	int id;
	int inited;
	void *priv;
	struct sensor sen;
	struct sensor_operations *ops;
};

int sensor_register(struct sensor_dev *d, struct sensor_operations *ops,
			const char *name, int id, void *priv);
int sensor_unregister(struct sensor_dev *d);
int sensor_read(struct sensor_dev *d, int *pval);
int sensor_write(struct sensor_dev *d, int val);
int sensor_config(struct sensor_dev *d, int cmd);
#endif
