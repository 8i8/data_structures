#include "DS_linked_list.h"
#include "GE_error.h"
#include <stdlib.h>
#include <string.h>

/*
 * _ds_linked_list_new_node: Internal function for creating new list nodes.
 */
DS_linked_list *_ds_linked_list_new_node(Data data)
{
	DS_linked_list *new_node = NULL;
	if ((new_node = malloc(sizeof(DS_linked_list))) == NULL) {
		DS_error_set("%s: memory allocation failed.", __func__);
		return NULL;
	}
	new_node->next = NULL;
	new_node->data = data;

	return new_node;
}

/*
 * DS_linked_list_add: Create the next node in the list and add data.
 */
DS_linked_list **DS_linked_list_add(DS_linked_list **list, Data data)
{
	if (*list == NULL)
		*list = _ds_linked_list_new_node(data);
	else {
		while ((*list)->next != NULL)
			list = &(*list)->next;

		if (((*list)->next = _ds_linked_list_new_node(data)) == NULL) {
			DS_error_append("%s: ", __func__);
			return NULL;
		}
		list = &(*list)->next;
	}

	return list;
}

/*
 * DS_linked_list_add_string: Create the next node in the list and add data.
 */
DS_linked_list **DS_linked_list_add_string(DS_linked_list **list, char *str)
{
	Data data;
	strcpy(data.str, str);
	data.num = strlen(str);

	if (*list == NULL)
		*list = _ds_linked_list_new_node(data);
	else {
		while ((*list)->next != NULL)
			list = &(*list)->next;

		if (((*list)->next = _ds_linked_list_new_node(data)) == NULL) {
			DS_error_append("%s: ", __func__);
			return NULL;
		}
		list = &(*list)->next;
	}

	return list;
}

/*
 * DS_linked_list_get: Returns the requested node if it exists, NULL if it does
 * not.
 */
DS_linked_list **DS_linked_list_get(DS_linked_list **list, size_t num)
{
	size_t i;

	if (list == NULL || *list == NULL) {
		DS_error_set("%s: NULL pointer.", __func__);
		return NULL;
	}

	if (--num == SIZE_MAX) {
		DS_error_set("%s: list 0 does not exist, count starts at 1.", __func__);
		return NULL;
	}

	for (i = 0; i < num && (*list)->next != NULL; i++)
		list = &(*list)->next;

	if (i < num && (*list)->next == NULL) {
		DS_error_set("%s: Out of bounds.", __func__);
		return NULL;
	}

	return list;
}

/*
 * DS_linked_list_do: Iterate over the entire list, performing the given
 * function upon each node.
 */
int DS_linked_list_do(DS_linked_list **list, void *var, int(*func)(void*, void*))
{
	if (list == NULL || *list == NULL) {
		DS_error_set("%s: NULL pointer.", __func__);
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
 * DS_linked_list_insert: Insert a new node at current location.
 */
DS_linked_list **DS_linked_list_insert(DS_linked_list **list, Data data)
{
	DS_linked_list *new;

	if (list == NULL || *list == NULL) {
		DS_error_set("%s: NULL pointer.", __func__);
		return NULL;
	}
	if ((new = _ds_linked_list_new_node(data)) == NULL) {
		DS_error_append("%s: ", __func__);
		return NULL;
	}

	new->next = *list;
	*list = new;

	return list;
}

/*
 * DS_linked_list_insert_at: Insert a new node before node n.
 */
DS_linked_list **DS_linked_list_insert_at(DS_linked_list **list, size_t num, Data data)
{
	DS_linked_list *new;

	if (list == NULL || *list == NULL) {
		DS_error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_error_set("%s: Out of bounds.", __func__);
		return NULL;
		/* Get node, but not number one; You are already there */
	} else if ((num != 1) && (list = DS_linked_list_get(list, num)) == NULL) {
		DS_error_insert("%s: ", __func__);
		return NULL;
	}

	/* We should now be at node n - 1, insert a node here. */
	if ((new = _ds_linked_list_new_node(data)) == NULL) {
		DS_error_append("%s: ", __func__);
		return NULL;
	}

	new->next = *list;
	*list = new;

	return list;
}

/*
 * DS_linked_list_remove: Remove and free the node at the given index.
 */
DS_linked_list **DS_linked_list_remove(DS_linked_list **list, size_t num)
{
	DS_linked_list *old;

	if (list == NULL || *list == NULL) {
		DS_error_set("%s: Null pointer.", __func__);
		return NULL;
	} else if (num == 0) {
		DS_error_set("%s: Out of bounds.", __func__);
		return NULL;
		/* Get node, not if num is 1 it is the current node; Deal with the
		 * case of removing the first node  */
	} else if ((num != 1) && (list = DS_linked_list_get(list, num)) == NULL) {
		DS_error_insert("%s: ", __func__);
		return NULL;
	}

	/* Remove the node */
	old = *list;
	*list = (*list)->next;
	free(old);

	return list;
}

/*
 * DS_linked_list_fwd: Move forward n nodes and return the new node, if the node
 * is null return an error.
 */
DS_linked_list **DS_linked_list_fwd(DS_linked_list **list, size_t num)
{
	if (list == NULL || *list == NULL) {
		DS_error_set("%s: Null pointer.", __func__);
		return NULL;
	}

	while (*list != NULL && num)
		list = &(*list)->next, num--;

	if (*list == NULL) {
		DS_error_set("%s: Out of bounds, "
				"you have reached the end of the list.",
				__func__);
		return NULL;
	}

	return list;
}

/*
 *  DS_linked_list_set: Set the data at index n to be the given data.
 */
DS_linked_list **DS_linked_list_set(DS_linked_list **list, size_t num, Data data)
{
	if (list == NULL || *list == NULL) { 
		DS_error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if ((list = DS_linked_list_get(list, num)) == NULL) {
		DS_error_set("%s: ", __func__);
		return NULL;
	}

	(*list)->data = data;

	return list;
}

/*
 * DS_linked_list_size: Returns the quantity of nodes in a linked list.
 */
size_t DS_linked_list_size(DS_linked_list **list)
{
	size_t i = 0;

	if (list == NULL || *list == NULL) {
		DS_error_set("%s: NULL pointer.", __func__);
		return 0;
	}

	while(*list != NULL)
		list = &(*list)->next, ++i;

	return i;
}

/*
 * DS_linked_list_print: Print list.
 */
void DS_linked_list_print(DS_linked_list **list)
{
	while (*list)
		printf("%s", (*list)->data.str), list = &(*list)->next;
}

/*
 * DS_linked_list_clear: Destroy all nodes in the list.
 */
int DS_linked_list_clear(DS_linked_list **list)
{
	DS_linked_list *old;

	if (list == NULL || *list == NULL) {
		DS_error_set("%s: NULL pointer.", __func__);
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

