#include "DS_heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * FN_data_strcmp: Compare Data one and two, the value should be a single char and
 * the result alphabetical order as per the ASCII char numbering system.
 */
int FN_data_strcmp_asc(const void *v1, const void *v2)
{
	Data *d1, *d2;
	d1 = (Data*) v1;
	d2 = (Data*) v2;

	return strcmp(d1->str, d2->str);
}

int FN_data_strcmp_dsc(const void *v1, const void *v2)
{
	Data *d1, *d2;
	d1 = (Data*) v1;
	d2 = (Data*) v2;

	return strcmp(d2->str, d1->str);
}

/*
 * FN_data_strcmp: Compare Data one and two, the value should be a single char and
 * the result alphabetical order as per the ASCII char numbering system.
 */
int FN_data_int_decending(const void *v1, const void *v2)
{
	Data *d1, *d2;
	d1 = (Data*) v1;
	d2 = (Data*) v2;

	return d1->num - d2->num;
}

int FN_data_int_assending(const void *v1, const void *v2)
{
	Data *d1, *d2;
	d1 = (Data*) v1;
	d2 = (Data*) v2;

	return d2->num - d1->num;
}

H_data set_string(char *str)
{
	H_data h;
	h.data.num = strlen(str);
	memcpy(h.data.str, str, h.data.num+1);
	return h;
}

void load_data(DS_heap *h)
{
	DS_heap_add(h, set_string("ccc"));
	DS_heap_add(h, set_string("bb"));
	DS_heap_add(h, set_string("eeeee"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("dddd"));
	DS_heap_add(h, set_string("ggggggg"));
	DS_heap_add(h, set_string("ffffff"));
	DS_heap_add(h, set_string("hhhhhhhh"));
	DS_heap_add(h, set_string("ccc"));
	DS_heap_add(h, set_string("bb"));
	DS_heap_add(h, set_string("eeeee"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("dddd"));
	DS_heap_add(h, set_string("ggggggg"));
	DS_heap_add(h, set_string("ffffff"));
	DS_heap_add(h, set_string("hhhhhhhh"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("dddd"));
	DS_heap_add(h, set_string("ggggggg"));
	DS_heap_add(h, set_string("ffffff"));
	DS_heap_add(h, set_string("hhhhhhhh"));
	DS_heap_add(h, set_string("ccc"));
	DS_heap_add(h, set_string("bb"));
	DS_heap_add(h, set_string("eeeee"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("ccc"));
	DS_heap_add(h, set_string("bb"));
	DS_heap_add(h, set_string("eeeee"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("dddd"));
	DS_heap_add(h, set_string("ggggggg"));
	DS_heap_add(h, set_string("ffffff"));
	DS_heap_add(h, set_string("hhhhhhhh"));
	DS_heap_add(h, set_string("ccc"));
	DS_heap_add(h, set_string("bb"));
	DS_heap_add(h, set_string("eeeee"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("dddd"));
	DS_heap_add(h, set_string("ggggggg"));
	DS_heap_add(h, set_string("ffffff"));
	DS_heap_add(h, set_string("hhhhhhhh"));
	DS_heap_add(h, set_string("a"));
	DS_heap_add(h, set_string("dddd"));
	DS_heap_add(h, set_string("ggggggg"));
	DS_heap_add(h, set_string("ffffff"));
	DS_heap_add(h, set_string("hhhhhhhh"));
	DS_heap_add(h, set_string("ccc"));
	DS_heap_add(h, set_string("bb"));
	DS_heap_add(h, set_string("eeeee"));
	DS_heap_add(h, set_string("a"));
}

void pop_heap(DS_heap *heap)
{
	H_data node;
	unsigned i = heap->len;
	unsigned j = 0;
	while (i--) {
		node = DS_heap_pop(heap);
		printf("Popped %d : %s\n",j++, node.data.str);
	}
	putchar('\n');
}

void print_heap(DS_heap *heap)
{
	for (unsigned i = 1; i <= heap->len; i++)
		printf("id : %d: %s\n", i, heap->heap[i].data.str);
	putchar('\n');
}

int DS_heap_test(void)
{
	DS_heap heap;
	DS_heap_init(&heap, FN_data_strcmp_dsc);
	load_data(&heap);
	print_heap(&heap);
	pop_heap(&heap);
	//DS_heap_function(&heap, FN_data_strcmp_asc);
	//load_data(&heap);
	//print_heap(&heap);
	//pop_heap(&heap);
	DS_heap_free(&heap);

	return 0;
}
