/*
 * DS_LinkedList
 *
 * void add(int value)
 * void clear()
 * int get(int index)
 * void insert(int index, int value)
 * void remove(int index)
 * void set(int index, void *value)
 * bool isEmpty(const List)
 * int size()
 */
#include <stdio.h>
#include "DS_Struct.h"

typedef struct DS_LinkedList {
	struct DS_LinkedList *next;
	Data data;
} DS_LinkedList;

DS_LinkedList *DS_LinkedList_Init(DS_LinkedList *list);

DS_LinkedList *DS_LinkedList_add(DS_LinkedList *list, Data data);

DS_LinkedList *DS_LinkedList_get(DS_LinkedList *list, size_t index);

int DS_LinkedList_insert(DS_LinkedList *list, size_t index, Data data);

int DS_LinkedList_remove(DS_LinkedList *list, size_t index);

DS_LinkedList *DS_LinkedList_set(DS_LinkedList *list, size_t index, Data data);

int DS_LinkedList_output(DS_LinkedList *list, void *var, int(*func)(void*, void*));

int DS_LinkedList_clear(DS_LinkedList *list);

