#include <ds/DS_BinarySearch.h>
#include <stdio.h>

unsigned DS_BinarySearch(void *left, unsigned width, unsigned num, void *x, int (*func)(void*, void*))
{
	char *obj;
	obj = (char*)left;
	register unsigned low, high, mid;
	int comp;

	comp = -1;
	low = 0;
	high = num - 1;
	mid = low + high / 2;

	while (((comp = (*func)((void*)x, (void*)(obj+(mid*width)))) != 0) && low < high) {

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

