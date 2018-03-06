#include "DS_LinkedList.h"
#include <stdlib.h>

/*
 * DS_LinkedList_Init: Initalise a linked list, creates the first node and sets
 * the size to 1, adds data.
 */
DS_LinkedList *DS_LinkedList_Init(DS_LinkedList *list)
{
	list = malloc(sizeof(DS_LinkedList));
	list->next = NULL;
	return list;
}

/*
 * DS_LinkedList_add: Create the next node in the list and add data, keep track
 * of the list size.
 */
DS_LinkedList *DS_LinkedList_add(DS_LinkedList *list, Data data)
{
	if (list == NULL)
		DS_LinkedList_Init(list);

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
	if (list == NULL)
		return -1;

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
	if ((list = DS_LinkedList_get(list, index)) == NULL)
		return -1;

	DS_LinkedList *temp = list->next;
	list->next = malloc(sizeof(DS_LinkedList));
	list = list->next;
	list->data = data;
	list->next = temp;

	return 0;
}

/*
 * DS_LinkedList_clear: Destroy all nodes in the list.
 */
int DS_LinkedList_clear(DS_LinkedList *list)
{
	if (list == NULL)
		return -1;
	DS_LinkedList *temp;
	while (list->next != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
	free(list);
	return 0;
}

