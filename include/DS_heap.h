#include "DS_struct.h"

#ifndef _heap_data_
#define _heap_data_
typedef struct heap_data {
	Data data;
	unsigned set:2;
} H_data;
#endif

#ifndef _ds_heap_
#define _ds_heap_
typedef struct ds_heap {
	H_data *heap;
	unsigned cur_id;
	unsigned len;
	short max;
} DS_heap;
#endif

/* DS_heap_max_init: Initalise a heap priority queue that returns the greatest
 * value first */
DS_heap *DS_heap_init(DS_heap *heap);

/* DS_heap_add: Add data to a heap structure */
int DS_heap_add(DS_heap *h, const H_data data, int(*)(const void*, const void*));

/* DS_heap_pop: Pop the value from the root of the heap, cascade the heap up to
 * fill the available space */
H_data DS_heap_pop(DS_heap *h, int(*comp)(const void*, const void*));

void DS_heap_free(DS_heap *h);
