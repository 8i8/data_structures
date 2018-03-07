#include <string.h>
#include "DS_Struct.h"
#include "DS_LinkedList.h"
#include "DS_Timer.h"

char output[255];
char *pt_out;

int print(void *list, char *tail)
{
	if (list == NULL)
		return -1;

	DS_LinkedList *out;
	out = (DS_LinkedList*)list;
	printf("%s%s", out->data.str, tail);

	return 0;
}

int print_n(void *list, void *n)
{
	if (list == NULL || n == NULL)
		return -1;

	size_t *num;
	num = n;
	DS_LinkedList *out;
	out = (DS_LinkedList*)list;

	if (pt_out - output < (int)*num)
		pt_out += sprintf(pt_out, out->data.str, strlen(out->data.str));

	return 0;
}

void linkedlist_test_init(DS_LinkedList *head)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	time_start();
	DS_LinkedList_init(head);
	time = time_stop();
	printf("%fs ~ passed. Head initiated.\n", time);
}

void linkedlist_test_add(DS_LinkedList *node, Data *data, size_t num)
{
	size_t i;
	double time = 0;
	int pass = 1;

	printf("%s()\t ~ ", __func__);

	time_start();
	for (i = 0; i < num; i++) {
		sprintf(data->str, "n:%lu", i+1);
		data->len = strlen(data->str);
		if((node = DS_LinkedList_add(node, *data)) == NULL) {
			time_stop();
			printf(" ~ failed.\n");
			pass = 0;
			break;
		}
	}
	time = time_stop();

	if (pass) {
		printf("%fs ~ passed.\t", time);
		print(node, "\n");
	}
}

void linkedlist_test_get(DS_LinkedList *node, size_t num)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	if ((node = DS_LinkedList_get(node, num)) == NULL) {
		time_stop();
		printf(" ~ failed.\n"), time_stop();
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		print(node, "\n");
	}
}

void linkedlist_test_output(DS_LinkedList *node, size_t var)
{
	double time = 0;
	printf("%s() ~ ", __func__);

	pt_out = output;
	time_start();
	if (DS_LinkedList_output(node, &var, print_n)) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("%s\n", output);
	}
}

void linkedlist_test_insert(DS_LinkedList *node, Data *data, size_t index)
{
	double time = 0;
	int i;
	printf("%s() ~ ", __func__);
	sprintf(data->str, "%s", "I used to be a number.");
	data->len = strlen(data->str);

	time_start();
	if ((node = DS_LinkedList_insert(node, index, *data)) == NULL) {
		time_stop();
		printf(" ~ insert failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		for (i = 4; node->next != NULL && i; node = node->next, i--)
			print(node, " ");
		putchar('\n');
	}
}

void linkedlist_test_remove(DS_LinkedList *node, size_t index)
{
	double time = 0;
	int i;
	printf("%s() ~ ", __func__);

	time_start();
	if ((node = DS_LinkedList_remove(node, index)) == NULL) {
		time_stop();
		printf(" ~ remove failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		for (i = 4; node->next != NULL && i; node = node->next, i--)
			print(node, " ");
		putchar('\n');
	}
}

void linkedlist_test_set(DS_LinkedList *node, size_t index, Data *data)
{
	double time = 0;
	int i;
	printf("%s()\t ~ ", __func__);
	sprintf(data->str, "%s", "I am now hypertextual.");
	data->len = strlen(data->str);

	time_start();
	if ((node = DS_LinkedList_set(node, index, *data)) == NULL) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		for (i = 4; node->next != NULL && i; node = node->next, i--)
			print(node, " ");
		putchar('\n');
	}
}

void linkedlist_test_size(DS_LinkedList *node)
{
	size_t i = 0;
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	if ((i = DS_LinkedList_size(node)) == 0) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("size = %lu\n", i);
	}
}

void linkedlist_test_clear(DS_LinkedList *node)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);

	time_start();
	if (DS_LinkedList_clear(node)) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed.\t", time);
		printf("\n");
	}
}

void DS_LinkedList_test(void)
{
	DS_LinkedList head;
	head.next = NULL;
	Data d, *data;
	data = &d;

	time_start();
	time_loop();
	time_stop();

	linkedlist_test_init(&head);
	linkedlist_test_add(&head, data, 1);
	linkedlist_test_remove(&head, 1);
	linkedlist_test_add(&head, data, 10000000);
	linkedlist_test_get(&head, 10000000);
	linkedlist_test_output(&head, 10);
	linkedlist_test_insert(&head, data, 5000000);
	linkedlist_test_set(&head, 5000000, data);
	linkedlist_test_remove(&head, 5000000);
	linkedlist_test_size(&head);
	linkedlist_test_clear(head.next);
}

