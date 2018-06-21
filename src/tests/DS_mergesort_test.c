#include "../data_structures/DS_mergesort.h"
#include "../general/DS_Timer.h"
#include <string.h>

int compare(void *left, void *right)
{
	if (!left && !right)
		return 0;
	else if (!left)
		return 1;
	else if (!right)
		return -1;
	Data *str1, *str2;
	str1 = (Data*)left;
	str2 = (Data*)right;

	return strcmp(str1->str, str2->str);
}

#define NUM 1000

void DS_mergesort_test()
{
	DS_LinkedList *list = NULL;
	char str[16];
	size_t i, j;
	j = NUM;

	for (i = 0; i < NUM; i++, j--) {
		sprintf(str, "%010lu\n", j);
		DS_LinkedList_add_string(&list, str);
	}

	//DS_mergesort(&list, compare);
	DS_mergesort_cut(&list, compare);
	DS_LinkedList_print(&list);
	DS_LinkedList_clear(&list);
}
