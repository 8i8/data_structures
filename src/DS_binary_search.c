#include "DS_binary_search.h"
#include <stdio.h>

int DS_binary_search(
				void *left,
				unsigned width,
				unsigned num,
				void *x,
				int (*func)(void*, void*))
{
	char *obj;
	obj = (char*)left;
	register unsigned low, high, mid;
	register int comp;

	comp = -1;
	low = 0;
	high = num - 1;
	mid = low + high / 2;

	while ((comp = (*func)(x, obj + mid * width)) && low < high)
	{
		if (comp > 0)
			low = mid + 1;
		else
			high = mid - 1;

		mid = low + high / 2;
	}	

	if (comp == 0)
		return mid;

	return -1;
}

