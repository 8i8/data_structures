#include "../data_structures/DS_LinkedList.h"
#include "../tests/DS_Struct.h"
#include "../general/DS_Error.h"

int _comp_test(void *v1, void *v2)
{
	Data *d1, *d2;
	d1 = (Data*) v1;
	d2 = (Data*) v2;

	return (char)*d1->str - (char)*d2->str;
}

/*
 * TODO Write function in linked lists to insert a new node at the current
 * spot.
 */
DS_LinkedList **_insert_alphanum_count(DS_LinkedList **list, Data data,
						int(*func)(void*, void*))
{
	int test;

	if (list == NULL) {
		DS_Error_set("%s: NULL pointer.", __func__);
		return NULL;
	} else if (*list == NULL) {
		DS_LinkedList_add(list, data);
		return list;
	}

	while (*list != NULL)
	{
		if ((test = (*func)((void*)&data, (void*)&(*list)->data)) < 0) {
			if ((DS_LinkedList_insert(list, data)) == NULL) {
				DS_Error_append("%s: ", __func__);
				return NULL;
			}
			break;
		} else if (test == 0) {
			(*list)->data.num++;
			break;
		} else if (test > 0)
			list = &(*list)->next;
		if (*list == NULL) {
			DS_LinkedList_add(list, data);
			break;
		}
	}

	return list;
}

DS_LinkedList **frequency_map(DS_LinkedList **list, FILE *fp)
{
	char c;
	Data data;

	while ((c = getc(fp)) != EOF) {
		data.str[0] = c, data.str[1] = '\0', data.num = 1;
		_insert_alphanum_count(list, data, _comp_test);
	}

	return list;
}

void print_frequency(DS_LinkedList **list)
{
	while (*list != NULL) {
		printf("%s ", (*list)->data.str);
		printf("%lu\n", (*list)->data.num);
		list = &(*list)->next;
	}
}

