#include "DS_LinkedList.h"
#include "../general/DS_Error.h"
#include <stdlib.h>
#include <string.h>

/*
 * _ds_linkedList_new_node: Internal function for creating new list nodes.
 */
DS_LinkedList *_ds_linkedList_new_node(Data data)
{
	DS_LinkedList *new_node = NULL;
	if ((new_node = malloc(sizeof(DS_LinkedList))) == NULL) {
		DS_Error_set("%s: memory allocation failed.", __func__);
		return NULL;
	}
	new_node->next = NULL;
	new_node->data = data;

	return new_node;
}

/*
 * DS_LinkedList_add: Create the next node in the list and add data.
 */
DS_LinkedList **DS_LinkedList_add(DS_LinkedList **list, Data data)
{
	if (*list == NULL)
		*list = _ds_linkedList_new_node(data);
	else {
		while ((*list)->next != NULL)
			list = &(*list)->next;

		if (((*list)->next = _ds_linkedList_new_node(data)) == NULL) {
			DS_Error_append("%s: ", __func__);
			return NULL;
		}
		list = &(*list)->next;
	}

	return list;
}

/*
 * DS_LinkedList_get: Returns the requested node if it exists, NULL if it does
 * not.
 */
DS_LinkedList **DS_LinkedList_get(DS_LinkedList **list, size_t num)
{
	size_t i;

	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	if (--num == SIZE_MAX) {
		DS_Error_set("%s: list 0 does not exist, count starts at 1.", __func__);
		return NULL;
	}

	for (i = 0; i < num && (*list)->next != NULL; i++)
		list = &(*list)->next;

	if (i < num && (*list)->next == NULL) {
		DS_Error_set("%s: Out of bounds.", __func__);
		return NULL;
	}

	return list;
}

/*
 * DS_LinkedList_do: Iterate over the entire list, performing the given
 * function upon each node.
 */
int DS_LinkedList_do(DS_LinkedList **list, void *var, int(*func)(void*, void*))
{
	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return -1;
	}

	while (*list != NULL) {
		if ((*func)((void*)list, (void*)var))
			return -1;
		list = &(*list)->next;
	}

	return 0;
}

/*
 * DS_LinkedList_insert: Insert a new node before node n.
 */
DS_LinkedList **DS_LinkedList_insert(DS_LinkedList **list, size_t num, Data data)
{
	DS_LinkedList *new;

	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_Error_set("%s: Out of bounds.", __func__);
		return NULL;
		/* Get node, but not number one; You are already there */
	} else if ((num != 1) && (list = DS_LinkedList_get(list, num)) == NULL) {
		DS_Error_insert("%s: ", __func__);
		return NULL;
	}

	/* We should now be at node n - 1, insert a node here. */
	if ((new = _ds_linkedList_new_node(data)) == NULL) {
		DS_Error_append("%s: ", __func__);
		return NULL;
	}

	new->next = *list;
	*list = new;

	return list;
}

/*
 * DS_LinkedList_insert_conditional: Insert a new node conditionaly.
 */
DS_LinkedList **DS_LinkedList_insert_conditional(DS_LinkedList **list, Data data,
						Data compare, int(*func)(void*, void*))
{
	DS_LinkedList *new;

	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	while (*list != NULL)
	{
	       if ((*func)((void*)&data, (void*)&compare))
	       {
			if ((new = _ds_linkedList_new_node(data)) == NULL) {
				DS_Error_append("%s: ", __func__);
				return NULL;
			}
			new->next = *list;
			*list = new;
	       }	       
	}

	return list;
}

/*
 * DS_LinkedList_remove: Remove and free the node at the given index.
 * TODO this function needs rethinking
 */
DS_LinkedList **DS_LinkedList_remove(DS_LinkedList **list, size_t num)
{
	DS_LinkedList *old;

	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: Null pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_Error_set("%s: Out of bounds.", __func__);
		return NULL;
		/* Get node, not if num is 1 it is the current node; Deal with the
		 * case of removing the first node  */
	} else if ((num != 1) && (list = DS_LinkedList_get(list, num)) == NULL) {
		DS_Error_insert("%s: ", __func__);
		return NULL;
	}

	/* Remove the node */
	old = *list;
	*list = (*list)->next;
	free(old);

	return list;
}

/*
 * DS_LinkedList_fwd: Move forward n nodes and return the new node, if the node
 * is null return an error.
 */
DS_LinkedList **DS_LinkedList_fwd(DS_LinkedList **list, size_t num)
{
	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: Null pointer.", __func__);
		return NULL;
	}

	while (*list != NULL && num)
		list = &(*list)->next, num--;

	if (*list == NULL) {
		DS_Error_set("%s: Out of bounds, you have reached the end of the list.", __func__);
		return NULL;
	}

	return list;
}

/*
 *  DS_LinkedList_set: Set the data at index n to be the given data.
 */
DS_LinkedList **DS_LinkedList_set(DS_LinkedList **list, size_t num, Data data)
{
	if (list == NULL || *list == NULL) { 
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if ((list = DS_LinkedList_get(list, num)) == NULL) {
		DS_Error_set("%s: ", __func__);
		return NULL;
	}

	(*list)->data = data;

	return list;
}

/*
 * DS_LinkedList_size: Returns the quantity of nodes in a linked list.
 */
size_t DS_LinkedList_size(DS_LinkedList **list)
{
	size_t i = 0;

	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return 0;
	}

	while(*list != NULL)
		list = &(*list)->next, ++i;

	return i;
}

/*
 * DS_LinkedList_clear: Destroy all nodes in the list.
 */
int DS_LinkedList_clear(DS_LinkedList **list)
{
	DS_LinkedList *old;

	if (list == NULL || *list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return -1;
	}

	while (*list != NULL) {
		old = *list;
		*list = (*list)->next;
		free(old);
	}
	free(*list);

	return 0;
}

