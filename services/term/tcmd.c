#include <common.h>
#include <tcmd.h>

static int term_cmd_handler_help(int argc, char *argv[])
{
	return 0;
}

static int term_cmd_handler_quit(int argc, char *argv[])
{
	return 0;
}

static int term_cmd_handler_hello(int argc, char *argv[])
{
	return 0;
}

static int term_cmd_handler_test(int argc, char *argv[])
{
	return 0;
}

INIT_TERM_CMD(tcmd_help,  TERM_CMD_ID_HELP, "help", "help info", term_cmd_handler_help);
INIT_TERM_CMD(tcmd_quit,  TERM_CMD_ID_QUIT, "quit", "quit term", term_cmd_handler_quit);
INIT_TERM_CMD(tcmd_test,  TERM_CMD_ID_TEST, "test", "test term", term_cmd_handler_test);
INIT_TERM_CMD(tcmd_hello, TERM_CMD_ID_HELLO, "hello", "print hello", term_cmd_handler_hello);

static term_cmd_t *tcmd_list[] = {
	&tcmd_help,
	&tcmd_quit,
	&tcmd_test,
	&tcmd_hello,
};

int term_get_cmd_list(term_cmd_t **list)
{
	if (list) {
		list = tcmd_list;
	}
	return ARRAY_SIZE(tcmd_list);
}


int term_register_cmd_handler(enum TERM_CMD_ID_T id, term_cmd_handler_t handler)
{
	int ret = -1;
	uint32_t i;

	for(i = 0 ; i < ARRAY_SIZE(tcmd_list); i++) {
		if (tcmd_list[i]->id == id) {
			tcmd_list[i]->handler = handler;
			ret = 0;
			break;
		}
	}
	return ret;
}

int term_deregister_cmd_handler(enum TERM_CMD_ID_T id)
{
	int ret = -1;
	uint32_t i;

	for(i = 0 ; i < ARRAY_SIZE(tcmd_list); i++) {
		if (tcmd_list[i]->id == id) {
			tcmd_list[i]->handler = NULL;
			ret = 0;
			break;
		}
	}
	return ret;
}

