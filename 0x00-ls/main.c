#include "hls.h"

bool printdir(const int argc, char *argv[], bool start, const unsigned int ec,
	struct content *entries)
{
	unsigned int i;

	_qsort(&entries, 0, ec - 1);
	if (start)
		printf("\n");
	start = false;
	if (argc > 2)
		printf("%s:\n", *argv);
	for (i = 0; i < ec; ++i)
	{
		if (start)
			printf("  ");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
	return (start);
}

void error(char *argv)
{
	char buf[BUFSIZ];

	printf("errno =  %d\n", errno);
	if (errno == ENOENT)
		sprintf(buf, "ls: cannot access '%s'", argv);
	else if (errno == EACCES)
		sprintf(buf, "ls: cannot open directory '%s'", argv);
	perror(buf);
}



void hls(const int argc, char *argv[])
{
	bool start;
	unsigned int entry_size, ec, i;
	DIR *dp;
	struct dirent *ep;
	struct content *entries;

	start = false;
	entry_size = 100;
	if (argc == 1)
	{
		dp = opendir(".");
		if (!dp)
			error(".");
	}
	for (i = 1, ec = 0; argv[i] || argc == 1; ++i, ec = 0)
	{
		entries = malloc(entry_size * sizeof(*entries));
		if (argc > 1)
		{
			dp = opendir(argv[i]);
			if (!dp)
			{
				error(argv[i]);
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
		start = printdir(argc, argv, start, ec, entries);
		if (argc == 1)
			break;
		free(entries);
	}
}

int main(int argc, char *argv[])
{
	hls(argc, argv);
	return (EXIT_SUCCESS);
}
