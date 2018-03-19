#include "../data_structures/DS_ListSort.h"
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

void DS_ListSort_test()
{
	DS_LinkedList *list = NULL;

	DS_LinkedList_add_string(&list, "2 world!\n");
	DS_LinkedList_add_string(&list, "1 hello,\n");
	DS_LinkedList_add_string(&list, "4 two\n");
	DS_LinkedList_add_string(&list, "5 three\n");
	DS_LinkedList_add_string(&list, "4 two\n");
	DS_LinkedList_add_string(&list, "4 two\n");
	DS_LinkedList_add_string(&list, "3 one\n");

	DS_ListSort(&list, compare);

	DS_LinkedList_print(&list);
	DS_LinkedList_clear(&list);
}

