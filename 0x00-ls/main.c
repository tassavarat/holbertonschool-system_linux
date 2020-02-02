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
	(void) argc;

	status = ls(argv);
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
		fprintf(stderr, "hls: invalid option -- '%c'\n", o);
		fprintf(stderr, "Try 'hls --help' for more information.\n");
	}
	else if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", argv);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", argv);
	if (errno > 0)
		perror(buf);
	if (e)
		exit(2);
	return (2);
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
 * checkoptions - checks for valid options and turns them on as necessary
 * @opt: structure of bools
 * @argv: string to check for options
 * @i: first index
 * @j: second index
 */
void checkoptions(struct option **opt, char *argv[], const unsigned int i,
		const unsigned int j)
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
			free(*opt);
			error(true, NULL, argv[i][j]);
	}
}
