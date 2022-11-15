#ifndef __PASSWORD_MANAGER_H__
#define __PASSWORD_MANAGER_H__

#include <stdlib.h>

#include "libny.h"

typedef enum cmd_e
{
	ADD,
	DELETE,
	LIST,
	GET,
	UNKNOWN
} cmd_et;

typedef struct item_s
{
	size_t id;
	char* website;
	char* username;
	char* email;
	char* password;
} item_st;

cmd_et parse_cmd(char const* cmd);

void exit_program(ny_list_st* items, char const* error_msg);

#endif
