#include "../tests/DS_Struct.h"
#include "../data_structures/DS_DLinkedList.h"
#include "../general/DS_Timer.h"
#include "../general/DS_Test_output.h"
#include "../general/ds_msg.h"
#include "../general/DS_Error.h"
#include "../general/DS_Message.h"
#include <string.h>
#include <stdint.h>

typedef struct _var {
	DS_DLinkedList *head;
	char *str;
	size_t num;
	size_t itt;
	size_t width;
} Var;

void dlinkedlist_test_add(DS_DLinkedList **list, size_t num, int msg, int err)
{
	DS_DLinkedList **rtn = NULL;
	Data d, *data;
	data = &d;
	size_t i;
	double time = 0;

	DS_Message_set("%s()\t", __func__);

	time_start();
	for (i = 0; i < num; i++)
	{
		sprintf(data->str, "n:%lu ", i+1), data->num = i+1;
		if((rtn = DS_DLinkedList_add(list, *data)) == NULL)
			break;
	}
	time = time_stop();

	if (*rtn)
		DS_Message_append("%fs passed. %s", time, (*rtn)->data.str);
	else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_get(DS_DLinkedList **list, size_t num, int msg, int err)
{
	DS_DLinkedList **rtn = NULL;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	rtn = DS_DLinkedList_get(list, num);
	time = time_stop();

	if (rtn)
		DS_Message_append("%fs passed. %s", time, (*rtn)->data.str);
	else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

/* TODO add this messaging to the DS_Message code */
void dlinkedlist_test_output(DS_DLinkedList **list, size_t num, int msg, int err)
{
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	DS_Out_reset();
	time_start();
	if (DS_DLinkedList_do(list, &num, DS_Out_store)) {
		time = time_stop();
		DS_Message_append("%fs failed.");
	} else {
		time = time_stop();
		DS_Message_append("%fs passed. %s", time, DS_Out_msg());
	}

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_insert(DS_DLinkedList **list, char *str, size_t num, int msg, int err)
{
	DS_DLinkedList **rtn = NULL;
	Data d, *data;
	data = &d;
	double time = 0;

	DS_Message_set("%s()\t", __func__);
	sprintf(data->str, "%s", str);
	data->num = num;

	time_start();
	rtn = DS_DLinkedList_insert(list, *data);
	time = time_stop();

	if (rtn)
		DS_Message_append("%fs passed. %s", time, (*rtn)->data.str);
	else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_remove(DS_DLinkedList **list, size_t num, int msg, int err)
{
	DS_DLinkedList **rtn = NULL;
	double time = 0;

	DS_Message_set("%s()\t", __func__);

	time_start();
	rtn = DS_DLinkedList_remove(list, num);
	time = time_stop();

	if (rtn)
		DS_Message_append("%fs passed. %s", time, (*rtn)->data.str);
	else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_fwd(DS_DLinkedList **list, size_t pos, size_t num, int msg, int err)
{
	DS_DLinkedList **rtn;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	if ((rtn = DS_DLinkedList_get(list, pos)) == NULL) {
		DS_Message_append("%fs 'get' failed.");
		return;
	}

	time_start();
	rtn = DS_DLinkedList_fwd(rtn, num);
	time = time_stop();

	if (rtn) {
		if (pos == (*rtn)->data.num - num)
			DS_Message_append("%fs passed. %s", time, (*rtn)->data.str);
		else {
			DS_Message_append("%fs failed.", time);
			DS_Error_set("%s: Position error start = %lu, new = %lu.",
					__func__, pos, (*rtn)->data.num);
		}
	} else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_rwd(DS_DLinkedList **list, size_t pos, size_t num, int msg, int err)
{
	DS_DLinkedList **rtn;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	if ((rtn = DS_DLinkedList_get(list, pos)) == NULL) {
		DS_Message_append("%fs 'get' failed.");
		return;
	}

	time_start();
	rtn = DS_DLinkedList_rwd(rtn, num);
	time = time_stop();

	if (rtn)
		if (pos == (*rtn)->data.num + num)
			DS_Message_append("%fs passed. %s", time, (*rtn)->data.str);
		else {
			DS_Message_append("%fs failed.", time);
			DS_Error_set("%s: Position error start = %lu, new = %lu.",
					__func__, pos, (*rtn)->data.num);
		}
	else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_set(DS_DLinkedList **list, size_t num, Data *data, int msg, int err)
{
	DS_DLinkedList **rtn;
	double time = 0;
	DS_Message_set("%s()\t", __func__);
	sprintf(data->str, "%s", "oOo");
	data->num = strlen(data->str);

	time_start();
	rtn = DS_DLinkedList_set(list, num, *data);
	time = time_stop();

	if (rtn) {
		if (rtn == list) {
			DS_Message_append("%fs passed.", time);
			DS_Message_append("%s", (*rtn)->data.str, "\n");
		} else
			DS_Message_append("%fs failed.", time);
	} else
		DS_Message_append("%fs failed.", time);

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_size(DS_DLinkedList **list, int msg, int err)
{
	size_t len = 0;
	double time = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	len = DS_DLinkedList_size(list);
	time = time_stop();

	if (len)
		DS_Message_append("%fs passed. size = %lu\n", time, len);
	else
		DS_Message_append("%fs failed.");

	_ds_check_messages(msg, err);
}

void dlinkedlist_test_clear(DS_DLinkedList **list, int msg, int err)
{
	double time = 0;
	int rtn = 0;
	DS_Message_set("%s()\t", __func__);

	time_start();
	rtn = DS_DLinkedList_clear(list);
	time = time_stop();

	if (rtn)
		DS_Message_append("%fs failed.");
	else
		DS_Message_append("%fs passed.", time);

	_ds_check_messages(msg, err);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Stop buffer underflow when getting the first few nodes for the output
 * display; Required to print n nodes before the current node. */
size_t _back_n_nodes2(size_t i, size_t n)
{
	return (i -= n) > (SIZE_MAX - n) ? 1 : i;
}

void _dlinkedlist_test_call(void* v)
{
	Var *var;
	var = (Var*)v;
	DS_DLinkedList **head;
	head = &(var->head);
	size_t i = var->itt;
	size_t num = var->num;
	int msg, err, n = var->width;
	msg = 1, err = 1;

	printf("%lu\n", i);
	dlinkedlist_test_get(head, i, msg, err);
	dlinkedlist_test_fwd(head, i, 3, msg, err);
	dlinkedlist_test_rwd(head, i, 3, msg, err);
	dlinkedlist_test_insert(head, var->str, i, msg, err);
	dlinkedlist_test_get(head, i, msg, err);
	dlinkedlist_test_output(DS_DLinkedList_get(
				head, _back_n_nodes2(i, n)), num, msg, err);
	dlinkedlist_test_remove(head, i, msg, err);
	dlinkedlist_test_output(head, num, msg, err);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _dlinkedlist_stages(Var *var, void(*func)(void*))
{
	DS_DLinkedList **head = &(var->head);
	size_t num = var->num;

	time_loop();
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
		var->itt = i, _dlinkedlist_stages(var, func);

	/* Should fail */
	for (i = num + 1; i <= num + 2; i++)
		var->itt = i, _dlinkedlist_stages(var, func);

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
	//Var var = {  { { { "INIT" }, 4 }, NULL, NULL },  "oOo ", 10, 0, 5 };
	Var var = { NULL, "oOo ", 10, 0, 5 };

	_dlinkedlist_test_itterate(&var, _dlinkedlist_test_call);
}

