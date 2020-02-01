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
	entries = malloc(entry_size * sizeof(*entries));
	for (i = 0; i < dc || argc == 1; ++i, ec = 0)
	{
		if (argc > 1)
		{
			dp = opendir(dirs[i].name);
			if (!dp)
			{
				status = error(false, dirs[i].name, '\0');
				continue;
			}
		}
		while ((ep = readdir(dp)))
		{
			if (*ep->d_name == '.')
				continue;
			_strcpy(entries[ec++].name, ep->d_name);
			if (ec == entry_size)
			{
				entry_size *= 2;
				entries = realloc(entries, entry_size * sizeof(*entries));
			}
		}
		closedir(dp);
		printcontent(false, argc, dirs[i].name, ec, entries);
		if (argc == 1)
			break;
	}
	if (argc > 1)
		free(dirs);
	free(entries);
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
			status = error(true, ".", '\0');
	}
	else
	{
		numfiles = parse_args(numdir, argv, option_a, file_a, dir_a);
		if (numfiles > 0)
		{
			handlecontent(true, numfiles, argv, file_a);
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
	char vo[8] = {'1', 'a', 'A', 'l', 'r', 'S', 't', 'R'};
	unsigned int i, j, k, l, numfiles, argsize;
	struct stat sb;

	k = numfiles = 0;
	argsize = 8;
	for (i = 1; argv[i]; ++i)
	{
		if (*argv[i] == '-')
		{
			for (j = 1; argv[i][j]; ++j)
			{
				for (l = 0; l < argsize; ++l)
					if (argv[i][j] == vo[l])
					{
						option_a[k] = argv[i][j];
						break;
					}
				if (l == argsize)
					error(true, NULL, argv[i][j]);
				++k;
			}
		}
		else if (lstat(argv[i], &sb) == -1)
		{
			status = error(false, argv[i], '\0');
		}
		else if ((sb.st_mode & S_IFMT) == S_IFREG)
		{
			file_a[numfiles++] = i;
		}
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
		{
			dir_a[(*numdir)++] = i;
		}
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
		printcontent(f, 0, NULL, c, entries);
		printf("\n");
		free(entries);
		return (NULL);
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
void printcontent(const bool f, const int argc, char *argv, const unsigned int c,
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
	if (f)
		start = false;
	printf("\n");
}
