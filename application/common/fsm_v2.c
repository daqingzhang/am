#include <fsm_v2.h>

int fsm_register(struct fsm_device *dev, const char *name,
		struct fsm_operations *ops, const struct fsm_state *map, void *priv)
{
	if((!dev) || (!ops) || (!map))
		return -FSM_ERR_INVAL;
	if(dev->inited)
		return -FSM_ERR_INITED;

	dev->inited = TRUE;
	dev->name = name;
	dev->ops = ops;
	dev->map = map;
	dev->priv = priv;

	if(!dev->ops->init)
		return 0;

	return dev->ops->init(&dev->s,priv);
}

int fsm_unregister(struct fsm_device *dev)
{
	dev->inited = FALSE;
	return 0;
}

int fsm_init(struct fsm_device *dev)
{
	struct fsm_state *s = fsm_device_to_state(dev);
	void *p = fsm_device_to_priv(dev);

	if(dev->inited)
		return -FSM_ERR_INITED;
	if(!dev->ops->init)
		return -FSM_ERR_INVAL;
	dev->inited = TRUE;
	return dev->ops->init(s,p);
}

static void fsm_state_copy(struct fsm_state *des, struct fsm_state *src)
{
	des->current	= src->current;
	des->next 	= src->next;
	des->route	= src->route;
}

int fsm_debug(struct fsm_device *dev)
{
	struct fsm_state c,*s = fsm_device_to_state(dev);
	void *p = fsm_device_to_priv(dev);

	if(!dev->ops->debug)
		return -1;

	fsm_state_copy(&c,s);
	return dev->ops->debug(&c,p);
}

int fsm_run(struct fsm_device *dev)
{
	struct fsm_state c;
	struct fsm_state *s = fsm_device_to_state(dev);
	void *p = fsm_device_to_priv(dev);

	if(dev->inited != TRUE)
		return -FSM_ERR_NOINITED;
	if(!dev->ops->run)
		return -FSM_ERR_INVAL;

	fsm_state_copy(&c,s);
	return dev->ops->run(&c,p);
}

/**
 * fsm_search() - Search a new state by the route value. This must be called
 * at least once before switch to the new state.
 *
 * @dev :	Device pointer
 * @route:	Route value for finding next state
 *
 * @return:	0(success) or -1(failed)
 */

int fsm_search(struct fsm_device *dev, int route)
{
	struct fsm_state *s = fsm_device_to_state(dev);
	const struct fsm_state *map = fsm_device_to_map(dev);

	while(map != NULL) {
		if(map->current < 0)
			break;
		if((map->current == s->current) && (map->route == route)) {
			s->next = map->next;
			s->route = route;
			return 0;
		}
		map++;
	}
	return -1;
}

/**
 * fsm_update() - Switch current state to new state. Before the state switches
 * we need to search the new state by calling fsm_search().
 *
 * @dev :	Device pointer will be updated
 *
 * @return:	0(success) or -1(failed)
 */

int fsm_update(struct fsm_device *dev)
{
	struct fsm_state *s = fsm_device_to_state(dev);

	if(s->next < 0)
		return -1;

	s->current = s->next;
	return 0;
}

/**
 * fsm_get_current_state() - Get the current state value
 * @dev :	Device pointer
 *
 * @return:	Current state value
 */
int fsm_get_current_state(struct fsm_device *dev)
{
	struct fsm_state *s = fsm_device_to_state(dev);
	return s->current;
}
