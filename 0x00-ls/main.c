#include "hls.h"

/**
 * main - entry point to ls program
 * @argc: number of arguments
 * @argv: pointer to an array of strings
 *
 * Return: 0 on success, error will exit with value of 2
 */
int main(int argc, char *argv[])
{
	unsigned int status;

	status = ls(argc, argv);
	return (status);
}

/**
 * error - prints error messages
 * @e: whether function should exit
 * @argv: string containing invalid argument
 * @o: character containing invalid ls option
 *
 * Return: error status
 */
unsigned int error(bool e, char *argv, char o)
{
	char buf[BUFSIZ];

	/* printf("errno =  %d\n", errno); */
	if (!argv)
	{
		fprintf(stderr, "ls: invalid option -- '%c'\n", o);
		fprintf(stderr, "Try 'ls --help' for more information.\n");
	}
	else if (errno == ENOENT)
		sprintf(buf, "ls: cannot access %s", argv);
	else if (errno == EACCES)
		sprintf(buf, "ls: cannot open directory %s", argv);
	perror(buf);
	if (e)
		exit(2);
	return (2);
}

/**
 * handlecontent - allocates space for struct containing content information
 * @f: if content is a file
 * @c: count of content
 * @argv: pointer to array of strings containing name of content
 * @a: pointer to array of integers containing index of content
 *
 * Return: created struct
 */
content_t *handlecontent(const bool f, const unsigned int c, char *argv[],
		int *a)
{
	unsigned int i;
	struct content *entries;

	entries = malloc(c * sizeof(*entries));
	for (i = 0; i < c; ++i)
		_strcpy(entries[i].name, argv[a[i]]);
	if (f)
	{
		printcontent(0, NULL, c, entries);
		free(entries);
		return (NULL);
	}
	return (entries);
}
