#include "../data_structures/DS_Struct.h"
#include "../data_structures/DS_LinkedList.h"
#include "../general/DS_Timer.h"
#include "../tests/DS_Test_output.h"
#include <string.h>
#include <stdint.h>

typedef struct _var {
	DS_LinkedList head;
	char *str;
	size_t num;
	size_t itt;
	size_t width;
} Var;

void linkedlist_test_init(DS_LinkedList *head)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	time_start();
	DS_LinkedList_init(head);
	time = time_stop();
	printf("%fs ~ passed.\n", time);
}

void linkedlist_test_add(DS_LinkedList *node, size_t num)
{
	Data d, *data;
	data = &d;
	size_t i;
	double time = 0;
	int pass = 1;

	printf("%s()\t ~ ", __func__);

	time_start();
	for (i = 0; i < num; i++)
	{
		sprintf(data->str, "n:%lu ", i+1);
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
		printf("%fs ~ passed. ", time);
		DS_Out_print_node(node, "\n");
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
		printf("%fs ~ passed. ", time);
		DS_Out_print_node(node, "\n");
	}
}

void linkedlist_test_output(DS_LinkedList *node, size_t var)
{
	double time = 0;
	printf("%s() ~ ", __func__);

	/* Set the string length position to the start of the output string */
	DS_Out_reset();
	time_start();
	if (DS_LinkedList_output(node, &var, DS_Out_store)) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed. ", time);
		printf("%s\n", DS_Out_get_string());
	}
}

void linkedlist_test_insert(DS_LinkedList *node, char *str, size_t index)
{
	Data d, *data;
	data = &d;
	double time = 0;
	printf("%s() ~ ", __func__);
	sprintf(data->str, "%s", str);
	data->len = strlen(data->str);

	time_start();
	if ((node = DS_LinkedList_insert(node, index, *data)) == NULL) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed. ", time);
		DS_Out_print_node(node, "\n");
	}
}

void linkedlist_test_remove(DS_LinkedList *node, size_t index)
{
	double time = 0;
	printf("%s() ~ ", __func__);

	time_start();
	if ((node = DS_LinkedList_remove(node, index)) == NULL) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed. ", time);
		DS_Out_print_node(node, "\n");
	}
}

void linkedlist_test_set(DS_LinkedList *node, size_t index, Data *data)
{
	double time = 0;
	printf("%s()\t ~ ", __func__);
	sprintf(data->str, "%s", "I am now hypertextual.");
	data->len = strlen(data->str);

	time_start();
	if ((node = DS_LinkedList_set(node, index, *data)) == NULL) {
		time_stop();
		printf(" ~ failed.\n");
	} else {
		time = time_stop();
		printf("%fs ~ passed. ", time);
		DS_Out_print_node(node, "\n");
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
		printf("%fs ~ passed. ", time);
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
		printf("%fs ~ passed. ", time);
		printf("\n");
	}
}

/* Stop buffer underflow when getting the first few nodes for the output
 * display; Required to print n nodes before the current node. */
size_t _back_n_nodes(size_t i, size_t n)
{
	return (i -= n) > (SIZE_MAX - n) ? 0 : i;
}

void _linkedlist_test_call(void* v)
{
	Var *var;
        var = (Var*)v;
	DS_LinkedList *head = &var->head;
	size_t i = var->itt;
	size_t num = var->num;
	int n = var->width;

	linkedlist_test_insert(head, var->str, i);
	linkedlist_test_get(head, i);
	linkedlist_test_output(DS_LinkedList_get(head, _back_n_nodes(i, n)), num);
	linkedlist_test_remove(head, i);
	linkedlist_test_output(head, num);
}

void _linkedlist_test_itterate(Var *var, void(*func)(void*))
{
	DS_LinkedList *head = &(var->head);
	size_t num = var->num;
	size_t i = var->itt;

	/* 4 to allow an overflow of 2 nodes from the end of the array */
	for (i = 0; i < num + 4; i++)
	{
		var->itt = i;
		printf("%lu\n", i);
		time_loop();
		linkedlist_test_init(head);
		linkedlist_test_add(head, num);
		(*func)(var);
		linkedlist_test_clear(head);
	}
}

void DS_LinkedList_test(void)
{
/* Var
	DS_LinkedList head;
	char *str;
	size_t num;
	size_t itt;
	size_t width;
*/
	Var var = {  { { { "STACK" }, 5 }, NULL },  "oOo ", 10, 0, 5 };

	_linkedlist_test_itterate(&var, _linkedlist_test_call);
}

