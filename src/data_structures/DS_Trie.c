#include "DS_Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UCHAR 127 /* Length of character index for c_list */
#define STR_BUF_INIT 8

#ifndef _string_
typedef struct {
	char *str;
	char *ptr;
	size_t buf;
} String;
#endif

String *GE_string_init(String *Str)
{
	Str = malloc(sizeof(*Str));
	Str->buf = STR_BUF_INIT;
	Str->ptr = Str->str = calloc(Str->buf, 1);

	return Str;
}

/*
 * _string_len: Buffer for simple string struct.
 */
String *GE_string_len(String *Str, size_t len)
{
	if (Str->buf > len-1) {
		Str->buf <<= 1;
		Str->ptr = Str->str = realloc(Str->str, Str->buf);
		Str->ptr += len;
	}
		
	return Str;
}

/*
 * GE_string_free: Destroy string.
 */
void GE_string_free(String *Str)
{
	free(Str->str);
	free(Str);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Create and fill
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * _new_c_arr: Create a new hash table, that is an array of possible characters
 * from the ASCII char set, all set to NULL ready for the next node.
 */
static DS_Trie **_new_c_arr(DS_Trie **arr)
{
	int i;
	if ((arr = malloc(UCHAR * sizeof(DS_Trie*))) == NULL)
		return NULL;

	for (i = 0; i < UCHAR; i++)
		arr[i] = NULL;

	return arr;
}

/*
 * _new_c_node: Create a new node with the given char.
 */
static DS_Trie *_new_c_node(char c)
{
	DS_Trie *new_node;
	if((new_node = malloc(sizeof(DS_Trie))) == NULL)
		return NULL;
	new_node->c = c;
	new_node->next = NULL;
	new_node->word_end = 0;

	return new_node;
}

/*
 * _add_word: Add a new word to the trie, a recursive function that adds the
 * string char by char, skipping over existing sub words and adding either
 * entire new words else new endings.
 */
static DS_Trie *_add_word(DS_Trie *c_node, char *str)
{
	DS_Trie *ptr;
	ptr = c_node;

	while (*++str) { 
		/* Next node list */
		if (c_node->next == NULL)
			if ((c_node->next = _new_c_arr(c_node->next)) == NULL)
				return NULL;
		/* Next node */
		if (c_node->next[(unsigned)*str] == NULL)
			if ((c_node->next[(unsigned)*str] = _new_c_node(*str)) == NULL)
				return NULL;

		c_node = c_node->next[(unsigned)*str];
	}

	c_node->word_end = 1;

	return ptr;
}

/*
 * DS_Trie_add_word: Creates a new node for the first character of the string
 * and then calls the recursive function that adds the given string to the trie.
 */
DS_Trie **DS_Trie_add_word(DS_Trie **trie, char *str)
{
	if (trie[(unsigned)*str] == NULL)
		if ((trie[(unsigned)*str] = _new_c_node(*str)) == NULL)
			return NULL;

	if ((_add_word(trie[(unsigned)*str], str)) == NULL)
		return NULL;

	return trie;
}

/*
 * DS_Trie_add_n_char: Creates a new node for the first character of the string
 * and then calls the recursive function that adds the given length of the
 * given string to the trie.
 */
DS_Trie **DS_Trie_add_n_char(DS_Trie **trie, int len, char *string)
{
	char str[len+1];
	snprintf(str, len+1, "%s", string);

	if (trie[(unsigned)*str] == NULL)
		if ((trie[(unsigned)*str] = _new_c_node(*str)) == NULL)
			return NULL;

	if ((_add_word(trie[(unsigned)*str], str)) == NULL)
		return NULL;

	return trie;
}

/*
 * DS_Trie_init: Instantiate a new trie.
 */
DS_Trie **DS_Trie_init(DS_Trie **trie)
{
	return _new_c_arr(trie);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Output
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * _func_print: Printout the content of the tree from char root to current
 * node.
 */
void _func_example(void *input, void *var)
{
	int *n = var;
	String *Str = input;
	*(Str->ptr+1) = '\0';
#ifndef __unix__
	printf("%s %d\n", Str->str);
#endif
#ifdef __unix__
	write(1, Str->str, *n);
	write(1, "\n", 1);
#endif
}

/*
 * _output_word: Recursive function that will perform it's given task on
 * arriving at each word ending.
 */
// TODO the string also needs to be made into a flexible buffer.
static void _output_word(
				DS_Trie *word,
				String *Str,
				void (*func)(void*, void*),
				int count)
{
	int i;
	*Str->ptr++ = word->c;
	Str = GE_string_len(Str, count);

	if (word->next != NULL)
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL) {
				_output_word(
						word->next[i],
						Str,
						func,
						++count);
				count--;
			}

	if (word->word_end)
		(*func)((void*)Str, &count);
}

/*
 * _output_list: Iterates over every node in the array, performing the
 * recursive function on each element.
 */
static void _output_list(
				DS_Trie **list,
				String *Str,
				void (*func)(void*, void*))
{
	int i, count;
	count = 1;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_output_word(list[i], Str, func, count);
}

/* 
 * DS_Trie_output: Iterate over all word_ endings in the trie perform the
 * given function on arriving at a words end marker.
 */
void DS_Trie_output(DS_Trie **list, void (*func)(void*, void*))
{
	String *Str = NULL;
	Str = GE_string_init(Str);

	_output_list(list, Str, func);

	GE_string_free(Str);
}

static void _trie_step_compaire(
				DS_Trie **list,
				String *Str,
				void (*func)(void*, void*))
{
	int i, count;
	count = 1;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_output_word(list[i], Str, func, count);
}

/*
 * DS_Trie_step_compare: Compare a string with trie char by char, return 0 if
 * the string is found and the number of char that are identical if not found.
 */
void DS_Trie_step_compaire(
				DS_Trie **list,
				void (*func)(void*, void*))
{
	String *Str = NULL;
	Str = GE_string_init(Str);

	_trie_step_compaire(list, Str, func);

	GE_string_free(Str);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Disposal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * _trie_free_word: Recursive function to free all the nodes in the trie.
 */
static void _trie_free_word(DS_Trie *word)
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

/*
 * DS_Trie_free: Iterate over and free used slots in the char list.
 */
void DS_Trie_free(DS_Trie **list)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			_trie_free_word(list[i]);
	free(list);
}

