#include <common.h>
#include "services.h"
#include "term_core.h"

int services_init(void)
{
#ifdef SVR_MOD_TERM
	term_open();
#endif
	return 0;
}

