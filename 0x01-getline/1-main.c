#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(const int argc, const char *argv[])
{
	int fd;
	char *line;

	if (argc != 2)
	{
		printf("Usage: command file\n");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], 0);
	while ((line = _getline(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
