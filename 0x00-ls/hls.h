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
	char name[256];
	char tperm[11];
	long lc;
	long uid;
	long gid;
	char *usr;
	char *grp;
	long siz;
	char mtim[12];
} content;

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
} option;

/* ls */
size_t ls(char *argv[]);

/* main */
size_t error(char *arg, char op, bool e, bool printed);
void cleanup(struct content *entries, struct content *dirs,
		struct option *opt);
void checkopt(struct option **opt, char *argv[], size_t i, size_t j);
void initoptions(struct option **opt);

/* strings */
char *_strcpy(char *dest, const char *src);
char *str_toupper(char *s);
int _strcmp(char *s1, char *s2);
size_t _strlen(const char *s);
char *_memcpy(char *dest, char *src, size_t n);

/* sort */
void _qsort(struct content *entries, ssize_t lo, ssize_t hi,
		int (*cmp)(const void *p1, const void *p2));
int cmpstringp(const void *p1, const void *p2);
int revstringp(const void *p1, const void *p2);

/* processargs */
size_t processargs(struct content **dirs, struct option *opt, char *argv[],
		size_t *file_a, size_t *dir_a, size_t status, DIR **dp,
		size_t fc, size_t dc, size_t erc, bool *printed);
void parsesym(char *arg, size_t *fc, size_t *dc, size_t *file_a, size_t *dir_a,
		size_t i, size_t len);

/* options */
bool filterhidden(struct dirent *ep, struct option *opt);
void linfo(char *dirstr, struct content *entries);

/* options2 */
void setug(struct content *entries, struct stat sb);
void plong(struct content *entries, size_t c, bool f, struct option *opt);
char *createpath(char *dirstr, char *entry);

#endif /* HLS_H */
