#include <stdlib.h>

#ifndef stack_ptr_
#define stack_ptr_
typedef struct stack_ptr {
	char **buf;
	size_t ptr;
	size_t len;
} PStack;
#endif

void DS_stack_ptr_new(PStack *s, size_t len);
void DS_stack_ptr_free(PStack *s);
void DS_stack_ptr_grow(PStack *s);
void DS_stack_ptr_push(PStack *s, char *ptr);
char *DS_stack_ptr_pop(PStack *s);

