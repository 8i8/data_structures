#include "DS_trie.h"
#include "GE_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UCHAR 127 /* Length of character index for c_list */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Create and fill
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * new_c_arr: Create a new hash table, that is an array of possible characters
 * from the ASCII char set, all set to NULL ready for the next node.
 */
static DS_trie **new_c_arr(DS_trie **arr)
{
	int i;
	if ((arr = malloc(UCHAR * sizeof(DS_trie*))) == NULL)
		return NULL;

	for (i = 0; i < UCHAR; i++)
		arr[i] = NULL;

	return arr;
}

/*
 * new_c_node: Create a new node with the given char.
 */
static DS_trie *new_c_node(char c)
{
	DS_trie *new_node;
	if((new_node = malloc(sizeof(DS_trie))) == NULL)
		return NULL;
	new_node->c = c;
	new_node->next = NULL;
	new_node->end = 0;

	return new_node;
}

/*
 * add_word: Add a new word to the trie, a recursive function that adds the
 * string char by char, skipping over existing sub words and adding either
 * entire new words else new endings.
 */
static DS_trie *add_word(DS_trie *c_node, char *str)
{
	DS_trie *ptr;
	ptr = c_node;

	while (*++str) { 
		/* Next node list */
		if (c_node->next == NULL)
			if ((c_node->next = new_c_arr(c_node->next)) == NULL)
				return NULL;
		/* Next node */
		if (c_node->next[(unsigned)*str] == NULL)
			if ((c_node->next[(unsigned)*str] = new_c_node(*str)) == NULL)
				return NULL;

		c_node = c_node->next[(unsigned)*str];
	}

	c_node->end = 1;

	return ptr;
}

/*
 * DS_trie_add_word: Creates a new node for the first character of the string
 * and then calls the recursive function that adds the given string to the trie.
 */
DS_trie **DS_trie_add_word(DS_trie **trie, char *str)
{
	if (trie[(unsigned)*str] == NULL)
		if ((trie[(unsigned)*str] = new_c_node(*str)) == NULL)
			return NULL;

	if ((add_word(trie[(unsigned)*str], str)) == NULL)
		return NULL;

	return trie;
}

/*
 * DS_trie_add_n_char: Creates a new node for the first character of the string
 * and then calls the recursive function that adds the given length of the
 * given string to the trie.
 */
DS_trie **DS_trie_add_n_char(DS_trie **trie, int len, char *string)
{
	char str[len+1];
	snprintf(str, len+1, "%s", string);

	if (trie[(unsigned)*str] == NULL)
		if ((trie[(unsigned)*str] = new_c_node(*str)) == NULL)
			return NULL;

	if ((add_word(trie[(unsigned)*str], str)) == NULL)
		return NULL;

	return trie;
}

/*
 * DS_trie_init: Instantiate a new trie.
 */
DS_trie **DS_trie_init(DS_trie **trie)
{
	return new_c_arr(trie);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Output
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * func_print_trie: Printout the content of the tree from char root to current
 * node.
 */
int func_print_trie(void *input, void *var)
{
	int *n = var;
	String *Str = input;
#ifdef __unix__
	write(1, Str->str, *n);
	write(1, "\n", 1);
#else
	printf("%s\n", Str->str);
#endif
	return 0;
}

/*
 * output_word: Recursive function that will perform it's given task on
 * arriving at each word ending.
 */
static void output_word(
				DS_trie *trie,
				String *Str,
				int (*func)(void*, void*),
				int count)
{
	int i;
	Str = GE_string_len(Str, count);
	*Str->ptr++ = trie->c;

	if (trie->end)
		*Str->ptr = '\0', (*func)((void*)Str, &count);

	if (trie->next != NULL)
		for (i = 0; i < UCHAR; i++)
			if (trie->next[i] != NULL) {
				output_word(
						trie->next[i],
						Str,
						func,
						++count);
				count--;
				Str->ptr--;
			}
}

/*
 * output_list: Iterates over every node in the array, performing the
 * recursive function on each element.
 */
static void output_list(
				DS_trie **trie,
				String *Str,
				int (*func)(void*, void*))
{
	int i, count = 0;

	for (i = 0; i < UCHAR; i++)
		if (trie[i] != NULL) {
			*Str->ptr = trie[i]->c;
			output_word(trie[i], Str, func, ++count);
			count--;
			Str->ptr = Str->str;
		}
}

/* 
 * DS_trie_print_list: Output content of trie to the terminal.
 */
DS_trie **DS_trie_print_list(DS_trie **trie, int (*func)(void*, void*))
{
	String *Str = NULL;
	Str = GE_string_init(Str);

	output_list(trie, Str, func);

	GE_string_free(Str);

	return trie;
}

/*
 * check_token: If the given token is found in the trie set the given state
 * with the given flag. Return 0 if the token is not found.
 */
static int check_token(
				DS_trie *trie,
				String *Str)
{
	if (trie->end)
		return 1;

	if (trie->next && trie->next[(unsigned int)*Str->ptr])
		return check_token(trie->next[(unsigned int)*Str->ptr++], Str);
	else
		return 0;
}

/*
 * DS_trie_is_token: Iterate over the given string to assertain whether or not
 * it is present in the trie.
 */
int DS_trie_is_token(DS_trie **trie, char *token)
{
	String *Str = NULL;
	int res = 0;
	Str = GE_string_init(Str);
	GE_string_set(Str, token);

	/* Is the first character in the tries hash? */
	if (trie[(unsigned int)*Str->ptr])
		res = check_token(trie[(unsigned int)*Str->ptr++], Str);

	GE_string_free(Str);

	return res;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Disposal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * trie_free_word: Recursive function to free all the nodes in the trie.
 */
static void trie_free_word(DS_trie *word)
{
	int i;

	if (word->next != NULL) {
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				trie_free_word(word->next[i]);
		free(word->next);
	}
	free(word);
}

/*
 * DS_trie_free: Iterate over and free used slots in the char list.
 */
void DS_trie_free(DS_trie **list)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			trie_free_word(list[i]);
	free(list);
}

