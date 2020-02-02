#include "hls.h"

static bool start;
static unsigned int status;
static struct option *opt;

/**
 * ls - Lists information about files and directories
 * @argc: number of arguments
 * @argv: pointer to an array of strings containing arguments
 *
 * Return: status
 */
unsigned int ls(const int argc, char *argv[])
{
	unsigned int entry_size = 100, dc, ec, i;
	DIR *dp;
	struct dirent *ep;
	struct content *entries, *dirs;

	dc = ec = 0;
	dirs = preprocess(argv, &dc, &dp);
	entries = malloc(entry_size * sizeof(*entries));
	for (i = 0; i < dc || dc == 0; ++i, ec = 0)
	{
		if (dc > 0)
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
		if (dc == 0)
			break;
	}
	if (dc > 0)
		free(dirs);
	free(entries);
	free(opt);
	return (status);
}

/**
 * preprocess - processes arguments
 * @argv: pointer to an array of strings to process
 * @dc: number of directories
 * @dp: pointer to pointer of struct DP containing lstat information
 *
 * Return: struct containing directory information
 */
content_t *preprocess(char *argv[], unsigned int *dc, DIR **dp)
{
	unsigned int fc;
	int file_a[256], dir_a[256];
	struct content *dirs;

	opt = malloc(sizeof(*opt));
	initoptions(&opt);
	fc = parse_args(dc, argv, file_a, dir_a);
	if (*dc == 0 && fc == 0)
	{
		*dp = opendir(".");
		if (!*dp)
		{
			free(opt);
			status = error(true, ".", '\0');
		}
	}
	else
	{
		if (fc > 0)
		{
			handlecontent(true, fc, argv, file_a);
		}
		if (*dc > 0)
		{
			dirs = handlecontent(false, *dc, argv, dir_a);
			_qsort(&dirs, 0, *dc - 1);
			return (dirs);
		}
	}
	return (NULL);
}

/**
 * parse_args - indexes position of valid arguments, files, directories
 * @dc: number of directories
 * @argv: pointer to an array of strings to parse
 * @file_a: pointer to an array of characters to populate with index of files
 * @dir_a: pointer an array of characters to populate with index of directories
 *
 * Return: number of files
 */
unsigned int parse_args(unsigned int *dc, char *argv[], int *file_a,
		int *dir_a)
{
	unsigned int i, j, fc;
	struct stat sb;

	fc = 0;
	for (i = 1; argv[i]; ++i)
	{
		if (*argv[i] == '-')
			for (j = 1; argv[i][j]; ++j)
				checkoptions(&opt, argv, i, j);
		else if (lstat(argv[i], &sb) == -1)
			status = error(false, argv[i], '\0');
		else if ((sb.st_mode & S_IFMT) == S_IFREG)
			file_a[fc++] = i;
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
			dir_a[(*dc)++] = i;
	}
	return (fc);
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
 * @f: if content is a file
 * @argc: number of arguments
 * @argv: string of directory to print
 * @c: count of total struct entries
 * @entries: contents of directory to print
 */
void printcontent(const bool f, const int argc, char *argv,
		const unsigned int c, content_t *entries)
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
			!opt->perline ? printf("  ") : printf("\n");
		printf("%s", entries[i].name);
		start = true;
	}
	if (f)
		start = false;
	printf("\n");
}
