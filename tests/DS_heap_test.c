#include "DS_heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * FN_data_strcmp: Compare Data one and two, the value should be a single char and
 * the result alphabetical order as per the ASCII char numbering system.
 */
int FN_data_strcmp(const void *v1, const void *v2)
{
	Data *d1, *d2;
	d1 = (Data*) v1;
	d2 = (Data*) v2;

	return strcmp(d1->str, d2->str);
}

/*
 * FN_data_strcmp: Compare Data one and two, the value should be a single char and
 * the result alphabetical order as per the ASCII char numbering system.
 */
int FN_data_intcmp(const void *v1, const void *v2)
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
	DS_heap_add(h, set_string("ccc"), FN_data_intcmp);
	DS_heap_add(h, set_string("bb"), FN_data_intcmp);
	DS_heap_add(h, set_string("eeeee"), FN_data_intcmp);
	DS_heap_add(h, set_string("a"), FN_data_intcmp);
	DS_heap_add(h, set_string("dddd"), FN_data_intcmp);
	DS_heap_add(h, set_string("ggggggg"), FN_data_intcmp);
	DS_heap_add(h, set_string("ffffff"), FN_data_intcmp);
	DS_heap_add(h, set_string("hhhhhhhh"), FN_data_intcmp);
	DS_heap_add(h, set_string("ccc"), FN_data_intcmp);
	DS_heap_add(h, set_string("bb"), FN_data_intcmp);
	DS_heap_add(h, set_string("eeeee"), FN_data_intcmp);
	DS_heap_add(h, set_string("a"), FN_data_intcmp);
	DS_heap_add(h, set_string("dddd"), FN_data_intcmp);
	DS_heap_add(h, set_string("ggggggg"), FN_data_intcmp);
	DS_heap_add(h, set_string("ffffff"), FN_data_intcmp);
	DS_heap_add(h, set_string("hhhhhhhh"), FN_data_intcmp);
}

void print_heap(DS_heap *h, int len)
{
	for (int i = 1; i <= len; i++)
		printf("id : %d: %s\n", i, h->heap[i].data.str);
	putchar('\n');
}

int DS_heap_test(void)
{ H_data node;
	DS_heap heap;
	DS_heap_init(&heap);
	load_data(&heap);
      	print_heap(&heap, 16);

	int i = 16;

	while (i--) {
		node = DS_heap_pop(&heap, FN_data_intcmp);
		printf("Popped : %s\n", node.data.str);
	}

	DS_heap_free(&heap);

	return 0;
}
