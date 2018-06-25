/*
 * DS_linked_list
 */
#include <stdio.h>
#include "DS_struct.h"

#ifndef _ds_linked_list_
#define _ds_linked_list_
typedef struct _ds_linked_list {
	Data data;
	struct _ds_linked_list *next;
} DS_linked_list;
#endif

/* DS_linked_list_add: Create the next node and add data */
DS_linked_list **DS_linked_list_add(DS_linked_list **list, Data data);

/* DS_linked_list_add_string: Create the next node in the list and add data */
DS_linked_list **DS_linked_list_add_string(DS_linked_list **list, char *str);

/* DS_linked_list_get: Returns the node at the given index, if that index
 * exists */
DS_linked_list **DS_linked_list_get(DS_linked_list **list, size_t num);

/* DS_linked_list_do: Itterate over the intire list, perform given function
 * on each node */
int DS_linked_list_do(DS_linked_list **list, void *var, int(*func)(void*, void*));

/* DS_linked_list_insert: Insert a new node at current location */
DS_linked_list **DS_linked_list_insert(DS_linked_list **list, Data data);

/* DS_linked_list_insert_at: Insert a new node before node n */
DS_linked_list **DS_linked_list_insert_at(DS_linked_list **list, size_t num, Data data);

/* DS_linked_list_insert_conditional: Insert a new node conditionaly. */
DS_linked_list **DS_linked_list_insert_conditional(DS_linked_list **list, Data data,
						Data compare, int(*func)(void*, void*));

/* DS_linked_list_remove: Remove and free the node at the given index */
DS_linked_list **DS_linked_list_remove(DS_linked_list **list, size_t num);

/* DS_linked_list_fwd: Fastforward n nodes, if node is null return an error */
DS_linked_list **DS_linked_list_fwd(DS_linked_list **list, size_t num);

/*  DS_linked_list_set: Set the data at index n to be the given data */
DS_linked_list **DS_linked_list_set(DS_linked_list **list, size_t index, Data data);

/* DS_linked_list_size: Returns the quantity of nodes in a linked list */
size_t DS_linked_list_size(DS_linked_list **list);

/* DS_linked_list_print: Print list */
void DS_linked_list_print(DS_linked_list **list);

/* DS_linked_list_clear: Destroy all nodes in the list */
int DS_linked_list_clear(DS_linked_list **list);

