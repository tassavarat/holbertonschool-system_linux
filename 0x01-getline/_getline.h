#ifndef LAPS_H
#define LAPS_H
#define READ_SIZE BUFSIZ

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * struct listchar - singly linked list of strings
 * @line: line number
 * @s: string
 * @next: pointer to next node
 */
typedef struct listchar
{
	size_t line;
	char s[BUFSIZ];
	struct listchar *next;
} listchar;

char *_getline(const int fd);

#endif /* LAPS_H */
