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

static int parse_item_line(char* line, ny_list_st** items)
{
	char** split;
	item_st* item;
	ny_list_st* node;

	split = ny_split(line, ' ');
	free(line);
	if (!split)
		return 0;
	item = create_item(ny_atoi(*split), split + 1);
	ny_free_double_ptr((void**)split, 5);
	if (!item)
		return 0;
	node = ny_list_new(item);
	if (!node)
	{
		delete_item(item);
		return 0;
	}
	ny_list_add(items, node);
	return 1;
}

void parse_file(ny_list_st** items, size_t* next_id)
{
	int fd;
	char* line;
	int error_status;

	fd = open(FILENAME, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		exit_program(NULL, "unable to open file descriptor");
	error_status = 0;
	while (1)
	{
		line = ny_get_next_line(fd, &error_status);
		if (!line)
			break;
		if (!ny_strncmp(line, "id=", 3))
		{
			*next_id = (size_t)ny_atoi(line + 3);
			free(line);
		}
		else
		{
			encrypt_rot13(line);
			if (!parse_item_line(line, items))
			{
				close(fd);
				exit_program(*items, "unable to allocate memory");
			}
		}
	}
	close(fd);
	if (error_status)
		exit_program(*items, "GNL error");
}
