/*
 * pq.enqueue(element, priority); add element at the given priority.
 * pq.dequeue(); removes/returns the highest priority value.
 * pq.peek(); returns highest priority value.
 * pq.is_empty(); returns true if if the queue contains no elements.
 * pq.size(); returns the number of elements in the queue.
 * pq.to_string(); returns a string such as "{3, 42, -7, 15}"
 * pq.change_priority(value, pri); alter an existing elements priority.
 * pq.clear(); empty the set.
 */
#include "DS_PQLinkedList.h"
#include "../data_structures/DS_LinkedList.h"

void DS_PQLinkedList_init()
{
}

void DS_PQLinkedList_enqueue(Data *data)
{
	data->len = 5;
}
