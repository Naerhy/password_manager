#include "password_manager.h"

item_st* create_item(char const* line)
{
	char** split;
	item_st* item;

	split = ny_split(line, ' ');
	if (!split)
		return NULL;
	item = malloc(sizeof(item_st));
	if (!item)
	{
		ny_free_double_ptr((void**)split, 5);
		return NULL;
	}
	item->id = ny_atoi(*split);
	item->website = ny_strdup(*(split + 1));
	item->username = ny_strdup(*(split + 2));
	item->email = ny_strdup(*(split + 3));
	item->password = ny_strdup(*(split + 4));
	ny_free_double_ptr((void**)split, 5);
	if (!item->website || !item->username || !item->email || !item->password)
	{
		delete_item(item);
		return NULL;
	}
	return item;
}
