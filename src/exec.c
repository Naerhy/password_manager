#include "password_manager.h"

static void exec_add(char** argv, ny_list_st** items, size_t next_id)
{
	item_st* item;
	ny_list_st* node;

	if (!ny_strlen(*(argv + 2)) || !ny_strlen(*(argv + 3)) || !ny_strlen(*(argv + 4))
			|| !ny_strlen(*(argv + 5)))
		exit_program(*items, "invalid list of arguments");
	if (!create_backup_file())
		exit_program(*items, "unable to create log file");
	item = create_item(next_id, argv + 2);
	if (!item)
		exit_program(*items, "unable to allocate memory");
	node = ny_list_new(item);
	if (!node)
	{
		delete_item(item);
		exit_program(*items, "unable to allocate memory");
	}
	ny_list_add(items, node);
}

static bool is_valid_id(char const* str)
{
	if (ny_strlen(str) > 5)
		return FALSE;
	while (*str)
	{
		if (!ny_isdigit(*str))
			return FALSE;
		str++;
	}
	return TRUE;
}

static void exec_delete(ny_list_st** head, ny_list_st* items, char const* str_id)
{
	size_t id;
	ny_list_st* temp;
	item_st* item;

	if (!create_backup_file())
		exit_program(items, "unable to create log file");
	id = ny_atoi(str_id);
	while (items)
	{
		temp = items->next;
		item = (item_st*)items->content;
		if (item->id == id)
			ny_list_delete(head, items, delete_item);
		items = temp;
	}
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

void exec_cmd(cmd_et cmd, int argc, char** argv, ny_list_st** items, size_t* next_id)
{
	if (cmd == ADD && argc == 6)
	{
		exec_add(argv, items, *next_id);
		(*next_id)++;
	}
	else if (cmd == DELETE && argc == 3 && is_valid_id(*(argv + 2)))
		exec_delete(items, *items, *(argv + 2));
	else if (cmd == LIST)
		exec_list(*items);
	else if (cmd == GET && argc == 3)
		exec_get(*items, *(argv + 2));
	else
		exit_program(*items, "invalid arguments");
}
