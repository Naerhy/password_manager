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

void parse_file(ny_list_st** items, size_t* next_id)
{
	int fd;
	char* line;
	int error_status;
	item_st* item;
	ny_list_st* node;

	fd = open(FILENAME, O_RDONLY | O_CREAT, 0666);
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
			item = create_item(line);
			free(line);
			if (!item)
			{
				close(fd);
				exit_program(*items, "unable to allocate memory");
			}
			node = ny_list_new(item);
			if (!node)
			{
				free(item);
				close(fd);
				exit_program(*items, "unable to allocate memory");
			}
			ny_list_add(items, node);
		}
	}
	close(fd);
	if (error_status)
		exit_program(*items, "GNL error");
}
