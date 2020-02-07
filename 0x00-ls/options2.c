#include "hls.h"

/**
 * getlink - gets symlink info
 * @arg: symlink string
 * @len: len of symlink string
 *
 * Return: string of symlink target
 */
char *getlink(char *arg, size_t len)
{
	char *buf;
	ssize_t bufsiz, nbytes;

	bufsiz = len + 1;
	if (len == 0)
		bufsiz = PATH_MAX;
	buf = malloc(bufsiz);
	if (!buf)
		exit(2);
	nbytes = readlink(arg, buf, bufsiz);
	if (nbytes == -1)
		exit(2);
	buf[bufsiz - 1] = '\0';
	return (buf);
}

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
		_memcpy(path + len1, "/", 1);
		_memcpy(path + len1 + 1, entry, len2 + 1);
	}
	else
		_memcpy(path + len1, entry, len2 + 1);
	return (path);
}

/**
 * plong2 - prints remaining long format info
 * @entries: pointer to entries struct
 * @f: if printing file
 * @dirstr: directory string
 */
void plong2(struct content entries, bool f, char *dirstr)
{
	char *buf, *path;
	struct stat sb;

	if (f)
	{
		if ((lstat(entries.name, &sb) == 0) && (sb.st_mode & S_IFMT) == S_IFLNK)
		{
			buf = getlink(entries.name, sb.st_size);
			printf(" %ld %s %s -> %s\n", entries.siz,
					entries.mtim, entries.name, buf);
			free(buf);
		}
		else
		{
			printf(" %ld %s %s\n", entries.siz,
					entries.mtim, entries.name);
		}
	}
	else
	{
		path = createpath(dirstr, entries.name);
		lstat(path, &sb);
		if ((sb.st_mode & S_IFMT) == S_IFLNK)
		{
			buf = getlink(path, sb.st_size);
			printf(" %5ld %s %s -> %s\n", entries.siz,
					entries.mtim, entries.name, buf);
			free(buf);
		}
		else
		{
			printf(" %5ld %s %s\n", entries.siz, entries.mtim,
					entries.name);
		}
		free(path);
	}
}

/**
 * plong - prints long format
 * @entries: pointer to entries struct
 * @c: count of struct entries
 * @f: if printing file
 * @opt: options state
 * @dirstr: directory string
 */
void plong(struct content *entries, size_t c, bool f, struct option *opt,
		char *dirstr)
{
	size_t i;

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
		plong2(entries[i], f, dirstr);
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


