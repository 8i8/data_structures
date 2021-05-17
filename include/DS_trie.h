#ifndef DS_TRIE
#define DS_TRIE

#include <stdio.h>

typedef struct ds_Trie {
	int c;
	struct ds_Trie **next;
	int end;
} DS_trie;

/* Create a new trie */
DS_trie **DS_trie_init(DS_trie **trie);

/* Add a new word to the trie */
DS_trie **DS_trie_add_word(DS_trie **trie, char *string);

/* Add a n char of a string to the trie */
DS_trie **DS_trie_add_n_char(DS_trie **trie, int len, char *string);

/* DS_trie_print_list: Output content of trie to the terminal */
DS_trie **DS_trie_print_list(DS_trie **trie, int (*func)(void*, void*));

/* DS_trie_is_token: Iterate over the given string to assertain whether or not
 * it is present in the trie, returns 1 or 0 */
int DS_trie_is_token(DS_trie **trie, char *token);

/* Dispose of trie */
void DS_trie_free(DS_trie **trie);

/* func_print: Printout the content of the tree from char root to current
 * node */
int func_print_trie(void *trie, void *var);

#endif
