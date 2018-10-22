#include "DS_merge_sort.h"
#include "GE_timer.h"
#include <string.h>

//int compare(void *left, void *right)
//{
//	if (!left && !right)
//		return 0;
//	else if (!left)
//		return 1;
//	else if (!right)
//		return -1;
//	Data *str1, *str2;
//	str1 = (Data*)left;
//	str2 = (Data*)right;
//
//	return strcmp(str1->str, str2->str);
//}

#define NUM 1000

void DS_merge_sort_d_test()
{
	DS_linked_list *list = NULL;
	char str[16];
	size_t i, j;
	j = NUM;

	for (i = 0; i < NUM; i++, j--) {
		sprintf(str, "%010lu\n", j);
		DS_linked_list_add_string(&list, str);
	}

	//DS_merge_sort(&list, compare);
//	DS_merge_sort_cut(&list, compare);
	DS_linked_list_print(&list);
	DS_linked_list_clear(&list);
}

