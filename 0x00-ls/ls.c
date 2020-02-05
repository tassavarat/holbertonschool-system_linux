#include "hls.h"

static size_t status;

/**
 * printcontent - prints and formats content
 * @entries: pointer content entries to print
 * @c: count of entries
 * @fc: file count
 * @dc: directory count
 * @erc: error count
 * @dir: directory to print
 * @printed: if printfile was called
 */
void printcontent(struct content *entries, size_t c, size_t fc, size_t dc,
		size_t erc, char *dir, bool printed)
{
	size_t i;
	static bool start;

	_qsort(entries, 0, c - 1);
	if (start || printed)
	{
		printf("\n");
		start = false;
	}
	if (fc + dc + erc > 1)
		printf("%s:\n", dir);
	for (i = 0; i < c; ++i)
	{
		if (start)
			printf("  ");
		printf("%s", entries[i].name);
		start = true;
	}
	if (printed)
		printf("\n");
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
			status = error(dirs[i].name, false);
			return (false);
		}
	}
	while ((ep = readdir(dp)))
	{
		if (*ep->d_name == '.')
			continue;
		_strcpy((*entries)[*ec].name, ep->d_name);
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
	size_t i;
	struct stat sb;

	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFREG)
				file_a[(*fc)++] = i;
			else if ((sb.st_mode & S_IFMT) == S_IFDIR)
				dir_a[(*dc)++] = i;
		}
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == -1)
		{
			status = error(argv[i], false);
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
	bool printed;
	size_t fc, dc, ec, erc, entsiz, i;
	size_t file_a[256], dir_a[256];
	DIR *dp;
	struct content *entries, *dirs;

	printed = false;
	fc = dc = ec = erc = 0;
	entsiz = 100;
	parse_args(argv, &fc, &dc, &erc, file_a, dir_a);

	status = processargs(&dirs, argv, file_a, dir_a, status, &dp, fc, dc,
			erc, &printed);
	entries = malloc(entsiz * sizeof(*entries));
	for (i = 0; i < dc || (fc == 0 && dc == 0 && erc == 0); ++i)
	{
		if (!readcontents(dp, &entries, dirs, &ec, dc, i, &entsiz))
			continue;
		printcontent(entries, ec, fc, dc, erc, dirs[i].name, printed);
		if (fc == 0 && dc == 0)
			break;
		ec = 0;
	}
	cleanup(entries, dirs);
	if (!printed)
		printf("\n");
	return (status);
}
