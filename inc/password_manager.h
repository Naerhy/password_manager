#ifndef __PASSWORD_MANAGER_H__
#define __PASSWORD_MANAGER_H__

#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h> // remove once printf is not mandatory anymore

#include "libny.h"

#define FILENAME BASE_DIR "passwords"
#define BACKUPS_DIR BASE_DIR "backups/"

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

typedef struct timeval timeval_st;

// exec.c
void exec_cmd(cmd_et cmd, int argc, char** argv, ny_list_st** items, size_t* next_id);

// exit.c
void exit_program(ny_list_st* items, char const* error_msg);
void delete_item(void* content);
void write_to_file(ny_list_st* items, size_t next_id);

// item.c
item_st* create_item(size_t id, char** data);

// log.c
int create_backup_file(void);

// parsing.c
cmd_et parse_cmd(char const* cmd);
void parse_file(ny_list_st** items, size_t* next_id);

#endif
