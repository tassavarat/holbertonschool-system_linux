#include "hls.h"

static bool start;
static unsigned int status;

/**
 * ls - Lists information about files and directories
 * @argc: number of arguments
 * @argv: pointer to an array of strings containing arguments
 *
 * Return: status
 */
unsigned int ls(const int argc, char *argv[])
{
	unsigned int entry_size, dc, ec, i;
	DIR *dp;
	char option_a[256];
	struct dirent *ep;
	struct content *entries, *dirs;

	entry_size = 100;
	dc = ec = 0;

	dirs = preprocess(argc, argv, &dc, &dp, option_a);
	for (i = 0; i < dc || argc == 1; ++i)
	{
		entries = malloc(entry_size * sizeof(*entries));
		if (argc > 1)
		{
			dp = opendir(dirs[i].name);
			if (!dp)
			{
				status = error(dirs[i].name, '\0');
				free(entries);
				continue;
			}
		}
		while ((ep = readdir(dp)))
		{
			if (*ep->d_name == '.')
				continue;
			_strcpy(entries[ec].name, ep->d_name);
			++ec;
		}
		closedir(dp);
		printcontent(argc, dirs[i].name, ec, entries);
		free(entries);
		if (argc == 1)
			break;
		ec = 0;
	}
	if (argc > 1)
		free(dirs);
	return (status);
}

/**
 * preprocess - processes arguments
 * @argc: number of arguments
 * @argv: pointer to an array of strings to process
 * @dp: pointer to pointer of struct DP containing lstat information
 * @numdir: number of directories
 * @option_a: pointer to a character array to contain index of options
 *
 * Return: struct containing directory information
 */
content_t *preprocess(const int argc, char *argv[], unsigned int *numdir,
		DIR **dp, char *option_a)
{
	unsigned int numfiles;
	int file_a[256], dir_a[256];
	struct content *dirs;

	if (argc == 1)
	{
		*dp = opendir(".");
		if (!*dp)
			status = error(".", '\0');
	}
	else
	{
		numfiles = parse_args(numdir, argv, option_a, file_a, dir_a);
		if (numfiles > 0)
		{
			handlecontent(true, numfiles, argv, file_a);
			start = true;
		}
		if (*numdir > 0)
		{
			dirs = handlecontent(false, *numdir, argv, dir_a);
			_qsort(&dirs, 0, *numdir - 1);
			return (dirs);
		}
	}
	return (NULL);
}

/**
 * parse_args - indexes position of valid arguments, files, directories
 * @numdir: number of directories
 * @argv: pointer to an array of strings to parse
 * @option_a: pointer to a character array to populate with index of options
 * @file_a: pointer to an array of characters to populate with index of files
 * @dir_a: pointer an array of characters to populate with index of directories
 *
 * Return: number of files
 */
unsigned int parse_args(unsigned int *numdir, char *argv[], char *option_a,
		int *file_a, int *dir_a)
{
	unsigned int i, j, k, numfiles;
	struct stat sb;

	k = numfiles = 0;
	for (i = 1; argv[i]; ++i)
	{
		if (*argv[i] == '-')
			for (j = 1; argv[i][j]; ++j)
			{
				if (argv[i][j] == '1' || argv[i][j] == 'a' ||
						argv[i][j] == 'A' || argv[i][j] == 'l' ||
						argv[i][j] == 'r' || argv[i][j] == 'S' ||
						argv[i][j] == 't' || argv[i][j] == 'R')
					option_a[k] = argv[i][j];
				else
					error(NULL, argv[i][j]);
				++k;
			}
		else if (lstat(argv[i], &sb) == -1)
			status = error(argv[i], '\0');
		else if ((sb.st_mode & S_IFMT) == S_IFREG)
			file_a[numfiles++] = i;
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
			dir_a[(*numdir)++] = i;
	}
	return (numfiles);
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
	}
	return (entries);
}

/**
 * printcontent - prints and formats content
 * @argc: number of arguments
 * @argv: string of directory to print
 * @c: count of total struct entries
 * @entries: contents of directory to print
 */
void printcontent(const int argc, char *argv, const unsigned int c,
		content_t *entries)
{
	unsigned int i;

	_qsort(&entries, 0, c - 1);
	if (start)
		printf("\n");
	start = false;
	if (argc > 2)
		printf("%s:\n", argv);
	for (i = 0; i < c; ++i)
	{
		if (start)
			printf("  ");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
}
