#include <stdio.h>
#include "DS_trie.h"

int DS_trie_test(void)
{
	DS_trie **trie = NULL;
	int state = 0;

	trie = DS_trie_init(trie);
	trie = DS_trie_add_word(trie, "Youpiiedo");
	trie = DS_trie_add_word(trie, "Aello");
	trie = DS_trie_add_word(trie, "Hello");
	trie = DS_trie_add_word(trie, "Youpie");
	trie = DS_trie_add_word(trie, "Heloo");
	trie = DS_trie_add_word(trie, "Aeloo");
	trie = DS_trie_add_word(trie, "World");
	trie = DS_trie_add_word(trie, "A");
	trie = DS_trie_add_word(trie, "iA");
	trie = DS_trie_add_word(trie, "Helios");
	trie = DS_trie_add_word(trie, "Ylkasdjflnxcvklhasd klasdf asdkljasdf asfdl;;ldfgocivubm akfgou");

	DS_trie_print_list(trie, _func_print_trie);

	if (state)
		printf("false.\n");

	state = DS_trie_is_token(trie, "Heloo");

	if (state)
		printf("true.\n");

	DS_trie_free(trie);

	return 0;
}

