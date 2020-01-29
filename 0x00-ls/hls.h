#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

struct content
{
	char name[256];
};

/* string */
int _strcmp(char *s1, char *s2);
char *str_toupper(char *s);
char *_strcpy(char *dest, const char *src);
int cmpstringp(const char *p1, const char *p2);

/* sort */
void swap(struct content **entries, int i, int j);
int partition(struct content **entries, int lo, int hi);
void _qsort(struct content **entries, int lo, int hi);

#endif /* HLS_H */
