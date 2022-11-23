#include "password_manager.h"

static char* get_filename(void)
{
	timeval_st tv;
	char* time_str;
	char* join;

	gettimeofday(&tv, NULL);
	time_str = ny_itoa(tv.tv_sec);
	if (!time_str)
		return NULL;
	join = ny_strjoin(BACKUPS_DIR, time_str);
	free(time_str);
	if (!join)
		return NULL;
	return join;
}

int create_backup_file(void)
{
	char* filename;
	int fd_out;
	int fd_in;
	char* line;
	int error_status;

	filename = get_filename();
	if (!filename)
		return 0;
	fd_in = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	free(filename);
	if (fd_in == -1)
		return 0;
	fd_out = open(FILENAME, O_RDONLY);
	if (fd_out == -1)
	{
		close(fd_in);
		return 0;
	}
	error_status = 0;
	while (1)
	{
		line = ny_get_next_line(fd_out, &error_status);
		if (!line)
			break;
		ny_wrstr_nl(fd_in, line);
		free(line);
	}
	close(fd_out);
	close(fd_in);
	if (error_status)
		return 0;
	return 1;
}
