#include <stdio.h>
#include "../data_structures/DS_Trie.h"

int DS_Trie_test(void)
{
	DS_Trie **trie = NULL;

	trie = DS_Trie_init(trie);
	trie = DS_Trie_add_word(trie, "Hello");
	trie = DS_Trie_add_word(trie, "World");
	DS_Trie_output(trie, _func_example);
	DS_Trie_free(trie);

	return 0;
}

