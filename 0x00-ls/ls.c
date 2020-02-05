#include "hls.h"

static size_t status;

void printcontent(struct content *entries, size_t c)
{
	size_t i;
	static bool start;

	_qsort(entries, 0, c - 1);
	for (i = 0; i < c; ++i)
	{
		if (start)
			printf("  ");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
}

void readcontents(DIR *dp, struct content **entries, size_t *ec)
{
	struct dirent *ep;

	while ((ep = readdir(dp)))
	{
		if (*ep->d_name == '.')
			continue;
		(*entries)[*ec].name = _strdup(ep->d_name);
		++*ec;
	}
	closedir(dp);
}

void preprocessing(DIR **dp, size_t *fc, size_t *dc)
{
	if (*dc == 0 && *fc == 0)
	{
		*dp = opendir(".");
		if (!*dp)
			status = error(".", true);
	}
}

void parse_args(char *argv[], size_t *fc, size_t *dc)
{
	size_t i;
	struct stat sb;

	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFREG)
				++fc;
			else if ((sb.st_mode & S_IFMT) == S_IFDIR)
				++dc;
		}
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == -1)
			status = error(argv[i], false);
}

/**
 * ls - Lists information about files and directories
 * @argv: pointer to an array of strings containing arguments
 *
 * Return: status
 */
size_t ls(char *argv[])
{
	size_t fc, dc, ec, entsiz;
	DIR *dp;
	struct content *entries;

	fc = dc = ec = 0;
	entsiz = 100;
	parse_args(argv, &fc, &dc);
	preprocessing(&dp, &fc, &dc);

	entries = malloc(entsiz * sizeof(*entries));
	readcontents(dp, &entries, &ec);
	printcontent(entries, ec);
	cleanup(entries, ec);
	free(entries);
	return (status);
}
