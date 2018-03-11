#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/DS_BinarySearch.h"
#include "DS_Struct.h"

#define LEN 100000000

int data_cmp(void *a, void *b)
{
	Data *da, *db;
	int state;
	da = (Data*)a;
	db = (Data*)b;

	if (da->len > db->len)
		state = 1;
	else if (da->len < db->len)
		state = -1;
	else
		state = 0;

	return state;
}

int DS_BinarySearch_test(void)
{
	Data *data, test;
	data = malloc(LEN * sizeof test);
	unsigned i, x;
	x = 0;
	test.len = LEN/2-1;

	for (i = 0; i < LEN; i++)
		data[i].len = i;

	x = DS_BinarySearch(&data[0], sizeof test, LEN, &test, data_cmp);

	printf("%lu is at index number %d\n", test.len, x);
	free(data);

	return 0;
}
