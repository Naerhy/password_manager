#include "password_manager.h"

void exit_program(ny_list_st* items, char const* error_msg)
{
	if (items)
		ny_list_clear(items, delete_item);
	if (error_msg)
	{
		ny_wrstr_nl(2, error_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void delete_item(void* content)
{
	item_st* item;

	item = content;
	free(item->website);
	free(item->username);
	free(item->email);
	free(item->password);
	free(item);
}

void write_to_file(ny_list_st* items)
{
	int fd;
	ny_list_st* temp;
	item_st* item;
	char* id;
	char* join;

	fd = open(FILENAME, O_WRONLY | O_TRUNC);
	if (fd == -1)
		exit_program(items, "unable to open file");
	temp = items;
	while (items)
	{
		item = (item_st*)items->content;
		id = ny_itoa(item->id);
		if (!id)
		{
			close(fd);
			exit_program(temp, "unable to allocate memory");
		}
		join = ny_strjoin_var(9, id, " ", item->website, " ", item->username, " ",
				item->email, " ", item->password);
		free(id);
		if (!join)
		{
			close(fd);
			exit_program(temp, "unable to allocate memory");
		}
		ny_wrstr_nl(fd, join);
		free(join);
		items = items->next;
	}
	close(fd);
}
