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

/* main */
unsigned int error(bool e, char *argv, char o);

/* ls */
unsigned int ls(const int argc, char *argv[]);
content_t *preprocess(const int argc, char *argv[], unsigned int *numdir,
		DIR **dp, char *option_a);
unsigned int parse_args(unsigned int *numdir, char *argv[], char *option_a,
		int *file_a, int *dir_a);
content_t *handlecontent(const bool f, const unsigned int c, char *argv[],
		int *a);
void printcontent(const bool f, const int argc, char *argv, const unsigned int c,
		struct content *entries);

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
