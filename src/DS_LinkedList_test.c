#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DS_Struct.h"
#include "DS_LinkedList.h"

int print(void *list)
{
	if (list == NULL)
		return -1;

	DS_LinkedList *out;
	out = (DS_LinkedList*)list;
	printf("%s", out->data.str);

	return 0;
}

int print_n(void *list, void *n)
{
	if (list == NULL || n == NULL)
		return -1;

	static size_t i;
	size_t *num;
	num = n;
	DS_LinkedList *out;
	out = (DS_LinkedList*)list;

	if (i++ < *num)
		printf("%s", out->data.str);

	return 0;
}

void add_test(DS_LinkedList *node, Data *data, size_t num)
{
	size_t i;
	int pass = 1;

	printf("%s() ~ ", __func__);

	for (i = 0; i < num; i++) {
		sprintf(data->str, "%lu", i);
		data->len = strlen(data->str);
		if((node = DS_LinkedList_add(node, *data)) == NULL) {
			printf("failed.\n");
			pass = 0;
			break;
		}
	}

	if (pass) {
		print(node);
		printf(" ~ passed.\n");
	}
}

void get_test(DS_LinkedList *node, size_t num)
{
	printf("%s() ~ ", __func__);

	if ((node = DS_LinkedList_get(node, num)) == NULL)
		printf("failed.\n");
	else {
		print(node);
		printf(" ~ passed.\n");
	}
}

void output_test(DS_LinkedList *node, size_t var)
{
	printf("%s() ~ ", __func__);
	if (DS_LinkedList_output(node, &var, print_n))
		printf(" ~ failed.\n");
	else
		printf(" ~ passed.\n");
}

void insert_test(DS_LinkedList *node, Data *data, size_t index)
{
	printf("%s() ~ ", __func__);
	sprintf(data->str, "%s", "I used to be number 120");
	data->len = strlen(data->str);

	if (DS_LinkedList_insert(node, index, *data))
		printf(" ~ insert failed.\n");
	else if ((node = DS_LinkedList_get(node, index+1)) == NULL)
		printf(" ~ get failed.\n");
	else
		print(node), printf(" ~ passed.\n");
}

void remove_test(DS_LinkedList *node, size_t index)
{
	printf("%s() ~ ", __func__);
	if (DS_LinkedList_remove(node, index))
		printf(" ~ remove failed.\n");
	else if ((node = DS_LinkedList_get(node, index+1)) == NULL)
		printf(" ~ get failed.\n");
	else {
		printf("index ");
		print(node), printf(" ~ passed.\n");
	}
}

void set_test(DS_LinkedList *node, size_t index, Data *data)
{
	printf("%s() ~ ", __func__);
	sprintf(data->str, "%s", "I have replased the number 120");
	data->len = strlen(data->str);

	if ((node = DS_LinkedList_set(node, index, *data)) == NULL)
		printf(" ~ failed.\n");
	else
		print(node), printf(" ~ passed.\n");
}

void clear_test(DS_LinkedList *node)
{
	printf("%s() ~ ", __func__);
	if (DS_LinkedList_clear(node))
		printf(" ~ failed.\n");
	else
		printf("Use valgrind to be certain ~ passed.\n");
}

void DS_LinkedList_test(void)
{
	DS_LinkedList head;
	head.next = NULL;
	Data d, *data;
	data = &d;

	add_test(&head, data, 1001);   // 1000
	get_test(&head, 500);          // 500
	output_test(&head, 10);        // 0123456789
	insert_test(&head, data, 119); // I used to be number 120.
	remove_test(&head, 119);       // index 120
	set_test(&head, 119, data);
	clear_test(head.next);
}

