#include "helf.h"

/**
 * convertmsb - converts to big endian
 * @ptr: pointer to first octet of word
 * @size: size of type ptr points to
 */
void convertmsb(char *ptr, size_t size)
{
	size_t tmp, start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		tmp = ptr[start];
		ptr[start] = ptr[end];
		ptr[end] = tmp;
	}
}

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
	struct stat sb;

	if (argc != 2)
	{
		fprintf(stderr, "%s: Warning: Nothing to do.\n"
				"Usage: %s elf-file\n", *argv, *argv);
		goto out;
	}
	stat(argv[1], &sb);
	if (!S_ISREG(sb.st_mode))
	{
		fprintf(stderr, "%s: Error: '%s': is not an ordinary file\n",
				argv[0], argv[1]);
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
