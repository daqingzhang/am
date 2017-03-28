#ifndef __MOTOR_H__
#define __MOTOR_H__

struct motor
{
	int wire_a;
	int wire_b;
	int wire_c;
	int wire_d;
};

struct motor_operations
{
	int (*init)(struct motor *m, void *priv);
	int (*run)(struct motor *m, void *priv, unsigned int pulse,int forward);
	int (*stop)(struct motor *m, void *priv);
};

struct motor_dev
{
	const char *name;
	int id;
	int inited;
	void *priv;
	struct motor motor;
	struct motor_operations *ops;
};

int motor_register(struct motor_dev *d, struct motor_operations *ops,
			const char *name, int id,void *priv);
int motor_unregister(struct motor_dev *d);
int motor_stop(struct motor_dev *d);
int motor_run_backward(struct motor_dev *d, unsigned int mm);
int motor_run_forward(struct motor_dev *d, unsigned int mm);

#endif
