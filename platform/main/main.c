#include <string.h>
#include <common.h>
#include <app_init.h>

#define SAMPLE_TEST

#ifdef SAMPLE_TEST
void sample_test(void)
{
	int tick = 0;

	do {
		printf("hello world, %d",++tick);
		mdelay(1000);
	} while(1);
}
#endif

int main(void)
{
	printf("hello world\n");

#ifdef SAMPLE_TEST
	sample_test();
#endif
#ifdef CMD_QUEUE_TEST
	cmd_queue_test();
#endif

	app_init(0, NULL);

	for(;;) {
		//TODO: do sth
	}

	return 0;
}

int _start(void)  __attribute__((weak,alias("main")));
