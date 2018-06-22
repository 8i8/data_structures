#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/DS_binary_search.h"
#include "DS_struct.h"

#define LEN 100000000

int data_cmp(void *a, void *b)
{
	Data *da, *db;
	int state;
	da = (Data*)a;
	db = (Data*)b;

	if (da->num > db->num)
		state = 1;
	else if (da->num < db->num)
		state = -1;
	else
		state = 0;

	return state;
}

int DS_binary_search_test(void)
{
	Data *data, test;
	data = malloc(LEN * sizeof test);
	unsigned i, x;
	x = 0;
	test.num = LEN/2-1;

	for (i = 0; i < LEN; i++)
		data[i].num = i;

	x = DS_binary_search(&data[0], sizeof test, LEN, &test, data_cmp);

	printf("%lu is at index number %d\n", test.num, x);
	free(data);

	return 0;
}
