#include "hls.h"

/**
 * cleanup - performs cleanup
 * @entries: entry struct
 * @dirs: directories to free
 */
void cleanup(struct content *entries, struct content *dirs)
{
	free(dirs);
	free(entries);
}

/**
 * error - prints error messages
 * @arg: string containing invalid argument
 * @e: whether function should exit
 *
 * Return: error status
 */
size_t error(char *arg, bool e)
{
	char buf[256];

	if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", arg);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", arg);
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
