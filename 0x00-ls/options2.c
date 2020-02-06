#include "hls.h"

/**
 * createpath - concatenate relative path
 * @dirstr: directory string
 * @entry: entry name string
 *
 * Return: concatenated string
 */
char *createpath(char *dirstr, char *entry)
{
	char *path;
	size_t len1, len2, n;

	len1 = _strlen(dirstr);
	len2 = _strlen(entry);
	n = 1;
	if (dirstr[len1 - 1] != '/')
		n = 2;
	path = malloc(sizeof(char) * (len1 + len2 + n));
	if (!path)
		exit(2);
	_memcpy(path, dirstr, len1);
	if (dirstr[len1 - 1] != '/')
	{
		_memcpy(path + len1, "/", len1 + 1);
		_memcpy(path + len1 + 1, entry, len2 + 1);
	}
	else
		_memcpy(path + len1, entry, len2 + 1);
	return (path);
}

/**
 * plong - prints long format
 * @entries: pointer to entries struct
 * @c: count of struct entries
 * @f: if printing file
 * @opt: options state
 */
void plong(struct content *entries, size_t c, bool f, struct option *opt)
{
	unsigned int i;

	if (!opt->rev)
		_qsort(entries, 0, c - 1, cmpstringp);
	else
		_qsort(entries, 0, c - 1, revstringp);
	for (i = 0; i < c; ++i)
	{
		printf("%s %ld", entries[i].tperm, entries[i].lc);
		if (entries[i].usr)
			printf(" %s", entries[i].usr);
		else
			printf(" %ld", entries[i].uid);
		if (entries[i].grp)
			printf(" %s", entries[i].grp);
		else
			printf(" %ld", entries[i].gid);
		if (f)
			printf(" %ld %s %s\n", entries[i].siz, entries[i].mtim,
					entries[i].name);
		else
			printf(" %5ld %s %s\n", entries[i].siz, entries[i].mtim,
					entries[i].name);
	}
}

/**
 * setug - initialises content struct with permission info
 * @entries: pointer to entries
 * @sb: stat buffer
 */
void setug(struct content *entries, struct stat sb)
{
	struct passwd *p;
	struct group *g;

	entries->uid = sb.st_uid;
	entries->gid = sb.st_gid;
	p = getpwuid(entries->uid);
	if (p)
		entries->usr = p->pw_name;
	g = getgrgid(entries->uid);
	if (g)
		entries->grp = g->gr_name;
}


