/*
 * DS_linked_list_d
 */
#include <stdio.h>
#include "../tests/DS_struct.h"

#ifndef _ds_linked_list_d_
#define _ds_linked_list_d_
typedef struct _ds_linked_list_d {
	Data data;
	struct _ds_linked_list_d *prev;
	struct _ds_linked_list_d *next;
} DS_linked_list_d;
#endif

/* DS_linked_list_d_new_node: Internal function for creating new list nodes */
DS_linked_list_d *DS_linked_list_d_new_node(Data data);

/* DS_linked_list_d_add: Create the next node in the list and add data */
DS_linked_list_d **DS_linked_list_d_add(DS_linked_list_d **list, Data data);

/* DS_linked_list_d_get: Returns the node at the given index, if that index
 * exists */
DS_linked_list_d **DS_linked_list_d_get(DS_linked_list_d **list, size_t index);

/* DS_linked_list_d_do: Itterate over the intire list, perform given function
 * on each node */
int DS_linked_list_d_do(DS_linked_list_d **list, void *var, int(*func)(void*, void*));

/* DS_linked_list_d_insert: Insert a new node at tyhe current location */
DS_linked_list_d **DS_linked_list_d_insert(DS_linked_list_d **list, Data data);

/* DS_linked_list_d_insert_at: Insert a new node before node n */
DS_linked_list_d **DS_linked_list_d_insert_at(DS_linked_list_d **list, size_t num, Data data);

/* DS_linked_list_d_remove: Remove and free the node at the given index */
DS_linked_list_d **DS_linked_list_d_remove(DS_linked_list_d **list, size_t num);

/* DS_linked_list_d_fwd: Fastforward n nodes, if node is null return an error */
DS_linked_list_d **DS_linked_list_d_fwd(DS_linked_list_d **list, size_t num);

/* DS_linked_list_d_rwd: Rewind n nodes, if node is the head return an error */
DS_linked_list_d **DS_linked_list_d_rwd(DS_linked_list_d **list, size_t num);

/*  DS_linked_list_d_set: Set the data at index n to be the given data */
DS_linked_list_d **DS_linked_list_d_set(DS_linked_list_d **list, size_t index, Data data);

/* DS_linked_list_d_size: Returns the quantity of nodes in a linked list */
size_t DS_linked_list_d_size(DS_linked_list_d **list);

/* DS_linked_list_d_clear: Destroy all nodes in the list */
int DS_linked_list_d_clear(DS_linked_list_d **list);

