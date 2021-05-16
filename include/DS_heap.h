#include "DS_struct.h"

#ifndef heap_data_
#define heap_data_
typedef struct heap_data {
	Data data;
	unsigned set:1;
} H_data;
#endif

#ifndef ds_heap_
#define ds_heap_
typedef struct ds_heap {
	H_data *heap;
	unsigned cur_id;
	unsigned end;
	unsigned len;
	short max;
	int (*comp)(const void*, const void*);
} DS_heap;
#endif

/* DS_heap_max_init: Initalise a heap priority queue that returns the greatest
 * value first */
DS_heap *DS_heap_init(DS_heap *heap, int(*comp)(const void*, const void*));

/* DS_heap_function: Change the sort funtion the heap struct */
DS_heap *DS_heap_function(DS_heap *heap, int(*comp)(const void*, const void*));

/* DS_heap_add: Add data to a heap structure */
int DS_heap_add(DS_heap *h, const H_data data);

/* DS_heap_pop: Pop the value from the root of the heap, cascade the heap up to
 * fill the available space */
H_data DS_heap_pop(DS_heap *h);

void DS_heap_free(DS_heap *h);
