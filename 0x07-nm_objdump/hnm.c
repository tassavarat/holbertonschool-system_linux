#include "helf.h"

/**
 * conv_msb - convert to big endian by reversing given array
 * @ptr: pointer to first octet of word
 * @size: size of type ptr points to
 */
void conv_msb(char *ptr, size_t size)
{
	size_t start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		ptr[start] ^= ptr[end];
		ptr[end] ^= ptr[start];
		ptr[start] ^= ptr[end];
	}
}

/**
 * getelf - get ELF information
 * @fp: pointer to file stream
 * @prog_name: name of program
 * @arg_str: pointer to name of file to get ELF information from
 * @exit_stat: current exit status to update accordingly
 */
void getelf(FILE *fp, char *prog_name, char *arg_str, int *exit_stat)
{
	hdrs hdr;
	struct stat sb;

	memset(&hdr, 0, sizeof(hdr));
	if (stat(arg_str, &sb))
		goto prnterr;
	hdr.addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
			fileno(fp), 0);
	if (hdr.addr == MAP_FAILED)
	{
prnterr:
		perror(NULL);
		goto out;
	}
	init_ehdr(&hdr);
	if (memcmp(hdr.Ehdr64->e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: %s: file format not recognized\n",
				prog_name, arg_str);
out:
		*exit_stat = 1;
		fclose(fp);
		return;
	}
	init_shdr(&hdr);
	if (!sym(&hdr))
		fprintf(stderr, "%s: %s: no symbols\n",
				prog_name, arg_str);
	fclose(fp);
}

/**
 * parse_args - check for usage errors
 * @argc: count of arguments
 * @argv: pointer to array containing arguments
 * @i: index for argv
 *
 * Return: pointer to file stream, otherwise NULL
 */
FILE *parse_args(int argc, char *argv[], int i)
{
	FILE *fp;
	struct stat sb;

	if (argc == 1)
		argv[1] = "a.out";
	stat(argv[i], &sb);
	if (S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "%s: Warning: '%s' is a directory\n",
				argv[0], argv[i]);
		return (NULL);
	}
	fp = fopen(argv[i], "rb");
	if (!fp)
	{
		fprintf(stderr, "%s: '%s': No such file\n", argv[0], argv[i]);
		return (NULL);
	}
	return (fp);
}

/**
 * main - entry point
 * @argc: count of arguments
 * @argv: pointer to an array containing arguments
 *
 * Return: 0 on success, otherwise 1
 */
int main(int argc, char *argv[])
{
	FILE *fp;
	int exit_stat = 0, i = 1;

	do {
		fp = parse_args(argc, argv, i);
		if (!fp)
			exit_stat = 1;
		else
			getelf(fp, argv[0], argv[i], &exit_stat);
	} while (++i < argc);
	return (exit_stat);
}
