#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/**
 * struct content - stores entry information
 * @name: string buffer
 * @tperm: permissions buffer
 * @lc: link count
 * @uid: user id
 * @gid: group id
 * @usr: user name
 * @grp: group name
 * @siz: content size in bytes
 * @mtim: last modified time
 */
typedef struct content
{
	char *name;
	char tperm[11];
	long lc;
	long uid;
	long gid;
	char *usr;
	char *grp;
	long siz;
	char *mtim;
} content_t;

/**
 * struct option - stores options state
 * @perline: Whether to print contents per line
 * @hidden: Whether to show hidden contents
 * @hiddenavigation: Whether to omit . and ..
 * @longfmt: Whether to show lstat information
 * @rev: Whether to sort in reverse
 * @sortsize: Whether to sort by content size
 * @sorttime: Whether to sort by modification time
 * @recurs: Whether list subdirectories recursively
 */
typedef struct option
{
	bool perline;
	bool hidden;
	bool hiddenavigation;
	bool longfmt;
	bool rev;
	bool sortsize;
	bool sorttime;
	bool recurs;
} option_t;

#endif /* HLS_H */
