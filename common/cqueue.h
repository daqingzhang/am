#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t *buf;
	uint32_t wpos;
	uint32_t rpos;
	uint32_t item_size;
	uint32_t total_size;
} cqueue_t;

int cqueue_init(cqueue_t *q, uint8_t *buf, uint32_t item_size, uint32_t total_size);
int cqueue_enqueue(cqueue_t *q, void *item);
void *cqueue_dequeue(cqueue_t *q);
void cqueue_dequeue2(cqueue_t *q, void *item);
bool cqueue_is_empty(cqueue_t *q);
uint32_t cqueue_get_total_size(cqueue_t *q);

int cmd_queue_init(cqueue_t *q, uint8_t *buf, uint32_t total_size);
int cmd_queue_push(cqueue_t *q, uint32_t val);
uint32_t cmd_queue_pop(cqueue_t *q);
bool cmd_queue_is_empty(cqueue_t *q);
uint32_t cmd_queue_total_size(cqueue_t *q);

void cmd_queue_test(void);
#endif
