#include "../tests/DS_Struct.h"
#include "../data_structures/DS_DLinkedList.h"
#include "../general/DS_Timer.h"
#include "../general/DS_Output.h"
#include "../general/DS_Error.h"
#include "../general/DS_Message.h"
#include <string.h>
#include <stdint.h>

typedef struct _var {
	DS_DLinkedList head;
	char *str;
	size_t num;
	size_t itt;
	size_t width;
} Var;

void _dlinkedlist_stack_or_heap(DS_DLinkedList *node, char *type)
{
	double time = 0;
	int pass = 1;
	DS_DLinkedList *rtn = NULL;

	time_start();
	if ((rtn = DS_DLinkedList_init(node)) == NULL)
		pass--, DS_Error_set("%s: %s", __func__, DS_Error_get());

	time = time_stop();

	if (strcmp(rtn->data.str, type))
		pass--, DS_Error_set("%s: list head type mismatched.", __func__);

	DS_Message_append((pass) ? "%fs passed." : "%fs failed.", time);
}

void dlinkedlist_test_init(DS_DLinkedList *head, int msg, int err)
{
	DS_DLinkedList *node;
	node = head;

	DS_Message_set("%s()\t", __func__);

	if (head == NULL)
		_dlinkedlist_stack_or_heap(node, "HEAP");
	else
		_dlinkedlist_stack_or_heap(node, "STACK");

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_add(DS_DLinkedList *node, size_t num, int msg, int err)
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
		data->num = i+1;
		if((node = DS_DLinkedList_add(node, *data)) == NULL) {
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

void dlinkedlist_test_get(DS_DLinkedList *node, size_t num, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if ((node = DS_DLinkedList_get(node, num)) == NULL) {
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
void dlinkedlist_test_output(DS_DLinkedList *node, size_t var, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	DS_Out_reset();
	time_start();
	if (DS_DLinkedList_do(node, &var, DS_Out_store)) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", DS_Out_msg());
	}

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_insert(DS_DLinkedList *node, char *str, size_t num, int msg, int err)
{
	Data d, *data;
	data = &d;
	double time = 0;

	DS_Message_set("%s()\t", __func__);
	sprintf(data->str, "%s", str);
	data->num = strlen(data->str);

	time_start();
	if ((node = DS_DLinkedList_insert(node, num, *data)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.", time);
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", node->data.str, "\n");
	}

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_remove(DS_DLinkedList *node, size_t num, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if ((node = DS_DLinkedList_remove(node, num)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("%s", node->data.str, "\n");
	}

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_fwd(DS_DLinkedList *list, size_t pos, size_t num, int msg, int err)
{
	DS_DLinkedList *rtn;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	if ((rtn = DS_DLinkedList_get(list, pos)) == NULL) {
		DS_Message_append("%fs 'get' failed.");
		return;
	}

	time_start();
	if ((rtn = DS_DLinkedList_fwd(rtn, num)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.", time);
	} else {
		time = time_stop();
		if (pos == rtn->data.num - num)
			DS_Message_append("%fs passed.", time);
		else {
			DS_Message_append("%fs failed.", time);
			DS_Error_set("%s: Position error start = %lu, new = %lu.",
					__func__, pos, rtn->data.num);
		}
	}

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_rwd(DS_DLinkedList *list, size_t pos, size_t num, int msg, int err)
{
	DS_DLinkedList *rtn;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	if ((rtn = DS_DLinkedList_get(list, pos)) == NULL) {
		DS_Message_append("%fs 'get' failed.");
		return;
	}

	time_start();
	if ((rtn = DS_DLinkedList_rwd(rtn, num)) == NULL) {
		time = time_stop();
		DS_Message_append("%fs failed.", time);
	} else {
		time = time_stop();
		if (pos == rtn->data.num + num)
			DS_Message_append("%fs passed.", time);
		else {
			DS_Message_append("%fs failed.", time);
			DS_Error_set("%s: Position error start = %lu, new = %lu.",
					__func__, pos, rtn->data.num);
		}
	}

	_ds_check_messages(msg, err);
}


void dlinkedlist_test_set(DS_DLinkedList *head, size_t num, Data *data, int msg, int err)
{
	DS_DLinkedList *node, *rtn_value;
	node = head;
	double time = 0;
	DS_Message_set("%s()\t", __func__);
	sprintf(data->str, "%s", "I am now hypertextual.");
	data->num = strlen(data->str);

	time_start();
	if ((rtn_value = DS_DLinkedList_set(node, num, *data)) == NULL) {
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

void dlinkedlist_test_size(DS_DLinkedList *node, int msg, int err)
{
	size_t i = 0;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if ((i = DS_DLinkedList_size(node)) == 0) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed.", time);
		DS_Message_append("size = %lu\n", i);
	}

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_clear(DS_DLinkedList *node, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	if (DS_DLinkedList_clear(node)) {
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
size_t _back_n_nodes2(size_t i, size_t n)
{
	return (i -= n) > (SIZE_MAX - n) ? 0 : i;
}

void _dlinkedlist_test_call(void* v)
{
	Var *var;
	var = (Var*)v;
	DS_DLinkedList *head = &var->head;
	size_t i = var->itt;
	size_t num = var->num;
	int msg, err, n = var->width;
	msg = 0;
	err = 1;

	printf("%lu\n", i);
	dlinkedlist_test_get(head, i, msg, err);
	dlinkedlist_test_fwd(head, i, 3, msg, err);
	dlinkedlist_test_rwd(head, i, 3, msg, err);
	dlinkedlist_test_insert(head, var->str, i, msg, err);
	dlinkedlist_test_get(head, i, msg, err);
	dlinkedlist_test_output(DS_DLinkedList_get(head, _back_n_nodes2(i, n)), num, msg, err);
	dlinkedlist_test_remove(head, i, msg, err);
	dlinkedlist_test_output(head, num, msg, err);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _dlinkedlist_stages(Var *var, void(*func)(void*))
{
	DS_DLinkedList *head = &(var->head);
	size_t num = var->num;

	time_loop();
	dlinkedlist_test_init(head, 0, 1);
	dlinkedlist_test_add(head, num, 0 , 1);
	(*func)(var);
	dlinkedlist_test_clear(head, 0, 1);
}

void _dlinkedlist_test_itterate(Var *var, void(*func)(void*))
{
	size_t num = var->num;
	size_t i;

	/* i is 0 */
	var->itt = 0;
	_dlinkedlist_stages(var, func);

	/* I is between 1 and the end of the list */
	for (i = 1; i <= num; i++)
		_dlinkedlist_stages(var, func), var->itt = i;

	/* Should fail */
	for (i = num + 1; i <= num + 2; i++)
		_dlinkedlist_stages(var, func), var->itt = i;

}

void DS_DLinkedList_test(void)
{
/* Var
	DS_DLinkedList head;
	char *str;
	size_t num;
	size_t itt;
	size_t width;
*/
	Var var = {  { { { "INIT" }, 4 }, NULL, NULL },  "oOo ", 10, 0, 5 };

	_dlinkedlist_test_itterate(&var, _dlinkedlist_test_call);
}

