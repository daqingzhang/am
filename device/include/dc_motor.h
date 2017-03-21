#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__

struct dc_motor
{
	unsigned char wire_a; //1 or 0
	unsigned char wire_b; //1 or 0
};

struct dc_motor_operations
{
	int (*init)(struct dc_motor *m, void *priv);
	int (*run)(struct dc_motor *m, void *priv, unsigned int pulse);
	int (*stop)(struct dc_motor *m, void *priv);
};

struct dc_motor_dev
{
	const char *name;
	int id;
	void *priv;
	struct dc_motor motor;
	struct dc_motor_operations *ops;
};

int dc_motor_register(struct dc_motor_dev *dev, struct dc_motor_operations *ops,
			const char *name, int id, void *priv);

int dc_motor_unregister(struct dc_motor_dev *dev);
int dc_motor_stop(struct dc_motor_dev *dev);
int dc_motor_run_backward(struct dc_motor_dev *dev, unsigned int mm);
int dc_motor_run_forward(struct dc_motor_dev *dev, unsigned int mm);

#endif
