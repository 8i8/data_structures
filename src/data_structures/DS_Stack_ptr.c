#include "DS_Stack_ptr.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Stack
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void DS_Stack_ptr_new(PStack *s, size_t len)
{
	s->len = len;
	s->ptr = 0;
	s->buf = malloc(len * sizeof(char*));
}

void DS_Stack_ptr_free(PStack *s)
{
	free(s->buf);
}

void DS_Stack_ptr_grow(PStack *s)
{
	s->len += s->len;
	s->buf = realloc(s->buf, s->len);
}

void DS_Stack_ptr_push(PStack *s, char *ptr)
{
	if (s->ptr >= s->len)
		DS_Stack_ptr_grow(s);
	s->ptr++;
	s->buf[(s->ptr) - 1] = ptr;
}

char *DS_Stack_ptr_pop(PStack *s)
{
	return s->buf[(s->ptr--) - 1];
}

