#include <common.h>
#include <term_cmd.h>

#define TCMD_LOG(...) do{}while(0)

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

term_cmd_t **term_get_cmd_list(int *nr)
{
	if (nr) {
		*nr = ARRAY_SIZE(tcmd_list);
	}
	return tcmd_list;
}

int term_register_cmd_handler(enum TERM_CMD_ID_T id, term_cmd_handler_t handler)
{
	uint32_t i;

	for(i = 0 ; i < ARRAY_SIZE(tcmd_list); i++) {
		if (tcmd_list[i]->id == id) {
			if (tcmd_list[i]->handler != handler) {
				tcmd_list[i]->handler = handler;
				return 0;
			}
		}
	}
	return -1;
}

int term_deregister_cmd_handler(enum TERM_CMD_ID_T id)
{
	uint32_t i;

	for(i = 0 ; i < ARRAY_SIZE(tcmd_list); i++) {
		if (tcmd_list[i]->id == id && tcmd_list[i]->handler != NULL) {
			tcmd_list[i]->handler = NULL;
			return 0;
		}
	}
	return -1;
}

void term_print_cmd(enum TERM_CMD_ID_T id)
{
	term_cmd_t *c = NULL;
	uint32_t i;

	if (id >= TERM_CMD_ID_QTY) {
		return;
	}
	(void)c;
	for(i = 0 ; i < ARRAY_SIZE(tcmd_list); i++) {
		if (tcmd_list[i]->id == id) {
			c = tcmd_list[i];
			TCMD_LOG("term cmd: name=%s,id=%d,desc=%s,handler=%x",
				c->name,c->id,c->desc,(uint32_t)(c->handler));
		}
	}

}

void term_print_cmd_list(void)
{
	uint32_t i;

	for(i = 0 ; i < ARRAY_SIZE(tcmd_list); i++) {
		term_print_cmd(i);
	}
}
