/*
 * DS_LinkedList
 */
#include <stdio.h>
#include "DS_Struct.h"

typedef struct DS_LinkedList {
	struct DS_LinkedList *next;
	Data data;
} DS_LinkedList;

/* DS_LinkedList_Init: Initialise a linked list on the heap, creates the first
 * node and sets the size to 1 */
DS_LinkedList *DS_LinkedList_init(DS_LinkedList *list);

/* DS_LinkedList_add: Create the next node in the list and add data */
DS_LinkedList *DS_LinkedList_add(DS_LinkedList *list, Data data);

/* DS_LinkedList_get: Returns the node at the given index, if that index
 * exists */
DS_LinkedList *DS_LinkedList_get(DS_LinkedList *list, size_t index);

/* DS_LinkedList_output: Itterate over the intire list, perform given function
 * on each node */
int DS_LinkedList_output(DS_LinkedList *list, void *var, int(*func)(void*, void*));

/* DS_LinkedList_insert: Insert a new node at the given index, add data */
DS_LinkedList *DS_LinkedList_insert(DS_LinkedList *list, size_t index, Data data);

/* DS_LinkedList_remove: Remove and free the node at the given index */
DS_LinkedList *DS_LinkedList_remove(DS_LinkedList *list, size_t index);

/*  DS_LinkedList_set: Set the data at index n to be the given data */
DS_LinkedList *DS_LinkedList_set(DS_LinkedList *list, size_t index, Data data);

/* DS_LinkedList_size: Returns the quantity of nodes in a linked list */
size_t DS_LinkedList_size(DS_LinkedList *list);

/* DS_LinkedList_clear: Destroy all nodes in the list */
int DS_LinkedList_clear(DS_LinkedList *list);

