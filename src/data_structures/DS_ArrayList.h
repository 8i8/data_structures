/*
 * add(value)
 * get(index)
 * size()
 * remove(index)
 * index_of(value)
 * toString()
 */
#include "DS_Struct.h"
#include <stdio.h>
 
typedef struct DS_ArrayList {
	Data *data;
	size_t len;
	size_t capacity;
} DS_ArrayList;

DS_ArrayList *DS_ArrayList_init(DS_ArrayList *list, Data *data, unsigned int size);

Data *DS_ArrayList_get(DS_ArrayList *list, size_t index);

int DS_ArrayList_add(DS_ArrayList *list, Data *data);

int DS_ArrayList_insert(DS_ArrayList *list, size_t index, Data *data);

int DS_ArrayList_remove(DS_ArrayList *list, size_t index);

void DS_ArrayList_free(DS_ArrayList *list);
