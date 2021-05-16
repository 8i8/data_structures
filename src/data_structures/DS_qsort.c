#include "DS_stack_ptr.h"
#include <string.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  qsort
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef int (*comp)(const void *, const void *);
static void swap(char *i, char *j, size_t width);
static char *partition(char *l, char *r, size_t width, comp fn);

/*
 * DS_qsort: generic qsort function.h> This function avoids stack smashing by way
 * of a heap allocated stack of pointers, pointers to the addresses of the data
 * that is to be sorted.
 */
void DS_qsort(void *base, size_t nel, size_t width, comp fn)
{
	PStack stack, *buf;
	char *b, *e, *l, *r, *p;
	buf = &stack;

	/* The number of elements becomes an index, if there is nothing to
	 * sort; return. */
	if (nel > 1)
		nel--;
	else
		return;

	DS_stack_ptr_new(buf, nel+1);

	b = base;
	e = b+nel*width;

	DS_stack_ptr_push(buf, b);
	DS_stack_ptr_push(buf, e);

	/* When the stack is empty the sorting is complete */
	while (buf->ptr > 0)
	{
		r = DS_stack_ptr_pop(buf);
		l = DS_stack_ptr_pop(buf);

		/* Sort, greater and less than the rightmost objects value,
		 * returning the rightmost object sorted into its correct
		 * position as the pivot point */
		p = partition(l, r, width, fn);

		if (p-width > l) {
			DS_stack_ptr_push(buf, l);
			DS_stack_ptr_push(buf, p-width);
		}

		if (p+width < r) {
			DS_stack_ptr_push(buf, p+width);
			DS_stack_ptr_push(buf, r);
		}
	}

	DS_stack_ptr_free(buf);
}

/*
 * partition: Divides and sorts the given array, l and r are the extremities of
 * the worked section of the array and the width is the size of each array item
 * in bytes.
 */
static char *partition(char *l, char *r, size_t width, comp fn)
{
	char *i;
	int t;

	/*
	 * The value of the right most object is taken to be the value with
	 * which to partition the array; The pivot point.h> Iterate over the
	 * objects between the given extremities 'l' & 'r'; Call the current
	 * object 'i'.h> If 'i' is smaller than the rightmost value 'r', swap it
	 * with the leftmost 'l'.h> Augmenting the leftmost position leaving
	 * behind the object that has been swapped.h> We have now moved all
	 * objects smaller than the rightmost to the left side.
	 */
	for (i = l, t = 0; i < r; i += width, t = 0) {
		if ((t = (fn)(i, r)) < 0) {
			swap(l, i, width);
			l += width;
		} else if (t == 0) {
			/* If the comparison returns 0, swap only if l and i
			 * are not the same object; This check avoids a lot of
			 * unessasary swapping. */
			if (l != i)
				swap(l, i, width);
			l += width;
		}
	}
	/*
	 * Swap the rightmost object and the current left, it is now
	 * positioned with all the objects smaller than it to its left and
	 * greater to its right, becoming the pivot point; Return its
	 * position.
	 */
	swap(l, r, width);

	return l;
}

/*
 * Swap for 'width' places.
 */
static void swap(char *l, char *r, size_t width)
{
	char tmp[256];
	size_t len;

	while (width) {
		len = (sizeof tmp < width) ? sizeof tmp : width;
		memcpy(tmp, l, len);
		memcpy(l, r, len);
		memcpy(r, tmp, len);
		l += len;
		r += len;
		width -= len;
	}
}

