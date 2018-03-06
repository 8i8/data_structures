#include "DS_ArrayList.h"
#include <stdlib.h>
#include <string.h>

void arraylist_init_test(DS_ArrayList *list, Data *data, size_t n)
{
	printf("%s() ~ ", __func__);
	sprintf(data->str, "init OK!");
	data->len = strlen(data->str);

	if ((list = DS_ArrayList_init(list, data, n)) == NULL)
		printf(" ~ failed.\n");
	else {
		printf("str = %s ", list->data[0].str);
		printf("len = %lu capacity = %lu", list->len, list->capacity);
		printf(" ~ passed.\n");
	}
}

void arraylist_add_test(DS_ArrayList *list, Data *data, size_t index)
{
	size_t i;
	printf("%s() ~ ", __func__);

	for (i = 0; i < index; i++) {
		sprintf(data->str, "number %lu", i+2);
		data->len = strlen(data->str);
		if (DS_ArrayList_add(list, data)) {
			printf(" ~ failed.\n");
			break;
		}
	}
	if (i == index) {
		printf("str = %s ", list->data[list->len-1].str);
		printf("len = %lu capacity = %lu", list->len, list->capacity);
		printf(" ~ passed.\n");
	}
}

void free_test(DS_ArrayList *list)
{
	free(list->data);
}

void DS_ArrayList_test()
{
	DS_ArrayList list;
	Data d, *data;
	data = &d;

	arraylist_init_test(&list, data, 16);
	arraylist_add_test(&list, data, 999999);

	free_test(&list);
}
