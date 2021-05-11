#include <common.h>
#include <string.h>
#include "cqueue.h"

#define QUEUE_LOG(...) do {} while(0)

int cqueue_init(cqueue_t *q, uint8_t *buf, uint32_t item_size, uint32_t total_size)
{
	if (q == NULL || buf == NULL) {
		return -1;
	}
	if (item_size > total_size) {
		return -2;
	}
	if ((total_size % item_size) != 0) {
		return -3;
	}
	q->buf = buf;
	q->wpos = 0;
	q->rpos = 0;
	q->item_size = item_size;
	q->total_size = total_size;
	memset(q->buf, 0, q->total_size);
	return 0;
}

int cqueue_enqueue(cqueue_t *q, void *item)
{
	void *dst = (void *)(q->buf+q->wpos);

	memcpy(dst, item, q->item_size);
	q->wpos += q->item_size;
	if (q->wpos >= q->total_size) {
		q->wpos -= q->total_size;
	}
	return 0;
}

void *cqueue_dequeue(cqueue_t *q)
{
	void *src = NULL;
	uint32_t avail;

	if (q->wpos >= q->rpos) {
		avail = q->wpos - q->rpos;
	} else {
		avail = q->total_size - q->rpos + q->wpos;
	}
	if (avail >= q->item_size) {
		src = (void *)(q->buf + q->rpos);
		q->rpos += q->item_size;
		if (q->rpos >= q->total_size) {
			q->rpos -= q->total_size;
		}
	}
	return src;
}

void cqueue_dequeue2(cqueue_t *q, void *item)
{
	void *src = cqueue_dequeue(q);
	if (item) {
		memcpy(item, src, q->item_size);
	}
}

bool cqueue_is_empty(cqueue_t *q)
{
	uint32_t avail;

	if (q->wpos >= q->rpos) {
		avail = q->wpos - q->rpos;
	} else {
		avail = q->total_size - q->rpos + q->wpos;
	}
	return avail > 0 ? false : true;
}

uint32_t cqueue_get_total_size(cqueue_t *q)
{
	return q->total_size;
}

/* Command Queue Driver */
int cmd_queue_init(cqueue_t *q, uint8_t *buf, uint32_t total_size)
{
	return cqueue_init(q, buf, 4, total_size);
}

int cmd_queue_push(cqueue_t *q, uint32_t val)
{
	return cqueue_enqueue(q, &val);
}

uint32_t cmd_queue_pop(cqueue_t *q)
{
	return *(uint32_t*)cqueue_dequeue(q);
}

bool cmd_queue_is_empty(cqueue_t *q)
{
	return cqueue_is_empty(q);
}

uint32_t cmd_queue_total_size(cqueue_t *q)
{
	return cqueue_get_total_size(q);
}

#ifdef CMD_QUEUE_TEST
void cmd_queue_test(void)
{
	uint8_t buf[32];
	uint8_t d[32] = {0};
	cqueue_t queue;
	cqueue_t *q = &queue;

    (void)d[0];

	cmd_queue_init(q, buf, 8);

	cmd_queue_push(q, 0x10);
	cmd_queue_push(q, 0x11);
	cmd_queue_push(q, 0x12);
	cmd_queue_push(q, 0x13);
	cmd_queue_push(q, 0x14);
	cmd_queue_push(q, 0x15);
	cmd_queue_push(q, 0x16);
	cmd_queue_push(q, 0x17);

	d[0] = cmd_queue_pop(q);
	d[1] = cmd_queue_pop(q);
	d[2] = cmd_queue_pop(q);
	d[3] = cmd_queue_pop(q);
	d[4] = cmd_queue_pop(q);
	d[5] = cmd_queue_pop(q);
	d[6] = cmd_queue_pop(q);
	d[7] = cmd_queue_pop(q);
	QUEUE_LOG("pop: %x, %x, %x, %x, %x, %x, %x, %x",
		d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);

	cmd_queue_push(q, 0x18);
	d[8] = cmd_queue_pop(q);
	d[9] = cmd_queue_pop(q);
	QUEUE_LOG("pop: %x, %x", d[8],d[9]);

	cmd_queue_push(q,0x19);
	d[10] = cmd_queue_pop(q);
	QUEUE_LOG("pop: %x, %x", d[10]);
}
#endif

