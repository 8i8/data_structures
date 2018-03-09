#include "DS_LinkedList.h"
#include "../general/DS_Error.h"
#include <stdlib.h>
#include <string.h>

/*
 * DS_LinkedList_Init: Initialise a linked list on the heap if NULL, else fill
 * in with relevent data for a stack allocated head.
 */
DS_LinkedList *DS_LinkedList_init(DS_LinkedList *list) 
{
	if (list == NULL) {
		if ((list = malloc(sizeof(DS_LinkedList))) == NULL) {
			DS_Error_set("%s: memory allocation failed.", __func__);
			return NULL;
		}
		/* TODO this code is not generic and requires the use of a head
		struct with differeing type to the node to be so. */
		strcpy(list->data.str, "HEAP");
		list->data.len = 4;
	} else {
		strcpy(list->data.str, "STACK");
		list->data.len = 5;
	}

	list->next = NULL;
	return list;
}

/*
 * DS_LinkedList_add: Create the next node in the list and add data.
 */
DS_LinkedList *DS_LinkedList_add(DS_LinkedList *list, Data data)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	while (list->next != NULL)
		list = list->next;

	if ((list->next = malloc(sizeof(DS_LinkedList))) == NULL) {
		DS_Error_set("%s: memory allocation failed.", __func__);
		return NULL;
	}

	list = list->next;
	list->data = data;
	list->next = NULL;

	return list;
}

/*
 * DS_LinkedList_get: Returns the requested node if it exists, NULL if not.
 * The for loop itteration starts at 1 to avoid the case that the head of the
 * list, assuming that it can easily be stack allocated.
 */
DS_LinkedList *DS_LinkedList_get(DS_LinkedList *list, size_t num)
{
	size_t i;

	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	/* num starts at 1 to avoid the head node, returning n from the current
	 * node not inclusive of list. */
	for (i = 1; i <= num && list->next != NULL; i++)
		list = list->next;

	/* Stop if the requested node does not exist */
	if (i <= num && list->next == NULL) {
		DS_Error_set("%s: num out of bounds.", __func__);
		return NULL;
	}

	return list;
}

/*
 * DS_LinkedList_output: Iterate over the entire list, performing the given
 * function upon each node.
 */
int DS_LinkedList_output(DS_LinkedList *list, void *var, int(*func)(void*, void*))
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
 * DS_LinkedList_insert: Insert a new node before node n.
 */
DS_LinkedList *DS_LinkedList_insert(DS_LinkedList *list, size_t num, Data data)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_Error_set("%s: num out of bounds.", __func__);
		return NULL;
		/* Get node, but not number one; You are already there */
	} else if ((num != 1) && (list = DS_LinkedList_get(list, num - 1)) == NULL) {
		DS_Error_set("%s: ", __func__);
		return NULL;
	}

	/* We should now bw at node n - 1, insert a node here. */
	DS_LinkedList *temp = list->next;

	if((list->next = malloc(sizeof(DS_LinkedList))) == NULL) {
		DS_Error_set("%s: memory allocation failed.", __func__);
		list->next = temp;
		return NULL;
	}

	list->next->data = data;
	list->next->next = temp;

	return list->next;
}

/*
 * DS_LinkedList_remove: Remove and free the node at the given index.
 */
DS_LinkedList *DS_LinkedList_remove(DS_LinkedList *list, size_t num)
{
	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_Error_set("%s: Are you trying to free the lists head?", __func__);
		return NULL;
		/* Get node, not if num is 1 it is the current node; Deal with the
		 * case of removing the first node  */
	} else if ((num != 1) && (list = DS_LinkedList_get(list, num - 1)) == NULL) {
		DS_Error_set("%s: ", __func__);
		return NULL;
		/* Deal with the next node being the NULL terminator */
	} else if (list->next == NULL) {
		DS_Error_set("%s: warning: num is the end of the list.", __func__);
		return list;
	}

	/* Remove the node */
	DS_LinkedList *temp = list->next;
	list->next = list->next->next;
	free(temp);

	/* Return the current node and not NULL if you have just removed the last
	 * node */
	return (list->next == NULL) ? list : list->next;
}

/*
 *  DS_LinkedList_set: Set the data at index n to be the given data.
 */
DS_LinkedList *DS_LinkedList_set(DS_LinkedList *list, size_t index, Data data)
{
	if (list == NULL) { 
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if ((list = DS_LinkedList_get(list, index)) == NULL) {
		DS_Error_set("%s: ", __func__);
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
		DS_Error_set("%s: NULL pointer.", __func__);
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
		DS_Error_set("%s: NULL pointer.", __func__);
		return -1;
	}

	if (list->next == NULL) {
		DS_Error_set("%s: warning: nothing to free.", __func__);
		return 0;
	}

	/* Skip forwards one to avoid freeing the head */
	list = list->next;

	DS_LinkedList *temp;
	while (list->next != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
	free(list);

	return 0;
}

