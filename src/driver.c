#include "tests/DS_LinkedList_test.h"
#include "tests/DS_DLinkedList_test.h"
#include "tests/DS_Vector_test.h"
#include "tests/DS_BinarySearch_test.h"
#include "widgets/widget.h"
#include <stdio.h>
#include <stdint.h>

/*
 * TODO Assignment https://www.youtube.com/watch?v=ocO3T5cdaBg&feature=youtu.be&t=9m
 * implement using unsorted array and sorted linked list.
 *
 * TODO implement a priority queue with a binary tree an array and a heap
 *
 * TODO Write Huffman compression using the queue, do so in a way that makes
 * the algorithm used to formulate the compression is interchangeable; test
 * and time the results.
 */

int main(void)
{
	DS_LinkedList_test();
	DS_DLinkedList_test();
	//DS_BinarySearch_test();
	//DS_Vector_test();

	//unsigned a, ia = 255;
	
	//W_Print_binary(ia, 16), putchar('\n');
	//a = getbits(ia, 14, 15);
	//W_Print_binary(a, 16), putchar('\n');

	return 0;
}

