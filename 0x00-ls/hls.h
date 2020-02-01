#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * struct content - stores entry information
 * @name: string buffer
 */
typedef struct content
{
	char name[256];
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

/* main */
unsigned int error(bool e, char *argv, char o);
void initoptions(struct option **opt);
void checkoptions(struct option **opt, char *argv[], const unsigned int i,
		const unsigned int j);

/* ls */
unsigned int ls(const int argc, char *argv[]);
content_t *preprocess(const int argc, char *argv[], unsigned int *numdir,
		DIR **dp);
unsigned int parse_args(unsigned int *numdir, char *argv[], int *file_a,
		int *dir_a);
content_t *handlecontent(const bool f, const unsigned int c, char *argv[],
		int *a);
void printcontent(const bool f, const int argc, char *argv,
		const unsigned int c, struct content *entries);

/* string */
char *_strcpy(char *dest, const char *src);
int cmpstringp(const char *p1, const char *p2);
char *str_toupper(char *s);
int _strcmp(char *s1, char *s2);

/* sort */
void _qsort(struct content **entries, int lo, int hi);
int partition(struct content **entries, int lo, int hi);
void swap(struct content **entries, int i, int j);

#endif /* HLS_H */
