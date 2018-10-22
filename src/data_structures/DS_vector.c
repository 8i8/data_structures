#include "DS_vector.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * DS_Vector: Initiate an Vector with an itial size of 2^n spaces.
 */
DS_Vector *DS_Vector_init(DS_Vector *list, Data *data, unsigned int size)
{
	size_t capacity = size << 1;

	if ((list->data = malloc(sizeof(Data) * capacity)) == NULL) {
		printf("%s: error: memory allocation failed.", __func__);
		return NULL;
	}

	list->capacity = capacity;
	list->len = 1;
	memcpy(&list->data[0], data, sizeof(Data));

	return list;
}

/*
 * DS_Vector_add: Add data struct to the end of the list, if no places
 * remain then grow the list.
 */
int DS_Vector_add(DS_Vector *list, Data *data)
{
	if (list->len < list->capacity)
		memcpy(&list->data[list->len++], data, sizeof(Data));
	else {
		list->capacity <<= 1;
		if (!list->capacity || (list->data = realloc(
						list->data,
						(sizeof(Data) * list->capacity)
						)) == NULL)
		{
			printf("%s: error: memory allocation failed.", __func__);
			return -1;
		}
		memcpy(&list->data[list->len++], data, sizeof(Data));
	}
	return 0;
}

/*
 * DS_Vector_insert: Insert a Data struct into the list at the given index,
 * if required, grow the list.
 */
int DS_Vector_insert(DS_Vector *list, size_t index, Data *data)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.h>.h>", __func__);
		return -1;
	} else if (index >= list->len) {
		printf("%s: error: index out of bounds.", __func__);
		return -1;
	}

	Data *stop;
	stop = &list->data[index];

	if (list->len < list->capacity)
		memmove(stop+1, stop, list->len - index);
	else {
		list->capacity <<= 1;
		if (!list->capacity && (list->data = realloc(
						list->data,
						(sizeof(Data) * list->capacity)
						)) == NULL)
		{
			printf("%s: error: memory allocation failed.", __func__);
			return -1;
		}
		memmove(stop+1, stop, list->len - index);
	}

	memcpy(stop, data, sizeof(Data));
	list->len++;

	return 0;
}

/*
 * DS_Vector_remove: Remove the node at index n.
 */
int DS_Vector_remove(DS_Vector *list, size_t index)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.h>.h>", __func__);
		return -1;
	} else if (index >= list->len) {
		printf("%s: error: index out of bounds.", __func__);
		return -1;
	}

	Data *stop;
	stop = &list->data[index];

	memmove(stop-1, stop, list->len - index - 1);
	//memcpy(stop-1, stop, list->len - index - 1);

	return 0;
}

/*
 * DS_linked_list_get: Returns the Data struct, if there is one at the given index.
 */
Data *DS_Vector_get(DS_Vector *list, size_t index)
{
	if (index >= list->len) {
		printf("%s: error: index out of bounds.", __func__);
		return NULL;
	}
	return &list->data[index];
}

/*
 * DS_Vector_free: Free allocated memory.
 */
DS_Vector *DS_Vector_free(DS_Vector *list)
{
	free(list->data);
	return NULL;
}
