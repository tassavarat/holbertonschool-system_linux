#include "hls.h"

static size_t status;


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

/**
 * _strcpy - copies a string
 * @dest: buffer being copied to
 * @src: pointer to string being copied
 *
 * Return: pointer to destination string dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i]; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

int cmpstringp(char *p1, char *p2)
{
	char tp1[BUFSIZ];
	char tp2[BUFSIZ];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp1, tp2));
}

void swap(struct content **entries, int i, int j)
{
	struct content *tmp;

	printf("entries[j]->name %s\n", (*entries)[j].name);
	printf("entries[i]->name %s\n", (*entries)[i].name);
	tmp = entries[j];
	printf("tmp->name %s\n", tmp->name);
	(*entries)[j] = (*entries)[i];
	entries[i] = tmp;
	printf("entries[j]->name %s\n", (*entries)[j].name);
	printf("entries[i]->name %s\n", (*entries)[i].name);
}

size_t partition(struct content **entries, size_t lo, size_t hi)
{
	char *piv;
	size_t i, j;

	piv = (*entries)[hi].name;
	i = lo;
	for (j = lo; j < hi; ++j)
		if (cmpstringp((*entries)[j].name, piv) < 0)
		{
			swap(entries, i, j);
			++i;
		}
	swap(entries, i, hi);
	return (i);
}

void _qsort(struct content **entries, size_t lo, size_t hi)
{
	size_t p;

	if (lo < hi)
	{
		p = partition(entries, lo, hi);
		_qsort(entries, lo, p - 1);
		_qsort(entries, p + 1, hi);
	}
}

void cleanup(struct content *entries, size_t ec)
{
	size_t i;

	for (i = 0; i < ec; ++i)
		free(entries[i].name);
}

void printcontent(struct content *entries, size_t c)
{
	size_t i;
	static bool start;

	_qsort(&entries, 0, c - 1);
	for (i = 0; i < c; ++i)
	{
		if (start)
			printf("  ");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
}

/**
 * _strdup - Returns pointer to newly allocated space which contains a string
 * @str: String to be copied
 *
 * Return: Pointer to new string identical to str, NULL if str = NULL
 */
char *_strdup(char *str)
{
	char *s;
	int i;
	int len;

	i = 0;
	if (!str)
		return (NULL);
	while (*(str + i))
		++i;
	len = i;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	for (i = 0; i <= len; ++i)
		*(s + i) = *(str + i);
	return (s);
}

void readcontents(DIR *dp)
{
	size_t ec, entsiz;
	struct content *entries;
	struct dirent *ep;

	ec = 0;
	entsiz = 100;
	entries = malloc(entsiz * sizeof(*entries));
	while ((ep = readdir(dp)))
	{
		if (*ep->d_name == '.')
			continue;
		entries[ec].name = _strdup(ep->d_name);
		++ec;
	}
	closedir(dp);
	printcontent(entries, ec);
	cleanup(entries, ec);
	free(entries);
}

size_t error(char *arg, bool e)
{
	char buf[256];

	if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", arg);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", arg);
	perror(buf);
	if (e)
		exit(2);
	return (2);
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

content_t *preprocessing(char *argv[], DIR **dp, size_t *fc, size_t *dc)
{
	parse_args(argv, fc, dc);
	if (*dc == 0 && *fc == 0)
	{
		*dp = opendir(".");
		if (!*dp)
			status = error(".", true);
	}
	return (NULL);
}

size_t ls(char *argv[])
{
	size_t fc, dc;
	DIR *dp;

	fc = dc = 0;
	preprocessing(argv, &dp, &fc, &dc);
	readcontents(dp);
	return (status);
}

/**
 * main - entry point to ls program
 * @argc: number of arguments
 * @argv: pointer to an array of strings
 *
 * Return: 0 on success, error will exit with value of 2
 */
int main(int argc, char *argv[])
{
	size_t status;
	(void) argc;

	status = ls(argv);
	return (status);
}
