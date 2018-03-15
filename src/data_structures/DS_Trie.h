/*
 ============================================================================
 Name        : trie.c trie.h
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL

 Description : trie data structure for C programming.

    Copyright (C) 2018 Iain Hill. 

 ============================================================================
 */
#ifndef _DS_trie_
#define _DS_trie_
typedef struct DS_Trie {
	int c;
	struct Trie **next;
	int word_end;
} DS_Trie;
#endif

/* Create a new trie list */
DS_Trie **tTrie_init(DS_Trie **listing);

/* Add a new word to the trie */
DS_Trie **tTrie_add_word(DS_Trie **list, char *string);

/* Add a n char of a string to the trie */
DS_Trie **tTrie_add_n_char(DS_Trie **list, int len, char *string);

/* Output trie via given function */
void tTrie_output(DS_Trie **list, void (*func)(void*, void*, int), void *var);

/* Dispose of trie */
void tTrie_free(DS_Trie **list);
