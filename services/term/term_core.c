#include <common.h>
#include "term_cmd.h"
#include "term_core.h"

#define TERM_LOG(...) do{ } while(0);

static term_cmd_t **term_cmds = NULL;
static int term_cmd_nr = 0;
static bool term_opened = false;

int term_open(void)
{
	TERM_LOG("%s:", __func__);

	if (!term_opened) {
		term_cmds = term_get_cmd_list(&term_cmd_nr);
		TERM_LOG("term_cmds=%x, term_cmd_nr=%d", (int)term_cmds, term_cmd_nr);
		term_print_cmd_list();
		term_opened = true;
	}
	//TODO: init uart & dma;

	//TODO: create thread for term
	return 0;
}

int term_close(void)
{
	TERM_LOG("%s:", __func__);

	if (term_opened) {
		term_opened = false;
	}
	return 0;
}

