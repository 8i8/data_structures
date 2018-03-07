#include "DS_ArrayList.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * DS_ArrayList: Initiate an ArrayList with an itial size of 2^n spaces.
 */
DS_ArrayList *DS_ArrayList_init(DS_ArrayList *list, Data *data, unsigned int size)
{
	size_t capacity = 1 << size;

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
 * DS_ArrayList_add: Add data struct to the end of the list, if no places
 * remain then grow the list.
 */
int DS_ArrayList_add(DS_ArrayList *list, Data *data)
{
	if (list->len < list->capacity)
		memcpy(&list->data[list->len++], data, sizeof(Data));
	else {
		list->capacity *= 2;
		if ((list->data = realloc(list->data, (sizeof(Data) * list->capacity))) == NULL) {
			printf("%s: error: memory allocation failed.", __func__);
			return -1;
		}
		memcpy(&list->data[list->len++], data, sizeof(Data));
	}
	return 0;
}

/*
 * DS_ArrayList_insert: Insert a Data struct into the list at the given index,
 * if required, grow the list.
 */
int DS_ArrayList_insert(DS_ArrayList *list, size_t index, Data *data)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer..", __func__);
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
		list->capacity *= 2;
		if ((list->data = realloc(list->data, (sizeof(Data) * list->capacity))) == NULL) {
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
 * DS_ArrayList_remove: Remove the node at index n.
 */
int DS_ArrayList_remove(DS_ArrayList *list, size_t index)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer..", __func__);
		return -1;
	} else if (index >= list->len) {
		printf("%s: error: index out of bounds.", __func__);
		return -1;
	}

	Data *stop;
	stop = &list->data[index];

	//memmove(stop-1, stop, list->len - index - 1);
	memcpy(stop-1, stop, list->len - index - 1);

	return 0;
}

/*
 * DS_LinkedList_get: Returns the Data struct, if there is one at the given index.
 */
Data *DS_ArrayList_get(DS_ArrayList *list, size_t index)
{
	if (index >= list->len) {
		printf("%s: error: index out of bounds.", __func__);
		return NULL;
	}
	return &list->data[index];
}

void DS_ArrayList_free(DS_ArrayList *list)
{
	free(list->data);
}
