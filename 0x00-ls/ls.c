#include "hls.h"

static bool start;
static unsigned int status;
static struct option *opt;

/**
 * ls - Lists information about files and directories
 * @argv: pointer to an array of strings containing arguments
 *
 * Return: status
 */
unsigned int ls(char *argv[])
{
	unsigned int entry_size = 100, fc = 0, dc = 0, ec = 0, erc = 0, i;
	DIR *dp;
	struct dirent *ep;
	struct content *entries, *dirs = preprocess(argv, &fc, &dc, &erc, &dp);

	entries = malloc(entry_size * sizeof(*entries));
	for (i = 0; i < dc || (fc == 0 && dc == 0); ++i, ec = 0)
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
			if (filterhidden(ep, opt))
				continue;
			_strcpy(entries[ec++].name, ep->d_name);
			if (opt->longfmt)
				linfo(&entries[i]);
			if (ec == entry_size)
			{
				entry_size *= 2;
				entries = realloc(entries, entry_size * sizeof(*entries));
			}
		}
		closedir(dp);
		if (opt->longfmt)
			plong(entries,  ec);
		else
			printcontent(false, dc, fc, erc, dirs[i].name, ec, entries);
		if (dc == 0)
			break;
	}
	cleanup(dc, dirs, entries, opt);
	return (status);
}

/**
 * preprocess - processes arguments
 * @argv: pointer to an array of strings to process
 * @fc: number of files
 * @dc: number of directories
 * @erc: number of errors
 * @dp: pointer to pointer of struct DP containing lstat information
 *
 * Return: struct containing directory information
 */
content_t *preprocess(char *argv[], unsigned int *fc,
		unsigned int *dc, unsigned int *erc, DIR **dp)
{
	int file_a[256], dir_a[256];
	struct content *dirs;

	opt = malloc(sizeof(*opt));
	initoptions(&opt);
	parse_args(fc, dc, erc, argv, file_a, dir_a);
	if (*dc == 0 && *fc == 0)
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
		if (*fc > 0)
		{
			handlecontent(true, *fc, *dc, argv, file_a);
		}
		if (*dc > 0)
		{
			dirs = handlecontent(false, *dc, *dc, argv, dir_a);
			_qsort(&dirs, 0, *dc - 1);
			return (dirs);
		}
	}
	return (NULL);
}

/**
 * parse_args - indexes position of valid arguments, files, directories
 * @fc: number of directories
 * @dc: number of directories
 * @erc: number of errors
 * @argv: pointer to an array of strings to parse
 * @file_a: pointer to an array of characters to populate with index of files
 * @dir_a: pointer an array of characters to populate with index of directories
 *
 * Return: number of files
 */
void parse_args(unsigned int *fc, unsigned int *dc,
		unsigned int *erc, char *argv[], int *file_a, int *dir_a)
{
	unsigned int i, j;
	struct stat sb;

	for (i = 1; argv[i]; ++i)
		if (*argv[i] == '-')
			for (j = 1; argv[i][j]; ++j)
				checkoptions(&opt, argv, i, j);
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFREG)
				file_a[(*fc)++] = i;
			else if ((sb.st_mode & S_IFMT) == S_IFDIR)
				dir_a[(*dc)++] = i;
		}
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == -1 && ((*argv[i] != '-') ||
					(*argv[i] == '-' && _strlen(argv[i]) == 1)))
		{
			if (*fc == 0 && *dc == 0)
			{
				free(opt);
				status = error(true, argv[i], '\0');
			}
			status = error(false, argv[i], '\0');
			++*erc;
		}
}

/**
 * handlecontent - allocates space for struct containing content information
 * @f: if content is a file
 * @c: count of content
 * @dirc: count of content
 * @argv: pointer to array of strings containing name of content
 * @a: pointer to array of integers containing index of content
 *
 * Return: created struct
 */
content_t *handlecontent(const bool f, const unsigned int c,
		const unsigned int dirc, char *argv[], int *a)
{
	unsigned int i;
	struct content *entries;

	entries = malloc(c * sizeof(*entries));
	for (i = 0; i < c; ++i)
	{
		_strcpy(entries[i].name, argv[a[i]]);
		if (opt->longfmt && f)
			linfo(&entries[i]);
	}
	if (f)
	{
		if (opt->longfmt)
			plong(entries,  c);
		else
			printcontent(f, 0, 0, 0, NULL, c, entries);
		if (dirc > 0)
			printf("\n");
		free(entries);
		return (NULL);
	}
	return (entries);
}

/**
 * printcontent - prints and formats content
 * @f: if content is a file
 * @fc: number of arguments
 * @dc: number of arguments
 * @erc: number of errors
 * @argv: string of directory to print
 * @c: count of total struct entries
 * @entries: contents of directory to print
 */
void printcontent(const bool f, const int fc, const int dc, const int erc,
		char *argv, const int c, content_t *entries)
{
	int i;

	_qsort(&entries, 0, c - 1);
	if (start)
		printf("\n");
	start = false;
	if (fc + dc + erc > 1)
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
	if (c > 0)
		printf("\n");
}
