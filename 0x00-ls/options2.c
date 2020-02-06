#include "hls.h"

/**
 * plong - prints long format
 * @entries: pointer to entries struct
 * @c: count of struct entries
 * @f: if printing file
 */
void plong(content *entries, size_t c, bool f)
{
	unsigned int i;

	_qsort(entries, 0, c - 1);
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
void setug(content *entries, struct stat sb)
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


