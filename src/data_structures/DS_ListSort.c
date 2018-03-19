/*
 */
#include "../data_structures/DS_ListSort.h"

DS_LinkedList *_advance_and_cut(DS_LinkedList **list, size_t len)
{
	DS_LinkedList *fin;

	for (; len && *list; len--)
		list = &(*list)->next;

	if (*list) {
		fin = *list;
		list = &(*list)->next;
		fin->next = NULL;
	}

	return *list;
}

/*
 * Trial code to see if there is a difference using null terminated lists
 * rather than counting the merge length.
 */
DS_LinkedList **_listsort_cut(DS_LinkedList **list, size_t m_len, int(*comp)(void*, void*))
{
	size_t count;
	DS_LinkedList *left, *l_pt, *right, *r_pt, *new, *tail, *end;

	/* Set the merge count to 0, this value will effect the recursion of
	 * this function */
	count = 0;

	/* Set the left list to the head of the current list and then the
	 * current list to NULL, the merged list will have a different head */
	left = *list;
	new = tail = *list = NULL;
	
	while (left)
	{
		count++;
		right = r_pt = l_pt = left;

		right = _advance_and_cut(&l_pt, m_len);
		end = _advance_and_cut(&r_pt, m_len);

		/* Whilst there remains any length of either the right or the
		 * left lists, compare the two else merge the remainder */
		while (left || right)
		{
			/* Two list to compare */
			if (left && right)
				if ((comp(left, right)) > 0)
					new = right, right = right->next;
				else
					new = left, left = left->next;

			/* Merge the remaining node */
			else if (left)
				new = left, left = left->next;

			else if (right)
				new = right, right = right->next;

			/* If there is not yet a merged list, make one; Else
			 * add the new node to the new lists tail */
			if (tail)
				tail->next = new;
			else
				*list = new;

			tail = new;
		}

		/* Merge done, move the left list to the start of the remaining
		 * original list */
		left = end;
	}

	/* Clip the end of the list to stop an infinite loop, if the last node
	 * came from the middle of the list, it will have an address in next */
	tail->next = NULL;

	/* If more than one merge has been made, continue. If only one merge or
	 * fewer have been counted, then the sort is finished */
	if (count > 1)
		list = _listsort_cut(list, m_len * 2, comp);

	return list;
}

/*
 * DS_ListSort: Merge sort for linked lists.
 */
DS_LinkedList **_listsort(DS_LinkedList **list, size_t m_len, int(*comp)(void*, void*))
{
	size_t i, count, l_len, r_len;
	DS_LinkedList *left, *right, *new, *tail;

	/* Set the merge count to 0, this value will effect the recursion of
	 * this function */
	count = 0;

	/* Set the left list to the head of the current list and then the
	 * current list to NULL, the merged list will have a different head */
	left = *list;
	new = tail = *list = NULL;
	
	while (left)
	{
		count++;
		right = left;

		/* Advance the right list head and count the number of nodes
		 * for the length of the left. */
		l_len = 0;
		for (i = 0; i < m_len; i++) {
			l_len++;
			right = right->next;
			if (!right)
				break;
		}

		r_len = m_len;

		/* Whilst there remains any length of either the right or the
		 * left lists, compare the two else merge the remainder */
		while (l_len > 0 || (r_len > 0 && right))
		{
			/* Two list to compare */
			if (l_len && r_len)
				if ((comp(left, right)) > 0)
					new = right, right = right->next, r_len--;
				else
					new = left, left = left->next, l_len--;

			/* Merge the remaining node */
			else if (!r_len)
				new = left, left = left->next, l_len--;

			else if (!l_len)
				new = right, right = right->next, r_len--;

			/* If there is not yet a merged list, make one; Else
			 * add the new node to the new lists tail */
			if (tail)
				tail->next = new;
			else
				*list = new;

			tail = new;
		}

		/* Merge done, move the left list forwards to the end of the
		 * right list, ready for the next sort, or the end */
		left = right;
	}

	/* Clip the end of the list to stop an infinite loop, if the last node
	 * came from the middle of the list, it will have an address in next */
	tail->next = NULL;

	/* If more than one merge has been made, continue. If only one merge or
	 * fewer have been counted, then the sort is finished */
	if (count > 1)
		list = _listsort(list, m_len * 2, comp);

	return list;
}

DS_LinkedList **DS_ListSort(DS_LinkedList **list, int(*comp)(void*, void*))
{
	/* Doh! Nothing to see here, please move along. */
	if (list == NULL || *list == NULL || (*list)->next == NULL)
		return NULL;

	/* Set the ball rolling with a merge length of one node */
	return _listsort(list, 1, comp);
}

