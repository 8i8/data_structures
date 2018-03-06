#include "DS_LinkedList.h"
#include <stdlib.h>

/*
 * DS_LinkedList_Init: Initalise a linked list on the heap, creates the first
 * node and sets the size to 1, adds data.
 */
DS_LinkedList *DS_LinkedList_Init(DS_LinkedList *list)
{
	if ((list = malloc(sizeof(DS_LinkedList))) == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return NULL;
	}

	list->next = NULL;
	return list;
}

/*
 * DS_LinkedList_add: Create the next node in the list and add data, keep track
 * of the list size.
 */
DS_LinkedList *DS_LinkedList_add(DS_LinkedList *list, Data data)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return NULL;
	}

	while (list->next != NULL)
		list = list->next;

	if ((list->next = malloc(sizeof(DS_LinkedList))) == NULL)
		return NULL;

	list = list->next;
	list->data = data;
	list->next = NULL;

	return list;
}

/*
 * DS_LinkedList_get: Returnes the node at the given index, if that index
 * exists.
 */
DS_LinkedList *DS_LinkedList_get(DS_LinkedList *list, size_t index)
{
	size_t i;

	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return NULL;
	}

	for (i = 0; i < index && list->next != NULL; i++)
		list = list->next;

	if (i <= index && list->next == NULL) {
		printf("%s: error: index out of bounds.", __func__);
		return NULL;
	}

	list = list->next;

	return list;
}

int DS_LinkedList_output(DS_LinkedList *list, void *var, int(*func)(void*, void*))
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return -1;
	}

	while (list->next != NULL) {
		list = list->next;
		if ((*func)((void*)list, (void*)var))
			return -1;
	}

	return 0;
}

/*
 * DS_LinkedList_insert: Insert a new node at the given index, add data and
 * keep track of the list size.
 */
int DS_LinkedList_insert(DS_LinkedList *list, size_t index, Data data)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return -1;
	} else if ((list = DS_LinkedList_get(list, index)) == NULL) {
		printf("%s: error: index returned NULL.", __func__);
		return -1;
	}

	DS_LinkedList *temp = list->next;
	if((list->next = malloc(sizeof(DS_LinkedList))) == NULL)
		return -1;

	list = list->next;
	list->data = data;
	list->next = temp;

	return 0;
}

/*
 * DS_LinkedList_remove: Remove and free the node at the given index.
 */
int DS_LinkedList_remove(DS_LinkedList *list, size_t index)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return -1;
	} else if ((list = DS_LinkedList_get(list, index-1)) == NULL) {
		printf("%s: error: index returned NULL.", __func__);
		return -1;
	} else if (list->next == NULL) {
		printf("%s: warning: index is already the end of the list.", __func__);
		return 0;
	}

	DS_LinkedList *temp = list->next;
	list->next = list->next->next;
	free(temp);

	return 0;
}

/*
 *  DS_LinkedList_set: Set the data at index n to be the given data.
 */
DS_LinkedList *DS_LinkedList_set(DS_LinkedList *list, size_t index, Data data)
{
	if (list == NULL) { 
		printf("%s: error: NULL pointer.", __func__);
		return NULL;
	} else if ((list = DS_LinkedList_get(list, index)) == NULL) {
		printf("%s: error: index returned NULL.", __func__);
		return NULL;
	}

	list->data = data;

	return list;
}

/*
 * DS_LinkedList_size: Returns the quantity of nodes in a linked list.
 */
size_t DS_LinkedList_size(DS_LinkedList *list)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return 0;
	}

	size_t i = 0;
	while(list->next != NULL)
		list = list->next, ++i;
	return i;
}

/*
 * DS_LinkedList_clear: Destroy all nodes in the list.
 */
int DS_LinkedList_clear(DS_LinkedList *list)
{
	if (list == NULL) {
		printf("%s: error: NULL pointer.", __func__);
		return -1;
	}

	DS_LinkedList *temp;
	while (list->next != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
	free(list);

	return 0;
}

