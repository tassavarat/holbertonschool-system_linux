#include "laps.h"

/**
 * printstate - prints race state
 * @head: pointer to pointer of head
 */
void printstate(linkedlist **head)
{
	linkedlist **cur;

	printf("Race state:\n");
	for (cur = head; *cur; cur = &(*cur)->next)
		printf("Car %i [%lu laps]\n", (*cur)->n, (*cur)->lap);
}

/**
 * insertsort - inserts linked list in a sorted order
 * @head: pointer to pointer of head node
 * @new: pointer to new node
 */
void insertsort(linkedlist **head, linkedlist *new)
{
	linkedlist **cur;

	cur = head;
	while (*cur && new->n > (*cur)->n)
		cur = &(*cur)->next;
	new->next = *cur;
	*cur = new;
}

/**
 * createnode - creates new linked list node
 * @id: car id
 *
 * Return: created linked list node
 */
linkedlist *createnode(int id)
{
	linkedlist *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->n = id;
	new->lap = 0;
	new->next = NULL;
	return (new);
}

/**
 * checknew - checks for new car id
 * @head: pointer to pointer of head
 * @id: pointer to array of id's
 * @size: size of array
 */
void checknew(linkedlist **head, int *id, size_t size)
{
	linkedlist **cur;
	size_t i;

	for (i = 0; i < size; ++i)
	{
		for (cur = head; *cur; cur = &(*cur)->next)
			if (id[i] == (*cur)->n)
			{
				++(*cur)->lap;
				break;
			}
		if (!*cur)
		{
			printf("Car %i joined the race\n", id[i]);
			insertsort(head, createnode(id[i]));
		}
	}
}

/**
 * race_state - tracks number of laps made by cars in a race
 * @id: array of int representing "identifier" of each car
 * @size: array size
 */
void race_state(int *id, size_t size)
{
	static linkedlist *head;
	linkedlist *cur;

	cur = head;
	if (size)
	{
		checknew(&head, id, size);
		printstate(&head);
	}
	else
	{
		while (cur)
		{
			cur = cur->next;
			free(head);
			head = cur;
		}
	}
}
