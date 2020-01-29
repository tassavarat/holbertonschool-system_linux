#include "hls.h"

size_t _strlen(const char *s)
{
	int i;

	for (i = 0; s[i]; ++i)
		;
	return (i);
}

char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i]; ++i)
		dest[i] = src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

void swap(struct content **entries, int i, int j)
{
	char tmp[256];

	_strncpy(tmp, (*entries)[j].name, _strlen((*entries)[j].name) + 1);
	_strncpy((*entries)[j].name, (*entries)[i].name, _strlen((*entries)[j].name) + 1);
	_strncpy((*entries)[i].name, tmp, _strlen((*entries)[i].name) + 1);
}

int partition(struct content **entries, int lo, int hi)
{
	char pivot;
	int i, j;

	printf("lo: %u\thi: %u\n", lo, hi);
	pivot = *(*entries)[hi].name;
	i = lo - 1;
	for (j = lo; j < hi; ++j)
		if (*(*entries)[j].name < pivot)
		{
			++i;
			swap(*&entries, i, j);
		}
	++i;
	swap(*&entries, i, hi);
	return (i);
}

void _qsort(struct content **entries, int lo, int hi)
{
	unsigned int p;

	if (lo < hi)
	{
		p = partition(*&entries, lo, hi);
		_qsort(*&entries, lo, p - 1);
		_qsort(*&entries, p + 1, hi);
	}
}

void error(char *argv)
{
	char buf[BUFSIZ];

	sprintf(buf, "ls: cannot access '%s'", argv);
	perror(buf);
}

void hls(int argc, char *argv[])
{
	(void) argc;
	/* bool start; */
	unsigned int entry_size, ec, i;
	DIR *dp;
	struct dirent *ep;
	struct content *entries;

	/* start = false; */
	entry_size = 100;
	ec = 0;
	entries = malloc(entry_size * sizeof(*entries));
	dp = opendir("./");
	if (!dp)
		error(*argv);
	else
	{
		while ((ep = readdir(dp)))
		{
			if (*ep->d_name == '.')
				continue;
			/*
			if (start)
				printf("  ");
			printf("%s", ep->d_name);
			*/
			_strncpy(entries[ec++].name, ep->d_name, _strlen(ep->d_name) + 1);
			/* start = true; */
		}
		closedir(dp);
		printf("\n");
	}
	printf("Before sort\n");
	for (i = 0; i < ec; ++i)
		printf("%s\n", entries[i].name);
	_qsort(&entries, 0, ec - 1);
	printf("After sort\n");
	for (i = 0; i < ec; ++i)
		printf("%s\n", entries[i].name);
	free(entries);

}

int main(int argc, char *argv[])
{
	(void) argc;
	hls(argc, argv);
	return (EXIT_SUCCESS);
}
