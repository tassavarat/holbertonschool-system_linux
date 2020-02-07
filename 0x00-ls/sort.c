#include "hls.h"

/**
 * revstringp - reverses regardless of case
 * @p1: first string
 * @p2: second string
 *
 * Return: positive or negative value whether p1 or p2 are greater
 */
int revstringp(const void *p1, const void *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp2, tp1));
}

/**
 * cmpstringp - copies strings to buffers and compares them regardless of case
 * @p1: first string
 * @p2: second string
 *
 * Return: positive or negative value whether p1 or p2 are greater
 */
int cmpstringp(const void *p1, const void *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp1, tp2));
}

/**
 * swap - swaps given data
 * @ent1: first data to swap
 * @ent2: second data to swap
 */
void swap(struct content *ent1, struct content *ent2)
{
	struct content tmp;

	tmp = *ent2;
	*ent2 = *ent1;
	*ent1 = tmp;
}

/**
 * partition - partitions given data into pieces for sorting
 * @entries: data to sort
 * @lo: lower boundry
 * @hi: upper boundry
 * @cmp: function pointer
 *
 * Return: partition position
 */
size_t partition(struct content *entries, ssize_t lo, ssize_t hi,
		int (*cmp)(const void *p1, const void *p2))
{
	char *piv;
	int i, j;

	piv = entries[hi].name;
	i = lo;
	for (j = lo; j < hi; ++j)
		if (cmp(entries[j].name, piv) <= 0)
		{
			swap(&entries[i], &entries[j]);
			++i;
		}
	swap(&entries[i], &entries[j]);
	return (i);
}

/**
 * _qsort - sorts given data
 * @entries: data to sort
 * @lo: lower boundry
 * @hi: upper boundry
 * @cmp: function pointer
 */
void _qsort(struct content *entries, ssize_t lo, ssize_t hi,
		int (*cmp)(const void *p1, const void *p2))
{
	size_t p;

	if (lo < hi)
	{
		p = partition(entries, lo, hi, cmp);
		_qsort(entries, lo, p - 1, cmp);
		_qsort(entries, p + 1, hi, cmp);
	}
}
