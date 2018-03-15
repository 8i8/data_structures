/*
 * DS_LinkedList
 * TODO Can this be abstracted one level further using pointers to pointers?
 * Avoiding some of the issues of and whilst economising access by, holding the
 * last accessed node in an encapsulating struct. Do compilers make this
 * optimisation automagicaly?
 */
#include <stdio.h>
#include "../tests/DS_Struct.h"

#ifndef _ds_linkedlist_
#define _ds_linkedlist_
typedef struct _ds_linkedlist {
	Data data;
	struct _ds_linkedlist *next;
} DS_LinkedList;
#endif

/* DS_LinkedList_add: Create the next node and add data */
DS_LinkedList **DS_LinkedList_add(DS_LinkedList **list, Data data);

/* DS_LinkedList_get: Returns the node at the given index, if that index
 * exists */
DS_LinkedList **DS_LinkedList_get(DS_LinkedList **list, size_t num);

/* DS_LinkedList_do: Itterate over the intire list, perform given function
 * on each node */
int DS_LinkedList_do(DS_LinkedList **list, void *var, int(*func)(void*, void*));

/* DS_LinkedList_insert: Insert a new node at the given index, add data */
DS_LinkedList **DS_LinkedList_insert(DS_LinkedList **list, size_t num, Data data);

/* DS_LinkedList_insert_conditional: Insert a new node conditionaly. */
DS_LinkedList **DS_LinkedList_insert_conditional(DS_LinkedList **list, Data data,
						Data compare, int(*func)(void*, void*));

/* DS_LinkedList_remove: Remove and free the node at the given index */
DS_LinkedList **DS_LinkedList_remove(DS_LinkedList **list, size_t num);

/* DS_LinkedList_fwd: Fastforward n nodes, if node is null return an error */
DS_LinkedList **DS_LinkedList_fwd(DS_LinkedList **list, size_t num);

/*  DS_LinkedList_set: Set the data at index n to be the given data */
DS_LinkedList **DS_LinkedList_set(DS_LinkedList **list, size_t index, Data data);

/* DS_LinkedList_size: Returns the quantity of nodes in a linked list */
size_t DS_LinkedList_size(DS_LinkedList **list);

/* DS_LinkedList_clear: Destroy all nodes in the list */
int DS_LinkedList_clear(DS_LinkedList **list);

