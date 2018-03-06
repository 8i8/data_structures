#include "DS_ArrayList.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * ipow: Fast bitwise int pow.
 */
int ipow(int base, int exp)
{
	int result = 1;

	while (exp) {
		if (exp & 1)
	    		result *= base;
		exp >>= 1;
		base *= base;
	}
	return result;
}

/*
 * DS_ArrayList: Initiate an ArrayList with an itial size of 2^n spaces.
 */
DS_ArrayList *DS_ArrayList_init(DS_ArrayList *list, Data *data, unsigned int size)
{
	size_t capacity = 1 << size;
	Data *new;

	if ((new = malloc(sizeof(Data) * capacity)) == NULL) {
		printf("%s: error: memory allocation failed.", __func__);
		return NULL;
	}

	list->data = new;
	list->capacity = capacity;
	list->len = 1;
	memcpy(&list->data[0], data, sizeof(Data));

	return list;
}

/*
 * DS_ArrayList_add: Add data struct to the list, if no places remain then grow
 * the list.
 */
int DS_ArrayList_add(DS_ArrayList *list, Data *data)
{
	Data *new;

	if (list->len < list->capacity)
		memcpy(&list->data[list->len++], data, sizeof(Data));
	else {
		list->capacity *= 2;
		if ((new = realloc(list->data, (sizeof(Data) * list->capacity))) == NULL) {
			printf("%s: error: memory allocation failed.", __func__);
			return -1;
		}
		list->data = new;
		memcpy(&list->data[list->len++], data, sizeof(Data));
	}
	return 0;
}

