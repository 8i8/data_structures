#include <stdio.h>
#include "../data_structures/DS_Trie.h"

int DS_Trie_test(void)
{
	DS_Trie **trie = NULL;
	int state = 0;

	trie = DS_Trie_init(trie);
	trie = DS_Trie_add_word(trie, "Youpiiedo");
	trie = DS_Trie_add_word(trie, "Aello");
	trie = DS_Trie_add_word(trie, "Hello");
	trie = DS_Trie_add_word(trie, "Youpie");
	trie = DS_Trie_add_word(trie, "Heloo");
	trie = DS_Trie_add_word(trie, "Aeloo");
	trie = DS_Trie_add_word(trie, "World");
	trie = DS_Trie_add_word(trie, "A");
	trie = DS_Trie_add_word(trie, "iA");
	trie = DS_Trie_add_word(trie, "Helios");
	trie = DS_Trie_add_word(trie, "Ylkasdjflnxcvklhasd klasdf asdkljasdf asfdl;;ldfgocivubm akfgou");

	DS_Trie_print_list(trie, _func_print_trie);

	if (state)
		printf("false.\n");

	state = DS_Trie_is_token(trie, "Heloo");

	if (state)
		printf("true.\n");

	DS_Trie_free(trie);

	return 0;
}

