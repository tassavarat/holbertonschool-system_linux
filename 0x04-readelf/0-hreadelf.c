#include "helf.h"

/**
 * parse_args - checks for usage errors
 * @argc: number of arguments
 * @argv: pointer to array of characters containing arguments
 *
 * Return: pointer to file stream, otherwise NULL
 */
FILE *parse_args(int argc, char **argv)
{
	FILE *fp;

	if (argc != 2)
	{
		fprintf(stderr, "%s: Warning: Nothing to do.\n"
				"Usage: %s elf-file\n", *argv, *argv);
		goto out;
	}
	fp = fopen(argv[1], "rb");
	if (!fp)
	{
		fprintf(stderr, "%s: Error: '%s': No such file\n", argv[0],
				argv[1]);
out:
		return (NULL);
	}
	return (fp);
}

/**
 * main - calls parse_args and printelfh
 * @argc: number of arguments
 * @argv: pointer to array of characters containing arguments
 *
 * Return: 0 on success, otherwise 1
 */
int main(int argc, char **argv)
{
	FILE *fp;
	int exit_stat;

	fp = parse_args(argc, argv);
	if (!fp)
		return (1);
	exit_stat = printelfh(fp, *argv);
	return (exit_stat);
}
