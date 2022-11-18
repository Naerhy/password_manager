#ifndef __PASSWORD_MANAGER_H__
#define __PASSWORD_MANAGER_H__

#include <stdlib.h>
#include <fcntl.h>

#include "libny.h"

#define FILENAME ".passwords"

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

// exit.c
void exit_program(ny_list_st* items, char const* error_msg);
void delete_item(void* content);
void write_to_file(ny_list_st* items, size_t next_id);

// item.c
item_st* create_item(char const* line);

// parsing.c
cmd_et parse_cmd(char const* cmd);
void parse_file(ny_list_st** items, size_t* next_id);

#endif
