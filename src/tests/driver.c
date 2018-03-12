#include "DS_LinkedList_test.h"
#include "DS_DLinkedList_test.h"
#include "DS_Vector_test.h"
#include "DS_BinarySearch_test.h"
#include "../widgets/widget.h"
#include <stdio.h>
#include <stdint.h>

/*
 * TODO test ffw and rwd for the linkedlists.
 *
 * TODO impliment a priority queue with a binary tree an array and a heap
 *
 * TODO Write Huffman compression using the queue, do so in a way that makes
 * the algorithem used to formulate the compression is interchangable; test
 * and time the results.
 */

int main(void)
{
	DS_LinkedList_test();
	//DS_DLinkedList_test();
	//DS_BinarySearch_test();
	//DS_Vector_test();

	//unsigned a, ia = 255;
	
	//W_Print_binary(ia, 16), putchar('\n');
	//a = getbits(ia, 14, 15);
	//W_Print_binary(a, 16), putchar('\n');

	return 0;
}

