#include "hls.h"

/**
 * printfile - prints and formats files
 * @entries: pointer content entries to print
 * @c: count of entries
 */
void printfile(struct content *entries, size_t c)
{
	size_t i;
	static bool start;

	for (i = 0; i < c; ++i)
	{
		if (start)
			printf("  ");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
}

/**
 * handlecontent - creates entries and prints if file
 * @f: if file
 * @argv: pointer to array of arguments
 * @a: pointer to array of file or directory indexes
 * @c: content count
 * @printed: if files have been printed
 *
 * Return: created entries or NULL if file
 */
content *handlecontent(bool f, char *argv[], size_t *a, size_t c,
		bool *printed)
{
	size_t i;
	struct content *entries;

	entries = malloc(c * sizeof(*entries));
	for (i = 0; i < c; ++i)
		_strcpy(entries[i].name, argv[a[i]]);
	if (f)
	{
		printfile(entries, c);
		*printed = true;
		cleanup(entries, NULL, NULL);
	}
	return (entries);
}

/**
 * processargs - process arguments
 * @dirs: pointer to pointer of directories
 * @opt: pointer to options struct
 * @argv: pointer to array of arguments
 * @file_a: pointer to array containing file indexes
 * @dir_a: pointer to array containing directory indexes
 * @status: current error status
 * @dp: pointer to directory pointer
 * @fc: file count
 * @dc: directory count
 * @erc: error count
 * @printed: if files have been printed
 *
 * Return: error status
 */
size_t processargs(struct content **dirs, struct option *opt, char *argv[],
		size_t *file_a, size_t *dir_a, size_t status, DIR **dp,
		size_t fc, size_t dc, size_t erc, bool *printed)
{
	*dirs = NULL;
	if (dc == 0 && fc == 0 && erc == 0)
	{
		*dp = opendir(".");
		if (!*dp)
		{
			cleanup(NULL, NULL, opt);
			error(".", '\0', true, printed);
		}
	}
	else
	{
		if (fc > 0)
			handlecontent(true, argv, file_a, fc, printed);
		if (dc > 0)
		{
			*dirs = handlecontent(false, argv, dir_a, dc, printed);
			_qsort(*dirs, 0, dc - 1);
		}
	}
	return (status);
}
