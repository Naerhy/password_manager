#include "password_manager.h"

void encrypt_rot13(char* str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str = 'A' + (*str - 'A' + 13) % 26;
		else if (*str >= 'a' && *str <= 'z')
			*str = 'a' + (*str - 'a' + 13) % 26;
		else
			// no action is needed
		str++;
	}
}
