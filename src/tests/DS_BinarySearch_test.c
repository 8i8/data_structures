#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/DS_BinarySearch.h"
#include "../data_structures/DS_Struct.h"

#define LEN 1000000

int data_cmp(void *a, void *b)
{
	Data *da, *db;
	size_t state;
	da = (Data*)a;
	db = (Data*)b;

	if (da->len > db->len)
		state = 1;
	else if (da->len < db->len)
		state = 2;
	else
		state = 0;

	return state;
}

int DS_BinarySearch_test(void)
{
	Data *data, test;
	data = malloc(LEN * sizeof test);
	size_t i, x;
	x = 0;
	test.len = 33;

	for (i = 0; i < LEN; i++)
		data[i].len = i;

	x = DS_BinarySearch(&data[0], sizeof test, LEN, &test, data_cmp);

	printf("%lu is at index number %lu\n", test.len, x);
	free(data);

	return 0;
}
