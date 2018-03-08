#include "DS_Trie.h"
#include <stdio.h>
#include <stdlib.h>

#define UCHAR 127 /* Length of character index for c_list */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Create and fill
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

DS_Trie *_new_c_node(char c)
{
	if((DS_Trie *new_node = malloc(sizeof(DS_Trie))) == NULL)
		return NULL;
	new_node->c = c;
	new_node->next = NULL;
	new_node->word_end = 0;

	return new_node;
}

DS_Trie **_new_c_list(DS_Trie **list)
{
	int i;
	if ((list = malloc(UCHAR * sizeof(DS_Trie*))) == NULL)
		return NULL;

	for (i = 0; i < UCHAR; i++)
		list[i] = NULL;

	return list;
}

DS_Trie *_add_word(DS_Trie *word, char *str)
{
	DS_Trie *ptr, *c_node = word;
	ptr = c_node;

	while (*++str) {

		/* Next node list */
		if (c_node->next == NULL)
			if ((c_node->next = _new_c_list(c_node->next)) == NULL)
				return NULL;
		/* Next node */
		if (c_node->next[(int)*str] == NULL)
			if ((c_node->next[(int)*str] = _new_c_node(*str)) == NULL)
				return NULL;

		c_node = c_node->next[(int)*str];
	}

	c_node->word_end = 1;

	return ptr;
}

DS_Trie **tDS_Trie_add_word(DS_Trie **list, char *string)
{
	char* str = (char*)string;

	if (list[(int)*str] == NULL)
		if ((list[(int)*str] = _new_c_node(*str)) == NULL)
			return NULL;

	if ((_add_word(list[(int)*str], str)) == NULL)
		return NULL;

	return list;
}

DS_Trie **tDS_Trie_add_n_char(DS_Trie **list, int len, char *string)
{
	char str[len+1];
	snprintf(str, len+1, string);

	if (list[(int)*str] == NULL)
		if ((list[(int)*str] = _new_c_node(*str)) == NULL)
			return NULL;

	if ((_add_word(list[(int)*str], str)) == NULL)
		return NULL;

	return list;
}

DS_Trie **tDS_Trie_init(DS_Trie **list)
{
	return _new_c_list(list);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Output
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _output_word(DS_Trie *word, char *out, char *pt_out, void (*func)(void*, void*, int), void *var)
{
	int i;
	static int count;
	pt_out += sprintf(pt_out, "%c", word->c);

	if (word->next != NULL)
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				_output_word(word->next[i], out, pt_out, func, var);

	if (word->word_end)
		(*func)((void*)out, var, ++count);
}

void _output_list(DS_Trie **list, char *out, char *pt_out, void (*func)(void*, void*, int), void *var)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_output_word(list[i], out, pt_out, func, var);
}

/* Output trie via given function */
void tDS_Trie_output(DS_Trie **list, void (*func)(void*, void*, int), void *var)
{
	char *pt, out[UCHAR] = {'\0'};
	pt = out;

	_output_list(list, pt, pt, func, var);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Disposal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void _trie_free_word(DS_Trie *word)
{
	int i;

	if (word->next != NULL) {
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				_trie_free_word(word->next[i]);
		free(word->next);
	}
	free(word);
}

void tDS_Trie_free(DS_Trie **list)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_trie_free_word(list[i]);
	free(list);
}

