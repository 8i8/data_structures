#include "DS_ArrayList.h"
#include <stdlib.h>
#include <string.h>
#include "DS_Timer.h"

void arraylist_test_init(DS_ArrayList *list, Data *data, size_t n)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	sprintf(data->str, "init OK!");
	data->len = strlen(data->str);

	time_start();
	if ((list = DS_ArrayList_init(list, data, n)) == NULL)
		printf(" ~ failed.\n");
	else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("str = %s ", list->data[0].str);
		printf("len = %lu capacity = %lu\n", list->len, list->capacity);
	}
}

void arraylist_test_add(DS_ArrayList *list, Data *data, size_t index)
{
	size_t i;
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	for (i = 0; i < index; i++) {
		sprintf(data->str, "n:%lu", i+2);
		data->len = strlen(data->str);
		if (DS_ArrayList_add(list, data)) {
			printf(" ~ failed.\n");
			time_stop();
			break;
		}
	}
	if (i == index) {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("str = %s ", list->data[list->len-1].str);
		printf("len = %lu capacity = %lu\n", list->len, list->capacity);
	}
}

void arraylist_test_get(DS_ArrayList *list, size_t index)
{
	Data *data;
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	if ((data = DS_ArrayList_get(list, index)) == NULL)
		printf(" ~ failed.\n");
	else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("str = %s\n", data->str);
	}
}

void arraylist_test_insert(DS_ArrayList *list, size_t index, Data *data)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	sprintf(data->str, "I was inserted here");
	data->len = strlen(data->str);

	time_start();
	if (DS_ArrayList_insert(list, index, data)) {
		printf(" ~ failed.\n");
		time_stop();
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("%s ", list->data[index].str);
		printf("%s ", list->data[index + 1].str);
		printf("%s\n", list->data[index + 2].str);
	}
}

void arraylist_test_remove(DS_ArrayList *list, size_t index)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	if (DS_ArrayList_remove(list, index)) {
		printf(" ~ failed.\n");
		time_stop();
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("%s ", list->data[index].str);
		printf("%s ", list->data[index + 1].str);
		printf("%s\n", list->data[index + 2].str);
	}
}

void arraylist_test_free(DS_ArrayList *list)
{
	free(list->data);
}

void DS_ArrayList_test()
{
	DS_ArrayList list;
	Data d, *data;
	data = &d;
	int i;

	time_start();
	for (i = 0; i < 1000000; )
		i++;
	time_stop();

	arraylist_test_init(&list, data, 4);
	arraylist_test_add(&list, data, 9999999);
	arraylist_test_get(&list, 9999999);
	arraylist_test_insert(&list, 5000000, data);
	arraylist_test_remove(&list, 5000000);

	arraylist_test_free(&list);
}
