#include "hls.h"

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

char *str_toupper(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= ' ';
	return (s);
}

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i]; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

int cmpstringp(const char *p1, const char *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp1, tp2));
}

void swap(struct content **entries, int i, int j)
{
	char tmp[256];

	_strcpy(tmp, (*entries)[j].name);
	_strcpy((*entries)[j].name, (*entries)[i].name);
	_strcpy((*entries)[i].name, tmp);
}

int partition(struct content **entries, int lo, int hi)
{
	char *pivot;
	int i, j;

	pivot = (*entries)[hi].name;
	i = lo;
	for (j = lo; j < hi; ++j)
		if (cmpstringp((*entries)[j].name, pivot) < 0)
		{
			swap(*&entries, i, j);
			++i;
		}
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
			_strcpy(entries[ec].name, ep->d_name);
			++ec;
			/* start = true; */
		}
		closedir(dp);
		/* printf("\n"); */
	}
	_qsort(&entries, 0, ec - 1);
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
