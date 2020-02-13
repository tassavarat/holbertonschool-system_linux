#ifndef LAPS_H
#define LAPS_H
#define READ_SIZE BUFSIZ

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * struct listfd - singly linked list of file descriptors
 * @fd: file descriptor
 * @rd: if list has been read
 * @head: pointer to head of listchar linked list
 * @next: pointer to next node
 */
typedef struct listfd
{
	int fd;
	size_t rd;
	struct listchar *head;
	struct listfd *next;
} listfd;

/**
 * struct listchar - singly linked list of strings
 * @line: line number
 * @s: string
 * @size: size of string
 * @next: pointer to next node
 */
typedef struct listchar
{
	size_t line;
	char *s;
	size_t size;
	struct listchar *next;
} listchar;

char *_getline(const int fd);

#endif /* LAPS_H */
