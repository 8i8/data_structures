
typedef struct _stack {
	void *elems;
	int elem_size;
	int log_length;
	int alloc_length;
} Stack;

void DS_Stack_new(stack *s, int elem_size);
void DS_Stack_dispose(stack *s);
void DS_Stack_push(stack *s, void *elem_addr);
void DS_Stack_pop(stack *s, void *elem_addr);
