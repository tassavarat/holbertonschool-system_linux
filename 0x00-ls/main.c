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
