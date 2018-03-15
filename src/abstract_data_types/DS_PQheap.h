/*
 * pq.enqueue(element, priority); add element at the given priority.
 * pq.dequeue(); removes/returns the highest priority value.
 * pq.peek(); returns highest priority value.
 * pq.is_empty(); returns true if if the queue contains no elements.
 * pq.size(); returns the number of elements in the queue.
 * pq.to_string(); returns a string such as "{3, 42, -7, 15}"
 * pq.change_priority(value, pri); alter an existing elements priority.
 * pq.clear(); empty the set.
 *
 * For the heap implimentation, when adding add to the bottom and bubble up by
 * priority. When removing the highest priority take the last value to fill its
 * place and then bubble that down. This way we can avoid moving every element
 * over by one place, which is far leass efficient. The Heap is (log n) time.
 */
