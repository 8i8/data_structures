#include "DS_heap.h"
#include <stdlib.h>
#include <string.h>

#define INIT 1024
#define MIN(a, b) ((a)<(b) ? (a) : (b))
static int unit = sizeof(H_data);

/*
 * DS_heap_init: Initialise a heap priority queue that returns the greatest
 * value first.
 */
DS_heap *DS_heap_init(DS_heap *heap, int(*comp)(const void*, const void*))
{
	heap->comp = comp;
	heap->heap = calloc(INIT, unit);
	heap->end = INIT;
	heap->max = 1;
	heap->cur_id = 1;
	heap->len = 0;
	return heap;
}

/*
 * DS_heap_function: Change the sort funtion the heap struct.
 */
DS_heap *DS_heap_function(DS_heap *heap, int(*comp)(const void*, const void*))
{
	heap->comp = comp;
	return heap;
}

void swap(void* h1, void* h2, unsigned len)
{
	char *d1 = (char*)h1;
	char *d2 = (char*)h2;
	char tmp[256];
	size_t l;

	while (len) {
		l = MIN(sizeof tmp, len);
		memcpy(tmp, d1, l);
		memcpy(d1, d2, l);
		memcpy(d2, tmp, l);
		d1 += l;
		d2 += l;
		len -= l;
	}
}

/*
 * heap_bubble_up: raise the latest entry from the end of the heap, to wherever
 * it should be.
 */
void heap_bubble_up(
					DS_heap *h,
					unsigned id)
{
	unsigned half = id/2;
	while (id > 1 && h->comp(&h->heap[id], &h->heap[half]) > 0) {
		swap(&h->heap[id], &h->heap[half], unit);
		id = half;
		half = id/2;
	}
}

/*
 * DS_heap_add: Add data to a heap structure.
 */
int DS_heap_add(
					DS_heap *h,
					const H_data data)
{
	unsigned id = h->cur_id;

	if (id > h->end)
		return 1;

	memcpy(&h->heap[id], &data, unit);
	h->heap[id].set |= 1;
	h->cur_id++;
	h->len++;
	heap_bubble_up(h, id);

	return 0;
}

struct index {
	unsigned cur;
	unsigned next;
	unsigned prev;
	unsigned from;
};

enum branch { LEFT, RIGHT };

/*
 * erase: Overwrite the given node with '\0' characters.
 */
static void erase(void* h1, unsigned len)
{
	char *d1 = (char*)h1;
	memset(d1, '\0', len);
}

static struct index set_indexes(struct index id)
{
	id.prev = id.cur;
	id.cur = id.next;
	id.next = id.cur << 1;
	return id;
}

/*
 * DS_heap_pop: Pop the value from the root of the heap, cascade the heap up to
 * fill the available space, ejecting the zombie node.
 */
H_data DS_heap_pop(DS_heap *h)
{
	H_data pop;
	struct index id = { 1, 2, 0, 0 };
	pop = h->heap[1];

	/* While there are still values beneath the zombie node in the heap,
	 * keep it cascading down */
	while (h->heap[id.next].set || h->heap[id.next+1].set)
	{
		/* If both branches are used, bubble the appropriate one up */
		if (h->heap[id.next].set && h->heap[id.next+1].set)
		{
			int n;
			/* Compare, then do the necessary */
			if ((n = h->comp(&h->heap[id.next], &h->heap[id.next+1])) >= 0)
				memcpy(&h->heap[id.cur], &h->heap[id.next], unit);
			else
				memcpy(&h->heap[id.cur], &h->heap[++id.next], unit);
		}

		/* If only one branch exists, swap with this */
		else if (h->heap[id.next].set)
			memcpy(&h->heap[id.cur], &h->heap[id.next], unit);

		/* or that */
		else if (h->heap[id.next+1].set)
			memcpy(&h->heap[id.cur], &h->heap[++id.next], unit);

		/* Set values so as to move down the branch */
		id = set_indexes(id);
	}

	erase(&h->heap[id.cur], unit);
	h->cur_id--;
	h->len--;

	return pop;
}

void DS_heap_free(DS_heap *h)
{
	free(h->heap);
}

