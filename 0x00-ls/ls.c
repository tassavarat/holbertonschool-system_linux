#include "hls.h"

static bool printed;
static size_t status;
static struct option *opt;

/**
 * printcontent - prints and formats content
 * @entries: pointer content entries to print
 * @c: count of entries
 * @fc: file count
 * @dc: directory count
 * @erc: error count
 * @dir: directory to print
 * @printed: if printfile was called
 *
 * Return: true after print
 */
bool printcontent(struct content *entries, size_t c, size_t fc, size_t dc,
		size_t erc, char *dir, bool printed)
{
	size_t i;
	static bool start;

	_qsort(entries, 0, c - 1);
	if (fc + dc + erc > 1)
	{
		if (start || printed)
			printf("\n");
		printf("%s:\n", dir);
	}
	start = false;
	for (i = 0; i < c; ++i)
	{
		if (start)
			!opt->perline ? printf("  ") : printf("\n");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
	return (true);
}

/**
 * readcontents - reads contents of directory and populates entries
 * @dp: pointer to a directory stream
 * @entries: pointer to a pointer of content entries to read
 * @dirs: pointer to directories to read
 * @ec: pointer to entry count
 * @dc: directory count
 * @i: current index
 * @entsiz: size of entries
 *
 * Return: true if successful read otherwise false
 */
bool readcontents(DIR *dp, struct content **entries, struct content *dirs,
		size_t *ec, size_t dc, size_t i, size_t *entsiz)
{
	struct dirent *ep;

	if (dc > 0)
	{
		dp = opendir(dirs[i].name);
		if (!dp)
		{
			status = error(dirs[i].name, '\0', false, printed);
			printed = false;
			return (false);
		}
	}
	while ((ep = readdir(dp)))
	{
		if (filterhidden(ep, opt))
			continue;
		_strcpy((*entries)[*ec].name, ep->d_name);
		if (opt->longfmt)
			linfo(&(*entries)[*ec]);
		++*ec;
		if (*ec == *entsiz)
		{
			*entsiz *= 2;
			*entries = realloc(*entries, *entsiz * sizeof(**entries));
		}

	}
	closedir(dp);
	return (true);
}

/**
 * parse_args - indexes positions of valid arguments, files, and directories
 * @argv: pointer to an array of strings to parse
 * @fc: number of files
 * @dc: number of directories
 * @erc: number of errors
 * @file_a: pointer to array to populate with file indexes
 * @dir_a: pointer to array to populate with directory indexes
 */
void parse_args(char *argv[], size_t *fc, size_t *dc, size_t *erc,
		size_t *file_a, size_t *dir_a)
{
	size_t i, j;
	struct stat sb;

	for (i = 1; argv[i]; ++i)
		if (*argv[i] == '-')
			for (j = 1; argv[i][j]; ++j)
				checkopt(&opt, argv, i, j);
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFREG)
				file_a[(*fc)++] = i;
			else if ((sb.st_mode & S_IFMT) == S_IFDIR)
				dir_a[(*dc)++] = i;
		}
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == -1 && (*argv[i] != '-' ||
					_strcmp(argv[i], "-") == 0))
		{
			status = error(argv[i], '\0', false, printed);
			++*erc;
		}
}

/**
 * ls - Lists information about files and directories
 * @argv: pointer to an array of strings containing arguments
 *
 * Return: status
 */
size_t ls(char *argv[])
{
	size_t fc, dc, ec, erc, entsiz, i;
	size_t file_a[256], dir_a[256];
	DIR *dp;
	struct content *entries, *dirs;

	fc = dc = ec = erc = 0;
	entsiz = 100;
	opt = malloc(sizeof(*opt));
	initoptions(&opt);

	parse_args(argv, &fc, &dc, &erc, file_a, dir_a);
	status = processargs(&dirs, opt, argv, file_a, dir_a, status, &dp, fc, dc,
			erc, &printed);
	entries = malloc(entsiz * sizeof(*entries));
	for (i = 0; i < dc || (fc == 0 && dc == 0 && erc == 0); ++i)
	{
		if (!readcontents(dp, &entries, dirs, &ec, dc, i, &entsiz))
			continue;
		if (opt->longfmt)
			plong(entries, ec, false);
		else
			printed = printcontent(entries, ec, fc, dc, erc,
				dirs[i].name, printed);
		if (fc == 0 && dc == 0)
			break;
		ec = 0;
	}
	cleanup(entries, dirs, opt);
	return (status);
}
