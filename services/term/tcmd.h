#ifndef __TCMD_H__
#define __TCMD_H__

enum TERM_CMD_ID_T {
	TERM_CMD_ID_HELP,
	TERM_CMD_ID_QUIT,
	TERM_CMD_ID_TEST,
	TERM_CMD_ID_HELLO,

	TERM_CMD_ID_QTY,
};

typedef int (*term_cmd_handler_t)(int argc, char *argv[]);

typedef struct {
	int id;
	const char *name;
	const char *sname;
	const char *desc;
	term_cmd_handler_t handler;
} term_cmd_t;

#define INIT_TERM_CMD(_item, _id,_name,_desc,_handler) \
	static term_cmd_t _item = { \
		.id = _id, \
		.name = _name, \
		.sname = NULL, \
		.desc = _desc, \
		.handler = _handler, \
	}

int term_get_cmd_list(term_cmd_t **list);
int term_register_cmd_handler(enum TERM_CMD_ID_T cmd, term_cmd_handler_t handler);
int term_deregister_cmd_handler(enum TERM_CMD_ID_T cmd, term_cmd_handler_t handler);

#endif
