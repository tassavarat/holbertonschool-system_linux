#include "hls.h"

void swap(struct content **entries, int i, int j)
{
	char tmp[256];

	_strcpy(tmp, (*entries)[j].name);
	_strcpy((*entries)[j].name, (*entries)[i].name);
	_strcpy((*entries)[i].name, tmp);
}

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
