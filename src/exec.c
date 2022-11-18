#include "password_manager.h"

static void exec_add(char const** argv, ny_list_st** items, size_t next_id)
{
	char* str_next_id;
	char* line;
	item_st* item;
	ny_list_st* node;

	if (!ny_strlen(*(argv + 2)) || !ny_strlen(*(argv + 3)) || !ny_strlen(*(argv + 4))
			|| !ny_strlen(*(argv + 5)))
		exit_program(*items, "invalid list of arguments");
	str_next_id = ny_itoa(next_id);
	if (!str_next_id)
		exit_program(*items, "unable to allocate memory");
	line = ny_strjoin_var(9, str_next_id, " ", *(argv + 2), " ", *(argv + 3), " ",
			*(argv + 4), " ", *(argv + 5));
	free(str_next_id);
	if (!line)
		exit_program(*items, "unable to allocate memory");
	item = create_item(line);
	free(line);
	if (!item)
		exit_program(*items, "unable to allocate memory");
	node = ny_list_new(item);
	if (!node)
	{
		free(item);
		exit_program(*items, "unable to allocate memory");
	}
	ny_list_add(items, node);
}

static void exec_list(ny_list_st* items)
{
	item_st* item;

	while (items)
	{
		item = (item_st*)items->content;
		printf("%ld | %s | %s | %s | %s\n", item->id, item->website, item->username,
				item->email, item->password);
		items = items->next;
	}
}

static void exec_get(ny_list_st* items, char const* to_find)
{
	item_st* item;

	while (items)
	{
		item = (item_st*)items->content;
		if (!ny_strcmp(item->website, to_find))
			printf("%ld | %s | %s | %s | %s\n", item->id, item->website, item->username,
					item->email, item->password);
		items = items->next;
	}
}

void exec_cmd(cmd_et cmd, int argc, char const** argv, ny_list_st** items, size_t* next_id)
{
	if (cmd == ADD && argc == 6)
	{
		exec_add(argv, items, *next_id);
		(*next_id)++;
	}
	// else if (cmd == DELETE && argc == 3 && is_valid_id(*(argv + 2)));
	else if (cmd == LIST)
		exec_list(*items);
	else if (cmd == GET && argc == 3)
		exec_get(*items, *(argv + 2));
	else
		exit_program(*items, "invalid arguments");
}
