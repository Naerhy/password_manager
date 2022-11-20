#include "password_manager.h"

int main(int argc, char** argv)
{
	cmd_et cmd;
	ny_list_st* items;
	size_t next_id;

	if (argc < 2 || argc > 6)
		exit_program(NULL, "invalid number of arguments");
	cmd = parse_cmd(*(argv + 1));
	if (cmd == UNKNOWN)
		exit_program(NULL, "unknown command");
	items = NULL;
	next_id = 0;
	parse_file(&items, &next_id);
	exec_cmd(cmd, argc, argv, &items, &next_id);
	write_to_file(items, next_id);
	ny_list_clear(items, delete_item);
	return 0;
}
