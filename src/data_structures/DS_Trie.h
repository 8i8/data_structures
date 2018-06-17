#include <stdio.h>

#ifndef _ds_trie_
#define _ds_trie_
typedef struct _ds_Trie {
	char c;
	struct _ds_Trie **next;
	int word_end;
} DS_Trie;
#endif

/* Create a new trie */
DS_Trie **DS_Trie_init(DS_Trie **trie);

/* Add a new word to the trie */
DS_Trie **DS_Trie_add_word(DS_Trie **trie, char *string);

/* Add a n char of a string to the trie */
DS_Trie **DS_Trie_add_n_char(DS_Trie **trie, int len, char *string);

/* Output trie via given function */
void DS_Trie_output(DS_Trie **trie, void (*func)(void*, void*));

/* Dispose of trie */
void DS_Trie_free(DS_Trie **trie);

/* _func_print: Printout the content of the tree from char root to current
 * node */
void _func_example(void *trie, void *var);
