#include "password_manager.h"

#include <stdio.h>

int main(int argc, char const** argv)
{
	ny_list_st* items;
	cmd_et cmd;

	if (argc < 2 || argc > 6)
		exit_program(NULL, "invalid number of arguments");
	cmd = parse_cmd(*(argv + 1));
	if (cmd == UNKNOWN)
		exit_program(NULL, "unknown command");
	items = NULL;
	parse_file(&items);
	write_to_file(items);
	ny_list_clear(items, delete_item);
	return 0;
}
