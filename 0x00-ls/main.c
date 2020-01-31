#include "hls.h"

static bool start;

void printcontent(const int argc, char *argv, const unsigned int c,
		struct content *entries)
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

void error(char *argv, char o)
{
	char buf[BUFSIZ];

	/* printf("errno =  %d\n", errno); */
	if (!argv)
	{
		fprintf(stderr, "ls: invalid option -- '%c'\n", o);
		fprintf(stderr, "Try 'ls --help' for more information.\n");
		exit(2);
	}
	if (errno == ENOENT)
		sprintf(buf, "ls: cannot access '%s'", argv);
	else if (errno == EACCES)
		sprintf(buf, "ls: cannot open directory '%s'", argv);
	perror(buf);
}

struct content *handlefiles(const bool f, const unsigned int c, char *argv[],
		int *a)
{
	unsigned int i;
	struct content *entries;

	entries = malloc(c * sizeof(*entries));
	for (i = 0; i < c; ++i)
		_strcpy(entries[i].name, argv[a[i]]);
	printcontent(0, NULL, c, entries);
	if (f)
		free(entries);
	return (entries);
}

struct content *preprocess(const int argc, unsigned int *numdir, char *argv[],
		char *option_a)
{
	unsigned int i, j, k, numfiles;
	int file_a[256], dir_a[256];
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
			error(argv[i], '\0');
		else if ((sb.st_mode & S_IFMT) == S_IFREG)
			file_a[numfiles++] = i;
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
			dir_a[(*numdir)++] = i;
	}
	if (numfiles > 0)
	{
		handlefiles(true, numfiles, argv, file_a);
		start = true;
	}
	if (argc == 1)
		if (!opendir("."))
			error(".", '\0');
	if (numfiles > 0)
		return (handlefiles(false, numfiles, argv, dir_a));
	return (NULL);
}

void _ls(const int argc, char *argv[])
{
	unsigned int entry_size, dc, ec, i;
	DIR *dp;
	char option_a[256];
	struct dirent *ep;
	struct content *entries, *dirs;

	entry_size = 100;
	dc = ec = 0;

	dirs = preprocess(argc, &dc, argv, option_a);
	for (i = 0; i < dc || argc == 1; ++i)
	{
		if (argc > 1)
		{
			entries = malloc(entry_size * sizeof(*entries));
			dp = opendir(dirs[i].name);
			if (!dp)
			{
				error(dirs[i].name, '\0');
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
		if (argc == 1)
			break;
		free(entries);
		ec = 0;
	}
	free(dirs);
}

int main(int argc, char *argv[])
{
	_ls(argc, argv);
	exit(0);
}
