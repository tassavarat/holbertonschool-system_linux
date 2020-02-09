#include "_getline.h"
#include <stdio.h> /* remove me */

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: null-terminated string excluding newline character
 * NULL on EOF or error
 */
char *_getline(const int fd)
{
	char buf[READ_SIZE] = {0};
	char *line;
	size_t i, nl, linsiz;
	ssize_t bytrd;
	static char readover[READ_SIZE];
	static size_t start;

	nl = 0;
	linsiz = READ_SIZE * 2;
	line = calloc(linsiz, sizeof(*line));
	if (!line)
		return (NULL);
	if (start)
		strcpy(line, readover);
	start = 1;
	while ((bytrd = read(fd, buf, READ_SIZE)) > 0)
	{
		for (i = 0; buf[i] && buf[i] != '\n'; ++i)
			;
		if (buf[i] == '\n')
		{
			strcpy(readover, buf + i + 1);
			buf[i] = '\0';
			nl = 1;
		}
		strcat(line, buf);
		linsiz += READ_SIZE;
		if (nl)
			break;
		line = realloc(line, linsiz + sizeof(*line));
	}
	if (bytrd <= 0)
	{
		printf("Error\n");
		free(line);
		return (NULL);
	}
	return (line);
}
