#ifndef __FSM_V2_H__
#define __FSM_V2_H__

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

enum fsm_comm_route
{
	FSM_COMM_R0 = 0,
	FSM_COMM_R1,
	FSM_COMM_R2,
	FSM_COMM_R3,
	FSM_COMM_R4,
	FSM_COMM_R5,
	FSM_COMM_R6,
	FSM_COMM_R7,
	FSM_COMM_R8,
	FSM_COMM_R9,
	FSM_COMM_R10,
	FSM_COMM_R11,
	FSM_COMM_R12,
	FSM_COMM_R13,
	FSM_COMM_R14,
	FSM_COMM_R15,
	FSM_COMM_R16,
	FSM_COMM_R17,
	FSM_COMM_R18,
	FSM_COMM_R19,
	FSM_COMM_R20,
	FSM_COMM_R21,
	FSM_COMM_R22,
	FSM_COMM_R23,
	FSM_COMM_R24,
	FSM_COMM_R25,
};

enum fsm_comm_state
{
	FSM_COMM_S0 = 0,
	FSM_COMM_S1,
	FSM_COMM_S2,
	FSM_COMM_S3,
	FSM_COMM_S4,
	FSM_COMM_S5,
	FSM_COMM_S6,
	FSM_COMM_S7,
	FSM_COMM_S8,
	FSM_COMM_S9,
	FSM_COMM_S10,
	FSM_COMM_S11,
	FSM_COMM_S12,
	FSM_COMM_S13,
	FSM_COMM_S14,
	FSM_COMM_S15,
	FSM_COMM_S16,
	FSM_COMM_S17,
	FSM_COMM_S18,
	FSM_COMM_S19,
	FSM_COMM_S20,
	FSM_COMM_S21,
	FSM_COMM_S22,
	FSM_COMM_S23,
	FSM_COMM_S24,
	FSM_COMM_S25,

};

#define FSM_R_END -1
#define FSM_S_END -1

#define FSM_ERR_FAULT	 1
#define FSM_ERR_INVAL	 2
#define FSM_ERR_INITED	 3
#define FSM_ERR_NOINITED 4

struct fsm_state
{
	int current;
	int route;
	int next;
};

struct fsm_operations
{
	int (*init)(struct fsm_state *s, void *priv);
	int (*run)(struct fsm_state *s, void *priv);
	int (*debug)(struct fsm_state *s, void *priv);
};

struct fsm_device
{
	int inited;
	void *priv;
	const char *name;
	struct fsm_state s;
	const struct fsm_state *map;
	struct fsm_operations *ops;
};

#define fsm_device_to_state(dev) (&(dev->s))
#define fsm_device_to_priv(dev) (dev->priv)
#define fsm_device_to_map(dev)	(dev->map)

int fsm_register(struct fsm_device *dev, const char *name,
		struct fsm_operations *ops, const struct fsm_state *map, void *priv);
int fsm_unregister(struct fsm_device *dev);
int fsm_init(struct fsm_device *dev);
int fsm_run(struct fsm_device *dev);
int fsm_debug(struct fsm_device *dev);

int fsm_get_current_state(struct fsm_device *dev);
int fsm_search(struct fsm_device *dev,int route);
int fsm_update(struct fsm_device *dev);

#endif /*__FSM_V2_H__ */
