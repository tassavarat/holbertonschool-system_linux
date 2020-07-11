#include "list.h"
#include <stdio.h>	/* debug */

/**
 * prime_factors - factorise a number into a list of prime factors
 * @s: string representation of the number to factorise
 *
 * Return: list of prime factors
 */
list_t *prime_factors(char const *s)
{
	list_t *list;

	if (s == NULL)
		return (NULL);
	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list = list_init(list);
	return (list);
}
