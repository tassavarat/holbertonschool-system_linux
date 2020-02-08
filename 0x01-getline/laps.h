#ifndef LAPS_H
#define LAPS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * struct linkedlist - singly linked list of integers
 * @n: integer value
 * @lap: current lap
 * @next: pointer to next node
 */
typedef struct linkedlist
{
	int n;
	size_t lap;
	struct linkedlist *next;
} linkedlist;

/* laps.c */
void race_state(int *id, size_t size);

#endif /* LAPS_H */
