#include "../data_structures/DS_Vector.h"
#include "../general/DS_Timer.h"
#include "../general/DS_Error.h"
#include <stdlib.h>
#include <string.h>

void vector_test_init(DS_Vector *list, Data *data, size_t n)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	strcpy(data->str, "oOo");
	data->len = strlen(data->str);

	time_start();
	if ((list = DS_Vector_init(list, data, n)) == NULL)
		printf(" ~ failed.\n");
	else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("str = %s ", list->data[0].str);
		printf("len = %lu capacity = %lu\n", list->len, list->capacity);
	}
}

void vector_test_add(DS_Vector *list, Data *data, size_t index)
{
	size_t i;
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	for (i = 0; i < index; i++) {
		sprintf(data->str, "n:%lu", i+2);
		data->len = strlen(data->str);
		if (DS_Vector_add(list, data)) {
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

void vector_test_get(DS_Vector *list, size_t index)
{
	Data *data;
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	if ((data = DS_Vector_get(list, index)) == NULL)
		printf(" ~ failed.\n");
	else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("str = %s\n", data->str);
	}
}

void vector_test_insert(DS_Vector *list, size_t index, Data *data)
{
	double time = 0;
	int i;
	printf("%s()\t ~ ", __func__);
	sprintf(data->str, "oOo");
	data->len = strlen(data->str);

	time_start();
	if (DS_Vector_insert(list, index, data)) {
		printf(" ~ failed.\n");
		time_stop();
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		for (i = 3; index < list->len && i; index++, i--)
			printf("%s ", list->data[index].str);
		putchar('\n');
	}
}

void vector_test_remove(DS_Vector *list, size_t index)
{
	double time = 0;
	int i;
	printf("%s()\t ~ ", __func__);

	time_start();
	if (DS_Vector_remove(list, index)) {
		printf(" ~ failed.\n");
		time_stop();
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		for (i = 3; index < list->len && i; index++, i--)
			printf("%s ", list->data[index].str);
		putchar('\n');
	}
}

void vector_test_free(DS_Vector *list)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	time_start();
	DS_Vector_free(list);
	time = time_stop();
	printf("%fs ~ passed.\t", time);
}

void DS_Vector_test()
{
	DS_Vector list;
	Data d, *data;
	data = &d;

	time_start();
	time_loop();
	time_stop();

	vector_test_init(&list, data, 4);
	vector_test_add(&list, data, 9999999);
	vector_test_get(&list, 9999999);
	vector_test_insert(&list, 5000000, data);
	vector_test_remove(&list, 5000000);
	vector_test_free(&list);
}
