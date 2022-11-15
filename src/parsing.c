#include "password_manager.h"

cmd_et parse_cmd(char const* cmd)
{
	if (!ny_strcmp(cmd, "add"))
		return ADD;
	else if (!ny_strcmp(cmd, "delete"))
		return DELETE;
	else if (!ny_strcmp(cmd, "list"))
		return LIST;
	else if (!ny_strcmp(cmd, "get"))
		return GET;
	else
		return UNKNOWN;
}
