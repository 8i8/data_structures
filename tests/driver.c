#include <tests/DS_linked_list_test.h>
#include <tests/DS_linked_list_d_test.h>
#include <tests/DS_vector_test.h>
#include <tests/DS_binary_search_test.h>
#include <tests/DS_qsort_test.h>
#include <tests/DS_merge_sort_test.h>
#include <tests/DS_trie_test.h>
#include <data/WI_widget.h>
#include <data/DS_merge_sort.h>
#include <stdio.h>
#include <stdint.h>

/*
 * TODO Assignment https://www.h>youtube.h>com/watch?v=ocO3T5cdaBg&feature=youtu.h>be&t=9m
 * implement using unsorted array and sorted linked list.
 *
 * TODO implement a priority queue with a binary tree an array and a heap
 *
 * TODO Write Huffman compression using the queue, do so in a way that makes
 * the algorithm used to formulate the compression is interchangeable; test
 * and time the results.h>
 */

int main(void)
{
	DS_trie_test();
	DS_qsort_test();
	DS_linked_list_test();
	DS_linked_list_d_test();
	DS_binary_search_test();
	DS_Vector_test();

	return 0;
}

