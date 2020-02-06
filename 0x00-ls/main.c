#include "hls.h"

/**
 * checkopt - checks for valid options and turns them on as necessary
 * @opt: structure of bools
 * @argv: string to check for options
 * @i: first index
 * @j: second index
 */
void checkopt(struct option **opt, char *argv[], size_t i, size_t j)
{
	switch (argv[i][j])
	{
		case '1':
			(*opt)->perline = true;
			break;
		case 'a':
			(*opt)->hidden = true;
			break;
		case 'A':
			(*opt)->hiddenavigation = true;
			break;
		case 'l':
			(*opt)->longfmt = true;
			break;
		case 'r':
			(*opt)->rev = true;
			break;
		case 'S':
			(*opt)->sortsize = true;
			break;
		case 't':
			(*opt)->sorttime = true;
			break;
		case 'R':
			(*opt)->recurs = true;
			break;
		default:
			cleanup(NULL, NULL, *opt);
			error(NULL, argv[i][j], true, false);
	}
}

/**
 * initoptions - initialises option struct
 * @opt: struct to initialise
 */
void initoptions(struct option **opt)
{
	(*opt)->perline = false;
	(*opt)->hidden = false;
	(*opt)->hiddenavigation = false;
	(*opt)->longfmt = false;
	(*opt)->rev = false;
	(*opt)->sortsize = false;
	(*opt)->sorttime = false;
	(*opt)->recurs = false;
}

/**
 * cleanup - performs cleanup
 * @entries: entry struct to free
 * @dirs: directories to free
 * @opt: option struct to free
 */
void cleanup(struct content *entries, struct content *dirs, struct option *opt)
{
	if (dirs)
		free(dirs);
	if (entries)
		free(entries);
	if (opt)
		free(opt);
}

/**
 * error - prints error messages
 * @arg: string containing invalid argument
 * @op: invalid char option
 * @e: whether function should exit
 * @printed: whether print has occured
 *
 * Return: error status
 */
size_t error(char *arg, char op, bool e, bool printed)
{
	char buf[256];

	if (printed)
		printf("\n");
	if (!arg)
	{
		fprintf(stderr, "hls: invalid option -- '%c'\n", op);
		fprintf(stderr, "Try 'hls --help' for more information.\n");
	}
	else if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", arg);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", arg);
	if (errno > 0)
		perror(buf);
	if (e)
		exit(2);
	return (2);
}

/**
 * main - entry point to ls program
 * @argc: number of arguments
 * @argv: pointer to an array of strings
 *
 * Return: 0 on success, error will exit with value of 2
 */
int main(int argc, char *argv[])
{
	size_t status;
	(void) argc;

	status = ls(argv);
	return (status);
}
