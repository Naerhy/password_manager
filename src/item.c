#include "password_manager.h"

item_st* create_item(size_t id, char** data)
{
	item_st* item;

	item = malloc(sizeof(item_st));
	if (!item)
		return NULL;
	item->id = id;
	item->website = ny_strdup(*data);
	item->username = ny_strdup(*(data + 1));
	item->email = ny_strdup(*(data + 2));
	item->password = ny_strdup(*(data + 3));
	if (!item->website || !item->username || !item->email || !item->password)
	{
		delete_item(item);
		return NULL;
	}
	return item;
}
