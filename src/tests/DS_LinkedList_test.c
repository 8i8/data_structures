#include "../data_structures/DS_Struct.h"
#include "../data_structures/DS_LinkedList.h"
#include "../general/DS_Timer.h"
#include "../general/DS_Output.h"
#include "../general/DS_Error.h"
#include "../general/DS_Message.h"
#include <string.h>
#include <stdint.h>

typedef struct _var {
	DS_LinkedList head;
	char *str;
	size_t num;
	size_t itt;
	size_t width;
} Var;

void _linkedlist_stack_or_heap(DS_LinkedList *node, char *type)
{
	double time = 0;
	int pass = 1;
	DS_LinkedList *rtn = NULL;

	time_start();
	if ((rtn = DS_LinkedList_init(node)) == NULL)
		pass--, DS_Error_set("%s: %s", __func__, DS_Error_get());

	time = time_stop();

	if (strcmp(rtn->data.str, type))
		pass--, DS_Error_set("%s: list head type mismatched.", __func__);

	DS_Message_append((pass) ? "%fs passed." : "%fs failed.", time);
}

void linkedlist_test_init(DS_LinkedList *head, int msg, int err)
{
	DS_LinkedList *node;
	node = head;

	DS_Message_set("%s()\t", __func__);

	if (head == NULL)
		_linkedlist_stack_or_heap(node, "HEAP");
	else
		_linkedlist_stack_or_heap(node, "STACK");

	_ds_check_messages(msg, err);
}

void linkedlist_test_add(DS_LinkedList *node, size_t num, int msg, int err)
{
	Data d, *data;
	data = &d;
	size_t i;
	double time = 0;
	int pass = 1;

	DS_Message_set("%s()\t", __func__);

	time_start();
	for (i = 0; i < num; i++)
	{
		sprintf(data->str, "n:%lu ", i+1);
		data->len = strlen(data->str);
		if((node = DS_LinkedList_add(node, *data)) == NULL) {
			DS_Message_append("%fs failed.", time);
			pass = 0;
			break;
		}
	}
	time = time_stop();

	if (pass) {
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", node->data.str, "\n");
	}

	_ds_check_messages(msg, err);
}

void linkedlist_test_get(DS_LinkedList *node, size_t num, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if ((node = DS_LinkedList_get(node, num)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.", time);
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", node->data.str);
	}

	_ds_check_messages(msg, err);
}

/* TODO add this messaging to the DS_Message code */
void linkedlist_test_output(DS_LinkedList *node, size_t var, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	DS_Out_reset();
	time_start();
	if (DS_LinkedList_do(node, &var, DS_Out_store)) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", DS_Out_msg());
	}

	_ds_check_messages(msg, err);
}

void linkedlist_test_insert(DS_LinkedList *node, char *str, size_t num, int msg, int err)
{
	Data d, *data;
	data = &d;
	double time = 0;

	DS_Message_set("%s()\t", __func__);
	sprintf(data->str, "%s", str);
	data->len = strlen(data->str);

	time_start();
	if ((node = DS_LinkedList_insert(node, num, *data)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.", time);
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", node->data.str, "\n");
	}

	_ds_check_messages(msg, err);
}

void linkedlist_test_remove(DS_LinkedList *node, size_t num, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if ((node = DS_LinkedList_remove(node, num)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", node->data.str, "\n");
	}

	_ds_check_messages(msg, err);
}

void linkedlist_test_set(DS_LinkedList *head, size_t num, Data *data, int msg, int err)
{
	DS_LinkedList *node, *rtn_value;
	node = head;
	double time = 0;
	DS_Message_set("%s()\t", __func__);
	sprintf(data->str, "%s", "I am now hypertextual.");
	data->len = strlen(data->str);

	time_start();
	if ((rtn_value = DS_LinkedList_set(node, num, *data)) == NULL) {
		time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		if (rtn_value != node) {
			DS_Message_append("%fs failed.");
		} else {
			DS_Message_append("%fs passed.", time);
			DS_Message_append("%s", node->data.str, "\n");
		}
	}

	_ds_check_messages(msg, err);
}

void linkedlist_test_size(DS_LinkedList *node, int msg, int err)
{
	size_t i = 0;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if ((i = DS_LinkedList_size(node)) == 0) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("size = %lu\n", i);
	}

	_ds_check_messages(msg, err);
}

void linkedlist_test_clear(DS_LinkedList *node, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if (DS_LinkedList_clear(node)) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
	}

	_ds_check_messages(msg, err);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

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
	int msg, err, n = var->width;
	msg = 0;
	err = 1;

	printf("%lu\n", i);
	linkedlist_test_get(head, i, msg, err);
	linkedlist_test_insert(head, var->str, i, msg, err);
	linkedlist_test_get(head, i, msg, err);
	linkedlist_test_output(DS_LinkedList_get(head, _back_n_nodes(i, n)), num, msg, err);
	linkedlist_test_remove(head, i, msg, err);
	linkedlist_test_output(head, num, msg, err);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _linked_list_stages(Var *var, void(*func)(void*))
{
	DS_LinkedList *head = &(var->head);
	size_t num = var->num;

	time_loop();
	linkedlist_test_init(head, 0, 1);
	linkedlist_test_add(head, num, 0 , 1);
	(*func)(var);
	linkedlist_test_clear(head, 0, 1);
}

void _linkedlist_test_itterate(Var *var, void(*func)(void*))
{
	size_t num = var->num;
	size_t i;

	/* i is 0, Should fail */
	var->itt = 0;
	_linked_list_stages(var, func);

	/* I is between 1 and the end of the list; Should pass */
	for (i = 1; i <= num; i++){
		var->itt = i;
		_linked_list_stages(var, func);
		//if (DS_Out_print_node(DS_LinkedList_get(&var->head, i), "\n"))
		//	DS_Error_print(), putchar('\n');
	}

	/* Should fail */
	for (i = num + 1; i <= num + 2; i++) {
		var->itt = i;
		_linked_list_stages(var, func);
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
	Var var = {  { { { "INIT" }, 4 }, NULL },  "oOo ", 10, 0, 5 };

	_linkedlist_test_itterate(&var, _linkedlist_test_call);
}
