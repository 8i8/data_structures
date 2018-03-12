#include "DS_DLinkedList.h"
#include "../general/DS_Error.h"
#include <stdlib.h>
#include <string.h>

/*
 * DS_DLinkedList_init: Initialise a linked list on the heap if NULL, else fill
 * in with relevent data for a stack allocated head.
 */
DS_DLinkedList *DS_DLinkedList_init(DS_DLinkedList *list) 
{
	if (list == NULL) {
		if ((list = malloc(sizeof(DS_DLinkedList))) == NULL) {
			DS_Error_set("%s: memory allocation failed.", __func__);
			return NULL;
		}
		/* TODO this code is not generic and requires the use of a head
		struct with differeing type to the node to be so. */
		strcpy(list->data.str, "HEAP");
		list->data.len = 0;
	} else {
		strcpy(list->data.str, "STACK");
		list->data.len = 0;
	}

	list->next = NULL;
	list->prev = NULL;
	return list;
}

/*
 * DS_DLinkedList_add: Create the next node in the list and add data.
 */
DS_DLinkedList *DS_DLinkedList_add(DS_DLinkedList *list, Data data)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	while (list->next != NULL)
		list = list->next;

	if ((list->next = malloc(sizeof(DS_DLinkedList))) == NULL) {
		DS_Error_set("%s: memory allocation failed.", __func__);
		return NULL;
	}

	list->next->prev = list;
	list = list->next;
	list->data = data;
	list->next = NULL;

	return list;
}

/*
 * DS_DLinkedList_get: Returns the requested node if it exists, NULL if iit does
 * not.
 */
DS_DLinkedList *DS_DLinkedList_get(DS_DLinkedList *list, size_t num)
{
	size_t i;

	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	// TEST case.
	for (i = 0; i < num && list->next != NULL; i++)
		list = list->next;

	// TEST case.
	if (i < num && list->next == NULL) {
		DS_Error_set("%s: overflow, request out of bounds.", __func__);
		return NULL;
	}

	return list;
}

/*
 * DS_DLinkedList_do: Iterate over the entire list, performing the given
 * function upon each node.
 */
int DS_DLinkedList_do(DS_DLinkedList *list, void *var, int(*func)(void*, void*))
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
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
 * DS_DLinkedList_insert: Insert a new node before node n.
 */
DS_DLinkedList *DS_DLinkedList_insert(DS_DLinkedList *list, size_t num, Data data)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_Error_set("%s: num out of bounds.", __func__);
		return NULL;
		/* Get node, but not number one; You are already there */
	} else if ((num != 1) && (list = DS_DLinkedList_get(list, num - 1)) == NULL) {
		DS_Error_insert("%s: ", __func__);
		return NULL;
	}

	/* We should now bw at node n - 1, insert a node here. */
	DS_DLinkedList *temp = list->next;

	if((list->next = malloc(sizeof(DS_DLinkedList))) == NULL) {
		DS_Error_set("%s: memory allocation failed.", __func__);
		list->next = temp;
		return NULL;
	}

	list->next->data = data;
	list->next->prev = list;
	list->next->next = temp;
	if (temp != NULL)
		list->next->next->prev = list->next;

	return list->next;
}

/*
 * DS_DLinkedList_remove: Remove and free the node at the given index.
 */
DS_DLinkedList *DS_DLinkedList_remove(DS_DLinkedList *list, size_t num)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_Error_set("%s: Out of bounds; The head must be freed manualy.", __func__);
		return list;
		/* Get node, not if num is 1 it is the current node; Deal with the
		 * case of removing the first node  */
	} else if ((num != 1) && (list = DS_DLinkedList_get(list, num - 1)) == NULL) {
		DS_Error_insert("%s: ", __func__);
		return NULL;
		/* Deal with the next node being the NULL terminator */
	} else if (list->next == NULL) {
		DS_Error_insert("%s: Node out of bounds.", __func__);
		return NULL;
	}

	/* Remove the node */
	DS_DLinkedList *temp = list->next;
	list->next = list->next->next;
	if (list->next != NULL)
		list->next->prev = list;
	free(temp);

	return list->next;
}

/*
 * DS_DLinkedList_fwd: Fastforward n nodes, if node is null return an error.
 */
DS_DLinkedList *DS_DLinkedList_fwd(DS_DLinkedList *list, size_t num)
{
	for ( ;list != NULL && num; num--)
		list = list->next;

	if (list == NULL) {
		DS_Error_set("%s: Out of bounds"
				", you have reached the end of the list.", __func__);
		return NULL;
	}

	return list;
}

/*
 * DS_DLinkedList_rwd: Rewind n nodes, if node is the head return an error.
 */
DS_DLinkedList *DS_DLinkedList_rwd(DS_DLinkedList *list, size_t num)
{
	for ( ;list != NULL && num; num--)
		list = list->prev;

	if (list == NULL || (list->next == NULL && list->data.len == 0)) {
		DS_Error_set("%s: Out of bounds"
				", you have reached the head of the list.", __func__);
		return NULL;
	}

	return list;
}

/*
 *  DS_DLinkedList_set: Set the data at index n to be the given data.
 */
DS_DLinkedList *DS_DLinkedList_set(DS_DLinkedList *list, size_t index, Data data)
{
	if (list == NULL) { 
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if ((list = DS_DLinkedList_get(list, index)) == NULL) {
		DS_Error_set("%s: ", __func__);
		return NULL;
	}

	list->data = data;

	return list;
}

/*
 * DS_DLinkedList_size: Returns the quantity of nodes in a linked list.
 */
size_t DS_DLinkedList_size(DS_DLinkedList *list)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return 0;
	}

	size_t i = 0;
	while(list->next != NULL)
		list = list->next, ++i;

	return i;
}

/*
 * DS_DLinkedList_clear: Destroy all nodes in the list.
 */
int DS_DLinkedList_clear(DS_DLinkedList *list)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return -1;
	}

	if (list->next == NULL) {
		DS_Error_set("%s: warning: nothing to free.", __func__);
		return 0;
	}

	/* Skip forwards one to avoid freeing the head */
	list = list->next;

	DS_DLinkedList *temp;
	while (list->next != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
	free(list);

	return 0;
}

