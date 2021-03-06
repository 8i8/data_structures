#include "DS_stack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void DS_stack_new(Stack *s, int elem_size)
{
	assert(elem_size > 0);
	s->elem_size = elem_size;
	s->log_length = 0;
	s->alloc_length = 4;
	s->elems = malloc (4 * elem_size);
	assert(s->elems != NULL);
}

void DS_stack_dispose(Stack *s)
{
	free(s->elems);
}

static void stack_grow(Stack *s)
{
	s->alloc_length <<= 1;
	s->elems = realloc(s->elems, s->alloc_length * s->elem_size);
}

void DS_stack_push(Stack *s, void* elem_addr)
{
	if (s->log_length == s->alloc_length)
		stack_grow(s);

	void *target = (char*)s->elems + s->log_length * s->elem_size;

	memcpy(target, elem_addr, s->elem_size);
	s->log_length++;
}

void DS_stack_pop(Stack *s, void *elem_addr)
{
	s->log_length--;
	void *source = (char*)s->elems + s->log_length * s->elem_size;
	memcpy(elem_addr, source, s->elem_size);
}

