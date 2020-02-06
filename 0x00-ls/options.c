#include "hls.h"

/**
 * setperm - initialises content struct with permission info
 * @entries: pointer to entries
 * @sb: stat buffer
 */
void setperm(content *entries, struct stat sb)
{
	if (sb.st_mode & S_IRUSR)
		entries->tperm[1] = 'r';
	if (sb.st_mode & S_IWUSR)
		entries->tperm[2] = 'w';
	if (sb.st_mode & S_IXUSR)
		entries->tperm[3] = 'x';
	if (sb.st_mode & S_IRGRP)
		entries->tperm[4] = 'r';
	if (sb.st_mode & S_IWGRP)
		entries->tperm[5] = 'w';
	if (sb.st_mode & S_IXGRP)
		entries->tperm[6] = 'x';
	if (sb.st_mode & S_IROTH)
		entries->tperm[7] = 'r';
	if (sb.st_mode & S_IWOTH)
		entries->tperm[8] = 'w';
	if (sb.st_mode & S_IXOTH)
		entries->tperm[9] = 'x';
}

/**
 * settype - initialises content struct with type info
 * @entries: pointer to entries
 * @sb: stat buffer
 */
void settype(content *entries, struct stat sb)
{
	switch (sb.st_mode & S_IFMT)
	{
		case S_IFBLK:
			entries->tperm[0] = 'b';
			break;
		case S_IFCHR:
			entries->tperm[0] = 'c';
			break;
		case S_IFDIR:
			entries->tperm[0] = 'd';
			break;
		case S_IFIFO:
			entries->tperm[0] = 'p';
			break;
		case S_IFLNK:
			entries->tperm[0] = 'l';
			break;
		case S_IFREG:
			entries->tperm[0] = '-';
			break;
		case S_IFSOCK:
			entries->tperm[0] = 's';
			break;
	}
}

/**
 * initinfo - initialises content struct
 * @entries: struct to initialise
 */
void initinfo(content *entries)
{
	size_t i;

	for (i = 0; i < 10; ++i)
		entries->tperm[i] = '-';
	entries->tperm[i] = '\0';
	entries->lc = 0;
	entries->uid = 0;
	entries->gid = 0;
	entries->usr = '\0';
	entries->grp = '\0';
	entries->siz = 0;
}

/**
 * linfo - populates entries with lstat information
 * @entries: pointer to entries
 */
void linfo(content *entries)
{
	struct stat sb;
	char *fmtim;

	initinfo(entries);
	lstat((entries)->name, &sb);
	settype(entries, sb);
	setperm(entries, sb);
	entries->lc = sb.st_nlink;
	setug(entries, sb);
	entries->siz = sb.st_size;
	fmtim = ctime(&(sb.st_mtime));
	fmtim[16] = '\0';
	_strcpy(entries->mtim, fmtim + 4);
}

/**
 * filterhidden - filters hidden files
 * @ep: entry pointer to check entry names
 * @opt: options struct to check if enabled
 *
 * Return: true if filtering otherwise false
 */
bool filterhidden(struct dirent *ep, struct option *opt)
{
	if (*ep->d_name == '.' && !opt->hidden && !opt->hiddenavigation)
		return (true);
	if (opt->hidden)
		return (false);
	if (opt->hiddenavigation && (_strcmp(ep->d_name, ".") == 0 ||
				_strcmp(ep->d_name, "..") == 0))
		return (true);
	return (false);
}
