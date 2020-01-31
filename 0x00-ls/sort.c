#include "hls.h"

/**
 * _qsort - sorts given data
 * @entries: data to sort
 * @lo: lower boundry
 * @hi: upper boundry
 */
void _qsort(struct content **entries, int lo, int hi)
{
	unsigned int p;

	if (lo < hi)
	{
		p = partition(*&entries, lo, hi);
		_qsort(*&entries, lo, p - 1);
		_qsort(*&entries, p + 1, hi);
	}
}

/**
 * partition - partitions given data into pieces for sorting
 * @entries: data to sort
 * @lo: lower boundry
 * @hi: upper boundry
 *
 * Return: partition position
 */
int partition(struct content **entries, int lo, int hi)
{
	char *pivot;
	int i, j;

	pivot = (*entries)[hi].name;
	i = lo;
	for (j = lo; j < hi; ++j)
		if (cmpstringp((*entries)[j].name, pivot) < 0)
		{
			swap(*&entries, i, j);
			++i;
		}
	swap(*&entries, i, hi);
	return (i);
}

/**
 * swap - swaps given data
 * @entries: data to swap
 * @i: first index being swapped to
 * @j: second index being swapped to
 */
void swap(struct content **entries, int i, int j)
{
	char tmp[256];

	_strcpy(tmp, (*entries)[j].name);
	_strcpy((*entries)[j].name, (*entries)[i].name);
	_strcpy((*entries)[i].name, tmp);
}
