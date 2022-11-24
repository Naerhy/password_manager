#include "password_manager.h"

void exit_program(ny_list_st* items, char const* error_msg)
{
	if (items)
		ny_list_clear(items, delete_item);
	if (error_msg)
	{
		ny_wrstr(2, "PwM: ");
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

static int write_id(int fd, size_t next_id)
{
	char* str_next_id;
	char* join;

	str_next_id = ny_itoa(next_id);
	if (!str_next_id)
		return 0;
	join = ny_strjoin("id=", str_next_id);
	free(str_next_id);
	if (!join)
		return 0;
	ny_wrstr_nl(fd, join);
	free(join);
	return 1;
}

static void sort_list(ny_list_st* items)
{
	ny_list_st* loop;
	item_st* x;
	item_st* y;
	void* temp;

	while (items)
	{
		loop = items->next;
		while (loop)
		{
			x = (item_st*)items->content;
			y = (item_st*)loop->content;
			if (ny_strcmp(x->website, y->website) > 0)
			{
				temp = items->content;
				items->content = loop->content;
				loop->content = temp;
			}
			loop = loop->next;
		}
		items = items->next;
	}
}

void write_to_file(ny_list_st* items, size_t next_id)
{
	int fd;
	ny_list_st* temp;
	item_st* item;
	char* id;
	char* join;

	fd = open(FILENAME, O_WRONLY | O_TRUNC);
	if (fd == -1)
		exit_program(items, "unable to open file descriptor");
	if (!write_id(fd, next_id))
	{
		close(fd);
		exit_program(items, "unable to allocate memory");
	}
	sort_list(items);
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
