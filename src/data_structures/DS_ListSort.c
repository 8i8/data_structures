
/*
 * 1) divide the list (either top down or bottom up)
 * 2) sort left division
 * 3) sort right division
 * 4) merge
 *
 * Set the head of two linked lists to the head of the list to be sorted.
 *
 * Set the i_len to one for bottom up or to list length / 2 for top down. We
 * will use bottom up, assuming a linked list of an undetermined size.
 *
 * move the right list i_len places along the list, this will be the start of
 * list two.
 *
 * After checking that we have not come to the end of the list, set both the
 * left and the right list sizes.
 *
 * Merge both the lists into a new list, using a given function to swap the
 * nodes when required.
 *
 * Keep track of the tail of the new list, for the next addition from the next
 * iteration.
 *
 * Set i_len to be `2n' and reiterate.
 *
 */
#include "DS_LinkedList.h"

void _set_tail(Var *var)
{
}

DS_LinkedList **_merge(DS_LinkedList **left, DS_LinkedList **right, Var *var)
{
	DS_LinkedList **merged, **pt;
	pt = merged;

	while (*left || *right) {
		*merged = var->comp(*left, *right);
		merged = &(*merged)->next;
	}

	return pt;
}

DS_LinkedList **_advance_and_cut(DS_LinkedList *list, int n)
{
	DS_LinkedList **last;


	for ( ; n && *list != NULL; n--) {
		if (var->is_circular && *list == var->oldhead)
			return NULL;
		else if (n == 1) {
			/* Snip! */
			last = list;
			list = &(*list)->next;
			(*last)->next = NULL;
		} else
			list = &(*list)->next;
	}

	return list;
}

DS_LinkedList **_listsort(DS_LinkedList **list, Var *var, int i_len)
{
	DS_LinkedList **left, **right, **rtn;

	if ((*list)->next == NULL || *list == NULL || list == NULL)
		return NULL;
	
	// set left and right position and list length
	left = list, right = _advance_and_cut(*list, i_len);

	// listsort call for remaining list
	while (rtn = _advance_and_cut(right, i_len) && (*rtn)->next != NULL)
		_listsort(rtn, var, i_len);

	// sort whilst mergeing to new list
	(*var->tail)->next = _merge(left, right, var);

	rtn = var->tail;
	while (*rtn != NULL)
		rtn = &(*rtn)->next;
	var->tail = rtn

	// listsort call for new list
	_listsort(var->new, var, i_len * 2);
}

void *DS_ListSort(void *list, int is_circular, int is_double, int (*comp)(void*, void*))
{
	struct _var {
		DS_LinkedList **new;
		DS_LinkedList **tail;
		DS_LinkedList **oldhead;
		int is_circular;
		int is_double;
		int ((*comp)(void*, void*);
	} Var;

}
