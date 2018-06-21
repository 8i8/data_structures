/*
 * add(value)
 * get(index)
 * size()
 * remove(index)
 * index_of(value)
 * toString()
 */
#include "../tests/DS_Struct.h"
#include <stdio.h>
 
typedef struct DS_Vector {
	Data *data;
	size_t len;
	size_t capacity;
} DS_Vector;

/* DS_Vector: Initiate an Vector with an itial size of 2^n spaces */
DS_Vector *DS_Vector_init(DS_Vector *list, Data *data, unsigned int size);

/* DS_Vector_add: Add data struct to the end of the list, if no places
 * remain then grow the list */
int DS_Vector_add(DS_Vector *list, Data *data);

/* DS_Vector_insert: Insert a Data struct into the list at the given index,
 * if required, grow the list */
int DS_Vector_insert(DS_Vector *list, size_t index, Data *data);

/* DS_Vector_remove: Remove the node at index n */
int DS_Vector_remove(DS_Vector *list, size_t index);

/* DS_LinkedList_get: Returns the Data struct, if there is one at the given
 * index */
Data *DS_Vector_get(DS_Vector *list, size_t index);

/* DS_Vector_free: Free allocated memory */
DS_Vector *DS_Vector_free(DS_Vector *list);

