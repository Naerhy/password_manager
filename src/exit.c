#include "password_manager.h"

static void delete_item(void* content)
{
	item_st* item;

	item = content;
	free(item->website);
	free(item->username);
	free(item->email);
	free(item->password);
	free(item);
}

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
