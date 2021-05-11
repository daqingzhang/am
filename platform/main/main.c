#include <string.h>
#include <common.h>
#include <app_init.h>

int main(void)
{
	printf("hello world\n");

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
