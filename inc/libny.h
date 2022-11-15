#ifndef __LIBNY_H__
#define __LIBNY_H__

#include <stdlib.h>
#include <unistd.h>

#define GNL_BUFSIZE 1000

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct ny_list_s
{
	void* content;
	struct ny_list_s* next;
} ny_list_st;

char* ny_strdup(char const* src, size_t length);

char* ny_strcpy(char* dest, char const* src, size_t n);

char *ny_strcat(char* dest, char const* src, size_t n);

char* ny_strjoin(char const* s1, char const* s2);

int ny_strcmp(char const* s1, char const* s2);

int ny_strncmp(char const* s1, char const* s2, size_t n);

size_t ny_strlen(char const* str);

char** ny_split(char const* str, char c);

void ny_wrstr_nl(int fd, char const* str);

void ny_free_double_ptr(void** dptr, size_t size);

ny_list_st* ny_list_new(void* content);

void ny_list_add(ny_list_st** list, ny_list_st* new);

void ny_list_delete(ny_list_st** list, ny_list_st* node, void (*delete)(void*));

void ny_list_clear(ny_list_st* list, void (*delete)(void*));

ny_list_st* ny_list_last(ny_list_st* list);

size_t ny_list_size(ny_list_st const* list);

size_t ny_list_pos(ny_list_st const* list, ny_list_st const* node);

ny_list_st* ny_list_nth(ny_list_st* list, size_t pos);

char* ny_get_next_line(int fd, int* error_status);

#endif
