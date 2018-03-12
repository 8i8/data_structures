#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef int (*comp)(const void *, const void *);

/*
 * Swap for 'width' places, 'i' to 'j' on the given string.
 */
static int _swap(void *string, size_t i, size_t j, size_t width)
{
	if (i == j)
		return; /* return directly if swap is not required */

	char *s = string;
	char temp[width];

	//TODO Time the difference between these two pieces of code.
	memcpy(temp, s[i * width], width);
	memcpy(s[i * width], s[j * width], width);
	memcpy(s[j * width], temp, width);

	//char temp;
	//char *s = string;

	//i = i*width;
	//j = j*width;

	////TODO Replace this function with memcpy()
	//size_t k;
	//for (k = 0; k < width; k++) {
	//	t        = *(s+k+i);
	//	*(s+k+i) = *(s+k+j);
	//	*(s+k+j) = t;
	//}

	return 0;
}

/*
 * DS_Quicksort: Generic quicksort function.
 */
int DS_Quicksort(void *base, size_t num, size_t width, comp fn)
{
	unsigned char *b = (void*)base;
	size_t i, left, last;

	left = 0;
	if (num)
		num--;

	if (left >= num)
		return 0;

	_swap(b, left, num / 2, width);

	last = left;
	for (i = left + 1; i <= num; i++)
		if ((fn)(&b[i * width], &b[left * width]) < 0)
			_swap(b, ++last, i, width);

	_swap(b, left, last, width);

	DS_Quicksort(b + (left * width), last - left, width, fn);
	DS_Quicksort(b + ((last + 1) * width), num - last, width, fn);
}

