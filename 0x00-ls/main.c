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
	exit(status);
}

/**
 * error - prints error messages
 * @argv: string containing invalid argument
 * @o: character containing invalid ls option
 *
 * Return: error status
 */
unsigned int error(char *argv, char o)
{
	char buf[BUFSIZ];

	/* printf("errno =  %d\n", errno); */
	if (!argv)
	{
		fprintf(stderr, "ls: invalid option -- '%c'\n", o);
		fprintf(stderr, "Try 'ls --help' for more information.\n");
		exit(2);
	}
	if (errno == ENOENT)
		sprintf(buf, "ls: cannot access %s", argv);
	else if (errno == EACCES)
		sprintf(buf, "ls: cannot open directory %s", argv);
	perror(buf);
	return (2);
}
